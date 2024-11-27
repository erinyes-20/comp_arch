#ifndef ROB
#define ROB

#include "all_defs.h"

class Rob{

    public:
    std::map <int, ROB_element> Rob_map;

    public:
    Rob(){}

    void insert(ROB_element elem){
        Rob_map.insert({elem.iq.ID, elem});
    }

    void modify_instr_record(int ins_ID, std::string field, int value){
        // map.at() method used for inherent protection since it throws out_of_range exception if elem not present
 
        if (field == "time_D_in"){ 
            Rob_map.at(ins_ID).time_D_in = value;
            Rob_map.at(ins_ID).time_F_dur = Rob_map.at(ins_ID).time_D_in - Rob_map.at(ins_ID).time_F_in;
        }

        else if (field == "time_S_in"){ 
            Rob_map.at(ins_ID).time_S_in = value;
            Rob_map.at(ins_ID).time_D_dur = Rob_map.at(ins_ID).time_S_in - Rob_map.at(ins_ID).time_D_in;
        }

        else if (field == "time_E_in"){ 
            Rob_map.at(ins_ID).time_E_in = value;
            Rob_map.at(ins_ID).time_S_dur = Rob_map.at(ins_ID).time_E_in - Rob_map.at(ins_ID).time_S_in;
        }

        else if (field == "time_W_in"){ 
            Rob_map.at(ins_ID).time_W_in = value;
            Rob_map.at(ins_ID).time_E_dur = Rob_map.at(ins_ID).time_W_in - Rob_map.at(ins_ID).time_E_in;
            Rob_map.at(ins_ID).time_W_dur = 1;
        }
            
        
    }

    void modify_inst_stage(int ins_ID, stage stg){
        Rob_map.at(ins_ID).iq.stg = stg;
    }


    void remove(int ins_ID){
        Rob_map.erase(ins_ID);
    }

    void print(){
        std::cout << "\nID\t" << "T_F_IN\t" << "T_F_DUR\t" << 
                                "T_D_IN\t" << "T_D_DUR\t" << 
                                "T_S_IN\t" << "T_S_DUR\t" << 
                                "T_E_IN\t" << "T_E_DUR\t" << 
                                "T_W_IN\t" << "T_W_DUR\t" << std::endl;
        std::cout << "------------------------------------------------------------------------------------------" << std::endl;
        for (auto& x: Rob_map){
            std::cout << x.first << "\t" << x.second.time_F_in << "\t" << x.second.time_F_dur << "\t" << 
                                                x.second.time_D_in << "\t" << x.second.time_D_dur << "\t" <<
                                                x.second.time_S_in << "\t" << x.second.time_S_dur << "\t" <<
                                                x.second.time_E_in << "\t" << x.second.time_E_dur << "\t" <<
                                                x.second.time_W_in << "\t" << x.second.time_W_dur << "\t" <<
                                                std::endl;
        }
    }
    

};

// int main(){

//     ROB_element test1 = {.iq = {.ID = 71}};
//     ROB_element test2 = {.iq = {.ID = 72}};
//     ROB_element test3 = {.iq = {.ID = 73}};

//     Rob rob;
//     // rob.insert(test1);
//     rob.modify_inst_stage(2, ID);
//     // rob.insert(test2);
//     // rob.remove(71);
//     // rob.insert(test3);
//     rob.print();

// }



#endif