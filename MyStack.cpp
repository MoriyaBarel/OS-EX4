#include <iostream>
#include <pthread.h>
#include "MyStack.hpp"
using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

ex4::Stack::Stack()
{
    this->head = new ex4::Node();
    this->head = NULL;
}

ex4::Stack::~Stack()
{
    ex4::Node *curr = this->head;
    Node *prev = NULL;
    while (curr != NULL)
    {
        prev = curr;
        curr = curr->next;
        delete prev;
    }
}

void ex4::Stack::PUSH(string val)
{
    pthread_mutex_lock(&mutex);
    if (val.size() > 1024)
    {
        throw ::invalid_argument("ERROR: string size has to be less then 1025.");
        pthread_mutex_unlock(&mutex);
    }
    ex4::Node *newnode = (ex4::Node *)malloc(sizeof(ex4::Node));
    newnode->data = val;
    newnode->next = this->head;
    this->head = newnode;
    pthread_mutex_unlock(&mutex);
}

void ex4::Stack::POP()
{
    pthread_mutex_lock(&mutex);
    if (this->head == NULL)
        cout << "Stack is empty." << endl;
    else
    {
        this->head = this->head->next;
    }
    pthread_mutex_unlock(&mutex);
}

void ex4::Stack::TOP()
{
    pthread_mutex_lock(&mutex);
    if (this->head == NULL)
        cout << "Stack is empty.";
    else
    {
        cout << "OUTPUT: " << this->head->data << endl;
    }
    pthread_mutex_unlock(&mutex);
}

// int main() {
//     ex4::Stack s;
//     s.PUSH("hi");
//     s.TOP();
//     s.POP();
//     s.TOP();
    
// }