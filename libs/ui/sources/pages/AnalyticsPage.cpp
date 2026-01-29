#include <includes/pages/AnalyticsPage.h>


Analytics::Analytics(QWidget *parent): QWidget(parent){
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout -> setContentsMargins(60, 60, 60, 60);

    QLabel *title = new QLabel("Analytics", this);
    title->setStyleSheet("font-size: 36px; font-weight: 900; color: #2c2c2c;");

    QLabel *content = new QLabel("View detailed analytics and statistics.", this);
    content->setWordWrap(true);
    content->setStyleSheet("font-size: 16px; color: #666666; margin-top: 20px;");

    layout->addWidget(title);
    layout->addWidget(content);
    layout->addStretch();

}
