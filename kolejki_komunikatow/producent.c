#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>

#define QUEUE_NAME  "/prod_q"
#define MAX_SIZE    10


int main(int argc, char **argv)
{
    mqd_t mq;
    char produkowane_dane[MAX_SIZE];

    /* open the mail queue */
    mq = mq_open(QUEUE_NAME, O_WRONLY);


    while(1) {
		//te dwie linijki symuluja produkowanie danych
		//trzeba bedzie je podmienic na funckje produkujaca
        memset(produkowane_dane, 0, MAX_SIZE);
        fgets(produkowane_dane, MAX_SIZE, stdin);

        /* send the message */
		mq_send(mq, produkowane_dane, MAX_SIZE, 0);
    }

    /* cleanup */
	mq_close(mq);

    return 0;
}
