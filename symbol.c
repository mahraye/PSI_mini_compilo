#include "symbol.h"

int push_symbol(char *id, int cons, int depth)
{
    printf("symbol : %s à l'addresse : %d\n",id,idSymbol);
    struct symbol * new_symbol = &(symbolTable[idSymbol]);
    strcpy(new_symbol->id, id);

    new_symbol->constant = cons;
    new_symbol->init = 0;
    new_symbol->depth = depth;

    idSymbol++;
    return idSymbol-1;
}

int push_tmp_symbol(char * id, int cons, int depth)
{
    struct symbol * new_symbol = &(symbolTable[idSymbolTemp]);
    strcpy(new_symbol->id, id);
    new_symbol->constant = cons;
    new_symbol->init = 0;
    new_symbol->depth = depth;
    printf("ajout  symbole temporaire à l'@ : %d \n",idSymbolTemp);
    idSymbolTemp--;

    return idSymbolTemp+1;
}

void pop_symbol() {
    idSymbol--;
}

void clear_tmp_symbol(){
    idSymbolTemp = 255;
}

int get_address(char * id, int depth)
{
    for(int i=0 ; i < idSymbol ; i++)
    {
        struct symbol *current_symbol = &(symbolTable[i]);
        if(current_symbol->depth == depth){
            if(!strcmp(current_symbol->id, id)){
                return i;
            } 
        }
    }
    exit(-2);  
}

int is_initialized(char * id, int depth)
{
    int addr = get_address(id, depth);
    return symbolTable[addr].init;
}

void set_initialized(char * id, int depth)
{
    int addr = get_address(id, depth);
    symbolTable[addr].init = 1;
}

void clearUseless(int depth)
{
    struct symbol * last = &(symbolTable[idSymbol]);
    int a = 0;
    while( a == 0 ) {
        if( last->depth > depth) {
            pop_symbol();
            last = &(symbolTable[idSymbol]);
        }
        else {
            a++;
        }
    }
}

int get_indice_temp(){
    return idSymbolTemp;
}

int get_indice(){
    return idSymbolTemp;
}