#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h> 

void chercher(int argc, char *argv[], char *envp[],int i){
    char* tab[] = {"francais.txt","italiano.txt","english.txt","deutsch.txt"};
	int cpt; 
    char *envl[]= {"LANG=C",NULL};
    argv[0] = "grep"; 
    //argv[argc] = "eng.txt";
    argv[argc] = tab[i];
    printf("\tFichier : %s\n",tab[i]);
    argv[argc+1] = (char *)NULL;  
    if(execvpe(argv[0], argv, envl)== -1) 
    { 
        perror("execvpe "); 
        _exit(EXIT_FAILURE); 
    } 
}

int main(int argc, char *argv[], char *envp[]){
	pid_t pid; 
   	int statut;
    for(int i = 0; i < 4; i++){
	        pid = fork();

            if(pid == -1)
            {
                    perror("fork");
                    exit(1);
            }
            if (pid == 0){
		        	printf("\tFils n°%d, pid %d de pere %d\n",i+1, (int) getpid(), (int) getppid());
		        	chercher(argc,argv,envp,i);
		        	exit(0);
            }
    }
		        
    printf("Pere %d de pere %d\n",(int) getpid(), (int) getppid());
	//On est dans le parent 
    printf("** Enfant créé  %d : - cherche chaine %s\n",pid, argv[1]); 
    for(int cpt = 0; cpt < argc; cpt++) 
    { 
          printf ("arg %i : %s\n", cpt,  argv[cpt]); 
    }
}