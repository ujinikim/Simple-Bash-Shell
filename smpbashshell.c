//
//  main.c
//  simple shell implementation
//  CS 4348 - Section 004
//  Project
//  Created by Jin Kim on 2/14/21.
//

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_BUFFER_LEN 1024
#define READ_END 0
#define WRITE_END 1

//tokenizes the user input separeted by each pipes into tokens using the space delimiter
//the tokenized input to be stored in pointer array dividedArg.
void tokenizeIt(char args[], char *dividedArg[])
{
    
    char *temparg;
    int cnt = 0;
    char* delim = " ";
    temparg = strtok(args, delim);
    while ( temparg )
    {
        dividedArg[cnt++] = strdup(temparg);
        temparg = strtok(NULL, delim);
    }

}


int main()
{
    //takes user input
    char commands[MAX_BUFFER_LEN];
    char* delimPipe = "|";
    
    while(1)
    {
        puts("\n--- Enter some commands below ---");
        fgets(commands, MAX_BUFFER_LEN, stdin);
        
        commands[strlen(commands) - 1] = '\0';
        if(strcmp("exit", commands) == 0 | strcmp("quit", commands) == 0)
            {
            return 0;
            }

        
        //use strtok to tokenize each arguments(commands) using delimiter (|) into pointer array args
        char *args[50];
        char *temparg;
        temparg = strtok(commands, delimPipe);
        int numArgs = 0;
        while (temparg)
        {
            args[numArgs++] = strdup(temparg);
            temparg = strtok(NULL, delimPipe);
        }
             
        // number of pipes are one less than number of arguments(commands)
        int numPipes = numArgs - 1;
        int fd[numPipes][2]; //created file descriptor for each pipes
        int i = 0;
        for(i = 0; i < numPipes; i++) //for loop to open each pipes
        {
            if (pipe(fd[i]) == -1)
            {
                fprintf( stderr, "Pipe failed.\n" );
                _exit(1);
            }
        }

        
        pid_t pid; // process id
        i = 0;
         //for loop to execute each user commands
         //every iterlation, the process forks and makes a child processor to execute
        for(i = 0; i < numPipes; i++)
        {
            pid = fork();
            if( pid == 0 )
            {
                char *dividedArg[50]; // resets the dividedArgs(commands separated by the space delimiter)
                tokenizeIt(args[i], dividedArg); //call tokenize function and store them into dividedArgs
                
                
                if(i == 0) // if it's first pipe, close the unused file descriptors and dup2 to sync the pipe so the next process receives
                {
                    close(fd[0][0]);
                    dup2(fd[i][1], 1);
                    close(fd[i][1]);
                
                }
                else if(0 < i < numArgs - 1) // if it's neither first nor last iteration
                {
                    dup2(fd[i-1][0], 0);
                    dup2(fd[i][1], 1);

                }
                else //if it's last iteration
                {
                    close(fd[i][1]);
                    dup2(fd[i-1][0], 0);
                    close(fd[i][0]);
                }
                
                if( execvp(dividedArg[0], dividedArg ) < 0 ) //executes the command
                {
                    perror("exec fail");
                    _exit(1);
                }
                
            }
            else if( pid < 0 ) //fork fails
            {
                perror("fork fail");
                _exit(1);
            }
            else if( pid > 0) //if the current process is a parent process, then wait for child process to finish and close the file descriptor
            {
                wait(NULL);
                close(fd[i][1]);
            }
        }
        
        pid = fork(); //fork for last pipe, used to receive read end of last pipe
        if(pid == 0) //if child process
        {
            char *dividedArg[50];
            tokenizeIt(args[numArgs-1], dividedArg);
            dup2(fd[numPipes-1][0], 0);
            if( execvp(dividedArg[0], dividedArg ) < 0 )
            {
                perror("exec fail");
                _exit(1);
            }
        }
        wait(NULL); // wait for all the processes to finish
        

        i = 0;
        for(i = 0; i < numPipes; i++) // all the file descriptors are used and now needs to be closed
        {
            close(fd[i][0]);
            close(fd[i][1]);
        }
            
    }


    
}


