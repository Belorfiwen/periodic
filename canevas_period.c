
/* déclaration de variables globales servant de drapeaux */
int usr1_receive = 0;
int usr2_receive = 0;
...

/* handler du signal SIGUSR1 */
void handSIGUSR1(int sig) {
  usr1_receive = 1;
}

/* handler du signal SIGUSR2 */
void handSIGUSR2(int sig) {
  usr2_receive = 1;
}

...

int main (int argc, char *argv[]){

  /* initialisations diverses */
  
  /* installation des handlers */
  
  while(1){
    // attente de réception d'un signal
    ...
    if (usr1_receive){
      ...
    }
    if (usr2_receive){
      ...
    }
    ...
  }
  
  ...
}	
