#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<exception>
#include<algorithm>

#include "./c_bindings.cpp"

using namespace std;

int current_line=0;


void process_line(string line,ifstream reader){
	
	if(line.length<){
		
	}
	
	string temp = "";
	
	//linsolve -> 8 chars
	temp = line.substr(0,8);
	if(temp.compare("linsolve")){
		
		if(isdigit(line[8])==0 || isdigit(line[9]) != 0){
			throw "Invalid Syntax..Should be 'linsolve<number of variables> where number of variables should be less than 9'";
		}
		
		lin_solve(reader,line[8]-'0');
		return;
	
	}
	
	//polysolve -> 9 char
	temp = line.substr(0,9);
	if(temp.compare("polysolve")){
		
		poly_solve(line.substr(9,line.length()));
		return;
	
	}
	
	//simple parse
	
	parse(line);


}

int main(int argc,char *argv[]){
	string line;
	ifstream file_reader;
	
	if(argc<2){
	
		cerr<<"Please give appropriate arguments..."<<endl;
		cerr<<"eqparce <script_file_name>"<<endl;
		return 1;
	
	}
	file_reader.open(argv[1]);
	
	//Prints Error message if file cannot be accessed
	if (file_reader.bad()){
		cerr<<"Cannot Read File "<<argv[1]<<endl;
		cerr<<"Please Check if user has appropriate read permissions"<<endl;
		return 1;
	}
	
	
	while(file_reader.good()){
	
		try{
			line = get_next_data_line(file_reader);
			try{
				process_line(line,file_reader);
			}catch(string err){
				cerr<<"Error at line "<<current_line<<" : "<<endl;
				cerr<<"\t"<<temp<<endl;
				cerr<<"\t"<<err<<endl;
				break;
			}
		}catch(exception){
			//Do nothing
		}
		
			
			
	}
	cout<<"Number of Lines: "<<current_line<<endl;
	file_reader.close();
	return 0;
}
