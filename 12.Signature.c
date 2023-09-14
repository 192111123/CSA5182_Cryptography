#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
uint64_t mod_exp(uint64_t base, uint64_t exponent, uint64_t modulus) {
    uint64_t result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}
void dsa_keygen(uint64_t q, uint64_t alpha, uint64_t *private_key, uint64_t *public_key) {
    *private_key = 1 + rand() % (q - 1);
    *public_key = mod_exp(alpha, *private_key, q);
}
void dsa_sign(uint64_t q, uint64_t alpha, uint64_t private_key, const uint8_t *message, size_t message_len, uint64_t *r, uint64_t *s) {
    uint64_t k, inv_k;
    do {
        k = 1 + rand() % (q - 1);
        inv_k = mod_exp(k, q - 2, q);
        *r = mod_exp(alpha, k, q);
        *r = *r % q;
    } while (*r == 0);

    uint64_t hash = 0;
    for (size_t i = 0; i < message_len; ++i) {
        hash = (hash * 256 + message[i]) % q;
    }
    *s = (inv_k * (hash + private_key * (*r))) % q;
}
int dsa_verify(uint64_t q, uint64_t alpha, uint64_t public_key, const uint8_t *message, size_t message_len, uint64_t r, uint64_t s) {
    if (r <= 0 || r >= q || s <= 0 || s >= q) {
        return 0; 
    }
    uint64_t w = mod_exp(s, q - 2, q);
    uint64_t hash = 0;
    for (size_t i = 0; i < message_len; ++i) {
        hash = (hash * 256 + message[i]) % q;
    }
    uint64_t u1 = (hash * w) % q;
    uint64_t u2 = (r * w) % q;
    uint64_t v = (mod_exp(alpha, u1, q) * mod_exp(public_key, u2, q)) % q;
    v = v % q;
    return v == r;
}
int main() {
    srand(time(NULL));
    uint64_t q = 100;   
    uint64_t alpha = 5;  
    uint64_t private_key, public_key;
    dsa_keygen(q, alpha, &private_key, &public_key);
    const uint8_t message[] = "hello siri";
    size_t message_len = strlen((char *)message);
    uint64_t r, s;
    dsa_sign(q, alpha, private_key, message, message_len, &r, &s);
    int verified = dsa_verify(q, alpha, public_key, message, message_len, r, s);
    if (verified) {
        printf("Signature verified successfully.\n");
    } else {
        printf("Signature verification failed.\n");
    }
    return 0;
}
