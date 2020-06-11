//Kod producenta w przypadku komunikacji za pomoca potoku
#include <stdio.h>
#include <string.h>

int main() {
  char produkowane_dane[5+1]; 

  while(1){
	//str = generuj_dane();	//zakladam, ze generuj_dane bedzie zwracalo stringa co chwile innego
	strcpy(produkowane_dane, "hejka");
  	printf("%s", produkowane_dane);
  }
  return 0;
}
