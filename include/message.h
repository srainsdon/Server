#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>

using namespace std;

class Message
{
public:
            Message(void *source);
            Message(string msgText = NULL, int msgT = 255);
    void    print_bin(unsigned hBit);
    void    print_char();
protected:
private:
    void    setMessage(void *source, string msgText, int msgT);
    int     type = 0;
    void    *buffer;
    string  msgText;
};

#endif // MESSAGE_H
