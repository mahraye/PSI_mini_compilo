%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #define SIZE 1024

    int yydebug=1;
    extern int yylex();
    int yywrap(void) {};
    int yyerror(char *s) {
        printf("%s\n",s);
    }

    struct symbol{
      char * name;        // nom de la variable
      int constant;       // boolean
      float value;        // valeut des var tmp
    };

    FILE * inputFile;
    int index_pile = 0;
    struct symbol table[SIZE];

    int COD_ADD = 1;
    int COD_SUB = 3;
    int COD_MUL = 2;
    int COD_DIV = 4;
    int COD_COP = 5;
    int COD_AFC = 6;

    void malloc_easy(void){
        for(int j=0;j<SIZE;j++){
            struct symbol ini_symbol =
                {"null/!!/20caracteres", 1, 1.0};
            table[j]=ini_symbol;
        }
    }

    int find_symbol(char * name){
      int i = 0;
      int index = -1;
      int found = 0;
      while(i<SIZE & !found){
        if (strcmp(name, table[i].name)==0){
          index = i;
          found = 1;
        } else {
          i++;
        }
      }
      printf("Name trouvé : %s index : %d\n\n", name, index);
      return index;
    }

    void add_symbol(char*name, int constant){
      int index = find_symbol("null/!!/20caracteres");
      table[index].name = name;
      table[index].constant = constant;
      for(int i=0; i<10;i++){
        printf("valeur table: %d %s/%d\n", i, table[i].name, table[i].constant);
      }
    }

    void empile_tmp(float result){
      table[SIZE-index_pile-1].value = result;
      index_pile++;
    }

    void write_instruction1(int ope_cod, int num){
      // jmp; pri
      fprintf(inputFile,"%d %d\n", ope_cod, num);
    }
    void write_instruction2(int ope_cod, int ret, int op1){
      // cop; afc; jmf
      fprintf(inputFile,"%d %d %d\n", ope_cod, ret,op1);
    }
    void write_instruction3(int ope_cod, int ret, int op1, int op2){
      // add; sub; mul; div; inf; sup; equ
    	fprintf(inputFile,"%d %d %d %d\n", ope_cod, ret,op1, op2);
    }

%}
%union        {int nb; char var [32];};
%token        tMAIN tFIN tCONST tVOID tINT tCHAR tFLOAT tPRINTF tEQ tADD tSUB tMUL tDIV tVIRG tPTvirg tPARo tPARf tACCo tACCf tNULL tREAL tNOM
%token        <nb>  tNB
%token        <var> tVAR
%type         <nb> EXPRESSION OPE DECLARATION VAL INSTRUCT VARS LVARS

%left tADD tSUB
%left tDIV tMUL
%right tPOW
%start S;

%%
S: MAIN;
MAIN: TYPE tMAIN tPARo VARS tPARf tACCo BODY tACCf { fprintf(inputFile,"main"); } ;
TYPE:
        tINT    { fprintf(inputFile,"INT\n"); }
    |   tFLOAT  { fprintf(inputFile,"FLOAT\n"); }
    |   tCHAR   { fprintf(inputFile,"CHAR\n"); }
    |   tVOID   { fprintf(inputFile,"VOID\n"); }
    ;
BODY: DECLARATION INSTRUCT ;
VARS:

    |   tVAR LVARS
    ;
LVARS:

    |   tVIRG tVAR LVARS
    ;

DECLARATION:
        TYPE tVAR tPTvirg DECLARATION {add_symbol($2,0);}
    |   tCONST TYPE tVAR tPTvirg DECLARATION {add_symbol($3,1);}
    |   TYPE tVAR tEQ VAL tPTvirg DECLARATION {add_symbol($2,0); write_instruction2(COD_AFC,find_symbol($2),$4);}
    |
    ;

INSTRUCT:
        tVAR tEQ EXPRESSION tPTvirg INSTRUCT          {printf("ICI\n") ;int index =find_symbol($1); write_instruction2(COD_AFC,index,$3); }
    |   tPRINTF tPARo EXPRESSION tPARf tPTvirg INSTRUCT
    |
    ;

EXPRESSION:
        tNB                        { $$ = 0; }
    |   tREAL                      { $$ = 0; }
    |   tVAR                       { $$ = find_symbol($1);}
    |   tPARo EXPRESSION tPARf     { $$ = $2; }
    |   EXPRESSION OPE EXPRESSION  { write_instruction3($2, $$, $1, $3); }
    |   tSUB EXPRESSION %prec tMUL { write_instruction3(0, $$,  0, $2); }
    ;

OPE:
        tADD  {$$=COD_ADD;}
    |   tSUB  {$$=COD_SUB;}
    |   tMUL  {$$=COD_MUL;}
    |   tDIV  {$$=COD_DIV;}

VAL:
        tNB
    |   tREAL
    |   tVAR
    ;

%%
int main(){
    printf("Début\n");
    malloc_easy();
    inputFile= fopen( "asm.txt", "w" );
    if ( inputFile == NULL ) {
        printf( "Cannot open file %s\n", "ASM" );
        exit( 0 );
    }
    yyparse();
    fclose( inputFile );
    printf("FIN\n");
    return 0;
}

C:
int a = 5;
int b = 6;
int c = 7;
a = (b-c)*(a+b);


NOUS:
[a,,,,,]
AFC @a 5 -> 6 0 5
[a,b,,,,]
AFC @b 6 -> 6 1 6
[a,b,c,,,]
AFC @c 7 -> 6 2 7
[a,b,c,,,tmp1]
SUB @tmp1 @b @c -> 3 6 1 2
[a,b,c,,tmp2,tmp1]
ADD @tmp2 @a @b -> 1 5 0 1
[a,b,c,@tmp3,tmp2,tmp1]
MUL @tmp3 @tmp1 @tmp2 -> 2 4 6 5
COP @tmp3 @a -> 5 4 0
[a,b,c,,,]
