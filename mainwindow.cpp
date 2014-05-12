#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(loadFile()));
    tabClean();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeTab(const int& index)
{
    QWidget* tabItem = ui->tabWidget->widget(index);
    ui->tabWidget->removeTab(index);
    tabs[index].clean();
    delete tabItem;
    tabItem = nullptr;
}

void MainWindow::addTab(QString dir, QWidget* plot)
{    
    QStringList parts = dir.split("/");
    QString tabName = parts.at(parts.size()-1);
    QWidget* tab = new QWidget(ui->tabWidget);
    QGridLayout *layout = new QGridLayout(this);

    layout->addWidget(plot,0,0);
    tab->setLayout(layout);
    tab->show();
    ui->tabWidget->addTab(tab, tabName);
}

void MainWindow::loadFile()
{
    QStringList filenames = QFileDialog::getOpenFileNames(
            this,
            tr("Open Document"),
            QDir::currentPath(),
            tr("All files (*.*);;Documents (*.txt)") );
        if( !filenames.isEmpty() )
        {
            #pragma omp parallel for
            for(int i = 0; i < filenames.size(); ++i){
                std::vector<int> v;
                v.push_back(1);

                parser p(filenames[i]);

                QCustomPlot* cplot = new QCustomPlot();
                cplot->addGraph();
                cplot->addGraph();
                cplot->graph(0)->setPen(QPen(Qt::blue));
                cplot->graph(1)->setPen(QPen(Qt::yellow));

                QVector<double> *x, *y, *yFiltered;
                x = p.getJaw();
                y = p.getForce();

                yFiltered = KolmogorovZurbenko::Filter(p.getJaw(), p.getForce(), 100);

                double maxX = *std::max_element(std::begin(*x), std::end(*x));
                double maxY = *std::max_element(std::begin(*y), std::end(*y));
                double minX = *std::min_element(std::begin(*x), std::end(*x));
                double minY = *std::min_element(std::begin(*y), std::end(*y));

                cplot->graph(0)->setData(*x, *y);
                cplot->graph(1)->setData(*x, *yFiltered);
                cplot->xAxis->setLabel("Jaw(mm)");
                cplot->yAxis->setLabel("Force(kgf)");
                cplot->xAxis->setRange(minX, maxX);
                cplot->yAxis->setRange(minY, maxY);
                cplot->setInteraction(QCP::iRangeDrag, true);
                cplot->setInteraction(QCP::iRangeZoom, true);

                cplot->replot();

                QWidget* plot = cplot;
                addTab(filenames[i], plot);
                tab t =  tab(x,y);
                tabs.append(t);
            }
        }
}

void MainWindow::tabClean()
{
    ui->tabWidget->clear();
}
