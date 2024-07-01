#include "Poco/Util/ServerApplication.h"

class TodoApp : public Poco::Util::ServerApplication
{
protected:
    void initialize(Application& self) override;
    void uninitialize() override;
    int main(const std::vector<std::string>& args) override;
};