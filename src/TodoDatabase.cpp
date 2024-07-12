#include "Poco/Data/SQLite/Connector.h"
#include "TodoDatabase.h"

TodoDatabase::TodoDatabase(const std::string& db_name)
    : _session("SQLite", db_name)
{
    Poco::Data::SQLite::Connector::registerConnector();
    _session = std::make_unique<Poco::Data::Session>("SQLite", db_name);
    initDatabase();
}

TodoDatabase::~TodoDatabase()
{
    Poco::Data::SQLite::Connector::unregisterConnector();
}


void TodoDatabase::initDatabase()
{
    *_session << "CREATE TABLE IF NOT EXISTS Todo ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "title TEXT, "
        "completed BOOLEAN)",
        Poco::Data::Keywords::now;
}
