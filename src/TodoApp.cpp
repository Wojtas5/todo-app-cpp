#include "Poco/Net/HTTPServer.h"
#include "TodoApp.h"
#include "MyRequestHandlerFactory.h"

using Poco::Net::ServerSocket;
using Poco::Net::HTTPServerParams;
using Poco::Net::HTTPServer;

void TodoApp::initialize(Application& self)
{
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
    params->setMaxThreads(16);

    HTTPServer server(new MyRequestHandlerFactory, socket, params);
    server.start();
    logger().information(Poco::format("Server started on port %d", port));

    waitForTerminationRequest();

    server.stop();
    logger().information("Server stopped");

    return Application::EXIT_OK;
}
