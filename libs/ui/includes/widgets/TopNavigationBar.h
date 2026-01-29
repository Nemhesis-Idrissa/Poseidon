#ifndef TOPNAVIGATIONBAR_H
#define TOPNAVIGATIONBAR_H


#include<QWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QMap>

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenu>
#include <QStackedWidget>




class SettingsPage : public QWidget {
    Q_OBJECT
public:
    explicit SettingsPage(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setContentsMargins(60, 60, 60, 60);

        QLabel *title = new QLabel("Settings", this);
        title->setStyleSheet("font-size: 36px; font-weight: 900; color: #2c2c2c;");

        QLabel *content = new QLabel("Configure system settings and preferences.", this);
        content->setWordWrap(true);
        content->setStyleSheet("font-size: 16px; color: #666666; margin-top: 20px;");

        layout->addWidget(title);
        layout->addWidget(content);
        layout->addStretch();
    }
};


class TopNavBar : public QWidget{
    Q_OBJECT

signals:
    void navigationRequested(int pageIndex);

public slots:
    void setActiveButton(int pageIndex);

public:
    explicit TopNavBar(QWidget *parent = nullptr);


    void setupUI();
    void switchToPage(int pageIndex);
    void updateResponsiveLayout(int width);
    void setActiveNavButton(QPushButton *btn);

    QPushButton *createNavButton(const QString &text, int pageIndex);
    QPushButton *createDropdownButton(const QString &text, const QList<QPair<QString, int>> &items);

    QWidget *createTopNavBar();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:

    QPushButton *m_homeBtn      {nullptr};
    QPushButton *m_searchBtn    {nullptr};
    QPushButton *m_analyticsBtn {nullptr};
    QPushButton *m_datasetsBtn  {nullptr};
    QPushButton *m_reportsBtn   {nullptr};
    QPushButton *m_alertsBtn    {nullptr};
    QPushButton *m_dashboardsBtn{nullptr};
    QLineEdit   *m_searchBar;
    QPushButton *m_settingsBtn  {nullptr};

    QPushButton *m_activeNavButton  {nullptr};
    QStackedWidget *m_stackedWidget {nullptr};
    QList<QPushButton*> m_navButtons;

    void smoothSetVisible(QWidget* widget, bool visible);
    void initializeOpacityEffects();
    QMap<QWidget*, QGraphicsOpacityEffect*> m_effects;
};


#endif // TOPNAVIGATIONBAR_H
