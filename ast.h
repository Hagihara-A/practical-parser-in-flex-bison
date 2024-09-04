#ifndef AST_H
#define AST_H

typedef int Nr;

typedef enum { PartNr, PartId } PartTag;
typedef struct {
  Nr nr;
} PartNrVal;
typedef struct {
  char *id;
} PartIdVal;
typedef union {
  PartNrVal partNr;
  PartIdVal partId;
} PartVal;
typedef struct {
  PartTag tag;
  PartVal val;
} Part;

typedef struct Parts {
  Part part;
  struct Parts *next;
} Parts;

typedef Parts Pre;

typedef Parts Build;

typedef struct {
  Pre pre;
  Build build;
} Quolifier;

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
  Quolifier *quolifier;
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

typedef Partial Caret;

typedef Partial Tilde;

typedef enum { CompLt, CompGt, CompGte, CompLte, CompEq } Compare;

typedef struct {
  Compare compare;
  Partial partial;
} Primitive;

typedef enum {
  SimplePrimitive,
  Simplepartial,
  SimpleTilde,
  SimpleCaret
} SimpleTag;
typedef union {
  Primitive primitive;
  Partial partial;
  Tilde tilde;
  Caret caret;
} SimpleVal;
typedef struct {
  SimpleTag tag;
  SimpleVal val;
} Simple;

typedef struct {
  Partial *partial1;
  Partial *partial2;
} Hyphen;

typedef struct Simples{
  Simple simple;
  struct Simples *next;
} Simples;

typedef enum { RangeHyphen, RangeSimples, RangeVoid } RangeTag;
typedef struct {
  Hyphen hyphen;
} RangeHyphenVal;
typedef struct {
  Simples simples;
} RangeSimplesVal;
typedef union {
  RangeHyphenVal rangeHyphen;
  RangeSimplesVal rangeSimples;
} RangeVal;
typedef struct {
  RangeTag tag;
  RangeVal val;
} Range;

typedef struct RangeSet {
  Range range;
  struct RangeSet *next;
} RangeSet;

#endif