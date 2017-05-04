#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//Ex1

int main (int argc, char* argv[]){

	time_t tloc;
	time_t sec=time(&tloc);
	if(sec==-1){
		perror("time");
		exit(1);
	}

	fprintf(stdout,"%ld secondes\n",sec);

	return 0;

}
