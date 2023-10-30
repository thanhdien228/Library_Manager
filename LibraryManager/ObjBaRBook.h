#ifndef OBJBARBOOK_H
#define OBJBARBOOK_H

#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QString>

using namespace std;

class ObjBaRBook{
private:
    int BookCode;
    QString BookBorrowDate;
    QString BookReturnDate;
    int BookStatus;
    int NumberBorrowTime;
    int ReaderID;
public:
    ObjBaRBook(int bookCode, const QString& bookBorrowDate, const QString& bookReturnDate, int bookStatus, int numberBorrowTime, int readerID)
        : BookCode(bookCode), BookBorrowDate(bookBorrowDate), BookReturnDate(bookReturnDate), BookStatus(bookStatus), NumberBorrowTime(numberBorrowTime), ReaderID(readerID) {
    }

    // Phương thức get cho BookCode
    int getBookCode() const {
        return BookCode;
    }

    // Phương thức get cho BookBorrowDate
    QString getBookBorrowDate() const {
        return BookBorrowDate;
    }

    // Phương thức get cho BookReturnDate
    QString getBookReturnDate() const {
        return BookReturnDate;
    }

    // Phương thức get cho BookStatus
    int getBookStatus() const {
        return BookStatus;
    }

    // Phương thức get cho NumberBorrowTime
    int getNumberBorrowTime() const {
        return NumberBorrowTime;
    }

    // Phương thức get cho ReaderID
    int getReaderID() const {
        return ReaderID;
    }


};

class ListBaRBook{
private:
    vector<ObjBaRBook> barbooks;
public:
public:
    // Phương thức thêm BaRBook
    void addBaRBook(const ObjBaRBook& barbook) {
        barbooks.push_back(barbook);
        saveToTextFile("C:/Users/84976/Documents/untitled/databarbooks.txt");
    }

    // Phương thức xóa BaRBook dựa trên BookCode
    void removeBaRBook(int bookCode) {
        for (auto it = barbooks.begin(); it != barbooks.end(); ++it) {
            if (it->getBookCode() == bookCode) {
                barbooks.erase(it);
                saveToTextFile("C:/Users/84976/Documents/untitled/databarbooks.txt");
                break;
            }
        }
    }

    // Phương thức để lưu danh sách BaRBook vào tệp văn bản
    void saveToTextFile(const QString& filename) {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            std::cerr << "Không thể mở tệp văn bản" << std::endl;
                return;
        }

        QTextStream out(&file);
        for (const ObjBaRBook& barbook : barbooks) {
            out << barbook.getBookCode() << ","
                << barbook.getBookBorrowDate() << ","
                << barbook.getBookReturnDate() << ","
                << barbook.getBookStatus() << ","
                << barbook.getNumberBorrowTime() << ","
                << barbook.getReaderID() << "\n";
        }

        file.close();
    }

    // Phương thức để đọc dữ liệu BaRBook từ tệp văn bản
    bool loadFromTextFile(const QString& filename) {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            std::cerr << "Không thể mở tệp văn bản" << std::endl;
                return false;
        }

        barbooks.clear();

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList tokens = line.split(",");

            if (tokens.size() == 6) {
                int bookCode = tokens[0].toInt();
                QString bookBorrowDate = tokens[1];
                QString bookReturnDate = tokens[2];
                int bookStatus = tokens[3].toInt();
                int numberBorrowTime = tokens[4].toInt();
                int readerID = tokens[5].toInt();

                ObjBaRBook barbook(bookCode, bookBorrowDate, bookReturnDate, bookStatus, numberBorrowTime, readerID);
                barbooks.push_back(barbook);
            } else {
                std::cerr << "Dòng không hợp lệ: " << line.toStdString() << std::endl;
            }
        }

        file.close();
        return true;
    }
};


#endif // OBJBARBOOK_H
