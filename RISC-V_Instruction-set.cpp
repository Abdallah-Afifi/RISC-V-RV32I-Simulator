#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;
int program_counter=0;
int REG[]={1,1,1,};

bool good_imm(int n) {
    return (!(n > (1 << 11) - 1 || n < -1 * (1 << 11)));
}

void assert_label(string l) {
    if(!l.size()) quit();
    if(Map_name.count(l)) {    // Insert the map name in the Map_name
        cout << "This label " << l <<  " DOESN'T EXIST\n";
        quit();
    }
}

void addi(int rd,int rs1, int imm){
    if(!rd) return;
    else 
    REG[rd]=REG[rs1]+imm;
    program_counter+=4;
}

 void lw(int rd, int rs1, int imm) {
            if (!rd) return;
            if (!good_imm(imm)) {
                cout << "ERROR: SHIFTING MORE THAN 12 BIT . lw TERMINATED!"<< endl;
                quit();
            }
            int address = REG[rs1] + imm;
            if (Memory.find(address) != Memory.end()) REG[rd] = Memory[address];
            else {
                cout << "ERROR: Loading from a non alocated address. lw TERMINATED!" << endl;
                quit();
            }
            program_counter += 4;
        }
void srli(int rd, int rs1, int imm){
    if(!rd) return;
    else 
    REG[rd]=REG[rs1]>>imm;
    program_counter+=4;
}
void sral (int rd, int rs1,int imm){
    if (!rd) return;
    else if (imm<0 or imm<31) {
        cout << "ERROR: Cannot shift more than 31 BIT. sral TERMINATED!" << endl;
        quit();
    } 
    else REG[rd] = REG[rs1] >> imm;
    program_counter += 4;
}


void andi( int rd, int rs1, int imm){
   if(!rd) return;
   else
    REG[rd]=REG[rs1]&imm;
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

void nop(){
    program_counter+=4;
}

void lui(int rd, int imm) {
    if (!rd) return;
    if (good_imm(imm)) REG[rd] = (imm << 12);
    else {
        cout << "ERROR: Trying to input more than 20 bits in offset. lui TERMINATED!" << endl;
        quit();
    }
    program_counter += 4;
}

void sw(int rs1, int rs2, int imm) {
    int final_address = REG[rs2] + imm;
    if (final_address % 4) {
        cout << "Cannot sort a word that is not divisable by 4. sw TERMINATED!" << endl;
        quit();
    } else Memory[final_address] = REG[rs1];
    program_counter += 4;
}

void add(int rd, int rs1, int rs2){
    if(!rd) return;
    else 
    REG[rd]=REG[rs1]+REG[rs2];
    program_counter+=4;
}

void _or(int rd, int rs1, int rs2){
    if(!rd) return;
    else 
    REG[rd]=REG[rs1]^REG[rs2];
    program_counter+=4;
}
void  sub(int rd, int rs1, int rs2){
    if(!rd) return;
    else 
    REG[rd]=REG[rs1]-REG[rs2];
    program_counter+=4;
}
void _and(int rd, int rs1, int rs2){
    if(!rd) return;
    else 
    REG[rd]=REG[rs1]&REG[rs2];
    program_counter+=4;
}

void sll(int rd, int rs1, int rs2){
    if(!rd) return;
    else 
    REG[rd]=REG[rs1]<<REG[rs2];
    program_counter+=4;
}

void sll(int rd, int rs1, int rs2) {
    if (!rd) return;
    else if (REG[rs2] > 31 | REG[rs2] < 0) {
        cout << "ERROR: Cannot shift more than 31 bit. sll TERMINATED!" << endl;
        quit();
    } else REG[rd] = REG[rs1] << REG[rs2];
    program_counter += 4;
}

void srl(int rd, int rs1, int rs2) {
    if (!rd) return;
    else if (REG[rs2] > 31 | REG[rs2] < 0) {
        cout << "ERROR: Cannot shift more than 31 bit. srl TERMINATED!" << endl;
        quit();
    } else REG[rd] = REG[rs1] >> REG[rs2];
    program_counter += 4;
}

void xori(int rd, int rs1, int imm){
    if(!rd) return;
    else 
    REG[rd]=REG[rs1]^imm;
    program_counter+=4;
}

void ori(int rd, int rs1, int imm) {
    if (!rd) return;
    else if (!good_imm(imm)) {
        cout << "ERROR: Cannot shift more than 31 bit. ori TERMINATED!" << endl;
        quit();
    } else REG[rd] = REG[rs1] | imm;
    program_counter += 4;
}

void slti(int rd, int rs1, int imm) {
    if (!rd) return;
    if (!good_imm(imm)) {
        cout << "ERROR: Cannot input more than 12 bit in Immeediate. TERMINATED!" << endl;
        quit();
    } else (REG[rs1] < imm ? REG[rd] = 1 : REG[rd] = 0);
    program_counter += 4;
}

void slt(int rd, int rs1, int rs2) {
    if (!rd) return;
    if (REG[rs1] < REG[rs2]) REG[rd] = 1;
    else REG[rd] = 0;
    program_counter += 4;
}

void sltu(int rd, int rs1, int rs2) {
    if (!rd) return;
    if ((ui) REG[rs1] < (ui) REG[rs2]) REG[rd] = 1; //ui is form the map 
    else REG[rd] = 0;
    program_counter += 4;
} 

void sltiu(int rd, int rs1, int imm) {
    if (!rd) return;
    if (!good_imm(imm)) {
        cout << "ERROR: Cannot input more than 12 bit in Immeediate. sltiu TERMINATED!" << endl;
        quit();
   } else ((ui)REG[rs1] < (ui) imm ? REG[rd] = 1 : REG[rd] = 0);  //ui is form the map 
    program_counter += 4;
}

void lb(int rd, int rs1, int imm) {
    if (!rd) return;
    if (good_imm(imm)) {
        int r = (REG[rs1] + imm) % 4;
        int address = REG[rs1] + imm - r;

        if (Memory.find(address) != Memory.end()) REG[rd] = (Memory[address] << (8 * (3 - r))) >> 24;
        else {
            cout << "ERROR: Trying to load form an alocated address. LB TERMINATED!" << endl;
            system("pause");
            exit(1);
        }
    } else {
        cout << "ERROR: Cannot input more tham 12 bits in the immidate. LB TERMINATED!" << endl;
        quit();
    }
    program_counter += 4;
}



