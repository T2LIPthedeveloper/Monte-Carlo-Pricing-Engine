#include "monte_carlo.h"
#include <cmath>
#include <random>
#include <thread>
#include <fstream>
#include <sstream>
#include <iostream>
#include "spdlog/spdlog.h"

MonteCarloPricer::MonteCarloPricer(size_t numSimulations, double spotPrice, double strikePrice,
                                   double riskFreeRate, double volatility, double timeToMaturity, bool isCall)
    : numSimulations(numSimulations), spotPrice(spotPrice), strikePrice(strikePrice),
      riskFreeRate(riskFreeRate), volatility(volatility), timeToMaturity(timeToMaturity), isCall(isCall) {
    spdlog::info("Monte Carlo Pricer initialized with {} simulations.", numSimulations);
}

double MonteCarloPricer::generateGaussianNoise() {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::normal_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

double MonteCarloPricer::simulateGBM() {
    double drift = (riskFreeRate - 0.5 * volatility * volatility) * timeToMaturity;
    double diffusion = volatility * std::sqrt(timeToMaturity) * generateGaussianNoise();
    return spotPrice * std::exp(drift + diffusion);
}

double MonteCarloPricer::optionPayoff(double finalPrice) {
    return isCall ? std::max(0.0, finalPrice - strikePrice)
                  : std::max(0.0, strikePrice - finalPrice);
}

double MonteCarloPricer::runSimulation() {
    size_t numThreads = std::thread::hardware_concurrency();
    if(numThreads == 0) numThreads = 2; // Fallback

    std::vector<std::thread> threads;
    std::vector<double> threadResults(numThreads, 0.0);
    size_t simulationsPerThread = numSimulations / numThreads;
    size_t remainingSimulations = numSimulations % numThreads;

    auto worker = [&](size_t threadId, size_t sims) {
        double sumPayoff = 0.0;
        for (size_t i = 0; i < sims; ++i) {
            double finalPrice = simulateGBM();
            sumPayoff += optionPayoff(finalPrice);
        }
        // Protect shared result vector
        std::lock_guard<std::mutex> lock(mtx);
        threadResults[threadId] = sumPayoff;
    };

    for (size_t i = 0; i < numThreads; ++i) {
        size_t sims = simulationsPerThread + (i < remainingSimulations ? 1 : 0);
        threads.emplace_back(worker, i, sims);
    }

    for (auto &t : threads)
        t.join();

    double totalPayoff = 0.0;
    for (double result : threadResults)
        totalPayoff += result;

    double optionPrice = (totalPayoff / numSimulations) * std::exp(-riskFreeRate * timeToMaturity);
    spdlog::info("Option price estimated: ${:.2f}", optionPrice);
    return optionPrice;
}

void MonteCarloPricer::exportResultsToCSV(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        spdlog::error("Failed to open file: {}", filename);
        return;
    }

    file << "Simulation,OptionPrice\n";
    for (size_t i = 0; i < simulatedPrices.size(); ++i) {
        file << i + 1 << "," << simulatedPrices[i] << "\n";
    }

    file.close();
    spdlog::info("Results exported to {}", filename);
}

std::vector<std::vector<double>> MonteCarloPricer::importMarketDataFromCSV(const std::string& filename) {
    std::vector<std::vector<double>> marketData;
    std::ifstream file(filename);
    if (!file.is_open()) {
        spdlog::error("Failed to open market data file: {}", filename);
        return marketData;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<double> row;
        std::string value;
        while (std::getline(ss, value, ',')) {
            try {
                row.push_back(std::stod(value));
            } catch (...) {
                spdlog::warn("Skipping invalid value in CSV: {}", value);
            }
        }
        if (!row.empty()) {
            marketData.push_back(row);
        }
    }
    file.close();
    spdlog::info("Market data imported from {}", filename);
    return marketData;
}
