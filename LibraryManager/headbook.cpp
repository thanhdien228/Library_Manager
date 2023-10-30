#include "headbook.h"
#include "ui_headbook.h"
#include "ObjHeadbook.h"
#include "ObjBook.h"

#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QList>
#include <QDebug>
#include <vector>
#include <QString>
#include <QMessageBox>
using namespace std;

QString fileHeadBook = "C:/Users/84976/Documents/LibraryManager/txtfile/headbook.txt";
QString fileBook = "C:/Users/84976/Documents/LibraryManager/txtfile/book.txt";

Headbook::Headbook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Headbook)
{
    ui->setupUi(this);

}

Headbook::~Headbook()
{
    delete ui;
}


void Headbook::on_BtnRefresh_clicked()
{
    bool success = loadToTableViewHeadBook(fileHeadBook, ui->TableListHeadbook);
    if (!success) {
        // Xử lý lỗi nếu không thể load dữ liệu từ tệp văn bản
    }
}

bool Headbook:: loadToTableViewHeadBook(const QString& filename, QTableView* tableView) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Lỗi", "Không thể mở tệp văn bản.");
        return false;
    }

    QTextStream in(&file);

    // Đọc dòng đầu tiên (tiêu đề) để lấy tên các cột
    QString headerLine = in.readLine();
    QStringList headers = headerLine.split(",");

    QStandardItemModel* model = new QStandardItemModel(0, headers.size(), tableView);
    tableView->setModel(model);
    model->clear();

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
    return true;
}

void Headbook::displaytableListBooks(QTableView* tableView, const std::vector<ObjBook>& data) {
    QStandardItemModel* model = new QStandardItemModel(tableView);
    model->setColumnCount(4);  // Số cột, thay đổi tùy theo cần hiển thị

    // Đặt tên cột cho bảng
    model->setHorizontalHeaderItem(0, new QStandardItem("Mã "));
    model->setHorizontalHeaderItem(1, new QStandardItem("Tên "));
    model->setHorizontalHeaderItem(2, new QStandardItem("Trạng thái"));
    model->setHorizontalHeaderItem(3, new QStandardItem("Vị trí"));

    // Đặt số hàng dựa trên kích thước vector
    model->setRowCount(data.size());

    // Lặp qua vector và thêm dữ liệu vào mô hình
    for (int row = 0; row < data.size(); ++row) {
        const ObjBook& book = data[row];
        model->setItem(row, 0, new QStandardItem(QString::number(book.getbookcode())));
        model->setItem(row, 1, new QStandardItem(book.getbookname()));
        model->setItem(row, 2, new QStandardItem(QString::number(book.getbookstatus())));
        model->setItem(row, 3, new QStandardItem(book.getbooklocation()));
    }

    // Gán mô hình dữ liệu cho QTableView
    tableView->setModel(model);
}

void Headbook :: displaytableListHeadBooksfind(QTableView* tableView, const std::vector<ObjHeadBook>& data)
{
    QStandardItemModel* model = new QStandardItemModel(tableView);
    model->setColumnCount(6);  // Số cột, tùy thuộc vào dữ liệu của ObjHeadBook

    // Đặt tên cột cho bảng
    model->setHorizontalHeaderItem(0, new QStandardItem("ISBN"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Tên Sách"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Số Trang"));
    model->setHorizontalHeaderItem(3, new QStandardItem("Tác Giả"));
    model->setHorizontalHeaderItem(4, new QStandardItem("Năm Xuất Bản"));
    model->setHorizontalHeaderItem(5, new QStandardItem("Loại Sách"));

    // Đặt số hàng dựa trên kích thước vector
    model->setRowCount(data.size());

    // Lặp qua vector và thêm dữ liệu vào mô hình
    for (int row = 0; row < data.size(); ++row) {
        const ObjHeadBook& headbook = data[row];
        model->setItem(row, 0, new QStandardItem(QString::number(headbook.getISBN())));
        model->setItem(row, 1, new QStandardItem(headbook.getBookName()));
        model->setItem(row, 2, new QStandardItem(QString::number(headbook.getNumberPage())));
        model->setItem(row, 3, new QStandardItem(headbook.getAuthor()));
        model->setItem(row, 4, new QStandardItem(QString::number(headbook.getPublishingYear())));
        model->setItem(row, 5, new QStandardItem(headbook.getTypeBook()));
    }

    // Gán mô hình dữ liệu cho QTableView
    tableView->setModel(model);
}

void Headbook::on_TableListHeadbook_clicked(const QModelIndex &index)
{
    ListHeadBook lhb;
    lhb.loadFromTextFile(fileHeadBook);
    ListBook lb;
    lb.loadFromTextFile(fileBook);
    lhb.loadBooksToHeadBooks(lb);

    if (index.isValid()) {
        int row = index.row();
        QStandardItemModel *model = dynamic_cast<QStandardItemModel*>(ui->TableListHeadbook->model());

        if (model) {
            QString ISBN = model->item(row, 0)->text();
            QString Bookname = model->item(row, 1)->text();
            QString PagesNumber = model->item(row, 2)->text();
            QString Author = model->item(row,3)->text();
            QString PublishingYear = model->item(row, 4)->text();
            QString TypeHeadbook = model->item(row, 5)->text();

            ui->txtISBN->setPlainText(ISBN);
            ui->txtBookname->setPlainText(Bookname);
            ui->txtPagesNumber->setPlainText(PagesNumber);
            ui->txtAuthor->setPlainText(Author);
            ui->txtPublishingYear->setPlainText(PublishingYear);
            ui->txtTypeHeadbook->setPlainText(TypeHeadbook);
            vector<ObjBook> a = lhb.getBooksfromHeadBook(ISBN.toInt());
            displaytableListBooks(ui->tableListBook, a);
        }
    }
}


void Headbook::on_btnAddHeadbook_clicked()
{
    bool conversionSuccessful = false;

    // Lấy dữ liệu từ các QPlainTextEdit và kiểm tra kiểu dữ liệu
    int ISBN = ui->txtISBN->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Ma ISBN Khong hop le");
        return; // Không thực hiện xóa sách nếu ISBN không phải số nguyên.
    }


    QString Bookname = ui->txtBookname->toPlainText();

    int PagesNumber = ui->txtPagesNumber->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Số trang không phải là một số nguyên hợp lệ.");
        return; // Không thực hiện thêm sách nếu số trang không phải số nguyên.
    }

    QString Author = ui->txtAuthor->toPlainText();

    int PublishingYear = ui->txtPublishingYear->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Năm xuất bản không phải là một số nguyên hợp lệ.");
        return; // Không thực hiện thêm sách nếu năm xuất bản không phải số nguyên.
    }

    QString TypeHeadbook = ui->txtTypeHeadbook->toPlainText();

    // Tạo một đối tượng ObjBook từ dữ liệu
    ObjHeadBook headbook(ISBN, Bookname, PagesNumber, Author, PublishingYear, TypeHeadbook);

    // Thêm đối tượng vào ListBook
    ListHeadBook lhb;
    lhb.loadFromTextFile(fileHeadBook);
    for (const ObjHeadBook& existingHeadbook : lhb.getHeadBooks()) {
        if (existingHeadbook.getISBN() == ISBN || existingHeadbook.getBookName() == Bookname) {
            QMessageBox::critical(this, "Lỗi", "Sách đã tồn tại trong thư viện.");
            return; // Không thực hiện thêm sách nếu đã có sách tương tự.
        }
        else
        {
            lhb.addHeadBook(headbook);
        }

    }


    // Cập nhật lại dữ liệu trên QTableView
    bool success = loadToTableViewHeadBook(fileHeadBook, ui->TableListHeadbook);
    if (!success) {
        // Xử lý lỗi nếu không thể load dữ liệu từ tệp văn bản
    }

    // Xóa dữ liệu từ các QPlainTextEdit sau khi đã thêm sách
    ui->txtISBN->clear();
    ui->txtBookname->clear();
    ui->txtPagesNumber->clear();
    ui->txtAuthor->clear();
    ui->txtPublishingYear->clear();
    ui->txtTypeHeadbook->clear();
}


void Headbook::on_btnRemoveHeadBook_clicked()
{
    bool conversionSuccessful = false;
    int ISBN = ui->txtISBN->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "ISBN không phải là một số nguyên hợp lệ.");
        return; // Không thực hiện xóa sách nếu ISBN không phải số nguyên.
    }

    ListHeadBook lhb;
    if (lhb.loadFromTextFile(fileHeadBook)) {
        lhb.deleteHeadBook(ISBN);

        bool success = loadToTableViewHeadBook(fileHeadBook, ui->TableListHeadbook);
        if (success) {
            // Dữ liệu đã được cập nhật thành công
        } else {
            QMessageBox::critical(this, "Lỗi", "Không thể tải dữ liệu từ tệp văn bản.");
            // Xử lý lỗi nếu không thể load dữ liệu từ tệp văn bản.
        }
    } else {
        QMessageBox::critical(this, "Lỗi", "Không thể tải dữ liệu từ tệp văn bản.");
        // Xử lý lỗi nếu không thể tải dữ liệu từ tệp văn bản.
    }
}


void Headbook::on_btnFixHeadBook_clicked()
{
    bool conversionSuccessful = false;
    int ISBN = ui->txtISBN->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "ISBN không phải là một số nguyên hợp lệ.");
        return; // Không thực hiện thay đổi thông tin đầu sách nếu ISBN không phải số nguyên.
    }

    QString Bookname = ui->txtBookname->toPlainText();
    int PagesNumber = ui->txtPagesNumber->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Số trang không phải là một số nguyên hợp lệ.");
        return; // Không thực hiện thay đổi thông tin đầu sách nếu số trang không phải số nguyên.
    }

    QString Author = ui->txtAuthor->toPlainText();
    int PublishingYear = ui->txtPublishingYear->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Năm xuất bản không phải là một số nguyên hợp lệ.");
        return; // Không thực hiện thay đổi thông tin đầu sách nếu năm xuất bản không phải số nguyên.
    }

    QString TypeHeadbook = ui->txtTypeHeadbook->toPlainText();


    ListHeadBook lhb;
    lhb.loadFromTextFile(fileHeadBook);
    if (lhb.FindHeadBookbyISBN(ISBN)==true) {
        // Tìm thấy đầu sách với ISBN tương ứng
        lhb.uppdateHeadBook(ISBN, Bookname, PagesNumber, Author, PublishingYear, TypeHeadbook);
    }
    else {
        QMessageBox::critical(this, "Lỗi", "Không có đầu sách có mã ISBN này trong thư viện.");
    }

    bool success = loadToTableViewHeadBook(fileHeadBook, ui->TableListHeadbook);
    if (!success) {
        // Xử lý lỗi nếu không thể load dữ liệu từ tệp văn bản
    }
}



void Headbook::on_btnFindHeadBook_clicked()
{
    bool conversionSuccessful = false;
    int ISBN = ui->txtISBN->toPlainText().toInt(&conversionSuccessful);
    QString Bookname = ui->txtBookname->toPlainText();
    int PagesNumber = ui->txtPagesNumber->toPlainText().toInt(&conversionSuccessful);
    QString Author = ui->txtAuthor->toPlainText();
    int PublishingYear = ui->txtPublishingYear->toPlainText().toInt(&conversionSuccessful);
    QString TypeHeadbook = ui->txtTypeHeadbook->toPlainText();

    vector<ObjHeadBook> findheadbook;
    ListHeadBook lhb;
    lhb.loadFromTextFile(fileHeadBook);
    for (const ObjHeadBook& hb : lhb.getHeadBooks()) {
        if(hb.getISBN()==ISBN || hb.getBookName() == Bookname || hb.getAuthor() == Author || hb.getTypeBook() == TypeHeadbook)
        {
            findheadbook.push_back(hb);
        }
    }
    displaytableListHeadBooksfind(ui->TableListHeadbook,findheadbook);
}


void Headbook::on_btnAddBook_clicked()
{
    bool conversionSuccessful = false;
    int IDBook = ui->txtIDBook->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Mã Sách Không hợp lệ");
        return; // Không thực hiện thêm sách nếu Mã Sách không phải số nguyên.
    }

    QString BookName = ui->txtBookName->toPlainText();
    int Status = ui->txtStatus->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Trạng thái không hợp lệ");
        return; // Không thực hiện thêm sách nếu Trạng thái không phải số nguyên.
    }

    QString Location = ui->txtLocation->toPlainText();

    ObjBook book(IDBook, BookName, Status, Location);

    ListBook lb;
    ListHeadBook lhb;
    lhb.loadFromTextFile(fileHeadBook);
    lb.loadFromTextFile(fileBook);

    bool foundHeadBook = false;
    for (const ObjHeadBook& hb : lhb.getHeadBooks()) {
        if (hb.getBookName() == BookName) {
            foundHeadBook = true;
            break;
        }
    }

    bool foundIDbook = true;

    for(const ObjBook& b: lb.getBooks())
    {
        if(b.getbookcode()==IDBook)
        {
            foundIDbook = false;
        }
    }

    if (foundHeadBook&&foundIDbook) {
        lb.addBook(book);
        QMessageBox::information(this, "Success", "Thêm sách thành công");
    } else if (foundHeadBook == false )
    {
        QMessageBox::critical(this, "Lỗi", "Đầu sách này không có trong thư viện");
    }
    else if (foundIDbook == false )
    {
         QMessageBox::critical(this, "Lỗi", "Ma sach nay da co trong thu vien");
    }
}


void Headbook::on_btnDeleteBook_clicked()
{
    bool conversionSuccessful = false;
    int IDBook = ui->txtIDBook->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Mã Sách Không hợp lệ");
        return; // Không thực hiện thêm sách nếu Mã Sách không phải số nguyên.
    }

    QString BookName = ui->txtBookName->toPlainText();
    int Status = ui->txtStatus->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Trạng thái không hợp lệ");
        return; // Không thực hiện thêm sách nếu Trạng thái không phải số nguyên.
    }

    QString Location = ui->txtLocation->toPlainText();

    ListBook lb;
    lb.loadFromTextFile(fileBook);

    bool foundHeadBook = false;
    for (const ObjBook& book : lb.getBooks()) {
        if (book.getbookcode() == IDBook) {
            foundHeadBook = true;
            break;
        }
    }

    if (foundHeadBook) {
        lb.removeBook(IDBook);
        QMessageBox::information(this, "Success", "Xoa sach thanh cong");
    } else {
        QMessageBox::critical(this, "Lỗi", "Khong the xoa sach");
    }
}


void Headbook::on_tableListBook_clicked(const QModelIndex &index)
{
    if (index.isValid()) {
        int row = index.row();
        QStandardItemModel *model = dynamic_cast<QStandardItemModel*>(ui->tableListBook->model());

        if (model) {
            QString IDBook = model->item(row, 0)->text();
            QString Bookname = model->item(row, 1)->text();
            QString Status = model->item(row, 2)->text();
            QString Location = model->item(row,3)->text();

            ui->txtIDBook->setPlainText(IDBook);
            ui->txtBookName->setPlainText(Bookname);
            ui->txtStatus->setPlainText(Status);
            ui->txtLocation->setPlainText(Location);
        }
    }
}


void Headbook::on_btnFixBook_clicked()
{
    bool conversionSuccessful = false;
    int IDBook = ui->txtIDBook->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Mã Sách Không hợp lệ");
        return; // Không thực hiện thêm sách nếu Mã Sách không phải số nguyên.
    }

    QString BookName = ui->txtBookName->toPlainText();
    int Status = ui->txtStatus->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Trạng thái không hợp lệ");
        return; // Không thực hiện thêm sách nếu Trạng thái không phải số nguyên.
    }

    QString Location = ui->txtLocation->toPlainText();

    ListBook lb;
    lb.loadFromTextFile(fileBook);

    bool foundHeadBook = false;
    for (const ObjBook& book : lb.getBooks()) {
        if (book.getbookcode() == IDBook) {
            foundHeadBook = true;
            break;
        }
    }

    if (foundHeadBook) {
        lb.updateBookLocation(IDBook,Location);
        QMessageBox::information(this, "Success", "Doi vi tri sach thanh cong");
    } else {
        QMessageBox::critical(this, "Lỗi", "Sach nay khong ton tai");
    }
}

