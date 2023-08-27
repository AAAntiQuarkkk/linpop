#include <QMessageBox>
#include <QSqlQuery>
#include <QVariant>
#include <QtDebug>
#include <QSqlError>
#include "database.h"
#include "login.h"

#include <QObject>

quint32 current_userID;

DataDB* DataDB::db = NULL;
DataDB::DataDB() {
    sqldb = QSqlDatabase::addDatabase("QSQLITE");
    sqldb.setDatabaseName("trial.db");

    if (!sqldb.open()) {
        qDebug() << "Error opening database" ;
    }else{
        qDebug() << "connected" ;
    }

    QSqlQuery qry;
    qry.exec("CREATE TABLE users ("
                   "user_id BIGINT PRIMARY KEY NOT NULL UNIQUE,"
                   "password VARCHAR(255) NOT NULL,"
                   "nickname VARCHAR(255) DEFAULT 'default',"
                   "gender INT DEFAULT -1,"
                   "avatar VARCHAR(255) DEFAULT 'null'"
               ")");
    qry.exec("CREATE TABLE friends ("
                   "user_id BIGINT NOT NULL,"
                   "friend_id BIGINT NOT NULL,"
                   "PRIMARY KEY (user_id, friend_id),"
                   "FOREIGN KEY (user_id) REFERENCES users(user_id),"
                   "FOREIGN KEY (friend_id) REFERENCES users(user_id)"
               ")");
    qry.exec("CREATE TABLE message ("
                   "message_id BIGINT PRIMARY KEY NOT NULL,"
                   "sender_id BIGINT NOT NULL,"
                   "receiver_id BIGINT NOT NULL,"
                   "content TEXT NOT NULL,"
                   "time DATETIME(6) NOT NULL,"
                   "FOREIGN KEY (sender_id) REFERENCES users(user_id),"
                   "FOREIGN KEY (receiver_id) REFERENCES users(user_id)"
               ")");
    qry.exec("CREATE TABLE groups ("
                   "group_id BIGINT PRIMARY KEY NOT NULL,"
                   "group_name VARCHAR(255) NOT NULL,"
                   "create_time DATETIME(6) NOT NULL,"
                   "creator_id BIGINT NOT NULL"
               ")");
    qry.exec("CREATE TABLE group_members ("
                   "group_id BIGINT NOT NULL,"
                   "user_id BIGINT NOT NULL,"
                   "PRIMARY KEY (group_id, user_id),"
                   "FOREIGN KEY (group_id) REFERENCES groups(group_id),"
                   "FOREIGN KEY (user_id) REFERENCES users(user_id)"
               ")");
    qry.exec("CREATE TABLE groupMessage ("
                   "message_id BIGINT PRIMARY KEY NOT NULL,"
                   "group_id BIGINT NOT NULL,"
                   "user_id BIGINT NOT NULL,"
                   "content TEXT NOT NULL,"
                   "time DATETIME(6) NOT NULL,"
                   "FOREIGN KEY (group_id) REFERENCES groups(group_id),"
                   "FOREIGN KEY (user_id) REFERENCES users(user_id)"
               ")");
}

DataDB::~DataDB() {
    if (db != NULL) {
        delete db;
    }
}
DataDB* DataDB::GetInstance() {
    if (db == NULL) {
        db = new DataDB;
    }
    return db;
}

bool DataDB::registerUser(const quint32 user_id, const QString& password) {
    QSqlQuery query(db->sqldb);
    query.prepare("INSERT INTO users (user_id, password) VALUES (:user_id, :password)");
    query.bindValue(":user_id", user_id);
    query.bindValue(":password", password);
    if (!query.exec()) {
        qDebug() << "Error registering user:" << query.lastError().text();
        return false;
    }
    return true;
}
/*
bool DataDB::loginUser(const quint32 user_id, const QString& password) {
    QSqlQuery query(db->sqldb);
    query.prepare("SELECT * FROM users WHERE user_id = :user_id AND password = :password ");
    query.bindValue(":user_id", user_id);
    query.bindValue(":password", password);
    if (!query.exec()) {
        qDebug() << "Error logging in";
        return false;
    }

    if (query.next()) {
        qDebug() << "Login successful." ;
        current_userID = user_id;
        login *configWindow = new login;
        configWindow->show();
        return true;
    } else {
        qDebug() << "Login failed. Invalid username or password.";
        return false;
    }
}
*/
void DataDB::addFriendship(quint32 friend_id){
    QSqlQuery query(db->sqldb);
    query.prepare("INSERT INTO friends (user_id, friend_id) VALUES (:user_id, :friend_id)");
    query.bindValue(":user_id", current_userID);
    query.bindValue(":friend_id", friend_id);//添加好友：在输入框中输入好友ID，将输入框内容绑定在friend_id上执行addfriend(friend_id)

    if (!query.exec()) {
        qDebug() << "Error adding friend";
    }
}

void DataDB::deleteFriendship(quint32 friend_id){
    QSqlQuery query(db->sqldb);
    query.prepare("DELETE FROM friends WHERE user_id = :user_id AND friend_id = :friend_id");
    query.bindValue(":user_id", current_userID);
    query.bindValue(":friend_id", friend_id);

    if (!query.exec()) {
        qDebug() << "Error deleting friend";
    }
}

void DataDB::addMsg(quint32 msg_id, quint32 sender_id,quint32 receiver_id,QString Msg,QString Time){

}
