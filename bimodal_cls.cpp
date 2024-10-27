#include <iostream>
#include <fstream>
#include <bitset>
#include <sstream>
#include <bits/stdc++.h>
#include <unordered_map>
// using namespace std;

template <size_t m>
class Bimodal_Predictor{

    public:
        const std::string trace_path;
        std::vector<std::bitset<32>>  addresses_vec;  
        std::vector<char> true_br_vec; 
        std::vector<std::bitset<m> > pc_index_vec;
        std::unordered_map <std::bitset<m>, int> hmap;
        std::vector<char> preds_vec;

    public:
        Bimodal_Predictor(std::string path_val) : trace_path(path_val) {}

        std::bitset<m> slice_addr (std::bitset<32> addr, int hi, int lo){
            addr = addr >> lo;
            unsigned long mask = (1<<(hi-lo+1)) - 1;
            // std::cout << (std::bitset<8> (l_addr) & std::bitset<8> (mask)) << std::endl;
            unsigned long res = (addr & std::bitset<32> (mask)).to_ulong();
            return std::bitset<m> (res);
        }

        int increment(int value){
            assert(value>=0 && value<=3);
            if (value < 3){return (value+1);}
            else {return value;}         
        }

        int decrement(int value){
            assert(value>=0 && value<=3);
            if (value > 0){return (value-1);}
            else {return value;}         
        }

        char predict_branch_taken (std::unordered_map <std::bitset<m>,int>& map, std::bitset<m> index){
            if (map[index]==2 || map[index]==3){return 't';}
            else {return 'n';}
            // else if (value==0 || value ==1) {return 'n';}
        }

        void update_table (std::unordered_map <std::bitset<m>,int>& map, std::bitset<m> index, 
                            char pred, char true_val)
        {
            if (pred==true_val){
                if (map[index]==2 || map[index]==3){map[index] = increment(map[index]);}
                else {map[index] = decrement(map[index]);}   
            }
            else {
                if (map[index]==2 || map[index]==3){map[index] = decrement(map[index]);}
                else {map[index] = increment(map[index]);}  
            }
            
        }

        void initialize_table (std::unordered_map <std::bitset<m>,int>& map){
            for (unsigned int i=0; i<pow(2,m); i++){
                map[std::bitset<m>(i)] = 2;
            }
        }

        void display_table (std::unordered_map <std::bitset<m>,int>& map){
            std::cout << "\nINDEX\t" << "COUNTER_VAL" << std::endl;
            std::cout << "---------------------------" << std::endl;

            for (unsigned int i=0; i<pow(2,m); i++){
                // std::cout << std::bitset<m>(i) << "\t" << map[std::bitset<m>(i)] << std::endl;
                std::cout << i << "\t" << map[std::bitset<m>(i)] << std::endl;
            }
        }

        float display_stats(std::vector<char> true_vals, std::vector<char> preds_vals){
            std::cout << "number of predictions - " << preds_vals.size() << std::endl;
            float count=0;
            for (int i=0; i<preds_vals.size(); i++){
                if (true_vals[i] != preds_vals[i]){count++;}
            }
            std::cout << "number of mispredicts - " << count << std::endl;
            std::cout << " misprediction rate - " << (count/preds_vals.size()) << std::endl;
            return (count/preds_vals.size());
        }

        void load_trace(){
            // Reading in trace
            std::ifstream file(trace_path); 
            std::string line;                    

            if (!file.is_open()) {std::cerr << "Error: Unable to open file.\n";}

            std::string hex_address;
            char char_val;

            while (std::getline(file, line)) {
                std::stringstream ss(line);

                if (ss >> hex_address >> char_val) {
                    // std::cout << "hex - " << hex_address << std::endl;
                    // Convert the hexadecimal address to a 32-bit unsigned int then bitstring
                    std::bitset<32> bitset_addr(std::stoul(("00"+hex_address), nullptr, 16));
                    // std::cout << "bit-string - " << bitset_addr << std::endl;
                    
                    addresses_vec.push_back(bitset_addr);
                    true_br_vec.push_back(char_val);
                }
            }
            file.close();
            
            // Slicing addresses_vec
            for (int i=0; i<addresses_vec.size(); i++){
                std::bitset<m> slc (slice_addr(addresses_vec[i], m+1, 2));
                // std::cout << " addr - " << addresses_vec[i] << ", slice - " << slc << std::endl;
                pc_index_vec.push_back(slc);
            }
        }

        float run_config(){
            initialize_table(hmap);
            char pred;

            for(unsigned int i=0; i<pc_index_vec.size(); i++){
                pred = predict_branch_taken(hmap, pc_index_vec[i]);
                update_table(hmap, pc_index_vec[i], pred, true_br_vec[i]);
                preds_vec.push_back(pred);
                // std::cout << "\n\n ITER - " << i << std::endl;
                // display_table(hmap);     
            }

            float res = display_stats(true_br_vec, preds_vec);
            // display_table(hmap);   
            return res;
        }

};



// int main(){

//     Bimodal_Predictor<4> bp1("../sample_trace.txt");
//     bp1.load_trace();
//     std::cout << bp1.run_config();
    
// }
