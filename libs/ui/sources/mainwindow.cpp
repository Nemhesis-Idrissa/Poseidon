#include <includes/mainwindow.h>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
    {
        setWindowTitle("Aegis Security Platform - Live SIEM");
        setMinimumSize(1600, 900);

        m_stackedWidget = new QStackedWidget(this);
        setCentralWidget(m_stackedWidget);

        m_loginPage = new LoginPage(this);
        //m_dashboardPage = new DashboardPage(this);

        m_stackedWidget->addWidget(m_loginPage);
        //m_stackedWidget->addWidget(m_dashboardPage);

        m_stackedWidget->setCurrentWidget(m_loginPage);

        connect(m_loginPage, &LoginPage::loginSuccessful, this, &MainWindow::onLoginSuccess);
        //connect(m_dashboardPage, &DashboardPage::logoutRequested, this, &MainWindow::onLogout);

        setStyleSheet(getStyleSheet());
    }

    void MainWindow::onLoginSuccess(const QString &username){
        //m_dashboardPage -> updateUsername(username);
        //m_stackedWidget->setCurrentWidget(m_dashboardPage);
        qWarning()<<"Connected";

    }


    void MainWindow::onLogout() {
        UserDatabase::instance().logActivity("Logout", "User logged out");
        UserDatabase::instance().logout();
        m_loginPage->clearFields();
        m_stackedWidget->setCurrentWidget(m_loginPage);
    }


    //Must come back here
    QString MainWindow::getStyleSheet() {
        return R"(
            #LoginPage { background-color: #F3F4F6; }
            #LoginLeftSide { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1e40af, stop:1 #3b82f6); }
            #LoginLeftSide {
                        background-image: url(:/images/login_background.png);
                        background-repeat: no-repeat;
                        background-position: center;
                    }

#LoginBrandContainer {
    /*  Add a dark backdrop */
    background-color: rgba(10, 25, 41, 0.7);
    border-left: 4px solid #3498db;

}


#LoginBrandAegis {

    color: #ffffff;
    font-size: 64px;
    font-weight: 900;
padding:0px;
    letter-spacing: 16px;
    font-family: "Rajdhani", "Orbitron", sans-serif;
    text-transform: uppercase;




}
            #LoginTagline {padding-left: 150px;padding-right: 60px;   color: rgba(255, 255, 255, 0.8); font-size: 16px;  }
            #LoginRightSide { background-color: #ffffff; }
            #LoginWelcome { color: #111827; font-size: 32px; font-weight: bold; }
            #LoginSubtitle { color: #6B7280; font-size: 16px; margin-top: 5px; }
            #LoginLabel { color: #374151; font-size: 14px; font-weight: 600; margin-bottom: 8px; }
            #LoginInput { background-color: #F9FAFB; color: #1F2937; border: 2px solid #E5E7EB; border-radius: 8px; padding: 0 16px; font-size: 14px; }
            #LoginInput:focus { background-color: #ffffff; border: 2px solid #3B82F6; }
            #PasswordContainer { background-color: transparent; }
            #PasswordToggle { background-color: #F9FAFB; border: 2px solid #E5E7EB; border-left: none; border-top-right-radius: 8px; border-bottom-right-radius: 8px; font-size: 18px; }
            #PasswordToggle:hover { background-color: #EFF6FF; }
            #PasswordToggle:checked { background-color: #DBEAFE; }
            #ErrorMessage { color: #EF4444; font-size: 13px; font-weight: 600; margin-top: 5px; }
            #LoginButton { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #2563eb, stop:1 #3b82f6); color: #ffffff; border: none; border-radius: 8px; font-size: 16px; font-weight: 600; }
            #LoginButton:hover { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #1d4ed8, stop:1 #2563eb); }
            #LoginButton:pressed { background: #1e40af; }
            #LoginToggleText { color: #6B7280; font-size: 14px; }
            #LoginToggleButton { background-color: transparent; color: #3B82F6; border: none; font-size: 14px; font-weight: 600; text-decoration: underline; }
            #LoginToggleButton:hover { color: #2563eb; }
            #LoginDemoInfo { color: #6B7280; font-size: 12px; background-color: #F9FAFB; border: 1px solid #E5E7EB; border-radius: 8px; padding: 15px; }


        )";
    }


