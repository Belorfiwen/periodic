#ifndef MESSAGE_H
#define MESSAGE_H

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>







//Envoie la taille de la chaine de caractères str dans le descripteur de fichier puis la chaine de caractères
int send_string(int fd, char *str);

/**Recoit la taille de la chaine de caractères str depuis le descripteur de fichier puis la chaine de caractères
 * Renvoie la chaine de caractères.
 */
char *recv_string(int fd);

//Envoie la taille du tableau de chaine de caractères dans le descripteur de fichier puis les chaines de caractères du tableau
int send_argv(int fd, char *argv[]);

/**Recoit la taille du tableau de chaine de caractères depuis le descripteur de fichier puis le tableau
 * Renvoie le tableau de chaines de caractères.
 */
char **recv_argv(int fd);


int retpid();

void envoiSignal1();

void envoiSignal2();
#endif
