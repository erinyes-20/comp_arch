#ifndef SQ
#define SQ

#include "all_defs.h"

SQ_element SQ_INIT_VAL = {.occp = 0, .ins_ID = 0, .reg1_q = 0, .reg2_q = 0};

// prioritising older ins while picking issue ccandidates
bool compare_IDs (SQ_element sq1, SQ_element sq2){
    return (sq1.ins_ID < sq2.ins_ID);
}

template <size_t N_SQ>
class ScheduleQ{

    public:
    // Elements of SchedQ can be removed from any index for issue to EX
    // hence quick indexed array needed

    SQ_element SchedQ[N_SQ];
    int num_elems;

    public:    
    ScheduleQ(){
        // Initializing all elements of SQ
        num_elems = 0;
        for (int i=0; i<N_SQ; i++){
            SchedQ[i] = SQ_INIT_VAL;
        }
    }

    bool isEmpty() {return (num_elems==0); }    
    bool isFull() {return (num_elems==N_SQ); }

    int find_vacant_index(){
        // Linear scan for vacancy, returns vacant index
        // Else returns -1

        for (int i=0; i<N_SQ; i++){
            if (SchedQ[i].occp == 0) {return i;}
        }
        return -1;
    }

    bool insert(SQ_element elem){
        // placing instruction in reservation station with renamed regs

        int index = find_vacant_index();
        if (index != -1){
            SchedQ[index] = elem;
            num_elems++;
            return true;
        }
        return false;
    }

    int find_instruc(int ins_ID){
        // find index of instruc
        // else return -1

        for (int i=0; i<N_SQ; i++){
            if (SchedQ[i].ins_ID == ins_ID) {return i;}
        }
        return -1;
    }

    bool remove(int ins_ID){
        // track and remove instr with its ID

        int index = find_instruc(ins_ID);
        if (index != -1) {
            SchedQ[index] = SQ_INIT_VAL;
            num_elems--;
            return true;
        }
        return false;            
    }

    void print(){
        std::cout << "SQ occp\t\tSQ instr ID\tSQ s1q\t\tSQ s2q " << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        for (int i=0; i<N_SQ; i++){
            std::cout << SchedQ[i].occp << "\t\t" << SchedQ[i].ins_ID << "\t\t" << 
            SchedQ[i].reg1_q << "\t\t" << SchedQ[i].reg2_q << std::endl;
        }
    }


    std::vector<SQ_element> get_issue_candidates(int N){
        std::vector<SQ_element> issue_candidates;

        // scan over all N_SQ elements for awakened ones
        for (int i=0; i<N_SQ; i++){
            // Ready ins condition
            if (SchedQ[i].occp == 1 &&  SchedQ[i].reg1_q == -1 && SchedQ[i].reg2_q == -1){
                issue_candidates.push_back(SchedQ[i]);
            }
        }

        if (issue_candidates.size() > N){
            sort(issue_candidates.begin(), issue_candidates.end(), compare_IDs);
            issue_candidates.erase(issue_candidates.begin() + N, issue_candidates.end());
        }
        return issue_candidates;
    }
    


};

// int main(){

//     SQ_element SQ_TEST_VAL1 = {.occp = 1, .ins_ID = 42, .reg1_q = 100, .reg2_q = 100};
//     SQ_element SQ_TEST_VAL2 = {.occp = 1, .ins_ID = 2323, .reg1_q = 100, .reg2_q = 100};

//     ScheduleQ<5> sq;
//     sq.insert(SQ_TEST_VAL1);
//     sq.print();
//     sq.insert(SQ_TEST_VAL2);
//     sq.print();
//     sq.remove(42);
//     sq.print();
//     std::cout << "Find inst - " << sq.find_instruc(2323) << std::endl;
//     std::cout << "Vacant index - " << sq.find_vacant_index() << std::endl;

//     // ScheduleQ<5> sq;
//     // sq.get_issue_candidates(5);


// }

#endif