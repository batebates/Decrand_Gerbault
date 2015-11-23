#define N 4
#define M 4
#define t_max N*M
#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED
/**
\struct t_coord
\brief contient les coordonnees x y
*/
typedef struct{int x;int y;}t_coord;
/**
\struct t_valeurmot
\brief un mot avec son score
*/
typedef struct{char mot[t_max] ;int score;}t_valeurmot;
typedef enum {rien, dl, tl, dw, tw} t_bonus;
/**
\struct t_lettre
\brief un mot avec son score
*/
typedef struct {char c; int pts; t_bonus bonus;} t_lettre;

#endif
