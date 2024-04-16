#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;
int program_counter=0;
int REG[];

void addi(int rd,int rs1, int num){
    if(!rd) return;
    else 
    REG[rd]=REG[rs1]+num;
    program_counter+=4;
}

void srli(int rd, int rs1, int num){
    if(!rd) return;
    else 
    REG[rd]=REG[rs1]>>num;
    program_counter+=4;
}
void sral (int rd, int rs1,){

}

void andi( int rd, int rs1, int num){
   if(!rd) return;
   else
    REG[rd]=REG[rs1]&num;
    program_counter+=4;
}

void sub(int rd, int rs1, int rs2){
    if (!rd) return;
    else 
    REG[rd]=REG[rs1]-REG[rs2];
    program_counter+=4;
}

void _xor(int rd, int rs1, int rs2){
    if (!rd) return; 
    else 
    REG[rd]=REG[rs1]^REG[rs2];
    program_counter+=4;
}
