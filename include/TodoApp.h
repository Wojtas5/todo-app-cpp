#ifndef TODOAPP_H
#define TODOAPP_H

#include "Poco/Util/ServerApplication.h"
#include "TodoDatabase.h"

class TodoApp : public Poco::Util::ServerApplication
{
public:
    TodoApp();

protected:
    void initialize(Application& self) override;
    void uninitialize() override;
    int main(const std::vector<std::string>& args) override;

private:
    void initDatabase();

    std::unique_ptr<TodoDatabase> _todo_database;
};

#endif // TODOAPP_H