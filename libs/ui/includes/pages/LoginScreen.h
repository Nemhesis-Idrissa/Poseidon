#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>


class LoginPage : public QWidget{
    Q_OBJECT
public:
    LoginPage(QWidget *parent = nullptr);
    void clearFields(void);

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
    bool m_isLoginMode{true};
    QVBoxLayout *m_formLayout{nullptr};

    QLineEdit *m_usernameInput{nullptr};
    QLineEdit *m_passwordInput{nullptr};
    QLineEdit *m_emailInput{nullptr};

    QPushButton *m_actionButton{nullptr};
    QPushButton *m_toggleButton{nullptr};
    QPushButton *m_togglePasswordBtn{nullptr};

    QLabel *m_welcomeLabel{nullptr};
    QLabel *m_subtitleLabel{nullptr};
    QLabel *m_emailLabel{nullptr};
    QLabel *m_demoInfo{nullptr};
    QLabel *m_usernameError{nullptr};
    QLabel *m_passwordError{nullptr};
    QLabel *m_generalError{nullptr};
};


#endif
