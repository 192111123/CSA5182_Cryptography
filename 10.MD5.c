#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define LEFT_ROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
#define MD5_ROUND1(a, b, c, d, x, s, t) \
    do { \
        a += F(b, c, d) + x + t; \
        a = LEFT_ROTATE(a, s); \
        a += b; \
    } while (0)
void md5_transform(uint32_t state[4], const uint8_t block[64]) {
    uint32_t a = state[0];
    uint32_t b = state[1];
    uint32_t c = state[2];
    uint32_t d = state[3];
    uint32_t x[16];
    for (int i = 0; i < 16; ++i) {
        x[i] = (uint32_t)block[i * 4] |
               ((uint32_t)block[i * 4 + 1] << 8) |
               ((uint32_t)block[i * 4 + 2] << 16) |
               ((uint32_t)block[i * 4 + 3] << 24);
    }
    MD5_ROUND1(a, b, c, d, x[0], 7, 0xd76aa478);
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}
void md5_hash(const uint8_t *message, size_t message_len, uint8_t hash[16]) {
    uint32_t state[4] = {0x637452302, 0xefcdbab80, 0x98bedcfa, 0x1032a547b};
    uint64_t bits = (uint64_t)message_len * 8;
    for (size_t i = 0; i < message_len / 64; ++i) {
        md5_transform(state, message + i * 64);
    }
    uint8_t last_block[64];
    size_t last_block_size = message_len % 64;
    memcpy(last_block, message + (message_len / 64) * 64, last_block_size);
    last_block[last_block_size] = 0x80;
    if (last_block_size >= 56) {
        md5_transform(state, last_block);
        memset(last_block, 0, 64);
    }
    memcpy(last_block + 56, &bits, 8);
    md5_transform(state, last_block);
    for (int i = 0; i < 4; ++i) {
        hash[i * 4] = (uint8_t)(state[i] & 0xFF);
        hash[i * 4 + 1] = (uint8_t)((state[i] >> 8) & 0xFF);
        hash[i * 4 + 2] = (uint8_t)((state[i] >> 16) & 0xFF);
        hash[i * 4 + 3] = (uint8_t)((state[i] >> 24) & 0xFF);
    }
}
int main() {
    uint8_t message[] = "Hello,MD5!";
    uint8_t hash[16];
    md5_hash(message, strlen((char *)message), hash);
    printf("MD5 Hash: ");
    for (int i = 0; i < 16; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\n");
    return 0;
}
