#include "heu_func_select.h"
#include "graph_select.h"
#include <QPainter>
#include <QDebug>

Heu_func_select::Heu_func_select(QWidget* parent)
    : QWidget(parent){
    setWindowTitle("Heu_func Comparison");

    QHBoxLayout *mainUI = new QHBoxLayout(this);
    QVBoxLayout *L = new QVBoxLayout;

    QLabel *Introduction = new QLabel("f(x)=A*g(x)+B*h(x)");
    QLabel *IN_label = new QLabel("Input A: ");
    QLabel *OUT_label = new QLabel("Input B: ");
    IN_line = new QLineEdit;
    OUT_line = new QLineEdit;
    connect(IN_line, &QLineEdit::textChanged, this, &Heu_func_select::update_A);
    connect(OUT_line, &QLineEdit::textChanged, this, &Heu_func_select::update_B);
    QHBoxLayout *IN = new QHBoxLayout;
    IN->addWidget(IN_label);
    IN->addWidget(IN_line);
    QHBoxLayout *OUT = new QHBoxLayout;
    OUT->addWidget(OUT_label);
    OUT->addWidget(OUT_line);
    QPushButton *Bt = new QPushButton("Analyse");
    connect(Bt, SIGNAL(clicked()), this, SLOT(graph()));

    L->addWidget(Introduction);
    L->addLayout(IN);
    L->addLayout(OUT);
    L->addWidget(Bt);

    QGroupBox *info = new QGroupBox;
    info->setTitle("Statistics");
    QGridLayout *info_grid = new QGridLayout;
    QLabel *nodes = new QLabel("Travelled nodes: ");
    QLabel *time = new QLabel("Time used (ms): ");
    QLabel *steps = new QLabel("Steps: ");
    nodes_show = new QLabel;
    nodes_show->setMinimumWidth(50);
    time_show = new QLabel;
    time_show->setMinimumWidth(50);
    steps_show = new QLabel;
    steps_show->setMinimumWidth(50);
    info_grid->addWidget(nodes,0,0);
    info_grid->addWidget(nodes_show,0,1);
    info_grid->addWidget(time,1,0);
    info_grid->addWidget(time_show,1,1);
    info_grid->addWidget(steps,2,0);
    info_grid->addWidget(steps_show,2,1);
    info->setLayout(info_grid);

    mainUI->addLayout(L);
    mainUI->addWidget(info);
}

void Heu_func_select::update_A(){
    A=IN_line->text().toInt();
}

void Heu_func_select::update_B(){
    B=OUT_line->text().toInt();
}

Heu_func_select::~Heu_func_select(){}

void Heu_func_select::set(const QString & input1, const QString & input2, const int & _A, const int & _B){
    ini_line=input1;
    goal_line=input2;
    A=_A;
    B=_B;
}

void Heu_func_select::graph(){
    Graph_select *g = new Graph_select;
    connect(g, SIGNAL(sig_update(const double &, const int &, const int&)), this, SLOT(update(const double &, const int &, const int &)));
    g->set(ini_line, goal_line, A, B);
    g->show();
}

void Heu_func_select::update(const double & t, const int & n, const int & s){
    time_show->setText(QString::number(t));
    nodes_show->setText(QString::number(n));
    steps_show->setText(QString::number(s));
}
