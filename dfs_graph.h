#ifndef DFS_graph_H
#define DFS_graph_H

#include <QWidget>
#include <QObject>
#include <stack>
#include "bitmap.h"

extern const int d[9][4];

class DFS_graph : public QWidget
{
    Q_OBJECT

// 绘图部分
public:
    explicit DFS_graph(QWidget* parent = 0);
    ~DFS_graph();

protected:
    void paintEvent(QPaintEvent *);

// 主算法部分
public:
    void set(const QString &, const QString &);

private:
    // 数据成员
    struct state{
        int s[9]; // 0 represents Space
        int pos; // Position of space
        int steps; // Steps to reach current state
        int prepos;
        double px,py;
        double fpx,fpy;
    }ini,goal;

    std::stack<state> st;

    const int h=20; // 每层高

    const int max_depth=30;

    const double w[32]={ // 第 i 层两节点间宽度的一半
        300,
        75,
        18.75,
        4.6875,
        1.17188,
        0.292969,
        0.0732422,
        0.0183105,
        0.00457764,
        0.00114441,
        0.000286102,
        7.15256e-05,
        1.78814e-05,
        4.47035e-06,
        1.11759e-06,
        2.79397e-07,
        6.98492e-08,
        1.74623e-08,
        4.36557e-09,
        1.09139e-09,
        2.72848e-10,
        6.82121e-11,
        1.7053e-11,
        4.26326e-12,
        1.06581e-12,
        2.66454e-13,
        6.66134e-14,
        1.66533e-14,
        4.16334e-15,
        1.04083e-15,
        2.60209e-16,
        6.50521e-17,
    };

    // 工具函数
    bool is_solvable(const state &, const state &);
};

#endif // DFS_graph_H
