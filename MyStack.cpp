#include <iostream>
#include <pthread.h>
#include "MyStack.hpp"
#include "MyMemory.hpp"
using namespace std;

pthread_mutex_t stack_mutex = PTHREAD_MUTEX_INITIALIZER;

ex4::MyStack::MyStack()
{
    ex4::Node *p = NULL;
    this->head = p;
}

void ex4::MyStack::PUSH(string val)
{
    pthread_mutex_lock(&stack_mutex);
    if (val.size() > 1024)
    {
        pthread_mutex_unlock(&stack_mutex);
        throw ::invalid_argument("DEBUG:string size has to be less then 1025.");
    }
    ex4::Node *newnode = (ex4::Node *)MyMemory::my_malloc(sizeof(ex4::Node));
    newnode->data = val;
    newnode->next = this->head;
    this->head = newnode;
    pthread_mutex_unlock(&stack_mutex);
}

void ex4::MyStack::POP()
{
    pthread_mutex_lock(&stack_mutex);
    if (this->head == NULL)
        cout << "DEBUG:stack is empty." << endl;
    else
    {
        ex4::Node *temp = this->head;
        temp->data = this->head->data;
        this->head = this->head->next;
        MyMemory::my_free(temp);
    }
    pthread_mutex_unlock(&stack_mutex);
}

std::string ex4::MyStack::TOP()
{
    std::string ans;
    pthread_mutex_lock(&stack_mutex);
    if (this->head == NULL)
    {
        pthread_mutex_unlock(&stack_mutex);
        return "DEBUG:Stack is empty.";
    }
    else
    {
        std::string ans = "OUTPUT:" + this->head->data;
        pthread_mutex_unlock(&stack_mutex);
        return ans;
    }
}