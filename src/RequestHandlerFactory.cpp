#include "RequestHandlerFactory.h"
#include "RootHandler.h"
#include "TodoRequestHandler.h"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;

HTTPRequestHandler* RequestHandlerFactory::createRequestHandler(
    const HTTPServerRequest& request)
{
    auto uri = request.getURI();
    if (uri == "/")
    {
        return new RootHandler();
    }
    else if (uri == "/todo")
    {
        return new TodoRequestHandler();
    }
}
