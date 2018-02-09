#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <ctype.h>
void collatz(int num, void *ptr);
int main()
{
	const int SIZE = 4096;
	const char *name = "Collatz";
	int shm_fd;
	void *ptr;
	pid_t pid;
	int num[1000];
	printf("Welcome\n");
	printf("Enter a number: ");
	int Integer;
	scanf("%d",&Integer);
	if(Integer < 0){
		printf("Invalid\n");
		exit(0);
	}
	pid = fork();	
	if(pid == 0){
		shm_fd = shm_open(name,O_CREAT|O_RDWR,0666);
		ftruncate(shm_fd,SIZE);
		ptr = mmap(0,SIZE,PROT_WRITE,MAP_SHARED,shm_fd,0);
		int i = 0;
		while(Integer!=1){
			printf("Child Read: %s\n ",ptr);
			sprintf(ptr,"%d",Integer);
			printf("Child wrote: %s\n", ptr);
			ptr+= sizeof(Integer);
			if(Integer%2==0){
				Integer/=2;
			}else{
				Integer = 3*Integer + 1;
			}
			if(Integer == 1){
				printf("child wrote: %s\n",Integer);
				sprintf(ptr,"%d",Integer);
				ptr+=sizeof(Integer);
			
			}
			
		}
		shm_unlink(name);	
	}else if(pid > 0){
		wait(NULL);
		shm_fd = shm_open(name,O_RDONLY,0666);
		ptr = mmap(0,SIZE,PROT_READ,MAP_SHARED,shm_fd,0);
		int i = 20;
		while(i != 0){
			printf("Parent read: %s \n",(char *)ptr);
			ptr += sizeof(ptr)/2;
			i--;
		}
	}

	shm_unlink(name);	
	return 0;
}

void collatz(int num, void *ptr)
{
	while(num!=1){
		sprintf(ptr,"%s, ",num);
		ptr +=(2 + sizeof(num));
		if(num%2==0){
			num/=2;
		}else{
			num = 3*num + 1;
		}
	}
	sprintf(ptr,"1");
	ptr+= 1;	
}
