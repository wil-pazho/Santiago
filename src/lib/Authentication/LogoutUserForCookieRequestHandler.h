#ifndef SANTIAGO_AUTHENTICATION_LOGOUTUSERFORCOOKIEREQUESTHANDLER_H
#define SANTIAGO_AUTHENTICATION_LOGOUTUSERFORCOOKIEREQUESTHANDLER_H

#include "RequestHandlerBase.h"
#include "Database/MariaDBConnections.h"

namespace Santiago{ namespace Authentication
{
    class LogoutUserForCookieRequestHandler:public RequestHandlerBase
    {
    public:
        LogoutUserForCookieRequestHandler(const RequestId& requestId_,
                                          ConnectionServer& connectionServer_,
                                          const OnCompletedCallbackFn& onCompletedCallbackFn_,
                                          const ServerMessage& initiatingMessage_);
        virtual void start();
        virtual void handleReplyMessage(const ServerMessage& serverMessage);
        
    private:
        Database::MariaDBConnections _databaseConnector;
    };

}}

#endif
