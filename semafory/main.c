#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
	
	system("gnome-terminal -e \"./run_producer.sh\"");
	usleep(500);

	system("gnome-terminal -e \"./run_client.sh\"");

return 0;

}
