#include <includes/pages/HomePage.h>

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenu>
#include <QStackedWidget>

HomePage::HomePage(QWidget *parent) : QWidget(parent){
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout -> setContentsMargins(0,0,0,0);
    mainLayout -> setSpacing(0);

    QLabel *workInProgress = new QLabel("Works on progress");
    workInProgress -> setAlignment(Qt::AlignCenter);
    workInProgress -> setStyleSheet("font-size: 18px; color: #666;");

}

