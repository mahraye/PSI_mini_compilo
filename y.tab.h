/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 259 "source.y" /* yacc.c:1909  */
int nb; char var [32];

#line 115 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
