#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Data/RecordSet.h"
#include "Poco/JSON/Parser.h"
#include "TodoRequestHandler.h"

using namespace Poco;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;

TodoRequestHandler::TodoRequestHandler(TodoDatabase& database) :
    _db(database)
{}

void TodoRequestHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
{
    if (request.getMethod() == HTTPRequest::HTTP_GET)
    {
        getTodos(response);
    }
    else if (request.getMethod() == HTTPRequest::HTTP_POST)
    {
        addTodo(request, response);
    }
    else
    {
        response.setStatus(HTTPResponse::HTTP_NOT_FOUND);
        response.send();
    }
}

void TodoRequestHandler::addTodo(HTTPServerRequest& request, HTTPServerResponse& response)
{
    JSON::Parser parser;
    Dynamic::Var result = parser.parse(request.stream());
    JSON::Object::Ptr obj = result.extract<JSON::Object::Ptr>();

    std::string title = obj->getValue<std::string>("title");
    bool completed = obj->getValue<bool>("completed");

    _db.addTodo(title, completed);

    response.setStatus(HTTPResponse::HTTP_CREATED);
    response.send();
}

void TodoRequestHandler::getTodos(HTTPServerResponse& response)
{
    JSON::Array todos = _db.getTodos();

    response.setContentType("application/json");
    std::ostream& out = response.send();
    todos.stringify(out);
}
