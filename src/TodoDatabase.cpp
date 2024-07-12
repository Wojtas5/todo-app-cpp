#include "Poco/Data/SQLite/Connector.h"
#include "Poco/Data/RecordSet.h"
#include "TodoDatabase.h"

using namespace Poco;
using Poco::Data::Session;

TodoDatabase::TodoDatabase(const std::string& db_name)
{
    Data::SQLite::Connector::registerConnector();
    _session = std::make_unique<Session>("SQLite", db_name);
    initDatabase();
}

TodoDatabase::~TodoDatabase()
{
    Data::SQLite::Connector::unregisterConnector();
}

void TodoDatabase::addTodo(const std::string& title, bool completed)
{
    Data::Statement insert(*_session);
    insert << "INSERT INTO Todo (title, completed) VALUES(?, ?)",
        Data::Keywords::useRef(title),
        Data::Keywords::use(completed),
        Data::Keywords::now;
}

JSON::Array TodoDatabase::getTodos()
{
    Data::Statement select(*_session);
    select << "SELECT id, title, completed FROM Todo",
        Data::Keywords::now;

    Data::RecordSet rs(select);
    JSON::Array resultArray;
    for (auto it = rs.begin(); it != rs.end(); ++it)
    {
        JSON::Object::Ptr obj = new JSON::Object(JSON_PRESERVE_KEY_ORDER);
        obj->set("id", it->get(0).convert<int>());
        obj->set("title", it->get(1).convert<std::string>());
        obj->set("completed", it->get(2).convert<bool>());
        resultArray.add(obj);
    }
    return resultArray;
}

void TodoDatabase::initDatabase()
{
    *_session << "CREATE TABLE IF NOT EXISTS Todo ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "title TEXT, "
        "completed BOOLEAN)",
        Data::Keywords::now;
}
