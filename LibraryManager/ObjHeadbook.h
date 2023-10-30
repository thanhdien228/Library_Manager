#ifndef OBJHEADBOOK_H
#define OBJHEADBOOK_H

#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QString>
#include "ObjBook.h"


using namespace std;


class ObjHeadBook {
private:
    int ISBN;
    QString BookName;
    int NumberPage;
    QString Author;
    int PublishingYear;
    QString TypeBook;
    vector<ObjBook> Books;

public:
    ObjHeadBook(int ISBN, QString BookName, int NumberPage, QString Author, int PublishingYear, QString TypeBook)
        : ISBN(ISBN), BookName(BookName), NumberPage(NumberPage), Author(Author), PublishingYear(PublishingYear), TypeBook(TypeBook) {
    }

    int getISBN() const {
        return ISBN;
    }

    QString getBookName() const {
        return BookName;
    }

    int getNumberPage() const {
        return NumberPage;
    }

    QString getAuthor() const {
        return Author;
    }

    int getPublishingYear() const {
        return PublishingYear;
    }

    QString getTypeBook() const {
        return TypeBook;
    }
    void addBookHB(const ObjBook& book){
        Books.push_back(book);
    }
    const vector<ObjBook>& getBooks() const {
        return Books;
    }

};


class ListHeadBook{
private:
    std::vector<ObjHeadBook> HeadBooks;

public:

    const vector<ObjBook> getBooksfromHeadBook(int ISBN)
    {
        vector<ObjBook> result;

        for (const ObjHeadBook& headBook : HeadBooks) {
            if (headBook.getISBN() == ISBN) {
                result = headBook.getBooks();
                break;
            }
        }

        return result;
    }

    const vector<ObjHeadBook> getHeadBooks()
    {
        return HeadBooks;
    }

    void addHeadBook(const ObjHeadBook& headbook) {

        // Thêm sách mới vào danh sách
        HeadBooks.push_back(headbook);

        // Lưu danh sách vào tệp văn bản
        saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/headbook.txt");
    }

    void loadBooksToHeadBooks(ListBook& listBook) {
        for (ObjHeadBook& headbook : HeadBooks) {
            for (const ObjBook& book : listBook.getBooks()) {
                if (book.getbookname() == headbook.getBookName()) {
                    headbook.addBookHB(book);
                }
            }
        }
    }

    void deleteHeadBook(int ISBN)
    {
        for (auto it = HeadBooks.begin(); it != HeadBooks.end(); ++it) {
            if (it->getISBN() == ISBN) {
                HeadBooks.erase(it);
                saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/headbook.txt");
                break;
            }
        }
    }

    bool FindHeadBookbyISBN(int ISBN)
    {
        for (ObjHeadBook& headbook : HeadBooks) {
            if (headbook.getISBN() == ISBN) {
                return true; // Mã ISBN tồn tại trong danh sách
            }
        }
        return false; // Không tìm thấy đầu sách với mã ISBN
    }
    bool FindHeadBookbyBookName(QString BookName)
    {
        for (ObjHeadBook& headbook : HeadBooks) {
            if (headbook.getBookName() == BookName) {
                return true; //
            }
        }
        return false; // Không tìm thấy đầu sách với mã ISBN
    }
    bool FindHeadBookbyAuthor(QString Author)
    {
        for (ObjHeadBook& headbook : HeadBooks) {
            if (headbook.getAuthor() == Author) {
                return true;
            }
        }
        return false; // Không tìm thấy đầu sách với mã ISBN
    }
    bool FindHeadBookbyTypeBook(QString Typebook)
    {
        for (ObjHeadBook& headbook : HeadBooks) {
            if (headbook.getTypeBook() == Typebook) {
                return true;
            }
        }
        return false; // Không tìm thấy đầu sách với mã ISBN
    }

    void uppdateHeadBook(int ISBN, const QString& newBookName, int newNumberPage, const QString& newAuthor, int newPublishingYear, const QString& newTypeBook)
    {
        for (ObjHeadBook& headbook : HeadBooks) {
            if (headbook.getISBN() == ISBN) {
                // Sửa lại thông tin cho đối tượng `headbook`
                headbook = ObjHeadBook(ISBN, newBookName, newNumberPage, newAuthor, newPublishingYear, newTypeBook);

                // Lưu danh sách vào tệp văn bản sau khi đã sửa
                saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/headbook.txt");

                // Đã tìm thấy và sửa xong, thoát khỏi vòng lặp
                break;
            }
        }
    }
    bool loadFromTextFile(const QString& filename) {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            std::cerr << "Không thể mở tệp văn bản" << std::endl;
                return false;
        }

        HeadBooks.clear();

        QTextStream in(&file);

        // Đọc dòng tiêu đề (hàng đầu tiên) để bỏ qua
        QString header = in.readLine();

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList tokens = line.split(",");

            if (tokens.size() == 6) {
                int ISBN = tokens[0].toInt();
                QString BookName = tokens[1];
                int NumberPage = tokens[2].toInt();
                QString Author = tokens[3];
                int PublishingYear = tokens[4].toInt();
                QString TypeBook = tokens[5];

                ObjHeadBook headbook(ISBN, BookName, NumberPage, Author, PublishingYear, TypeBook);
                HeadBooks.push_back(headbook);
            } else {
                std::cerr << "Dòng không hợp lệ: " << line.toStdString() << std::endl;
            }
        }

        file.close();
        return true;
    }

    void saveToTextFile(const QString& filename) {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            std::cerr << "Không thể mở tệp văn bản" << std::endl;
                return;
        }

        QTextStream out(&file);

        // Viết tiêu đề (hàng đầu tiên)
        out << "ISBN,Ten sach,So trang,Tac Gia,Nam xuat ban,The loai\n";

        for (const ObjHeadBook& headbook : HeadBooks) {
            out << headbook.getISBN() << ","
                << headbook.getBookName() << ","
                << headbook.getNumberPage() << ","
                << headbook.getAuthor() << ","
                << headbook.getPublishingYear() << ","
                << headbook.getTypeBook() << "\n";
        }

        file.close();
    }
};

#endif // OBJHEADBOOK_H
