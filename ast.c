#include "ast.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_nr(const Nr nr, int depth) {
  for (int i = 0; i < depth; i++) {
    printf("  ");
  }
  printf("Nr: %d\n", nr);
}

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

void print_part(const Part* part, int depth) {
  for (int i = 0; i < depth; i++) {
    printf("  ");
  }
  printf("Part:\n");

  int d2 = depth + 1;
  for (int i = 0; i < d2; i++) {
    printf("  ");
  }
  switch (part->tag) {
    case PartNr:
      printf("PartNr\n");
      print_nr(part->val.partNr, d2);
      break;
    case PartId:
      printf("PartId\n");
      for (int i = 0; i < d2; i++) {
        printf("  ");
      }
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
Parts* parts_append(Parts* head, const Part* part) {
  Parts* sentinel = head;
  while (sentinel->next != NULL) {
    sentinel = sentinel->next;
  }
  sentinel->next = parts_singleton(part);
  return head;
}
void print_parts(const Parts* parts, int depth) {
  for (int i = 0; i < depth; i++) {
    printf("  ");
  }
  printf("Parts:\n");
  const Parts* sentinel = parts;
  while (sentinel != NULL) {
    print_part(sentinel->part, depth + 1);
    sentinel = sentinel->next;
  }
}

Qualifier* qualifier(const Pre* pre, const Build* build) {
  Qualifier* q = malloc(sizeof(Qualifier));
  q->pre = pre;
  q->build = build;
  return q;
}
void print_qualifier(const Qualifier* qualifier, const int depth) {
  for (int i = 0; i < depth; i++) {
    printf("  ");
  }
  printf("Qualifier:\n");
  print_parts(qualifier->pre, depth + 1);
  print_parts(qualifier->build, depth + 1);
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
void print_partial(const Partial* partial, const int depth) {
  for (int i = 0; i < depth; i++) {
    printf("  ");
  }
  switch (partial->tag) {
    case Partial0:
      printf("Partial0\n");
      break;
    case Partial1:
      printf("Partial1:\n");
      print_nr(partial->val.partial1.nr1, depth + 1);
      break;
    case Partial2:
      printf("Partial2:\n");
      print_nr(partial->val.partial2.nr1, depth + 1);
      print_nr(partial->val.partial2.nr2, depth + 1);
      break;
    case Partial3:
      printf("Partial3:\n");
      print_nr(partial->val.partial3.nr1, depth + 1);
      print_nr(partial->val.partial3.nr2, depth + 1);
      print_nr(partial->val.partial3.nr3, depth + 1);
      print_qualifier(partial->val.partial3.qualifier, depth + 1);
      break;
    default:
      printf("unknown partial\n");
      break;
  }
}

Primitive* primitive(const Compare compare, const Partial* partial) {
  Primitive* p = malloc(sizeof(Primitive));
  p->compare = compare;
  p->partial = partial;
  return p;
}
void print_primitive(const Primitive* primitive, const int depth) {
  for (int i = 0; i < depth; i++) {
    printf("  ");
  }
  printf("Primitive\n");

  int d2 = depth + 1;
  for (int i = 0; i < d2; i++) {
    printf("  ");
  }
  printf("Compare: ");
  switch (primitive->compare) {
    case CompLt:
      printf("CompLt\n");
      break;
    case CompGt:
      printf("CompGt\n");
      break;
    case CompGte:
      printf("CompGte\n");
      break;
    case CompLte:
      printf("CompLte\n");
      break;
    case CompEq:
      printf("CompEq\n");
      break;
    default:
      printf("unknown compare\n");
      break;
  }
  print_partial(primitive->partial, d2);
}

Simple* simple_primitive(const Primitive* primitive) {
  Simple* s = malloc(sizeof(Simple));
  s->tag = SimplePrimitive;
  s->val.primitive = primitive;
  return s;
}

Simple* simple_partial(const Partial* partial) {
  Simple* s = malloc(sizeof(Simple));
  s->tag = SimplePartial;
  s->val.partial = partial;
  return s;
}

Simple* simple_tilde(const Tilde* tilde) {
  Simple* s = malloc(sizeof(Simple));
  s->tag = SimpleTilde;
  s->val.tilde = tilde;
  return s;
}

Simple* simple_caret(const Caret* caret) {
  Simple* s = malloc(sizeof(Simple));
  s->tag = SimpleCaret;
  s->val.caret = caret;
  return s;
}
void print_simple(const Simple* simple, const int depth) {
  for (int i = 0; i < depth; i++) {
    printf("  ");
  }
  printf("Simple:\n");
  int d2 = depth + 1;
  for (int i = 0; i < d2; i++) {
    printf("  ");
  }
  switch (simple->tag) {
    case SimplePrimitive:
      printf("SimplePrimitive:\n");
      print_primitive(simple->val.primitive, d2 + 1);
      break;
    case SimplePartial:
      printf("SimplePartial:\n");
      print_partial(simple->val.partial, d2 + 1);
      break;
    case SimpleTilde:
      printf("SimpleTilde:\n");
      print_part(simple->val.tilde, d2 + 1);
      break;
    case SimpleCaret:
      printf("SimpleCaret:\n");
      print_part(simple->val.caret, d2 + 1);
      break;
    default:
      printf("unknown simple\n");
      break;
  }
}

Hyphen* hyphen(const Partial* l, const Partial* r) {
  Hyphen* h = malloc(sizeof(Hyphen));
  h->partial1 = l;
  h->partial2 = r;
  return h;
}
void print_hyphen(const Hyphen* hyphen, const int depth) {
  for (int i = 0; i < depth; i++) {
    printf("  ");
  }
  printf("Hyphen\n");
  print_partial(hyphen->partial1, depth + 1);
  print_partial(hyphen->partial2, depth + 1);
}

Simples* simples_singleton(const Simple* simple) {
  Simples* s = malloc(sizeof(Simples));
  s->simple = simple;
  s->next = NULL;
  return s;
}

Simples* simples_append(Simples* head, const Simple* simple) {
  Simples* sentinel = head;
  while (sentinel->next != NULL) {
    sentinel = sentinel->next;
  }
  sentinel->next = simples_singleton(simple);
  return head;
}
void print_simples(const Simples* simples, const int depth) {
  for (int i = 0; i < depth; i++) {
    printf("  ");
  }
  printf("Simples:\n");
  if (simples == NULL) {
    return;
  }
  const Simples* s = simples;
  while (s != NULL) {
    print_simple(s->simple, depth + 1);
    s = s->next;
  }
}

Range* range_hyphen(const Hyphen* hyphen) {
  Range* r = malloc(sizeof(Range));
  r->tag = RangeHyphen;
  r->val.rangeHyphen = hyphen;
  return r;
}

Range* range_simples(const Simples* simples) {
  Range* r = malloc(sizeof(Range));
  r->tag = RangeSimples;
  r->val.rangeSimples = simples;
  return r;
}
void print_range(const Range* range, const int depth) {
  for (int i = 0; i < depth; i++) {
    printf("  ");
  }
  printf("Range:\n");
  int d2 = depth + 1;

  for (int i = 0; i < d2; i++) {
    printf("  ");
  }
  switch (range->tag) {
    case RangeHyphen:
      printf("RangeHyphen:\n");
      print_partial(range->val.rangeHyphen->partial1, d2 + 1);
      print_partial(range->val.rangeHyphen->partial2, d2 + 1);
      break;
    case RangeSimples:
      printf("RangeSimples:\n");
      print_simples(range->val.rangeSimples, d2 + 1);
      break;
    case RangeVoid:
      printf("RangeVoid:\n");
      break;
    default:
      printf("unknown range\n");
      break;
  }
}

Range* range_void() {
  Range* r = malloc(sizeof(Range));
  r->tag = RangeVoid;
  return r;
}

RangeSet* range_set_singleton(const Range* range) {
  RangeSet* r = malloc(sizeof(RangeSet));
  r->range = range;
  r->next = NULL;
  return r;
}

RangeSet* range_set_append(RangeSet* head, const Range* range) {
  RangeSet* sentinel = head;
  while (sentinel->next != NULL) {
    sentinel = sentinel->next;
  }
  sentinel->next = range_set_singleton(range);
  return head;
}

void print_range_set(const RangeSet* range_set, const int depth) {
  for (int i = 0; i < depth; i++) {
    printf("  ");
  }
  printf("RangeSet:\n");

  if (range_set == NULL) {
    return;
  }

  const RangeSet* r = range_set;
  while (r != NULL) {
    print_range(r->range, depth + 1);
    r = r->next;
  }
}