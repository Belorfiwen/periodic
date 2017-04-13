
/*send_string(descripteur,"bonjour");
calculer la longueur de la chaine
envoyer la longueur de la chaine puis la chaine*/


int send_string(int fd, char *str);

	size_t sz=strlen(str);

	char buf[BUFSIZE];
	
