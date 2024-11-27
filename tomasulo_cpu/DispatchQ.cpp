#ifndef DQ
#define DQ

#include "all_defs.h"

DQ_element DQ_INIT_VAL = {.occp = 0};

// Methods - insert_in_DQ (w/ checks)
//         - remove_from_DQ (w/ checks)
template <size_t N_DQ>
class DispatchQ{

    public:
    // DispatchQ modeled as a circular buffer due to in order fetch and
    // in order dispatch constraints
    std::vector<DQ_element> buffer;
    int head_index;
    int tail_index;
    int size;
    int capacity;
    
    DispatchQ() {
        buffer.resize(N_DQ, DQ_INIT_VAL);
        head_index=-1;
        tail_index=0;
        size=0;
        capacity=N_DQ;
    }
    
    bool enQueue(DQ_element value) {
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
        // DQ_element x = buffer[head_index];
        // while removing head val, reset that elem to INVALID
        buffer[head_index] = DQ_INVALID;
        head_index = (head_index + 1) % capacity;
        size--;
        return true;
    }
    
    DQ_element front() {
        if(size==0)    return DQ_INVALID;
        else return buffer[head_index];
    }
    
    DQ_element rear() {
        if(size==0)   return DQ_INVALID;
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

    void print(){
        std::cout << "DQ occp\t\tDQ instr ID " << std::endl;
        std::cout << "-------------------------------------------------" << std::endl;
        for (int i=0; i<N_DQ; i++){
            std::cout << buffer[i].occp << "\t\t" << buffer[i].iq.ID << std::endl;
        }
    }

};

// int main(){

//     DQ_element DQ_TEST_VAL = {.occp = 1, .iq = {.ID = 87}};
//     DispatchQ<4> dispq;
//     dispq.print();
//     dispq.enQueue(DQ_TEST_VAL);
//     dispq.print();
//     dispq.enQueue(DQ_TEST_VAL);
//     dispq.print();
//     dispq.deQueue();
//     dispq.print();
//     dispq.enQueue(DQ_TEST_VAL);
//     dispq.print();
    
// }



#endif