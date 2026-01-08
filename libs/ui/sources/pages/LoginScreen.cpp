#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <includes/pages/LoginScreen.h>
#include <UserDataBase.h>
#include <QPropertyAnimation>
#include <QTimer>

LoginPage::LoginPage(QWidget* parent) : QWidget(parent){
    setObjectName("LoginPage");

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout ->setContentsMargins(0, 0, 0, 0);
    mainLayout ->setSpacing(0);

    QWidget *leftSide = new QWidget(this);
    leftSide -> setObjectName("LoginLeftSide");

    QVBoxLayout *leftLayout = new QVBoxLayout(leftSide);
    leftLayout -> setAlignment(Qt::AlignCenter);

    QLabel *bckgroundImageLabel = new QLabel(leftSide);

    QLabel *logo = new QLabel(leftSide);
    logo->setObjectName("LoginLogo");
    logo->setAlignment(Qt::AlignCenter);

    QPixmap logoPixmap(":/images");


    if(!logoPixmap.isNull()){
        qDebug() << "Logo loaded successfully";

        QPixmap scaledLogo = logoPixmap.scaledToHeight(450, Qt::SmoothTransformation);
        logo->setPixmap(scaledLogo);

        leftLayout->addWidget(logo, 0, Qt::AlignCenter);
        leftLayout->addWidget(logo, 0, Qt::AlignHCenter);


    } else {
        qWarning() << "Logo failed to load";

    }

    QWidget *brandContainer = new QWidget(leftSide);
    brandContainer->setObjectName("LoginBrandContainer");

    QVBoxLayout *brandLayout = new QVBoxLayout(brandContainer);
    brandLayout->setSpacing(5);
    brandLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *aegis = new QLabel("AEGIS", brandContainer);
    aegis->setObjectName("LoginBrandAegis");
    aegis->setAlignment(Qt::AlignCenter);
    brandLayout->addWidget(aegis);

    QLabel *tagline = new QLabel("Security Information & Event Management", brandContainer);
    tagline->setObjectName("LoginTagline");
    tagline->setAlignment(Qt::AlignCenter);
    brandLayout->addWidget(tagline);

    QTimer::singleShot(0, [this, brandContainer]() {
        brandContainer->adjustSize();
        brandContainer->move(200, 700);
    });


    mainLayout->addWidget(leftSide, 1);




    // Must create functions later for all of this
    QWidget *rightSide = new QWidget(this);
    rightSide->setObjectName("LoginRightSide");
    m_formLayout = new QVBoxLayout(rightSide);
    m_formLayout->setAlignment(Qt::AlignCenter);
    m_formLayout->setContentsMargins(80, 0, 80, 0);

    m_welcomeLabel = new QLabel("Welcome Back", rightSide);
    m_welcomeLabel->setObjectName("LoginWelcome");
    m_formLayout->addWidget(m_welcomeLabel);

    m_subtitleLabel = new QLabel("Sign in to your account", rightSide);
    m_subtitleLabel->setObjectName("LoginSubtitle");
    m_formLayout->addWidget(m_subtitleLabel);

    m_formLayout->addSpacing(40);

    QLabel *usernameLabel = new QLabel("Username", rightSide);
    usernameLabel->setObjectName("LoginLabel");
    m_formLayout->addWidget(usernameLabel);

    m_usernameInput = new QLineEdit(rightSide);
    m_usernameInput->setObjectName("LoginInput");
    m_usernameInput->setPlaceholderText("Enter your username");
    m_usernameInput->setFixedHeight(45);
    m_formLayout->addWidget(m_usernameInput);

    m_usernameError = new QLabel("", rightSide);
    m_usernameError->setObjectName("ErrorMessage");
    m_usernameError->setVisible(false);
    m_formLayout->addWidget(m_usernameError);

    m_formLayout->addSpacing(20);

    m_emailLabel = new QLabel("Email (optional)", rightSide);
    m_emailLabel->setObjectName("LoginLabel");
    m_emailLabel->hide();
    m_formLayout->addWidget(m_emailLabel);

    m_emailInput = new QLineEdit(rightSide);
    m_emailInput->setObjectName("LoginInput");
    m_emailInput->setPlaceholderText("Enter your email");
    m_emailInput->setFixedHeight(45);
    m_emailInput->hide();
    m_formLayout->addWidget(m_emailInput);

    QLabel *passwordLabel = new QLabel("Password", rightSide);
    passwordLabel->setObjectName("LoginLabel");
    m_formLayout->addWidget(passwordLabel);

    QWidget *passwordContainer = new QWidget(rightSide);
    passwordContainer->setObjectName("PasswordContainer");
    QHBoxLayout *passwordLayout = new QHBoxLayout(passwordContainer);
    passwordLayout->setContentsMargins(0, 0, 0, 0);
    passwordLayout->setSpacing(0);

    m_passwordInput = new QLineEdit(passwordContainer);
    m_passwordInput->setObjectName("LoginInput");
    m_passwordInput->setPlaceholderText("Enter your password");
    m_passwordInput->setEchoMode(QLineEdit::Password);
    m_passwordInput->setFixedHeight(45);
    passwordLayout->addWidget(m_passwordInput);

    m_togglePasswordBtn = new QPushButton("Visible", passwordContainer);
    m_togglePasswordBtn->setObjectName("PasswordToggle");
    m_togglePasswordBtn->setFixedSize(45, 45);
    m_togglePasswordBtn->setCursor(Qt::PointingHandCursor);
    m_togglePasswordBtn->setCheckable(true);
    passwordLayout->addWidget(m_togglePasswordBtn);

    m_formLayout->addWidget(passwordContainer);

    m_passwordError = new QLabel("", rightSide);
    m_passwordError->setObjectName("ErrorMessage");
    m_passwordError->setVisible(false);
    m_formLayout->addWidget(m_passwordError);

    m_generalError = new QLabel("", rightSide);
    m_generalError->setObjectName("ErrorMessage");
    m_generalError->setVisible(false);
    m_formLayout->addWidget(m_generalError);

    m_formLayout->addSpacing(30);

    m_actionButton = new QPushButton("Sign In", rightSide);
    m_actionButton->setObjectName("LoginButton");
    m_actionButton->setFixedHeight(45);
    m_actionButton->setCursor(Qt::PointingHandCursor);
    m_formLayout->addWidget(m_actionButton);

    m_formLayout->addSpacing(20);

    QHBoxLayout *toggleLayout = new QHBoxLayout();
    QLabel *toggleText = new QLabel("Don't have an account?", rightSide);
    toggleText->setObjectName("LoginToggleText");

    m_toggleButton = new QPushButton("Sign Up", rightSide);
    m_toggleButton->setObjectName("LoginToggleButton");
    m_toggleButton->setCursor(Qt::PointingHandCursor);

    toggleLayout->addWidget(toggleText);
    toggleLayout->addWidget(m_toggleButton);
    toggleLayout->addStretch();

    m_formLayout->addLayout(toggleLayout);
    m_formLayout->addSpacing(20);

    m_demoInfo = new QLabel(
        "Demo Accounts:\n"
        "- admin / admin123\n"
        "- analyst / analyst123\n"
        "- demo / demo123",
        rightSide
        );
    m_demoInfo->setObjectName("LoginDemoInfo");
    m_formLayout->addWidget(m_demoInfo);

    m_formLayout->addStretch();

    mainLayout->addWidget(rightSide, 1);

    connect(m_actionButton, &QPushButton::clicked, this, &LoginPage::handleAction);
    connect(m_toggleButton, &QPushButton::clicked, this, &LoginPage::toggleMode);
    connect(m_passwordInput, &QLineEdit::returnPressed, this, &LoginPage::handleAction);
    connect(m_togglePasswordBtn, &QPushButton::toggled, this, &LoginPage::togglePasswordVisibility);
    connect(m_usernameInput, &QLineEdit::textChanged, this, &LoginPage::clearErrors);
    connect(m_passwordInput, &QLineEdit::textChanged, this, &LoginPage::clearErrors);

}

void LoginPage::clearFields(){
    m_usernameInput -> clear();
    m_passwordInput -> clear();
    m_emailInput -> clear();
    clearErrors();

}

void LoginPage::handleAction(){
    clearErrors();

    QString username = m_usernameInput ->text().trimmed();
    QString password = m_passwordInput -> text();

    bool hasError = false;

    if(username.isEmpty()){
        showError(m_usernameError,u8"\u2716 Username is required");
        hasError = true;
    }

    if(password.isEmpty()){
        showError(m_passwordError, u8"\u2716 Password is required");
        hasError = true;
    }

    if (hasError){return;}

    if(m_isLoginMode){
        if (UserDatabase::instance().authenticate(username, password)) {
            UserDatabase::instance().setCurrentUser(username);
            UserDatabase::instance().logActivity("Login", "User logged in successfully");
            emit loginSuccessful(username);
        } else {
            showError(m_generalError, u8"\u2716 Invalid username or password");
            UserDatabase::instance().logActivity("Failed Login Attempt", QString("Failed login for user: %1").arg(username));
            m_passwordInput->setFocus();
            m_passwordInput->selectAll();
        }
    } else {
        if (password.length() < 6) {
            showError(m_passwordError, u8"\u2716 Password must be at least 6 characters");
            return;
        }

        QString email = m_emailInput->text().trimmed();

        if (UserDatabase::instance().registerUser(username, password, email)) {
            showSuccess(u8"\u2714 Account created successfully! You can now sign in.");
            UserDatabase::instance().logActivity("Account Created", QString("New account: %1").arg(username));
            toggleMode();
        } else {
            showError(m_generalError, u8"\u2716 " + UserDatabase::instance().getLastError());
        }
    }
}


void LoginPage::toggleMode(){
    clearErrors();

    m_isLoginMode = !m_isLoginMode;

    if(m_isLoginMode){
        m_welcomeLabel -> setText("Welcome back");
        m_subtitleLabel -> setText("Sign in to your account");
        m_actionButton -> setText("Sign In");
        m_toggleButton -> setText("Sign Up");
        m_emailLabel -> hide();
        m_emailInput -> hide();
        m_demoInfo -> show();
    }else{
        m_welcomeLabel -> setText("Create Account");
        m_subtitleLabel -> setText("Sign up for a new account");
        m_actionButton -> setText("Sign Up");
        m_toggleButton -> setText("Sign In");

        m_emailLabel->show();
        m_emailInput->show();
        m_demoInfo->hide();
    }

    m_usernameInput->clear();
    m_passwordInput->clear();
    m_emailInput->clear();
    m_usernameInput->setFocus();
}


void LoginPage::togglePasswordVisibility(bool show){
    if(show){
        m_passwordInput -> setEchoMode(QLineEdit::Normal);
        m_togglePasswordBtn -> setText("Hide");
    }else{
        m_passwordInput -> setEchoMode(QLineEdit::Password);
        m_togglePasswordBtn -> setText("visible");
    }
}

void LoginPage::clearErrors(){
    m_usernameError -> setVisible(false);
    m_passwordError -> setVisible(false);
    m_generalError -> setVisible(false);

}

void LoginPage::showError(QLabel *errorLabel, const QString &message){
    errorLabel -> setText(message);
    errorLabel -> setVisible(true);

    QPropertyAnimation *animation = new QPropertyAnimation(errorLabel, "pos");
    animation -> setDuration(400);
    animation -> setLoopCount(1);

    QPoint originalPos = errorLabel -> pos();
    animation ->setKeyValueAt(0, originalPos);
    animation -> setKeyValueAt(0.1, originalPos + QPoint(-5, 0));

    animation->setKeyValueAt(0.2, originalPos + QPoint(5, 0));
    animation->setKeyValueAt(0.3, originalPos + QPoint(-5, 0));
    animation->setKeyValueAt(0.4, originalPos + QPoint(5, 0));
    animation->setKeyValueAt(0.5, originalPos);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void LoginPage::showSuccess(const QString &message){
    m_generalError -> setText(message);
    m_generalError->setStyleSheet("QLabel { color: #10B981; font-size: 13px; font-weight: 600; }");
    m_generalError -> setVisible(true);
}
