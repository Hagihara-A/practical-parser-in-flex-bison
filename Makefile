PROGRAM = a.out
BISON = parser.y
BISON_O = $(BISON:%.y=%.tab.c) $(BISON:%.y=%.tab.h)
FLEX = lex.l
FLEX_O = $(FLEX:%.l=%.yy.c) $(FLEX:%.l=%.yy.h)
OBJS = $(BISON:%.y=%.tab.o) $(FLEX:%.l=%.yy.o) main.o
SRCS = $(OBJS:%.o=%.c)
CC = gcc
LD = gcc
CFLAGS = -Wall

all: $(PROGRAM) 

.PHONY: clean
clean:
	rm -rf $(PROGRAM) $(OBJS) $(BISON_O) $(FLEX_O)

$(BISON_O) &: $(BISON)
	bison $(BISON)

$(FLEX_O) &: $(FLEX) $(BISON_O)
	flex $(FLEX)

$(PROGRAM): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

