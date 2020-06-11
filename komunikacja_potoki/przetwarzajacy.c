//Kod przetwarzajacego w przypadku komunikacji za pomoca potoku
#include <stdio.h>
#include <string.h>

int main() {
  char otrzymane_dane[5+1]; 
  char przetworzone_dane[5+1]; 

  while(1){
 	scanf ("%4s",otrzymane_dane); 
	// przetworzone_dane = decrypt(otrzymane_dane);
	
	strcpy(przetworzone_dane, "decry");

  	printf("%s", przetworzone_dane);
  }
  return 0;
}
 
