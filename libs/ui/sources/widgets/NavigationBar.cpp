#include <includes/widgets/NavigationBar.h>

NavigationBar::NavigationBar(QWidget *parent):QWidget(parent){
    setupUI();
}

void NavigationBar::setupUI(){
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(10, 5, 10, 5);

    m_backButton = new QPushButton("<-", this);
    m_forwardButton = new QPushButton("->", this);


    m_homeButton = new QPushButton("Home", this);
    m_alertButton    = new QPushButton("Alerts", this);
    m_searchButton   = new QPushButton("Search", this);
    m_settingsButton = new QPushButton("Settings", this);


    m_layout ->addWidget(m_homeButton);
    m_layout ->addWidget(m_alertButton);
    m_layout ->addWidget(m_searchButton);
    m_layout ->addWidget(m_backButton);
    m_layout ->addWidget(m_forwardButton);

    m_layout ->addStretch();
    m_layout ->addWidget(m_settingsButton);



    QString buttonStyle = "QWidget { background-color: #2c3e50; }"
                          "QPushButton { background-color: #34495e; color: white; border: none; padding: 10px 20px; }"
                          "QPushButton:hover { background-color: #3498db; }";  // Your existing style
    m_backButton->setStyleSheet(buttonStyle);
    m_forwardButton->setStyleSheet(buttonStyle);
    m_homeButton->setStyleSheet(buttonStyle);
    m_searchButton->setStyleSheet(buttonStyle);


    connect(m_backButton, &QPushButton::clicked,
            this, &NavigationBar::backClicked);
    connect(m_forwardButton, &QPushButton::clicked,
            this, &NavigationBar::forwardClicked);
    connect(m_homeButton, &QPushButton::clicked,
            this, &NavigationBar::homeClicked);
    connect(m_searchButton, &QPushButton::clicked,
            this, &NavigationBar::searchClicked);


    m_backButton->setEnabled(false);
    m_forwardButton->setEnabled(false);
}

void NavigationBar::setBackEnabled(bool enabled)
{
    m_backButton->setEnabled(enabled);
}

void NavigationBar::setForwardEnabled(bool enabled)
{
    m_forwardButton->setEnabled(enabled);
}
