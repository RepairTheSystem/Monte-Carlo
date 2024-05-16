#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <cmath>

int inside_circle = 0;
std::mutex mtx;

void monte_carlo_pi(int samples) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    int count = 0;
    for (int i = 0; i < samples; ++i) {
        double x = dis(gen);
        double y = dis(gen);
        if (x * x + y * y <= 1.0) {
            ++count;
        }
    }
    
    std::lock_guard<std::mutex> lock(mtx);
    inside_circle += count;
}

double probability(double eps, int total_samples) {
    return std::min((M_PI / 4) * (1 - (M_PI / 4)) / (total_samples * eps * eps), 1.0);
}

int main() {
    int total_samples;
    std::cin >> total_samples;
    double eps = 0.0001;
    int num_threads = std::thread::hardware_concurrency();
    int samples_per_thread = total_samples / num_threads;

    std::vector<std::thread> threads;
    auto start_time = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(monte_carlo_pi, samples_per_thread);
    }

    for (auto& t : threads) {
        t.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;

    double pi = 4.0 * inside_circle / total_samples;
    double inaccuracy = M_PI - pi;

    std::cout << "Estimated value of Pi: " << pi << std::endl;
    std::cout << "Primitive Inaccuracy: " << inaccuracy << std::endl;
    std::cout << "Calculation time: " << duration.count() << " seconds" << std::endl;
    std::cout << "Accuracy theoretically: " << probability(eps, total_samples) << std::endl;

    return 0;
}
