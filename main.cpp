#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<algorithm>

#include "./c_bindings.cpp"

using namespace std;

int current_line=0;

int main(int argc,char *argv[]){
	ifstream file_reader;
	string line;
	
	if(argc<2){
	
		cout<<"Please give appropriate arguments..."<<endl;
		cout<<"eqparce <script_file_name>"<<endl;
	
	
	}
	file_reader.open(argv[1]);
	
	//Prints Error message if file cannot be accessed
	if (file_reader.bad()){
		cout<<"Cannot Read File "<<argv[1]<<endl;
		cout<<"Please Check if user has appropriate read permissions"<<endl;
		return 1;
	}
	
	
	while(file_reader.good()){
		getline(file_reader,line);
		string temp = line;
		//Removes space from line
		line.erase(remove_if(line.begin(),line.end(),::is_space),line.end());
		++current_line;
		//Checks for blank lines and comments(//)
		if(line.empty() || line.find("//")==0){
			continue;

		}else{
			try{
				process_line(line,file_reader);
			}catch(string err){
				cout<<"Error at line "<<current_line<<" : "<<endl;
				cout<<"\t"<<temp<<endl;
				cout<<"\t"<<err<<endl;
			}
			
        }
	}
	cout<<"Number of Lines: "<<current_line<<endl;
	file_reader.close();
	return 0;
}


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


void lin_solve(ifstream reader,int num_eq){
	Result ret;
	
	string line;
	
	while(1)
	{		
		get_next_data_line(reader);
		ret=parserLinear(line);
		//getline(reader,line);
		if(reader.eof())
			break;
		else
		{
			if(ret.status!=SUCCESS){
				printf("Error Occured...%s\n",ret.error_info);
			}
			else{
				for(currentEq=1;currentEq<=numVars;currentEq++){
			memset(eq,'\0',175);
			printf(">>>>> ");
			fgets(eq,170,stdin);
			eq[strlen(eq)-1] = '\0';
			if(strcmp(eq,"back")==0){
				ret.status = SUCCESS;
				linear =0;
				return ret;
			}
			if(strlen(eq)>150){
				printf("Please give Equation containing less Than 150 Character.\n");
				currentEq--;
				continue;
			}else{
				ret = parserLinear(eq);
				if(ret.status != SUCCESS){
					linear =0;
					return ret;
				}
			}
		}
    }
	ret = solveLinear();
    linear =0;
    CHECK(ret,eq,0);
    displayLinearSoln();
    return ret;
	}		
	}	//@Vatsal
}


void poly_solve(string eq){
	Result *ret;
	eq[strlen(eq)-1] = '\0';
            ret = solvePoly(eq);
            if(ret.status != SUCCESS){
                printf("Error Occured...%s\n",ret.error_info);
            }else{
                Quotient *temp;
                temp=rootstart;
                if (rootstart==NULL){
                    printf("No Real Roots are Found \n");
                }else{
                    while (temp!=NULL){
                        printf("Root = %f \n",temp->coef);			//Display the variables from top -> bottom
                        temp=temp->next;
                    }
                }
            }//@Yatharth

}

void parse(string line){
		
	char arr[] = line.c_str();
	
	int stat = checkAndEvalInternalFn(arr);
	if(stat == 1){
		return;
	}
	
	Result r = parse(arr,arr+line.length());
	
	if(r.status != SUCCESS){
		throw string(r.error_info);
        }
	
	//! Still to Decide on how to give the outputs...

}
