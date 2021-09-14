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
	
	/*Condicion de parada \0 ya que todo string en C (en la matriz) acaba con un \0
	str es lo que el usuario digitó (es un array)
	args es una matriz la cual estamos guardando cada comando por linea de la matriz
	  0 1 2 3
	1|l s 
	2|
	3| 
	k es el iterador que recorre todo la matriz char.
	i e j iteran la matriz args
	*/
	while( !(str[k] == '\0') ){
			//ls    -l
	   if( str[k] != ' ' /*&& str[k] != '\r'*/ && str[k] != '\n'){
		    estado = false;
		    args[i][j] = str[k];
	    	j++;		 
	   		printf("%c",str[k]);
	   }else{
		/*Objetivo del estado: Evitar que la matriz args salte de fila cuando 
		anteriormente ya lo había hecho.
		(Cuando hay espacios consecutivos)*/
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
		// cmd[p] = strdup(args[p+1]);
		cmd[p] = args[p+1];
	}
	
	cmd[i] = NULL;	

	execvp(cmd[0], cmd);
	perror("Return from execvp() not expected");
	exit(EXIT_FAILURE);
	
	return 0;
}
