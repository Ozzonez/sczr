#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include "../utils.h"



int main()
{
	
	Komunikat * message;
	int message_Id;
	int semId;
	char exit;

	message_Id = shmget(2138 , sizeof(Komunikat), IPC_CREAT|0666);
	message = (Komunikat*)shmat(message_Id,NULL,0);
	//semafory
	semId = semget(2138, 3, IPC_CREAT|IPC_EXCL|0600);
    semctl(semId, 0, SETVAL, (int)1); //mutex 
	semctl(semId, 1, SETVAL, (int)0); //empty czytanie z pustej
	semctl(semId, 2, SETVAL, (int)1); //pisanie do pelnej full 

	 printf("\nExit program? [y] ");
    do{
        scanf("%c",&exit);
    }while(exit != 'y');


	//czyszczenie
    
        shmctl(message_Id,IPC_RMID,NULL);
        semctl(semId, 0, IPC_RMID);
        semctl(semId, 1, IPC_RMID);
		semctl(semId, 2, IPC_RMID);
    


 
	

return 0;

}
