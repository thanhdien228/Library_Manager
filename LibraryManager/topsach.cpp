#include "topsach.h"
#include "ui_topsach.h"
#include "ObjReader.h"

TopSach::TopSach(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TopSach)
{
    ui->setupUi(this);
}

TopSach::~TopSach()
{
    delete ui;
}
