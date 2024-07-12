#ifndef TODODATABASE_H
#define TODODATABASE_H

#include <Poco/Data/Session.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>
#include <string>

class TodoDatabase
{
public:
    TodoDatabase(const std::string& db_name);
    ~TodoDatabase();

    void addTodo(const std::string& title, bool completed);
    Poco::JSON::Array getTodos();

private:
    void initDatabase();

    std::unique_ptr<Poco::Data::Session> _session;
};

#endif // TODODATABASE_H
