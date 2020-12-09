#include "base.h"

const int fact[10]={1,1,2,6,24,120,720,5040,40320,362880};

const int d[9][4]={
    {-1,3,-1,1},
    {-1,4,0,2},
    {-1,5,1,-1},
    {0,6,-1,4},
    {1,7,3,5},
    {2,8,4,-1},
    {3,-1,-1,7},
    {4,-1,6,8},
    {5,-1,7,-1}
};

const int manhattan[9][9]={
    {0,1,2,1,2,3,2,3,4},
    {1,0,1,2,1,2,3,2,3},
    {2,1,0,3,2,1,4,3,2},
    {1,2,3,0,1,2,1,2,3},
    {2,1,2,1,0,1,2,1,2},
    {3,2,1,2,1,0,3,2,1},
    {2,3,4,1,2,3,0,1,2},
    {3,2,3,2,1,2,1,0,1},
    {4,3,2,3,2,1,2,1,0}
};

int encode(int *p){
    int code=0;
    for(int i=0;i<9;i++){
        int cnt=0;
        for(int j=i+1;j<9;j++)
            if(p[j]<p[i])  cnt++;
        code+=fact[8-i]*cnt;
    }
    return code;
}