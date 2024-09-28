#ifndef AST_H
#define AST_H

#include <stddef.h>

typedef int Nr;

typedef enum { PartId, PartNr } PartTag;
typedef union {
  Nr partNr;
  char *partId;
} PartVal;
typedef struct {
  PartTag tag;
  PartVal val;
} Part;
void print_part(const Part *part, int depth);
Part *partId(const char *id, size_t len);
Part *partNr(const Nr nr);

typedef struct Parts {
  Part *part;
  struct Parts *next;
} Parts;
Parts *parts_singleton(const Part *part);
Parts *parts_append(Parts *head, const Part *part);
void print_parts(const Parts *parts, int depth);

typedef Parts Pre;

typedef Parts Build;

typedef struct {
  Pre *pre;
  Build *build;
} Qualifier;
Qualifier *qualifier(const Pre *pre, const Build *build);

typedef enum { Partial0, Partial1, Partial2, Partial3 } PartialTag;
typedef struct {
} Partial0Val;
typedef struct {
  Nr nr1;
} Partial1Val;
typedef struct {
  Nr nr1;
  Nr nr2;
} Partial2Val;
typedef struct {
  Nr nr1;
  Nr nr2;
  Nr nr3;
  Qualifier *qualifier;
} Partial3Val;
typedef union {
  Partial0Val partial0;
  Partial1Val partial1;
  Partial2Val partial2;
  Partial3Val partial3;
} PartialVal;
typedef struct {
  PartialTag tag;
  PartialVal val;
} Partial;
Partial *partial0();
Partial *partial1(const Nr nr1);
Partial *partial2(const Nr nr1, const Nr nr2);
Partial *partial3(const Nr nr1, const Nr nr2, const Nr nr3,
                  const Qualifier *qualifier);

typedef Partial Caret;

typedef Partial Tilde;

typedef enum { CompLt, CompGt, CompGte, CompLte, CompEq } Compare;

typedef struct {
  Compare compare;
  Partial *partial;
} Primitive;
Primitive *primitive(const Compare compare, const Partial *partial);

typedef enum {
  SimplePrimitive,
  SimplePartial,
  SimpleTilde,
  SimpleCaret
} SimpleTag;
typedef union {
  Primitive *primitive;
  Partial *partial;
  Tilde *tilde;
  Caret *caret;
} SimpleVal;
typedef struct {
  SimpleTag tag;
  SimpleVal val;
} Simple;
Simple *simple_primitive(const Primitive *primitive);
Simple *simple_partial(const Partial *partial);
Simple *simple_tilde(const Tilde *tilde);
Simple *simple_caret(const Caret *caret);

typedef struct {
  Partial *partial1;
  Partial *partial2;
} Hyphen;
Hyphen *hyphen(const Partial *partial1, const Partial *partial2);

typedef struct Simples {
  Simple *simple;
  struct Simples *next;
} Simples;
Simples *simples_singleton(const Simple *simple);
Simples *simples_append(Simples *head, const Simple *simple);

typedef enum { RangeHyphen, RangeSimples, RangeVoid } RangeTag;
typedef union {
  Hyphen *rangeHyphen;
  Simples *rangeSimples;
} RangeVal;
typedef struct {
  RangeTag tag;
  RangeVal val;
} Range;
Range *range_hyphen(const Hyphen *hyphen);
Range *range_simples(const Simples *simples);
Range *range_void();

typedef struct RangeSet {
  Range *range;
  struct RangeSet *next;
} RangeSet;
RangeSet *range_set_singleton(const Range *range);
RangeSet *range_set_append(RangeSet *head, const Range *range);
void print_range_set(const RangeSet *range_set, const int depth);

#endif