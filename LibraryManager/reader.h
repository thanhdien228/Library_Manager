#ifndef READER_H
#define READER_H

#include <QMainWindow>
#include <QMainWindow>
#include <QTableView>

namespace Ui {
class reader;
}

class reader : public QMainWindow
{
    Q_OBJECT

public:
    explicit reader(QWidget *parent = nullptr);
    ~reader();

private slots:
    void on_tableListReader_clicked(const QModelIndex &index);

    void loadToTableViewReader(const QString& filename, QTableView* tableView);

    void on_btnRefreshreder_clicked();

    void on_btnRegist_clicked();

    void on_btnRemoveReader_clicked();

    void on_btnUpdateReader_clicked();

private:
    Ui::reader *ui;
};

#endif // READER_H
