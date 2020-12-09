#include "A_star.h"

bool operator<(const A_star::state & x, const A_star::state & y){
    return x.f>y.f;
}

void A_star::set(const QString & input1, const QString & input2){
    for(int i=0;i<9;i++){
        ini.s[i]=int(input1[i].toLatin1()-'0');
        goal.s[i]=int(input2[i].toLatin1()-'0');
        if(!ini.s[i]) ini.pos=i;
        if(!goal.s[i]) goal.pos=i;
    }
}

int A_star::calc_manhattan(const state & cur,const state & goal){
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

bool A_star::is_solvable(const state & ini, const state & goal){
    int n1=0,n2=0; // Inverse number
    for(int i=0;i<9;i++){
        for(int j=i+1;j<9;j++){
            if(ini.s[i]>ini.s[j] && ini.s[j]!=0) n1++;
            if(goal.s[i]>goal.s[j] && goal.s[j]!=0) n2++;
        }
    }
    if((n1&1)!=(n2&1)) return 0; // Same parity => Solvable
    return 1; // Different parity => Insolvable
}

bool A_star::A_star_calc(){
    bitmap vis(362880);
    ini.steps=0;
    ini.h=calc_manhattan(ini,goal);
    ini.f=ini.steps+ini.h;
    ini.fa=-1;
    q.push(ini);
    while(!q.empty()){
        state cur=q.top();
        v.push_back(cur);
        v_end++;
        q.pop();
        if(!cur.h){ // Find!
            A_star_steps=cur.steps;
            //print(v_end);
            return true;
        }
        nodes++;
        for(int i=0;i<4;i++){ // try 4 direction
            if(~d[cur.pos][i]){ // If current move is accepted
                // Construct the new state after move
                state next;
                memcpy(next.s, cur.s, sizeof(cur.s));
                next.pos=d[cur.pos][i];
                std::swap(next.s[cur.pos],next.s[next.pos]);
                next.steps=cur.steps+1;
                next.h=calc_manhattan(next,goal);
                next.f=next.steps+next.h;
                next.fa=v_end;
                int code=encode(next.s);
                if(!vis.is_visited(code)){
                    vis.visit(code);
                    q.push(next);
                }
            }
        }
    }
    return false;
}

void A_star::calc(){
    start=clock();
    if(is_solvable(ini,goal)) A_star_calc();
    end=clock();
}

void A_star::print_in(const int & idx, QString & ans){
    if(~idx){
        print_in(v[idx].fa, ans);
        QString tmp;
        for(int i=0;i<9;i++){
            tmp.sprintf("%d ",v[idx].s[i]);
            ans+=tmp;
        }
        ans+='\n';
    }
}

QString A_star::print(){
    QString ans;
    if(v.empty()){
        ans.append("No Solution.");
        return ans;
    }
    print_in(v_end, ans);
    return ans;
}
