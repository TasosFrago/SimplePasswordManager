#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

#include "../include/fileM.h"
#include "../include/types.h"

uint32_t f(uint32_t block, uint32_t key) {
  return block ^ key;
}

uint64_t encrypt(uint32_t left, uint32_t right, uint32_t rounds, uint32_t keys[]) {
  uint32_t i, left1, right1;
  for(i = 0; i < rounds; i++) {
    left1 = f(left, keys[i]) ^ right;
    right1 = left;
    if(i == (rounds-1)) {
      left = right1;
      right = left1;
    } else {
      left = left1;
      right = right1;
    }
  }
  return (uint64_t)left<<32 | right;
}

uint64_t decrypt(uint32_t left, uint32_t right, uint32_t rounds, uint32_t keys[]) {
  uint32_t i, left1, right1;
  for(i = 0; i < rounds; i++) {
    left1 = f(left, keys[rounds-i-1]) ^ right;
    right1 = left;
    if(i == (rounds-1)) {
      left = right1;
      right = left1;
    } else {
      left = left1;
      right = right1;
    }
  }
  return (uint64_t)left<<32 | right;
}

void test() {
  char tes = 't';
  printf("%d\n", tes);
  int te;
  te = (int)tes;
  printf("%d\n", te);
}

// Group Name Date Username Password

int write_entry(char filename[], FileEntry entry) {
  FILE *fptr = NULL;
  fptr = fopen(filename, "r");
  if(fptr == NULL) {
    printf("File does not exist. Creating file %s...\n", filename);
  }
  fptr = fopen(filename, "a");
  if(fptr == NULL) {
    printf("Error opening file\n");
  }
  fptr = fopen(filename, "a");

  // Get current time in Unix timestamp
  time_t t = time(NULL);
  // Add encryption here
  fprintf(fptr, "%s\t%s\t%ld\t%s\t%s\t\n", entry.group, entry.name, t, entry.username, entry.password);

  fclose(fptr);
  return 0;
}

int show_entry_by_name(char filename[], char p_name[], FileEntry *entry) {
  FILE *fptr = NULL;
  fptr = fopen(filename, "r");
  if(fptr == NULL) {
    fprintf(stderr, "Error file %s does not exist.\nCreate a file first.\n", filename);
  }
  char chunk[256];
  char *copy;
  char *cpy;
  unsigned short int isEmpty = 0;
  while(fgets(chunk, sizeof(chunk), fptr)) {
    printf("%s", chunk);
    copy = strdup(chunk);

    char *saveptr;
    char *group = strtok_r(copy, "\t", &saveptr);
    char *name = strtok_r(NULL, "\t", &saveptr);
    long int date = atoi(strtok_r(NULL, "\t", &saveptr));
    char *username = strtok_r(NULL, "\t", &saveptr);
    char *password = strtok_r(NULL, "\t", &saveptr);
    password[strcspn(password, "\n")] = 0;

    if(!strcmp(name, p_name)) {
      entry->name = name;
      entry->group = group;
      entry->username = username;
      entry->password = password;
      entry->unixTime = date;

      struct tm *info;
      char buf[100];
      info = localtime(&entry->unixTime);
      strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", info);
      cpy = strdup(buf);

      entry->date = cpy;
      break;
    } else {
      isEmpty++;
    }
  }
  if(isEmpty) {
    printf("Entry does not exist.\n");
    return -1;
  }
  return 0;
}

int show_entry_by_group(char filename[], char p_group[], FileEntry *arr, int *len) {
  FILE *fptr = NULL;
  fptr = fopen(filename, "r");
  if(fptr == NULL) {
    fprintf(stderr, "Error file %s does not exist.\n", filename);
  }
  FileEntry entry;
  char chunk[256];
  char *copy;
  char *cpy;
  unsigned short int isEmpty = 0;
  unsigned int count = 0;
  *len = 0;
  size_t size = sizeof(FileEntry);
  while(fgets(chunk, sizeof(chunk), fptr)) {
    printf("%s", chunk);
    copy = strdup(chunk);

    char *saveptr;
    char *group = strtok_r(copy, "\t", &saveptr);
    char *name = strtok_r(NULL, "\t", &saveptr);
    long int date = atoi(strtok_r(NULL, "\t", &saveptr));
    char *username = strtok_r(NULL, "\t", &saveptr);
    char *password = strtok_r(NULL, "\t", &saveptr);
    password[strcspn(password, "\n")] = 0;

    if(!strcmp(group, p_group)) {
      arr[count].group = group;
      arr[count].name = name;
      arr[count].username = username;
      arr[count].password = password;
      arr[count].unixTime = date;

      struct tm *info;
      char buf[30];
      info = localtime(&date);
      strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S ", info);
      cpy = strdup(buf);

      arr[count].date = cpy;
      count++;
      (*len)++;
      /* size += sizeof(FileEntry); */
      /* arr = (FileEntry *)realloc(arr, size); */
    }
  }
  return 0;
}
