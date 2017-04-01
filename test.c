/*
*   Project        : FEEPS202
*   Source File    : test.c
*   Author         : Ilya Levin
*   Created on     : Apr 1, 2017
*
*   A compact and obscure SHA-3 implementation, inspired by @TweetFIPS202
*   https://github.com/ilvn/feeps202
*/
#include <stdio.h>
#include <string.h>
#include "test.h"


/* -------------------------------------------------------------------------- */
static void dump(const char *prompt, void *mem, size_t len)
{
	size_t i;
	u8 *b;

	if ( (mem != NULL) && (len > 0) ) {
		if ( prompt != NULL )
			printf("%s", prompt);
		for(i = 0, b = (u8 *)mem; i < len; i++)
			printf("%02x%s", b[i], ((i % 16) == 15) ? "\n" : " ");
		printf("\n");
	}
} /* dump */


/* -------------------------------------------------------------------------- */
static int hex2bin(u8 *dst, const char *src) /* unsafe & hacky, but who cares */
{
	int rc = -1;
	u8 j, c;

	if ( (dst != NULL) && (src != NULL) )
		for (j = 0, rc = 0; *src != '\0'; j ^= 1, src++) {
			c = (u8)(*src);
			if ( (c >= '0') && ( c <= '9') ) {
				c = c - '0';
			} else {
				c &= 0xDF;
				if ( (c >= 'A') && ( c <= 'F') ) {
					c = c - 'A' + 10;
				} else {
					rc = -1;
					break;
				}
			}
			if ( j > 0) {
				rc++;
				*dst++ ^= c & 15;
			} else {
				*dst = (u8)((c << 4) & 0xFF);
			}
		}

	return rc;
} /* hex2bin */


/* -------------------------------------------------------------------------- */
static int test(const test_vector_t *p)
{
	u8 hv[512 / 8], ka[512 / 8];
	size_t i, sz, len;
	int rc = -1;

	if ( (p != NULL) && (p->msg != NULL) )
		for (i = 0; i < ARRAY_SZ(bits_c); i++) {
			printf("SHA-3-%d = ", bits_c[i]);
			rc = hex2bin(ka, p->kav[i]);
			if ( rc != (bits_c[i] / 8) ) {
				printf("Invalid test vector\n");
				rc = -2;
				break;
			}
			len = rc & 0xff;
			sz  = strlen(p->msg);

			switch (bits_c[i]) {
				case 224:
					rc = sha3_224(hv, (const u8 *)p->msg, sz);
					break;
				case 256:
					rc = sha3_256(hv, (const u8 *)p->msg, sz);
					break;
				case 384:
					rc = sha3_384(hv, (const u8 *)p->msg, sz);
					break;
				case 512:
					rc = sha3_512(hv, (const u8 *)p->msg, sz);
					break;
				default:
					rc = -3;
					break;
			}
			if ( rc == 0 )
				if ( memcmp(hv, ka, len) != 0 ) {
					printf("Mismatch error\n");
					dump("Computed value:\n", hv, len);
					dump("Test vector:\n", ka, len);
					rc = -4;
				}

			printf("%s\n", (rc == 0) ? "Ok" : "Failed");
			if ( rc != 0 )
				break;
		}

	return rc;
} /* test */


/* -------------------------------------------------------------------------- */
int main(int UNUSED_ argc, char UNUSED_ **argv)
{
	const test_vector_t vec[] = {
		{
			"abc",
			{
				"e642824c3f8cf24ad09234ee7d3c766fc9a3a5168d0c94ad73b46fdf",
				"3a985da74fe225b2045c172d6bd390bd855f086e3e9d525b46bfe24511431532",
				"ec01498288516fc926459f58e2c6ad8df9b473cb0fc08c2596da7cf0e49be4b298d88cea927ac7f539f1edf228376d25",
				"b751850b1a57168a5693cd924b6b096e08f621827444f70d884f5d0240d2712e10e116e9192af3c91a7ec57647e3934057340b4cf408d5a56592f8274eec53f0"
			}
		},
		{
			"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
			{
				"8a24108b154ada21c9fd5574494479ba5c7e7ab76ef264ead0fcce33",
				"41c0dba2a9d6240849100376a8235e2c82e1b9998a999e21db32dd97496d3376",
				"991c665755eb3a4b6bbdfb75c78a492e8c56a22c5c4d7e429bfdbc32b9d4ad5aa04a1f076e62fea19eef51acd0657c22",
				"04a371e84ecfb5b8b77cb48610fca8182dd457ce6f326a0fd3d7ec2f1e91636dee691fbe0c985302ba1b0d8dc78c086346b533b49c030d99a27daf1139d6e75e"
			}
		},
		{
			"",
			{
				"6b4e03423667dbb73b6e15454f0eb1abd4597f9a1b078e3f5b5a6bc7",
				"a7ffc6f8bf1ed76651c14756a061d662f580ff4de43b49fa82d80a4b80f8434a",
				"0c63a75b845e4f7d01107d852e4c2485c51a50aaaa94fc61995e71bbee983a2ac3713831264adb47fb6bd1e058d5f004",
				"a69f73cca23a9ac5c8b567dc185a756e97c982164fe25859e0d1dcc1475c80a615b2123af1f5f94c11e3e9402c3ac558f500199d95b6d3e301758586281dcd26"
			}
		},
		{
			"abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu",
			{
				"543e6868e1666c1a643630df77367ae5a62a85070a51c14cbf665cbc",
				"916f6061fe879741ca6469b43971dfdb28b1a32dc36cb3254e812be27aad1d18",
				"79407d3b5916b59c3e30b09822974791c313fb9ecc849e406f23592d04f625dc8c709b98b43b3852b337216179aa7fc7",
				"afebb2ef542e6579c50cad06d2e578f9f8dd6881d7dc824d26360feebf18a4fa73e3261122948efcfd492e74e82e2189ed0fb440d187f382270cb455f21dd185"
			}
		}
	};
	size_t n;

	for (n = 0; n < ARRAY_SZ(vec); n++) {
		printf("Test #%zu: \"%s\"\n", n, vec[n].msg   );
		printf("Test #%zu = %d\n",    n, test(&vec[n]));
	}

	return 0;
} /* main */





