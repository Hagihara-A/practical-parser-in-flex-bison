typedef struct {
} Primitive;

typedef enum {
  SimplePrimitive,
  Simplepartial,
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

typedef struct {
  Partial *partial1;
  Partial *partial2;
} Hyphen;

typedef Simple[] Simples;

typedef enum { RangeHyphen, RangeSimples, RangeVoid } RangeTag;
typedef union {
  Hyphen hyphen;
  Simples simples;
} range_val;
typedef struct {
  RangeTag tag;
  RangeVal val;
} range;

typedef Range[] RangeSet;
