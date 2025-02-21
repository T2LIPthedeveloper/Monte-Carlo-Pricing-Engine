#include "monte_carlo.h"
#include <iostream>
#include "spdlog/spdlog.h>
#include <unistd.h> // for isatty and fileno

void printUsage() {
    std::cout << "Usage: ./monte_carlo [--export <filename>]\n";
}

int main(int argc, char* argv[]) {
    double S0, K, r, sigma, T;
    int numSimulations;
    char optionType;
    std::string exportFile;

    spdlog::info("Monte Carlo Pricing Engine Started");

    // Check if the input is interactive
    if (!isatty(fileno(stdin))) {
        spdlog::info("Non-interactive mode detected. Using default parameters.");
        S0 = 100;
        K = 110;
        r = 0.05;
        sigma = 0.2;
        T = 1;
        numSimulations = 100000;
        optionType = 'c';
    } else {
        std::cout << "Enter spot price (S0): ";
        std::cin >> S0;
        std::cout << "Enter strike price (K): ";
        std::cin >> K;
        std::cout << "Enter risk-free rate (r): ";
        std::cin >> r;
        std::cout << "Enter volatility (sigma): ";
        std::cin >> sigma;
        std::cout << "Enter time to expiration (T in years): ";
        std::cin >> T;
        std::cout << "Enter number of simulations: ";
        std::cin >> numSimulations;
        std::cout << "Enter option type (c for Call, p for Put): ";
        std::cin >> optionType;
    }

    if (std::cin.fail()) {
        spdlog::error("Invalid input. Please enter correct numeric values.");
        return 1;
    }

    bool isCall = (optionType == 'c' || optionType == 'C');

    MonteCarloPricer pricer(numSimulations, S0, K, r, sigma, T, isCall);
    double price = pricer.runSimulation();

    std::cout << "Monte Carlo Option Price: " << price << std::endl;
    spdlog::info("Option Price: {:.2f}", price);

    if (argc == 3 && std::string(argv[1]) == "--export") {
        exportFile = argv[2];
        pricer.exportResultsToCSV(exportFile);
        std::cout << "Results exported to " << exportFile << std::endl;
    } else if (argc > 1) {
        printUsage();
        return 1;
    }

    spdlog::info("Monte Carlo Pricing Engine Completed");
    return 0;
}
