# Monte Carlo Pricing Engine

A high-performance options pricing engine using C++ and Geometric Brownian Motion (GBM) simulations. Designed for **speed, efficiency, and robustness**, with support for **multithreading, logging, CSV export, and CI/CD**.

## 🚀 Features
- **Geometric Brownian Motion (GBM)** for realistic asset price modeling.
- **Multithreading** for faster simulations.
- **Logging with `spdlog`** for better debugging.
- **CSV import/export** for data handling.
- **Cross-platform compatibility** (Linux, Mac, Windows).
- **Dockerized build & deployment** with multi-stage optimization.
- **Unit tests with GoogleTest** (`gtest`).
- **Continuous Integration (CI) ready**.

---

## 🔧 Installation

### **1. Clone the repository**
```sh
git clone https://github.com/T2LIPthedeveloper/Monte-Carlo-Pricing-Engine.git
cd Monte-Carlo-Pricing-Engine
```

### **2. Build with CMake**
```sh
mkdir build && cd build
cmake .. -G Ninja
ninja
```

### **3. Run the executable**
```sh
./monte_carlo
```

---

## 🖥️ Usage

### **CLI Mode**
```sh
./monte_carlo
```
**Example Input:**
```
Enter spot price (S0): 100
Enter strike price (K): 110
Enter risk-free rate (r): 0.05
Enter volatility (sigma): 0.2
Enter time to expiration (T in years): 1
Enter number of simulations: 100000
Enter option type (c for Call, p for Put): c
```
**Example Output:**
```
Monte Carlo Option Price: 7.89
```

### **Export to CSV**
```sh
./monte_carlo --export results.csv
```

---

## 🐳 Running with Docker

### **Build the Docker Image**
```sh
docker build -t monte-carlo-pricer .
```

### **Run the Container**
```sh
docker run --rm monte-carlo-pricer
```

---

## 🧪 Running Tests
```sh
cd build
ctest --output-on-failure
```

---

## 📂 Project Structure
```
├── src/
│   ├── monte_carlo.h      # Monte Carlo implementation
│   ├── monte_carlo.cpp    # Pricing logic with GBM, multithreading
│   ├── main.cpp           # CLI interface
│   ├── utils.h/.cpp       # Helper functions (CSV, logging)
│   ├── tests/             # Unit tests (GoogleTest)
│── CMakeLists.txt         # Build configuration
│── Dockerfile             # Multi-stage Docker build
│── README.md              # Documentation
```

---

## 📌 Future Improvements
- Implement support for **stochastic volatility models** (Heston Model).
- Add a **REST API** wrapper for web integration.
- Support for **American-style options** via Least Squares Monte Carlo (LSM).

---

## 🛠️ Contributing
Feel free to submit PRs! Follow the standard C++ style guidelines.

---

## 🏆 License
MIT License

Copyright (c) 2025 Atul Parida

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


---

## 📩 Contact
For queries, reach out at [atul.parida@outlook.com].
