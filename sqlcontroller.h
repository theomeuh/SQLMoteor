#ifndef SQLCONTROLLER_H
#define SQLCONTROLLER_H

#include <QVariant>

class SqlController
{
public:
    static SqlController* Instance();

    /**
     * @brief Add a request to the list of requests to execute
     * @param void
     */
    void addRequest(QString request);

    /**
     * @brief Execute the list of requests
     * @param void
     */
    void executeRequestList();

    /**
     * @brief Show the list of requests
     * @param void
     */
    void showRequestList();


    /**
     * @brief Drop staged requests from the list
     * @param void
     */
    void dropRequestList();

private:
    QStringList requests;

    // for singleton pattern
    static SqlController* m_pInstance;
    SqlController(); // Private so that it can  not be called
    SqlController(SqlController const&);             // copy constructor is private
    SqlController& operator=(SqlController const&);  // assignment operator is private
};

#endif // SQLCONTROLLER_H
