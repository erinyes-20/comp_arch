#include <iostream>
#include <fstream>

#include <bits/stdc++.h>
// using namespace std;

#include "all_defs.h"
#include "utils.cpp"

#include "FetchQ.cpp"
#include "DispatchQ.cpp"
#include "ScheduleQ.cpp"
#include "RegStatus.cpp"
#include "ExecutionList.cpp"
#include "PseudoROB.cpp"

int global_time = 0;

template <size_t N, size_t S, size_t N_REGS>
class TomaCPU{

    public: 
    // Actual HW componenents
    FetchQueue FetQ;
    DispatchQ<2*N> DispQ;
    ScheduleQ<S> SchedQ;
    RegStatus<N_REGS> R_Status;
    ExecutionList ExecList;
    Rob Rob;

    // Help units
    std::vector<Instruction> trace_list;
    
    public:

    void pre_fetch(){
        Instruction ins;
        ROB_element ins_record;

        for (int i=0; i<N; i++){
            if (!trace_list.empty()){
                ins = trace_list.front();
                trace_list.erase(trace_list.begin());

                FetQ.FetchQ.push(ins);

                // Inserting ins for the first time in Rob
                ins_record = {.iq = ins, .time_F_in = global_time};
                Rob.insert(ins_record);
            }
        }
    }

    // ---------------------- FETCH ------------------------------
    void fetch(){

        /** Pop inst from FetchQ and insert into DispQ
         * Keep running timer as batches of N fetched
         * Record in ROB the time at insertion as time_D_in of ins and stage as ID
         */
        Instruction ins;
        DQ_element fetched_inst;

        for (int i=0; i<N; i++){
            if (!DispQ.isFull() && !FetQ.FetchQ.empty()){
                ins = FetQ.FetchQ.front();
                FetQ.FetchQ.pop();

                fetched_inst = {.occp = 1, .iq = ins};
                DispQ.enQueue(fetched_inst);

                // ROB update
                Rob.modify_instr_record(ins.ID, "time_D_in", global_time);
                Rob.modify_inst_stage(ins.ID, ID);
                
            }
        }
    }



    // ------------------------- DISPATCH ------------------------

    void dispatch(){
        DQ_element dq_elem;
        SQ_element dispatched_inst;

        // setting a maxcap of N ins to be dispatched
        for (int i=0; i<N; i++){            
            if (!SchedQ.isFull() && !DispQ.isEmpty()){
                
                dq_elem = DispQ.front();
                DispQ.deQueue();

                dispatched_inst.occp = 1;
                dispatched_inst.ins_ID = dq_elem.iq.ID;

                // REGISTER RENAMING
                // R_Status will provide either true reg val (signaling -1) or producer tag
                dispatched_inst.reg1_q = R_Status.get_RegStatus(dq_elem.iq.src1_reg); 
                dispatched_inst.reg2_q = R_Status.get_RegStatus(dq_elem.iq.src2_reg);
                R_Status.set_RegStatus_by_ins(dq_elem.iq.dest_reg, dq_elem.iq.ID);

                SchedQ.insert(dispatched_inst);

                Rob.modify_instr_record(dq_elem.iq.ID, "time_S_in", global_time);
                Rob.modify_inst_stage(dq_elem.iq.ID, IS);

            }
        }
    }



    // ------------------------- ISSUE ------------------------
    void issue(){
        // here the limit N of candidates = max number of HW units, hence we dont over-issue
        std::vector<SQ_element> issue_candidates = SchedQ.get_issue_candidates(N);
        EX_element ex_elem;

        // processing batch of ready instructs
        for (int i=0; i<issue_candidates.size(); i++){
            SchedQ.remove(issue_candidates[i].ins_ID);
            
            ex_elem.ins_ID = issue_candidates[i].ins_ID;
            ex_elem.timer = get_optype_latency(Rob.Rob_map.at(ex_elem.ins_ID).iq.stg);

            ExecList.insert(ex_elem);

            Rob.modify_instr_record(ex_elem.ins_ID, "time_E_in", global_time);
            Rob.modify_inst_stage(ex_elem.ins_ID, EX);

        }
    }


    // ------------------------- WB ------------------------

    void write_back(std::vector<EX_element> done_ins){
        // Write new computed value to Reservation stations (SchedQ) and RegStatus
        
        // CDB to RegStatus 
        for (int i=0; i<N_REGS; i++){
            for (int j=0; j<done_ins.size(); j++){
                if (R_Status.R_Status_arr[i].ins_ID == done_ins[j].ins_ID){
                    R_Status.reset_RegStatus_after_ins(i);
                }
            }
        }

        // CDB to RS 
        for (int i=0; i<S; i++){
            for (int j=0; j<done_ins.size(); j++){
                if (SchedQ.SchedQ[i].reg1_q == done_ins[j].ins_ID){
                    SchedQ.SchedQ[i].reg1_q = -1;
                }
                else if (SchedQ.SchedQ[i].reg2_q == done_ins[j].ins_ID){
                    SchedQ.SchedQ[i].reg2_q = -1;
                }
            }
        }
        
        // ROb update for all done instructs
        for (int i=0; i<done_ins.size(); i++){
            Rob.modify_instr_record(done_ins[i].ins_ID, "time_W_in", global_time);
            Rob.modify_inst_stage(done_ins[i].ins_ID, WB);
        }       
        
    }
    

    // ------------------------- EXECUTE ------------------------
    
    void execute(){
        // decrement and then check for done ins, cycle accuracy
        ExecList.decrement_timers();
        std::vector<EX_element> done_ins = ExecList.remove_completed_ins();

        // move to WB stage - no
        // writeback bypass
        write_back(done_ins);      
    }


    // ------------------------ TESTING ----------------------------
    void single_cycle_ops(){
        execute();
        issue();
        dispatch();
        fetch();
        pre_fetch();
    }

    void dump_state(){
        std::cout << "\n\n --- AT TIME - "<< global_time << "----------\n" << std::endl;
        std::cout << "\n\n--------------- EXEC LIST -----------------\n" << std::endl;
        ExecList.print();
        std::cout << "\n\n--------------- SCHED Q -----------------\n" << std::endl;
        SchedQ.print();
        std::cout << "\n\n--------------- DISPATCH Q -----------------\n" << std::endl;
        DispQ.print();
        std::cout << "\n\n--------------- FETCH Q -----------------\n" << std::endl;
        FetQ.print();
        std::cout << "\n\n--------------- ROB -----------------\n" << std::endl;
        Rob.print();
        std::cout << "\n\n--------------- REG STATUS -----------------\n" << std::endl;
        R_Status.print();
    }

};





int main(){

    /** The big functions dispatch, issue etc
     *  will access the DQ, SQ elements and set their fields appropriately
     *  hence the data of DQ class is DQ and member funcs are get, set
     *  The DQ, SQ classes will implement size checks etc internally
    */  

    // for perl - N = 3, S = 16, N_REGS = 128
    TomaCPU <3, 16, 128> tomaCPU;

    std::string trace_path = "../perl_trace.txt";
    tomaCPU.trace_list = build_trace_list(trace_path);
    // print_trace_list(tomaCPU.trace_list, 5);

    global_time = 0;
    for (int i = 0; i<20; i++){
        tomaCPU.single_cycle_ops();
        // tomaCPU.dump_state();
        global_time++;
    }

    tomaCPU.Rob.print();


    // /** Ideal core loop over each ins in trace_list for CPU sim */
    // while(!tomaCPU.trace_list.empty() && !tomaCPU.ExecList.ExecList.empty()){
    //     tomaCPU.execute();
    //     tomaCPU.issue();
    //     tomaCPU.dispatch();
    //     tomaCPU.fetch();
    //     tomaCPU.pre_fetch();
    //     global_time++;
    // }

    // // Final time values
    // tomaCPU.Rob.print();

    return 0;

}