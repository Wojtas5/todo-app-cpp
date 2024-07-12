#ifndef TODOREQUESTHANDLER_H
#define TODOREQUESTHANDLER_H

#include "Poco/Net/HTTPRequestHandler.h"
#include "TodoDatabase.h"


class TodoRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
    TodoRequestHandler(TodoDatabase& database);
    void handleRequest(Poco::Net::HTTPServerRequest& request,
        Poco::Net::HTTPServerResponse& response) override;

private:

    TodoDatabase& _db;
};

#endif // TODOREQUESTHANDLER_H