#include <iostream>
#include <fstream>
#include <vector>
#include "bimodal_cls.cpp"
#include "gshare_cls.cpp"

template<size_t M>
float run_bi_predictor(const std::string& trace_path) {
    // object automatically destroyed when function returns
    Bimodal_Predictor<M> bp(trace_path);
    bp.load_trace();
    return bp.run_config();
}

int main(){

    // Bimodal plts
    std::vector<int> m_tests = {7,8,9,10,11,12};
    std::vector<float> bi_gcc_mispred_rates;
    std::vector<float> bi_jpeg_mispred_rates;


    // gcc_trace
    bi_gcc_mispred_rates.push_back(run_bi_predictor<7> ("../gcc_trace.txt"));
    bi_gcc_mispred_rates.push_back(run_bi_predictor<8> ("../gcc_trace.txt"));
    bi_gcc_mispred_rates.push_back(run_bi_predictor<9> ("../gcc_trace.txt"));
    bi_gcc_mispred_rates.push_back(run_bi_predictor<10> ("../gcc_trace.txt"));
    bi_gcc_mispred_rates.push_back(run_bi_predictor<11> ("../gcc_trace.txt"));
    bi_gcc_mispred_rates.push_back(run_bi_predictor<12> ("../gcc_trace.txt"));

    std::ofstream file;
    file.open("bi_gcc_mr.csv");
    file << "m,rate\n";
    for (int i=0; i<m_tests.size(); i++){
        file << std::to_string(m_tests[i]) <<"," << std::to_string(bi_gcc_mispred_rates[i]) << "\n";
    }
    file.close();


    // jpeg_trace
    bi_jpeg_mispred_rates.push_back(run_bi_predictor<7> ("../jpeg_trace.txt"));
    bi_jpeg_mispred_rates.push_back(run_bi_predictor<8> ("../jpeg_trace.txt"));
    bi_jpeg_mispred_rates.push_back(run_bi_predictor<9> ("../jpeg_trace.txt"));
    bi_jpeg_mispred_rates.push_back(run_bi_predictor<10> ("../jpeg_trace.txt"));
    bi_jpeg_mispred_rates.push_back(run_bi_predictor<11> ("../jpeg_trace.txt"));
    bi_jpeg_mispred_rates.push_back(run_bi_predictor<12> ("../jpeg_trace.txt"));
    
    file.open("bi_jpeg_mr.csv");
    file << "m,rate\n";
    for (int i=0; i<m_tests.size(); i++){
        file << std::to_string(m_tests[i]) <<"," << std::to_string(bi_jpeg_mispred_rates[i]) << "\n";
    }
    file.close();




}