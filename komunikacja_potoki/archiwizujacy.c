//Kod archiwizujacego w przypadku komunikacji za pomoca potoku
#include <stdio.h>

int main() {
  char otrzymane_dane[5+1]; 

  while(1){
 	scanf ("%4s",otrzymane_dane); 
	// Otrzymane dane ten program archiwizuje poprzez prinft
  	printf("%s", otrzymane_dane);
  }
  return 0;
}
 
