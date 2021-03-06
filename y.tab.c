/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "source.y" /* yacc.c:339  */

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    //#include "tabSymbol.h"
    #define SIZE 1024
    #define DEBUT "<debut>"


    int yydebug=1;
    extern int yylex();
    int yywrap(void) {};
    int yyerror(char *s) {
        printf("%s\n",s);
    }


    typedef struct Cellule Cellule;
    struct Cellule {
        char* nom;
        int constante;
        Cellule* suivante;
    };

    typedef struct Liste Liste;
    struct Liste {
        Cellule* premiere;
    };



    Liste* tabSymbol;
    Liste* bufferSymbol; //pour les declarations a virgule
    FILE * inputFile;
    int index_pile = 0;


    int COD_ADD = 1;
    int COD_SUB = 3;
    int COD_MUL = 2;
    int COD_DIV = 4;
    int COD_COP = 5;
    int COD_AFC = 6;
    int COD_JMP = 7;
    int COD_JMF = 8;
    int COD_INF = 9;
    int COD_SUP = 10;
    int COD_EQU = 11;
    int COD_PRI = 12;

    // Fonctions utiles

    void write_instruction1(int ope_cod, int num){
      // jmp; pri
      if (ope_cod<10){
        fprintf(inputFile,"%d %d\n", ope_cod, num);
      } else {
        fprintf(inputFile,"%c %d\n", 55+ope_cod, num);
      }

    }
    void write_instruction2(int ope_cod, int ret, int op1){
      // cop; afc; jmf
      if (ope_cod<10){
        fprintf(inputFile,"%d %d %d\n", ope_cod, ret, op1);
      } else {
        fprintf(inputFile,"%c %d %d\n", 55+ope_cod, ret, op1);
      }
    }
    void write_instruction3(int ope_cod, int ret, int op1, int op2){
      // add; sub; mul; div; inf; sup; equ
      if (ope_cod<10){
    	  fprintf(inputFile,"%d %d %d %d\n", ope_cod, ret, op1, op2);
      } else {
        fprintf(inputFile,"%c %d %d %d\n", 55+ope_cod, ret, op1, op2);
      }
    }


    Liste* initialise() {
        tabSymbol = malloc(sizeof(Liste));
        Cellule* cellule = malloc(sizeof(Cellule));
        if (tabSymbol == NULL || cellule == NULL)  {
            exit(EXIT_FAILURE);
        }
        cellule->nom = malloc(strlen(DEBUT)+1);
        strncpy(cellule->nom, DEBUT, strlen(DEBUT));
        cellule->constante = 0;
        cellule->suivante = NULL;
        tabSymbol->premiere = cellule;
        return tabSymbol;
    }


    void supprime(Liste* tabSymbol) {
        if (tabSymbol == NULL) {
            exit(EXIT_FAILURE);
        }
        while (tabSymbol->premiere != NULL) {
            Cellule* bientotPlusLa = tabSymbol->premiere;
            tabSymbol->premiere = tabSymbol->premiere->suivante;
            free(bientotPlusLa);
        }
    }


    int ajoute(char* nvNom, int constante) {
        Cellule* nouvelle = malloc(sizeof(*nouvelle));
        if (tabSymbol == NULL || nouvelle == NULL) {
            exit(EXIT_FAILURE);
        }
        nouvelle->nom = malloc(strlen(nvNom)+1);
        strncpy(nouvelle->nom, nvNom, strlen(nvNom));
        nouvelle->constante = constante;

        int compteur = 0;
        Cellule* actuelle = tabSymbol->premiere;
        //printf("compteur ");
        int found = 0;
        while (!found && actuelle->suivante != NULL) {
        	if (strcmp(nvNom, actuelle->nom)==0) {
        		found = 1;
        		break;
        	}
        	compteur++;
            actuelle = actuelle->suivante;
        }
        //printf(" ; found %d\n",found);
        // on rajoute que s'il y a besoin
        if(!found && strcmp(nvNom, actuelle->nom)!=0) {
    	    actuelle->suivante = nouvelle;
    	    nouvelle->suivante = NULL;
    	    compteur++;  //on rajoute un element en plus
        }
        //affiche();
        return compteur;
    }


    int trouve(char* nvNom) {
        affiche();
        int compteur = 0;
        int arg = -1;
        Cellule* actuelle = tabSymbol->premiere;
        while (actuelle != NULL && arg < 0) {
        	if (strcmp(nvNom, actuelle->nom)==0)
        		arg = compteur;
        	compteur++;
          actuelle = actuelle->suivante;
        }
        return arg;
    }

    int constante(char* nvNom) {
        int compteur = 0;
        int arg = -1;
        Cellule* actuelle = tabSymbol->premiere;
        while (actuelle != NULL && arg < 0) {
          if (strcmp(nvNom, actuelle->nom)==0)
            arg = actuelle->constante;
          compteur++;
          actuelle = actuelle->suivante;
        }
        return arg;
    }


    void affiche() {
        if (tabSymbol == NULL) {
            exit(EXIT_FAILURE);
        }
        Cellule* actuelle = tabSymbol->premiere;
        while (actuelle != NULL) {
            fprintf(inputFile,"(%s, %d) -> ", actuelle->nom, actuelle->constante);
            actuelle = actuelle->suivante;
        }
        fprintf(inputFile,"NULL\n");
    }

    void afficheBuffer() {
        if (bufferSymbol == NULL) {
            exit(EXIT_FAILURE);
        }
        Cellule* actuelle = bufferSymbol->premiere;
        while (actuelle != NULL) {
            fprintf(inputFile,"(%s, %d) -> ", actuelle->nom, actuelle->constante);
            actuelle = actuelle->suivante;
        }
        fprintf(inputFile,"NULL\n");
    }

    Liste* initialiseBuffer() {
        bufferSymbol = malloc(sizeof(Liste));
        Cellule* cellule = malloc(sizeof(Cellule));
        if (bufferSymbol == NULL || cellule == NULL)  {
            exit(EXIT_FAILURE);
        }
        cellule->nom = malloc(strlen(DEBUT)+1);
        strncpy(cellule->nom, DEBUT, strlen(DEBUT));
        cellule->constante = 0;
        cellule->suivante = NULL;
        bufferSymbol->premiere = cellule;
        return bufferSymbol;
    }

    void ecritBuffer(int val) {
        afficheBuffer();
        if (bufferSymbol == NULL) {
            exit(EXIT_FAILURE);
        }
        while (bufferSymbol->premiere != NULL) {
            Cellule* bientotPlusLa = bufferSymbol->premiere;
            if (strcmp(bientotPlusLa->nom,DEBUT)!=0)
                fprintf(inputFile,"AFC %d %d\n", trouve(bientotPlusLa->nom), val);
            bufferSymbol->premiere = bufferSymbol->premiere->suivante;
            free(bientotPlusLa);
        }
    }

    void stocke(char* nvNom, int constante) {
        afficheBuffer();
        Cellule* nouvelle = malloc(sizeof(*nouvelle));
        if (bufferSymbol == NULL || nouvelle == NULL) {
            exit(EXIT_FAILURE);
        }
        nouvelle->nom = malloc(strlen(nvNom)+1);
        strncpy(nouvelle->nom, nvNom, strlen(nvNom));
        nouvelle->constante = constante;
        Cellule* actuelle = bufferSymbol->premiere;
        int found = 0;
        while (!found && actuelle->suivante != NULL) {
        	if (strcmp(nvNom, actuelle->nom)==0) {
        		found = 1;
        		break;
        	}
            actuelle = actuelle->suivante;
        }
        if(!found && strcmp(nvNom, actuelle->nom)!=0) {
    	    actuelle->suivante = nouvelle;
    	    nouvelle->suivante = NULL;
        }
    }



    int empile_tmp(){
      index_pile++;
      return SIZE-index_pile; //pile virtualisee par un simple index de pile (parce qui compte c'est
    }                         //l'adresse pas le contenu de la pile)

    int depile_tmp(){
      index_pile--;
      return SIZE-index_pile;
    }




#line 325 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    tMAIN = 258,
    tFIN = 259,
    tCONST = 260,
    tVOID = 261,
    tINT = 262,
    tCHAR = 263,
    tFLOAT = 264,
    tPRINTF = 265,
    tEQ = 266,
    tADD = 267,
    tSUB = 268,
    tMUL = 269,
    tDIV = 270,
    tVIRG = 271,
    tPTvirg = 272,
    tPARo = 273,
    tPARf = 274,
    tACCo = 275,
    tACCf = 276,
    tNULL = 277,
    tREAL = 278,
    tEXPO = 279,
    tNOM = 280,
    tVIRGULE = 281,
    tNB = 282,
    tVAR = 283,
    tPOW = 284
  };
#endif
/* Tokens.  */
#define tMAIN 258
#define tFIN 259
#define tCONST 260
#define tVOID 261
#define tINT 262
#define tCHAR 263
#define tFLOAT 264
#define tPRINTF 265
#define tEQ 266
#define tADD 267
#define tSUB 268
#define tMUL 269
#define tDIV 270
#define tVIRG 271
#define tPTvirg 272
#define tPARo 273
#define tPARf 274
#define tACCo 275
#define tACCf 276
#define tNULL 277
#define tREAL 278
#define tEXPO 279
#define tNOM 280
#define tVIRGULE 281
#define tNB 282
#define tVAR 283
#define tPOW 284

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 259 "source.y" /* yacc.c:355  */
int nb; char var [32];

#line 426 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 443 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   80

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  41
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  81

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   284

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   271,   271,   272,   274,   275,   276,   277,   279,   280,
     282,   284,   286,   289,   291,   292,   293,   294,   295,   299,
     300,   304,   305,   331,   333,   334,   337,   340,   341,   342,
     343,   344,   345,   346,   350,   351,   352,   353,   357,   358,
     359,   360
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "tMAIN", "tFIN", "tCONST", "tVOID",
  "tINT", "tCHAR", "tFLOAT", "tPRINTF", "tEQ", "tADD", "tSUB", "tMUL",
  "tDIV", "tVIRG", "tPTvirg", "tPARo", "tPARf", "tACCo", "tACCf", "tNULL",
  "tREAL", "tEXPO", "tNOM", "tVIRGULE", "tNB", "tVAR", "tPOW", "$accept",
  "S", "MAIN", "TYPE", "BODY", "LVAR", "LVARS", "DECLARATION", "VARSUIV",
  "CONSTVARSUIV", "INSTRUCT", "PRINT", "EXPRESSION", "OPE", "VAL", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284
};
# endif

#define YYPACT_NINF -47

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-47)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      55,   -47,   -47,   -47,   -47,    12,   -47,    10,   -47,    -4,
     -12,     5,     3,     6,   -47,    21,     5,    51,   -47,    55,
       7,    16,    -3,    20,    -6,   -47,    34,    42,   -47,    -3,
      -9,    27,    51,    41,    43,    15,   -47,    51,    44,   -47,
     -47,   -47,   -47,    56,   -47,    -8,    51,    57,    15,    15,
     -47,   -47,   -47,   -47,    32,   -47,    -7,    51,    51,   -47,
      41,   -47,    58,   -47,    17,   -47,   -47,   -47,   -47,    -3,
      15,   -47,    44,   -47,   -47,   -47,   -47,   -47,   -47,    53,
     -47
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,     4,     6,     5,     0,     2,     0,     1,     0,
       9,    11,     0,     0,    10,     0,    11,    13,    12,     0,
       0,     0,    23,     0,     0,     3,     0,     0,     8,    23,
       0,     0,    13,     0,     0,     0,    25,    13,     0,    39,
      40,    38,    41,     0,    14,     0,    13,     0,     0,     0,
      29,    28,    27,    30,     0,    15,     0,    13,    13,    20,
       0,    17,     0,    33,     0,    34,    35,    36,    37,    23,
       0,    22,     0,    18,    16,    19,    26,    31,    24,    32,
      21
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -47,   -47,   -47,     4,   -47,   -47,    54,   -31,    14,     8,
     -29,   -47,   -46,   -47,   -47
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,    20,    21,    12,    14,    22,    46,    57,
      28,    29,    54,    70,    43
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      36,    44,    63,    64,     7,    31,    55,    26,    37,    59,
      71,    32,     8,     9,    10,    61,    11,    38,    60,    72,
      33,    13,    15,    23,    79,    27,    73,    74,    48,    65,
      66,    67,    68,    49,    16,    24,    77,    25,    50,    51,
      78,    17,    52,    53,    65,    66,    67,    68,    30,    69,
      39,    40,    34,    35,    41,    42,    19,     1,     2,     3,
       4,     1,     2,     3,     4,    65,    66,    67,    68,    45,
      18,    47,    56,    58,    75,    76,    62,     0,     0,     0,
      80
};

static const yytype_int8 yycheck[] =
{
      29,    32,    48,    49,     0,    11,    37,    10,    17,    17,
      17,    17,     0,     3,    18,    46,    28,    26,    26,    26,
      26,    16,    19,    19,    70,    28,    57,    58,    13,    12,
      13,    14,    15,    18,    28,    28,    19,    21,    23,    24,
      69,    20,    27,    28,    12,    13,    14,    15,    28,    17,
      23,    24,    18,    11,    27,    28,     5,     6,     7,     8,
       9,     6,     7,     8,     9,    12,    13,    14,    15,    28,
      16,    28,    28,    17,    60,    17,    19,    -1,    -1,    -1,
      72
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,     8,     9,    31,    32,    33,     0,     3,
      18,    28,    35,    16,    36,    19,    28,    20,    36,     5,
      33,    34,    37,    33,    28,    21,    10,    28,    40,    41,
      28,    11,    17,    26,    18,    11,    40,    17,    26,    23,
      24,    27,    28,    44,    37,    28,    38,    28,    13,    18,
      23,    24,    27,    28,    42,    37,    28,    39,    17,    17,
      26,    37,    19,    42,    42,    12,    13,    14,    15,    17,
      43,    17,    26,    37,    37,    38,    17,    19,    40,    42,
      39
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    30,    31,    32,    33,    33,    33,    33,    34,    35,
      35,    36,    36,    37,    37,    37,    37,    37,    37,    38,
      38,    39,    39,    40,    40,    40,    41,    42,    42,    42,
      42,    42,    42,    42,    43,    43,    43,    43,    44,    44,
      44,    44
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     8,     1,     1,     1,     1,     2,     0,
       2,     0,     3,     0,     4,     5,     6,     5,     6,     3,
       2,     3,     2,     0,     5,     2,     5,     1,     1,     1,
       1,     3,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 272 "source.y" /* yacc.c:1646  */
    { fprintf(inputFile,"main"); }
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 291 "source.y" /* yacc.c:1646  */
    { ajoute((yyvsp[-2].var),0); }
#line 1577 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 292 "source.y" /* yacc.c:1646  */
    { ajoute((yyvsp[-2].var),1); }
#line 1583 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 293 "source.y" /* yacc.c:1646  */
    { ajoute((yyvsp[-4].var),0); write_instruction2(COD_AFC,trouve((yyvsp[-4].var)),(yyvsp[-2].nb)); }
#line 1589 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 294 "source.y" /* yacc.c:1646  */
    { ajoute((yyvsp[-3].var),0); }
#line 1595 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 295 "source.y" /* yacc.c:1646  */
    { ajoute((yyvsp[-3].var),1); }
#line 1601 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 299 "source.y" /* yacc.c:1646  */
    { ajoute((yyvsp[-2].var),0); }
#line 1607 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 300 "source.y" /* yacc.c:1646  */
    { ajoute((yyvsp[-1].var),0); }
#line 1613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 304 "source.y" /* yacc.c:1646  */
    { ajoute((yyvsp[-2].var),1); }
#line 1619 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 305 "source.y" /* yacc.c:1646  */
    { ajoute((yyvsp[-1].var),1); }
#line 1625 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 333 "source.y" /* yacc.c:1646  */
    { if(!constante((yyvsp[-4].var))){write_instruction2(COD_COP,trouve((yyvsp[-4].var)),(yyvsp[-2].nb)); depile_tmp();}  }
#line 1631 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 337 "source.y" /* yacc.c:1646  */
    { write_instruction1(COD_PRI,trouve((yyvsp[-2].var))); }
#line 1637 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 340 "source.y" /* yacc.c:1646  */
    { int addr_tmp = empile_tmp(); (yyval.nb) = addr_tmp; write_instruction2(COD_AFC,addr_tmp,(yyvsp[0].nb)); }
#line 1643 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 341 "source.y" /* yacc.c:1646  */
    { int addr_tmp = empile_tmp(); (yyval.nb) = addr_tmp; write_instruction2(COD_AFC,addr_tmp,(yyvsp[0].nb)); }
#line 1649 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 342 "source.y" /* yacc.c:1646  */
    { int addr_tmp = empile_tmp(); (yyval.nb) = addr_tmp; write_instruction2(COD_AFC,addr_tmp, 1); }
#line 1655 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 343 "source.y" /* yacc.c:1646  */
    { int addr_tmp = empile_tmp(); (yyval.nb) = addr_tmp; write_instruction2(COD_COP,addr_tmp,trouve((yyvsp[0].var))); }
#line 1661 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 344 "source.y" /* yacc.c:1646  */
    { (yyval.nb) = (yyvsp[-1].nb); }
#line 1667 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 345 "source.y" /* yacc.c:1646  */
    { (yyval.nb) = (yyvsp[-2].nb); write_instruction3((yyvsp[-1].nb), (yyvsp[-2].nb), (yyvsp[-2].nb), (yyvsp[0].nb)); depile_tmp(); }
#line 1673 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 346 "source.y" /* yacc.c:1646  */
    { write_instruction3(COD_SUB, (yyvsp[0].nb), 0, (yyvsp[0].nb)); }
#line 1679 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 350 "source.y" /* yacc.c:1646  */
    { (yyval.nb)=COD_ADD; }
#line 1685 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 351 "source.y" /* yacc.c:1646  */
    { (yyval.nb)=COD_SUB; }
#line 1691 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 352 "source.y" /* yacc.c:1646  */
    { (yyval.nb)=COD_MUL; }
#line 1697 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 353 "source.y" /* yacc.c:1646  */
    { (yyval.nb)=COD_DIV; }
#line 1703 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1707 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 363 "source.y" /* yacc.c:1906  */

int main(){
    printf("Début\n");
    Liste* tabSymbol = initialise();
    Liste* bufferSymbol = initialiseBuffer();

    inputFile = fopen( "asm.txt", "w" );
    if ( inputFile == NULL ) {
        printf( "Cannot open file %s\n", "ASM" );
        exit( 0 );
    }

    /*printf("ajoute titi: %d\n",ajoute( "titi"));
    printf("trouve titi: %d\n",trouve( "titi"));
    affiche(tabSymbol);
    printf("ajoute totodu31: %d\n",ajoute( "totodu31"));
    printf("trouve titi: %d\n",trouve( "titi"));
    printf("trouve totodu31: %d\n",trouve( "totodu31"));
    affiche(tabSymbol);
    printf("ajoute totodu31400: %d\n",ajoute( "totodu31400"));
    printf("trouve totodu31400: %d\n",trouve( "totodu31400"));
    affiche(tabSymbol);
    printf("ajoute totodu31: %d\n",ajoute( "totodu31"));
    printf("trouve totodu31: %d\n",trouve( "totodu31"));
    affiche(tabSymbol);
    printf("ajoute totodu31400: %d\n",ajoute( "totodu31400"));
    printf("trouve totodu31400: %d\n",trouve( "totodu31400"));
    affiche(tabSymbol);
    supprime(tabSymbol);*/

    yyparse();
    fclose(inputFile);

    printf("\nmemoire libérée\n");
    printf("FIN\n");
    return 0;
}
/*
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




C:
int a = 5;
a = a + 8;


NOUS:
[a,,,,,]
AFC @a 5 -> 6 0 5
[a,,,,,8]
index_pile = 1
ADD @tmp @a @8 -> 1 5 0 6
[a,,,,tmp,8]
COP @tmp @a -> 5 5 0
[a,,,,,]



8 + b + c

tNB tPLUS tVAR tPLUS tVAR

|      |
\_____/

Sachant EXPRESSION -> tNB {actionNB}
Alors, nous executons actionNB
Hypothèse : pas de modif. de la pile
*/
