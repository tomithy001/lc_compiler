
#include "compiler.h"
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void data_inverse(uint8_t* data,uint32_t len)
{
    uint32_t i = 0;
    uint8_t tmp;

    for(i=0;i<len/2;i++)
    {
        tmp = data[len-1-i];
        data[len-1-i] = data[i];
        data[i] = tmp;
    }
}

string to_string(uint128_t x);
#include <fstream>
void writeBin(char *path, uint8_t *buf, uint32_t size)
{
    FILE *outfile;

    if ((outfile = fopen(path, "wb")) == NULL)
    {
        printf("\nCan not open the path: %s \n", path);
        exit(-1);
    }
    fwrite(buf, sizeof(char), size, outfile);
    fclose(outfile);
}


void vector_to_char_array(std::vector<uint8_t>& vec, unsigned char* &arr) 
{
    arr = reinterpret_cast<unsigned char*>(vec.data());
}

int main()
{
    

    Compiler compiler;

    compiler._program.type="vector";
    compiler._program.operation_type = "PAILLIER_ENC";//
    compiler._program.p_bitcount = 4096;
    compiler._program.vec_size =200000;
    compiler._program.e_bitcount = 2048;

    compiler.compile();

    // for(auto &j_dat:compiler.inst_byte)
    // {
    //     std::cout<<static_cast<int>(j_dat)<<",";
    // }
    // std::cout<<std::endl;


    // for(auto &j_dat:compiler.executor.inst)
    // {
    //     std::cout<<static_cast<int>(j_dat)<<",";
    // }
    // std::cout<<std::endl;

    uint8_t *inst_buf;
    vector_to_char_array(compiler.executor.inst,inst_buf);
    writeBin("_inst.bin",inst_buf,compiler.executor.inst.size());

    uint8_t *inst_buf1;
    vector_to_char_array(compiler.executor.inst_fpga,inst_buf1);
    writeBin("_inst_fpga.bin",inst_buf1,compiler.executor.inst_fpga.size());

    // for(auto &j_dat:compiler.executor.inst_fpga)
    // {
    //     std::cout<<static_cast<int>(j_dat)<<",";
    // }
    // std::cout<<std::endl;

    

    // uint32_t ndigits = 0;
    // for(__uint128_t &ii_dat:compiler._generator_fpga.inst)
    // {
    //     std::cout << to_string(ii_dat)<<",";
    // }
    // std::cout<<std::endl;

    uint8_t bytes[16];
    std::vector<uint8_t> inst_fpga_bytes;
    for(__uint128_t &i_dat:compiler._generator_fpga.inst)
    {
        // std::cout << to_string(i_dat);
        // std::cout<<std::endl;
        memcpy(bytes, &i_dat, sizeof(i_dat));
        data_inverse(bytes,16);
        for(uint32_t i = 0;i<16;i++)
        {
            inst_fpga_bytes.push_back(bytes[i]);
        }
        // std::cout<<std::endl;
    }

    // for(auto &k_dat:inst_fpga_bytes)
    // {
    //     std::cout<<static_cast<int>(k_dat)<<" ";
    // }
    // std::cout<<std::endl;
}


string to_string(uint128_t x) {
    if (x == 0) return "0";
   string s = "";
    while (x > 0) {
        s += char(x % 10 + '0');
        x /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}
























