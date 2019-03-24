#include <mbed.h>
#include <stdint.h>
#include "counter.h"

enum controlData {N_ITERATIONS = 100};

Serial pc(USBTX, USBRX, 115200);

unsigned char key[16] = "0123456789abcde";
unsigned char plaintext[16] = "Confidential TX";
unsigned char ciphertext[16] = "               ";
unsigned char decryptedtext[16] = "               ";


mbedtls_aes_context aes_ctx;
unsigned char *key_schedule = (unsigned char *)&aes_ctx.buf;

void printBytesAsHex(const unsigned char *bytes, int len);
void displayStats(uint32_t, uint32_t, uint32_t, uint64_t);

int main() {
    int i;
    int ret;
    uint32_t timeElapsed = 0;
    uint32_t minTime = 0xFFFFFFFF;
    uint32_t meanTime = 0;
    uint32_t maxTime = 0;
    uint64_t totalTime = 0;

    counterInit();
    pc.printf("Time AES functions\n");
    pc.printf("MBED TLS Set Enc Key\n");
    mbedtls_aes_init(&aes_ctx);
    ret = mbedtls_aes_setkey_enc(&aes_ctx, key, 128);
    for (i = 0; i < 4; i += 1) {
        printBytesAsHex(&key_schedule[i * 44], 44);
        pc.printf("\n");
    }
    pc.printf("AES Encrypt\n");
    /* Reset all statistics
     */
    minTime = 0xFFFFFFFF;
    meanTime = 0;
    maxTime = 0;
    totalTime = 0;
    /* Repeatedly measure the execution time of the code in
     * which we are interested - this is the 'Software under test'
     */
    for (int i = N_ITERATIONS; i > 0; i-=1) {
      counterStart();
      /********* Software under test *********************/
      mbedtls_internal_aes_encrypt(&aes_ctx, plaintext, ciphertext);
      /********* End Software under test ****************/
      timeElapsed = counterStop();
      if (timeElapsed < minTime) {
        minTime = timeElapsed;
      }
      if (timeElapsed > maxTime) {
        maxTime = timeElapsed;
      }
      totalTime += timeElapsed;
    }

    /* Display the statistics that have been captured */
    meanTime = totalTime / N_ITERATIONS;
    displayStats(minTime, meanTime, maxTime, totalTime);
    pc.printf("Plaintext : ");
    printBytesAsHex(plaintext, 16);
    pc.printf("\nCiphertext: ");
    printBytesAsHex(ciphertext, 16);
    pc.printf("\n");
    pc.printf("MBED TLS Set Dec Key\n");
    mbedtls_aes_init(&aes_ctx);
    ret = mbedtls_aes_setkey_dec(&aes_ctx, key, 128);
    for (i = 0; i < 4; i += 1) {
        printBytesAsHex(&key_schedule[i * 44], 44);
        pc.printf("\n");
    }
    pc.printf("AES Decrypt\n");
    /* Reset all statistics
     */
    minTime = 0xFFFFFFFF;
    meanTime = 0;
    maxTime = 0;
    totalTime = 0;
    /* Repeatedly measure the execution time of the code in
     * which we are interested - this is the 'Software under test'
     */
    for (int i = N_ITERATIONS; i > 0; i-=1) {
      counterStart();
      /********* Software under test *********************/
      mbedtls_internal_aes_decrypt(&aes_ctx, ciphertext, decryptedtext);
      /********* End Software under test ****************/
      timeElapsed = counterStop();
      if (timeElapsed < minTime) {
        minTime = timeElapsed;
      }
      if (timeElapsed > maxTime) {
        maxTime = timeElapsed;
      }
      totalTime += timeElapsed;
    }

    /* Display the statistics that have been captured */
    meanTime = totalTime / N_ITERATIONS;
    displayStats(minTime, meanTime, maxTime, totalTime);
    pc.printf("Plaintext : ");
    printBytesAsHex(decryptedtext, 16);
    pc.printf("\n");
    return 0;
}

void printBytesAsHex(const unsigned char *bytes, int len) {
    int i;

    for (i = 0; i < len; i += 1) {
        pc.printf("%02x ", bytes[i]);
    }
}

void displayStats(uint32_t minTime,
                  uint32_t meanTime,
                  uint32_t maxTime,
                  uint64_t totalTime) {
  pc.printf("Min  : %020lu\n", minTime);
  pc.printf("Mean : %020lu\n", meanTime);
  pc.printf("Max  : %020lu\n", maxTime);
  pc.printf("Tot  : %020llu\n", totalTime);
}

