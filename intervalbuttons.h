#ifndef INTERVALBUTTONS_H
#define INTERVALBUTTONS_H

#include <QGroupBox>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QTableWidget>

#include "sort_algorithms.h"

class IntervalButtons : public QGroupBox
{
    Q_OBJECT
private:
    QTableWidget* m_pTable;
    QPushButton *m_lastClickedButton = nullptr;

    QPushButton* m_pcmdLargeInterval;
    QPushButton* m_pcmdSmallInterval;
    QPushButton* m_pcmdLargeIntervalPresorted;
    QPushButton* m_pcmdSmallIntervalPresorted;
public:
    IntervalButtons(QWidget* pwgt = 0, QTableWidget* pTable = 0);
public slots:
    void slotButtonClicked();
};

#endif // INTERVALBUTTONS_H
