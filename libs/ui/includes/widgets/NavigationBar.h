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
signals:
    void homeCliked(void);
    void searchClicked(void);
    void alertsCliked(void);
    void settingsClicked(void);

private:
    QPushButton* homeButton;
    QPushButton* searchButton;
    QPushButton* alrtsButton;
    QPushButton* settingsButtong;
};



#endif // NAVIGATIONBAR_H
