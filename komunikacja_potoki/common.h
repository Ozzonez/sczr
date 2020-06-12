#ifndef COMMON_H_
#define COMMON_H_

#define QUEUE_NAME  "/test"
#define MAX_SIZE    1024
#define MSG_STOP    "exit"

#define CHECK(x) \
    do { \
        if (!(x)) { \
            fprintf(stderr, "%s:%d: ", __func__, __LINE__); \
            perror(#x); \
            exit(-1); \
        } \
    } while (0) \

typedef struct Komunikat
{
  long czasDostarczenia;
  char dane[MAX_SIZE];
} Komunikat;

#endif /* #ifndef COMMON_H_ */
