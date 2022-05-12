#include <iostream>

namespace ex4
{
    class Node
    {
    public:
        std::string data;
        Node *next;
    };

    class MyStack
    {

    private:
        Node *head;

    public:
        MyStack();
        void PUSH(std::string val);
        void POP();
        std::string TOP();
    };
}
