#include "eight_puzzle.h"
#include "ui_eight_puzzle.h"
#include "IDA_star.h"
#include "BFS.h"
#include "IDDFS.h"
#include "A_star.h"
#include "DFS.h"
#include "advanced_analyse_tool.h"

eight_puzzle::eight_puzzle(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::eight_puzzle)
{
    ui->setupUi(this);
    setWindowTitle("8_puzzle");

    QVBoxLayout* mainUI = new QVBoxLayout(this);
    QHBoxLayout* UP = new QHBoxLayout();

    QGroupBox* Ini = new QGroupBox;
    Ini->setTitle("Ini");

    QGridLayout* grid_ini = new QGridLayout;
    for(int i=0;i<9;i++){
        block_ini[i]= new QLineEdit;
        block_ini[i]->setMaximumWidth(20);
        block_ini[i]->setReadOnly(true);
        block_ini[i]->setAlignment(Qt::AlignCenter);
        // Connect to get input
        grid_ini->addWidget(block_ini[i], i/3, i%3);
    }

    Ini->setLayout(grid_ini);
    UP->addWidget(Ini);

    QGroupBox* Goal = new QGroupBox;
    Goal->setTitle("Goal");

    QGridLayout* grid_goal = new QGridLayout;
    for(int i=0;i<9;i++){
        block_goal[i]= new QLineEdit;
        block_goal[i]->setMaximumWidth(20);
        block_goal[i]->setReadOnly(true); // 设为只读
        block_goal[i]->setAlignment(Qt::AlignCenter);
        // Connect to get input
        grid_goal->addWidget(block_goal[i], i/3, i%3);
    }

    Goal->setLayout(grid_goal);
    UP->addWidget(Goal);


    // 右栏
    QVBoxLayout *r_column = new QVBoxLayout;
    int cnt=0; // 纵向行数计数器

    // 输入输出
    QHBoxLayout* IN=new QHBoxLayout;
    QLabel *input = new QLabel("Ini: ");
    input_line = new QLineEdit;
    input_line->setMaxLength(9); // 最多输入 9 个数
    input_line->setValidator(new QIntValidator());
    input_line->setText("123456780");
    update_grid_ini(input_line->text());
    connect(input_line, &QLineEdit::textChanged, this, &eight_puzzle::update_grid_ini);
    IN->addWidget(input);
    IN->addWidget(input_line);

    QHBoxLayout* OUT=new QHBoxLayout;
    QLabel *output = new QLabel("Goal: ");
    output_line = new QLineEdit;
    output_line->setMaxLength(9); // 最多输入 9 个数
    output_line->setValidator(new QIntValidator());
    output_line->setText("123456708");
    update_grid_goal(output_line->text());
    connect(output_line, &QLineEdit::textChanged, this, &eight_puzzle::update_grid_goal);
    OUT->addWidget(output,0);
    OUT->addWidget(output_line,1);

    r_column->addLayout(IN,cnt++);
    r_column->addLayout(OUT,cnt++);

    // 选择计算方法
    QHBoxLayout* METHOD = new QHBoxLayout;
    QLabel *method_label = new QLabel("Method: ");
    METHOD->addWidget(method_label,0);
    method = new QComboBox;
    method->addItem("BFS");
    method->addItem("A*");
    method->addItem("DFS");
    method->addItem("IDDFS");
    method->addItem("IDA*");
    METHOD->addWidget(method,1);
    r_column->addLayout(METHOD, cnt++);

    QHBoxLayout *buttoms = new QHBoxLayout;

    //  计算
    QPushButton *calc = new QPushButton("Calculate");
    connect(calc, SIGNAL(clicked()), this, SLOT(calc_func()));
    buttoms->addWidget(calc);

    // 高级功能
    QPushButton *advanced  = new QPushButton("Advanced");
    connect(advanced, SIGNAL(clicked()), this, SLOT(advanced_func()));
    buttoms->addWidget(advanced);

    r_column->addLayout(buttoms);
    UP->addLayout(r_column);

    mainUI->addLayout(UP);


    // 结果部分

    QVBoxLayout *DOWN = new QVBoxLayout;

    QLabel *down_label = new QLabel("Statistics: ");
    DOWN->addWidget(down_label,0);

    QHBoxLayout *Statistics = new QHBoxLayout;

    QGridLayout *info = new QGridLayout;
    QLabel *nodes_label = new QLabel("     Traveled nodes: ");
    QLabel *time_label = new QLabel("     Time used (ms): ");
    QLabel *memory_label = new QLabel("     Memory used (KB): ");
    QLabel *steps_label = new QLabel("     Steps: ");
    nodes = new QLabel;
    time = new QLabel;
    memory = new QLabel;
    steps = new QLabel;
    info->addWidget(nodes_label,0,0);
    info->addWidget(time_label,1,0);
    info->addWidget(memory_label,2,0);
    info->addWidget(steps_label,3,0);
    info->addWidget(nodes,0,1);
    info->addWidget(time,1,1);
    info->addWidget(memory,2,1);
    info->addWidget(steps,3,1);

    QVBoxLayout *path_col = new QVBoxLayout;
    QLabel *path_label = new QLabel("Path: ");
    path = new QTextBrowser;
    path->setMaximumWidth(200);
    path_col->addWidget(path_label);
    path_col->addWidget(path);

    Statistics->addLayout(info,0);
    Statistics->addLayout(path_col,1);


    DOWN->addLayout(Statistics,1);

    mainUI->addLayout(DOWN);

    resize(500,150);
}

eight_puzzle::~eight_puzzle()
{
    delete ui;
}

void eight_puzzle::update_grid_ini(const QString & in){
    for(int i=0;i<in.count();i++){
        block_ini[i]->setText(in.at(i));
    }
}

void eight_puzzle::update_grid_goal(const QString & in){
    for(int i=0;i<in.count();i++){
        block_goal[i]->setText(in.at(i));
    }
}

void eight_puzzle::calc_func(){
    if(input_line->text().length()<9) return;
    if(output_line->text().length()<9) return;
    switch(method->currentIndex()){
    case 0:{
        BFS *c0=new BFS;
        c0->set(input_line->text(),output_line->text());
        c0->calc();
        steps->setText(c0->steps());
        time->setText(c0->time_used());
        nodes->setText(c0->traveled_nodes());
        path->setText(c0->print());
        delete c0;
        break;
    }
    case 1:{
        A_star *c1=new A_star;
        c1->set(input_line->text(),output_line->text());
        c1->calc();
        steps->setText(c1->steps());
        time->setText(c1->time_used());
        nodes->setText(c1->traveled_nodes());
        path->setText(c1->print());
        delete c1;
        break;
    }
    case 2:{
        DFS *c2 = new DFS;
        c2->set(input_line->text(),output_line->text());
        c2->calc();
        steps->setText(c2->steps());
        time->setText(c2->time_used());
        nodes->setText(c2->traveled_nodes());
        path->setText(c2->print());
        delete c2;
        break;
    }
    case 3:{
        IDDFS *c3 = new IDDFS;
        c3->set(input_line->text(),output_line->text());
        c3->calc();
        steps->setText(c3->steps());
        time->setText(c3->time_used());
        nodes->setText(c3->traveled_nodes());
        path->setText(c3->print());
        delete c3;
        break;
    }
    case 4:{
        IDA_star *c4 = new IDA_star;
        c4->set(input_line->text(),output_line->text());
        c4->calc();
        steps->setText(c4->steps());
        time->setText(c4->time_used());
        nodes->setText(c4->traveled_nodes());
        path->setText(c4->print());
        delete c4;
        break;
    }
    }
    return;
}

void eight_puzzle::advanced_func(){
    Advanced_analyse_tool *ad = new Advanced_analyse_tool;
    ad->set(input_line->text(), output_line->text(), method->currentIndex());
    ad->show();
    return;
}
