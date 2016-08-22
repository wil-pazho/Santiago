#ifndef SANTIAGO_AUTHENTICATION_VERIFYUSERFORCOOKIEREQUESTHANDLER_H
#define SANTIAGO_AUTHENTICATION_VERIFYUSERFORCOOKIEREQUESTHANDLER_H

#include "RequestHandlerBase.h"
#include "Database/MariaDBConnections.h"

namespace Santiago{ namespace Authentication
{
    class VerifyUserForCookieRequestHandler:public RequestHandlerBase
    {
    public:
        VerifyUserForCookieRequestHandler(ConnectionServer& connectionServer_
                                          ,const OnCompletedCallbackFn& onCompletedCallbackFn_
                                          ,const ServerMessage& initiatingMessage_);
        virtual void start();
        virtual void handleReplyMessage(const ServerMessage& serverMessage);
        
    private:
        Database::MariaDBConnections _databaseConnector;
    };

}}

#endif
