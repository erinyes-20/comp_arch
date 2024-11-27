#ifndef UTILS
#define UTILS

#include "all_defs.h"

int get_optype_latency(int op_type){
    if (op_type == 0) {return 1;}
    else if (op_type == 1) {return 2;}
    else if (op_type == 2) {return 10;}
    else {return 0;}
}

std::vector<Instruction> build_trace_list(std::string trace_path){
    /** Process all lines in trace, assign ID to each instruction
    *  and push into queue with full trace structure */

    std::vector <Instruction> trace_list;

    std::ifstream file(trace_path); 
    std::string line;                    

    if (!file.is_open()) {std::cerr << "Error: Unable to open file.\n";}

    int asgn_ID = 0;
    std::string PC;
    int op_ty;
    int dest_reg;
    int src1_reg;
    int src2_reg;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        if (ss >> PC >> op_ty >> dest_reg >> src1_reg >> src2_reg) {

            trace_list.push_back(Instruction{.ID = asgn_ID, .stg = IF, .PC = PC, 
            .op_type = op_ty, .dest_reg = dest_reg, .src1_reg = src1_reg,
            .src2_reg = src2_reg});
        }
        asgn_ID++;
    }
    file.close();

    return trace_list;
}


void print_trace_list(std::vector<Instruction> trace_list, int N){
    std::cout << "\nID\t" << "STG\t" << "PC\t" << "OP\t" << 
                    "DREG\t" << "SREG1\t" << "SREG2" << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    for (int i=0; i<N; i++){
        std::cout << trace_list[i].ID << "\t" << trace_list[i].stg << "\t" <<
        trace_list[i].PC << "\t" << trace_list[i].op_type << "\t" << 
        trace_list[i].dest_reg << "\t" <<
        trace_list[i].src1_reg << "\t" << trace_list[i].src2_reg << std::endl;
    }
}

#endif