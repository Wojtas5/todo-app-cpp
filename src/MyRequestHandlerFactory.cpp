#include "MyRequestHandlerFactory.h"
#include "RootHandler.h"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;

HTTPRequestHandler* MyRequestHandlerFactory::createRequestHandler(
    const HTTPServerRequest& request)
{
    return new RootHandler();
}
