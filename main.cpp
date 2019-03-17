#include <mbed.h>
#define FREESCALE_MMCAU 1
#ifdef __cplusplus
extern "C" {
#endif
#include "cau_api.h"
#ifdef __cplusplus
}
#endif

Serial pc(USBTX, USBRX, 115200);

unsigned char md5_state[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned char key[16] = "0123456789abcde";
unsigned char key_schedule[44 * 4];
unsigned char plaintext[16] = "Confidential TX";
unsigned char ciphertext[16] = "               ";
unsigned char decryptedtext[16] = "               ";

void printBytesAsHex(const unsigned char *bytes, int len);

int main() {
    pc.printf("MMCAU Test\n");
    pc.printf("MD5 Init\n");
    cau_md5_initialize_output(&md5_state[0]);
    printBytesAsHex(&md5_state[0], 15);
    pc.printf("\n");
    pc.printf("AES Set Key\n");
    cau_aes_set_key(&key[0], 128, &key_schedule[0]);
    printBytesAsHex(&key_schedule[0], 44 * 4);
    pc.printf("\n");
    pc.printf("AES Encrypt\n");
    cau_aes_encrypt(&plaintext[0], &key_schedule[0], 10, &ciphertext[0]);
    pc.printf("Plaintext : ");
    printBytesAsHex(&plaintext[0], 16);
    pc.printf("\nCiphertext: ");
    printBytesAsHex(&ciphertext[0], 16);
    pc.printf("\n");
    pc.printf("AES Decrypt\n");
    cau_aes_decrypt(&ciphertext[0], &key_schedule[0], 10, &decryptedtext[0]);
    pc.printf("Plaintext : ");
    printBytesAsHex(&decryptedtext[0], 16);
    pc.printf("\n");
    return 0;
}

void printBytesAsHex(const unsigned char *bytes, int len) {
    int i;

    for (i = 0; i < len; i += 1) {
        pc.printf("%02x ", bytes[i]);
    }
}