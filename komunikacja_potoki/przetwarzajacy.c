//Kod przetwarzajacego w przypadku komunikacji za pomoca potoku
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "utils.h"
#include "common.h"

int main() {
  struct timeval tv;
  char result[]="aaaa";
  Komunikat kom;

  while(1){
 	scanf ("%4s, %ld", kom.dane, &kom.czasDostarczenia);
	gettimeofday(&tv, NULL);
	kom.czasDostarczenia = ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000) - kom.czasDostarczenia;
	decryptMessage(kom.dane, 4, result);

  	printf("Received: %s\n", kom.dane);
			printf(" time: %ld\n", kom.czasDostarczenia);
  }
  return 0;
}
