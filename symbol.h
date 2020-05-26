#ifndef SYMBOL_H
#define SYMBOL_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int idSymbol=0;
int idSymbolTemp = 255;

struct symbol {
  int constant;
  int init;
  int depth;
  char id [256];
};

struct symbol symbolTable [256];

int push_symbol(char *, int , int);
void pop_symbol();
int push_tmp_symbol(char *, int, int);
void clear_tmp_symbol();
int get_address(char *, int);
void set_initialized(char *, int);
int is_initialized(char *, int);
void clearUseless(int);
int get_indice_temp();
int get_indice();

#endif