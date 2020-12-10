#include "dfs_graph.h"
#include <QPainter>
#include <QDebug>

DFS_graph::DFS_graph(QWidget* parent)
    : QWidget(parent){
    setWindowTitle("Advanced Analyse Tools");
    resize(650,700);
}

DFS_graph::~DFS_graph(){}

void DFS_graph::set(const QString & input1, const QString & input2){
    for(int i=0;i<9;i++){
        ini.s[i]=int(input1[i].toLatin1()-'0');
        goal.s[i]=int(input2[i].toLatin1()-'0');
        if(!ini.s[i]) ini.pos=i;
        if(!goal.s[i]) goal.pos=i;
    }
}

bool DFS_graph::is_solvable(const state & ini, const state & goal){
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

void DFS_graph::paintEvent(QPaintEvent *){

    // 指定绘图设备
    QPainter painter(this);

    // 抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    // 设置画笔
    QPen penLine;
    penLine.setWidth(1); //线宽
    penLine.setColor(Qt::black); //划线颜色
    penLine.setStyle(Qt::SolidLine); //线的类型，实线、虚线等
    penLine.setCapStyle(Qt::FlatCap); //线端点样式
    penLine.setJoinStyle(Qt::BevelJoin); //线的连接点样式
    painter.setBrush(Qt::red); // 填充颜色
    painter.setPen(penLine);

    QFont font("Fira Code", 13, QFont::Normal, false);
    painter.setFont(font);

    // 设置画布
    painter.translate(300,30); // 坐标原点初始化为 画布上边缘中点

    if(is_solvable(ini,goal)){
        while(!st.empty()) st.pop();
        ini.steps=0;
        ini.prepos=-1;
        ini.px=ini.py=ini.fpx=ini.fpy=0;

        //qDebug()<<ini.pos<<Qt::endl;

        painter.drawEllipse(ini.px-4,ini.py-4,8,8);
        painter.drawText(ini.px-10,ini.py-10,"Ini");

        st.push(ini);
        while(!st.empty()){
            state cur=st.top();
            st.pop();
            painter.drawLine(cur.px,cur.py,cur.fpx,cur.fpy); //画线
            if(!memcmp(cur.s, goal.s, sizeof(goal.s))){
                painter.drawEllipse(cur.px-4,cur.py-4,8,8);
                painter.drawText(cur.px-15,cur.py+18,"Goal");
                //qDebug()<<cur.px<<cur.py<<cur.steps;
                return;
            }
            if(cur.steps>max_depth) continue;
            for(int i=3;i>=0;i--){ // 保持 UDLR 的搜索顺序
                if(d[cur.pos][i]==cur.prepos) continue;
                if(~d[cur.pos][i]){
                    state next;
                    memcpy(next.s, cur.s, sizeof(cur.s));
                    next.pos=d[cur.pos][i];
                    std::swap(next.s[next.pos], next.s[cur.pos]);
                    next.steps=cur.steps+1;
                    next.prepos=cur.pos;
                    // 设置 next 坐标
                    next.px=cur.px-(3.0-i*2)*w[next.steps];
                    next.py=cur.py+h;
                    next.fpx=cur.px;
                    next.fpy=cur.py;
                    st.push(next);
                }
            }
        }
        return;
    }
}
