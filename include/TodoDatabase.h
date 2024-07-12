#ifndef TODODATABASE_H
#define TODODATABASE_H

#include <Poco/Data/Session.h>
#include <string>

class TodoDatabase
{
public:
    TodoDatabase(const std::string& db_name);
    ~TodoDatabase();


private:
    void initDatabase();

    Poco::Data::Session _session;
};

#endif // TODODATABASE_H
