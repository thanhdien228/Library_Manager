#ifndef TOPSACH_H
#define TOPSACH_H

#include <QMainWindow>

namespace Ui {
class TopSach;
}

class TopSach : public QMainWindow
{
    Q_OBJECT

public:
    explicit TopSach(QWidget *parent = nullptr);
    ~TopSach();

private:
    Ui::TopSach *ui;
};

#endif // TOPSACH_H
