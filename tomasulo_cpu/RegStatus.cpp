#ifndef REGSTATUS
#define REGSTATUS

#include "all_defs.h"

template <size_t N_REGS>
class RegStatus{

    public: 
    // Array of regs
    RG_element R_Status_arr [N_REGS];

    public:
    RegStatus(){
        for (int i=0; i < N_REGS; i++){
            // Initially, all regs ready with value, none dependent on ins
            R_Status_arr[i].ready = 1;  
            R_Status_arr[i].ins_ID = -1;
        }
    }
    
    int get_RegStatus(int src_reg_index){
        // returns the producer ins_ID or returns a signaling -1
        // to show that data ready in reg already

        if (src_reg_index == -1) {return -1;} // instr does not need src_reg
        else return R_Status_arr[src_reg_index].ins_ID;
    }

    void set_RegStatus_by_ins(int reg_index, int ins_ID){
        // setting the reg to be updated by the provided ins_ID

        if (reg_index == -1) {return;} // instr has no dest_reg
        else {
            R_Status_arr[reg_index].ready = 0;
            R_Status_arr[reg_index].ins_ID = ins_ID;
        }
    }


    void reset_RegStatus_after_ins(int reg_index){
        // resetting the reg after ins writes back
        R_Status_arr[reg_index].ready = 1;
        R_Status_arr[reg_index].ins_ID = -1;
    }


    void print(){
        std::cout << "R_Status ready" << "\t" << "R_Status ins_ID" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        for (int i=0; i<N_REGS; i++){
            std::cout << R_Status_arr[i].ready << "\t\t" << R_Status_arr[i].ins_ID << std::endl;
        }
    }

};

// int main(){
//     RegStatus<7> rs;
//     rs.set_RegStatus_by_ins(2, 13);
//     std::cout << " Reg status " << rs.get_RegStatus(2) << std::endl;
//     rs.set_RegStatus_by_ins(3, 11);
//     rs.set_RegStatus_by_ins(5, 34);
//     rs.print();
//     rs.reset_RegStatus_after_ins(5);
//     rs.print();
// }





#endif