#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "../include/encryptionDecryption.h"
#include "../include/fileM.h"
#include "../include/types.h"

void printEntry(FileEntry entry);
void readWriteTest();

int main(int argc, char **argv) {
  /* readWriteTest(); */

  /* FILE *infile = fopen("test.txt", "r"); */
  /* FILE *outfile = fopen("test2.txt", "w+"); */

  /* uint32_t *keys = pbkdf("TasosFr"); */
  /* encrypt_cbc(infile, outfile, keys); */
  /* fclose(infile); */
  /* fclose(outfile); */

  char filename[50];
  uint8_t new = 0;
  char secretkey[100];
  uint8_t newgroup;

  if(argc > 1) {
    for(int i = 1; i<argc; i++) {
      if(argv[i][0] == '-') {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
          printf("help\n");

        } else if (!strcmp(argv[i], "-f")) {
	  strcpy(filename, argv[i+1]);

        } else if (!strcmp(argv[i], "--new")) {
	  new = 1;

        } else if (!strcmp(argv[i], "--secretkey")) {
	  strcpy(secretkey, argv[i+1]);

        } else if (!strcmp(argv[i], "--changegroup")) {
	  FILE *infile;
	  FILE *outfile;
	  infile = fopen(filename, "r");
	  outfile = fopen("temp.txt", "w+");
	  uint32_t *keys = pbkdf(secretkey);
	  decrypt_cbc(infile, outfile, keys);
	  fclose(infile);
	  fclose(outfile);
	  change_group("temp.txt", argv[i+1], argv[i+2], 0);


        } else if (!strcmp(argv[i], "--deletegroup")) {
	  FILE *infile;
	  FILE *outfile;
	  infile = fopen(filename, "r");
	  outfile = fopen("temp.txt", "w+");

	  uint32_t *keys = pbkdf(secretkey);
	  decrypt_cbc(infile, outfile, keys);
	  fclose(infile);
	  fclose(outfile);
	  change_group("temp.txt", argv[i+1], argv[i+2], 1);

        } else if (!strcmp(argv[i], "--addpassword")) {
          printf("addpassword\n");

        } else if (!strcmp(argv[i], "--changepassword")) {
          printf("changepassword\n");

        } else if (!strcmp(argv[i], "--deletepassword")) {
          printf("deletepassword\n");

        } else if (!strcmp(argv[i], "--showentry")) {
          printf("showentry\n");

        } else if (!strcmp(argv[i], "--showgroups")) {
          printf("showgroups\n");
        }
      }
    }
  }
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
  /* show_entry_by_group("test.txt", "bank", arr, len); */
  for(int i = 0; i<*len; i++) {
    printEntry(arr[i]);
  }
  /* free(arr); */
  /* free(len); */
}
