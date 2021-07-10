#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int main(int argc,char *arr[])
{
	if(argc < 2)printf(2,"Invalid no of arguments");
	else{
		int pid = fork();
		if(pid==0)
		{
			if(exec(arr[1],arr+1)<0)
			{
				printf(2,"Exec failed");
				exit();
			}		
		}
		else {
			int *wtime = (int*)malloc(sizeof(int)),*rtime = (int*)malloc(sizeof(int));
			if(waitx(wtime,rtime) == -1)printf(2,"Error in waitx");
			printf(1,"waittime %d, runtime %d\n",*wtime,*rtime);	
		}
	}
	exit();
}