#ifndef BFS_H
#define BFS_H

#include<ctime>
#include<string>
#include<algorithm>
#include<QString>
#include<QEventLoop>
#include<QTimer>
#include<vector>
#include"bitmap.h"

extern const int d[9][4];
extern int encode(int *);

class BFS{
private:
    // 数据成员
    struct state{
        int s[9];
        int pos;
        int fa;
        int steps;
    }ini,goal;
    int nodes=0;
    clock_t start,end;
    std::vector<state> q;
    int front,rear;

    // 工具函数
    bool is_solvable(const state &, const state &);
    bool bfs();
    void print_in(const int & idx, QString & str);

public:
    void set(const QString &, const QString &);
    void calc();
    QString steps(){ return q.empty()?QString(""):QString::number(q[front].steps); }
    QString time_used(){ return q.empty()?QString(""):QString::number((end-start)/1e3); }
    QString traveled_nodes(){ return q.empty()?QString(""):QString::number(nodes); }
    QString print();
};

#endif
