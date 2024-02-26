#include <stdio.h>

// Constants for block sizes
const unsigned char const64 = 0x1b;
const unsigned char const128 = 0x87;

// Function to perform left shift on a byte
unsigned char leftShift(unsigned char value) {
    return (value << 1) | (value >> 7); // shift left by 1, handle overflow
}

// Function to generate subkeys
void generateSubkeys(unsigned char *key, unsigned char *subkey1, unsigned char *subkey2, int blockSize) {
    // Generate subkey 1
    for (int i = 0; i < blockSize / 8; i++) {
        subkey1[i] = key[i];
        if ((key[0] & 0x80) == 0x80) {
            subkey1[i] = leftShift(subkey1[i]);
            subkey1[i] ^= (blockSize == 64) ? const64 : const128;
        } else {
            subkey1[i] = leftShift(subkey1[i]);
        }
    }

    // Generate subkey 2
    for (int i = 0; i < blockSize / 8; i++) {
        subkey2[i] = subkey1[i];
        if ((subkey1[0] & 0x80) == 0x80) {
            subkey2[i] = leftShift(subkey2[i]);
            subkey2[i] ^= (blockSize == 64) ? const64 : const128;
        } else {
            subkey2[i] = leftShift(subkey2[i]);
        }
    }
}

int main() {
    // Example key
    unsigned char key64[8] = {0}; // 64-bit key, initialized with 0s
    unsigned char key128[16] = {0}; // 128-bit key, initialized with 0s

    // Subkeys
    unsigned char subkey1_64[8];
    unsigned char subkey2_64[8];
    unsigned char subkey1_128[16];
    unsigned char subkey2_128[16];

    // Generate subkeys
    generateSubkeys(key64, subkey1_64, subkey2_64, 64);
    generateSubkeys(key128, subkey1_128, subkey2_128, 128);

    // Print subkeys
    printf("Subkey 1 (64-bit):\n");
    for (int i = 0; i < 8; i++) {
        printf("%02x ", subkey1_64[i]);
    }
    printf("\n");

    printf("Subkey 2 (64-bit):\n");
    for (int i = 0; i < 8; i++) {
        printf("%02x ", subkey2_64[i]);
    }
    printf("\n");

    printf("Subkey 1 (128-bit):\n");
    for (int i = 0; i < 16; i++) {
        printf("%02x ", subkey1_128[i]);
    }
    printf("\n");

    printf("Subkey 2 (128-bit):\n");
    for (int i = 0; i < 16; i++) {
        printf("%02x ", subkey2_128[i]);
    }
    printf("\n");

    return 0;
}
