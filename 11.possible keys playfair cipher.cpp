#include <stdio.h>
#include <math.h>

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int main() {
    int unique_letters = 24;
    unsigned long long total_permutations = factorial(unique_letters);

    // Output the number of possible keys (ignoring identical encryption results)
    printf("Number of possible keys (ignoring identical encryption results): %llu\n", total_permutations);

    // Estimate the number of effectively unique keys considering identical encryption results
    unsigned long long effectively_unique_keys = total_permutations / 2; // Approximation
    printf("Number of effectively unique keys (considering identical encryption results): %llu\n", effectively_unique_keys);

    // Express the number of effectively unique keys as an approximate power of 2
    int power_of_2 = log2(effectively_unique_keys);
    printf("Number of effectively unique keys expressed as an approximate power of 2: 2^%d\n", power_of_2);

    return 0;
}