#ifndef EXL
#define EXL

#include "all_defs.h"

class ExecutionList{

    public:
    std::vector<EX_element> ExecList;
    // size obtained by ExecList.size()

    public:
    // ExecutionList(){}

    void insert(EX_element elem){
        ExecList.push_back(elem);
    }

    void decrement_timers(){
        // Decrement each FU's timer
        for (int i=0; i<ExecList.size(); i++){
            ExecList[i].timer--;
        }
    }

    std::vector<EX_element> remove_completed_ins(){
        std::vector<EX_element> terminated_ins;
        // Poll all elements to find terminated ones

        for (int i=0; i<ExecList.size(); i++){
            if(ExecList[i].timer == 0){
                ExecList.erase(ExecList.begin() + i);
                terminated_ins.push_back(ExecList[i]);
            }
        }        
        return terminated_ins;
    }


    void print(){
        std::cout << "\nINS_ID\t" << "TIMER" << std::endl;
        std::cout << "-------------------------" << std::endl;
        for (int i=0; i<ExecList.size(); i++){
            std::cout << ExecList[i].ins_ID << "\t" << ExecList[i].timer << std::endl;
        }
    }

};




// int main(){
    // Test multiple insertions, cycle behaviour

    // EX_element test1 = {.ins_ID = 23, .timer = 10};
    // EX_element test2 = {.ins_ID = 55, .timer = 2};
    // EX_element test3 = {.ins_ID = 99, .timer = 1};

    // ExecutionList ExList;
    // ExList.print();
    // ExList.insert(test1);
    // ExList.print();
    // ExList.decrement_timer();
    // ExList.print();
    // ExList.insert(test2);
    // ExList.insert(test3);
    // ExList.print();

    // // decrement and then check for done ins, cycle accuracy
    // ExecutionList ExList;
    // ExList.decrement_timers();
    // std::vector<EX_element> done_ins = ExList.remove_completed_ins();
    // std::cout << done_ins.size() << std::endl;
    // ExList.print();

    // move to WB stage - no
    // writeback bypass
    // write_back(done_ins); 
// }



#endif