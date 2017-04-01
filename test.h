/*
*   Project        : FEEPS202
*   Source File    : test.h
*   Author         : Ilya Levin
*   Created on     : Apr 1, 2017
*
*   A compact and obscure SHA-3 implementation, inspired by @TweetFIPS202
*   https://github.com/ilvn/feeps202
*
*/
#ifndef TEST_H__
#define TEST_H__

#define UNUSED_        __attribute__((unused))
#define ARRAY_SZ(a)    (sizeof(a)/sizeof(a[0]))

typedef unsigned char      u8;
typedef unsigned long long u64;

static const int bits_c[] = {224, 256, 384, 512};

typedef struct {
	char *msg;
	char *kav[ARRAY_SZ(bits_c)];
} test_vector_t;

#if PITHY_VER > 7
#define shake128 crypto_hash_shake128
#define shake256 crypto_hash_shake256
#define sha3_224 crypto_hash_sha3224
#define sha3_256 crypto_hash_sha3256
#define sha3_384 crypto_hash_sha3384
#define sha3_512 crypto_hash_sha3512
#endif

int shake128(u8 *h, const u8 *m, u64 n);
int shake256(u8 *h, const u8 *m, u64 n);
int sha3_224(u8 *h, const u8 *m, u64 n);
int sha3_256(u8 *h, const u8 *m, u64 n);
int sha3_384(u8 *h, const u8 *m, u64 n);
int sha3_512(u8 *h, const u8 *m, u64 n);

#endif
