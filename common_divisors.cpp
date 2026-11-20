#include <iostream>
#include <vector>
#include <unordered_map>

std::vector<int> factorize(int n) {
    std::vector<int> factors;

    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }

    if (n > 1)
        factors.push_back(n);

    return factors;
}

// count how many times each element occurs in the vector
std::unordered_map<int, int> get_exponents(const std::vector<int>& factors) {
    std::unordered_map<int, int> exponents;

    for (int x : factors) {
        exponents[x]++; //every time a prime appears its value increases
    }

    return exponents;
}

int get_total_divisors(std::unordered_map<int, int>& exponents) {
    int total = 1;

    for (auto [prime, exponent] : exponents) {
        total *= (exponent + 1);
    }

    return total;
}

int get_perf_sqr_divisors(std::unordered_map<int, int>& exponents) {
    int total = 1;

    for (auto [prime, exponent] : exponents) {
        total *= ((exponent/2) + 1); //automatic truncate
    }

    return total;
}



int main() {
    int n = 360;

    std::vector<int> factors = factorize(n);

    std::unordered_map<int, int> exponents = get_exponents(factors);

    std::cout << 
    get_perf_sqr_divisors(exponents)
    << std::endl;

    
}