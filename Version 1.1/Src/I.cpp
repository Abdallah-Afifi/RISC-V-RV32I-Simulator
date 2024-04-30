#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <bitset>
#include <algorithm>
#include "I.hpp"

using namespace std;

bool IFormatChecker(string inst, bool &offset)
{
    if( inst == "addi" || inst == "slti" || inst == "sltiu" || inst == "xori" || inst == "ori" || inst == "andi"|| inst == "slli" || inst == "srli" || inst == "srai" )
    {
        offset = false;
        return true;
    }
    else if (inst == "jalr" || inst == "lb" || inst == "lh" || inst == "lw" || inst == "lbu" || inst == "lhu" )
    {
        offset = true;
        return true;
    }
    else
        return false;  
}

void IFormat(string inst, string inst_rest, vector<pair<string, int> > &reg, int &pc, bool &pc_changed , map< int , int > &memory, bool &err, bool &offset)
{
    int rd = -1, rs1 = -1;
    int imm;
    
    stringstream instruction(inst_rest);
    
    string store;
    vector <string> temp;
    while (instruction >> store) {
                store.erase(remove(store.begin(), store.end(), ','), store.end());
                temp.push_back(store);
            }
    if(!offset){
        
	    for (size_t i = 0; i < reg.size(); ++i) {
		    if (reg[i].first == temp[0]) {
			    rd = i;
		    }
		    if (reg[i].first == temp[1]) {
			    rs1 = i;
		    }
	    }
        imm =  stoi(temp[2]);
    }
    else{
        string immediate, source;
        extractStrings(temp[1], immediate, source);
         for (size_t i = 0; i < reg.size(); ++i) {
		    if (reg[i].first == temp[0]) {
			    rd = i;
		    }
            if (reg[i].first == source) {
			    rs1 = i;
		    }
         }
         imm =  stoi(immediate);  
    }
	if (rd == -1 || rs1 == -1 ) {
		cout << "Invalid entries." << endl;
        err = true;
	}
	else
	{
        if(reg[rd] != reg[0])
        {
            if(inst == "jalr")
            {
                reg[rd].second = pc + 4;
                pc = reg[rs1].second + imm;
                pc_changed = true;
            }
            else if(inst == "lh")
            {
                        if(memory.find(reg[rs1].second+imm) != memory.end())
                {
                    if (memory[reg[rs1].second+imm] < 0)
                    {
                        reg[rd].second = memory[reg[rs1].second+imm] & 0xFFFF;
                        

                        reg[rd].second |= 0xFFFFFFFFFFFF0000;
                    }
                    else
                    {
                        reg[rd].second = memory[reg[rs1].second+imm] & 0xFFFF;
                        reg[rd].second |= 0;
                    }

                }
                else
                {
                    "Memory location not found please make sure it is initialized \n";
                    err = true;
                } 
            }
            else if(inst == "lb")
            {
                if(memory.find(reg[rs1].second+imm) != memory.end())
                {
                    if (memory[reg[rs1].second+imm] < 0)
                    {
                        reg[rd].second = memory[reg[rs1].second+imm] & 0xFF;
                        

                        reg[rd].second |= 0xFFFFFFFFFFFFFF00;
                    }
                    else
                    {
                        reg[rd].second = memory[reg[rs1].second+imm] & 0xFF;
                        reg[rd].second |= 0;
                    }

                }
                else
                {
                    "Memory location not found please make sure it is initialized \n";
                    err = true;
                }        
            }
            else if(inst == "lw")
            {
                if(memory.find(reg[rs1].second+imm) != memory.end())
                    reg[rd].second = memory[reg[rs1].second+imm];
                else
                {
                    "Memory location not found please make sure it is initialized \n";
                    err = true;
                }        
            }
            else if(inst == "lbu")
            {
                if(memory.find(reg[rs1].second+imm) != memory.end())
                    reg[rd].second = (memory[reg[rs1].second+imm] & 0xFF);
                else
                {
                    "Memory location not found please make sure it is initialized \n";
                    err = true;
                }  
            }
            else if(inst == "lhu")
            {
                if(memory.find(reg[rs1].second+imm) != memory.end())
                    reg[rd].second = (memory[reg[rs1].second+imm] & 0xFFFF);
                else
                {
                    "Memory location not found please make sure it is initialized \n";
                    err = true;
                }  
            }
            else if(inst == "addi")
            {
                reg[rd].second = reg[rs1].second + imm;
            }
            else if(inst == "slti")
            {
                if( reg[rs1].second < imm)
                    reg[rd].second = 1;
                else
                    reg[rd].second = 0;

            }
            else if(inst == "sltiu")
            {
                if ( reg[rs1].second >= 0 && imm>=0)
                    if(reg[rs1].second < imm)
                        reg[rd].second = 1;
                    else
                        reg[rd].second = 0;
                else if(reg[rs1].second >= 0 && imm < 0)
                    reg[rd].second = 1;
                else if (reg[rs1].second < 0 && imm < 0)
                    if (reg[rs1].second < imm)
                        reg[rd].second = 1;
                    else
                        reg[rd].second = 0;
                else if (reg[rs1].second < 0 && imm >= 0)
                    reg[rd].second = 0;
            }
            else if(inst == "xori")
            {
                reg[rd].second = reg[rs1].second ^ imm ;
            }
            else if(inst == "ori")
            {
                reg[rd].second = reg[rs1].second | imm ;
            }
            else if(inst == "andi")
            {
                reg[rd].second = reg[rs1].second & imm ;
            }
            else if(inst == "slli")
            {
                reg[rd].second = reg[rs1].second << imm ;
            }
            else if(inst == "srli")
            {
                unsigned int unsignedImm = static_cast<unsigned int>(imm);
                unsigned int unsignedrs1 = static_cast<unsigned int>(reg[rs1].second);
                reg[rd].second = static_cast<unsigned int> (unsignedrs1 >> unsignedImm );
            
            }
            else if(inst == "srai")
            {
            reg[rd].second = reg[rs1].second >> imm ;
            }
        }
    }

    return;
}
void extractStrings(string input, string& beforeParentheses, string& withinParentheses) {
    size_t openingParen = input.find('(');
    size_t closingParen = input.find(')');
    
    if (openingParen != string::npos && closingParen != string::npos && openingParen < closingParen) {
        beforeParentheses = input.substr(0, openingParen);
        withinParentheses = input.substr(openingParen + 1, closingParen - openingParen - 1);
    } 
}
