#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
void collatz(int num);
int main(int argc, char argv[])
{
	pid_t pid;
	printf("Welcome\n");
	printf("Enter a number: ");
	int Integer;
	scanf("%d", &Integer);
	if(Integer <= 0)
	{
		printf("Invalid Integer. Positive Integers Only.\n");
		exit(0);
	}
	pid = fork();
	if(pid==0)
	{
		printf("Number = %d\n",Integer);
		printf("CHILD: ");
		collatz(Integer);
	}
	else if(pid > 0){
		wait(NULL);
	}
	return 0;
}

void collatz(int num)
{
	while(num != 1){
		printf("%d, ",num);
		if(num%2 == 0)
		{
			num /= 2;	
		}else{
			num = 3*num + 1;
		}
	}
	printf("1\n");
}
