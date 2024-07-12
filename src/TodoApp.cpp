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
    _todo_database = std::make_unique<TodoDatabase>("todo.db");
    ServerApplication::initialize(self);
}

void TodoApp::uninitialize()
{
    ServerApplication::uninitialize();
}

int TodoApp::main(const std::vector<std::string>& args)
{
    auto port = 9999;
    ServerSocket socket(port);
    HTTPServerParams::Ptr params = new HTTPServerParams;
    params->setMaxQueued(100);
    params->setMaxThreads(std::thread::hardware_concurrency());

    HTTPServer server(new RequestHandlerFactory(*_todo_database), socket, params);
    server.start();
    logger().information(Poco::format("Server started on port %d", port));

    waitForTerminationRequest();

    server.stop();
    logger().information("Server stopped");

    return Application::EXIT_OK;
}
