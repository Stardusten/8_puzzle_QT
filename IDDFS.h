#ifndef IDDFS_H
#define IDDFS_H

#include<stack>
#include<ctime>
#include<string>
#include<algorithm>
#include<QString>
#include<QDebug>
#include"algo_base.h"

class IDDFS{
private:
    // 数据成员
    struct state{
        int s[9]; // 0 represents Space
        int pos; // Position of space
    }ini,goal;
    int max_f=1,nodes=0,need_steps;
    std::stack<state> path;
    clock_t start,end;

    // 工具函数
    bool is_solvable(const state &, const state &);
    bool IDDFS_in(state &, const int &, const int &);

public:
    void set(const QString &, const QString &);
    void calc();
    QString steps(){ return path.empty()?QString(""):QString::number(need_steps); }
    QString time_used(){ return path.empty()?QString(""):QString::number(end-start); }
    QString traveled_nodes(){ return path.empty()?QString(""):QString::number(nodes); }
    QString print();
};

bool IDDFS::is_solvable(const state & ini, const state & goal){
    int n1=0,n2=0;
    for(int i=0;i<9;i++){
        for(int j=i+1;j<9;j++){
            if(ini.s[i]>ini.s[j] && ini.s[j]!=0) n1++;
            if(goal.s[i]>goal.s[j] && goal.s[j]!=0) n2++;
        }
    }
    if((n1&1)!=(n2&1)) return 0;
    return 1;
}

bool IDDFS::IDDFS_in(state & cur, const int & steps, const int & prepos){
    if(!memcmp(cur.s,goal.s,sizeof(goal.s))){
        need_steps=steps;
        path.push(cur);
        return true;
    }
    if(steps>max_f) return false;
    nodes++;
    for(int i=0;i<4;i++){
        if(d[cur.pos][i]==prepos) continue;
        if(~d[cur.pos][i]){
            state next;
            memcpy(next.s,cur.s,sizeof(cur.s));
            next.pos=d[cur.pos][i];
            std::swap(next.s[cur.pos],next.s[next.pos]);
            if(IDDFS_in(next, steps+1, cur.pos)){
                path.push(cur);
                return true;
            }
        }
    }
    return false;
}

void IDDFS::set(const QString & input1, const QString & input2){
    for(int i=0;i<9;i++){
        ini.s[i]=int(input1[i].toLatin1()-'0');
        goal.s[i]=int(input2[i].toLatin1()-'0');
        if(!ini.s[i]) ini.pos=i;
        if(!goal.s[i]) goal.pos=i;
    }
}

void IDDFS::calc(){
    if(is_solvable(ini,goal)){
        start=clock();
        while(!IDDFS_in(ini,0,-1)) max_f++;
        end=clock();
    }
}

QString IDDFS::print(){
    QString ans;
    if(path.empty()){
        ans.append("No Solution.");
        return ans;
    }
    while(!path.empty()){
        state & cur = path.top();
        QString tmp;
        for(int i=0;i<9;i++){
            tmp.sprintf("%d ",cur.s[i]);
            ans+=tmp;
        }
        ans+='\n';
        path.pop();
    }
    return ans;
}

#endif // IDDFS_H
