#include <unistd.h> 
#include <stdio.h> 
#include <string.h> 
#include <errno.h> 
#include <stdlib.h>

int main(void)
{
        int     fd[2], nbytes;
        pid_t   childpid;
        char    string[] = "Hello, world!\n";
        char    readbuffer[80];

        pipe(fd);
        
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid ==0 )
        {
                printf("\t--Processus enfant %d de pere %d\n",(int) getpid(), (int) getppid());
                close(fd[0]);
                printf("\t--Fermeture de la lecture sur le tube\n");

                nbytes = write(fd[1], string, (strlen(string)+1));
                printf("\t--Le fils a ecrit %d octets\n",nbytes);

                exit(0);
        }
        else
        {
                printf("**Processus pere %d\n",(int) getpid());
                close(fd[1]);
                printf("**Fermeture de l'ecriture sur le tube\n");  

                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("**Le pere a recu %d octets\n",nbytes);
                printf("**String recu : %s\n", readbuffer);
        }
        
        return(0);
}