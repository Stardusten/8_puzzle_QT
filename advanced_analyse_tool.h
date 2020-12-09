#ifndef ADVANCED_ANALYSE_TOOL_H
#define ADVANCED_ANALYSE_TOOL_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QString>

class Advanced_analyse_tool : public QWidget
{
    Q_OBJECT
public:
    explicit Advanced_analyse_tool(QWidget *parent = nullptr);
    ~Advanced_analyse_tool(){}
    void set(const QString &, const QString &, const int &);

public slots:
    void Visualize_func();
    void Heu_analyse_func();

private:
    QString input_line;
    QString output_line;
    int method;
};

#endif // ADVANCED_ANALYSE_TOOL_H
