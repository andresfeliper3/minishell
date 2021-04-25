#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){

	char str[100];
	printf("digite un comando: ");
	fgets(str, 100,stdin);

	//IGNORAMOS FILA 0 PORQUE C GUARDA BASURA EN LA FILA 0	
	char args[50][50] = {'0'};	
	int i = 1;
	int j = 0;
	int k = 0;
	bool estado = false;
	
	while( !(str[k] == '\0') ){
			//ls    -l
	   if( str[k] != ' '){
		    estado = false;
		    args[i][j] = str[k];
	    	    j++;		 
	   }else{
	   	if (estado == false){
			i++;
			j = 0;
			estado = true;
		}
	   }
	   k++;
	
	}
	printf("valor de i final %d\n", i);
	printf("Fila 1 de args %s\n", args[1]);
	printf("Fila 2 de args %s\n ", args[2]);
	char *cmd[i+1];
	for(int p = 0; p < i; p++){
		cmd[p] = strdup(args[p+1]);
	}
	
	cmd[i] = NULL;	
	
	printf("fila 0 de cmd %s\n", cmd[0]);
	printf("Fila 1 de cmd %s\n", cmd[1]);
	printf("Fila 2  de cmd %s\n", cmd[2]);

	execvp(cmd[0], cmd);
	perror("Return from execvp() not expected");
	exit(EXIT_FAILURE);
	/*
	char *myargs[3];

	myargs[0] = strdup("ls");
	myargs[1] = strdup("-l");
	myargs[2] = NULL;

	execvp(myargs[0], myargs);
	perror("Return from execvp() not expected");
	exit(EXIT_FAILURE);
*/
	
	
	return 0;
}
