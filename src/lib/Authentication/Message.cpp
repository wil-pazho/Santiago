#include "Message.h"

namespace Santiago{ namespace Authentication
{
    /*
      TODO:
      1) TCPConnection::intReceive cannot be called here...better not make a separate fn for this at all and do at that
      in place. TCPConnection::intReceive uses strtol...this also will not work since we are not parsing the string.
      Instead try int size = *(reinterpret_cast<unsigned*>(string.c_str())) for reading. For writing pls use strncpy
      with reinterpret_cast. Pls make a separate free fn for this

      2) Make a small test program in the src/test/Authentication directory to test this 2 fns.
     */

    ConnectionMessage::ConnectionMessage(const std::string& inputString_)
    {
        int size = inputString_.size();
        std::string typeString = inputString_.substr(0, 4); //substr(4, 4) if no.of bytes is there in inputString_
        std::map<int, MessageType> type;
        type = {{65, MessageType::NEW_USER},
                {66, MessageType::LOGIN_USER},
                {67, MessageType::LOGOUT_USER},
                {68, MessageType::CHANGE_PASS_USER},
                {69, MessageType::CHANGE_PASS_AND_LOGOUT_USER},
                {70, MessageType::VERIFY_USER}};
        int typeNum = *(reinterpret_cast<const unsigned*>(typeString.c_str()));
        _type = type.find(typeNum)->second;
        //if no.of parameters is required
        /*std::string parametersNumString = inputString_.substr(4, 4); //substr(8, 4) if no.of bytes is there in inputString_
          int parameterNum = *(reinterpret_cast<const unsigned*>(parametersNumString.c_str()))*/
        int startPos = 8; //startPos = 12 if no.of bytes is there in inputString_
        while(startPos < size)
        {
            std::string parameterSizeString = inputString_.substr(startPos, 4);            
            int parameterSize = *(reinterpret_cast<const unsigned*>(parameterSizeString.c_str()));
            startPos += 4;
            std::string parameter = inputString_.substr(startPos, parameterSize);
            _parameters.push_back(parameter);
            startPos += parameterSize;
        }
        
    }
      
    std::string ConnectionMessage::getMessageString() const
    {
        std::stringstream messageString;
        std::map<MessageType, int> enumType;
        enumType = {{MessageType::NEW_USER, 65},
                    {MessageType::LOGIN_USER, 66},
                    {MessageType::LOGOUT_USER, 67},
                    {MessageType::CHANGE_PASS_USER, 68},
                    {MessageType::CHANGE_PASS_AND_LOGOUT_USER, 69},
                    {MessageType::VERIFY_USER, 70}};
        int type = enumType.find(_type)->second;
        messageString.write(reinterpret_cast<char*>(&type), sizeof(int));
        int parameterSize = _parameters.size();
        messageString.write(reinterpret_cast<char*>(&parameterSize), sizeof(int));
        for(auto it = _parameters.begin(); it != _parameters.end(); ++it)
        {
            int size = (*it).size();
            messageString.write(reinterpret_cast<char*>(&size), sizeof(int));
            messageString << *it; 
        }
        return messageString.str();
    }
}}//closing Santiago::Authentication 
