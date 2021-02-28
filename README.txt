## Table of Contents
1. [General Info]
2. [Technologies]
4. [Instructions]
    - 4.1 [Formatting instructions]


### General Info
***

"Smpbashshell" is a simple implementation of bash shell written in C language.
This program can receive variety combinations of user defined commands to execute them.
It simply takes input of the user and store the commands to run a certain program that are included in Linux terminal commands.


## Technologies
***

A list of technologies used within the project:
Microsoft Visual Studio Code
C language


## Instructions
***

Give instructions on how to collaborate with your project.
> It repeatedly asks for user input after execution of previous of command
> To exit or terminate the program, you can either type "exit" or "quit"
> Also, keystroke CTRL+D terminates the program
> Use make in terminal to update changes

## Formatting instructions 

> The user can use piping(|) between each commands to pass information to the next command.
> Please make sure there is a space between each commands.
    > Eg: note that commands "ls -al | grep someline" has space between every commands and uses piping (|) to pass output of "ls -al"
    > the files that are stored in the current directory
    > to the next command "grep someline" where receives the output of previous commands and executes "grep" commands to select lines that contain "someline".

