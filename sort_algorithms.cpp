#include "sort_algorithms.h"
#include <random>
#include <algorithm>
#include "bintreenode.h"

namespace sort_alg{

QVector<int> array10(10);
QVector<int> array1_000(1000);
QVector<int> array10_000(10000);
QVector<int> array1_000_000(1000000);
QVector<int> array100_000_000(100000000);

void fillVector(QVector<int>& vec, std::mt19937& gen, std::uniform_int_distribution<>& distrib) {
    vec.reserve(vec.size());
    for (auto& val : vec) {
        val = distrib(gen);
    }
}

bool isSorted(QVector<int>& vector);
void fillVectorPresorted(QVector<int>& vector, int limit){
    int size = vector.size();
    if(size <= limit){
        vector.reserve(size);
        int step = limit / size;
        int a = step;

        for(int i = 0; i < size; ++i){
            vector[i] = a;
            a += step;
        }
        return;
    }

    vector.resize(0);
    vector.reserve(size);

    int ranges = size / (limit + 1);
    int extra = size % (limit + 1);

    for (int i = 0; i <= limit; ++i) {
        int count = ranges + (i < extra ? 1 : 0);
        for (int j = 0; j < count; ++j) {
            vector.append(i);
        }
    }

    bool isSortedProperly = isSorted(vector);
    if(isSortedProperly){
        qDebug() << "Presorted algoritm works properly";
    }else{
        qDebug() << "Presorted algoritm works wrong";
    }

    return;
}

void largeInit(){

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(0, 1000000);

    fillVector(array10, gen, distrib);
    fillVector(array1_000, gen, distrib);
    fillVector(array10_000, gen, distrib);
    fillVector(array1_000_000, gen, distrib);
    fillVector(array100_000_000, gen, distrib);

    return;
}

void smallInit(){

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(0, 25);

    fillVector(array10, gen, distrib);
    fillVector(array1_000, gen, distrib);
    fillVector(array10_000, gen, distrib);
    fillVector(array1_000_000, gen, distrib);
    fillVector(array100_000_000, gen, distrib);

    return;
}

void largeInitPresorted(){

    const int limit = 1000000;
    fillVectorPresorted(array10, limit);
    fillVectorPresorted(array1_000, limit);
    fillVectorPresorted(array10_000, limit);
    fillVectorPresorted(array1_000_000, limit);
    fillVectorPresorted(array100_000_000, limit);

    return;
}

void smallInitPresorted(){

    const int limit = 25;
    fillVectorPresorted(array10, limit);
    fillVectorPresorted(array1_000, limit);
    fillVectorPresorted(array10_000, limit);
    fillVectorPresorted(array1_000_000, limit);
    fillVectorPresorted(array100_000_000, limit);

    return;
}


void updateTable(QTableWidget* pTable){
    qDebug() << "updateTable start";
    int nRows = pTable->rowCount();
    int nColumns = pTable->columnCount();

    QTableWidgetItem* curr_cell;

    //change background color to yellow
    for(int i = 0; i < nRows; ++i){
        for(int j = 0; j < nColumns; ++j){
            curr_cell = pTable->item(i, j);
            if (curr_cell) {
                curr_cell->setBackground(QColor(Qt::yellow));
            } else {
                qDebug() << "Null item at row" << i << "column" << j;
            }
        }
    }
    for(int i = 0; i < nRows; ++i){
        for(int j = 0; j < nColumns; ++j){
            QPair<bool, double> result;

            QPair<bool, double> (*pFunc)(QVector<int>);
            switch (i) {
            case INSERTION_SORT:
                qDebug() << "Insertion sort";
                pFunc = sort_alg::insertionSort;
                break;
            case QUICK_SORT:
                qDebug() << "Quick sort";
                pFunc = sort_alg::quickSort;
                break;
            case COUNT_SORT:
                qDebug() << "Count sort";
                pFunc = sort_alg::countSort;
                break;
            case RADIX_SORT:
                qDebug() << "Radix sort";
                pFunc = sort_alg::radixSort;
                break;
            case TIMSORT:
                qDebug() << "Tim sort";
                pFunc = sort_alg::timsort;
                break;
            case BIN_TREE_SORT:
                qDebug() << "Bin tree sort";
                pFunc = sort_alg::binTreeSort;
                break;
            }
            switch (j) {
            case ARRAY10:
                qDebug() << "10\n";
                result = pFunc(array10);
                break;
            case ARRAY1_000:
                qDebug() << "1_000\n";
                result = pFunc(array1_000);
                break;
            case ARRAY10_000:
                qDebug() << "10_000\n";
                result = pFunc(array10_000);
                break;
            case ARRAY1_000_000:
                qDebug() << "1_000_000\n";
                result = pFunc(array1_000_000);
                break;
            case ARRAY100_000_000:
                qDebug() << "100_000_000\n";
                result = pFunc(array100_000_000);
                break;
            }
            curr_cell = pTable->item(i, j);
            if(result.first){
                curr_cell->setText(QString::number(result.second));
                curr_cell->setBackground(QColor(qRgb(9,122, 20)));
            }else{
                if(result.second == -1){
                    curr_cell->setText("Too big array for this sorting method");
                    curr_cell->setBackground(QColor(Qt::red));
                }else{
                    curr_cell->setText("Vector wasn't sorted properly");
                    curr_cell->setBackground(QColor(Qt::magenta));
                }
            }
        }
        qDebug() << "cycle was ended\n";
    }
    qDebug() << "calculation was ended\n";
}

bool isSorted(QVector<int>& vector){
    size_t size = vector.size();
    for(int i = 1; i < size; ++i){
        if(vector[i] < vector[i - 1]){
            return false;
        }
    }
    return true;
}

//----------------------------------------------------------------------------------

void insertionSortCalc(QVector<int>& vector, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = vector[i];
        int j = i - 1;
        while (j >= left && vector[j] > temp) {
            vector[j + 1] = vector[j];
            j--;
        }
        vector[j + 1] = temp;
    }
}

QPair<bool,double> insertionSort(QVector<int> vector){
    if(vector.size() > 10000) return QPair<bool, double>(false, -1);
    Timer timer;

    insertionSortCalc(vector, 0, vector.size() - 1);

    double time = timer.elapsed();
    bool isCorrect = isSorted(vector);
    return QPair<bool, double>(isCorrect, time);
}

//----------------------------------------------------------------------------------
void quickSort3Way(QVector<int>& vector, int low, int high) {
    if (low >= high)
        return;

    int mid = low + (high - low) / 2;
    std::swap(vector[low], vector[mid]);
    int pivot = vector[low];

    int lt = low, i = low + 1, gt = high;

    while (i <= gt) {
        if (vector[i] < pivot) {
            std::swap(vector[i], vector[lt]);
            lt++;
            i++;
        } else if (vector[i] > pivot) {
            std::swap(vector[i], vector[gt]);
            gt--;
        } else {
            i++;
        }
    }

    quickSort3Way(vector, low, lt - 1);
    quickSort3Way(vector, gt + 1, high);
}

QPair<bool, double> quickSort(QVector<int> vector) {
    if (vector.size() > 1000000)
        return QPair<bool, double>(false, -1);

    Timer timer;
    quickSort3Way(vector, 0, vector.size() - 1);
    double time = timer.elapsed();
    bool isCorrect = isSorted(vector);
    return QPair<bool, double>(isCorrect, time);
}

//----------------------------------------------------------------------------------

QPair<bool, double> countSort(QVector<int> vector) {
    if (vector.size() > 100000000) return QPair<bool, double>(false, -1);
    Timer timer;
    int maxVal = *std::max_element(vector.begin(), vector.end());
    int minVal = *std::min_element(vector.begin(), vector.end());
    int range = maxVal - minVal + 1;
    size_t size = vector.size();

    if (range > 100000000) return QPair<bool, double>(false, -1);

    QVector<int> output(vector.size());
    output.reserve(vector.size());
    QVector<int> count(range, 0);

    for (int num : vector) {
        count[num - minVal]++;
    }

    for (int i = 1; i < range; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; --i) {
        output[count[vector[i] - minVal] - 1] = vector[i];
        count[vector[i] - minVal]--;
    }

    double time = timer.elapsed();
    bool isCorrect = isSorted(output);
    return QPair<bool, double>(isCorrect, time);
}


//----------------------------------------------------------------------------------
void countSortForRadix(QVector<int>& vector, int exp) {
    QVector<int> output(vector.size());
    int count[256] = {0};

    for (int i = 0; i < vector.size(); i++) {
        count[(vector[i] / exp) % 256]++;
    }

    for (int i = 1; i < 256; i++) {
        count[i] += count[i - 1];
    }

    for (int i = vector.size() - 1; i >= 0; i--) {
        output[count[(vector[i] / exp) % 256] - 1] = vector[i];
        count[(vector[i] / exp) % 256]--;
    }

    for (int i = 0; i < vector.size(); i++) {
        vector[i] = output[i];
    }
}

QPair<bool, double> radixSort(QVector<int> vector) {
    if(vector.size() > 100000000) return QPair<bool, double>(false, -1);
    Timer timer;
    int maxElement = *std::max_element(vector.begin(), vector.end());

    for (int exp = 1; maxElement / exp > 0; exp *= 256) {
        countSortForRadix(vector, exp);
    }

    double time = timer.elapsed();
    bool isCorrect = isSorted(vector);
    return QPair<bool, double>(isCorrect, time);
}


//----------------------------------------------------------------------------------
void merge(QVector<int>& vector, QVector<int>& tempLeft, QVector<int>& tempRight, int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;

    for (int i = 0; i < len1; i++) {
        tempLeft[i] = vector[l + i];
    }
    for (int i = 0; i < len2; i++) {
        tempRight[i] = vector[m + 1 + i];
    }

    int i = 0, j = 0, k = l;
    while (i < len1 && j < len2) {
        if (tempLeft[i] <= tempRight[j]) {
            vector[k] = tempLeft[i];
            i++;
        } else {
            vector[k] = tempRight[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        vector[k] = tempLeft[i];
        k++;
        i++;
    }

    while (j < len2) {
        vector[k] = tempRight[j];
        k++;
        j++;
    }
}

QPair<bool, double> timsort(QVector<int> vector) {
    if (vector.size() > 1000000) return QPair<bool, double>(false, -1);
    Timer timer;
    int n = vector.size();
    const int step = 32;

    QVector<int> tempLeft, tempRight;

    for (int i = 0; i < n; i += step) {
        insertionSortCalc(vector, i, std::min((i + step - 1), (n - 1)));
    }

    for (int size = step; size < n; size = 2 * size) {
        tempLeft.resize(size);
        tempRight.resize(size);
        for (int left = 0; left < n; left += 2 * size) {
            int mid = std::min((left + size - 1), (n - 1));
            int right = std::min((left + 2 * size - 1), (n - 1));

            if (mid < right) {
                merge(vector, tempLeft, tempRight, left, mid, right);
            }
        }
    }

    double time = timer.elapsed();
    bool isCorrect = isSorted(vector);
    return QPair<bool, double>(isCorrect, time);
}



//----------------------------------------------------------------------------------

QPair<bool, double> binTreeSort(QVector<int> vector){
    if(vector.size() > 100000000) return QPair<bool, double>(false, -1);
    Timer timer;

    BinTreeNode* root = nullptr;
    BinTreeNode::vectorToTree(root, vector);

    int size = vector.size();
    vector.resize(0);
    vector.reserve(size);

    BinTreeNode::TreeToVector(root, vector);

    BinTreeNode::deleteTree(root);

    double time = timer.elapsed();
    bool isCorrect = isSorted(vector);
    return QPair<bool, double>(isCorrect, time);
}

}
