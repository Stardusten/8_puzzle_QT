#ifndef A_STAR_H
#define A_STAR_H

#include<queue>
#include<algorithm>
#include<QString>
#include"bitmap.h"

extern const int d[9][4];
extern const int manhattan[9][9];
extern int encode(int *);

class A_star{
private:
    // 数据成员
    struct state{
        int s[9]; // 0 represents Space
        int pos; // Position of space
        int steps; // Steps to reach current state
        int h; // Heuristic function
        int f;
        int fa;
    }ini,goal;

    clock_t start,end;

    int A_star_steps, nodes=0;

    std::priority_queue<state> q;

    std::vector<state> v;
    int v_end=-1;

    // 工具函数
    friend bool operator<(const A_star::state &, const A_star::state &);
    int calc_manhattan(const state &,const state &);
    bool is_solvable(const state &, const state &);
    bool A_star_calc();
    void print_in(const int &, QString &);

public:
    void set(const QString &, const QString &);
    QString steps(){ return q.empty()?QString(""):QString::number(A_star_steps); }
    QString time_used(){ return q.empty()?QString(""):QString::number((end-start)/1e3); }
    QString traveled_nodes(){ return q.empty()?QString(""):QString::number(nodes); }
    void calc();
    QString print();
};

#endif // A_STAR_H
