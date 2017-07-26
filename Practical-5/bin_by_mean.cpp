/**	
	DMBI Practical No. : 5
	Aim : Smoothing by bin (mean).
	
	Author : Siddharth Goswami
	Github : https://github.com/siddharth1024
*/

#include<bits/stdc++.h>

#define input_file_name "Sample.csv"
#define output_file_normalized_name "Sample_Normalized.csv"

#define LINES 8400
#define RECORDS_COUNT LINES-1
#define COLUMN_PROFIT 9
#define BIN_SIZE 100

using namespace std;

/**
	Deci-norm v' = v / 10^j (j is smallest integer such that max(|v'|)) < 1
*/

struct Record {
	int line_no;
	float profit;
};

inline bool sortByProfit(const Record &a, const Record &b) {
	return a.profit < b.profit;
}

inline bool sortByLineNo(const Record &a, const Record &b) {
	return a.line_no < b.line_no;
}

int main() {	
	ifstream InputFileStream;	
	ofstream OutputFileStream;
	
	InputFileStream.open(input_file_name, ios_base::binary);
	OutputFileStream.open(output_file_normalized_name);
	
	vector <Record> records;
	vector <Record>::iterator records_iterator;

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
			OutputFileStream << ",Smoothing (mean),";
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
				float profit = stof(f_val);
				records.push_back(Record {p-1, profit});
				column_no++;								
			}			
		}
	}

	sort(records.begin(), records.end(), sortByProfit);

	int item_counter = 1; float basket_mean = 0.0f;
	vector <Record>::iterator rI, rBegin, rEnd;

	for(records_iterator = records.begin(); 
		records_iterator != records.end(); 
		records_iterator++) 
	{
		if(item_counter == 1) rBegin = records_iterator;
		if(item_counter == BIN_SIZE) {
			basket_mean /= BIN_SIZE;
			rEnd = records_iterator;
			for(rI = rBegin; rI != rEnd; rI++) 
			{
				(*rI).profit = basket_mean;
			}
			item_counter = 0;
			basket_mean = 0.0f;
		}
		Record record = *records_iterator;
		basket_mean += record.profit;
		item_counter++;
	}

	sort(records.begin(), records.end(), sortByLineNo);

	InputFileStream.close();
	InputFileStream.open(input_file_name, ios_base::binary);

	records_iterator = records.begin();

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
			
			if(column_no == COLUMN_PROFIT + 1) {				
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
				Record record = *records_iterator;
				OutputFileStream << record.profit;
				records_iterator++;

				for(int i = end_idx; i < line.length(); i++) {
					OutputFileStream << line[i];				
				}

				column_no++;								
			}			
		}
	}
	
	cout << "\n";
}





