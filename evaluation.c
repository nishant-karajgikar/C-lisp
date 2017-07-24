#include "parsing.h"
#include "lval.c"

lval eval_op(lval x, char* op, lval y) {

    /* Guard for operands */
    if (x.type == LVAL_ERR) {
        return x;
    } 

    if (y.type == LVAL_ERR) {
        return y;
    }

    if(strcmp(op, "+") == 0) {return lval_num(x.num + y.num);}
    if(strcmp(op, "-") == 0) {return lval_num(x.num - y.num);}
    if(strcmp(op, "*") == 0) {return lval_num(x.num * y.num);}
    if(strcmp(op, "/") == 0) {
        return (y.num == 0) 
                ? lval_err(LERR_DIV_ZERO) 
                : lval_num(x.num / y.num);
    }

    return lval_err(LERR_BAD_OP);
}

lval eval(mpc_ast_t* t) {

    // printf("%s",t->tag);
    if(strstr(t->tag, "number")) {

        errno = 0;
        long x = strtol(t->contents, NULL, 10);

        return errno != ERANGE ? lval_num(x) : lval_err(LERR_BAD_NUM);
    }

    // the operator is always the second child of an ast
    // printf("reading operator as : %s", t->children[1]->contents);
    char *op = t->children[1]->contents;

    // we store the third child in 'x'
    lval x = eval(t->children[2]);

    // iterate the remaining children and combining
    int i = 3;
    while(strstr(t->children[i]->tag, "expr")) {
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }

    return x;
}