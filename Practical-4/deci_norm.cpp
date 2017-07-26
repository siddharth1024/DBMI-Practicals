/**	
	DMBI Practical No. : 4
	Aim : Decimal-Normalization profit.
	
	Author : Siddharth Goswami
	Github : https://github.com/siddharth1024
*/

#include<iostream>
#include<string.h>
#include<fstream>
#include<math.h>

#define input_file_name "Sample.csv"
#define output_file_normalized_name "Sample_Normalized.csv"

#define LINES 8400
#define RECORDS LINES-1
#define COLUMN_PROFIT 9

using namespace std;

/**
	Deci-norm v' = v / 10^j (j is smallest integer such that max(|v'|)) < 1
*/

int main() {	
	ifstream InputFileStream;	
	ofstream OutputFileStream;
	
	InputFileStream.open(input_file_name, ios_base::binary);
	OutputFileStream.open(output_file_normalized_name);
	/**
		Work out the mean.
	*/
	float profits[RECORDS], profits_normalized[RECORDS], max_v = 0;

	string line;
	getline(InputFileStream, line, '\r');

	int column_no = 1, insert_idx = 0;

	for(int c = 0; c < line.length(); c++) {
		if(line[c] == ',')
			column_no++;

		if(column_no == COLUMN_PROFIT) { 
			insert_idx = c;
		}		
	}

	for(int c = 0; c < line.length(); c++) { 
		if(c == insert_idx + 1) {
			OutputFileStream << ",Decimal Normalization,";
		} else {
			OutputFileStream << line[c];
		}
	}

	for(int p = 1; p < LINES; p++) {
		string line;
		getline(InputFileStream, line, '\r');
		
		if(p == 0) continue;
		
		int column_no = 1;
		
		for(int c = 0; c < line.length(); c++) {			
			if(line[c] == ',')
				column_no++;
			
			if(column_no == COLUMN_PROFIT) {				
				c++;
				string f_val = "";
				while(line[c] != ',') {
					f_val += line[c];
					c++;
				}
				profits[p-1] = std::stof(f_val);
				column_no++;								
			}			
		}
	}

	for(int p = 0; p < RECORDS; p++) {
		float mod_profit = (profits[p] < 0) ? profits[p] * -1: profits[p];
		if(mod_profit > max_v) {
			max_v = mod_profit;
		}
	}

	max_v = (max_v < 0) ? -max_v : max_v;
	int divider = 1;
	while (max_v/divider > 1) { divider *= 10; }

	for(int p = 0; p < RECORDS; p++) { 
		profits_normalized[p] = profits[p] / divider;
	}

	InputFileStream.close();
	InputFileStream.open(input_file_name, ios_base::binary);

	for(int p = 0; p < LINES; p++) {
		string line;
		getline(InputFileStream, line, '\r');		
		
		if(p == 0) {
			OutputFileStream << line;
			continue;
		}
		
		int column_no = 1;
		
		for(int c = 0; c < line.length(); c++) {			
			if(line[c] == ',')
				column_no++;
			
			if(column_no == COLUMN_PROFIT) {				
				c++;
				int start_idx = c; string f_val = "";				
				while(line[c] != ',') {
					f_val += line[c];
					c++;
				}
				int end_idx = c;

				for(int i = 0; i < start_idx; i++) {
					OutputFileStream << line[i];				
				}

				OutputFileStream << profits[p] << "," << profits_normalized[p];

				for(int i = end_idx; i < line.length(); i++) {
					OutputFileStream << line[i];				
				}

				column_no++;								
			}			
		}
	}
	
	cout << "\n";
}





