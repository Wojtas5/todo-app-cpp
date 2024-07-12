#include "RequestHandlerFactory.h"
#include "RootHandler.h"
#include "TodoRequestHandler.h"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;

RequestHandlerFactory::RequestHandlerFactory(TodoDatabase& database) :
    _todo_database(database)
{}

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
        return nullptr;
    }
}
