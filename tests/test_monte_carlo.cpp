#include "monte_carlo.h"
#include "spdlog/spdlog.h"
#include <gtest/gtest.h>
#include <fstream>
#include <cmath>

constexpr double EPSILON = 1e-3;

bool nearlyEqual(double a, double b, double epsilon = EPSILON) {
    return std::fabs(a - b) < epsilon;
}

TEST(MonteCarloTests, BasicPricingTest) {
    // Run simulation with a large number of iterations for convergence check
    MonteCarloPricer pricer(100000, 100, 100, 0.05, 0.2, 1, true);
    double price = pricer.runSimulation();
    spdlog::info("Test Option Price: {:.2f}", price);
    EXPECT_GT(price, 0);
}

TEST(MonteCarloTests, CSVExportTest) {
    MonteCarloPricer pricer(1000, 100, 100, 0.05, 0.2, 1, true);
    pricer.runSimulation();
    pricer.exportResultsToCSV("test_results.csv");

    std::ifstream file("test_results.csv");
    EXPECT_TRUE(file.good());
    file.close();
}

TEST(MonteCarloTests, MarketDataImportTest) {
    // Create a temporary CSV file with dummy market data
    std::ofstream file("dummy_market.csv");
    file << "100,105,110\n";
    file << "200,210,220\n";
    file.close();

    auto data = MonteCarloPricer::importMarketDataFromCSV("dummy_market.csv");
    EXPECT_EQ(data.size(), 2);
    EXPECT_EQ(data[0].size(), 3);

    std::remove("dummy_market.csv");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
