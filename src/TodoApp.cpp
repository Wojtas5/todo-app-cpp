#include "Poco/Data/SQLite/Connector.h"
#include "Poco/Net/HTTPServer.h"
#include "TodoApp.h"
#include "RequestHandlerFactory.h"

using Poco::Net::ServerSocket;
using Poco::Net::HTTPServerParams;
using Poco::Net::HTTPServer;

TodoApp::TodoApp()
{}

void TodoApp::initialize(Application& self)
{
    Poco::Data::SQLite::Connector::registerConnector();
    session = std::make_unique<Poco::Data::Session>("SQLite", "todo.db");
    initDatabase();
    ServerApplication::initialize(self);
}

void TodoApp::uninitialize()
{
    Poco::Data::SQLite::Connector::unregisterConnector();
    ServerApplication::uninitialize();
}

int TodoApp::main(const std::vector<std::string>& args)
{
    auto port = 9999;
    ServerSocket socket(port);
    HTTPServerParams::Ptr params = new HTTPServerParams;
    params->setMaxQueued(100);
    params->setMaxThreads(16);

    HTTPServer server(new RequestHandlerFactory, socket, params);
    server.start();
    logger().information(Poco::format("Server started on port %d", port));

    waitForTerminationRequest();

    server.stop();
    logger().information("Server stopped");

    return Application::EXIT_OK;
}

void TodoApp::initDatabase()
{
    *session << "CREATE TABLE IF NOT EXISTS Todo ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "title TEXT, "
        "completed BOOLEAN)",
        Poco::Data::Keywords::now;
}
