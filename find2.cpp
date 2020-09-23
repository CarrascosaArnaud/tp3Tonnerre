#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h> 

void chercher(int argc, char *argv[], char *envp[]){
	int cpt; 
    //On prépare un environnement très réduit 
     char *envl[]= {"LANG=C",NULL}; 
     printf("\t-- Enfant pid %d\n",(int)getpid()); 
     // On modifie la liste d’arguments reçue : 
     // Le nom du programme chargé doit être le premier argument 
     argv[0] = "grep"; 
     // argv[1] est la chaine a rechercher on conserve
    // on ajoute un argument avec le fichier cible de la recherche
    argv[argc] = "eng.txt";

     // Le dernier élément du tableau doit être NULL 
     argv[argc+1] = (char *)NULL;  
     // On charge et exécute la commande reçue 
     if(execvpe(argv[0], argv, envl)== -1) 
     { 
           perror("execvpe "); 
           _exit(EXIT_FAILURE); 
     } 
}

int main(int argc, char *argv[], char *envp[]){

	pid_t pid; 
   	int statut; 
	if((pid = fork()) == -1)
    {
            perror("fork");
            exit(1);
    }
            if (pid == 0){
		        	printf("\t1er Fils %d de pere %d\n",(int) getpid(), (int) getppid());
		        	chercher(argc,argv,envp);
		        }
	        	pid = fork();
	        	if(pid == 0){
			        printf("\t2eme Fils %d de pere %d\n",(int) getpid(), (int) getppid());
			        chercher(argc,argv,envp);
			    }

                pid = fork();
                if(pid == 0){
                        printf("\t3eme Fils %d de pere %d\n",(int) getpid(), (int) getppid());
                        chercher(argc,argv,envp);  
                }

	            pid = fork();
                if(pid == 0){
	                printf("\t4eme Fils %d de pere %d\n",(int) getpid(), (int) getppid());
			        chercher(argc,argv,envp);
					exit(0);
				}else{
                printf("Pere %d de pere %d\n",(int) getpid(), (int) getppid());

		                //On est dans le parent 
				         printf("** Enfant créé  %d : - cherche chaine %s\n",pid, argv[1]); 
				         for(int cpt = 0; cpt < argc; cpt++) 
				         { 
				               printf ("arg %i : %s\n", cpt,  argv[cpt]); 
				         } 
				         // On attend la terminaison du processus enfant 
				         pid = wait(&statut); 
				         // La macro WEXITSTATUS() permet d’isoler 
				         // le code de terminaison envoyé par le processus enfant. 
				         printf("Statut retourné par %ld : %d\n",pid, WEXITSTATUS(statut));
        }
}