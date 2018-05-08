
#ifndef _PARSE_H_
#define _PARSE_H_

#include <iostream>
#include <string>
#include <math.h>
#include "ReversePolish.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

void Parse(std::string line);

extern void (* Func)();
extern void (* LastFunc)();

extern std::vector<Elem> ElemStack;
extern std::string String;
extern long Index;
extern char Curr;
extern char Next;

extern double Acc;
extern int DecPlace;


#endif
