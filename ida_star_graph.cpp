#include "ida_star_graph.h"
#include <QPainter>
#include <QDebug>

IDA_star_graph::IDA_star_graph(QWidget* parent)
    : QWidget(parent){
    setWindowTitle("Advanced Analyse Tools");
    resize(650,700);
}

IDA_star_graph::~IDA_star_graph(){}

void IDA_star_graph::set(const QString & input1, const QString & input2){
    for(int i=0;i<9;i++){
        ini.s[i]=int(input1[i].toLatin1()-'0');
        goal.s[i]=int(input2[i].toLatin1()-'0');
        if(!ini.s[i]) ini.pos=i;
        if(!goal.s[i]) goal.pos=i;
    }
}

bool IDA_star_graph::is_solvable(const state & ini, const state & goal){
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

void IDA_star_graph::paintEvent(QPaintEvent *){

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


}
