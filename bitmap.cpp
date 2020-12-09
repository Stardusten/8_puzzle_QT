#include "bitmap.h"

void bitmap::visit(int n){
    /*
    n is in the j-th bit of the i-th int
    +----------+----------+----------+----   ---+----------+----------
    |  1st int |  2nd int |  3rd int |          | i-th int |
    +----------+----------+----------+----   ---+----------+----------
                                                       ↑
                                                    j-th bit
    */
    int i=n/32;
    int j=n&31; // Equivalent to j=n%32;
    buf[i]|=(1<<j);
    /*
       To change the j-th bit from 0 to 1,
       we need to construct a number whose j-th bit is 1 and the rest bits are 0 (1<<j),
       then OR the original number with the constructed number.
       e.g      1100 0000
                0000 0010
            OR  1100 0010
    */
}

bool bitmap::is_visited(int n){
    int i=n/32;
    int j=n&31;
    return ((buf[i]&(1<<j))!=0);
    /*
       To check the j-th bit,
       we need to construct a number whose j-th is 1 and the rest bits are 0 (1<<j),
       then AND the original number with the constructed number.
       e.g      1100 0000			        1100 0000
                0000 0010			        0100 0000
           AND  0000 0000 (false)      AND  0100 0000 (true)
    */
}

void bitmap::undo_visit(int n){
    int i=n/32;
    int j=n&31;
    buf[i]|=~(1<<j);
}
