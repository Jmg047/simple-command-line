/**************************************************************
* Class:  CSC-415-02 Spring 2023
* Name: Jaime Guardado
* Student ID: 920290979
* GitHub ID: Jmg047
* Project: Assignment 3 – Simple Shell
*
* File: guardado_jaime_HW3_main.c
*
* Description: The prupose of this assignment is to create 
* a simple shell which runs on top of the Linux CLI, there 
* are child processes which will return a result, and this 
* assignment will demonstrate fork() and execvp().
*
**************************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_ARGS    12
#define MAX_LINE_BUFF    102

int main (int argc, char* argv[]) {

    int i = 0;               // i set to 0 for indexing purposes.
    int status;              // waitpid parameter
    char *clp;               // Commandline prompt will be represented with 'clp' 
    char *input[MAX_ARGS];
    char commands[MAX_LINE_BUFF];


    if (argc == 2) {
        clp = argv[1];      // approrpriate prompt will be assigned
    } 

    while (1) {

        printf("%s", clp);  // display the prompt
        
        if(fgets(commands, MAX_LINE_BUFF, stdin) == NULL) {     // fgets() --> read user input 
            // handle End of File error, gracefully
            printf("\n");
            return 0;
        }

        // EOF identifier for when the user uses "\n" / Enter-key
        if (commands[strlen(commands) - 1] == '\n') {
            // '\0' so programs can find end of a string
            commands[strlen(commands) - 1] = '\0';
        }

        if (strlen(commands) == 0) {
            // handle empty user input
            //printf("\n");   
            continue;
        }

        i = 0;
        char *substr = strtok(commands, " ");   // get first token, white space will be the delimiter

        while (substr != NULL) {
            input[i] = substr;          // every substring (substr) will populate input array
            substr = strtok(NULL, " "); // NULL passed in to continue tokenizing substrings.
            i++;
        }

        input[i] = NULL;        // NULL indicates the last substring for input
        pid_t pid = fork();     // fork() creates a child process, represented by 'pid' 

        if (pid == 0 && strcoll(input[0], "exit") != 0) {   
            // child process -> execvp start executing program with argument 
            execvp(input[0], input);
            return 1;
        } else if (pid <= -1) {
            // catch and handle any failures with creating a new child process
            printf("Child %d, failed to fork \n", pid);
            return 1;
        } else {
            // wait for parent process to finish if pid > 0
            waitpid(pid, &status, 0);
            if (WEXITSTATUS(status) != 0) {
                printf ("Child %d, exited with status: %d \n", pid, WEXITSTATUS(status));
            }

        }

        if (strcoll(input[0], "exit") == 0) {
            // "exit" will exit the shell program.
            return 0;
        }


    }

    return 0;
}
