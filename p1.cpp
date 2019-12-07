#include <fstream>
#include <string>
#include <iostream>
#include <iomanip> 
#include <vector>
#include <map>
#include <utility>
using namespace std;

void printMipsLine(string output[10][16], int lineNum);
bool differentStage(string output[10][16], int col);
int dependentLine(string mipsCode[10][4], int instructionLine, int instructionNum);
int calcRegVal(string mipsCode[10][4], map<string,int> registers, int instructionLine);

int main( int argc, char * argv[] ) {
	// Error checking
	if (argc < 2) {	
		cerr << "Incorrect amount of arguments \n";
		exit(-1);
	}

	char f = *argv[1];
	bool forwarding;
	if (f != 'F' && f != 'N') {
		cerr << "Incorrect forwarding mode \n";
		exit(-1);
	}
	if (f == 'F') {
		forwarding = true;
	}
	else {
		forwarding = false;
	}
	ifstream input(argv[2]);

	if (!input) {
		cerr << "Failed to open file \n";
		exit(-1);
	}

	cout << "START OF SIMULATION";
	if (forwarding) {
		cout << " (forwarding)" << endl;
	}
	else {
		cout << " (no forwarding)" << endl;
	}
	cout << "----------------------------------------------------------------------------------" << endl;

	// Initialize Variables
	int i, j, k, l, m, tempInt, dependent, counter;
	int instructionNum = 0;
	int nopIndex = 0;
	bool nopAdded = false;
	string line;

	string stages[5] = {"IF", "ID", "EX", "MEM", "WB"};
	map < string, int > registers = { {"$s0", 0}, {"$s1", 0}, {"$s2", 0}, 
		{"$s3", 0}, {"$s4", 0}, {"$s5", 0}, {"$s6", 0}, {"$s7", 0}, 
		{"$t0", 0}, {"$t1", 0}, {"$t2", 0}, {"$t3", 0}, {"$t4", 0}, 
		{"$t5", 0}, {"$t6", 0}, {"$t7", 0}, {"$t8", 0}, {"$t9", 0} };


	string mipsLine[10];
	string mipsCode[10][4];
	string output[10][16];
	string nop[20][16];

	int numNops[10] = {};
	bool loadComplete[10] = {};
	int stageNums[10] = { 0 };
	string tempStr;

	// Initialize Arrays
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 16; j++) {
			output[i][j] = ".";
		}
	}

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 16; j++) {
			nop[i][j] = ".";
		}
	}

	i = 0;
	while (getline(input, line)) {
		mipsLine[i] = line;
		instructionNum++;
		i++;
	}

	// save mips code as an array of strings
	for (int i = 0; i < instructionNum; i++) {
		j = 0;
		tempInt = mipsLine[i].find(" ");
		tempStr = mipsLine[i].substr(j,tempInt);
		mipsCode[i][0] = tempStr;
		j = tempInt + 1;

		tempInt = mipsLine[i].find(",", j);
		tempStr = mipsLine[i].substr(j, tempInt - j);
		mipsCode[i][1] = tempStr;
		j = tempInt + 1;

		tempInt = mipsLine[i].find(",", j);
		tempStr = mipsLine[i].substr(j, tempInt - j);
		mipsCode[i][2] = tempStr;
		j = tempInt + 1;

		tempInt = mipsLine[i].length();
		tempStr = mipsLine[i].substr(j, tempInt - j);
		mipsCode[i][3] = tempStr;
	}

	// Loop through each cycle in mips pipeline (max 16 cycles)
	for (i = 0; i < 16; i++) {
		// Check if last mips instruction is finished
  		if (output[instructionNum-1][i-1] == "WB") {
  			break;
  		}
		cout << "CPU Cycles ===>     1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16" << endl;
  		// Loop through each instruction
  		for (j = 0; j < instructionNum; j++) {
  			if (j == 0 || (i > j - 1 && j == 1) || (i > j - 1 && stageNums[j-1] >= 1)) {
  				// Forwarding
  				if (forwarding) {
  					if (stageNums[j] == 2) {
  						loadComplete[j] = true;
  					}
  				}
  				else {
					if (stageNums[j] == 4) {
						loadComplete[j] = true;
					}
  				}
				if (stageNums[j] >= 0 && stageNums[j] < 5) {
					output[j][i] = stages[stageNums[j]];
				}
				else {
					output[j][i] = ".";
				}
				if (stageNums[j] == 4) {
					cout << calcRegVal(mipsCode, registers, j) << endl;
					registers[mipsCode[j][1]] = calcRegVal(mipsCode, registers, j);
				}
				// Decides what to print for each line
				dependent = dependentLine(mipsCode, j, instructionNum);
				if (differentStage(output, i)) {
					if (stageNums[j] == 1) {
						if (dependent == -1 || loadComplete[dependent]) {
							stageNums[j]++;
						}
						else {
							nopAdded = true;
						}
					}
					else {
						stageNums[j]++;
					}
				}
				else {
					if (stageNums[j] > 0 && stageNums[j] < 5) {
						output[j][i] = stages[stageNums[j] - 1];
					}
					else {
						output[j][i] = ".";
					}
				}
				// Decides what the nop lines will print like (if they're used)
				if (numNops[j] > 0) {
					m = 0;
					for (int k = 0; k < j; k++) {
						m += numNops[k];
					}
					for (int k = 0; k < numNops[j]; k++) {
						counter = 0;
						cout << left << setw(20) << "nop";
						for (int l = 0; l < i; l++) {
							if (nop[m][l] == "*") {
								counter++;
							}
							cout << left << setw(4) << nop[m][l];
						}
						if (counter < 3) {
							nop[m][i] = "*";
						}
						for (l = i; l < 16; l++) {
							cout << left << setw(4) << nop[m][l];
						}
						cout << endl;
						m++;
					}
				}
				// prints mips instruction and output line
				cout << left << setw(20) << mipsLine[j];
				printMipsLine(output, j);

		  		if (nopAdded) {
		  			for (k = 0; k < 16; k++) {
						nop[nopIndex][k] = output[j][k];
					}
					nopIndex++;
					numNops[j]++;
		  		}
		  		nopAdded = false;				
  			}
		}
		// At end of cycle, print registers and their values (updated when line reaches WB stage)
		cout << endl;
		cout << "$s0 = "  << left << setw(13) << registers["$s0"] << "$s1 = " << left << setw(13) << registers["$s1"];
		cout << "$s2 = "  << left << setw(13) << registers["$s2"] << "$s3 = " << left << setw(13) << registers["$s3"] << endl;
		cout << "$s4 = "  << left << setw(13) << registers["$s4"] << "$s5 = " << left << setw(13) << registers["$s5"];
		cout << "$s6 = "  << left << setw(13) << registers["$s6"] << "$s7 = " << left << setw(13) << registers["$s7"] << endl;
		cout << "$t0 = "  << left << setw(13) << registers["$t0"] << "$t1 = " << left << setw(13) << registers["$t1"];
		cout << "$t2 = "  << left << setw(13) << registers["$t2"] << "$t3 = " << left << setw(13) << registers["$t3"] << endl;
		cout << "$t4 = "  << left << setw(13) << registers["$t4"] << "$t5 = " << left << setw(13) << registers["$t5"];
		cout << "$t6 = "  << left << setw(13) << registers["$t6"] << "$t7 = " << left << setw(13) << registers["$t7"] << endl;
		cout << "$t8 = "  << left << setw(13) << registers["$t8"] << "$t9 = " << left << setw(13) << registers["$t9"] << endl;
		cout << "----------------------------------------------------------------------------------" << endl;
	}
	cout << "END OF SIMULATION" << endl;
}

// Prints output line after mips instructions
void printMipsLine(string output[10][16], int lineNum) {
	for (int i = 0; i < 16; i++) {
		cout << left << setw(4) << output[lineNum][i];
	}
	cout << endl;
}

bool differentStage(string output[10][16], int col) {
	for (int i = 0; i < 9; i++) {
		string tempStr = output[i+1][col];
		if (!tempStr.compare(output[i][col]) && tempStr.compare(".")) {
			return false;
		}
	}
	return true;
}

int dependentLine(string mipsCode[10][4], int instructionLine, int instructionNum) {
	for (int i = 0; i < instructionNum; i++) {
		if (instructionLine == i) {
			break;
		}
		for (int j = 2; j < 4; j++) {
			if (mipsCode[i][0] == "" || mipsCode[instructionLine][j] == "") {
				continue;
			}
			string tempStr = mipsCode[instructionLine][j];
			if (!tempStr.compare(mipsCode[i][0])) {
				return i;
			}
		}
	}
	return -1;
}

// Finds the value of first register in current line
int calcRegVal(string mipsCode[10][4], map<string,int> registers, int instructionLine) {
	// use easier variables for everything
	string instruction = mipsCode[instructionLine][0];
	string reg1 = mipsCode[instructionLine][1];
	string reg2 = mipsCode[instructionLine][2];
	string reg3 = mipsCode[instructionLine][3];
	int val1, val2, val3;
	// assign values for val2 and val3
	if (reg2 == "$zero") {
		val2 = 0;
	}
	else if (isdigit(reg2[0])) {
		val2 = stoi(reg2);
	}
	else {
		val2 = registers[reg2];
	}
	if (reg3 == "$zero") {
		val3 = 0;
	}
	else if (isdigit(reg3[0])) {
		val3 = stoi(reg3);
	}
	else {
		val3 = registers[reg3];
	}
	// depending on instruction, assign val1
	if (instruction == "add" || instruction == "addi") {
		val1 = val2 + val3;
		return val1;
	}
	else if (instruction == "and" || instruction == "andi") {		// For and, andi, or, & ori, it's binary stuff
		val1 = val2 & val3;
		return val1;
	}
	else if (instruction == "or" || instruction == "ori") {
		val1 = val3 | val3;
		return val1;
	}
	else if (instruction == "slt" || instruction == "slti") {
		if (val2 < val3) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (instruction == "beq" || instruction == "bne") {
		return registers[reg1];
	}
	return registers[reg1];
}