#ifndef BITMAP_H
#define BITMAP_H

extern int fact[10];

class bitmap{
private:
    int* buf;
    int ceil(double x){
        return x>(int)x?(int)x+1:(int)x;
    }
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

#endif // BITMAP_H
