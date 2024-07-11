#include "Poco/Util/ServerApplication.h"
#include "Poco/Data/Session.h"

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

    std::unique_ptr<Poco::Data::Session> session;
};