#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int main(int argc,char *arr[])
{
	if(argc!=3){
		printf(2,"Incorrect number of arguments\n");
		exit();
	}
	int errhan = atoi(arr[1]);
	if(arr[1][0] == '-' || errhan > 100){
		printf(2,"Priority should be in range [0,100]\n");
		exit();
	}
	int hand = setpriority(atoi(arr[1]),atoi(arr[2]));
	if(hand==-1)printf(2,"PID %d doesnot exist\n",atoi(arr[2]));
	exit();
}