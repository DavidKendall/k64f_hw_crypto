## Introduction

A very simple demo of some of the MMCAU API functions using the 
[Freescale library](https://www.nxp.com/products/processors-and-microcontrollers/additional-processors-and-mcus/coldfire-plus-coldfire/crypto-acceleration-unit-cau-and-mmcau-software-library:CAUAP)
and ARM mbed OS-5.

## Building with mbed-cli

1. Import the repository

     ```sh
     $ mbed import https://github.com/davidkendall/k64f_hw_crypto
     ```
1. Change the current working directory to the repository and copy `targets.json` to `mbed-os/targets`

     ```sh
     $ cd k64f_hw_crypto
     $ cp targets.json mbed-os/targets
     ```

1. Connect an FRDM-K64F board and make sure that it is mounted.

1. Start a `minicom` session with parameters `115200 8N1`

1. Compile the program and flash the board

     ```sh
     $ mbed compile -t GCC_ARM -m K64F -f
     ```

1. If necessary, press `reset` to execute the code.

## Output

The program illustrates the use of the following functions which are used to
replace the standard `mbedtls` AES functions:

* `cau_aes_set_key -> mbedtls_aes_setkey_enc`
* `cau_aes_set_key -> mbedtls_aes_setkey_dec`
* `cau_aes_encrypt -> mbedtls_internal_aes_encrypt`
* `cau_aes_decrypt -> mbedtls_internal_aes_decrypt`

If all is well, you should see some output like the following

```
Time AES functions
MBED TLS Set Enc Key
33 32 31 30 37 36 35 34 62 61 39 38 00 65 64 63 c8 51 7c 72 ff 67 49 46 9d 06 70 7e 9d 63 14 1d 6c 0f 87 8a 93 68 ce cc 0e 6e be b2
93 0d aa af 15 d3 50 22 86 bb 9e ee 88 d5 20 5c 1b d8 8a f3 18 7c 31 54 9e c7 af ba 16 12 8f e6 0d ca 05 15 41 ab 45 2f df 6c ea 95
c9 7e 65 73 c4 b4 60 66 72 b7 c8 df ad db 22 4a 64 a5 47 39 a0 11 27 5f bd 57 4a 53 10 8c 68 19 74 29 2f 20 d4 38 08 7f 6f 1f 4d e3
7f 93 25 fa 0b ba 0a da df 82 02 a5 69 81 5e 8f 16 12 7b 75 1d a8 71 af c2 2a 73 0a 0e a4 bb 36 18 b6 c0 43 05 1e b1 ec c7 34 c2 e6
AES Encrypt
Min  : 00000000000000000166
Mean : 00000000000000000166
Max  : 00000000000000000169
Tot  : 00000000000000016603
Plaintext : 43 6f 6e 66 69 64 65 6e 74 69 61 6c 20 54 58 00
Ciphertext: 18 b0 6c c5 eb bf 0e 9e 23 68 27 55 ed fd eb ca
MBED TLS Set Dec Key
33 32 31 30 37 36 35 34 62 61 39 38 00 65 64 63 c8 51 7c 72 ff 67 49 46 9d 06 70 7e 9d 63 14 1d 6c 0f 87 8a 93 68 ce cc 0e 6e be b2
93 0d aa af 15 d3 50 22 86 bb 9e ee 88 d5 20 5c 1b d8 8a f3 18 7c 31 54 9e c7 af ba 16 12 8f e6 0d ca 05 15 41 ab 45 2f df 6c ea 95
c9 7e 65 73 c4 b4 60 66 72 b7 c8 df ad db 22 4a 64 a5 47 39 a0 11 27 5f bd 57 4a 53 10 8c 68 19 74 29 2f 20 d4 38 08 7f 6f 1f 4d e3
7f 93 25 fa 0b ba 0a da df 82 02 a5 69 81 5e 8f 16 12 7b 75 1d a8 71 af c2 2a 73 0a 0e a4 bb 36 18 b6 c0 43 05 1e b1 ec c7 34 c2 e6
AES Decrypt
Min  : 00000000000000000171
Mean : 00000000000000000171
Max  : 00000000000000000171
Tot  : 00000000000000017100
Plaintext : 43 6f 6e 66 69 64 65 6e 74 69 61 6c 20 54 58 00
LoRaMacCrypto Functions
MIC
c8 ff 13 ea 00 00 00 00 00 00 00 00 00 00 00 00
ENC
23 fe cd 20 62 0e bd 2d 1e ea d2 e0 83 0f e7 4a
DEC
43 6f 6e 66 69 64 65 6e 74 69 61 6c 20 54 58 00
```

## The program without hardware acceleration

To build a version of the program without hardware acceleration, checkout the
branch `no_hw_accel`, copy `targets.json` to `mbed-os/targets`,
and compile as usual:

```sh
$ git checkout no_hw_accel
$ cp targets.json mbed-os/targets
$ mbed compile -t GCC_ARM -m K64F -f
```

## More information

1. See the files in the `docs` directory
1. The gathering of timing statistics is extremely primitive and needs
   much more development.

