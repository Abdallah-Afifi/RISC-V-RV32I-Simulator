#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <bitset>
#include <algorithm>
#include "helper.hpp"
#include "R.cpp"
#include "I.cpp"
#include "S.cpp"
#include "B.cpp"
#include "J.cpp"
#include "U.cpp"

using namespace std;

void assembler()
{
	int pc;
	int ans(1);
	string filepath;
	vector<pair<string, int> > reg;
	reg.push_back(make_pair("zero", 0)); reg.push_back(make_pair("ra", 0)); reg.push_back(make_pair("sp", 1500000000));
	reg.push_back(make_pair("gp", 2000000000)); reg.push_back(make_pair("tp", 0)); reg.push_back(make_pair("t0", 0));
	reg.push_back(make_pair("t1", 0)); reg.push_back(make_pair("t2", 0)); reg.push_back(make_pair("s0", 0));
	reg.push_back(make_pair("s1", 0)); reg.push_back(make_pair("a0", 0)); reg.push_back(make_pair("a1", 0));
	reg.push_back(make_pair("a2", 0)); reg.push_back(make_pair("a3", 0)); reg.push_back(make_pair("a4", 0));
	reg.push_back(make_pair("a5", 0)); reg.push_back(make_pair("a6", 0)); reg.push_back(make_pair("a7", 0));
	reg.push_back(make_pair("s2", 0)); reg.push_back(make_pair("s3", 0)); reg.push_back(make_pair("s4", 0));
	reg.push_back(make_pair("s5", 0)); reg.push_back(make_pair("s6", 0)); reg.push_back(make_pair("s7", 0));
	reg.push_back(make_pair("s8", 0)); reg.push_back(make_pair("s9", 0)); reg.push_back(make_pair("s10", 0));
	reg.push_back(make_pair("s11", 0)); reg.push_back(make_pair("t3", 0)); reg.push_back(make_pair("t4", 0));
	reg.push_back(make_pair("t5", 0)); reg.push_back(make_pair("t6", 0));
	do
	{

		cout << "~~~~~~~~~~~~~~~~~Welcome to your RISC-V simulator~~~~~~~~~~~~~~~ \n\n";
		cout << "\t\tWhat would you like to do?\n\n"
			<< "\t\t  1. Read from an exisisting file\n\t\t  2. Exit\n";

		if (ans < 1 || ans > 2)
		{
			cout << "invalid number entered try again \n";
		}
		cout << "option:";
		cin >> ans;

	} while (ans > 2 || ans < 1);

	if (ans == 1)
	{
		map < int, int > memory;
		map < int, string> instructions;
		map < string, int> labels;
		char base('d');
		int end;
		int memadd, memvalue; //initializing data memory if user wants
		string mem;//flag to know if they want to initialize their data memory

		cout << "enter your file path\n";
		cin >> filepath;

		cout << "enter your starting PC\n";
		cin >> pc;

		end = Intializing_Data(filepath, pc, instructions, labels);

		cout << "choose how you want to view your data b: binary, d:decimal , h:hexadecimal  \n";
		cin >> base;
		while(base != 'b' && base != 'd' && base != 'h')
		{
			cout << "invalid value, please choose b: binary, d:decimal , h:hexadecimal  \n";
			cin >> base;
		}

		cout << "Do you want to initialize your memory ? yes/Yes \n";
		cin >> mem;

		while (mem == "yes" || mem == "Yes")
		{
			cout << "enter the memory address: ";
			cin >> memadd;
			cout << "enter the corresponding memory value: ";
			cin >> memvalue;

			memory[memadd] = memvalue;

			cout << "Do you want to initialize another thing in your memory? yes/Yes \n";
			cin >> mem;
		}

		

		int startpc(pc);
		bool pc_changed(false), err(false);
		char nextinst('n');
		

		do{
			
			string lowCAPinst(instructions[pc]);
			for(int i = 0; i < lowCAPinst.length(); i++)
			{
				lowCAPinst[i] = tolower(lowCAPinst[i]);
			}	
			stringstream instruction(lowCAPinst);
        	string store;
			string temp;

			

			if (instruction >> store) {
				temp = store;
			}

			string concat;
        	concat = lowCAPinst;
        	int i = concat.find(temp);
        	concat.erase(i,temp.length());
			removeLeadingSpacesAndTabs(concat);
			concat.erase(remove(concat.begin(), concat.end(), ' '), concat.end());
			AddSpaces(concat);
			cout <<"Instruction: " << instructions[pc] <<endl ;
        	check_format(temp, concat, reg, pc, memory, pc_changed, err, labels);
			
			
			if (!pc_changed)
				pc += 4;

			if (err)
			{
				cout << "encountered problem with your asm instructions\n";
				break;
			}
			string binary1, binary2;
			cout << "\n\nMemory: \n" ;
			if(memory.empty())
				cout << "Memory has not been accessed yet!\n";
			else
			{	
   
				if(base == 'd')
					for (const auto& pair : memory)
					{
						
					cout << "Address: " << pair.first << ", Value: " << pair.second << endl;
					}
				else if(base == 'b')
					for (const auto& pair : memory)
					{
						binary1 = bitset<32>(pair.first).to_string();
						binary2 = bitset<32>(pair.second).to_string();
						cout << "Address: " << binary1 << ", Value: " <<  binary2 << endl;
					}
				else
					for (const auto& pair : memory)
					{
						cout << "Address: ";
						printf("%#.8x", pair.first);
					 	cout << ", Value: " ;
						printf("%#.8x", pair.second);
					}

			}
				
			
			cout << "\n\n Registers: \n";
			cout <<"Name\tNumber\tValue\n";
			if(base == 'd')
				for (int i = 0; i < reg.size(); ++i) {
				cout  << reg[i].first<< "\t" << i << "\t" <<reg[i].second << endl;
				}
			else if(base == 'b')
				for (int i = 0; i < reg.size(); ++i) {
					binary1 = bitset<32>(reg[i].second).to_string();
					cout  << reg[i].first<< "\t" << i << "\t" << binary1 << endl;
				}
			else
				for (int i = 0; i < reg.size(); ++i) {
					cout  << reg[i].first<< "\t" << i << "\t" ;
					printf("%#.8x", reg[i].second);
					cout << endl;
    			}
			

			cout << "Current PC:" << pc << endl;

			cout << "Do you want to move to next instruction?y/n\n";
			tolower(nextinst);
			cin >> nextinst ;
		} while (pc != end + 4 && nextinst == 'y');
	}
	else
		exit(1);
}

void removeLeadingSpacesAndTabs(string& input) {
	int start = input.find_first_not_of(" \t"); // Find the first character that is not a space or tab
	if (start != string::npos) {
		input = input.substr(start); // Modify the input string to start from the first non-space/tab character
	}
	else {
		input = ""; // If the input is all spaces and tabs, set the input string to an empty string
	}
}

void check_format(string inst, string inst_rest, vector<pair<string, int> > &reg, int& pc, map <int,  int>& memory, bool& pc_changed, bool& err, map <string,  int>& labels) // name , string
{
	pc_changed = false;
	err = false;
	bool offset;
	if(RFormatChecker(inst))
	{
		RFormat(inst, inst_rest, reg, err);
	}
	else if(IFormatChecker(inst, offset))
	{
		IFormat(inst, inst_rest, reg, pc, pc_changed,  memory, err, offset);
	}
	else if(UFormatChecker(inst))
	{
		UFormat(inst, inst_rest, reg, pc, memory, err );
	}
	else if(SFormatChecker(inst))
	{
		SFormat(inst, inst_rest, reg,  memory, err);
	}
	else if(BFormatChecker(inst))
	{
		BFormat(inst, inst_rest, reg, err, labels, pc, pc_changed);
	}
	else if(JFormatChecker(inst))
	{
		JFormat(inst, inst_rest, reg, err, labels, pc, pc_changed);
	}
	else if(inst == "ecall" || inst == "ebreak" || inst == "fence")
	{
		cout << "\nProgram Terminated\n";
		exit(1);
	}
	else
	{
		cout << "invalid instruction used\n";
		err = true;
	}	
   
}
void AddSpaces(string& input) {
    string result;
    for (char c : input) {
        if (c == ',') {
            result += ", "; // Insert space before and after the comma
        } else {
            result += c; // Keep other characters unchanged
        }
    }
    input = result; // Update the original string
}
string removing_comments(string line)
{
	string new_line;
	size_t found = line.find('#');
	if (found != string::npos)
	{
		int i = 0;
		while (line[i] != '#')
		{
			new_line += line[i];
			i++;
		}

		return new_line;
	}
	else
		return line;
}
string storing_label(string line)
{
	string new_line;
	size_t found = line.find(':');
	if (found != string::npos)
	{
		int i = 0;
		while (line[i] != ':')
		{
			new_line += line[i];
			i++;
		}

		return new_line;
	}
	else
		return line;
}
int Intializing_Data(string filepath, int pc, map< int, string>& instructions, map<string, int>& labels)
{
	

	ifstream input(filepath);


	string line;
	string label = "";
	if (input.is_open())
	{
		getline(input, line);
		while(line.empty())
		{
			getline(input, line);
		}
		removeLeadingSpacesAndTabs(line);

		if (line[0] == '#' || line == "")
		{
			getline(input, line);
			line = removing_comments(line);
		}
		size_t found = line.find(':');
		if (found != string::npos)
		{
			int i = 0;
			while (line[i] != ':')
			{
				label += line[i];
				i++;
			}
			for(int i = 0 ; i < line.length(); i++)
				label[i] = tolower(label[i]);
			labels[label] = pc;
			getline(input, line);
			while(line.empty())
			{
				getline(input, line);
			}
			line = removing_comments(line);
			removeLeadingSpacesAndTabs(line);
			instructions[pc] = line;
			while (!input.eof())
			{
				
				label = "";
				getline(input, line);
				while(line.empty())
				{
					getline(input, line);
				}
				line = removing_comments(line);

				label = storing_label(line);
				if (label != line)
				{
					for(int i = 0 ; i < line.length(); i++)
						label[i] = tolower(label[i]);
					labels[label] = pc + 4;
				}
				else
				{
					removeLeadingSpacesAndTabs(line);
					pc += 4;
					instructions[pc] = line;
				}

			}
		}
		else
		{	
			
			line = removing_comments(line);
			removeLeadingSpacesAndTabs(line);
			instructions[pc] = line;
			while (!input.eof())
			{
				
				label = "";
				getline(input, line);
				while (line.empty())
				{
					getline(input, line);
				}
				line = removing_comments(line);
				label = storing_label(line);
				if (label != line)
				{
					for(int i = 0 ; i < line.length(); i++)
						label[i] = tolower(label[i]);
					labels[label] = pc + 4;
				}
				else
				{
					removeLeadingSpacesAndTabs(line);
					pc += 4;
					instructions[pc] = line;
				}

			}
		}

	}
	input.close();
	int end = pc;

	
}
