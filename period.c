#define _POSIX_C_SOURCE 200809L

#include "message.h"


int main (int argc, char *argv[]){

	//Ex7
	pid_t pid = getpid();
	struct stat buf;
	int exist = stat("/tmp/period.pid",&buf);
	if(exist==-1){

		if(errno != ENOENT){
			//ex7-1
			int des=open("/tmp/period.pid",O_WRONLY|O_CREAT, 0777);
			if(des==-1){
				fprintf(stderr,"Impossible d'ouvrir ou de créer le fichier\n");
				perror("open");
				exit(1);
			}
			
			int ret=write(des, &pid, 7);
			if(ret==-1){
				fprintf(stderr,"Impossible d'écrire dans le fichier\n");
				perror("write");
				exit(1);
			} 

			des=close(des);
			if(des){
				fprintf(stderr,"Impossible de fermer le descripteur\n");
				perror("close");
				exit(1);
			}
						

		}
		else{
			fprintf(stderr,"Impossible de vérifier les données\n");
			exit(1);
		}
	}
	else{
		fprintf(stderr,"Le fichier existe déjà\n");
		exit(1);
	}


	//ex7-2 Redirection de la sortie standard vers /tmp/period.out
	int des=open("/tmp/period.out",O_WRONLY|O_CREAT, 0777);
	if(des==-1){
		fprintf(stderr,"Impossible d'ouvrir ou de créer le fichier\n");
		perror("open");
		exit(1);
	}

	int dupl=dup2(des,1);
	if(dupl==-1){
		fprintf(stderr,"Impossible de dupliquer le descripteur\n");
		perror("dup2");
		exit(1);
	}

	des=close(des);
	if(des){
		fprintf(stderr,"Impossible de fermer le descripteur\n");
		perror("close");
		exit(1);
	}


	// redirection de l'erreur standard vers /tmp/period.err
	des=open("/tmp/period.err",O_WRONLY|O_CREAT, 0777);
	if(des==-1){
		fprintf(stderr,"Impossible d'ouvrir ou de créer le fichier\n");
		perror("open");
		exit(1);
	}

	dupl=dup2(des,2);
	if(dupl==-1){
		fprintf(stderr,"Impossible de dupliquer le descripteur\n");
		perror("dup2");
		exit(1);
	}

	des=close(des);
	if(des){
		fprintf(stderr,"Impossible de fermer le descripteur\n");
		perror("close");
		exit(1);
	}


	//Verifier que le tube nommé existe en créer un sinon
	int fifo;
	exist = stat("/tmp/period.fifo",&buf);
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
	

	//Verifier que le repertoire /tmp/period existe sinon le créer
	int rep;
	
	exist = stat("/tmp/period",&buf);
	if(exist==-1){

		if(errno != ENOENT){
			fprintf(stderr,"Le répertoire n'existe pas\n");
			exit(1);
		}

		rep= mkdir("/tmp/period", 0777);
		if(rep==-1){
			fprintf(stderr,"Impossible de créer un répertoire\n");
			perror("mkdir");
			exit(EXIT_FAILURE);
		}
	}
	else{
		if(!S_ISDIR(buf.st_mode)){
			exist = remove("/tmp/period");
			if(exist==-1){
				fprintf(stderr,"Impossible de supprimer les données\n");
				perror("remove");
				exit(1);
			}
	
			rep= mkdir("/tmp/period", 0777);
			if(rep==-1){
				fprintf(stderr,"Impossible de créer un répertoire\n");
				perror("mkdir");
				exit(EXIT_FAILURE);
			}
		}
	}


		

	return 0;

}
