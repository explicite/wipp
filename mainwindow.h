#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QWidget>
#include "kolmogorovzurbenko.h"
#include "qcustomplot.h"
#include "parser.h"
#include "tab.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void closeTab(const int&);
    void addTab(QString, QWidget*);
    void loadFile();
    void press(QCPAbstractPlottable*, QMouseEvent*);

private:
    Ui::MainWindow *ui;
    void tabClean();
    QVector<tab> tabs;
};

#endif // MAINWINDOW_H
