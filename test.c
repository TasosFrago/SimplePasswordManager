#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int numPlaces(int n) {
  if (n < 10) {
    return 1;
  }
  return 1 + numPlaces(n / 10);
}

int main() {
  int s = 0b1000;
  printf("%u\n", s);
  int num, bin, rem, place;
  char *str = "Hellooafdslalsfdiwepo0r";
  printf("%zu", sizeof(*str));
  int *test = (int *)malloc(sizeof(*str));
  int *bins = malloc(sizeof(test));
  printf("%ld\n", strlen(str));

  for(int i = 0; i<strlen(str); i++) {
    if(str[i] == '\0') {
      continue;
    }
    test[i] = (int)str[i];
    num = test[i];

    bin = 0;
    rem = 0;
    place = 1;
    while (num) {
      rem = num % 2;
      num = num / 2;
      bin = bin + (rem * place);
      place = place * 10;
    }
    int nu = numPlaces(bin);
    bins[i] = bin;
    printf("Char = %c, Ascii = %d, Binary = %d\n", str[i], test[i], bins[i]);
    printf("num of ch = %d\n", nu);
  }
  char te[100];
  int oo = itoa(145, te, 2);
  printf("%s\n", te);
  /* num = 1; */
  /* while(num) { */
  /*   rem = num % 2; */
  /*   num = num / 2; */
  /*   bin = bin + (rem * place); */
  /*   place = place * 10; */
  /* } */
  /* printf("bin = %d\n", bin); */
  /* printf("div = %d\n", (101 / 10)); */
  /* printf("mod = %d\n", (101 % 10)); */


  return 0;
}
