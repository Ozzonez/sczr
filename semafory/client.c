#include <stdio.h>
#include <stdint.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

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
	int * message;
	int message_Id;
	int semId;
	//pamiec
	message_Id = shmget(2137 , sizeof(Message), 0666);
	message = (int*)shmat(message_Id,NULL,0);
	//semafor
	semId = semget(2137, 3, 0600);

	while (1)
	{
		sleep(1);
		sem_down(semId,FULLID);
		sem_down(semId,MUTEXID);

		//tu pobueranie
			printf("pobrano -> %d\n",*message);

		sem_up(semId,MUTEXID);
		sem_up(semId,EMPTYID);
	}
	


return 0;

}
