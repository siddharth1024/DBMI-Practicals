/**	
	DMBI Practical No. : 2
	Aim : Filter dataset by zip code, valid zip code format is 5 numeric digits.
	
	Author : Siddharth Goswami
	Github : https://github.com/siddharth1024	
*/

#include<iostream>
#include<string.h>
#include<fstream>

#define input_file_name "Consumer_Complaints.csv"
#define output_file_filtered_name "Consumer_Complaints_Filtered.csv"
#define output_file_noise_name "Consumer_Complaints_Noise.csv"

#define LINES 807963
#define COLUMN_ZIP_CODE 10
#define ZIP_CODE_LENGTH 5

using namespace std;

int main() {
	
	ifstream InputFileStream;	
	ofstream OutputFileStream, OutputFileStreamNoise;
	
	InputFileStream.open(input_file_name, ios_base::binary);
	OutputFileStream.open(output_file_filtered_name);
	OutputFileStreamNoise.open(output_file_noise_name);
	
	int dirty_lines = 0, total_lines = 0;
	
	for(int p = 0; p < LINES; p++) {
		string line;
		getline(InputFileStream, line, '\r');		
		
		if(p == 0) {
			OutputFileStream << line;
			OutputFileStreamNoise << line;
			continue;
		}
		
		int column_no = 1, inside_quotes = 0, zip_digit_count = 0, is_line_dirty = 0;
		
		for(int c = 0; c < line.length(); c++) {			
			if(line[c] == '\"') 
				inside_quotes = !inside_quotes;
			
			if(line[c] == ',' && inside_quotes == 0)
				column_no++;
			
			if(column_no == COLUMN_ZIP_CODE) {				
				c++;
				int end_idx = c + ZIP_CODE_LENGTH;
				for(;c < end_idx; c++) {
					if(!(line[c] >= '0' && line[c] <= '9')) {
						is_line_dirty = 1;
						break;
					}
				}
				column_no++;								
			}			
		}		
		if(is_line_dirty) {
			OutputFileStreamNoise << line;
			dirty_lines++;
			
		} else {
			OutputFileStream << line;
		}
		total_lines++;
	}
	cout << "\nTotal Lines Read : " << total_lines;
	cout << "\nProper Lines : " << total_lines - dirty_lines;
	cout << "\nDirty Lines : " << dirty_lines;	
}