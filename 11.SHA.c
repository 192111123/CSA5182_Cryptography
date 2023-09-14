#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define SHA1_BLOCK_SIZE 64
#define SHA1_DIGEST_SIZE 20
#define SHA1_ROTL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
typedef struct {
    uint32_t state[5];
    uint64_t count;
    uint8_t buffer[SHA1_BLOCK_SIZE];
} SHA1_CTX;
void sha1_init(SHA1_CTX *ctx) {
    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xEFCDAB89;
    ctx->state[2] = 0x98BADCFE;
    ctx->state[3] = 0x10325476;
    ctx->state[4] = 0xC3D2E1F0;
    ctx->count = 0;
}
void sha1_transform(SHA1_CTX *ctx) {
    uint32_t w[80];
    uint32_t a, b, c, d, e, f, k, temp;
    int t;
    for (t = 0; t < 16; t++)
        w[t] = (ctx->buffer[t * 4] << 24) | (ctx->buffer[t * 4 + 1] << 16) |
               (ctx->buffer[t * 4 + 2] << 8) | (ctx->buffer[t * 4 + 3]);
    for (; t < 80; t++)
        w[t] = SHA1_ROTL(w[t - 3] ^ w[t - 8] ^ w[t - 14] ^ w[t - 16], 1);
    a = ctx->state[0];
    b = ctx->state[1];
    c = ctx->state[2];
    d = ctx->state[3];
    e = ctx->state[4];
    for (t = 0; t < 80; t++) {
        if (t < 20)
            f = (b & c) | ((~b) & d), k = 0x5A827999;
        else if (t < 40)
            f = b ^ c ^ d, k = 0x6ED9EBA1;
        else if (t < 60)
            f = (b & c) | (b & d) | (c & d), k = 0x8F1BBCDC;
        else
            f = b ^ c ^ d, k = 0xCA62C1D6;

        temp = SHA1_ROTL(a, 5) + f + e + k + w[t];
        e = d;
        d = c;
        c = SHA1_ROTL(b, 30);
        b = a;
        a = temp;
    }
    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
    ctx->state[4] += e;
}
void sha1_update(SHA1_CTX *ctx, const uint8_t *data, size_t len) {
    size_t i;
    for (i = 0; i < len; i++) {
        ctx->buffer[ctx->count % SHA1_BLOCK_SIZE] = data[i];
        ctx->count++;
        if (ctx->count % SHA1_BLOCK_SIZE == 0)
            sha1_transform(ctx);
    }
}
void sha1_final(SHA1_CTX *ctx, uint8_t *hash) {
    uint64_t bit_count = ctx->count * 8;
    size_t pad_length = (ctx->count % SHA1_BLOCK_SIZE < 56) ?
                        (56 - ctx->count % SHA1_BLOCK_SIZE) :
                        (120 - ctx->count % SHA1_BLOCK_SIZE);
    uint8_t padding[SHA1_BLOCK_SIZE] = {0x80};
    int i;
    padding[0] = 0x80;
    sha1_update(ctx, padding, pad_length);
    for (i = 0; i < 8; i++) {
        padding[i] = (bit_count >> (56 - i * 8)) & 0xFF;
    }
    sha1_update(ctx, padding, 8);
    for (i = 0; i < SHA1_DIGEST_SIZE; i++) {
        hash[i] = (uint8_t)((ctx->state[i >> 2] >> (24 - (i & 3) * 8)) & 0xFF);
    }
}
void sha1_hash(const uint8_t *data, size_t len, uint8_t *hash) {
    SHA1_CTX ctx;
    sha1_init(&ctx);
    sha1_update(&ctx, data, len);
    sha1_final(&ctx, hash);
}
int main() {
    const char *message = "Hello, SHA-1!";
    uint8_t hash[SHA1_DIGEST_SIZE];
    sha1_hash((const uint8_t *)message, strlen(message), hash);
    printf("SHA-1 Hash: ");
    for (int i = 0; i < SHA1_DIGEST_SIZE; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
    return 0;
}

