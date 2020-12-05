#include "eight_puzzle.h"
#include "ui_eight_puzzle.h"
#include"IDA_star.h"

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
    connect(input_line, &QLineEdit::textChanged, this, &eight_puzzle::update_grid_ini);
    IN->addWidget(input);
    IN->addWidget(input_line);

    QHBoxLayout* OUT=new QHBoxLayout;
    QLabel *output = new QLabel("Goal: ");
    output_line = new QLineEdit;
    output_line->setMaxLength(9); // 最多输入 9 个数
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


    //  计算
    QPushButton *calc = new QPushButton("Calculate");
    connect(calc, SIGNAL(clicked()), this, SLOT(calc_func()));
    r_column->addWidget(calc,cnt++);

    UP->addLayout(r_column);

    mainUI->addLayout(UP);

    QHBoxLayout *DOWN = new QHBoxLayout;
    path = new QLineEdit;
    DOWN->addWidget(path);
    mainUI->addLayout(DOWN);

    resize(500,100);
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
    IDA_star c1(input_line->text(),output_line->text());
    c1.calc();
    path->setText(c1.print_path());
    return;
}
