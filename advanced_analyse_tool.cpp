#include "advanced_analyse_tool.h"
#include "bfs_graph.h"
#include "a_star_graph.h"
#include "dfs_graph.h"
#include "iddfs_graph.h"
#include "ida_star_graph.h"
#include "heu_func_select.h"

Advanced_analyse_tool::Advanced_analyse_tool(QWidget *parent) : QWidget(parent)
{
    QGridLayout *select = new QGridLayout(this);
    QPushButton *Visualize = new QPushButton;
    Visualize->setText("Visualize");
    connect(Visualize, SIGNAL(clicked()), this, SLOT(Visualize_func()));
    QPushButton *Heu = new QPushButton;
    Heu->setText("Heu Analyse");
    connect(Heu, SIGNAL(clicked()), this, SLOT(Heu_analyse_func()));
    select->addWidget(Visualize,0,0);
    select->addWidget(Heu,1,0);
    setWindowTitle("Advanced Analyse Tools");
    resize(250,100);
}

void Advanced_analyse_tool::set(const QString & _input_line, const QString & _output_line, const int & _method){
    input_line=_input_line;
    output_line=_output_line;
    method=_method;
}


void Advanced_analyse_tool::Visualize_func(){
    if(input_line.length()<9) return;
    if(output_line.length()<9) return;
    switch(method){
    case 0:{
        BFS_graph *g0 = new BFS_graph;
        g0->set(input_line, output_line);
        g0->show();
        break;
    }
    case 1:{
        A_star_graph *g1 = new A_star_graph;
        g1->set(input_line, output_line);
        g1->show();
        break;
    }
    case 2:{
        DFS_graph *g2 = new DFS_graph;
        g2->set(input_line, output_line);
        g2->show();
        break;
    }
    case 3:{
        IDDFS_graph *g3 = new IDDFS_graph;
        g3->set(input_line, output_line);
        g3->show();
        break;
    }
    case 4:{
        IDA_star_graph *g4 = new IDA_star_graph;
        g4->set(input_line, output_line);
        g4->show();
        break;
    }
    }
    this->close();
}

void Advanced_analyse_tool::Heu_analyse_func(){
    Heu_func_select *s = new Heu_func_select;
    s->set(input_line, output_line, 1, 1);
    s->show();
}
