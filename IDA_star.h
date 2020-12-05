#ifndef IDA_STAR
#define IDA_STAR

#include<stack>
#include<string>
#include<algorithm>
#include<QString>
#include<QDebug>

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

class IDA_star{
private:
    // 数据成员
    struct state{
        int s[9]; // 0 represents Space
        int pos; // Position of space
    }ini,goal;
    int max_f;
    std::stack<state> path;

    // 工具函数
    int calc_manhattan(const state &,const state &);
    bool is_solvable(const state &, const state &);
    bool IDA_star_in(state &, const int &, const int &, const int &);

public:
    IDA_star(){}
    IDA_star(const QString &, const QString &);
    void calc();
    QString print_path();
};

int IDA_star::calc_manhattan(const state & cur,const state & goal){
    int dis=0;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(cur.s[i]==goal.s[j]){
                dis+=manhattan[i][j];
            }
        }
    }
    return dis;
}

bool IDA_star::is_solvable(const state & ini, const state & goal){
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

bool IDA_star::IDA_star_in(state & cur, const int & steps, const int & h, const int & prepos){
    if(!memcmp(cur.s,goal.s,sizeof(goal.s))){
        // print steps
        path.push(cur);
        return true;
    }
    if(steps+h>max_f) return false;
    for(int i=0;i<4;i++){
        if(d[cur.pos][i]==prepos) continue;
        if(~d[cur.pos][i]){
            state next;
            memcpy(next.s,cur.s,sizeof(cur.s));
            next.pos=d[cur.pos][i];
            std::swap(next.s[cur.pos],next.s[next.pos]);
            if(IDA_star_in(next, steps+1, calc_manhattan(next,goal), cur.pos)){
                path.push(cur);
                return true;
            }
        }
    }
    return false;
}

IDA_star::IDA_star(const QString & input1, const QString & input2){
    for(int i=0;i<9;i++){
        ini.s[i]=int(input1[i].toLatin1()-'0');
        goal.s[i]=int(input2[i].toLatin1()-'0');
        if(!ini.s[i]) ini.pos=i;
        if(!goal.s[i]) goal.pos=i;
    }
    return;
}

void IDA_star::calc(){
    max_f=calc_manhattan(ini,goal);
    if(is_solvable(ini,goal)){
        while(!IDA_star_in(ini,0,max_f,-1)) max_f++;
    }
}

QString IDA_star::print_path(){
    QString ans("No solution");
    if(path.empty()) return ans;
    ans.clear();
    while(!path.empty()){
        state & tmp=path.top();
        for(int i=0;i<9;i++){
            ans.append(tmp.s[i]);
            ans.append(' ');
        }
        ans.append('\n');
        path.pop();
    }
    return ans;
}

#endif
