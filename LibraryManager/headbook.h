#ifndef HEADBOOK_H
#define HEADBOOK_H

#include <QMainWindow>
#include <QTableView>
#include "ObjBook.h"
#include "ObjHeadbook.h"

namespace Ui {
class Headbook;
}

class Headbook : public QMainWindow
{
    Q_OBJECT

public:
    explicit Headbook(QWidget *parent = nullptr);
    ~Headbook();

private slots:

    void on_BtnRefresh_clicked();

    void on_TableListHeadbook_clicked(const QModelIndex &index);

    void on_btnAddHeadbook_clicked();

    void on_btnRemoveHeadBook_clicked();

    void on_btnFixHeadBook_clicked();

    void displaytableListBooks(QTableView* tableView, const std::vector<ObjBook>& data);

    void displaytableListHeadBooksfind(QTableView* tableView, const std::vector<ObjHeadBook>& data);

    void on_btnFindHeadBook_clicked();

    void on_btnAddBook_clicked();

    void on_btnDeleteBook_clicked();

    void on_tableListBook_clicked(const QModelIndex &index);

    void on_btnFixBook_clicked();

    bool loadToTableViewHeadBook(const QString& filename, QTableView* tableView);

private:
    Ui::Headbook *ui;
};

#endif // HEADBOOK_H
