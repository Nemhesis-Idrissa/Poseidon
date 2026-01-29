#include <includes/mainwindow.h>



void MainWindow::switchToPage(int pageIndex) {
    m_stackedWidget->setCurrentIndex(pageIndex);
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
        setWindowTitle("Aegis Security");
        setMinimumSize(800, 600);

        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
        mainLayout -> setContentsMargins(0,0,0,0);
        mainLayout -> setSpacing(0);


        m_loginPage = new LoginPage(this);
        m_homePage = new HomePage(this);

        //create top navigation bar
        m_topNavBar = new TopNavBar(this);
        mainLayout -> addWidget(m_topNavBar);
        //Hidding nav bar initialy
        m_topNavBar -> setVisible(false);

        //connect navigation signal to page switching
        connect(m_topNavBar, &TopNavBar::navigationRequested, this, &MainWindow::switchToPage);


        m_stackedWidget = new QStackedWidget(this);
        m_stackedWidget -> setObjectName("MainContent");
        m_stackedWidget -> addWidget(m_loginPage);
        m_stackedWidget -> addWidget(m_homePage);
        mainLayout -> addWidget(m_stackedWidget);


        //start with login page
        m_stackedWidget -> setCurrentWidget(m_loginPage);
        connect(m_loginPage, &LoginPage::loginSuccessful, this, &MainWindow::onLoginSuccess);

        setStyleSheet(getStyleSheet());



    }


    void MainWindow::onLoginSuccess(const QString &username){
        m_topNavBar -> setVisible(true);
        m_stackedWidget -> setCurrentWidget(m_homePage);

        qWarning()<<"Connected";
    }


    void MainWindow::onLogout() {
        UserDatabase::instance().logActivity("Logout", "User logged out");
        UserDatabase::instance().logout();
        m_loginPage->clearFields();
        m_topNavBar -> setVisible(false);
        m_stackedWidget->setCurrentWidget(m_loginPage);
    }


    //Must come back here
    QString MainWindow::getStyleSheet() {
        return R"(

            #DashboardPage { background-color: #F3F4F6; }
            #Sidebar { background-color: #1F2937; }
            #LogoSection { background-color: #111827; }
            #SidebarLogo { color: #3B82F6; font-size: 32px; }
            #SidebarBrand { color: #ffffff; font-size: 20px; font-weight: bold; letter-spacing: 2px; }
            #UserSection { background-color: transparent; }
            #UserAvatar { background-color: #3B82F6; color: #ffffff; font-size: 20px; border-radius: 20px; padding: 8px; }
            #UserName { color: #F9FAFB; font-size: 14px; font-weight: 600; }
            #UserRole { color: #9CA3AF; font-size: 12px; }
            #SidebarSectionLabel { color: #6B7280; font-size: 11px; font-weight: 700; padding: 10px 20px; letter-spacing: 1px; }
            #NavItem { background-color: transparent; color: #9CA3AF; border: none; text-align: left; padding: 14px 20px; font-size: 14px; font-weight: 500; }
            #NavItem:hover { background-color: #374151; color: #F9FAFB; }
            #NavItemActive { background-color: #3B82F6; color: #ffffff; border: none; border-left: 4px solid #2563EB; text-align: left; padding: 14px 20px; font-size: 14px; font-weight: 600; }

            #ContentArea { background-color: #F3F4F6; }
            #TopBar { background-color: #ffffff; border-bottom: 1px solid #E5E7EB; }
            #SearchBar { background-color: #F9FAFB; color: #1F2937; border: 1px solid #E5E7EB; border-radius: 10px; padding: 0 16px; font-size: 14px; }
            #SearchBar:focus { background-color: #ffffff; border: 2px solid #3B82F6; }
            #NotificationButton { background-color: #F9FAFB; border: 1px solid #E5E7EB; border-radius: 10px; font-size: 18px; }
            #NotificationButton:hover { background-color: #EFF6FF; border: 1px solid #3B82F6; }
            #ScrollArea { background-color: #F3F4F6; border: none; }
            QScrollBar:vertical { background: #E5E7EB; width: 8px; border-radius: 4px; }
            QScrollBar::handle:vertical { background: #9CA3AF; border-radius: 4px; }
            QScrollBar::handle:vertical:hover { background: #6B7280; }

            #WelcomeLabel { color: #111827; font-size: 26px; font-weight: 700; }
            #DateLabel { color: #6B7280; font-size: 13px; }
            #SectionTitle { color: #111827; font-size: 18px; font-weight: 700; margin-bottom: 10px; }

            #CompactStatsBar { background-color: #ffffff; border-radius: 10px; border: 1px solid #E5E7EB; }
            #CompactStatLabel { color: #6B7280; font-size: 13px; font-weight: 600; }

            #MetricsBar { background-color: transparent; }
            #MetricCard { background-color: #ffffff; border-radius: 10px; border: 1px solid #E5E7EB; }
            #MetricIcon { font-size: 28px; }
            #MetricValue { font-size: 22px; font-weight: 700; }
            #MetricLabel { color: #6B7280; font-size: 12px; }

            #EventChart { background-color: #1E293B; border: 1px solid #334155; border-radius: 10px; }

            #ControlLabel { color: #374151; font-size: 14px; font-weight: 600; }
            #LogSourceCombo { background-color: #ffffff; border: 1px solid #E5E7EB; border-radius: 6px; padding: 8px 12px; font-size: 14px; }

            #LogTable { background-color: #ffffff; border: 1px solid #E5E7EB; border-radius: 8px; gridline-color: #E5E7EB; font-size: 12px; }
            #LogTable::item { padding: 6px; border-bottom: 1px solid #F3F4F6; }
            #LogTable::item:selected { background-color: #DBEAFE; color: #1F2937; }
            QHeaderView::section { background-color: #F9FAFB; color: #374151; padding: 10px; border: none; border-bottom: 2px solid #E5E7EB; font-weight: 600; font-size: 12px; }

            #SettingsDialog { background-color: #ffffff; }
            #DialogTitle { color: #111827; font-size: 24px; font-weight: 700; }
            #SectionHeader { color: #374151; font-size: 16px; font-weight: 700; margin-top: 10px; }
            #DialogLabel { color: #6B7280; font-size: 13px; font-weight: 600; }
            #DialogValue { color: #111827; font-size: 14px; font-weight: 600; margin-bottom: 10px; }
            #DialogInput { background-color: #F9FAFB; color: #1F2937; border: 2px solid #E5E7EB; border-radius: 6px; padding: 10px 12px; font-size: 14px; }
            #DialogInput:focus { background-color: #ffffff; border: 2px solid #3B82F6; }
            #DialogButton { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #2563eb, stop:1 #3b82f6); color: #ffffff; border: none; border-radius: 6px; padding: 10px; font-size: 14px; font-weight: 600; }
            #DialogButton:hover { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #1d4ed8, stop:1 #2563eb); }
            #DialogCloseButton { background-color: #F3F4F6; color: #374151; border: 1px solid #E5E7EB; border-radius: 6px; padding: 10px; font-size: 14px; font-weight: 600; }
            #DialogCloseButton:hover { background-color: #E5E7EB; }
            #DialogError { font-size: 13px; font-weight: 600; }

            #CardWidget { background-color: #ffffff; border-radius: 12px; }
            #CardWidget[hover="true"] { background-color: #F9FAFB; }
            #CardIcon { color: #3B82F6; font-size: 28px; background-color: #EFF6FF; border-radius: 10px; padding: 8px; }
            #CardStatus { color: #10B981; font-size: 11px; font-weight: 600; background-color: #D1FAE5; padding: 4px 10px; border-radius: 6px; }
            #CardTitle { color: #1F2937; font-size: 16px; font-weight: 600; }
            #CardDescription { color: #6B7280; font-size: 13px; line-height: 1.4; }
        )";
    }


