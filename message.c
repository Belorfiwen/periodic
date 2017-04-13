#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
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

	ret= write(fd,str,sizeof(size_t));
	
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

	char *tab=malloc(sz*sizeof(char));
	
	nb=read(fd,tab,sz*sizeof(char));

	if(nb<0){
		perror("read");
		return NULL;
	}

	return tab;

}

int main(int argc, char *argv[]){

	return 0;
}



