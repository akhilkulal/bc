#include"ll.h"
#include <stdio.h>
#include<stdlib.h>
void init(list *l){
    l->n = malloc(sizeof(char));
    l->ms =1;
    l->co = 0;
}
void ins(list *l, char num, int pos){
    for(int i=l->co; i > pos; i--){
        l->n[i] = l->n[i-1];
    }
    l->n[pos] = num;
    l->co++;
    if(l->co == l->ms){
        l->n = (char*)realloc(l->n,sizeof(char)*(++l->ms));
    }
}
void del(list *l, int pos){
    for(int i=pos; i<l->co-1; i++){
        l->n[i] = l->n[i+1];
    }
    l->co--;
}
void print(list l){
    for(int i=0; i<l.co; i++){
        printf("%c", l.n[i]);
    }
    printf("\n");
}
int cmp(list *a, list *b){
    list c;
    c = sub(a, b, '+');
    normalize(&c);
    if(c.n[0] == '-')
        return -1;
    for(int i = 0; i < c.co; i++){
        if(c.n[i] != '.'){
            if(c.n[i] != '0'){
                return 1;
            }
        }
    }
    return 0;
}
void copyl(list *l1, list *l2){
    for(int i = 0; i < l2->co; i++){
        ins(l1,l2->n[i],i);
    }
}
list add( list *a, list *b, char resm){
    int i=0, j=0, k, cy = 0;
    char ch;
    list c;
    init(&c);
    while(a->n[i] != '.' && i != a->co){
        i++;
    }
    while(b->n[j] != '.' && j != b->co){
        j++;
    }
    if (i == 0){
        ins(a, '0', 0);
        i = 1;
    }
    if (j == 0){
        ins(b, '0', 0);
        j = 1;
    }
    if(i == a->co-1 && a->n[i] == '.'){
        del(a, i);
        i = a->co;

    } 
    if(j == b->co-1 && b->n[j] == '.'){
        del(b, j);
        j = b->co;
    } 
    if(i != a->co && j!= b->co){
        i = a->co -i;
        j = b->co- j;
        if(i != j){
            if(i > j){
                for(k = 0; k < i-j; k++){
                    ins(b, '0', b->co);
                }
            }
            else{
                for(k = 0; k < j-i; k++){
                    ins(a, '0', a->co);
                }
            }
        }
    }
    else if(i != a->co && j == b->co){
        ins(b, '.', b->co);
        for(k = 1; k < a->co-i; k++){
            ins(b, '0', b->co);
        }
    }
    else if(i == a->co && j != b->co){
        ins(a, '.', a->co);
        for(k = 1; k < b->co-j; k++){
            ins(a, '0', a->co);
        }
    }
    i = a->co-1;
    j = b->co-1;
    while(i != -1 && j != -1){
        if(a->n[i] == '.'){
            ins(&c, '.', 0);
        }
        else{
            k = (a->n[i] - '0')+(b->n[j] - '0')+cy;
            cy = k / 10;
            k = k%10;
            ch= k+48;
            ins(&c, ch, 0);
        }
        i--;
        j--;
    }
    if(i != -1){
        while(i != -1){
            k = (a->n[i]-'0') + cy;
            cy = k /10;
            k = k %10;
            ch = k+48;
            ins(&c, ch, 0);
            i--;
        }
    }
    if(j != -1){
        while(j != -1){
            k = (b->n[j]-'0') + cy;
            cy = k /10;
            k = k %10;
            ch = k+48;
            ins(&c, ch, 0);
            j--;
        }
    }
    if(cy == 1){
        ins(&c, '1', 0);
    }
    if (resm == '-'){
        ins(&c, '-', 0);
    }
    return c;
}
list sub(list *a, list *b, char resm){
    int i=0, j=0, k, cy = 0;
    char ch;
    list c;
    init(&c);
    while(a->n[i] != '.' && i != a->co){
        i++;
    }
    while(b->n[j] != '.' && j != b->co){
        j++;
    }
    if (i == 0){
        ins(a, '0', 0);
        i = 1;
    }
    if (j == 0){
        ins(b, '0', 0);
        j = 1;
    }
    if(i == a->co-1 && a->n[i] == '.'){
        del(a, i);
        i = a->co;
    } 
    if(j == b->co-1 && b->n[j] == '.'){
        del(b, j);
        j = b->co;
    } 
    if(i != a->co && j!= b->co){
        i = a->co -i;
        j = b->co- j;
        if(i != j){
            if(i > j){
                for(k = 0; k < i-j; k++){
                    ins(b, '0', b->co);
                }
            }
            else{
                for(k = 0; k < j-i; k++){
                    ins(a, '0', a->co);
                }
            }
        }
    }
    else if(i != a->co && j == b->co){
        ins(b, '.', b->co);
        for(k = 1; k < a->co-i; k++){
            ins(b, '0', b->co);
        }
    }
    else if(i == a->co && j != b->co){
        ins(a, '.', a->co);
        for(k = 1; k < b->co-j; k++){
            ins(a, '0', a->co);
        }
    }
    i = a->co-1;
    j = b->co-1;
    cy = 0;
    while(i != -1 && j!=-1){
        if(a->n[i] == '.'){
            ins(&c, '.', 0);
        }
        else{
            k = (a->n[i] - '0') - (b->n[j]-'0')-cy;
            if(k < 0){
                k = k + 10;
                cy = 1;
            }
            else{
                cy = 0;
            }
            ch = k+'0';
            ins(&c, ch, 0); 
        }
        i--;
        j--;
    }
    if(i != -1){
        while(i != -1){
            k = (a->n[i]-'0')-cy;
            if(k < 0){
                k += 10;
                cy = 1;
            }
            else{
                cy = 0;
            }
            ch = k+48;
            ins(&c, ch, 0);
            i--;
        }
    }
    else if(j != -1){
        while(j != -1){
            k = -(b->n[j]-'0')-cy;
            if(k < 0){
                k += 10;
                cy = 1;
            }
            else{
                cy = 0;
            }
            ch = k+48;
            ins(&c, ch, 0);
            j--;
        }
    }
    if(cy == 1){
        i = c.co - 1;
        cy = 0;
        while(i != -1){
            if(c.n[i] != '.'){
                k = -(c.n[i]-'0') - cy;
                if(k < 0){
                    k += 10;
                    cy = 1;
                }
                else{
                    cy = 0;
                }
                c.n[i] = k+48;
            }
            i--;
        }
        cy = 1;
    }
    if((resm == '+' && cy == 1) || (resm == '-' && cy == 0)){
        ins(&c, '-', 0);
    }
    return c;
}
list mul(list *a, list *b, char resm){
    int ad = a->co-1, bd = b->co-1, i, j, k, cy = 0;
    char ch;
    list c,d;
    init(&c);
    ins(&c, '0', 0);
    while(ad != -1 && a->n[ad] != '.'){
        ad--;
    }
    while(bd != -1 && b->n[bd] != '.'){
        bd--;
    }
    if(ad != -1){
        del(a, ad);
    }
    if(bd != -1){
        del(b, bd);
    }
    j = b->co-1;
    while(j != -1){
        i = a->co-1;
        init(&d);
        for(k = 1; k < b->co-j; k++)
            ins(&d, '0', 0);
        while(i != -1){
            k = (a->n[i]-'0')*(b->n[j] - '0') + cy;
            cy = k/10;
            k = k %10;
            ch = k+48;
            ins(&d, ch, 0);
            i--;
        }
        c = add(&c, &d, '+');
        j--;
    }
    if(ad != -1){
        ad = a->co-ad;
    }
    else{
        ad = 0;
    }
    if(bd != -1){
        bd = b->co-bd;
    }
    else{
        bd = 0;
    }
    if(ad != 0 || bd != 0){
        ins(&c, '.', c.co - (ad+bd));
    }
    if(resm == '-')
        ins(&c, '-', 0);
    return c;
}
void normalize(list *a){
    int i = 0, j;
    if(a->n[0] == '-'){
        i = 1;
    }
    while(a->n[i] == '0' && a->co != i){
        del(a, i);
    }
    if(a->co == i){
        ins(a, '0', i);
        return;
    }
    for(i = i; a->n[i] != '.' && a->co != i; i++);
    if(i == a->co)
        return;
    else{
        j= a->co-1;
        while(a->n[j] == '0' && j != i){
            del(a,j);
            j= a->co-1;
        }
    }
    if(a->n[0] == '.' && a->co == 1){
        a->n[0] = '0';
    }
    else if(a->n[0] == '.'){
        ins(a, '0', 0);
    }
    if(a->n[a->co-1] == '.'){
        del(a, a->co-1);
    }
}
list strtn(char *s){
    list d;
    init(&d);
    for(int i= 0; s[i] != '\0'; i++){
        ins(&d, s[i], i);
    }
    return d;
}
list divi(list *a, list *b, char resm){
    normalize(a);
    normalize(b);
    int i = 0, j = 0, k = 0;
    list c, d, e;
    init(&c);
    init(&d);
    while (a->n[i] != '.' && i != a->co){
        i++;
    }
    while (b->n[j] != '.' && j != b->co){
        j++;
    }
    if(i != a->co){
        del(a, i);
    }
    if(j != b->co){
        del(b, j);
    }
    k = (b->co-j)-(a->co-i);
    for(i = k; i >0; i--){
        ins(a, '0', a->co);
    }
    i = 0;
    while(i != a->co){
        ins(&d, a->n[i], d.co);
        j = 0;
        init(&e);
        ins(&e, '0', 0);
        while(cmp(&d, &e) == 1){
            e = add(&e, b, '+');
            j++;
        }
        if(cmp(&d, &e) == -1){
            e = sub(&e, b, '+');
            j--;
        }
        d = sub(&d, &e, '+');
        ins(&c, (j+48), i);
        i++;
    }
    for(i = k; i < 0; i++){
        del(&c, c.co-1);
    }
    if(resm == '-')
        ins(&c, '-', 0);
    normalize(&c);
    return c;
}
list mod(list *a, list *b, char resm){
    int i=0, j=0, k;
    while(i != a->co && a->n[i] != '.'){
        i++;
    }
    while(j != b->co && b->n[j] != '.'){
        j++;
    }
    i = a->co-i-1;
    j = b->co-j-1;
    k = (i > j)?i:j;
    list d, c, e;
    init(&d);
    e = strtn("10");
    for(i = 0; i < j; i++){
        *a = mul(a, &e, '+');
        *b = mul(b, &e, '+');
    }
    normalize(a);
    normalize(b);
    i = 0;
    while(i != a->co && a->n[i] != '.'){
        ins(&d, a->n[i], d.co);
        init(&e);
        ins(&e, '0', 0);
        while(cmp(&d, &e) == 1){
            e = add(b,&e, '+');
        }
        if(cmp(&d, &e) == -1){
            e = sub(&e, b, '+');
        }
        d = sub(&d, &e, '+');
        normalize(&d);
        i++;
    }
    for(j = i+1; j < a->co; j++){
        ins(&d, a->n[j], d.co);
    }
    if(k < d.co){
        ins(&d, '.', d.co-k);
    }
    else{
        while(k > d.co){
            ins(&d, '0', 0);
        }
        ins(&d, '.', 0);
        ins(&d, '0', 0);
    }
    if(resm == '-')
        ins(&d, '-', 0);
    return d;
}
