#include <unistd.h> 
#include <stdio.h> 
#include <string.h> 
#include <errno.h> 
#include <stdlib.h>

int main(void)
{
        int rayon = 5;
        const double pi = 3.14159265358979323846;
        pid_t pid;
        int fd[2];
        pipe(fd);
        char readbuffer[60];

        if((pid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if (pid == 0){
                printf("\t1er Fils %d de pere %d\n",(int) getpid(), (int) getppid());
                int surface = rayon*rayon*pi;
                char string[] = "Rayon = \%d, Surface = \%d\n";//Simulation d'envoi données
                close(fd[0]);
                write(fd[1],string,(strlen(string)+1));
                exit(0);
        }else{
                printf("Pere %d de pere %d\n",(int) getpid(), (int) getppid());
                read(fd[0], readbuffer, sizeof(readbuffer));
                printf("%s\n", readbuffer);
                if((pid = fork()) == -1)
                {
                        perror("fork");
                        exit(1);
                }

                if(pid == 0){
                        printf("\t2eme Fils %d de pere %d\n",(int) getpid(), (int) getppid());
                        int perimetre = 2*rayon*pi;
                        char string[] = "Rayon = \%d, Perimetre = \%d\n";//Simulation d'envoi données
                        close(fd[0]);
                        write(fd[1],string,(strlen(string)+1));
                        exit(0);
                }
                close(fd[1]);
                read(fd[0], readbuffer, sizeof(readbuffer));
                printf("%s\n", readbuffer);
        }
}