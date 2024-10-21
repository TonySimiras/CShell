#include <stdio.h>
#include <sys/syscall.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "libshell.h"

int main(){
while(1){
	char input[256];

	shell_prompt();

	syscall(SYS_read,0,input,sizeof(input));
	
	proceseaza_input(input);


	if (argsc > 0 && args[0] != NULL) {
            shell_execute(args[0]);
	}

	free_buffer(args,argsc);
	
	

}

return 0;
}
