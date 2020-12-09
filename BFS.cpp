#include "BFS.h"

void BFS::set(const QString & input1, const QString & input2){
    for(int i=0;i<9;i++){
        ini.s[i]=int(input1[i].toLatin1()-'0');
        goal.s[i]=int(input2[i].toLatin1()-'0');
        if(!ini.s[i]) ini.pos=i;
        if(!goal.s[i]) goal.pos=i;
    }
}

bool BFS::is_solvable(const state & ini, const state & goal){
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

void BFS::print_in(const int & idx, QString & ans){
    if(~idx){
        print_in(q[idx].fa, ans);
        QString tmp;
        for(int i=0;i<9;i++){
            tmp.sprintf("%d ",q[idx].s[i]);
            ans+=tmp;
        }
        ans+='\n';
    }
}

QString BFS::print(){
    QString ans;
    if(q.empty()){
        ans.append("No Solution.");
        return ans;
    }
    print_in(front, ans);
    return ans;
}

bool BFS::bfs(){
    bitmap vis(362880);
    ini.fa=-1; // Recursive termination condition
    ini.steps=0;
    q.push_back(ini); // Push ini state into the Open list
    front=0, rear=1;
    while(front<rear){ // Loop until queue is empty
        state cur=q[front];
        if(!memcmp(cur.s,goal.s,sizeof(goal.s))){ // Find!
            return true;
        }
        nodes++;
        for(int i=0;i<4;i++){ // try 4 direction
            if(~d[cur.pos][i]){ // If current move is accepted
                // Construct the new state after move
                state next;
                memcpy(next.s,cur.s,sizeof(cur.s));
                next.pos=d[cur.pos][i];
                std::swap(next.s[cur.pos],next.s[next.pos]);
                next.fa=front;
                next.steps=cur.steps+1;
                // Encode new state
                int code=encode(next.s);
                if(!vis.is_visited(code)){ // If the new state is unvisited
                    vis.visit(code); // Mark it as visited
                    q.push_back(next); // Add it to the Open list
                    rear++;
                }
            }
        }
        front++;
    }
    return false;
}

void BFS::calc(){
    start=clock();
    if(is_solvable(ini,goal)) bfs();
    end=clock();
}
