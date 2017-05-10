#define _POSIX_C_SOURCE 200809L

#include "message.h"
#include <sys/wait.h>

int main(int argc, char *argv[], char **envp){


	//Ex6-1
	pid_t pid1=fork();

	if(pid1==-1){
		fprintf(stderr,"Duplication de processus impossible\n");
		perror("fork");
		exit(1);
	}
	pid_t pid2;
	if(pid1==0){
		int set=setsid();
		if(set==-1){
			fprintf(stderr,"Mise en leader de session impossible\n");
			perror("setsid");
			exit(1);
		}

		pid2=fork();
		if(pid2==-1){
			fprintf(stderr,"Duplication de processus impossible\n");
			perror("fork");
			exit(1);
		}
		
		//EX6-2
		if(pid2==0){
			int chd= chdir("/");
			if(chd==-1){
				fprintf(stderr,"Changement du répertoire courant impossible\n");
				perror("chdir");
				exit(1);
			}

			umask(0000);

			int fin=close(2);
			if(fin){
				fprintf(stderr,"Fermeture du descripteur impossible\n");
				perror("close");
				exit(1);
			}

			fin=close(1);
			if(fin){
				fprintf(stderr,"Fermeture du descripteur impossible\n");
				perror("close");
				exit(1);
			}

			fin=close(0);
			if(fin){
				fprintf(stderr,"Fermeture du descripteur impossible\n");
				perror("close");
				exit(1);
			}
			
			char **tmp=malloc(sizeof(char**));
			execve("./period",tmp,envp);
			perror("execve");	

		}
		exit(0);
		
			
	}
	int status;
	int wt=wait(&status);
	if(wt==-1){
		fprintf(stderr,"Attente de terminaison du processus fils impossible\n");
		perror("wait");
		exit(1);
	}




	return 0;
}
