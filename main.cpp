#include "mainwindow.h"
#include "intervalbuttons.h"

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QApplication>
#include <QHBoxLayout>
#include <QTimer>
#include <QHeaderView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    QTableWidget* pTable = new QTableWidget(6, 5);
    pTable->setObjectName("Table");
    pTable->setVerticalHeaderLabels(QStringList() << "Insertion sort" << "Quick sort" << "Count sort" << "Radix sort" << "Timsort" << "Binary tree sort");
    pTable->setHorizontalHeaderLabels(QStringList() << "10" << "1 000" << "10 000" << "1 000 000" << "100 000 000");
    for (int row = 0; row < pTable->rowCount(); ++row) {
        for (int col = 0; col < pTable->columnCount(); ++col) {
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            pTable->setItem(row, col, item);
        }
    }

    IntervalButtons *pButtons = new IntervalButtons(nullptr, pTable);

    //Layout setup
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(pTable);
    layout->addWidget(pButtons);
    w.setLayout(layout);

    pTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    pTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    w.adjustSize();

    w.show();

    //QTimer::singleShot(0, pButtons->findChild<QPushButton*>("largeIntervalButton"), &QPushButton::click);

    return a.exec();
}
