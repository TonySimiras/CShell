#include <stdio.h>
#include <sys/syscall.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "libshell.h"

char *args[20];
int argsc;


Command commands[] = {
	{"pwd", shell_pwd},
	{"echo", shell_echo},
	{"cd", shell_cd},
	{"exit", shell_exit},
};

void proceseaza_input(char *input){
	input[strcspn(input, "\n")] = 0; //elimina \n de la sfarsitul sirului
	char *token = strtok(input, " ");
	int index=0;

	while (token != NULL)
	{
        	args[index++] = strdup(token);
        	token = strtok(NULL, " "); 
	}

	argsc = index;
}


void shell_prompt(){
	char prompt_path[1024];
	syscall(SYS_getcwd, prompt_path, sizeof(prompt_path));
	syscall(SYS_write,1,"\033[34m",5);
	syscall(SYS_write,1, prompt_path, strlen(prompt_path));
	syscall(SYS_write,1, "\033[0m$ ",6);
}


void shell_execute(char *command){
	int commands_c= sizeof(commands)/sizeof(commands[0]);
	for(int i=0;i<commands_c;i++){
		if(strcmp(command, commands[i].name) ==0) {
		commands[i].func();
		return;
		}
	}
	syscall(SYS_write,1,"\033[31mComanda inexistenta: \033[0m",30);
        syscall(SYS_write,1, args[0], strlen(args[0]));
        new_line();
}


void new_line(){
	syscall(SYS_write,1,"\n",1);
}

void free_buffer(char **buffer, int counter){
	for(int i=0; i<counter;i++){
		free(buffer[i]);
	}
}

void shell_pwd(){
	char current_path[1024];
	syscall(SYS_getcwd, current_path, sizeof(current_path));
	syscall(SYS_write,1, current_path, strlen(current_path));
	new_line();

}


void shell_echo(){
	if(argsc>1){
		for(int i=1; i<argsc; i++){
			syscall(SYS_write,1,args[i],strlen(args[i]));
			syscall(SYS_write,1," ",1);
	}
	new_line();
}
}

void shell_cd(){
	if(argsc>1 && args[1]!=NULL){
		if(syscall(SYS_chdir,args[1])!=0){
			syscall(SYS_write,1,"\033[31mDirector inexistent\n\033[0m",30);
		}
	}
	else syscall(SYS_chdir,"/home/tony");
}


void shell_exit(){
	syscall(SYS_exit,0);
}
