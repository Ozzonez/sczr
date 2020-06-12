#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <mqueue.h>
#include <sys/time.h>
#include "../utils.h"
#include "common.h"


int main(int argc, char **argv)
{

	int ret;
        int flags = 0;

// tworzy 10ms rezerwacje na okres 2000ms (2s)
	struct sched_attr attri = {
    		.size = sizeof (attri),			
  		.sched_policy = SCHED_DEADLINE,						
    		.sched_runtime = 1000 * 1000 * 1000,	// czas procesora jaki ma proces w czasie period
    		.sched_period = 1 * 1000 * 1000 * 1000,	// okres na runtime
    		.sched_deadline = 2 * 1000 * 1000	// przed tym czasem w period task musi byc ukonczony
};
       memset(&attri, 0, sizeof(attri)); 
       attri.size = sizeof(attri);

	ret = sched_setattr(0, &attri, flags);
        if (ret < 0) {
            perror("sched_setattr failed to set the priorities");
            exit(-1);
        }
	// Trzeba usuwac pozostale w systemie kolejki o tej samej nazwie, zeby nie bylo bledow
	if(mq_unlink(QUEUE_NAME) == 0)
		fprintf(stdout, "Message queue %s removed from system.\n", QUEUE_NAME);

    /* initialize the queue attributes */
    mqd_t mq;
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(Komunikat);
    attr.mq_curmsgs = 0;

    /* create the message queue */
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);
    CHECK((mqd_t)-1 != mq);

	struct timeval tv;
	char  result[]="aaaaa";

	Komunikat kom;

	int i = 0;
    while(i < 2000) {
	i++;
        ssize_t bytes_read;

        /* receive the message */
        bytes_read = mq_receive(mq, (char *) &kom, sizeof(Komunikat), NULL);
        CHECK(bytes_read >= 0);
        //printf("Received: %d\n", kom.dane);

	//Obliczanie czasu przesylania 
	gettimeofday(&tv, NULL);
	kom.czasDostarczenia = ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000) - kom.czasDostarczenia;
	printf("%ld\n", kom.czasDostarczenia);

	//Przetwarzanie danych
	decryptMessage(kom.dane, 4, result);


	//printf("%s\n", result);
		
    }

    /* cleanup */
    CHECK((mqd_t)-1 != mq_close(mq));
    CHECK((mqd_t)-1 != mq_unlink(QUEUE_NAME));

    return 0;
}
