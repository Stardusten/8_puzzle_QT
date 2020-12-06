#ifndef ALGO_BASE_H
#define ALGO_BASE_H

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

const int fact[10]={1,1,2,6,24,120,720,5040,40320,362880};

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

inline int ceil(double x){
    return x>(int)x?(int)x+1:(int)x;
}

class bitmap{
private:
    int* buf;
public:
    bitmap(): buf(nullptr){}
    bitmap(const int & siz){
        buf=new int[ceil(siz/32)]();
    }
    ~bitmap(){
        delete [] buf;
        buf=nullptr;
    }
    void visit(int);
    bool is_visited(int);
    void undo_visit(int);
};

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

#endif // ALGO_BASE_H
