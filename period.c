#include "message.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define POSIX C SOURCE 200809L


int main (int argc, char *argv[]){

//Ex3
	if(argc<4){

		fprintf(stderr,"usage : ./periodic start period cmd [args]");
		exit(1);

	}

	time_t tloc;
	time_t sec=time(&tloc);
	if(sec==-1){
		perror("time");
		exit(1);
	}

	char *now="now";
	int arg1=atoi(argv[1]);
	if((arg1<sec)&&(strcmp(argv[1],now)!=0)&&(argv[1][0]!='+')){
		fprintf(stderr,"Le premier argument doit être superieur au nombre de seconde depuis Epoch\n usage : ./periodic start period cmd [args]");
		exit(1);

	}

	int arg2=atoi(argv[2]);
	if(arg2<0){
		fprintf(stderr,"Le deuxieme argument doit être superieur à 0\n usage : ./periodic start period cmd [args]");
		exit(1);
	}
	


	//Ex4-3

	// tester si il existe avec stats comme tp ls
	int fifo= mkfifo("/tmp/period.fifo", 0644);
	if(fifo==-1){
		perror("mkfifo");
		exit(EXIT_FAILURE);
	}

	int fd = open("/tmp/period.fifo", O_WRONLY);
	if(fd==-1){
		perror("mkfifo");
		exit(EXIT_FAILURE);
	}

	if(strcmp(argv[1],now)==0){
		char *tab[argc-1];
		tab[0]=sec;
		for(size_t i=
		
		int res= send_argv(fd, char *argv[]){
	}
	

	return 0;

}
