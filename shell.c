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
void  split(char string[], char **split_string, const char delimiter[] ){
 char *token = strtok(string, delimiter);
 int n = 0;
 while(token != NULL)
 {
	split_string[n] = token;
  	n++;
  	token = strtok(NULL, delimiter);
 }
  split_string[n] = NULL; //split_string must have NULL in the last position
}
void bufferToFile(char *left_side[] , char *file_reach[]){
    int file = open(file_reach[0],O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR ); //Open the file in the previous modes.
    dup2(file, STDOUT_FILENO); //Allow the output to go to the file
    close(file); 
    execvp(left_side[0],left_side); //Execute the commands
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
	}else {
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
