#include <stdio.h>
#include <stdlib.h>
#include <math.h>
unsigned long long power_modulo(unsigned long long base, unsigned long long exponent, unsigned long long modulus) 
{
    unsigned long long result = 1;
    base = base % modulus; 
    while (exponent > 0) 
	{
        if (exponent % 2 == 1)
            result = (result * base) % modulus;       
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}
int main()
 {
    unsigned long long prime = 23; 
    unsigned long long base = 5;  
    unsigned long long private_a = 6;
    unsigned long long private_b = 15;
    unsigned long long public_a = power_modulo(base, private_a, prime);
    unsigned long long public_b = power_modulo(base, private_b, prime);
    unsigned long long secret_a = power_modulo(public_b, private_a, prime);
    unsigned long long secret_b = power_modulo(public_a, private_b, prime);
    printf("Prime: %llu\nBase: %llu\n\n", prime, base);
    printf("A's private key: %llu\nB's private key: %llu\n\n", private_a, private_b);
    printf("A's public key: %llu\nB's public key: %llu\n\n", public_a, public_b);
    printf("Shared secret key for A: %llu\nShared secret key for B: %llu\n\n", secret_a, secret_b);
    return 0;
}

