#include "sqlcontroller.h"
#include "QDebug"
#include <QtSql>

#include <iostream>
using namespace std;

SqlController* SqlController::m_pInstance = nullptr;

SqlController* SqlController::Instance()
    {
       if (!m_pInstance)
       {   // Only allow one instance of class to be generated.
          m_pInstance = new SqlController;
       }
       return m_pInstance;
    }

SqlController::SqlController()
{
    QStringList requests = QStringList();
}

void SqlController::addRequest(QString request)
{
    this->requests.append(request);
}

void SqlController::executeRequestList()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // loading driver
    db.setDatabaseName("HARDCODED.db"); // name db
    if (! db.open()){
        cout << "Unable to open the database." << endl;
    }

    for ( const QString &request : this->requests  )
    {
        QSqlQuery query(db);
        query.prepare(request);
        if (! query.exec())
        {
            cout << "Error executing Get query" << endl;
            qDebug() << query.lastError();
        }
    }
    this->dropRequestList();
}

void SqlController::showRequestList()
{
    qDebug() << "#### STAGED REQUESTS";
    for ( const QString &request : this->requests  )
    {
        qDebug() << request;
    }
}

void SqlController::dropRequestList()
{
    this->requests.clear();
}
