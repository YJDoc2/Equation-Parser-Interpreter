#include<string>
#include<cctype>
#include<cstring>

#include "./parser/typedef.c"

extern void showVars(void);
extern void showConst(void);
extern Result vardump(void);
extern Result varload(void);
extern void clearVars(void);
extern Result parse(char * start, char * end);
extern float absolute(float x);
extern Result solvePoly(string eq);

using namespace std;

int checkAndEvalInternalFn(char in[]){

    Result ret;

    if(strcmp(in,"showvars")==0){
        showVars();
        return 1;
    }else if(strcmp(in,"showconst")==0){
        showConst();
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

void print_output(string out){
	
	//! To Implement


}

string get_next_data_line(ifstream reader){
	string line;
	
	while(reader.good()){
		getline(reader,line);
		++current_line;
		//Removes space from line
		line.erase(remove_if(line.begin(),line.end(),::is_space),line.end());
		
		//Checks for blank lines and comments(//)
		if(line.empty() || line.find("//")==0){
			contine;

		}else{
			return line;
        	}
	}
	
	throw exception("Reached End of file.");
	

}

void lin_solve(ifstream reader,int num_eq){
	
	//@Vatsal

}


void poly_solve(string eq){
	Result ret;
        ret = solvePoly(eq);
        if(ret.status != SUCCESS){
        	throw string(ret.error_info);
        }else{
		Quotient *temp;
                temp=rootstart;
                if (rootstart==NULL){
                    printf("No Real Roots are Found \n");
                }else{
		    //Display the variables from top -> bottom
                    while (temp!=NULL){
                        printf("Root = %f \n",temp->coef);
                        temp=temp->next;
                    }
                }
        }

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
