#include "parsing.h"

long eval_op(long x, char* op, long y) {

    if(strcmp(op, "+") == 0) {return x+y;}
    if(strcmp(op, "-") == 0) {return x-y;}
    if(strcmp(op, "*") == 0) {return x*y;}
    if(strcmp(op, "/") == 0) {return x/y;}

    return 0;
}


long eval(mpc_ast_t* t) {
    
    /* If tagged as numbre return it directly. */
    // if(t) {} else {
    //     printf("t is nil");
    //     return -1;
    // }

    // printf("%s",t->tag);
    if(strstr(t->tag, "number")) {
        return atoi(t->contents);
    }

    // the operator is always the second child of an ast
    // printf("reading operator as : %s", t->children[1]->contents);
    char *op = t->children[1]->contents;

    // we store the third child in 'x'
    long x = eval(t->children[2]);

    // iterate the remaining children and combining
    int i = 3;
    while(strstr(t->children[i]->tag, "expr")) {
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }

    return x;
}