#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <mqueue.h>

#include "common.h"


int main(int argc, char **argv)
{
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

	Komunikat kom;

    int must_stop = 0;
    do {
        ssize_t bytes_read;

        /* receive the message */
        bytes_read = mq_receive(mq, (char *) &kom, sizeof(Komunikat), NULL);
        CHECK(bytes_read >= 0);


        if (! strncmp(kom.dane, MSG_STOP, strlen(MSG_STOP)))
        {
            must_stop = 1;
        }
        else
        {
            printf("Received: %s\n", kom.dane);
			printf(" time: %d\n", kom.time);
        }
    } while (!must_stop);

    /* cleanup */
    CHECK((mqd_t)-1 != mq_close(mq));
    CHECK((mqd_t)-1 != mq_unlink(QUEUE_NAME));

    return 0;
}
