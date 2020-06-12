//Kod producenta w przypadku komunikacji za pomoca potoku
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "utils.h"
#include "common.h"
#include <unistd.h>

int main() {
  Komunikat kom;
  struct timeval tv;
  strcpy(kom.dane, "aaaa");
  char produkowane_dane[5+1]; 
  while(1){
	usleep(10000);
	generateMessage(4, kom.dane);
	gettimeofday(&tv, NULL);
	kom.czasDostarczenia = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	//str = generuj_dane();	//zakladam, ze generuj_dane bedzie zwracalo stringa co chwile innego
	//strcpy(produkowane_dane, "hejka");
  	printf("%4s, %ld", kom.dane, kom.czasDostarczenia);
  }
  return 0;
}
