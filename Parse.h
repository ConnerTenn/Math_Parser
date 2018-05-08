
#ifndef _PARSE_H_
#define _PARSE_H_

#include <iostream>
#include <string>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

void Start();
void End();
void Error();
void White();
void Num();
void Add();
void Sub();

void Parse(std::string line);

extern void (* Func)();
extern void (* LastFunc)();

extern std::string String;
extern u64 Index;
extern char Curr;
extern char Next;
extern int Acc;


#endif
