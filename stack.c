#include "stack.h"
#include<stdlib.h>
void sinit(stack *s){
    s->l = (list*)malloc(sizeof(list));
    s->top = 0;
    s->com = 1;
}
void push(stack *s, list *l){
    if(s->top+1 == s->com){
        init(&s->l[s->top]);
        copyl(&s->l[s->top++], l);
        s->com++;
        s->l = realloc(s->l, s->com*(sizeof(list)));
    }
    else{
        init(&s->l[s->top]);
        copyl(&s->l[s->top++], l);
    }
}
list pop(stack *s){
    s->top--;
    return s->l[s->top];
}
int isempty(stack *s){
    if(s->top == 0){
        return 1;
    }
    return 0;
}
int cisempty(cstack *cs){
    if(cs->top == 0){
        return 1;
    }
    return 0;
}
void prst(stack s){
    for(int i= s.top-1; i >= 0; i--){
        print(s.l[i]);
    }
}
void cinit(cstack *cs){
    cs->c = malloc(sizeof(char));
    cs->top = 0;
}
void cpush(cstack *cs, char ch){
    if(cs->top+1 == sizeof(cs->c)/sizeof(char)){
        cs->c[cs->top++] = ch;
        cs->c= realloc(cs->c, (cs->top+1)*sizeof(char));
    }
    else{
        cs->c[cs->top++] = ch;
    }
}
char cpop(cstack *cs){
    cs->top--;
    return cs->c[cs->top];
}
void cprst(cstack cs){
    for(int i = cs.top-1; i >= 0; i--){
        printf("%c\n", cs.c[i]);
    }
}
char ctop(cstack *cs){
    return cs->c[cs->top-1];
}