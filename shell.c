/*
	Andrés Felipe Rincón - 1922840
	Juan Camilo Randazzo - 1923948
*/




#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*
  nameFunction: includes
  arguments: array of chars * char
  returns: boolean
  purpose: Gets a word and a letter and returns whether the letter is within the word or not. 
 */
bool includes(char word[], char letter)
{
	for (int i = 0; i < strlen(word); i++)
	{
		if (word[i] == letter)
		{
			return true;
		}
	}
	return false;
}
/*
	nameFunction: split
	arguments: array of  chars, matrix of chars, array of chars
	returns: integer
	purpose: Takes a array of chars and returns a matrix of the words split by the delimiter
*/
int split(char string[], char **split_string, const char delimiter[])
{
	char *token = strtok(string, delimiter);
	int n = 0;
	while (token != NULL)
	{
		split_string[n] = token;
		n++;
		token = strtok(NULL, delimiter);
	}
	split_string[n] = NULL; //split_string must have NULL in the last position
	return n;
}

/*
	nameFunction: bufferToFile
	arguments: matrix of chars, matrix of chars
	returns: void
	purpose: execute the redirection command.
*/
void bufferToFile(char *left_side[], char *file_reach[])
{
	int file = open(file_reach[0], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); //Open the file in the previous modes.
	dup2(file, STDOUT_FILENO); //Allow the output to go to the file
	close(file);
	execvp(left_side[0], left_side); //Execute the commands
}

void pipeline(char *left_side[], char *right_side[])
{

	pid_t pid;
	int fd[2];
	if (pipe(fd) == -1)
	{
		perror("Pipe's in the making...");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		//This section is executed by the son's process.
		close(fd[1]);//Closes the write descriptor since we're not interested by
		dup2(fd[0], STDIN_FILENO); //Clones the read descriptor into the default input.
		execvp(right_side[0], right_side);
	}
	else if (pid == -1)
	{
		perror("fork execution failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		//This section is executed by the dad process.
		close(fd[0]); //Closes the read descriptor.
		dup2(fd[1], STDOUT_FILENO);
		execvp(left_side[0], left_side);
	}
}
int main(int argc, char *argv[])
{
	char str[100];
	printf("Type a command: ");
	fgets(str, sizeof(str), stdin);

	//Find new line if exists
	char *ptr = strchr(str, '\n');

	if (ptr)
	{
		*ptr = '\0'; //Replace the newline character in the string with '\0'
	}

	if (includes(str, '>'))
	{
		char *new_str[3];
		char *left_side[7];
		char *right_side[4];
		char *file_reach[2];
		//Splits the str by the delimiter into pieces which will be saved into new_string
		split(str, new_str, ">");
		split(new_str[0], left_side, " ");
		split(new_str[1], right_side, " ");
		file_reach[0] = right_side[0];
		file_reach[1] = NULL;
		bufferToFile(left_side, file_reach);
	}
	else if (includes(str, '|'))
	{
		char *pipe[3];
		split(str, pipe, "|");
		char *left_side[4];
		char *right_side[10];
		split(pipe[0], left_side, " ");
		split(pipe[1], right_side, " ");
		pipeline(left_side, right_side);
	}
	else
	{
		char *argss[9];
		split(str, argss, " ");
		execvp(argss[0], argss);
		exit(EXIT_FAILURE);
	}

	return 0;
}
