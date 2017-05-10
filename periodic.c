#define _POSIX_C_SOURCE 200809L

#include "message.h"


int main (int argc, char *argv[]){

//Ex3
	if(argc<4){

		fprintf(stderr,"usage : ./periodic start period cmd [args]\n");
		exit(1);

	}

	time_t tloc;
	time_t sec=time(&tloc);
	if(sec==-1){
		fprintf(stderr,"Impossible d'obtenir le temps réel\n");
		perror("time");
		exit(1);
	}

	char *now="now";
	int arg1=atoi(argv[1]);
	if((arg1<sec)&&(strcmp(argv[1],now)!=0)&&(argv[1][0]!='+')){
		fprintf(stderr,"Le premier argument doit être superieur au nombre de seconde depuis Epoch\n usage : ./periodic start period cmd [args]\n");
		exit(1);

	}

	int arg2=atoi(argv[2]);
	if(arg2<0){
		fprintf(stderr,"Le deuxieme argument doit être superieur à 0\n usage : ./periodic start period cmd [args]\n");
		exit(1);
	}
	

	//Ex4-2
	envoiSignal1();


	//Ex4-3

	struct stat buf;
	int fifo;
	int exist = stat("/tmp/period.fifo",&buf);
	if(exist==-1){

		if(errno != ENOENT){
			fprintf(stderr,"Le tube n'existe pas");
			exit(1);
		}

		fifo= mkfifo("/tmp/period.fifo", 0777);
		if(fifo==-1){
			fprintf(stderr,"Impossible de créer un tube\n");
			perror("mkfifo");
			exit(EXIT_FAILURE);
		}
	}
	else{
		if(!S_ISFIFO(buf.st_mode)){
			exist = remove("/tmp/period.fifo");
			if(exist==-1){
				fprintf(stderr,"Impossible de supprimer les données\n");
				perror("remove");
				exit(1);
			}
	
			fifo= mkfifo("/tmp/period.fifo", 0777);
			if(fifo==-1){
				fprintf(stderr,"Impossible de créer un tube\n");
				perror("mkfifo");
				exit(EXIT_FAILURE);
			}
		}
	}
	

	int fd = open("/tmp/period.fifo", O_WRONLY);
	if(fd==-1){
		fprintf(stderr,"Impossible d'ouvrir le tube\n");
		perror("open");
		exit(EXIT_FAILURE);
	}

	if(strcmp(argv[1],now)==0){
		char *tab[argc];
		sprintf(tab[0],"%ld",sec);
		for(size_t i=2;i<argc;i++){
			tab[i-1]=argv[i];
		}
		tab[argc-1]=NULL;
		int res= send_argv(fd, tab);
		if(res==-1){
			fprintf(stderr,"Impossible d'écrire dans le tube\n");
			exit(1);
		}
	}else{
	
		if(argv[1][0]=='+'){
			char *tab[argc-1];
			int timeTest=atoi(argv[1]);
			sec=sec+timeTest;
			sprintf(tab[0], "%ld",sec);
			for(size_t i=2;i<argc;i++){
				tab[i-1]=argv[i];
			}
			tab[argc-1]=NULL;		

			int res= send_argv(fd, tab);
			if(res==-1){
				fprintf(stderr,"Impossible d'écrire dans le tube\n");
				exit(1);
			}
		}else{

			char *tab[argc-1];
			long timeTest=atoi(argv[1]);
			sprintf(tab[0], "%ld",timeTest);
			for(size_t i=2;i<argc;i++){
				tab[i-1]=argv[i];
			}
			tab[argc-1]=NULL;
		
			int res= send_argv(fd, tab);
			if(res==-1){
				fprintf(stderr,"Impossible d'écrire dans le tube\n");
				exit(1);
			}
		}

	}

	int fin = close(fd);
	if(fin){
		fprintf(stderr,"Impossible de fermer le tube\n");
		perror("close");
		exit(EXIT_FAILURE);
	}


	//Ex5
	fd = open("/tmp/period.fifo", O_RDONLY);
	if(fd==-1){
		fprintf(stderr,"Impossible d'ouvrir le tube\n");
		perror("open");
		exit(EXIT_FAILURE);
	}
			
	envoiSignal2();

	char **recv=recv_argv(fd);
	if(recv==NULL){
		fprintf(stderr,"Impossible de lire dans le tube\n");
		exit(1);
	}


	size_t i=0;
	while(recv[i]!=NULL){
		fprintf(stdout, "%s\n",recv[i]);
		i++;
	}

	fin = close(fd);
	if(fin){
		fprintf(stderr,"Impossible de fermer le tube\n");
		perror("close");
		exit(EXIT_FAILURE);
	}

	return 0;

}
