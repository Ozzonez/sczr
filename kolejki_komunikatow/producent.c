#include <sys/time.h>
#include "../utils.h"
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

	struct timeval tv;
	char  result[]="aaaaa";

	Komunikat kom;


    while(1) {
        ssize_t bytes_read;

        /* receive the message */
        bytes_read = mq_receive(mq, (char *) &kom, sizeof(Komunikat), NULL);
        CHECK(bytes_read >= 0);
        printf("Received: %d\n", kom.dane);

	//Obliczanie czasu przesylania 
	gettimeofday(&tv, NULL);
	kom.czasDostarczenia = ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000) - kom.czasDostarczenia;
	printf(" time: %ld\n", kom.czasDostarczenia);

	//Przetwarzanie danych
	decryptMessage(kom.dane, 4, result);


	printf("%s\n", result);
    }

    /* cleanup */
    CHECK((mqd_t)-1 != mq_close(mq));
    CHECK((mqd_t)-1 != mq_unlink(QUEUE_NAME));

    return 0;
}
