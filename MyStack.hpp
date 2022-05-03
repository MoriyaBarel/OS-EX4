#include <iostream>

namespace ex4
{
    class Node
    {
    public:
        std::string data;
        Node *next;
    };

    class Stack
    {

    private:
        Node *head;

    public:
        Stack();
        ~Stack();
        void PUSH(std::string val);
        void POP();
        void TOP();
    };
}
