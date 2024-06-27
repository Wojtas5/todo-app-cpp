#include <iostream>
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Util/ServerApplication.h"

class RootHandler : public Poco::Net::HTTPRequestHandler
{
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request,
        Poco::Net::HTTPServerResponse& response)
    {
        Poco::Util::Application& app = Poco::Util::Application::instance();
        app.logger().information("Request from " + request.clientAddress().toString());

        response.setChunkedTransferEncoding(true);
        response.setContentType("text/html");
        std::ostream& ostr = response.send();
        ostr <<
            "<html>"
                "<head>"
                    "<title>HTTP Server powered by POCO C++ Libraries</title>"
                "</head>"
                "<body>"
                    "<p>This is an example of a simple HTML page with one paragraph.</p>"
                "</body>"
            "</html>";
    }
};

class MyRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
    MyRequestHandlerFactory()
    {}

    Poco::Net::HTTPRequestHandler* createRequestHandler(
        const Poco::Net::HTTPServerRequest& request)
    {
        return new RootHandler();
    }
};

class TodoApp : public Poco::Util::ServerApplication
{
protected:
    void initialize(Application& self) override
    {
        ServerApplication::initialize(self);
    }

    void uninitialize() override
    {
        ServerApplication::uninitialize();
    }

    int main(const std::vector<std::string>& args)
    {
        Poco::UInt16 port = 9999;
        Poco::Net::ServerSocket svs(port);
        Poco::Net::HTTPServerParams* pParams = new Poco::Net::HTTPServerParams;
        pParams->setMaxQueued(100);
        pParams->setMaxThreads(16);

        Poco::Net::HTTPServer srv(new MyRequestHandlerFactory, svs, pParams);
        srv.start();
        std::cout << "Server started on port 9999" << std::endl;
        waitForTerminationRequest();
        srv.stop();
        std::cout << "Server stopped" << std::endl;
        return Application::EXIT_OK;
    }
};

int main(int argc, char** argv)
{
    TodoApp app;
    app.run(argc, argv);

    return 0;
}
