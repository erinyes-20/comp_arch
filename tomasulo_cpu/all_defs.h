#ifndef ALL_DEFS
#define ALL_DEFS

#include <iostream>
#include <bits/stdc++.h>
// using namespace std;

enum stage {IF, ID, IS, EX, WB};

// Define global instr struct
typedef struct {
    int ID;
    stage stg;
    std::string PC;
    int op_type;
    int dest_reg;
    int src1_reg;
    int src2_reg;
} Instruction;

Instruction INS_INVALID = {.ID = -1, .PC = "INVALID"};
Instruction INS_INIT_VAL = {.ID = 98};




typedef struct{
    int occp;
    Instruction iq;   
} DQ_element;

DQ_element DQ_INVALID = {.occp = -1, .iq = INS_INVALID};




typedef struct{
    int occp;
    int ins_ID;    
    int reg1_q;
    int reg2_q;   
} SQ_element;

// be careful of initialized values in queues since initializing regq with -1 makes it auto-ready
SQ_element SQ_INVALID = {.occp = -1, .ins_ID= -1, .reg1_q = -1, .reg2_q = -1};





typedef struct {
    int ins_ID;
    int ready;
} RG_element ;




typedef struct{
    int ins_ID;
    int timer;
} EX_element;



typedef struct{
    Instruction iq;
    int time_F_in;
    int time_F_dur;
    int time_D_in;
    int time_D_dur;
    int time_S_in;
    int time_S_dur;
    int time_E_in;
    int time_E_dur;
    int time_W_in;
    int time_W_dur;
} ROB_element;








#endif