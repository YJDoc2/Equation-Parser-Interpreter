#include<string>
#include<fstream>
#include<algorithm>
#include <iostream>
#include<cctype>
#include<cstring>

#include "./parser/typedef.c"
#include "./parser/linkedlist.c"

extern "C"{
    Result vardump(void);
    Result varload(void);
    void clearVars(void);
    Result parse(char * start, char * end);
    float absolute(float x);
    Result solvePoly(char* eq);
    Result parserLinear(char *eq);
    Result solveLinear();
    void initLinear(void);

    extern int linear;
    extern int numVars;
    extern int currentEq;
    Var* var_start;
    extern float default_var[];
    extern float X[];
}

using namespace std;

int current_line=0;
bool output_is_terminal = true;
ofstream output_file;

void print_output(string out){

    static ostream& printer = output_is_terminal ? cout : output_file;
    
    printer<<"Output : line "+to_string(current_line) + " : ";
    printer<<out<<endl;
    


}

void show_vars(){

    int c =0;
    Var *temp =var_start;
    string out ="";
    out += "Default Vars :\n\t\t\t\t   ";
    for(;c<10;c++){
        out += "$"+to_string(c)+" : "+to_string(default_var[c])+"\n\t\t\t\t   ";
    }
    out += "Defined Vars :\n\t\t\t\t   ";
    while (temp!=NULL){

        out += string(temp->name)+" : "+to_string(temp->val)+"\n\t\t\t\t   ";
        temp = temp->next;
    }

    print_output(out);

}

void display_linear_soln(){

    int i;
    string out ="";
    out += "Solution : ";
    for(i=1;i<=numVars;i++){
        out += "x"+to_string(i-1)+" = "+to_string(X[i])+"\n\t\t\t\t\t\t\t  ";
    }

    print_output(out);


}

int checkAndEvalInternalFn(char in[]){

    Result ret;

    if(strcmp(in,"showvars")==0){
        show_vars();
        return 1;
    }else if(strcmp(in,"vardump")==0){
        ret = vardump();
        if(ret.status != SUCCESS){
        	throw string(ret.error_info);
        }
        return 1;
    }else if(strcmp(in,"varload")==0){
        ret = varload();
        if(ret.status != SUCCESS){
            throw string(ret.error_info);
        }
        return 1;
    }else if(strcmp(in,"varclear")==0){
        clearVars();
        return 1;
    }else{
    	return 0;
    }
}

bool is_space_c(char c){
    return c == ' ' || c == '\n' || c== '\t' ||c == '\v';
}

string get_next_data_line(ifstream& reader){
	string line;
	
	while(reader.good()){
		getline(reader,line);
		++current_line;
		//Removes space from line
        if(line[0]=='#'){
		    print_output(line.substr(1,line.length()));
		    continue;
	    }
        line.erase(remove_if(line.begin(), line.end(), is_space_c), line.end());
		
		//Checks for blank lines and comments(//)
		if(line.empty() || line.find("//")==0){
			continue;

		}else{
			return line;
        	}
	}
	
	throw string("EOF");
	

}

void lin_solve(ifstream& reader,int num_eq){
	
	Result ret;
	numVars = num_eq;
    linear =1;
    initLinear();
	for(currentEq=1;currentEq<=numVars;++currentEq){		
		if(reader.bad()){
			throw string("Incomplete number of equations on line "+to_string(current_line)+"\n\tRequired "+to_string(num_eq)+" Found"+to_string(currentEq)+".");
		}else{
            string line = get_next_data_line(reader);
            char eq[line.size()+1];
            strcpy(eq,line.c_str());
		    ret = parserLinear(eq);
            
			if(ret.status!=SUCCESS){
                linear = 0;
                throw string(ret.error_info);
			}
        }		
	}
    ret = solveLinear();
    linear =0;
    if(ret.status != SUCCESS && ret.status != MATH_ERROR){
        throw string(ret.error_info);
    }
    if(ret.status == MATH_ERROR){
        print_output(string(ret.error_info));
    }else{
        display_linear_soln();
    }
}


void poly_solve(string in){
	Result ret;
    char eq[in.length()+1];
    strcpy(eq,in.c_str());
    ret = solvePoly(eq);
    if(ret.status != SUCCESS){
        throw string(ret.error_info);
    }else{
	    Quotient *temp;
        temp = rootstart;
        if (rootstart==NULL){
            print_output("No Real Roots are Found \n");
        }else{
            string out ="";
		    //Display the variables from top -> bottom
            while (temp!=NULL){
                out += "Root = "+to_string(temp->coef)+"\n\t\t\t\t   ";
                temp=temp->next;
            }
            print_output(out);
        }
    }

}

void parse(string line){
		
	char arr[line.length()+1];
    strcpy(arr,line.c_str());
	
	int stat = checkAndEvalInternalFn(arr);
	if(stat == 1){
		return;
	}
	
	Result r = parse(arr,arr+line.length());
	
	if(r.status != SUCCESS){
		throw string(r.error_info);
    }
    print_output(to_string(r.data));

}
