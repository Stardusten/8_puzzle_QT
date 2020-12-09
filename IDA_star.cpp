#include "IDA_star.h"

int IDA_star::calc_manhattan(const state & cur,const state & goal){
    int dis=0;
    for(int i=0;i<9;i++){
        if(!cur.s[i]) continue;
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
        need_steps=steps;
        path.push(cur);
        return true;
    }
    if(steps+h>max_f) return false;
    nodes++;
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

void IDA_star::set(const QString & input1, const QString & input2){
    for(int i=0;i<9;i++){
        ini.s[i]=int(input1[i].toLatin1()-'0');
        goal.s[i]=int(input2[i].toLatin1()-'0');
        if(!ini.s[i]) ini.pos=i;
        if(!goal.s[i]) goal.pos=i;
    }
}

void IDA_star::calc(){
    max_f=calc_manhattan(ini,goal);
    start=clock();
    if(is_solvable(ini,goal)){
        while(!IDA_star_in(ini,0,max_f,-1)) max_f++;
    }
    end=clock();
}

QString IDA_star::print(){
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
