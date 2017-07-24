#include "parsing.h"

typedef struct {
    int type;
    long num;
    int err;
} lval;

/*Create enumeration of possible lval types*/
enum {
    LVAL_NUM,
    LVAL_ERR
};

/*Create enumeration of possible error types*/
enum {
    LERR_DIV_ZERO,
    LERR_BAD_OP,
    LERR_BAD_NUM
};

/* Create a new number type lval */
lval lval_num(long x) {
    lval v;
    v.type = LVAL_NUM;
    v.num = x;
    return v;
}
/* Create a new error type lval */
lval lval_err(int x) {
    lval v;
    v.type = LVAL_ERR;
    v.err = x;
    return v;
}

void lval_print(lval v) {
    switch (v.type) {
        case LVAL_NUM: printf("%li", v.num); break;

        case LVAL_ERR:
            if (v.err == LERR_DIV_ZERO) {
                printf("Error: Division by Zero!");
            } else if (v.err == LERR_BAD_OP) {
                printf("Error: Invalid operator!");
            } else if (v.err == LERR_BAD_NUM) {
                printf("Error: Invalid number!");
            }
        break;
    }
}

void lval_println(lval v) 
{ 
    lval_print(v); 
    printf("\n"); 
}