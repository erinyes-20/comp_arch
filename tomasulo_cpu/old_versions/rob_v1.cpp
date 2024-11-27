#ifndef ROB
#define ROB

#include "all_defs.h"

class Rob{

    public:
    std::vector <ROB_element> Rob;

    public:
    void insert(ROB_element elem){
        Rob.push_back(elem);
    }

    void modify_instr_record(int ins_ID, std::string field, int value){
        for (int i=0; i < Rob.size(); i++){
            if (Rob[i].iq.ID == ins_ID){

                if (field == "time_D_in"){ 
                    Rob[i].time_D_in = value;
                    Rob[i].time_F_dur = Rob[i].time_D_in - Rob[i].time_F_in;
                }

                else if (field == "time_S_in"){ 
                    Rob[i].time_S_in = value;
                    Rob[i].time_D_dur = Rob[i].time_S_in - Rob[i].time_D_in;
                }

                else if (field == "time_E_in"){ 
                    Rob[i].time_E_in = value;
                    Rob[i].time_S_dur = Rob[i].time_E_in - Rob[i].time_S_in;
                }

                else if (field == "time_W_in"){ 
                    Rob[i].time_W_in = value;
                    Rob[i].time_E_dur = Rob[i].time_W_in - Rob[i].time_E_in;
                }
            }
        }
    }

    void modify_instr_stage(int ins_ID, stage val){
        
    }


    void remove(int ins_ID){
        for (int i=0; i<Rob.size(); i++){
            if (Rob[i].iq.ID == ins_ID) {Rob.erase(Rob.begin() + i);}
        }
    }

    void print(){
        std::cout << "\nID\t" << "TIME_F_IN\t" << "TIME_F_DUR\t" << 
                                "TIME_D_IN\t" << "TIME_D_DUR\t" << 
                                "TIME_S_IN\t" << "TIME_S_DUR\t" << 
                                "TIME_E_IN\t" << "TIME_E_DUR\t" << 
                                "TIME_W_IN\t" << "TIME_W_DUR\t" << std::endl;
        std::cout << "----------------------------------------------------------" << std::endl;
        for (int i=0; i<Rob.size(); i++){
            std::cout << Rob[i].iq.ID << "\t" << Rob[i].time_F_in << "\t" << Rob[i].time_F_dur <<
                                                Rob[i].time_D_in << "\t" << Rob[i].time_D_dur <<
                                                Rob[i].time_S_in << "\t" << Rob[i].time_S_dur <<
                                                Rob[i].time_E_in << "\t" << Rob[i].time_E_dur <<
                                                Rob[i].time_W_in << "\t" << Rob[i].time_W_dur << 
                                                std::endl;
        }
    }
    

};

// int main(){

//     ROB rob;

// }



#endif