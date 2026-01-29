#ifndef ANALYTICSPAGE_H
#define ANALYTICSPAGE_H

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class Analytics : public QWidget{
    Q_OBJECT;
public:
    Analytics() = default;
    explicit Analytics(QWidget *parent = nullptr);
};


#endif
