#ifndef OBJBOOK_H
#define OBJBOOK_H

#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QString>

using namespace std;


class ObjBook {
private:
    int bookcode;
    QString bookname;
    int bookstatus;
    QString booklocation;

public:
    ObjBook(int bookcode, const QString& bookname, int bookstatus, const QString& booklocation)
        : bookcode(bookcode), bookname(bookname), bookstatus(bookstatus), booklocation(booklocation) {
    }

    int getbookcode() const {
        return bookcode;
    }

    QString getbookname() const {
        return bookname;
    }

    QString getbooklocation() const {
        return booklocation;
    }

    int getbookstatus() const {
        return bookstatus;
    }

    void setlocation(QString location)
    {
        booklocation = location;
    }
};

class ListBook {
private:
    std::vector<ObjBook> books;

public:
    void addBook(const ObjBook& book) {
        books.push_back(book);
        saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/book.txt");
    }


    void removeBook(int bookcode) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getbookcode() == bookcode) {
                books.erase(it);
                saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/book.txt");
                break;
            }
        }
    }

    const std::vector<ObjBook>& getBooks() const {
        return books;
    }

    void updateBookLocation(int bookcode, const QString& newBookLocation) {
        for (ObjBook& book : books) {
            if (book.getbookcode() == bookcode) {
                // Chỉ cập nhật vị trí sách cho đối tượng `book`
                book.setlocation(newBookLocation);

                // Lưu danh sách vào tệp văn bản sau khi đã sửa
                saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/book.txt");

                // Đã tìm thấy và sửa xong, thoát khỏi vòng lặp
                break;
            }
        }
    }

    bool findBook(int bookcode)
    {
        for (const ObjBook& book : books) {
            if (book.getbookcode() == bookcode) {
                return true; // Mã sách tồn tại trong danh sách
            }
        }
        return false; // Không tìm thấy sách với mã tương ứng
    }

    loadFromTextFile(const QString& filename) {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            std::cerr << "Không thể mở tệp văn bản" << std::endl;
                return false;
        }

        books.clear();
        QTextStream in(&file);

        // Đọc dòng tiêu đề (hàng đầu tiên) để bỏ qua
        QString header = in.readLine();

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList tokens = line.split(",");

            if (tokens.size() == 4) {
                int bookcode = tokens[0].toInt();
                QString bookname = tokens[1];
                int bookstatus = tokens[2].toInt();
                QString booklocation = tokens[3];

                ObjBook book(bookcode, bookname, bookstatus, booklocation);
                books.push_back(book);
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
        out<< "Ma Sach,Ten sach,Trang Thai,Vi tri\n";
        for (const ObjBook& book : books) {
            out << book.getbookcode() << ","
                << book.getbookname() << ","
                << book.getbookstatus() << ","
                << book.getbooklocation() << "\n";
        }

        file.close();
    }
};

#endif // OBJBOOK_H
