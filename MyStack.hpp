
#include <iostream>
#include <string>

using namespace std;

namespace ex4
{
    class Node
    {
    public:
        string data;
        Node *next;
    };

    class Stack
    {

    private:
        Node *head;

    public:
        Stack();
        ~Stack();
        void PUSH(string val);
        void POP();
        void TOP();
    };
}
