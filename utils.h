//
// Created by Michal on 11.06.2020.
//

#ifndef SCZR_UTILS_H
#define SCZR_UTILS_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

char* hashMessage(char*);


typedef struct{
    char* message;
    //int time; - 3 timery
}message;


char * generateMessage(int length)
{
	
    srand(time(NULL));
    char message[length];
   
    for( int i = 0; i < length; i++ )
    {
        message[i] = 'a' + rand() % 26;   
    } 
	//printf("%s", message);
   
    return message;
}

char * decryptMessage(char *  message, int length)
{

    char  result[]="aaaaaaaaa";
    int i,j=0;
    for ( i = 0; i < pow(25,length) ; ++i)
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
    return result;
}


#endif //SCZR_UTILS_H
