#include <pthread.h>
#include <stdio.h>

#include <types.h>

int values = 0;
void *runner(void *param);

int main(int argc,char *argv[]){
	pid_t pid;
	pthread_t tid;
	pthread_attr_t attr;

	pid = fork();
	if(pid == 0){
		pthread_attr_init(&attr);
		pthread_create(&tid,&attr,runner,NULL);
	}
}
