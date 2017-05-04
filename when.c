#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//Ex1

int main (int argc, char* argv[]){

	if(argc<2){
		fprintf(stderr,"Manque d'arguments\n");
		exit(1);
	}

	time_t sec;
	sec=atoi(argv[1]);

	char *date=ctime(&sec);
	if(date==NULL){
		perror("ctime");
		exit(1);
	}

	fprintf(stdout,"%s\n",date);


	return 0;

}
