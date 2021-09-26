#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


bool includes(char word[], char letter){
	for(int i = 0; i < strlen(word); i++){
		if(word[i] == letter){
			return true;
		}
	}
	return false;
}
//Takes a array of chars and returns a matrix of the words split by the delimiter
int  split(char string[], char **split_string, const char delimiter[] ){
 char *token = strtok(string, delimiter);
 int n = 0;
 while(token != NULL)
 {
	split_string[n] = token;
  	n++;
  	token = strtok(NULL, delimiter);
 }
  split_string[n] = NULL; //split_string must have NULL in the last position
  return n;
}

int  splitMatrix(char string[], char **split_string, const char delimiter[], int pos){
 char *token = strtok(string, delimiter);
 while(token != NULL)
 {
	split_string[pos] = token;
  	pos++;
  	token = strtok(NULL, delimiter);
 }
  split_string[pos] = NULL; //split_string must have NULL in the last position
  return pos;
}

void bufferToFile(char *left_side[] , char *file_reach[]){
    int file = open(file_reach[0],O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR ); //Open the file in the previous modes.
    dup2(file, STDOUT_FILENO); //Allow the output to go to the file
    close(file); 
    execvp(left_side[0],left_side); //Execute the commands
}

void pipeline(char* left_side[], char* right_side[]){

	pid_t pid;
 	int fd[2];
 	if (pipe(fd) == -1) {
  		perror("Creating pipe");
  		exit(EXIT_FAILURE);
 	}
 	pid = fork();
 	if (pid == 0){
 	//Esta seccion de codigo es ejecutada por el hijo
   		close(fd[1]); //Se cierra el descriptor de escritura del pipe
   		dup2(fd[0], STDIN_FILENO);//Permite leer la salida que retorna el padre
   		execvp(right_side[0], right_side);
   		printf("Esto no se deberia imprimir\n");
 	}
 	else if (pid == -1){
  		perror("fork() failed");
  		exit(EXIT_FAILURE);
 	}
 	else{
 	//Esta seccion es ejecutada por el padre
  		close(fd[0]);
  		dup2(fd[1], STDOUT_FILENO);
  		execvp(left_side[0], left_side);
 	}

}
int main(int argc, char* argv[]){
	

	char str[100];
	printf("digite un comando: ");
	fgets(str, sizeof(str), stdin);

	//Find new line
	char *ptr = strchr(str, '\n');

	if(ptr){
		*ptr = '\0'; //Replace the newline character in the string with '\0'
	}

	if(includes(str,'>')){
		char* new_str[3];
		char* left_side[7];
		char* right_side[4];
		char* file_reach[2];
		split(str, new_str, ">");
		split(new_str[0], left_side, " ");
		split(new_str[1], right_side, " ");
		file_reach[0] = right_side[0];
		file_reach[1] = NULL;

		bufferToFile(left_side, file_reach);
		// printf("right side [0]%s\n", right_side[0]);
		// printf("left side [0]%s\n", left_side[0]);
		// printf("left side [1]%s\n", left_side[1]);
		// for(int i = 0; i < 3; i++){
		// 	printf("%s", new_str[i]);
		// }
	}else if (includes(str, '|')){
		char *pipe[3];
		split(str, pipe, "|");

		// char *matrix[] = {0};
		// int result = split(pipe[0], matrix," ");
		// int result2 = splitMatrix(pipe[1], matrix, " ", result);
		// printf("%d", result2);
		printf("pipe[0] %s\n", pipe[0]);
		printf("pipe[1] %s\n", pipe[1]);
		printf("pipe[2] %s\n", pipe[2]);
		// printf("pipe[3] %s", pipe[3]);
		// char *left_side[4];
		// char *right_side[10];
		// split(pipe[0], left_side," ");
		// split(pipe[1], right_side," ");
		//  printf("%s\n", matrix[0]);
		//  printf("%s\n", matrix[1]);
		//  printf("%s\n", matrix[2]);
		// for(int i = 0; i < 4; i++){
		// 	printf("%s", *matrix[i]);
		// }
		// pipeline(left_side, right_side);
	}else{
		char *argss[9];
		split(str, argss, " ");
		// printf("%s", argss[0]);
		// printf("%s", argss[1]);
		// printf("%s", argss[2]);
		execvp(argss[0], argss);
		exit(EXIT_FAILURE);

	}
	
	return 0;
}
