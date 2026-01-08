#ifndef USERDATABASE_H
#define USERDATABASE_H

#include <QWidget>
#include <QApplication>
#include <QList>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QDir>
#include<QJsonDocument>
#include<QIterator>
#include <QRandomGenerator>
#include <QByteArray>
#include <QCryptographicHash>
#include<QWidget>
#include <QApplication>



struct UserActivity {
    QString action;
    QDateTime timestamp;
    QString details;
};
class UserDatabase{
public:
    static UserDatabase& instance(void);
    bool authenticate(const QString& username, const QString& password);
    bool registerUser(const QString& username,
                    const QString& password,
                    const QString& email="");
    bool changePassword(const QString& username,
                        const QString& oldPassword,
                        const QString& newPassword);
    bool changeUsername(const QString& oldUsername,
                        const QString& newUsername,
                        const QString& password);
    QString getCurrentUser()const;

    void setCurrentUser(const QString& username);
    void logout(void);

    QString getLastError()const;

    void logActivity(const QString& action, const QString& details="");
    QList<UserActivity> getUserActivities()const;
    int getTotalLogins(void);
    int getTotalActivities(void);
    QString getAccountCreatedDate(void);

private:
    UserDatabase();

    void createDemoUsers();
    void loadFromFile();
    void saveToFile();
    void loadUserActivities();
    QString getFilePath();
    QString generateSalt();
    QString hashPassword(const QString& password, const QString& salt);

    QMap<QString, QJsonValue> m_users{};
    QString m_currentUser{};
    QString m_lastError{};
    QList<UserActivity> m_userActivities{};
};

#endif
