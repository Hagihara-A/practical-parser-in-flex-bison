#include <stdlib.h>

Partial* partial0(){
    Partial* p = malloc(sizeof(Partial));
    p->tag = Partial0;
    return p;
}

Partial* partial1(const Nr nr1){
    Partial* p = malloc(sizeof(Partial));
    p->tag = Partial1;
    p->val.partial1.nr1 = nr1;
    return p;
}

Partial* partial2(const Nr nr1, const Nr nr2){
    Partial* p = malloc(sizeof(Partial));
    p->tag = Partial2;
    p->val.partial2.nr1 = nr1;
    p->val.partial2.nr2 = nr2;
    return p;
}

Partial* partial3(const Nr nr1,const Nr nr2,const Nr nr3, const Quolifier* quolifier){
    Partial* p = malloc(sizeof(Partial));
    p->tag = Partial3;
    p->val.partial3.nr1 = nr1;
    p->val.partial3.nr2 = nr2;
    p->val.partial3.nr3 = nr3;
    p->val.partial3.quolifier = quolifier;
    return p;
}

