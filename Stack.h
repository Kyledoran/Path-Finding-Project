#include <iostream>
#include <cstdlib>
#include "Vector.h"
using namespace std;


#ifndef STACK_H
#define STACK_H


// Define the default capacity of a stack

// A class to represent a stack
template <typename Type>
class Stack {

private:
    int maxSize;

    int top;
public:
    Vector<Type> v;
    Stack() {
        this->maxSize = 1000;
        this->top = -1;
    }

    void push(Type j) {
       //std::cout << "Pushing " << j << "to stack " << std::endl;
            this->v.push(j); //uses vector class push function and increments top
            top++;

    }

    Type pop() {
        if (!(this->isEmpty())) {
            //std::cout << "Popping " << this->v[this->top] << "from stack " << std::endl;
            this->v.pop();
            top--;
            return this->v.operator[](top + 1);
        } else {
            cout << "\nstack is empty0"<< endl;
            cout<<  "StackOverflow "<<endl;
            return 0;
        }
    }

    Type peek() {  //checks top element of the stack and returns it
        if (this->top == -1){

            return 0;
        }
        else
        return this->v[this->top];
    }
    bool isEmpty() { //checks if stack is empty
        return (this->top == -1);
    }

    bool isFull() { //checks if stack is full
        return (this->top == this->maxSize - 1);
    }
    int size(){
        return this->top;
    }
    Type& operator[](int i){
        return this->v.operator[](i);
    }
};
#endif