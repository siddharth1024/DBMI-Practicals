/**	
	DMBI Practical No. : 1
	Aim : Normalize profit (0.0 - 1.0) .
	
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
	Z-Score v' = (v - meanA)/Stand.Dev.A
*/

int main() {	
	ifstream InputFileStream;	
	ofstream OutputFileStream;
	
	InputFileStream.open(input_file_name, ios_base::binary);
	OutputFileStream.open(output_file_normalized_name);
	/**
		Work out the mean.
	*/
	float profits[RECORDS], mean = 0, std_dev = 0, z_score = 0;

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
			OutputFileStream << ",Z-Score,";
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
		mean += profits[p];
	}
	cout << "\nSum : \t\t" << mean;
	mean /= RECORDS;
	cout << "\nMean : \t\t" << mean;
	cout << "\nRECORDS : \t\t" << RECORDS;
	
	for(int p = 0; p < RECORDS; p++) {
		profits[p] -= mean;
		profits[p] = profits[p] * profits[p];
	}

	for(int p = 0; p < RECORDS; p++) {
		std_dev += profits[p];
	}

	std_dev /= RECORDS;
	cout << "\nMean of squared differences : \t\t" << std_dev;

	std_dev = sqrt(std_dev);

	cout << "\nStandard Deviation : \t\t" << std_dev;
	
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
				
				float val = std::stof(f_val);
				float z_score = (val - mean) / std_dev;

				OutputFileStream << val << "," << z_score;

				for(int i = end_idx; i < line.length(); i++) {
					OutputFileStream << line[i];				
				}

				column_no++;								
			}			
		}
	}
	cout << "\n";
}





