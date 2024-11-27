#ifndef CQ
#define CQ

#include <bits/stdc++.h>
#include <iostream>

template <typename T>
class CircularQ {
public:
    std::vector<T> buffer;
    int head_index;
    int tail_index;
    int size;
    int capacity;
    T invalid_val;
    
    CircularQ(int k, T init_val, T in_val) {
        buffer.resize(k, init_val);
        head_index=-1;
        tail_index=0;
        size=0;
        capacity=k;
        invalid_val = in_val;
    }
    
    bool enQueue(T value) {
        if(size==capacity)   return false;
        buffer[tail_index] = value;
        tail_index = (tail_index + 1) % capacity;
        if(head_index==-1){
            head_index=0;
        }
        size++;
        return true;
    }
    
    bool deQueue() {
        if(size==0)   return false;
        T x = buffer[head_index];
        head_index=(head_index + 1) % capacity;
        size--;
        return true;
    }
    
    T Front() {
        if(size==0)    return invalid_val;
        else return buffer[head_index];
    }
    
    T Rear() {
        if(size==0)   return invalid_val;
        if(tail_index==0)   return buffer[capacity-1];
        else return buffer[tail_index-1];
    }
    
    bool isEmpty() {
        if(size==0)   return true;
        else return false;
    }
    
    bool isFull() {
        if(size==capacity)   return true;
        else return false;
    }

    void print_CQ(){
        std::cout << "CircQ pos\tCircQ element" << std::endl;
        int read_index = head_index;
        while(read_index != tail_index){
            std::cout << read_index << "\t" << buffer[read_index].print() << std::endl;
        }
    }
};

#endif

