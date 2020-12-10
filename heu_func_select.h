#ifndef Heu_func_select_H
#define Heu_func_select_H

#include <QWidget>
#include <QObject>
#include <queue>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include "bitmap.h"

extern const int d[9][4];
extern const int manhattan[9][9];
extern int encode(int *);

class Heu_func_select : public QWidget
{
    Q_OBJECT

// 绘图部分
public:
    explicit Heu_func_select(QWidget* parent = 0);
    ~Heu_func_select();


public slots:
    void update_A();
    void update_B();
    void graph();
    void update(const double &, const int &, const int &);

private:
    int A,B;
    QLineEdit *IN_line;
    QLineEdit *OUT_line;
    QString ini_line;
    QString goal_line;
    QLabel *nodes_show;
    QLabel *time_show;
    QLabel *steps_show;

public:
    void set(const QString &, const QString &, const int &, const int &);


};

#endif // Heu_func_select_H
