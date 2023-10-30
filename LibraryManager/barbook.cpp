#include "barbook.h"
#include "ui_barbook.h"

BARbook::BARbook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BARbook)
{
    ui->setupUi(this);
}

BARbook::~BARbook()
{
    delete ui;
}
