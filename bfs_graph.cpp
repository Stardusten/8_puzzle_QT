#include "bfs_graph.h"
#include <QPainter>
#include <QDebug>

BFS_graph::BFS_graph(QWidget* parent)
    : QWidget(parent){

    resize(650,700);
}

BFS_graph::~BFS_graph(){}


void BFS_graph::set(const QString & input1, const QString & input2){
    for(int i=0;i<9;i++){
        ini.s[i]=int(input1[i].toLatin1()-'0');
        goal.s[i]=int(input2[i].toLatin1()-'0');
        if(!ini.s[i]) ini.pos=i;
        if(!goal.s[i]) goal.pos=i;
    }
}

bool BFS_graph::is_solvable(const state & ini, const state & goal){
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

void BFS_graph::paintEvent(QPaintEvent *){

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

    while(!q.empty()) q.pop(); // 清空队列，防止重绘时出错
    bitmap vis(362880);
    ini.steps=0;
    ini.px=ini.py=ini.fpx=ini.fpy=0;
    q.push(ini);
    painter.drawEllipse(ini.px-4,ini.py-4,8,8);
    painter.drawText(ini.px-10,ini.py-10,"Ini");
    while(!q.empty()){ // Loop until queue is empty
        state cur=q.front();
        q.pop();
        painter.drawLine(cur.px,cur.py,cur.fpx,cur.fpy); // 画线
        //qDebug()<<cur.fpx<<cur.fpy<<cur.px<<cur.py<<Qt::endl;
        if(!memcmp(cur.s,goal.s,sizeof(goal.s))){ // Find!
            painter.drawEllipse(cur.px-4,cur.py-4,8,8);
            painter.drawText(cur.px-15,cur.py+18,"Goal");
            return;
        }
        for(int i=0;i<4;i++){ // try 4 direction
            if(~d[cur.pos][i]){ // If current move is accepted
                // Construct the new state after move
                state next;
                memcpy(next.s,cur.s,sizeof(cur.s));
                next.pos=d[cur.pos][i];
                std::swap(next.s[cur.pos],next.s[next.pos]);
                next.steps=cur.steps+1;
                // 设置 next 坐标
                next.px=cur.px-(3.0-i*2)*w[next.steps];
                next.py=cur.py+h;
                next.fpx=cur.px;
                next.fpy=cur.py;
                //qDebug()<<next.px<<next.py<<Qt::endl;
                // Encode new state
                int code=encode(next.s);
                if(!vis.is_visited(code)){ // If the new state is unvisited
                    vis.visit(code); // Mark it as visited
                    q.push(next);
                }
            }
        }
    }
    return;
}
