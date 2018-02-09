#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define BUFFER_SIZE 25
#define READ_END1 0
#define WRITE_END2 1
#define READ_END2 2
#define WRITE_END1 3
int main(void){
	char write_msg[BUFFER_SIZE] = "Greetings";
	char read_msg[BUFFER_SIZE];
	int fd[4];
	int sent,i;
	pid_t pid;
	for(i = 0; i < 2; ++i){
		if(pipe(fd+(i*2)) <0){
			fprintf(stderr,"pipe failed");
			exit(0);
		}
	}
	pid = fork();
	if(pid < 0){
		fprintf(stderr,"Fork failed");
		exit(0);
	}
	if(pid == 0){	
		close(fd[READ_END1]);
		close(fd[WRITE_END1]);

		sent = read(fd[READ_END2],&read_msg,sent);
		if(sent < 0){
			fprintf(stderr,"child: failed pipe read");
			exit(0);
		}else if(sent == 0){
			fprintf(stderr,"Read poor from pipe");
		}else{
			printf("Child read message %s. sending changes to parent\n",read_msg);
			i = 0;
			while(read_msg[i]){
				if(isupper(read_msg[i])){
					read_msg[i] = tolower(read_msg[i]);
					i++;
				}else if(islower(read_msg[i])){
					read_msg[i] = toupper(read_msg[i]);
					i++;
				}else{
					i++;
					continue;
				}
				
			}
			printf("Child sending %s\n", read_msg);
			write(fd[WRITE_END2],&read_msg,BUFFER_SIZE);
		}
		close(fd[READ_END2]);
		close(fd[WRITE_END2]);
		return 0;
	}

	close(fd[READ_END2]);
	close(fd[WRITE_END2]);
	printf("Parent sending msg %s\n",write_msg);
	write(fd[WRITE_END1],write_msg,BUFFER_SIZE);
	sent = read(fd[READ_END1],&write_msg,BUFFER_SIZE);
	if(sent < 0){
		fprintf(stderr,"failed pipe read\n");
		exit(0);
	}else if(sent == 0){
		fprintf(stderr,"weird\n");
	}else{
		printf("parent received msg %s\n",write_msg);
	}
	close(fd[READ_END1]);
	close(fd[WRITE_END1]);
	wait(NULL);
	return 0;
}
