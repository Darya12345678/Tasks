#include <iostream>
#include <cmath>
#include <random>
// Функция для вычисления математического ожидания
double calculateExpectedValue(const std::vector<double>& ws, const std::vector<double>& ps) {
    double expectedValue = 0.0;
    for (int i = 0; i < ws.size(); i++) {
        expectedValue += ws[i] * ps[i];
    }
    return expectedValue;
}

// Функция для вычисления дисперсии
double calculateVariance(const std::vector<double>& ws, const std::vector<double>& ps, double expectedValue) {
    double variance = 0.0;
    for (int i = 0; i < ws.size(); i++) {
        variance += pow(ws[i] - expectedValue, 2) * ps[i];
    }
    return variance;
}
// Функция для проверки требований E(W) и D(W)
bool checkRequirements(double expectedValue, double variance) {
    double requiredExpectedValue = 0.95;
    double requiredVariance = 154.0;
    double epsilon = 0.005;
    double varianceEpsilon = 0.5;
    if (std::abs(expectedValue - requiredExpectedValue) <= epsilon &&
        std::abs(variance - requiredVariance) <= varianceEpsilon) {
        return true;
    }
    return false;
  }

int main() {
    std::vector<double> ws = {0, 1, 2, 3, 5, 7, 10, 50, 100, 200, 500};
    std::vector<double> ps(ws.size(), 0.0);

    // Инициализация вероятностей p1, p2, ..., p11(начальные значения могут быть произвольными)
    ps[0] = 0.1;
    ps[1] = 0.1;
    // ...
    bool requirementsMet = false;
    int iterations = 0;

    while (!requirementsMet) {
        iterations++;
     // Моделирование игрового процесса
        std::random_device rd;
        std::mt19937 gen(rd());
        std::discrete_distribution<> d(ps.begin(), ps.end());
        int positiveWins = 0;
        int totalIterations = 1000000; // Количество итераций моделирования
        for (int i = 0; i < totalIterations; i++) {
            int prizeIndex = d(gen);
            if (ws[prizeIndex] > 0) {
                positiveWins++;
            }
        }
        // Обновление вероятностей на основе результатов моделирования
        for (int i = 0; i < ws.size(); i++) {
            ps[i] = static_cast<double>(positiveWins) / totalIterations;
        }

        // Вычисление E(W) и D(W)
        double expectedValue = calculateExpectedValue(ws, ps);
        double variance = calculateVariance(ws, ps, expectedValue);

        // Проверка требований
        requirementsMet = checkRequirements(expectedValue, variance);
    }
    std::cout << "Требуемые вероятности ps: ";
    for (int i = 0; i < ps.size(); i++) {
        std::cout << ps[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Количество итераций: " << iterations << std::endl;
    return 0;
}
