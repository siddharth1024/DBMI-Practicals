/**	
	DMBI Practical No. : 1
	Aim : Normalize profit (0.0 - 1.0) .
	
	Author : Siddharth Goswami
	Github : https://github.com/siddharth1024
*/

#include<iostream>
#include<string.h>
#include<fstream>

#define input_file_name "Sample.csv"
#define output_file_normalized_name "Sample_Normalized.csv"

#define LINES 8400
#define COLUMN_PROFIT 9

using namespace std;

inline float normalize(float v, float min, float max) {
	return (v-min)/(max-min);
}

int main() {	
	ifstream InputFileStream;	
	ofstream OutputFileStream;
	
	InputFileStream.open(input_file_name, ios_base::binary);
	OutputFileStream.open(output_file_normalized_name);

	float min_profit = 0.0f, max_profit = 0.0f;
	/**
		Search minimum and maximum profit.
	*/
	for(int p = 0; p < LINES; p++) {
		string line;
		getline(InputFileStream, line, '\r');		
		
		if(p == 0) {
			continue;
		}
		
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
				float val = std::stof(f_val);
				if(val < min_profit) { min_profit = val; }
				if(val > max_profit) { max_profit = val; }
				column_no++;								
			}			
		}
	}

	InputFileStream.close();
	InputFileStream.open(input_file_name, ios_base::binary);

	/**
		Normalize profit and write whole line to file.
	*/
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
				int start_idx = c;
				string f_val = "";
				while(line[c] != ',') {
					f_val += line[c];
					c++;
				}
				int end_idx = c;

				for(int i = 0; i < start_idx; i++) {
					OutputFileStream << line[i];				
				}
				
				float val = std::stof(f_val);
				OutputFileStream << normalize(val, min_profit, max_profit);

				for(int i = end_idx; i < line.length(); i++) {
					OutputFileStream << line[i];				
				}

				column_no++;								
			}			
		}
	}
	cout << "\nMin Profit : " << min_profit;
	cout << "\nMax Profit : " << max_profit;
}
