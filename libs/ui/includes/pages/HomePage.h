#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QApplication>
#include <QDateTime>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QThread>
#include <QTableWidget>
#include <UserDataBase.h>
#include <QPushButton>

struct WindowsEvent {
    QDateTime timestamp;
    QString severity;
    QString type;
    QString hostname;
    QString source;
    QString process;
    QString eventId;
    QString message;
};


class HomePage : public QWidget{
    Q_OBJECT;
public:
    explicit HomePage(QWidget *parent = nullptr);

    void updateUsername(const QString &username);
    QWidget *createSideBar();

private:

    QWidget *sideBar{nullptr};
    QLabel *m_userNameLabel{nullptr};
    QWidget *m_scrollContent{nullptr};
    QVBoxLayout *m_logSourceCombo{nullptr};
    QTableWidget *m_logTable{nullptr};
    QString m_currentLogSource;

    QLabel *m_loginsLabel;
    QLabel *m_actionsLabel;
    QLabel *m_memberLabel;

};

#endif // HOMEPAGE_H
