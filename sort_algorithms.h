#include <cstdint>
#include <QVector>
#include <QTableWidget>
#include "timer.h"

#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

namespace sort_alg{
enum Rows{
    INSERTION_SORT,
    QUICK_SORT,
    COUNT_SORT,
    RADIX_SORT,
    TIMSORT,
    BIN_TREE_SORT,
};
enum Columns{
    ARRAY10,
    ARRAY1_000,
    ARRAY10_000,
    ARRAY1_000_000,
    ARRAY100_000_000,
};

extern QVector<int> array10;
extern QVector<int> array1_000;
extern QVector<int> array10_000;
extern QVector<int> array1_000_000;
extern QVector<int> array100_000_000;

void largeInit();
void smallInit();
void largeInitPresorted();
void smallInitPresorted();

QPair<bool, double> insertionSort(QVector<int> vector);
QPair<bool, double> quickSort(QVector<int> vector);
QPair<bool, double> countSort(QVector<int> vector);
QPair<bool, double> radixSort(QVector<int> vector);
QPair<bool, double> timsort(QVector<int> vector);
QPair<bool, double> binTreeSort(QVector<int> vector);

void updateTable(QTableWidget *pTable);
}

#endif // SORT_ALGORITHMS_H
