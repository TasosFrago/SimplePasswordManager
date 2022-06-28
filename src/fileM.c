#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

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
  time_t t;
  if(entry.unixTime == 0) {
    t = time(NULL);
  } else {
    t = entry.unixTime;
  }
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

FileEntry *show_entry_by_group(char filename[], char p_group[], int *len) {
  FILE *fptr = NULL;
  fptr = fopen(filename, "r");
  if(fptr == NULL) {
    fprintf(stderr, "Error file %s does not exist.\n", filename);
  }
  char chunk[256];
  char *copy;
  char *cpy;

  FileEntry *array = malloc(sizeof(FileEntry));
  uint8_t isEmpty = 0;
  while(fgets(chunk, sizeof(chunk), fptr)) {
    FileEntry entry;
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
      array[*len].group = group;
      array[*len].name = name;
      array[*len].username = username;
      array[*len].password = password;
      array[*len].unixTime = date;

      struct tm *info;
      char buf[30];
      info = localtime(&date);
      strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S ", info);
      cpy = strdup(buf);

      array[*len].date = cpy;
      (*len)++;

      array = realloc(array, sizeof(FileEntry) * (*len + 1));
    } else {
      isEmpty++;
    }
  }
  return array;
}

int change_group(char filename[], char groupName[], char newGroupName[], uint8_t del) {
  FILE *fptr = NULL;
  FILE *fptr2 = NULL;
  fptr = fopen(filename, "r+");

  char new[] = "new";
  char *newFilename = malloc(sizeof(char)*strlen(filename) + 3);
  newFilename = strdup(new);
  strcat(newFilename, filename);
  printf("%s\n", newFilename);

  fptr2 = fopen(newFilename, "w+");
  if(fptr == NULL) {
    fprintf(stderr, "Error file %s does not exist.\n", filename);
  }
  char chunk[256];
  char *copy;
  char *cpy;

  uint8_t isEmpty = 0;
  while(fgets(chunk, sizeof(chunk), fptr)) {
    FileEntry entry;
    printf("%s", chunk);
    copy = strdup(chunk);

    char *saveptr;
    char *group = strtok_r(copy, "\t", &saveptr);
    char *name = strtok_r(NULL, "\t", &saveptr);
    long int date = atoi(strtok_r(NULL, "\t", &saveptr));
    char *username = strtok_r(NULL, "\t", &saveptr);
    char *password = strtok_r(NULL, "\t", &saveptr);
    password[strcspn(password, "\n")] = 0;

    entry.group = group;
    entry.name = name;
    entry.unixTime = date;
    entry.username = username;
    entry.password = password;
    if (!strcmp(group, groupName)) {
      if(del == 0) {
        entry.group = newGroupName;
        write_entry(newFilename, entry);
      }
    } else {
      write_entry(newFilename, entry);
      isEmpty++;
    }
  }
  fclose(fptr);
  fclose(fptr2);
  remove(filename);
  rename(newFilename, filename);
  return 0;
}
