#include "stack.h"
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<signal.h>
#define OPERAND 100
#define OPERATOR 200
#define ERROR 300
#define END 400
typedef struct token{
    int type;
    union data{
        list num;
        char op;
    }data;
}token;
enum states{SPC, OP,NUM, ERR, STOP};
token gettoken(char *s){
    static enum states currstate;
    static long long int i,j;
    static char *expr;
    char currchar;
    if(expr == 0){
        expr = malloc(sizeof(char)*strlen(s));
        currstate=SPC;
        i = 0;
        j=0;
        strcpy(expr,s);
    }
    else if(strlen(expr) < strlen(s) && strcmp(expr,s)!=0){
        expr = (char*)realloc(expr, ((strlen(s)+1)*sizeof(char)));
        strcpy(expr,s);
        currstate=SPC;
        i=0;
    }
    else if(strcmp(expr,s) != 0){
        strcpy(expr,s);
        i=0;
        currstate=SPC;
    }
    token t;
    static list n;
    while (1){
        currchar = expr[i];
        switch(currstate){
            case NUM:
                switch(currchar){
                    case '0':case '1':case '2':case '3':case '4':
                    case '5':case '6':case '7':case '8':case '9':
                        ins(&n,currchar,j);
                        j++;
                        currstate= NUM;
                        i++;
                        break;
                    case '+':case '-':case '*':case '/':case'%':case '(':case ')':
                        t.type = OPERAND;
                        t.data.num.ms = 1;
                        t.data.num.n=malloc(sizeof(char));
                        init(&t.data.num);
                        copyl(&t.data.num,&n);
                        currstate = OP;
                        i++;
                        return t;
                        break;
                    case ' ':
                        t.type = OPERAND;
                        t.data.num.ms = 1;
                        t.data.num.n=malloc(sizeof(char));
                        init(&t.data.num);
                        copyl(&t.data.num,&n);
                        currstate = SPC;
                        i++;
                        return t;
                        break;
                    case '\0':
                        t.type = OPERAND;
                        t.data.num.ms = 1;
                        t.data.num.n=malloc(sizeof(char));
                        init(&t.data.num);
                        copyl(&t.data.num,&n);
                        currstate = STOP;
                        return t;
                        break;
                    default:
                        t.type = OPERAND;
                        t.data.num.ms = 1;
                        t.data.num.n=malloc(sizeof(char));
                        init(&t.data.num);
                        copyl(&t.data.num,&n);
                        currstate = ERR;
                        return t;
                        break;
                }
                break;
            case OP:
                switch(currchar){
                    case '0':case '1':case '2':case '3':case '4':
                    case '5':case '6':case '7':case '8':case '9':
                        j = 0;
                        init(&n);
                        ins(&n,currchar,j);
                        j++;
                        t.type = OPERATOR;
                        t.data.op = expr[i-1];
                        currstate = NUM;
                        i++;
                        return t;
                        break;
                    case '+':case '-':case '*':case '/':case'%':case '(':case ')':
                        t.type = OPERATOR;
                        t.data.op = expr[i-1];
                        currstate = OP;
                        i++;
                        return t;
                        break;
                    case ' ':
                        t.type = OPERATOR;
                        t.data.op = expr[i-1];
                        currstate = SPC;
                        i++;
                        return t;
                        break;
                    case '\0':
                        t.type = OPERATOR;
                        t.data.op = expr[i-1];
                        currstate = STOP;
                        return t;
                        break;
                    default:
                        t.type = OPERATOR;
                        t.data.op = expr[i-1];
                        currstate = ERR;
                        return t;
                        break;
                }
                break;
            case SPC:
                switch(currchar){
                    case '0':case '1':case '2':case '3':case '4':
                    case '5':case '6':case '7':case '8':case '9':
                        j = 0;
                        init(&n);
                        ins(&n,currchar,j);
                        j++;
                        currstate = NUM;
                        i++;
                        break;
                    case '+':case '-':case '*':case '/':case'%':case '(':case ')':
                        currstate = OP;
                        i++;
                        break;
                    case ' ':
                        currstate=SPC;
                        i++;
                        break;
                    case '\0':
                        currstate = STOP;
                        break;
                    default:
                        currstate = ERR;
                        break;
                }
                break;
            case STOP:
                t.type = END;
                return t;
                break;
            case ERR:
                t.type = ERROR;
                return t;
                break;
        }
    }
}
int prec(char op){
    if(op == '*' || op == '/' || op == '%'){
        return 3;
    }
    else if(op == '+' || op == '-'){
        return 2;
    }
    return -1;
}
list oper(list *l1,list *l2,char op){
    if(op == '+'){
        if(l1->n[0] == '-' && l2->n[0] != '-'){
            del(l1,0);
            return sub(l2,l1,'+');
        }
        else if(l2->n[0] == '-' && l1->n[0] != '-'){
            del(l2,0);
            return sub(l1,l2,'+');
        }
        else if(l1->n[0] == '-' && l2->n[0] == '-'){
            del(l1,0);
            del(l2,0);
            return add(l1,l2,'-');
        }
        return add(l1,l2,'+');
    }
    else if(op == '-'){
        if(l1->n[0] == '-' && l2->n[0] != '-'){
            del(l1,0);
            return add(l2,l1,'-');
        }
        else if(l2->n[0] == '-' && l1->n[0] != '-'){
            del(l2,0);
            return add(l1,l2,'+');
        }
        else if(l1->n[0] == '-' && l2->n[0] == '-'){
            del(l1,0);
            del(l2,0);
            return sub(l2,l1,'+');
        }
        return sub(l1,l2,'+');
    }
    else if(op == '*'){
        if(l1->n[0] == '-' && l2->n[0] != '-'){
            del(l1,0);
            return mul(l2,l1,'-');
        }
        else if(l2->n[0] == '-' && l1->n[0] != '-'){
            del(l2,0);
            return mul(l1,l2,'-');
        }
        else if(l1->n[0] == '-' && l2->n[0] == '-'){
            del(l1,0);
            del(l2,0);
            return mul(l2,l1,'+');
        }
        return mul(l1,l2,'+');
    }
    else if(op == '/'){
        if(l1->n[0] == '-' && l2->n[0] != '-'){
            del(l1,0);
            return divi(l1,l2,'-');
        }
        else if(l2->n[0] == '-' && l1->n[0] != '-'){
            del(l2,0);
            return divi(l1,l2,'-');
        }
        else if(l1->n[0] == '-' && l2->n[0] == '-'){
            del(l1,0);
            del(l2,0);
            return divi(l1,l2,'+');
        }
        return divi(l1,l2,'+');
    }
    else if(op == '%'){
        if(l2->n[0] == '-'){
            del(l2,0);
        }
        if(l1->n[0] == '-'){
            del(l1,0);
            return mod(l1,l2,'-');
        }
        return mod(l1,l2,'%');
    }
}
list bc(char *expr){
    list x,y,z;
    stack s;
    cstack cs;
    char op;
    int n = 0;
    char prevop;
    int pres =0;
    sinit(&s);
    cinit(&cs);
    cpush(&cs,'(');
    strcat(expr,")");
    init(&x);
    init(&y);
    init(&z);
    token t;
    while(1){
        t = gettoken(expr);
        if(t.type == OPERAND){
            if(n == 1){
                ins(&t.data.num,'-',0);
                n = 0;
            }
            push(&s,&t.data.num);
        }
        else if(t.type == OPERATOR){
            if(s.top == pres || s.top == 0){
                if(s.top == 0){
                    if(t.data.op == '-'){
                        n=1;
                    }
                }
                else{

                    if(t.data.op == '-' && prevop != '-' && prevop != ')'){
                        n = 1;
                    }
                }
            }
            if(t.data.op == ')'){
                while(ctop(&cs) != '('){
                    if(!isempty(&s)){
                        x =pop(&s);
                    }
                    else{
                        init(&x);
                        return x;
                    }
                    if(!isempty(&s)){
                        y =pop(&s);
                    }
                    else{
                        init(&x);
                        return x;
                    }
                    if(!cisempty(&cs)){
                        op =cpop(&cs);
                    }
                    else{
                        init(&x);
                        return x;
                    }
                    switch (op){
                        case '+':
                            z=oper(&y,&x,'+');
                            break;
                        case '-':
                            z=oper(&y,&x,'-');
                            break;
                        case '*':
                            z=oper(&y,&x,'*');
                            break;
                        case '/':
                            z=strtn("0");
                            if(cmp(&x,&z) == 0){
                                init(&x);
                                return x;
                            }
                            z=oper(&y,&x,'/');
                            break;
                        case '%':
                            z=strtn("0");
                            if(cmp(&x,&z) == 0){
                                init(&x);
                                return x;
                            }
                            z=oper(&y,&x,'%');
                            break;
                        default:
                            init(&z);
                            return z;
                            break;
                    }
                    push(&s,&z);
                }
                if(n == 1){
                    z= pop(&s);
                    ins(&z,'-',0);
                    push(&s,&z); 
                    n = 0;  
                }
                op = cpop(&cs);
            }
            else if(prec(ctop(&cs)) >= prec(t.data.op) && t.data.op != '(' && n != 1){
                while(prec(ctop(&cs)) >= prec(t.data.op)){
                    if(!isempty(&s)){
                        x =pop(&s);
                    }
                    else{
                        init(&x);
                        return x;
                    }
                    if(!isempty(&s)){
                        y =pop(&s);
                    }
                    else{
                        init(&x);
                        return x;
                    }
                    if(!cisempty(&cs)){
                        op =cpop(&cs);
                    }
                    else{
                        init(&x);
                        return x;
                    }
                    switch (op){
                        case '+':
                            z=oper(&y,&x,'+');
                            break;
                        case '-':
                            z=oper(&y,&x,'-');
                            break;
                        case '*':
                            z=oper(&y,&x,'*');
                            break;
                        case '/':
                            z=strtn("0");
                            if(cmp(&x,&z) == 0){
                                init(&x);
                                return x;
                            }
                            z=oper(&y,&x,'/');
                            break;
                        case '%':
                            z=strtn("0");
                            if(cmp(&x,&z) == 0){
                                init(&x);
                                return x;
                            }
                            z=oper(&y,&x,'%');
                            break;
                        default:
                            init(&z);
                            return z;
                            break;
                    }
                    push(&s,&z);
                }
                cpush(&cs,t.data.op);
            }
            else if(n !=1){
                cpush(&cs,t.data.op);
            }
            prevop = t.data.op;
            pres= s.top;
        }
        else if(t.type == ERROR){
            init(&x);
            return x;
        }
        else{
            break;
        }
    }
    if(cisempty(&cs)){
        if(!isempty(&s)){
            x = pop(&s);
            if(isempty(&s)){
                return x;
            }
        }
    }
    init(&x);
    return x;

}
char *readline(){
    char ch, *s = malloc(sizeof(char));
    long long int i = 0;
    while(1){
        scanf("%c", &ch);
        if(ch == '\n'){
            s[i] = '\0';
            break;
        }
        s[i++] = ch;
        s = realloc(s, (i+1)*sizeof(char));
    }
    return s;
}
int main(){
    while(1){
        char *s=readline();
        if(strlen(s) ==0){
            printf("%s",s);
            break;
        }
        token t;
        list x =bc(s);
        if(x.co == 0){
            printf("Incorrect expression\n");
        }
        else{
            print(x);
        }
    }
    return 0;
}