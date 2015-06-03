#ifndef MESSAGE_H
#define MESSAGE_H


class Message
{
public:
    Message(void *source);
    void print_bin(unsigned hBit);
    void print_char();
protected:
private:
    int     type = 0;
    void    *buffer;
};

#endif // MESSAGE_H
