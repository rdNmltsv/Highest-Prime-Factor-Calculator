#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>
#include <limits>
#include <chrono>

template<typename T>
void printVector(const std::vector<T>& data) {
    std::copy(data.begin(), data.end(), std::ostream_iterator<T>(std::cout, " "));
}

template<typename T>
T getMaxElem(std::vector<T> &&factors) {
    return *std::max_element(factors.begin(), factors.end());
}

/* Trial division integer factorization algorithm */
template<typename T>
std::vector<T> trialDivision(T n) {
    std::vector<T> factors{};
    for (T i = 2; i <= std::sqrt(n); i++) {
        while (n % i == 0) {
            factors.emplace_back(i);
            n /= i;
        }
    }

    if (n != 1)
        factors.emplace_back(n);

    return factors;
}

int main()
{
    std::cout << "<< Highest Prime Factor Calculator >>";

    for (;;) {

        std::cout << "\nEnter positive real number (EOF to exit): ";
        long long n{};
        std::cin >> n;

        if (std::cin.eof())
            break;

        if (std::cin.fail() || n < 0) {
            std::cout << "You must enter positive real number.";
        }
        else {        
            auto startTime = std::chrono::high_resolution_clock::now();

            auto factorFunc = trialDivision<decltype(n)>;

            auto prime = getMaxElem(std::move(factorFunc(n)));

            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsedTime_ms = endTime - startTime;

            std::cout << "Highest prime factor of " << n << " is " << prime << '.';
          
            std::cout << "\nElapsed time is " << std::fixed << std::setprecision(3) << elapsedTime_ms.count() << " ms.";
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "\nExiting..." << std::endl;
    return EXIT_SUCCESS;
}
