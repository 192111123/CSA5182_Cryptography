#include <stdio.h>
#include <stdint.h>
#include "blowfish.h"

int main() {
    // Initialize the Blowfish cipher with a key
    uint32_t P[18] = { /* ... */ };  // Replace with actual subkeys
    uint32_t S[4][256] = { /* ... */ };  // Replace with actual S-boxes
    char key[] = "MySecret"; // Replace with your desired key
    BF_key_setup((uint32_t*)key, P, S);

    // Message to encrypt (64 bits)
    uint32_t data[2] = {0x01234567, 0x89ABCDEF};

    // Encrypt the message
    BF_encrypt(data, P, S);

    // Display the results
    printf("Encrypted: %08X %08X\n", data[0], data[1]);

    // Decrypt the message
    BF_decrypt(data, P, S);

    // Display the decrypted message
    printf("Decrypted: %08X %08X\n", data[0], data[1]);

    return 0;
}
