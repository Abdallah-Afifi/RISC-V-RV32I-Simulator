#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;
int program_counter=0;
int REG[]={1,1,1,};

bool valid_imm(int n) {
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
            if (!valid_imm(imm)) {
                cout << "ERROR: Cannot shift more than 12 bits. lw TERMINATED!"<< endl;
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
    if (valid_imm(imm)) REG[rd] = (imm << 12);
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
    else if (!valid_imm(imm)) {
        cout << "ERROR: Cannot shift more than 31 bit. ori TERMINATED!" << endl;
        quit();
    } else REG[rd] = REG[rs1] | imm;
    program_counter += 4;
}

void slti(int rd, int rs1, int imm) {
    if (!rd) return;
    if (!valid_imm(imm)) {
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
    if (!valid_imm(imm)) {
        cout << "ERROR: Cannot input more than 12 bit in Immeediate. sltiu TERMINATED!" << endl;
        quit();
   } else ((ui)REG[rs1] < (ui) imm ? REG[rd] = 1 : REG[rd] = 0);  //ui is form the map 
    program_counter += 4;
}

void lb(int rd, int rs1, int imm) {
    if (!rd) return;
    if (valid_imm(imm)) {
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

void lh(int rd, int rs1, int imm) {
    if (!rd) return;
    if (valid_imm(imm)) {
        int r = (REG[rs1] + imm) % 4;
        int address = REG[rs1] + imm - r;
        if (Memory.find(address) != Memory.end()) REG[rd] = (Memory[address] << (8 * (2 - r))) >> 16;
        else {
            cout << "ERROR: Cannot input from a non alocated address. LH TERMINATED!" << endl;
            system("pause");
            exit(1);
        }
    } else { 
        cout << "ERROR: Cannot input more thsn 12 bits in immediate. LH TERMINATED!" << endl;
        quit();
    }
    program_counter += 4;
}

void bltu(int rs1, int rs2, string label) {
    assert_label(label);
    (REG[rs1] < REG[rs2] ? program_counter = labToAdd[label] : program_counter += 4); //labToAdd from the map
}

void lhu(int rd, int rs1, int imm) {
    if (!rd) return;
    if (good_imm(imm)) {
        int r = (REG[rs1] + imm) % 4;
        int address = REG[rs1] + imm - r;
        if (Memory.find(address) != Memroy.end()) {
            REG[rd] = (ui)(Memory[address] << (8 * (2 - r))) >> 16;
        } else {
            cout << "ERROR: Cannot load form a non allocated address. lhu TERMINATED!" << endl;
            system("pause");
            exit(1);
        }
    } else {
        cout << "ERROR: Cannot input more than 12 bits in Immediate. LB TERMINATED!" << endl;
        quit();
    }
    program_counter += 4;
}


void sb(int rs1, int rs2, int imm) {
    int address = REG[rs2] + imm;
    int r = address % 4;
    int final_address = address - r;

    ui byte = REG[rs1] << 24;  //ui from libary
    byte = byte >> 24;
    byte = byte << 8 * r;

    ui mask = BYTREP;  //ui from libary  the BYTREP is assigend as ui mask=BYTREP
    mask = mask << 8 * r;
    mask = ~mask;
    int edited_word = Memory[final_address];
    edited_word = ((edited_word & mask) | byte);

    Memory[final_address] = edited_word;
    program_counter += 4;
}

void sh(int rs1, int rs2, int imm) {
    int address = REG[rs2] + imm, r = address % 4, final_address = address - r;
    if (final_address % 2) {
        cout << "Cannot store a half word that is not divisable by 2.  sh TERMINATED!" << endl;
        quit();
    } else {
        ui half = REG[rs1] << 16;
        half = half >> 16;
        half = half << 8 * r;
        ui mask = HALFREP;  //  from the map ui mask = HALFREP;
        mask = mask << 8 * r;
        mask = ~mask;
        int edited_word = Memory[final_address];
        edited_word = ((edited_word & mask) | half);
        Memory[final_address] = edited_word;
    }
    program_counter += 4;
} 

void beq(int rs1, int rs2, string label) {
    assert_label(label);
    (REG[rs1] == REG[rs2] ? program_counter = labToAdd[label] : program_counter += 4); //labtoadd is from the map 
}

void beq(int rs1, int rs2, int offset) {
    if (REG[rs1] == REG[rs2]) {
        if (good_imm(offset)) program_counter = program_counter + 2 * offset;
        else {
            cout << "ERROR:  Cannot input more than 12 bits in the offset. beq TERMINATED!" << endl;
            system("pause");
            exit(1);
        }
    } else program_counter += 4;
}

void bne(int rs1, int rs2, string label) {
    assert_label(label);
    (REG[rs1] != REG[rs2] ? program_counter = labToAdd[label] : program_counter += 4);
}
void bne(int rs1, int rs2, int offset) {
    if (REG[rs1] != REG[rs2]) {
        if (good_imm(offset)) program_counter = program_counter + 2 * offset;
        else {
            cout << "ERROR: Cannot input more than 12 bits in the offset. bne TERMINATED!" << endl;
            system("pause");
            exit(1);
        }
    } else program_counter += 4;
}

void blt(int rs1, int rs2, string label) {
    assert_label(label);
    (REG[rs1] < REG[rs2] ? program_counter = labToAdd[label] : program_counter += 4);
}
void blt(int rs1, int rs2, int offset) {
    if (REG[rs1] < REG[rs2]) {
        if (good_imm(offset)) {
            program_counter = program_counter + 2 * offset;
        } else {
            cout << "ERROR: Cannot input more than 12 bits in the offset. blt TERMINATED!" << endl;
            system("pause");
            exit(1);
        }
    } else program_counter += 4;
}

void bge(int rs1, int rs2, string label) {
    assert_label(label);
    (REG[rs1] >= REG[rs2] ? program_counter = labToAdd[label] : program_counter += 4);
}

void bge(int rs1, int rs2, int offset) {
    if (REG[rs1] >= REG[rs2]) {
        if (good_imm(offset)) program_counter = program_counter + 2 * offset;
        else {
            cout << "ERROR: Cannot input more than 12 bits in the offset. bge TERMINATED!" << endl;
            system("pause");
            exit(1);
        }
    } else program_counter += 4;
}

void bgeu(int rs1, int rs2, string label) {
    assert_label(label);
    ((ui)REG[rs1] >= (ui)REG[rs2] ? program_counter = labToAdd[label] : program_counter += 4);
}

void bgeu(int rs1, int rs2, int offset) {
    if ((ui) REG[rs1] >= (ui) REG[rs2]) {
        if (good_imm(offset)) program_counter = program_counter + 2 * offset;
        else {
            cout << "ERROR: Cannot input more than 12 bits in the offset. bgue  TERMINATED!" << endl;
            system("pause");
            exit(1);
        }
    } else program_counter += 4;
}


void jal(int rd, string label) {
    assert_label(label);
    if (!rd) REG[rd] = program_counter + 4;
    program_counter = labToAdd[label];
}
void jal(int rd, int offset) {
    if (rd != 0) REG[rd] = program_counter + 4;
    if (good_imm(offset)) program_counter = program_counter + (offset << 1);
    else {    
        cout << "ERROR: Cannot input more than 20 buts in offset. jal TERMINATED!" << endl;
        quit();
    }
}

void jalr(int rd, int rs1, int imm) {
    if (rd != 0) REG[rd] = program_counter + 4;
    if (!good_imm(imm)) {
        cout << "ERROR: Cannot shift more than 12 bits. jalr TERMINATED!" << endl;
        quit();
    } else program_counter = REG[rs1] + imm;
}

void lui(int rd, int imm) {
    if (!rd) return;
    if (good_imm(imm)) REG[rd] = (imm << 12);
    else {
        cout << "ERROR: Cannot input more than 20 bits in offset. lui TERMINATED!" << endl;
        quit();
    }
    program_counter += 4;
}

void auipc(int rd, int imm) {
    if (!rd) return;
    if (good_imm(imm)) REG[rd] = program_counter + (imm << 12);
    else {
        cout << "ERROR: Cannot input more than 20 bits in offset. auip TERMINATED!" << endl;
        quit();
    }
    program_counter += 4;
}

void quit(){
    return;  // use this or use the comman exit(1)?
}
