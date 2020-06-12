//
// Created by Michal on 11.06.2020.
//

#ifndef SCZR_UTILS_H
#define SCZR_UTILS_H

//#include <math.h>
#include <linux/kernel.h>
#include <linux/unistd.h>
#include <time.h>
#include <linux/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <linux/sched.h>
#include <sys/resource.h>
#include <sys/syscall.h>
#include <unistd.h>

#ifdef __x86_64__
#define __NR_sched_setattr		314
#define __NR_sched_getattr		315
#endif

#ifdef __i386__
#define __NR_sched_setattr		351
#define __NR_sched_getattr		352
#endif

#ifdef __arm__
#define __NR_sched_setattr		380
#define __NR_sched_getattr		381
#endif

#define SF_SIG_RORUN		2
#define SF_SIG_DMISS		4
#define SF_BWRECL_DL		8
#define SF_BWRECL_RT		16
#define SF_BWRECL_OTH		32

#define RLIMIT_DLDLINE		16
#define RLIMIT_DLRTIME		17

char* hashMessage(char*);


typedef struct{
    char* message;
    //int time; - 3 timery
}message;

struct sched_attr {
	__u32 size;
	
	__u32 sched_policy;
	__u64 sched_flags;
	
	/* SCHED_NORMAL, SCHED_BATCH */
	__s32 sched_nice;
	
	/* SCHED_FIFO, SCHED_RR */
	__u32 sched_priority;
	
	/* SCHED_DEADLINE */
	__u64 sched_runtime;
	__u64 sched_deadline;
	__u64 sched_period;
};

int sched_setattr(pid_t pid,
		const struct sched_attr *attr,
		unsigned int flags)
{
	return syscall(__NR_sched_setattr, pid, attr, flags);
}

int sched_getattr(pid_t pid,
		struct sched_attr *attr,
		unsigned int size,
		unsigned int flags)
{
	return syscall(__NR_sched_getattr, pid, attr, size, flags);
}


int poww(int,int);
void generateMessage(int length,char * message)
{
    int r;
    struct timespec ts;
    if (timespec_get(&ts, TIME_UTC) == 0) {
    /* Handle error */
    }
    srandom(ts.tv_nsec ^ ts.tv_sec);
    r = random();
    
    //char message[length];
   
    for( int i = 0; i < length; i++ )
    {
	r = random();
        message[i] = 'a' + r % 26;   
    } 
	//printf("%s", message);
   
    //return message;
}

void decryptMessage(char *  message, int length,char * result)
{

    //char  result[]="aaaaaaaaa";
    int i,j=0;
    for ( i = 0; i < poww(25,length) ; ++i)
    {

        //tu porówn
        if(strcmp(result,message)==0)
        {
            printf("%s\n",result);
            break;
        }
        
        result[0]++;
        if(result[0]=='z'+1)
        {
            j=1;
            while(result[j]=='z')j++;
            result[j]++;
            while(j!=0) result[--j]='a';
        }
    }
    //return result;
}

int poww(int x,int y)
{
	int result=1;
	int i=0;
	for(i=0;i<y;i++)
	{
		result*=x;
	}
	return result;
	
}


#endif //SCZR_UTILS_H
