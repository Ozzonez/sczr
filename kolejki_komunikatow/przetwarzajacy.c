#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <mqueue.h>

#define QUEUE_NAME  "/prod_q"
#define MAX_SIZE    10

int main(int argc, char **argv)
{
    char odebrane_dane[MAX_SIZE + 1];	//+1 ze wzgledu na znak konca stringa
    char przetworzone_dane[MAX_SIZE + 1];

    mqd_t mq;
    struct mq_attr attr;

    /* initialize the queue attributes */
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    /* create the message queue */
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);

    ssize_t bytes_read;
    while(1) {
        /* receive the message */
        bytes_read = mq_receive(mq, odebrane_dane, MAX_SIZE, NULL);

        odebrane_dane[bytes_read] = '\0';

		/* Dane zostaly odebrane, mozna je przetwarzac */
        printf("Received: %s", odebrane_dane);

		// Przetwarzanie

		// Wysylanie przetworzonych danych do archiwizujacego
    }

    /* cleanup */
    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return 0;
}
