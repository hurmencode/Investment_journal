#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

class Database {
public:
    static bool connect();

private:
    static QSqlDatabase db;
    static bool initialized;
};

#endif
