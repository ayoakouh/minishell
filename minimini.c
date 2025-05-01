#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int    ac, char    **av, char  **envp)
{
    pid_t pid;
    char *argv[] = {"/bin/ls", "-l", NULL};
    char *argv2[] = {"/usr/bin/wc", "-l", NULL};
    int i = 0;

    int  fd[2]; //fd[0]--> read , fd[1] --> write;
    pipe(fd);
    while (i < 2)
    {
        pid = fork();
        if (pid < 0) 
        {
            perror("fork failed");
            return 1;
        }
        else if (pid == 0)  // child process
        {
            if(i == 0) //commande 1
            {
                close(fd[0]);
                dup2(fd[1], 1);
                close(fd[1]);
            }
            else if (i == 1)
            {
                close(fd[1]);
                dup2(fd[0], 0);
                close(fd[0]);
            }
            if (pid == -1)
            {
                perror("execve failed");
                return 1;
            }
            if(i == 0)
                execve(argv[0], argv, envp);
            else if(i == 1)
                execve(argv2[0], argv2, envp);
        }
        i++;
    }
    while (wait(NULL) > 0)
        ;
    close(fd[0]);
    close(fd[1]);
}
