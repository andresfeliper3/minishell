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
	   if( str[k] != ' ' && str[k] != '\r' && str[k] != '\n'){
		    estado = false;
		    args[i][j] = str[k];
	    	    j++;		 
	   }else{
	   	if (estado == false && str[k] == ' '){
			i++;
			j = 0;
			estado = true;
		}
	   }
	   k++;
	
	}
	char *cmd[i+1];
	for(int p = 0; p < i; p++){
		cmd[p] = strdup(args[p+1]);
	}
	
	cmd[i] = NULL;	

	execvp(cmd[0], cmd);
	perror("Return from execvp() not expected");
	exit(EXIT_FAILURE);
	
	return 0;
}
