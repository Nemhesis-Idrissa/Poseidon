#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QApplication>

#include <QIcon>
#include <QTimer>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>

#include <QSizePolicy>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPropertyAnimation>

#include <UserDataBase.h>



class LoginPage : public QWidget{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);

    //copy operations
    LoginPage(const LoginPage&) = delete;
    LoginPage& operator=(const LoginPage&) = delete;

    //Move operations
    LoginPage(LoginPage&&) = delete;
    LoginPage& operator=(LoginPage&&) = delete;

    void clearFields(void);
    QWidget* createFooter(QWidget *parent);
    QWidget* createToggleSection(QWidget *parent);
    QWidget* createUsernameField(QWidget *parent);
    QWidget* createEmailField(QWidget *parent);
    QWidget* createFormHeader(QWidget *parent);
    QWidget* createBrandSection(QWidget *parent);
    QWidget* createSubmitButton(QWidget *parent);
    QWidget* createPasswordRecovery(QWidget *parent);

signals:
    void loginSuccessful(const QString&);

private slots:
    void handleAction(void);
    void toggleMode(void);
    void togglePasswordVisibility(bool);
    void clearErrors(void);
    void showError(QLabel *errorLabel, const QString &message);
    void showSuccess(const QString&);

private:
    //functions

    QWidget* createLeftSide(void);
    QWidget* createRightSide();
    QWidget* createPasswordField(QWidget *parent);
    QWidget* createDemoInfo(QWidget *parent);
    void setupConnections();


    //member variables
    bool m_isLoginMode{true};
    QVBoxLayout *m_formLayout{nullptr};

    QLineEdit *m_usernameInput{nullptr};
    QLineEdit *m_passwordInput{nullptr};
    QLineEdit *m_emailInput{nullptr};


    QPushButton *m_togglePasswordBtn{nullptr};
    QPushButton *m_passwordRecovery{nullptr};
    QPushButton *m_submitButton{nullptr};

    QPushButton *m_modeSwitchButton{nullptr}; //switch between mode sign up-sign in


    QLabel *m_welcomeLabel{nullptr};
    QLabel *m_subtitleLabel{nullptr};
    QLabel *m_emailLabel{nullptr};
    QLabel *m_demoInfo{nullptr};
    QLabel *m_usernameError{nullptr};
    QLabel *m_passwordError{nullptr};
    QLabel *m_generalError{nullptr};
    QLabel *m_toggleText{nullptr};

};


#endif
