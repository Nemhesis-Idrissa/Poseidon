#ifndef NAVIGATIONBAR_H
#define NAVIGATIONBAR_H


#include<QWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QPushButton>

class NavigationBar : public QWidget{
    Q_OBJECT
public:
    explicit NavigationBar(QWidget* parent = nullptr);

    // Methods to enable/disable buttons from outside
    void setBackEnabled(bool enabled);
    void setForwardEnabled(bool enabled);
signals:
    void homeClicked(void);
    void searchClicked(void);
    void alertsClicked(void);
    void settingsClicked(void);
    void backClicked(void);
    void forwardClicked(void);



private:

    void setupUI(void);

    QPushButton* m_homeButton{nullptr};
    QPushButton* m_searchButton{nullptr};
    QPushButton* m_alertButton{nullptr};
    QPushButton* m_settingsButton{nullptr};
    QHBoxLayout* m_layout{nullptr};

    QPushButton* m_backButton{nullptr};
    QPushButton* m_forwardButton{nullptr};
};



#endif // NAVIGATIONBAR_H
