#include "intervalbuttons.h"
#include "QHBoxLayout"

IntervalButtons::IntervalButtons(QWidget *pwgt, QTableWidget *pTable):
    QGroupBox("Buttons to chose the interval", pwgt), m_pTable(pTable)
{
    QPushButton* m_pcmdLargeInterval = new QPushButton("Large interval");
    m_pcmdLargeInterval->setObjectName("largeIntervalButton");
    QPushButton* m_pcmdSmallInterval = new QPushButton("Small interval");
    m_pcmdSmallInterval->setObjectName("smallIntervalButton");
    QPushButton* m_pcmdLargeIntervalPresorded = new QPushButton("Large interval pre-sorted in descending order");
    m_pcmdLargeIntervalPresorded->setObjectName("largeIntervalPresortedButton");
    QPushButton* m_pcmdSmallIntervalPresorded = new QPushButton("Small interval pre-sorted in descending order");
    m_pcmdSmallIntervalPresorded->setObjectName("smallIntervalPresortedButton");

    QObject::connect(m_pcmdLargeInterval, &QPushButton::clicked, this, &IntervalButtons::slotButtonClicked);
    QObject::connect(m_pcmdSmallInterval, &QPushButton::clicked, this, &IntervalButtons::slotButtonClicked);
    QObject::connect(m_pcmdLargeIntervalPresorded, &QPushButton::clicked, this, &IntervalButtons::slotButtonClicked);
    QObject::connect(m_pcmdSmallIntervalPresorded, &QPushButton::clicked, this, &IntervalButtons::slotButtonClicked);

    //Layout setup
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(m_pcmdLargeInterval);
    layout->addWidget(m_pcmdSmallInterval);
    layout->addWidget(m_pcmdLargeIntervalPresorded);
    layout->addWidget(m_pcmdSmallIntervalPresorded);
    setLayout(layout);
}

void IntervalButtons::slotButtonClicked() {
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    if (m_lastClickedButton) {
        m_lastClickedButton->setStyleSheet("");
    }

    btn->setStyleSheet("background-color: green;");
    m_lastClickedButton = btn;

    QString buttonName = btn->objectName();

    if (buttonName == "largeIntervalButton") {
        this->setEnabled(false);
        sort_alg::largeInit();
        sort_alg::updateTable(m_pTable);
        this->setEnabled(true);
    } else if (buttonName == "smallIntervalButton") {
        this->setEnabled(false);
        sort_alg::smallInit();
        sort_alg::updateTable(m_pTable);
        this->setEnabled(true);
    } else if (buttonName == "largeIntervalPresortedButton") {
        this->setEnabled(false);
        sort_alg::largeInitPresorted();
        sort_alg::updateTable(m_pTable);
        this->setEnabled(true);
    } else if (buttonName == "smallIntervalPresortedButton") {
        this->setEnabled(false);
        sort_alg::smallInitPresorted();
        sort_alg::updateTable(m_pTable);
        this->setEnabled(true);
    }
    return;
}
