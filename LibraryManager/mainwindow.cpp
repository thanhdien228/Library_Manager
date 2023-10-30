#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "headbook.h"
#include "reader.h"
#include "headbook.h"
#include "barbook.h"
#include "topsach.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnHeadbook_clicked()
{
    Headbook* hb = new Headbook(this);
    hb->show();
}


void MainWindow::on_btnReader_clicked()
{
    reader* rd = new reader(this);
    rd->show();
}


void MainWindow::on_btnbarbook_clicked()
{
    BARbook* bb = new BARbook(this);
    bb -> show();
}


void MainWindow::on_btnbarbook_2_clicked()
{
    TopSach* ts = new TopSach(this);
    ts ->show();
}

