#include <includes/pages/LoginScreen.h>


LoginPage::LoginPage(QWidget* parent) : QWidget(parent) {
    setObjectName("LoginPage");

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Create  sections
    QWidget *leftSide = createLeftSide();
    QWidget *rightSide = createRightSide();

    mainLayout->addWidget(leftSide, 1);
    mainLayout->addWidget(rightSide, 1);

    // Setup connections
    setupConnections();
}

QWidget* LoginPage::createLeftSide() {
    QWidget *leftSide = new QWidget(this);
    leftSide->setObjectName("LoginLeftSide");

    QVBoxLayout *leftLayout = new QVBoxLayout(leftSide);
    leftLayout->setAlignment(Qt::AlignCenter);

    // Add spacer
    QSpacerItem *topSpacer = new QSpacerItem(
        20, 10,
        QSizePolicy::Minimum,
        QSizePolicy::Expanding
        );
    leftLayout->addItem(topSpacer);

    // Add brand section
    QWidget *brandContainer = createBrandSection(leftSide);
    leftLayout->addWidget(brandContainer);

    return leftSide;
}

QWidget* LoginPage::createBrandSection(QWidget *parent) {
    QWidget *brandContainer = new QWidget(parent);
    brandContainer->setObjectName("LoginBrandContainer");
    brandContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QVBoxLayout *brandLayout = new QVBoxLayout(brandContainer);
    brandLayout->setSpacing(5);
    brandLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *aegis = new QLabel("AEGIS", brandContainer);
    aegis->setObjectName("LoginBrandAegis");
    aegis->setAlignment(Qt::AlignCenter);
    brandLayout->addWidget(aegis);

    QLabel *tagline = new QLabel("Monitor Today, Protect Tomorrow.", brandContainer);
    tagline->setObjectName("LoginTagline");
    tagline->setAlignment(Qt::AlignCenter);
    brandLayout->addWidget(tagline);

    return brandContainer;
}

QWidget *LoginPage::createPasswordRecovery(QWidget *parent) {
    m_passwordRecovery = new QPushButton(" Forgot Password?", parent);
    m_passwordRecovery->setObjectName("PasswordRecovery");
    m_passwordRecovery->setFlat(true);
    m_passwordRecovery->setCursor(Qt::PointingHandCursor);

    m_formLayout->addWidget(m_passwordRecovery , 0, Qt::AlignLeft);  // Align to right

    return nullptr;
}

QWidget* LoginPage::createRightSide() {
    QWidget *rightSide = new QWidget(this);
    rightSide->setObjectName("LoginRightSide");

    m_formLayout = new QVBoxLayout(rightSide);
    m_formLayout->setAlignment(Qt::AlignCenter);
    m_formLayout->setContentsMargins(80, 0, 80, 0);

    createFormHeader(rightSide);
    m_formLayout->addSpacing(40);

    //Username
    createUsernameField(rightSide);
    m_formLayout->addSpacing(20);

    //Email
    createEmailField(rightSide);

    //Password
    createPasswordField(rightSide);
    m_formLayout->addSpacing(30);

    //Sign Up - Sign In
    createSubmitButton(rightSide);
    m_formLayout->addSpacing(20);

    //createPasswordRecovery(rightSide);
    //m_formLayout -> addSpacing(20);

    createToggleSection(rightSide);
    m_formLayout->addSpacing(20);

    createDemoInfo(rightSide);
    m_formLayout->addStretch();

    QWidget *footer = createFooter(rightSide);
    m_formLayout->addWidget(footer);

    return rightSide;
}

QWidget* LoginPage::createFormHeader(QWidget *parent) {
    m_welcomeLabel = new QLabel("Aegis Security", parent);
    m_welcomeLabel->setObjectName("LoginWelcome");
    m_welcomeLabel->setAlignment(Qt::AlignCenter);
    m_formLayout->addWidget(m_welcomeLabel);

    m_subtitleLabel = new QLabel("Sign in to your account", parent);
    m_subtitleLabel->setObjectName("LoginSubtitle");
    m_formLayout->addWidget(m_subtitleLabel);

    return nullptr;  // Using m_formLayout directly
}

QWidget* LoginPage::createUsernameField(QWidget *parent) {
    QLabel *usernameLabel = new QLabel("Username", parent);
    usernameLabel->setObjectName("LoginLabel");
    m_formLayout->addWidget(usernameLabel);

    m_usernameInput = new QLineEdit(parent);
    m_usernameInput->setObjectName("LoginInput");
    m_usernameInput->setPlaceholderText("Enter your username");
    m_usernameInput->setFixedHeight(45);
    m_formLayout->addWidget(m_usernameInput);

    m_usernameError = new QLabel("", parent);
    m_usernameError->setObjectName("ErrorMessage");
    m_usernameError->setVisible(false);
    m_formLayout->addWidget(m_usernameError);

    return nullptr;
}

QWidget* LoginPage::createEmailField(QWidget *parent) {
    m_emailLabel = new QLabel("Email (optional)", parent);
    m_emailLabel->setObjectName("LoginLabel");
    m_emailLabel->hide();
    m_formLayout->addWidget(m_emailLabel);

    m_emailInput = new QLineEdit(parent);
    m_emailInput->setObjectName("LoginInput");
    m_emailInput->setPlaceholderText("Enter your email");
    m_emailInput->setFixedHeight(45);
    m_emailInput->hide();
    m_formLayout->addWidget(m_emailInput);

    return nullptr;
}

QWidget* LoginPage::createPasswordField(QWidget *parent) {
    QLabel *passwordLabel = new QLabel("Password", parent);
    passwordLabel->setObjectName("LoginLabel");
    m_formLayout ->addWidget(passwordLabel);

    QWidget *passwordContainer = new QWidget(parent);
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

    //If toggle show password
    m_togglePasswordBtn = new QPushButton(QIcon(":/images/show.png"), "", passwordContainer);
    m_togglePasswordBtn->setObjectName("PasswordToggle");
    m_togglePasswordBtn->setFixedSize(45, 45);
    m_togglePasswordBtn->setCursor(Qt::PointingHandCursor);
    m_togglePasswordBtn->setCheckable(true);

    passwordLayout->addWidget(m_togglePasswordBtn);

    m_formLayout->addWidget(passwordContainer);

    m_passwordError = new QLabel("", parent);
    m_passwordError->setObjectName("ErrorMessage");
    m_passwordError->setVisible(false);
    m_formLayout->addWidget(m_passwordError);

    m_generalError = new QLabel("", parent);
    m_generalError->setObjectName("ErrorMessage");
    m_generalError->setVisible(false);
    m_formLayout->addWidget(m_generalError);

    return passwordContainer;
}

QWidget* LoginPage::createSubmitButton(QWidget *parent) {
    /*  Creates the main form submission button
    Text changes between "Sign In" and "Sign Up" via toggleMode()*/

    m_submitButton = new QPushButton("Sign In",parent); //default state
    m_submitButton->setObjectName("SubmitButton");
    m_submitButton->setFixedHeight(45);
    m_submitButton->setCursor(Qt::PointingHandCursor);
    m_formLayout->addWidget(m_submitButton);

    return nullptr;
}

QWidget* LoginPage::createToggleSection(QWidget *parent) {
    QHBoxLayout *toggleLayout = new QHBoxLayout();

    m_toggleText = new QLabel("Don't have an account?", parent);
    m_toggleText->setObjectName("LoginToggleText");

    m_modeSwitchButton = new QPushButton("Sign Up", parent);
    m_modeSwitchButton->setObjectName("LoginToggleButton");
    m_modeSwitchButton->setCursor(Qt::PointingHandCursor);

    toggleLayout->addWidget(m_toggleText);
    toggleLayout->addWidget(m_modeSwitchButton);
    toggleLayout->addStretch();

    m_formLayout->addLayout(toggleLayout);

    return nullptr;
}

QWidget* LoginPage::createDemoInfo(QWidget *parent) {
    m_demoInfo = new QLabel(
        "You can use these accounts below for testing :\n\n"
        "- admin / admin123!\n"
        "- analyst / analyst123!\n"
        "- demo / demo123!",
        parent
        );

    m_demoInfo->setObjectName("LoginDemoInfo");
    m_formLayout->addWidget(m_demoInfo);

    return nullptr;
}

QWidget* LoginPage::createFooter(QWidget *parent) {
    QWidget *footer = new QWidget(parent);
    footer->setObjectName("LoginFooter");

    QVBoxLayout *footerLayout = new QVBoxLayout(footer);
    footerLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *copyright = new QLabel("© 2026 AEGIS Security. All rights reserved.", footer);
    copyright->setObjectName("CopyrightLabel");
    copyright->setAlignment(Qt::AlignCenter);

    QLabel *attribution = new QLabel(
        "Profile Linkedin <a href='www.linkedin.com/in/idrissa-injai-cybersecurite'>INJAI Idrissa</a> - "
        "<a href='https://github.com/Nemhesis-Idrissa'>GitHub</a>",
        footer
        );

    attribution->setTextFormat(Qt::RichText);
    attribution->setOpenExternalLinks(true);
    attribution->setAlignment(Qt::AlignCenter);
    attribution->setObjectName("AttributionLabel");

    footerLayout->addWidget(copyright);
    footerLayout->addWidget(attribution);

    footer->adjustSize();

    return footer;
}

void LoginPage::setupConnections() {
    connect(m_submitButton,      &QPushButton::clicked,     this, &LoginPage::handleAction);
    connect(m_modeSwitchButton,  &QPushButton::clicked,     this, &LoginPage::toggleMode);
    connect(m_passwordInput,     &QLineEdit::returnPressed, this, &LoginPage::handleAction);
    connect(m_togglePasswordBtn, &QPushButton::toggled,     this, &LoginPage::togglePasswordVisibility);
    connect(m_usernameInput,     &QLineEdit::textChanged,   this, &LoginPage::clearErrors);
    connect(m_passwordInput,     &QLineEdit::textChanged,   this, &LoginPage::clearErrors);
}

void LoginPage::clearFields(){
    m_usernameInput->clear();
    m_passwordInput->clear();
    m_emailInput->clear();
    clearErrors();

}

void LoginPage::handleAction(){
    clearErrors();

    QString username = m_usernameInput -> text().trimmed();
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
        m_welcomeLabel->setText("AEGIS Security");
        m_subtitleLabel->setText("Sign in to your account");
        m_submitButton->setText("Sign In");
        m_toggleText->setText("Don't have an account? ");
        m_modeSwitchButton->setText("Sign Up");
        //m_passwordRecovery -> show();
        m_emailLabel->hide();
        m_emailInput->hide();
        m_demoInfo->show();
    }else{
        m_welcomeLabel->setText("Create Account");
        m_subtitleLabel->setText("Sign up for a new account");
        m_submitButton->setText("Sign Up");
        m_modeSwitchButton->setText("Sign In");
        //m_passwordRecovery ->hide();
        m_emailLabel->show();
        m_toggleText->setText("Already have an account? ");
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
        m_passwordInput->setEchoMode(QLineEdit::Normal);
        m_togglePasswordBtn->setIcon(QIcon(":/images/hide.png"));
    }else{
        m_passwordInput->setEchoMode(QLineEdit::Password);
        m_togglePasswordBtn->setIcon(QIcon(":/images/show.png"));
    }
}

void LoginPage::clearErrors(){
    m_usernameError->setVisible(false);
    m_passwordError->setVisible(false);
    m_generalError->setVisible(false);

}

void LoginPage::showError(QLabel *errorLabel, const QString &message){
    errorLabel->setText(message);
    errorLabel->setVisible(true);

    QPropertyAnimation *animation = new QPropertyAnimation(errorLabel, "pos");
    animation->setDuration(400);
    animation->setLoopCount(1);

    QPoint originalPos = errorLabel -> pos();
    // Shake left and right, then return to original
    animation->setKeyValueAt(0.0, originalPos);                    // Start
    animation->setKeyValueAt(0.1, originalPos + QPoint(-10, 0));  // Left
    animation->setKeyValueAt(0.2, originalPos + QPoint(10, 0));   // Right
    animation->setKeyValueAt(0.3, originalPos + QPoint(-10, 0));  // Left
    animation->setKeyValueAt(0.4, originalPos + QPoint(10, 0));   // Right
    animation->setKeyValueAt(0.5, originalPos + QPoint(-5, 0));   // Small left
    animation->setKeyValueAt(0.6, originalPos + QPoint(5, 0));    // Small right
    animation->setKeyValueAt(1.0, originalPos);                    // End,  back to original


    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void LoginPage::showSuccess(const QString &message){
    m_generalError->setText(message);
    m_generalError->setStyleSheet("QLabel { color: #10B981; font-size: 13px; font-weight: 600; }");
    m_generalError->setVisible(true);
}
