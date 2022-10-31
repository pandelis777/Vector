

#include"vector.h"


#include<stdlib.h>
#include<assert.h>


Vector* new_Vector( Rational** list, size_t listlen ) {
        Vector* v = (Vector*) malloc( 1 *sizeof(Vector) );

        v->list = list;
        v->listlen = listlen;

        return v;
}

Vector* add_vector( Vector* v1, Vector* v2 ) {
        assert( v1->listlen == v2->listlen );
        Vector* v1v2 = new_Vector( (Rational*) malloc( v1->listlen *sizeof(Vector) ), v1->listlen );

        for (size_t i = 0; i < v1v2->listlen; i++) {
                v1v2->list[i] = add_rational( v1->list[i], v2->list[i] );
        }

        return v1v2;
}

Vector* mult_vector( Vector* v, Rational* r ) {
        Vector* rv = new_Vector( (Rational*) malloc( v1->listlen *sizeof(Vector) ), v1->listlen );

        for (size_t i = 0; i < rv->listlen; i++) {
                rv->list[i] = mult_rational( r, v->list[i] );
        }

        return rv;
}

Vector* div_vector( Vector* v, Rational* r ) {
        Vector* rv = new_Vector( (Rational*) malloc( v1->listlen *sizeof(Vector) ), v1->listlen );

        for (size_t i = 0; i < rv->listlen; i++) {
                rv->list[i] = div_rational( r, v->list[i] );
        }

        return rv;
}

Rational* dot( Vector* v1, Vector* v2 ) {
        assert( v1->listlen == v2->listlen );
        Rational* r, tmp, tmp2;

        r = mult_rational( v1->list[0], v2->list[0] );

        for (size_t i = 1; i < v1->listlen; i++) {
                tmp = r;
                tmp2 = mult_rational( v1->list[i], v2->list[i] );

                r = add_rational( tmp, tmp2 );

                free_rational( tmp2 );
                free_rational( tmp );
        }

        return r;
}

void set_elem_vector( Vector* v, Rational* r, size_t index ) {
        assert( index < v->listlen );
        v->list[index] = r;
}

Rational* get_elem_vector( Vector* v, size_t index ) {
        assert( index < v->listlen );
        return v->list[index];
}

bool linearly_independent( Vector** vs, size_t vslen ) {
        Rational* r_0 = new_Rational(0,1);
        Rational* r_n1 = new_Rational( -1, 1 );
        Rational* r_tmp;
        size_t minlen = (vslen < listlen) ? vslen : listlen;
        Vector** vs_tmp = (Vector**) malloc( minlen *sizeof(Vector*) );
        for (size_t i = 0; i < count; i++) {
                vs_tmp[i] = add_vector( vs[i], r_0 ); // copy_vector
        }
        Vector* tmp;

        for (size_t i = 0; i < minlen; i++) {
                // divide by vs[i][i]
                for (size_t j = i; j < minlen; j++) {
                        if ( compare_rational( get_elem_vector( vs_tmp[j], i ), r_0 ) == 0 ) {
                                tmp = vs_tmp[i];
                                vs_tmp[j] = vs_tmp[i];
                                vs_tmp[i] = tmp;
                        }
                }
                if ( compare_rational( get_elem_vector( vs_tmp[i], i ), r_0 ) == 0 ) {
                        free_rational( r_0 );
                        free_rational( r_n1 );
                        for (size_t j = 0; j < minlen; j++) {
                                free_vector( vs_tmp[j] );
                        }
                        return false;
                }
                vs_tmp[i] = div_vector( vs_tmp[i], get_elem_vector(vs_tmp[i], i) );


                // set zeroes
                for (size_t j = i+1; j < minlen; j++) {
                        assert( compare_rational( get_elem_vector(vs_tmp[j], i), r_0 ) != 0 );
                        r_tmp = mult_rational( get_elem_vector(vs_tmp[j], i), r_n1 );
                        tmp = mult_vector( vs_tmp[i], r_tmp );
                        tmp2 = add_vector( vs_tmp[j], tmp );
                        free_rational( r_tmp );
                        free_vector( tmp );
                        free_vector( vs_tmp[j] );
                        vs_tmp[j] = tmp2;
                }
        }


        free_rational( r_0 );
        free_rational( r_n1 );
        for (size_t j = 0; j < minlen; j++) {
                free_vector( vs_tmp[j] );
        }
        return true;
}

void free_vector( Vector* v ) {
        if (v->list != NULL) {
                for (size_t i = 0; i < v->listlen; i++) {
                        free_rational( v->list[i] );
                }
        }
        free( v->list );
        free( v );
}
