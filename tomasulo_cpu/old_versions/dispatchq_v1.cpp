#ifndef DQ
#define DQ

#include "all_defs.h"
#include "CircularQ.cpp"
#include <bits/stdc++.h>


// Methods - insert_in_DQ (w/ checks)
//         - remove_from_DQ (w/ checks)
template <size_t N_DQ>
class DispatchQ{

    public:
    DQ_element DispQ[N_DQ];
    int num_elems;

    public:    
    DispatchQ(){
        // Initializing all elements of DQ
        num_elems = 0;
        for (int i=0; i<N_DQ; i++){
            DispQ[i].occp = 0;
            // DispQ[i].iq = {.ID = 77};
        }
    }

    bool has_space(){return(num_elems < N_DQ);}

    int find_vacant_index(){
        // Linear scan for vacancy
        for (int i=0; i<N_DQ; i++){
            if (DispQ[i].occp == 0) {return i;}
        }
        return -1;
    }

    void insert_into_DQ(Instruction iq){
        int index = this->find_vacant_index();
        DispQ[index] = {.occp = 1, .iq = iq};
        num_elems++;
    }

    int find_instruc(Instruction ins){
        for (int i=0; i<N_DQ; i++){
            if (DispQ[i].iq.ID == ins.ID) {return i;}
        }
        return -1;
    }

    void remove_from_DQ(Instruction ins){
        int index = find_instruc(ins);
        DispQ[index].occp = 0;
        num_elems--;
    }

    void print(){
        std::cout << "DQ occp\t\tDQ instr ID " << std::endl;
        for (int i=0; i<N_DQ; i++){
            std::cout << DispQ[i].occp << "\t\t" << DispQ[i].iq.ID << std::endl;
        }
    }

};



#endif