#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>

class dbManager
{
public:
    static dbManager* Instance();
    QSqlDatabase db;

    void openDb();

private:

    // for singleton pattern
    static dbManager* m_pInstance;
    dbManager(); // Private so that it can  not be called
    dbManager(dbManager const&);             // copy constructor is private
    dbManager& operator=(dbManager const&);  // assignment operator is private
};

#endif // DBMANAGER_H
