#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../include/encryptionDecryption.h"

#define BLOCK_SIZE 4
#define ROUNDS 8


uint32_t kdf(uint16_t pb, uint16_t ctx) {
  uint32_t sk = (ctx | 0);

  for(int i = 1; i<ROUNDS+1; i++) {
    sk |= f(pb, (ctx | i));
  }
  
  return f(pb, sk);
}

uint32_t *pbkdf(char *pb) {
  char *extendedPb = pbextend(pb);
  uint64_t hex = strtohex(extendedPb);

  uint16_t pb1 = (hex >> 48) & 0xFFFF;
  uint16_t pb2 = (hex >> 32) & 0xFFFF;
  uint16_t pb3 = (hex >> 16) & 0xFFFF;
  uint16_t pb4 = hex & 0xFFFF;
  uint16_t ctx = 0xFEEC;


  uint32_t key1 = kdf(pb1, ctx);
  uint32_t key2 = kdf(pb2, ctx);
  uint32_t key3 = kdf(pb3, ctx);
  uint32_t key4 = kdf(pb4, ctx);

  uint32_t *keys = malloc(sizeof(uint32_t) * ROUNDS);

  keys[0] = key1 | 1;
  keys[1] = key2 | 1;
  keys[2] = key3 | 1;
  keys[3] = key4 | 1;
  keys[4] = key1 | 2;
  keys[5] = key2 | 2;
  keys[6] = key3 | 2;
  keys[7] = key4 | 2;

  return keys;
}

uint64_t strtohex(char *string) {
  char *nStr = strdup(string);
  char *hexstr = malloc(sizeof(char)*strlen(nStr)*2 +1);

  for(int i = 0, j = 0; i<strlen(nStr); i++, j+=2) {
    sprintf(hexstr+j, "%02X", nStr[i]);
  }
  hexstr[strlen(hexstr)] = '\0';
  uint64_t hex = strtol(hexstr, NULL, 16);
  free(hexstr);
  return hex;
}

char *pbextend(char *pb) {
  char *nPb = strdup(pb);

  // Get the sum of all the ascii values of each character in the password for security purposes
  uint32_t sum = 0;
  for(int i = 0; i<strlen(nPb); i++) {
    sum += (int)nPb[i];
  }
  char sumstr[10];
  sprintf(sumstr, "%d", sum);

  char *cpy = malloc(sizeof(char) * strlen(nPb));
  cpy = strdup(nPb);
  if(strlen(nPb)+strlen(sumstr) < BLOCK_SIZE*2) {
    if(2*strlen(nPb)+strlen(sumstr) < BLOCK_SIZE*2) {
      uint16_t length = (BLOCK_SIZE*2-strlen(sumstr)) / strlen(nPb) + 1;
      cpy = realloc(cpy, sizeof(char)*length*strlen(nPb)+1);
      char *cpy2 = strdup(nPb);
      for(int i = 0; i<length; i++) {
	strcat(cpy, cpy2);
      }
    }
    strncat(nPb, cpy, BLOCK_SIZE*2-strlen(nPb)-strlen(sumstr));
    strncat(nPb, sumstr, strlen(sumstr));
  } else if(strlen(nPb)+strlen(sumstr) >= BLOCK_SIZE*2) {
    nPb[BLOCK_SIZE*2-strlen(sumstr)] = '\0';
    strncat(nPb, sumstr, strlen(sumstr));
  }
  return nPb;
}

uint32_t f(uint32_t block, uint32_t key) {
  return block ^ key;
}

uint64_t encrypt(uint32_t left, uint32_t right, uint8_t rounds, uint32_t *keys) {
  /* uint32_t temp; */
  /* for(int i = 0; i<rounds; i++) { */
  /*   temp = right; */
  /*   right = left ^ f(right, keys[i]); */
  /*   left = temp; */
  /* } */

  uint32_t i, left1, right1;
  for (i = 0; i < rounds; i++) {
    left1 = f(left, keys[i]) ^ right;
    right1 = left;
    if (i == (rounds - 1)) {
      left = right1;
      right = left1;
    } else {
      left = left1;
      right = right1;
    }
  }
  return (uint64_t)left << 16 | right;
}

uint64_t decrypt(uint32_t left, uint32_t right, uint8_t rounds, uint32_t *keys) {
  /* uint32_t temp; */
  /* for(int i = rounds-1; i>=0; i--) { */
  /*   temp = right; */
  /*   right = left ^ f(right, keys[i]); */
  /*   left = temp; */
  /* } */
  uint32_t i, left1, right1;
  for (i = 0; i < rounds; i++) {
    left1 = f(left, keys[rounds - i - 1]) ^ right;
    right1 = left;
    if (i == (rounds - 1)) {
      left = right1;
      right = left1;
    } else {
      left = left1;
      right = right1;
    }
  }
  return (uint64_t)left << 16 | right;
}

int encrypt_cbc(FILE *inF, FILE *outF, uint32_t *keys) {
  uint32_t left, right;
  uint64_t sblock, sblock_prev = 0xFEEDFACE;
  size_t ret;
  while(!feof(inF)) {
    memset(&sblock, 0, sizeof(sblock));
    ret = fread(&sblock, sizeof(char), BLOCK_SIZE, inF);
    sblock ^= sblock_prev;
    left = (sblock>>16) & 0xFFFF; // shifting sblock to the right by 16 bits so we have only 4 hex characters. The & operation with 0xFFFF is for safety;
    right = sblock & 0xFFFF;// the and with 0xffff will zero the first 4 hex numbers of the sblock halfing it and giving us only the right part
    sblock = encrypt(left, right, ROUNDS, keys);
    sblock_prev = sblock;
    if (ret < BLOCK_SIZE) {
      fwrite(&sblock, sizeof(char), ret, outF);
    } else {
      fwrite(&sblock, sizeof(char), BLOCK_SIZE, outF);
    }
  }
  
  return 0;
}

int decrypt_cbc(FILE *inF, FILE *outF, uint32_t *keys) {
  uint32_t left, right;
  uint64_t sblock, sblock_prev = 0xFEEDFACE, saved;
  size_t ret;
  while(!feof(inF)) {
    memset(&sblock, 0, sizeof(sblock));
    ret = fread(&sblock, sizeof(char), BLOCK_SIZE, inF);
    saved = sblock;
    left = (sblock>>16) & 0xFFFF;
    right = sblock & 0xFFFF;
    sblock = decrypt(left, right, ROUNDS, keys);
    sblock ^= sblock_prev;
    sblock_prev = saved;
    if (ret < BLOCK_SIZE) {
      fwrite(&sblock, sizeof(char), ret, outF);
    } else {
      fwrite(&sblock, sizeof(char), BLOCK_SIZE, outF);
    }
  }
  return 0;
}
