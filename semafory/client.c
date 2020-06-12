#include <stdio.h>
#include <stdint.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "../utils.h"

// semafor --
void sem_down(int semid, int semnum)
{
    struct sembuf buf;
    buf.sem_num = semnum;
    buf.sem_op = -1;
    buf.sem_flg = 0;
    if (semop(semid, &buf, 1) == -1)
    {
        printf("SEM DOWN ERROR");
        exit(-1);
    }
}

// semafor ++
void sem_up(int semid, int semnum)
{
    struct sembuf buf;
    buf.sem_num = semnum;
    buf.sem_op = 1;
    buf.sem_flg = 0;
    if (semop(semid, &buf, 1) == -1)
    {
        printf("SEM UP ERROR");
        exit(-1);
    }
}

#define EMPTYID 1
#define MUTEXID 0
#define FULLID 2

int main(int argc,char * argv)
{
	Komunikat * kom;
	int message_Id;
	Komunikat dane[5000];
	//char  danePrzetw[5000][4] ;
	int semId;
struct timeval tv;
	//pamiec
	message_Id = shmget(2138 , sizeof(Komunikat), 0666);
	kom = (Komunikat*)shmat(message_Id,NULL,0);
	//semafor
	semId = semget(2138, 3, 0600);
	char result[] = "aaaa";
	int i =0;

	while (1)
	{
		printf("%d\n",i);
		//sleep(1);
		sem_down(semId,FULLID);
		sem_down(semId,MUTEXID);

		//tu pobueranie
		
   	
			gettimeofday(&tv, NULL);
			kom->czasRozpPrzetw = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
			
			decryptMessage(kom->dane, 4, result);
			gettimeofday(&tv, NULL);
			kom->czasZakPrzetw = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
			//fflush(stdout);//pobrano -> %s ,result
			//printf("dlTransmisji: %ld,dlougoscPrzetw: %ld    ",kom->czasRozpPrzetw -kom->czasDostarczenia ,kom->czasZakPrzetw - kom->czasRozpPrzetw);
			// wysylanie do archiwizatora


			dane[i]	= *kom;
			//strcpy(danePrzetw[i], result);
			i++;
		sem_up(semId,MUTEXID);
		sem_up(semId,EMPTYID);
		
		if(i==5000) break;
	}

	//do pliku
	   FILE *fp; /* używamy metody wysokopoziomowej - musimy mieć zatem identyfikator pliku, uwaga na gwiazdkę! */
   	char tekst[] = "Hello world";
   	if ((fp=fopen("test.txt", "w"))==NULL)
	 {
     		printf ("Nie mogę otworzyć pliku test.txt do zapisu!\n");
     		exit(1);
     	}

	for( i=0;i<5000;i++)
	{
		fprintf (fp, "%ld;%ld; \n", dane[i].czasRozpPrzetw - dane[i].czasDostarczenia, dane[i].czasZakPrzetw - dane[i].czasRozpPrzetw);
	}
   	 /* zapisz nasz łańcuch w pliku */
   	fclose (fp); /* zamknij plik */
printf("ukonczono");
	


return 0;

}
