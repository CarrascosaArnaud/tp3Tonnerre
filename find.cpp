#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h> 

int main(int argc, char *argv[], char *envp[]) 
{ 
   pid_t pid_eng; 
   int statut; 
   if(argc < 2) 
   { 
         printf("Entrez une chaine a chercher par exemple : ./find chaine \n",argv[0]); 
         return 1; 
   } 
   // Création du processus enfant 
   pid_eng = fork(); 
   if(pid_eng == -1) 
   { 
         perror("erreur de fork "); 
         return errno; 
   } 
   if(pid_eng) 
   { 
         //On est dans le parent 
         printf("** Enfant créé  %d : - cherche chaine %s\n",pid_eng, argv[1]); 
         for(int cpt = 0; cpt < argc; cpt++) 
         { 
               printf ("arg %i : %s\n", cpt,  argv[cpt]); 
         } 
         // On attend la terminaison du processus enfant 
         pid_eng = wait(&statut); 
         // La macro WEXITSTATUS() permet d’isoler 
         // le code de terminaison envoyé par le processus enfant. 
         printf("Statut retourné par %ld : %d\n",pid_eng, WEXITSTATUS(statut)); 
   } 
   else 
   { 
         //On est dans l’enfant 
         int cpt; 
        //On prépare un environnement très réduit 
         char *envl[]= {"LANG=C",NULL}; 
         printf("\t-- Enfant pid %d\n",(int)getpid()); 
         // On modifie la liste d’arguments reçue : 
         // Le nom du programme chargé doit être le premier argument 
         argv[0] = "grep"; 
         // argv[1] est la chaine a rechercher on conserve
        // on ajoute un argument avec le fichier cible de la recherche
        argv[argc] = "english.txt";

         // Le dernier élément du tableau doit être NULL 
         argv[argc+1] = (char *)NULL;  
         // On charge et exécute la commande reçue 
         if(execvpe(argv[0], argv, envl)== -1) 
         { 
               perror("execvpe "); 
               _exit(EXIT_FAILURE); 
         } 
   } 
   return 0; 
}