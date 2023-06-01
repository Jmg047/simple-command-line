simple shell program that runs on Linux. It reads user input, parses the commands, and executes them using fork() and execvp(). After executing each command, it waits for the child process to complete and prints the child's PID, and return result.
The shell supports executing commands by specifying either a path to the executable file or by using path expansion. It handles errors while reading input and gracefully exits on EOF. It prevents buffer overflow by limiting input size to 102 bytes.
Before executing a command, the shell separates the input into the executable file and arguments. It handles empty input as an error. The arguments are stored in an array and passed to execvp(). The shell does not support the "cd" command.
The program accepts a command-line argument for the prompt. It uses "> " as the default if no prompt is specified.
The assignment requires submitting source code, Makefile, and a write-up in PDF format. The write-up should include implementation details, encountered issues, and output screenshots. The program's output should match the provided sample execution.

