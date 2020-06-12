#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <unistd.h>
#include "../utils.h"

#define EMPTYID 1
#define MUTEXID 0
#define FULLID 2


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

int main()
{
	Komunikat * kom;
	
	int message_Id;
	int semId;
	char  message[]="aaaa"; 
	struct timeval tv;
	//pamiec
	message_Id = shmget(2137 , sizeof(Komunikat), 0666);
	kom = (Komunikat*)shmat(message_Id,NULL,0);
	//semafor
	semId = semget(2137, 3, 0600);
    int i=0;
    while(1)
    {

       	generateMessage(4,message);
		
	sem_down(semId,EMPTYID);
	sem_down(semId,MUTEXID);

	//tu wysylanie
   	
	gettimeofday(&tv, NULL);
	kom->czasDostarczenia = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	strcpy(kom->dane,message);


	sem_up(semId,MUTEXID);
	sem_up(semId,FULLID);

    }
return 0;
}
