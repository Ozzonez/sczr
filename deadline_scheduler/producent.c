#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <mqueue.h>
#include "../utils.h"
#include "common.h"


int main(int argc, char **argv)
{
    	int ret;
        int flags = 0;

// tworzy 10ms rezerwacje na okres 2000ms (2s)
	struct sched_attr attr = {
    		.size = sizeof (attr),			
  		.sched_policy = SCHED_DEADLINE,			
    		.sched_runtime = 10 * 1000 * 1000,	// czas procesora jaki ma proces w czasie period
    		.sched_period = 2 * 1000 * 1000 * 1000,	// okres na runtime
    		.sched_deadline = 11 * 1000 * 1000	// przed tym czasem w period task musi byc ukonczony
};
       memset(&attr, 0, sizeof(attr)); 
       attr.size = sizeof(attr);

	ret = sched_setattr(0, &attr, flags);
        if (ret < 0) {
            perror("sched_setattr failed to set the priorities");
            exit(-1);
        }

    /* open the mail queue */
    mqd_t mq;
    mq = mq_open(QUEUE_NAME, O_WRONLY);
    CHECK((mqd_t)-1 != mq);


    printf("Send to server (enter \"exit\" to stop it):\n");

	Komunikat kom;
	kom.dane = 2077;
	struct timeval tv;


    while(1) {
        kom.dane = generateMessage(4);
	gettimeofday(&tv, NULL);
	kom.czasDostarczenia = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;

        /* send the message */
        CHECK(0 <= mq_send(mq, (const char *) &kom, sizeof(Komunikat), 0));
    }

    /* cleanup */
    CHECK((mqd_t)-1 != mq_close(mq));

    return 0;
}
