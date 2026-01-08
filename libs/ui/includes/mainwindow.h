#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <includes/pages/LoginScreen.h>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QVector>

#include <QMainWindow>
#include <QApplication>
#include <QScreen>
#include <UserDatabase.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
private slots:
    void onLoginSuccess(const QString &username);
    void onLogout();

private:
    QStackedWidget *m_stackedWidget;
    LoginPage *m_loginPage;
    QString getStyleSheet();
};

#endif // MAINWINDOW_H
