#ifndef BARBOOK_H
#define BARBOOK_H

#include <QMainWindow>

namespace Ui {
class BARbook;
}

class BARbook : public QMainWindow
{
    Q_OBJECT

public:
    explicit BARbook(QWidget *parent = nullptr);
    ~BARbook();

private:
    Ui::BARbook *ui;
};

#endif // BARBOOK_H
