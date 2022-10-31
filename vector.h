

#include"rational.h"
#include<stddef.h>
#include<stdbool.h>


struct Vector {
        Rational** list;
        size_t listlen;
};
typedef struct Vector Vector;


Vector* new_Vector( Rational** list, size_t listlen );

Vector* add_vector( Vector* v1, Vector* v2 );

Vector* mult_vector( Vector* v, Rational* r );

Vector* div_vector( Vector* v, Rational* r );

Rational* dot( Vector* v1, Vector* v2 );

void set_elem_vector( Vector* v, Rational* r, size_t index );

Rational* get_elem_vector( Vector* v, size_t index );

bool linearly_independent( Vector** vs, size_t vslen );

void free_vector( Vector* v );
