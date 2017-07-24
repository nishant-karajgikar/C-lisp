#include "parsing.h"
#include "evaluation.c"

int main(int argc, char** argv)
{
   
    /* Create Some Parsers */
    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* Lispy = mpc_new("lispy");

    /* Define them with the following language  */
    mpca_lang(MPCA_LANG_DEFAULT,
    "                                                     \
      number   : /-?[0-9]+/ ;                             \
      operator : '+' | '-' | '*' | '/' ;                  \
      expr     : <number> | '(' <operator> <expr>+ ')' ;  \
      lispy    : /^/ <operator> <expr>+ /$/ ;             \
    ",
    Number, Operator, Expr, Lispy);

    puts("C-lisp version 0.1\n");
    puts("Press Ctrl-C to exit\n");

    while (1)
    {
        char *input = readline("\nlispy> ");

        add_history(input);

        mpc_result_t res;

        if (mpc_parse("<stdin>", input, Lispy, &res))
        {
            /*On success, print the AST*/
            mpc_ast_print(res.output);
            lval result = eval(res.output);
            printf("Result : ");
            lval_println(result);
            mpc_ast_delete(res.output);
        }
        else
        {
            printf("We found an error:\n");
            /*Otherwise, print the error*/
            mpc_err_print(res.error);
            mpc_err_delete(res.error);
        }

        free(input);
    }

    /*cleaning up the parsers*/
    mpc_cleanup(4, Number, Operator, Expr, Lispy);

    return 0;
}
