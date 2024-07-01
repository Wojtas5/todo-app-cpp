#include "Poco/Util/Application.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "RootHandler.h"

using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

void RootHandler::handleRequest(HTTPServerRequest& request,
    HTTPServerResponse& response)
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
