#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "TodoRequestHandler.h"

using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

TodoRequestHandler::TodoRequestHandler(TodoDatabase& database) :
    _db(database)
{}

void TodoRequestHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
{
}

