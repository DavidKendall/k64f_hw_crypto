## Introduction

A very simple demo of some of the MMCAU API functions using the 
[Freescale library](https://www.nxp.com/products/processors-and-microcontrollers/additional-processors-and-mcus/coldfire-plus-coldfire/crypto-acceleration-unit-cau-and-mmcau-software-library:CAUAP)
and ARM mbed OS-5.

## Building with mbed-cli

1. Import the repository

     ```sh
     $ mbed import https://github.com/davidkendall/k64f_hw_crypto
     ```

1. Connect an FRDM-K64F board and make sure that it is mounted.

1. Start a `minicom` session with parameters `115200 8N1`

1. Compile the program and flash the board

     ```sh
     $ mbed compile -t GCC_ARM -m K64F -f
     ```

1. If necessary, press `reset` to execute the code.

## Output

The program illustrates the use of the following functions:

* `cau_md5_initialize_output`
* `cau_aes_set_key`
* `cau_aes_encrypt`
* `cau_aes_decrypt`

If all is well, you should see some output like the following

```
MMCAU Test
MD5 Init
01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 
AES Set Key
33 32 31 30 37 36 35 34 62 61 39 38 00 65 64 63 c8 51 7c 72 ff 67 49 46 9d 06 70 7e 9d 63 14 1d 6c 0f 87 8a 93 68 ce cc 0e 6e be b2 93 
AES Encrypt
Plaintext : 43 6f 6e 66 69 64 65 6e 74 69 61 6c 20 54 58 00 
Ciphertext: 18 b0 6c c5 eb bf 0e 9e 23 68 27 55 ed fd eb ca 
AES Decrypt
Plaintext : 43 6f 6e 66 69 64 65 6e 74 69 61 6c 20 54 58 00 
```

## More information

See the files in the `docs` directory

