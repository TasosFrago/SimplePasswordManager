#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "../include/fileM.h"
#include "../include/types.h"

void printEntry(FileEntry entry);
void readWriteTest();

int main(int argc, char **argv) {
  /* readWriteTest(); */
  test();

  return 0;
}

void printEntry(FileEntry entry) {
  printf("Group = %s\n", entry.group);
  printf("Name = %s\n", entry.name);
  printf("Username = %s\n", entry.username);
  printf("Password = %s\n", entry.password);
  printf("UnixTime = %ld\n", entry.unixTime);
  printf("Date = %s\n", entry.date);
  printf("\n");
}

void readWriteTest() {
  FileEntry test = {"bank", "revolut", "tasos", "1322"};
  FileEntry test1 = {"bank", "pireus", "tasos", "1322"};
  FileEntry test2 = {"bank", "ethniki", "tasos", "1322"};
  FileEntry test3 = {"bank", "attica", "tasos", "1322"};
  FileEntry test4 = {"bank", "alpha bank", "tasos", "1322"};
  write_entry("test.txt", test);
  write_entry("test.txt", test1);
  write_entry("test.txt", test2);
  write_entry("test.txt", test3);
  write_entry("test.txt", test4);
  FileEntry te;

  show_entry_by_name("test.txt", "revolut", &te);
  printEntry(te);
  printf("\n");

  FileEntry *arr;
  arr = calloc(100, sizeof(FileEntry));
  int *len;
  len = malloc(sizeof(int));
  show_entry_by_group("test.txt", "bank", arr, len);
  printf("asfkd\n");
  for(int i = 0; i<*len; i++) {
    printEntry(arr[i]);
  }
  free(arr);
  free(len);
}
