#include <iostream>
#include <pthread.h>
#include <string.h>
#include "MyStack.hpp"
using namespace std;

pthread_mutex_t stack_mutex = PTHREAD_MUTEX_INITIALIZER;

ex4::MyStack::MyStack()
{
    ex4::Node *p = NULL;
    this->head = p;
}

void ex4::MyStack::PUSH(char *val)
{
    pthread_mutex_lock(&stack_mutex);
    if (strlen(val) > 1024)
    {
        pthread_mutex_unlock(&stack_mutex);
        throw ::invalid_argument("DEBUG:string size has to be less then 1025.");
    }
    ex4::Node *newnode = (ex4::Node *)MyMemory::my_malloc(sizeof(ex4::Node));
    newnode->data = (char *)MyMemory::my_malloc(strlen(val) + 1);
    strcpy(newnode->data, val);
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
        this->head = this->head->next;
        MyMemory::my_free(temp->data);
        MyMemory::my_free(temp);
    }
    pthread_mutex_unlock(&stack_mutex);
}

char *ex4::MyStack::TOP()
{
    pthread_mutex_lock(&stack_mutex);
    if (this->head == NULL)
    {
        char *ans = (char *)MyMemory::my_malloc(25);
        strcpy(ans, "DEBUG:Stack is empty.");
        pthread_mutex_unlock(&stack_mutex);
        return ans;
    }
    else
    {
        char *ans = (char *)MyMemory::my_malloc(strlen(this->head->data)+10);
        strcpy(ans, "OUTPUT:");
        strcat(ans, this->head->data);
        pthread_mutex_unlock(&stack_mutex);
        return ans;
    }
}