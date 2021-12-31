#ifndef Vector_H
#define Vector_H
#include <iostream>



using namespace std;
template <typename Type>
class Vector {
private:
    Type* arr;

    int capacity;

    int current;
    int ptr = 0;


public:


    Vector()
    {
        arr = new Type[1000];
        capacity = 1000;
        current = 0;

    }

    void push(Type data)
    {

        if (current == capacity) {
            //std::cout << "****" << current << std::endl;
            Type* temp = new Type[2 * capacity];

            for (int i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }

        arr[current] = data;
        current++;



        //std::cout << "Vectors push capacity" << current << std::endl;

    }


    void push(Type data, int index)
    {

        if (index == capacity)
            push(data);
        else
            arr[index] = data;
    }

    int get(int index)
    {

        if (index < current)
            return arr[index];
    }


    void pop()
    {
        current--;
    }

    int size()
    {
        return current;
    }

    int getCapacity()
    {
        return capacity;
    }

    int getCurrPtr()
    {
        return ptr;
    }

    void incrementPtr()
    {
        ptr++;
    }
    void resetPtr()
    {
        ptr = 0;
    }

    void decrementPtr()
    {
        ptr--;
    }

  /*  void print()
    {
        for (int i = 0; i < current; i++) {
            arr[i].getActualWord().print();


        }
        std::cout << std::endl;
    }*/
    int getCurrent(){
        return current;
    }
    Type getValueAtCurrent(){
        return arr[current];
    }
    Type& operator[](int i){
        return arr[i];
    }
    void setCurrent(int z){
        current = z;
    }
    bool operator==(Vector obj)
    {
        if(current != obj.current)
            return false;
        for(int i = 0 ; i < current;  i++)
            if(arr[i] != obj.arr[i]) return false;
        return true;
    }

};



#endif
