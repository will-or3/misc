#include <iostream>
#include <cstdint>

// 2^(p-1) * (2^p - 1) 

bool is_prime(uint64_t n){
    if (n<2) return false;

    // if a number has a greater divisor than it's square root
    // it must also have a divisor smaller than it's square root 
    for (uint64_t i = 2; i*i <= n; i++){
        if (n % i == 0)
            return false;
    }

    return true;
}

bool is_prime_exponent(int p){
    return is_prime(p);
}

uint64_t nth_perfect_number(int n){
    int count = 0;

    for (int p = 2; p <= 31; p++){
        if (!is_prime_exponent(p))
            continue;
        
        uint64_t mersenne = (1ULL << p) - 1;

        if (is_prime(mersenne)) {
            count++;

            // 1ULL << p = 2^p
            if (count == n) {
                return (1ULL << (p - 1)) * mersenne;
            }
        }
    }
    return 0;
}

int main(){
    std::cout << 
    nth_perfect_number(5)
    << std::endl;

}