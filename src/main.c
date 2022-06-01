#include <stdio.h>

#include "../include/fileM.h"
#include "../include/types.h"

int main(int argc, char **argv) {
  FileEntry test = {"bank", "revolut", "date", "1322"};
  write_entry("test.txt", test);

  FileEntry *test2;
  test2 = show_entry_by_name("test.txt", "revolut");
  printf("%s", test2->username);
  printf("%s", test2->name);
  printf("%s", test2->group);
  printf("%s", test2->username);
  printf("%s", test2->password);
  printf("%d", test2->date);
  return 0;
}
