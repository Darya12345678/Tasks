#include <iostream>
#include <random>
#include <mutex>
#include <vector>
#include <thread>

std::mutex accumulator_mutex;
std::vector<double> accumulator;
std::mt19937 rng;

void simulateGame(int iterations) {
    std::vector<double> local_accumulator(iterations);
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < iterations; ++i) {
        double r = distribution(rng);
        double p1 = 0.15;

        if (r < p1) {
            std::vector<int> Ws = {0, 1, 2, 3, 5, 7, 10, 50, 100, 200, 500};
P(W1) = 0.292, P(W2) = 0.038, P(W3) = 0.061, P(W4) = 0.098, P(W5) = 0.106, P(W6) = 0.098, P(W7) = 0.086, P(W8) = 0.032, P(W9) = 0.027, P(W10) = 0.091, P(W11) = 0.071.

            std::vector<double> ps = {0.292, 0.038, 0.061, 0.098, 0.106, 0.098, 0.086, 0.032, 0.027, 0.091, 0.071};

            std::discrete_distribution<int> W_distribution(ps.begin(), ps.end());
            int W = Ws[W_distribution(rng)];

            local_accumulator[i] = W;
        } else {
            local_accumulator[i] = 0;
        }
    }
    std::lock_guard<std::mutex> lock(accumulator_mutex);
    accumulator.insert(accumulator.end(), local_accumulator.begin(), local_accumulator.end());
}

int main() {
    int num_threads = 4;
    int iterations_per_thread = 100000;

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(simulateGame, iterations_per_thread);
    }

    for (auto& thread : threads) {
        thread.join();
    }
    // Вывод результатов
    for (int i = 0; i < accumulator.size(); ++i) {
        std::cout << "Iteration " << i << ": " << accumulator[i] << std::endl;
    }
    return 0;
}
