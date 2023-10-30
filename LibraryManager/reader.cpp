#include "reader.h"
#include "ui_reader.h"

#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QList>
#include <QDebug>
#include <vector>
#include <QString>
#include <QMessageBox>
#include "ObjReader.h"

using namespace std;

QString fileReader = "C:/Users/84976/Documents/LibraryManager/txtfile/reader.txt";

reader::reader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::reader)
{
    ui->setupUi(this);
}

reader::~reader()
{
    delete ui;
}

void reader::loadToTableViewReader(const QString& filename, QTableView* tableView) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Lỗi", "Không thể mở tệp văn bản.");
        return;
    }

    QTextStream in(&file);

    // Đọc dòng đầu tiên (tiêu đề) để lấy tên các cột
    QString headerLine = in.readLine();
    QStringList headers = headerLine.split(",");

    QStandardItemModel* model = new QStandardItemModel(0, headers.size(), tableView);
    tableView->setModel(model);

    // Đặt tên các cột từ danh sách đề mục
    for (int col = 0; col < headers.size(); col++) {
        model->setHorizontalHeaderItem(col, new QStandardItem(headers[col]));
    }

    // Đọc và thêm dữ liệu từ các dòng tiếp theo
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList tokens = line.split(",");

        if (tokens.size() == headers.size()) {
            QList<QStandardItem*> items;
            for (const QString& token : tokens) {
                items.append(new QStandardItem(token));
            }
            model->appendRow(items);
        }
    }

    file.close();
}

void reader::on_tableListReader_clicked(const QModelIndex &index)
{
    if (index.isValid()) {
        int row = index.row();
        QStandardItemModel *model = dynamic_cast<QStandardItemModel*>(ui->tableListReader->model());

        if (model) {
            QString ReaderID = model->item(row, 0)->text();
            QString ReaderName = model->item(row, 1)->text();
            QString ReaderSex = model->item(row, 2)->text();
            QString ReaderStatus = model->item(row,3)->text();

            ui->txtReaderID->setPlainText(ReaderID);
            ui->txtNameReader->setPlainText(ReaderName);
            ui->txtReaderSex->setPlainText(ReaderSex);
            ui->txtReaderStatus->setPlainText(ReaderStatus);
        }
    }
}


void reader::on_btnRefreshreder_clicked()
{
    loadToTableViewReader(fileReader, ui->tableListReader);
}


void reader::on_btnRegist_clicked()
{
    QString ipName = ui->txtinputName->toPlainText();
    QString ipSex = ui->txtinputSex->toPlainText();
    if(ipSex != "Nam" && ipSex != "Nu")
    {
        QMessageBox::critical(this, "Lỗi", "Giới tính phải là Nam hoặc Nu");
    }
    else{
    ListReader rd;
    rd.loadFromTextFile(fileReader);
    rd.addReader(ipName,ipSex);
    loadToTableViewReader(fileReader, ui->tableListReader);
    }
}



void reader::on_btnRemoveReader_clicked()
{
    bool conversionSuccessful = false;
    int ReaderID = ui->txtReaderID->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
            QMessageBox::critical(this, "Lỗi", "Mã độc giả không hợp lệ");
            return;
    }
    else
    {
        ListReader rd;
        rd.loadFromTextFile(fileReader);

        if(rd.isReaderIDExists(ReaderID)==false)
        {
           QMessageBox::critical(this, "Lỗi", "Mã độc giả không có trong thư viện");
        }
        else
        {
           rd.removeReader(ReaderID);
        }
    }
    loadToTableViewReader(fileReader, ui->tableListReader);
}


void reader::on_btnUpdateReader_clicked()
{
    bool conversionSuccessful = false;
    int ReaderID = ui->txtReaderID->toPlainText().toInt(&conversionSuccessful);
    QString ReaderName = ui->txtNameReader->toPlainText();
    QString ReaderSex = ui->txtReaderSex->toPlainText();
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Mã độc giả không hợp lệ");
        return;
    }
    if(ReaderSex != "Nam" && ReaderSex != "Nu")
    {
        QMessageBox::critical(this, "Lỗi", "Giới tính phải là Nam hoặc Nu");
        return;
    }

        ListReader rd;
        rd.loadFromTextFile(fileReader);
        if(rd.isReaderIDExists(ReaderID)==false)
        {
           QMessageBox::critical(this, "Lỗi", "Mã độc giả không có trong thư viện");
        }
        else
        {
           rd.updateReader(ReaderID,ReaderName,ReaderSex);
        }
    loadToTableViewReader(fileReader, ui->tableListReader);

}

