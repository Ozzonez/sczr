#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
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

    /* Inicjalizowanie parametrow kolejki */
    mqd_t mq;
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;
    /* create the message queue */
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);

    ssize_t bytes_read;
    while(1) {
        /* receive the message */
        bytes_read = mq_receive(mq, (char *) &kom, sizeof(kom), NULL);

        //kom.dane[bytes_read] = '\0';

		/* Dane zostaly odebrane, mozna je przetwarzac */
        printf("   Time: %d", kom.time);
        printf("Received: %s", kom.dane);


		// Przetwarzanie

		// Wysylanie przetworzonych danych do archiwizujacego
    }

    /* cleanup */
    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return 0;
}
