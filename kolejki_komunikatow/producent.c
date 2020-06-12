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
