#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <assert.h>
#include <sys/wait.h>
int main (int argc, char* argv[]) {
		pid_t pid;
		int estado;
		char* valor[1];
		printf("Escriba\n");
		scanf("%s", valor[0] );
		pid = fork();
		assert(pid >= 0);

		//hijo
		if(pid == 0) {
			printf("Soy el hijo");
			char *cmd[1];
			int i;
			for(i = 0; i < 1; i++) {
			 cmd[i] = valor[i];
			}
			cmd[1] = NULL;
			execvp(cmd[0], cmd);
			perror("Return from execvp() not expected");
			exit(EXIT_FAILURE);		 		
		}
		//padre	
		else {
			wait(&estado);
			if(WIFEXITED(estado)) { //valido si el hijo sale de manera natural no eliminado por señal
				printf(":)  %d\n", WEXITSTATUS(estado));
			}
		}

		
}

