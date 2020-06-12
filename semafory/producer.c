#include <stdio.h>

int main()
{
	Message * message;
	int message_Id;
	int semId;
	//pamiec
	message_Id = shmget(2137 , sizeof(Message), 0666);
	message = (Message*)shmat(message_Id,NULL,0);
	//semafor
	semId = semget(2137, 3, 0600);

    while(1)
    {


        
    }
return 0;
}
