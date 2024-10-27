#include <iostream>
#include <fstream>
#include <bitset>
#include <sstream>
#include <bits/stdc++.h>
#include <unordered_map>
// using namespace std;

// const int m = 4;
// std::string trace_path = "../jpeg_trace.txt";

template <size_t m>
std::bitset<m> slice_addr (std::bitset<8> addr, int hi, int lo){
    addr = addr >> lo;
    unsigned long mask = (1<<(hi-lo+1)) - 1;
    // std::cout << (std::bitset<8> (l_addr) & std::bitset<8> (mask)) << std::endl;
    unsigned long res = (addr & std::bitset<8> (mask)).to_ulong();
    return std::bitset<m> (res);
}

int main(){

    std::bitset<4> a(slice_addr<4>(0b10000110, 4, 1));
    std::cout << a << std::endl;

    
}