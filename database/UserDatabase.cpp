#include "UserDatabase.h"

UserDatabase::UserDatabase(){
    loadFromFile();
    qDebug() << "Creating demo users...";
    createDemoUsers();
    qDebug() << "Demo users count:" << m_users.size();

    for(const auto& key : m_users.keys()) {
        if(key == "admin" || key == "analyst") {
            qDebug() << key << m_users[key] << "\n";
        }
    }
}

UserDatabase& UserDatabase::instance(){
    static UserDatabase db;
    return db;
}
void UserDatabase::resetDatabase() {
    qDebug() << getFilePath();

    // Clear all users
    m_users.clear();

    // Delete the file
    QFile file(getFilePath());
    if (file.exists()) {
        file.remove();
        qDebug() << "Deleted old database file";
    }

    // Recreate demo users
    createDemoUsers();

    qDebug() << "Database reset complete. Users:" << m_users.keys();
}
bool UserDatabase::authenticate(const QString& username, const QString& password){
    if(!m_users.contains(username)){return false;}

    QJsonObject user = m_users[username].toObject();
    QString storedHash = user["password_hash"].toString();
    QString salt = user["salt"].toString();
    QString computedHash = hashPassword(password, salt);

    if(storedHash == computedHash){
        user["last_login"] = QDateTime::currentDateTime().toString(Qt::ISODate);
        m_users[username] = user;
        saveToFile();
        return true;
    }
    return false;
}


bool UserDatabase::registerUser(const QString& username, const QString& password,
                                const QString& email){

    if(m_users.contains(username)){
        m_lastError = "Username already exists";
        return false;
    }

    if(username.isEmpty() || password.isEmpty()){
        m_lastError = "Username and password required";
        return false;
    }

    if(password.length() < 6){
        m_lastError = "Password must be at least 6 characters";
        return false;
    }else if(!password.contains(QRegularExpression("[!,:+]"))){
        m_lastError = "Password must contains special characters(!,:+)";
        qDebug()<<"Password special characters error:  " <<username;
        return false;
    }


    QString salt = generateSalt();
    QString passwordHash = hashPassword(password, salt);
    QJsonObject user;

    user["username"] = username;
    user["password_hash"] = passwordHash;
    user["salt"] = salt;
    user["email"] = email;
    user["created_at"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    user["last_login"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    user["activities"] = QJsonArray();
    m_users[username] = user;
    saveToFile();

    return true;
 }

bool UserDatabase::changePassword(const QString& username,
                                   const QString& oldPassword,
                                   const QString& newPassword){

    if(!authenticate(username, oldPassword)){
        m_lastError = "Current password is incorrect";
        return false;
    }

    if(newPassword.length() < 6){
        m_lastError = "New password must be at least 6 characters";
        return false;
    }else if(newPassword.contains(QRegularExpression("[!,:+]"))){
        m_lastError = "Password must contains special characters(!,:+)";
        return false;
    }

    QJsonObject user = m_users[username].toObject();
    QString salt = generateSalt();
    user["salt"] = salt;
    user["password_hash"] = hashPassword(newPassword, salt);
    m_users[username] = user;
    saveToFile();
    return true;
}

bool UserDatabase::changeUsername(const QString& oldUsername,
                                  const QString& newUsername,
                                  const QString& password){
    if(!authenticate(oldUsername, password)){
        m_lastError = "Password is incorrect";
        return false;
    }

    if(m_users.contains(newUsername)){
        m_lastError = "Username already exists";
        return false;
    }

    QJsonObject user = m_users[oldUsername].toObject();
    user["username"] = newUsername;
    m_users.remove(oldUsername);
    m_users[newUsername] = user;
    m_currentUser = newUsername;
    saveToFile();

    return true;
}

QString UserDatabase::getCurrentUser()const{return m_currentUser;}

void UserDatabase::setCurrentUser(const QString& username){
    m_currentUser =username;
    loadUserActivities();
}

void UserDatabase::logout(){
    m_currentUser.clear();
    m_userActivities.clear();
}

QString UserDatabase::getLastError()const{return m_lastError;}

void UserDatabase::logActivity(const QString& action, const QString& details){
    if (m_currentUser.isEmpty()){return;}
    QJsonObject activity;
    activity["action"] = action;
    activity["details"] = details;
    activity["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);

    QJsonObject user = m_users[m_currentUser].toObject();
    QJsonArray activities = user["activities"].toArray();
    activities.prepend(activity);

    //I must come back here
    while(activities.size() > 1000){
        activities.removeLast();
    }

    user["activities"] = activities;
    m_users[m_currentUser] = user;
    saveToFile();


    UserActivity act;
    act.action = action;
    act.details = details;
    act.timestamp = QDateTime::currentDateTime();
    m_userActivities.prepend(act);

    if (m_userActivities.size() > 100) {
        m_userActivities.removeLast();
    }
}

QList<UserActivity> UserDatabase::getUserActivities() const{return m_userActivities;}

int UserDatabase::getTotalLogins(){
    if(m_currentUser.isEmpty()){return 0;}

    QJsonObject user = m_users[m_currentUser].toObject();
    QJsonArray activities = user["activities"].toArray();
    int count{0};

    for(const QJsonValue& val : activities){
        if (val.toObject()["action"].toString() == "Login"){
            count++;
        }
    }
    return count;
}

int UserDatabase::getTotalActivities(){
    if(m_currentUser.isEmpty()){return 0;}
    QJsonObject user = m_users[m_currentUser].toObject();
    return user["activities"].toArray().size();
}

QString UserDatabase::getAccountCreatedDate(){
    if(m_currentUser.isEmpty()){return "";}
    QJsonObject user = m_users[m_currentUser].toObject();
    QDateTime created = QDateTime::fromString(user["created_at"].toString(), Qt::ISODate);
    return created.toString("MMM dd, yyyy");

}



void UserDatabase::createDemoUsers(){
    registerUser("admin", "admin123!", "admin@aegis.local");
    registerUser("analyst", "analyst123!", "analyst@aegis.local");
    registerUser("demo", "demo123!", "demo@aegis.local");
}

QString UserDatabase::getFilePath(){
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    return path + "/aegis_users.json";
}

void UserDatabase::loadFromFile(){
    QFile file(getFilePath());
    if(!file.open(QIODevice::ReadOnly)){return;}

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if(doc.isObject()){
        QJsonObject root = doc.object();
        for(const QString& key : root.keys()){
            m_users[key] = root[key];
        }
    }


}

void UserDatabase::saveToFile() {
    QJsonObject root;
    for (auto it = m_users.constBegin(); it != m_users.constEnd(); ++it) {
        root[it.key()] = it.value();
    }

    QJsonDocument doc(root);
    QFile file(getFilePath());
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

void UserDatabase::loadUserActivities(){
    m_userActivities.clear();
    if(m_currentUser.isEmpty()){return;}

    QJsonObject user = m_users[m_currentUser].toObject();
    QJsonArray activities = user["activities"].toArray();

    for(const QJsonValue& val : activities){
        QJsonObject obj = val.toObject();
        UserActivity act;
        act.action = obj["action"].toString();
        act.details = obj["details"].toString();
        act.timestamp = QDateTime::fromString(obj["timestamp"].toString(), Qt::ISODate);

        m_userActivities.append(act);
    }
}



QString UserDatabase::generateSalt() {
    constexpr int saltBytes = 32;
    QByteArray salt(saltBytes, 0);

    for (int i = 0; i < saltBytes; ++i) {
        salt[i] = static_cast<char>(QRandomGenerator::system()->bounded(256));
    }

    return salt.toBase64();
}



QString UserDatabase::hashPassword(const QString &password, const QString &salt){
    const int iterations{600000};
    auto saltResult = QByteArray::fromBase64Encoding(salt.toUtf8());

    if(saltResult.decodingStatus != QByteArray::Base64DecodingStatus::Ok){
        qWarning()<<"Invalid base64 salt";
        return QString();
    }

    QByteArray saltBytes = saltResult.decoded;
    QByteArray passwordBytes = password.toUtf8();

    //Initial hash
    QByteArray hash = QCryptographicHash::hash(saltBytes+passwordBytes, QCryptographicHash::Sha256);

    //Iterations to slow down attacks
    for(int i{1}; i < iterations; ++i ){
        hash = QCryptographicHash::hash(hash + saltBytes + passwordBytes,
        QCryptographicHash::Sha256);
    }

    return QString(hash.toHex());

}
















