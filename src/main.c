#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "../include/fileM.h"
#include "../include/types.h"

void printEntry(FileEntry entry);

int main(int argc, char **argv) {
  FileEntry test = {"bank", "revolut", "date", "1322"};
  write_entry("test.txt", test);
  FileEntry te;

  /* show_entry_by_name("test.txt", "revolut", &te); */
  /* printEntry(te); */

  FileEntry *arr;
  arr = calloc(100, sizeof(FileEntry));
  int *len;
  show_entry_by_group("test.txt", "bank", arr, len);
  printf("asfkd\n");
  for(int i = 0; i<*len; i++) {
    printEntry(arr[i]);
  }
  free(arr);

  return 0;
}

void printEntry(FileEntry entry) {
  printf("Group = %s\n", entry.group);
  printf("Name = %s\n", entry.name);
  printf("Username = %s\n", entry.username);
  printf("Password = %s\n", entry.password);
  printf("UnixTime = %ld\n", entry.unixTime);
  printf("Date = %s\n", entry.date);
}
