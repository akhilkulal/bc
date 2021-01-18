#include<stdio.h>
typedef struct list
{
    char *n;
    int co;
    int ms;
}list;
void init(list *);
void ins(list *, char, int);
void del(list *,int );
list add(list *, list *, char);
list sub(list *, list *, char);
list mul(list *, list *, char);
list mod(list *, list *, char);
int cmp(list *, list *);
list strtn(char *);
list divi(list *, list *, char );
list power(list *, list *, char);
void print(list);
void normalize(list *);
void copyl(list *l1, list *l2);