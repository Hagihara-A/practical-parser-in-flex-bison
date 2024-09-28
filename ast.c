#include "ast.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Part* partNr(const Nr nr) {
  Part* p = malloc(sizeof(Part));
  p->tag = PartNr;
  p->val.partNr = nr;
  return p;
}

Part* partId(const char* id, size_t len) {
  Part* p = malloc(sizeof(Part));
  p->tag = PartId;
  p->val.partId = strndup(id, len);
  return p;
}

void print_part(const Part* part) {
  switch (part->tag) {
    case PartNr:
      printf("PartNr: ");
      printf("%d\n", part->val.partNr);
      break;
    case PartId:
      printf("PartId: ");
      printf("%s\n", part->val.partId);
      break;
    default:
      printf("unknown part\n");
      break;
  }
}

Parts* parts_singleton(const Part* part) {
  Parts* p = malloc(sizeof(Parts));
  p->part = part;
  p->next = NULL;
  return p;
}

Parts* parts_cons(Parts* parts, const Part* part) {
  Parts* last = NULL;
  while (1) {
    if (last->next == NULL) {
      break;
    }
  }
  last->next = part;
  return parts;
}

Qualifier* qualifier(const Pre* pre, const Build* build) {
  Qualifier* q = malloc(sizeof(Qualifier));
  q->pre = pre;
  q->build = build;
  return q;
}

Partial* partial0() {
  Partial* p = malloc(sizeof(Partial));
  p->tag = Partial0;
  return p;
}

Partial* partial1(const Nr nr1) {
  Partial* p = malloc(sizeof(Partial));
  p->tag = Partial1;
  p->val.partial1.nr1 = nr1;
  return p;
}

Partial* partial2(const Nr nr1, const Nr nr2) {
  Partial* p = malloc(sizeof(Partial));
  p->tag = Partial2;
  p->val.partial2.nr1 = nr1;
  p->val.partial2.nr2 = nr2;
  return p;
}

Partial* partial3(const Nr nr1, const Nr nr2, const Nr nr3,
                  const Qualifier* qualifier) {
  Partial* p = malloc(sizeof(Partial));
  p->tag = Partial3;
  p->val.partial3.nr1 = nr1;
  p->val.partial3.nr2 = nr2;
  p->val.partial3.nr3 = nr3;
  p->val.partial3.qualifier = qualifier;
  return p;
}