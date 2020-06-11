#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>

#define QUEUE_NAME  "/prod_q"
#define MAX_SIZE    10

typedef struct Komunikat
{
  int time;
  char dane[MAX_SIZE];
} Komunikat;


int main(int argc, char **argv)
{
	Komunikat kom;

    /* open the mail queue */
	mqd_t mq;
        mq = mq_open(QUEUE_NAME, O_WRONLY);


    while(1) {
		//te dwie linijki symuluja produkowanie danych
		//trzeba bedzie je podmienic na funckje produkujaca
        memset(kom.dane, 0, MAX_SIZE);
        fgets(kom.dane, MAX_SIZE, stdin);

		kom.time = 7;


        /* send the message */
		mq_send(mq, (const char *) &kom, sizeof(kom), 0);
    }

    /* cleanup */
	mq_close(mq);

    return 0;
}
