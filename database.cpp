#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

QSqlDatabase Database::db;
bool Database::initialized = false;

bool Database::connect()
{
    if (!initialized) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        initialized = true;
    }

    db.setDatabaseName("investments.db");

    if (!db.open()) {
        qDebug() << "DB error:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;
    query.exec(
        "CREATE TABLE IF NOT EXISTS investments ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "asset TEXT,"
        "amount REAL,"
        "price REAL,"
        "date TEXT"
        ")"
        );

    return true;
}
