#ifndef FQ
#define FQ

#include "all_defs.h"

class FetchQueue{

    public:
    std::queue<Instruction> FetchQ;
    std::queue<Instruction> dupl_FQ;

    public:
    void print(){
        Instruction current_ins;
        std::cout << " INSTR ID " << std::endl;
        std::cout << "-------------------------------------------------" << std::endl;
        while (!FetchQ.empty()){
            current_ins = FetchQ.front();
            FetchQ.pop();
            dupl_FQ.push(current_ins);
            std::cout << current_ins.ID << std::endl;
        }

        // use dupl to restock FetchQ
        while(!dupl_FQ.empty()){
            FetchQ.push(dupl_FQ.front());
            dupl_FQ.pop();
        }
    }

};

// int main(){
//     FetchQueue fq;
//     fq.FetchQ.push({.ID = 456});
//     fq.FetchQ.push({.ID = 42});
//     fq.FetchQ.push({.ID = 45});
//     fq.print();
// }

#endif