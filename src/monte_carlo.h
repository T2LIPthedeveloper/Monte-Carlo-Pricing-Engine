#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include <vector>
#include <string>
#include <mutex>

class MonteCarloPricer {
public:
    MonteCarloPricer(size_t numSimulations, double spotPrice, double strikePrice,
                     double riskFreeRate, double volatility, double timeToMaturity, bool isCall);

    double runSimulation(); // Runs Monte Carlo Simulation
    void exportResultsToCSV(const std::string& filename);
    static std::vector<std::vector<double>> importMarketDataFromCSV(const std::string& filename);

private:
    size_t numSimulations;
    double spotPrice;
    double strikePrice;
    double riskFreeRate;
    double volatility;
    double timeToMaturity;
    bool isCall;
    std::vector<double> simulatedPrices;
    std::mutex mtx;

    double simulateGBM(); // Simulate stock path via GBM
    double optionPayoff(double finalPrice);
    static double generateGaussianNoise();
};

#endif // MONTE_CARLO_H
