#include<stdio.h>
#include "ll.h"
typedef struct stack
{
    list *l;
    int top;
    int com;
}stack;
typedef struct cstack
{
    char *c;
    int top;
}cstack;
void sinit(stack *s);
void push(stack *s, list *l);
list pop(stack *s);
void prst(stack s);
void cinit(cstack *);
void cpush(cstack *, char);
char cpop(cstack *);
void cprst(cstack);
char ctop(cstack *);
int isempty(stack *s);
int cisempty(cstack *cs);
