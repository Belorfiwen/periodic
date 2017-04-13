#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*send_string(descripteur,"bonjour");
calculer la longueur de la chaine
envoyer la longueur de la chaine puis la chaine*/


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
	
	nb=read(fd,&tab,sz*sizeof(char));

	if(nb<0){
		perror("read");
		return NULL;
	}
	tab[sz-1]='\0';

	return tab;

}

int main(int argc, char *argv[]){

	int des=open(argv[1],O_RDWR|O_CREAT);
	if(des==-1){
		perror("open");
		exit(1);
	}

	send_string(des,"Bonjour");
	char *test;
	test=recv_string(des);
	printf("%s\n",test);

	int res=close(des);
	if(res){
		perror("close");
		fprintf(stderr, "erreur lors de la fermeture du descripteur");
		exit(1);
	}

	return 0;
}



