#ifndef ENCRYPTION_DECRYPTION_H
#define ENCRYPTION_DECRYPTION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


uint32_t *pbkdf(char *pb); // Function that takes a user password and derives an array of keys, to be used for the encryption and decryption of a file

// Functions that encrypt and decrypt a file using cbc mode of operation algorithm and a feistel cipher
int encrypt_cbc(FILE *inF, FILE *outF, uint32_t *keys);
int decrypt_cbc(FILE *inF, FILE *outF, uint32_t *keys);

uint32_t f(uint32_t block, uint32_t key);
uint64_t encrypt(uint32_t left, uint32_t right, uint8_t rounds, uint32_t *keys);
uint64_t decrypt(uint32_t left, uint32_t right, uint8_t rounds, uint32_t *keys);

uint64_t strtohex(char *string);
char *pbextend(char *pb);
uint32_t kdf(uint16_t pb, uint16_t ctx);

#endif // ENCRTYPTION_DECRYPTION_H
