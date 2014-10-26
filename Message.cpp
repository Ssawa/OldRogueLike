#include "Message.h"

Message::Message(std::string message, TCODColor color):
_message(message), _messageColor(color), _numberOfLines(0)
{
    //Wraps string text
    for(int i = 0; i < _message.size(); i++)
    {
        if(i% 70 == 0)
        {
            _message.insert(i, "\n");
            _numberOfLines++;
        }
    }
}
