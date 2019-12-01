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
extern Result solveLinear();

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
