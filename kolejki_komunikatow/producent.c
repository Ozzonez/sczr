#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>

#include "common.h"


int main(int argc, char **argv)
{
    /* open the mail queue */
    mqd_t mq;
    mq = mq_open(QUEUE_NAME, O_WRONLY);
    CHECK((mqd_t)-1 != mq);


    printf("Send to server (enter \"exit\" to stop it):\n");

	Komunikat kom;

    do {
        printf("> ");
        fflush(stdout);

        memset(kom.dane, 0, MAX_SIZE);
        fgets(kom.dane, MAX_SIZE, stdin);
		kom.time = 7;

        /* send the message */
        CHECK(0 <= mq_send(mq, (const char *) &kom, sizeof(Komunikat), 0));

    } while (strncmp(kom.dane, MSG_STOP, strlen(MSG_STOP)));

    /* cleanup */
    CHECK((mqd_t)-1 != mq_close(mq));

    return 0;
}
