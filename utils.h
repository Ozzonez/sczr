//
// Created by Michal on 11.06.2020.
//

#ifndef SCZR_UTILS_H
#define SCZR_UTILS_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
//#include <math.h>

char* hashMessage(char*);


typedef struct{
    char* message;
    //int time; - 3 timery
}message;

int poww(int,int);
void generateMessage(int length,char * message)
{
	
    srand(time(NULL));
    //char message[length];
   
    for( int i = 0; i < length; i++ )
    {
        message[i] = 'a' + rand() % 26;   
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
