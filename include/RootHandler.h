#ifndef ROOTHANDLER_H
#define ROOTHANDLER_H

#include "Poco/Net/HTTPRequestHandler.h"

class RootHandler : public Poco::Net::HTTPRequestHandler
{
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request,
        Poco::Net::HTTPServerResponse& response) override;
};

#endif // ROOTHANDLER_H