#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>

int main(int argc, char** argv)
{
    puts("C-lisp version 0.1\n");
    puts("Press Ctrl-C to exit\n");

    while(1)
    {
        char* input = readline("clisp> ");

        add_history(input);

        printf("\nEchoing : %s\n",input);

        free(input);
    }

    return 0;
}
