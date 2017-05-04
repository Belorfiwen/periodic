#include "message.h"
#include <errno.h>
#include <sys/types.h>
#include <signal.h>


#define LONG_MIN ((long) 0x80000000L)
#define LONG_MAX 0x7FFFFFFFL
//Ex2




int send_string(int fd, char *str){

	size_t sz=strlen(str);

	int ret=write(fd,&sz,sizeof(size_t));
	if(ret==-1){
		perror("write");
		return -1;
	}

	ret= write(fd,str,sz*sizeof(char));
	
	if(ret==-1){
		perror("write");
		return -1;
	}

	return 0;
}


char *recv_string(int fd){

	size_t sz=0;

	size_t nb=read(fd,&sz,sizeof(size_t));
	if(nb<0){
		perror("read");
		return NULL;
	}

	char *tab=malloc(sz*sizeof(char)+1);
	
	nb=read(fd,tab,sz*sizeof(char));

	if(nb<0){
		perror("read");
		return NULL;
	}
	tab[sz]='\0';

	return tab;

}

int send_argv(int fd, char *argv[]){

	size_t nb=0;
	while(argv[nb]!=NULL){
		nb++;
	}

	int ret=write(fd, &nb, sizeof(size_t));
	if(ret==-1){
		perror("write");
		return -1;
	} 

	for(int i=0;i<nb;i++){
		send_string(fd,argv[i]);
	}

	return 0;

}


char **recv_argv(int fd){

	size_t i;
	int ret=read(fd, &i, sizeof(size_t));
	if(ret==-1){
		perror("read");
		return NULL;
	} 

	char **tab=malloc(sizeof(char*)*(i+1));
	size_t j;
	for(j=0;j<i;j++){
		tab[j]=recv_string(fd);	
	}
	tab[j]=NULL;

	return tab;

}


int retpid(){

	
	int des=open("/tmp/period.pid",O_RDONLY,0777);
	if(des==-1){
		fprintf(stderr, "erreur lors de l'ouverture du descripteur");
		perror("open");
		return -1;
	} 
	int i;
	int nb_read=read(des, &i, sizeof(int));
	if(nb_read==-1){
		fprintf(stderr, "erreur lors de la lecture du descripteur");
		perror("read");
		return -1;
	} 

	int res=close(des);
	if(res){
		fprintf(stderr, "erreur lors de la fermeture du descripteur");
		perror("close");
		return -1;
	}

	char *tmp;
	long ret=strtol(i,&tmp,10);

	if((tmp==i)||(*tmp != '\0')||(((ret == LONG_MIN)||(ret == LONG_MAX))&&(errno == ERANGE))){

		fprintf(stderr,"Impossible de convertir le pid '%d'\n",i);
		return -1;

	}
	
	return i;
	
}


//Ex4
void envoiSignal1(){

	int rec=retpid();
	
	int ret=kill(rec,SIGUSR1);
	if(ret==-1){
		fprintf(stderr, "erreur lors de l'envoi du signal SIGUSR1");
		perror("kill");
		return;
	} 	

}

void envoiSignal2(){

	int rec=retpid();
	
	int ret=kill(rec,SIGUSR2);
	if(ret==-1){
		fprintf(stderr, "erreur lors de l'envoi du signal SIGUSR1");
		perror("kill");
		return;
	} 	

}


int main(int argc, char *argv[]){

	if(argc!=3){
		printf("nombre d'arguments incorrect\n");
		exit(1);
	}


	int des=open(argv[1],O_WRONLY|O_CREAT,0777);
	if(des==-1){
		perror("open");
		exit(1);
	} 

	send_string(des,"Bonjour");

	int res=close(des);
	if(res){
		perror("close");
		fprintf(stderr, "erreur lors de la fermeture du descripteur");
		exit(1);
	}

	des=open(argv[1],O_RDONLY,0777);
	if(des==-1){
		perror("open");
		exit(1);
	} 

	char *test;
	test=recv_string(des);
	printf("%s\n",test);

	res=close(des);
	if(res){
		perror("close");
		fprintf(stderr, "erreur lors de la fermeture du descripteur");
		exit(1);
	}

	free(test);



	int des2=open(argv[2],O_WRONLY|O_CREAT,0777);
	if(des2==-1){
		perror("open");
		exit(1);
	} 
	char **to_send = malloc(sizeof(char *)*4);
	to_send[0] = "toto";
	to_send[1] = "tata";
	to_send[2] = "titi";
	to_send[3] = NULL;

	send_argv(des2,to_send);

	int res2=close(des2);
	if(res2){
		perror("close");
		fprintf(stderr, "erreur lors de la fermeture du descripteur");
		exit(1);
	}

	des2=open(argv[2],O_RDONLY,0777);
	if(des2==-1){
		perror("open");
		exit(1);
	} 
	char **test2;
	test2=recv_argv(des2);
	

	int i=0;
	while(test2[i]!=NULL){
	
		printf("%s\n",test2[i]);
		i++;
	}

	res2=close(des2);
	if(res2){
		perror("close");
		fprintf(stderr, "erreur lors de la fermeture du descripteur");
		exit(1);
	}

	return 0;
}



