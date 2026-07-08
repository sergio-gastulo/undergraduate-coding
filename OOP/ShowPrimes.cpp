#include<iostream>
#include<sstream>

bool isPrime(int p) {
    if (p <= 1)
        return false;

    for (int i = 2; i * i <= p; i++)
        if (p % i == 0)
            return false;
    return true;
}


void showPrimes(int low, int upper) {
    std::ostringstream oss;
    oss << "[";
    bool first = true;
    for (int i = low; i < upper; i++) {
        if (isPrime(i)) {
            if (!first) 
                oss << ", ";
            oss << i;
            first = false;
        }
    }
    oss << "]" << std::endl;
    std::cout << oss.str();
}

int main(int argc, char* argv[]) {
    
    long int lower_bound, upper_bound;       // inclusive
    if (argc == 3) {
        lower_bound = std::strtol(argv[1], NULL, 10);
        upper_bound = std::strtol(argv[2], NULL, 10);
    } else {
        lower_bound = 100;
        upper_bound = 200;
        std::cout   << "Pass lower and upper bounds: " 
                    << "[.exe] [lower = " << lower_bound << "]" 
                    << "[upper = "<< upper_bound << "]" 
                    << std::endl;
    }
    std::cout   << "lower_bound = " << lower_bound << std::endl
                << "upper_bound = " << upper_bound << std::endl;
    showPrimes(lower_bound, upper_bound);
    return 0;
}