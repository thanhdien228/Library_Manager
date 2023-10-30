#ifndef LOADFILETXT_H
#define LOADFILETXT_H

#include <QTableView>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStandardItemModel>
#include <QMessageBox>
#include "ObjHeadbook.h"
#include "ObjBook.h"

class LoadFileTxt {
public:
    static bool loadToTableViewHeadBook(const QString& filename, QTableView* tableView) {
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


};

#endif // LOADFILETXT_H
