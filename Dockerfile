# Stage 1: Build
FROM gcc:latest AS builder

# Install dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    ninja-build \
    libgtest-dev \
    libspdlog-dev \
    && apt-get clean

# Set working directory
WORKDIR /app

# Copy source files
COPY . .

# Create build directory and build the project using Ninja
RUN mkdir -p build && cd build && cmake .. -G Ninja && ninja

# Run unit tests
RUN cd build && ctest --output-on-failure

# Stage 2: Runtime - use gcc image to ensure compatible libstdc++
FROM gcc:latest

# Install runtime dependencies
RUN apt-get update && apt-get install -y libspdlog-dev && apt-get clean

# Set working directory
WORKDIR /app

# Copy built executable from builder stage
COPY --from=builder /app/build/monte_carlo .

# Default command to run the pricing engine
CMD ["./monte_carlo"]
