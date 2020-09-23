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
	if((pid = fork()) == -1)
    {
            perror("fork");
            exit(1);
    }
            if (pid == 0){
		        	printf("\t1er Fils %d de pere %d\n",(int) getpid(), (int) getppid());
		        	chercher(argc,argv,envp,0);
		        	exit(0);
		        }
	        	pid = fork();
	        	if(pid == 0){
			        printf("\t2eme Fils %d de pere %d\n",(int) getpid(), (int) getppid());
			        chercher(argc,argv,envp,1);
			        exit(0);
			    }

                pid = fork();
                if(pid == 0){
                    printf("\t3eme Fils %d de pere %d\n",(int) getpid(), (int) getppid());
                    chercher(argc,argv,envp,2);
                    exit(0);  
                }

	            pid = fork();
                if(pid == 0){
	                printf("\t4eme Fils %d de pere %d\n",(int) getpid(), (int) getppid());
			        chercher(argc,argv,envp,3);
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