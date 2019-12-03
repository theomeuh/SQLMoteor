#include "dbmanager.h"
#include <QtSql>
#include <QtDebug>

dbManager* dbManager::m_pInstance = nullptr;

dbManager* dbManager::Instance()
    {
       if (!m_pInstance)
       {   // Only allow one instance of class to be generated.
          m_pInstance = new dbManager;
       }
       return m_pInstance;
    }


dbManager::dbManager()
{
    this->db = QSqlDatabase::addDatabase("QSQLITE"); // loading driver
    this->openDb();
}


void dbManager::openDb()
{
    this->db.setDatabaseName("HARDCODED.db"); // name db
    if (! this->db.open()){
        qDebug() << "Unable to open the database.";
    }
}
