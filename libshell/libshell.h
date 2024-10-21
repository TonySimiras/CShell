
#ifndef LIBSHELL_H
#define LIBSHELL_H

void proceseaza_input(char *input);
void shell_prompt();
void shell_execute(char *command);
void new_line();
void free_buffer(char **buffer, int counter);
void shell_pwd();
void shell_echo();
void shell_cd();
void shell_exit();

extern char *args[20];
extern int argsc;

typedef struct {
    const char *name;
    void (*func)();
} Command;

#endif
