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

        if((pid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if (pid == 0){
                printf("\t1er Fils %d de pere %d\n",(int) getpid(), (int) getppid());
                int surface = rayon*rayon*pi;
                printf("Rayon = %d, Surface = %d\n",rayon, surface);
                exit(0);
        }else{
                printf("Pere %d de pere %d\n",(int) getpid(), (int) getppid());
                
                if((pid = fork()) == -1)
                {
                        perror("fork");
                        exit(1);
                }

                if(pid == 0){
                        printf("\t2eme Fils %d de pere %d\n",(int) getpid(), (int) getppid());
                        int perimetre = 2*rayon*pi;
                        printf("Rayon = %d, Perimetre = %d\n",rayon, perimetre);
                        exit(0);
                }
        }
}