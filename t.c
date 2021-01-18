
#include "stack.h"
#include <stdio.h>
int main(){
    stack s;
    sinit(&s);
    list l = strtn("1234.23");
    list m = strtn("2345.23");
    push(&s,&l);
    push(&s,&m);
    m=pop(&s);
    print(m);
    return 0;
}