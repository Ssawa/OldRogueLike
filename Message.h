#ifndef MESSAGE_H
#define MESSAGE_H

#include "precompiledheaders.h"

class Message
{
    public:
        Message(std::string message, TCODColor color);

        std::string _message;
        TCODColor _messageColor;
        int _numberOfLines;
};

#endif // MESSAGE_H
