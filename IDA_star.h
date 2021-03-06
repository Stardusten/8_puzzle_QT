#ifndef IDA_STAR
#define IDA_STAR

#include<stack>
#include<ctime>
#include<string>
#include<algorithm>
#include<QString>
#include<QDebug>

extern const int d[9][4];
extern const int manhattan[9][9];

class IDA_star{
private:
    // 数据成员
    struct state{
        int s[9]; // 0 represents Space
        int pos; // Position of space
    }ini,goal;
    int max_f,nodes=0,need_steps;
    std::stack<state> path;
    clock_t start,end;

    // 工具函数
    int calc_manhattan(const state &,const state &);
    bool is_solvable(const state &, const state &);
    bool IDA_star_in(state &, const int &, const int &, const int &);

public:
    void set(const QString &, const QString &);
    void calc();
    QString steps(){ return path.empty()?QString(""):QString::number(need_steps); }
    QString time_used(){ return path.empty()?QString(""):QString::number((end-start)/1e3); }
    QString traveled_nodes(){ return path.empty()?QString(""):QString::number(nodes); }
    QString print();
};

#endif
