#ifndef EIGHT_PUZZLE_H
#define EIGHT_PUZZLE_H

#include<stack>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QString>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include<QTextBrowser>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class eight_puzzle; }
QT_END_NAMESPACE

class eight_puzzle : public QWidget
{
    Q_OBJECT

public:
    eight_puzzle(QWidget *parent = nullptr);
    ~eight_puzzle();
    QTextBrowser *path;

public slots:
    void update_grid_ini(const QString &); // 根据输入实时更新棋盘数据
    void update_grid_goal(const QString &); // 根据输入实时更新棋盘数据
    void calc_func();

private:
    Ui::eight_puzzle *ui;
    QLabel *nodes;
    QLabel *time;
    QLabel *memory;
    QLabel *steps;
    QComboBox *method;
    QLineEdit *input_line;
    QLineEdit *output_line;
    QLineEdit *block_ini[9]; // 初始棋盘布局
    QLineEdit *block_goal[9]; // 目标棋盘布局
};
#endif // EIGHT_PUZZLE_H
