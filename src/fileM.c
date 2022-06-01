#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../include/fileM.h"
#include "../include/types.h"

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
  fprintf(fptr, "%s\t%s\t%ld\t%s\t%s\n", entry.group, entry.name, t, entry.username, entry.password);

  fclose(fptr);
  return 0;
}

FileEntry *show_entry_by_name(char filename[], char p_name[]) {
  FileEntry *entry = NULL;
  entry = malloc(sizeof(FileEntry));
  FILE *fptr = NULL;
  fptr = fopen(filename, "r");
  if(fptr == NULL) {
    fprintf(stderr, "Error file %s does not exist.\nCreate a file first.\n", filename);
  }
  char chunk[127];
  while(fgets(chunk, sizeof(chunk), fptr) != NULL) {
    printf("%s", chunk);
    char *saveptr;
    char *group = strtok_r(chunk, "\t", &saveptr);
    char *name = strtok_r(NULL, "\t", &saveptr);
    int date = atoi(strtok_r(NULL, "\t", &saveptr));
    char *username = strtok_r(NULL, "\t", &saveptr);
    char *password = strtok_r(NULL, "\t", &saveptr);
    password[strcspn(password, "\n")] = 0;

    if(!(strcmp(name, p_name))) {
      entry->group = group;
      entry->name = name;
      entry->username = username;
      entry->password = password;
      entry->date = date;

      printf("%s\n", entry->name);
      printf("%s\n", entry->group);
      printf("%s\n", entry->username);
      printf("%s\n", entry->password);
      printf("%d\n", entry->date);

      printf("ok\n");
      break;
    }
    free(saveptr);
  }
  fclose(fptr);
  printf("%s", entry->name);
  printf("%s", entry->group);
  printf("%s", entry->username);
  printf("%s", entry->password);
  printf("%d", entry->date);
  printf("slkdfj\n");
  return entry;
}
