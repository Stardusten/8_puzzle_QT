#include "a_star_graph.h"
#include <QPainter>
#include <QDebug>

A_star_graph::A_star_graph(QWidget* parent)
    : QWidget(parent){
    setWindowTitle("Advanced Analyse Tools");
    resize(650,700);
}

A_star_graph::~A_star_graph(){}

bool operator<(const A_star_graph::state & x, const A_star_graph::state & y){
    return x.f>y.f;
}

void A_star_graph::set(const QString & input1, const QString & input2){
    for(int i=0;i<9;i++){
        ini.s[i]=int(input1[i].toLatin1()-'0');
        goal.s[i]=int(input2[i].toLatin1()-'0');
        if(!ini.s[i]) ini.pos=i;
        if(!goal.s[i]) goal.pos=i;
    }
}

int A_star_graph::calc_manhattan(const state & cur,const state & goal){
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

bool A_star_graph::is_solvable(const state & ini, const state & goal){
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

void A_star_graph::paintEvent(QPaintEvent *){

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
        while(!q.empty()) q.pop();
        bitmap vis(362880);
        ini.steps=0;
        ini.h=calc_manhattan(ini,goal);
        ini.f=ini.steps+ini.h;
        ini.px=ini.py=ini.fpx=ini.fpy=0;

        painter.drawEllipse(ini.px-4,ini.py-4,8,8);
        painter.drawText(ini.px-10,ini.py-10,"Ini");

        q.push(ini);
        while(!q.empty()){
            state cur=q.top();
            q.pop();
            painter.drawLine(cur.px,cur.py,cur.fpx,cur.fpy); // 画线
            if(!cur.h){
                painter.drawEllipse(cur.px-4,cur.py-4,8,8);
                painter.drawText(cur.px-15,cur.py+18,"Goal");
                return;
            }
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
                    // 设置 next 坐标
                    next.px=cur.px-(3.0-i*2)*w[next.steps];
                    next.py=cur.py+h;
                    next.fpx=cur.px;
                    next.fpy=cur.py;
                    //qDebug()<<next.px<<' '<<next.py<<Qt::endl;
                    int code=encode(next.s);
                    if(!vis.is_visited(code)){
                        vis.visit(code);
                        q.push(next);
                    }
                }
            }
        }
        return;
    }
}
