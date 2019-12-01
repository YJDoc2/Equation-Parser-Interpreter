#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include "./typedef.c"
#include "./variables.c"
#include "./constants.c"
#include "./queues.c"
#include "./constants.c"


#ifndef PREPARSER
#define PREPARSER

char infix[150],buf[150];
int ASSIGN =-1,DEFAULT = -1,EXISTING=-1;
char v_name[30];

void initPreparse(){
    ASSIGN = -1;
    DEFAULT = -1;
    EXISTING = -1;
    memset(infix,'\0',150);
    memset(buf,'\0',150);
}

//*Removes spaces from the given equation
void removeSpaces(char *p){
    int n =0;
    if(p == NULL){
        return;
    }
    for(int i = 0;i<strlen(p);i++){
        if(p[i]!=' '){
            p[n++]=p[i];
        }
    }
    p[n]='\0';
}

//*Checks if the given equation assigns value to any variable,default or otherwise;
Result checkAssign(char *in){

    Result ret;
    char temp[30];
    char *start = strchr(in,'=');
    if(start == NULL){
        ret.status = SUCCESS;
        return ret;
    }
    if(start != strrchr(in,'=')){
        ret.status = ASSIGN_ERROR;
        strcpy(ret.error_info,"Cannot Perform Multiple Assignments");
        return ret;
    }
    memset(temp,'\0',30*sizeof(char));
    strncpy(temp,in,start-in);
    if(strlen(temp)>=30){
        ret.status = ASSIGN_ERROR;
        strcpy(ret.error_info,"Invalid Variable Assignment");
        return ret;
    }
    temp[strlen(temp) +1]='\0';
    ASSIGN =1;
    //printf("T : %s \n",temp);
    if(*in == '$'){
        if(!isdigit(*(in+1)) || *(in+2) != '='){
            ret.status = ASSIGN_ERROR;
            strcpy(ret.error_info,"Incorrect Default Variable Assignment");    
        }else{
            ret.status = SUCCESS;
            DEFAULT = *(in+1)-'0';
        }
    }else{
        strcpy(v_name,temp);
        if(getVar(v_name).status == VARIABLE_NOT_DEFINED){
            strcpy(ret.error_info,"Creating new var");
        }else{
            EXISTING =1;
            strcpy(ret.error_info,"Overwriting Existing Var");
        }
        ret.status = SUCCESS;
    }
    return ret;
}

//* this actually parses the values of Floating point +ve numbers that are in character string starting 
//* pointed by inString, ending with '\0'
//* Honestly !!! Should've done this by sscanf at start 
/*Result parseVal(char inString[]){
    Result ret;
    sscanf(inString,"%f",&ret.data);
    ret.status = SUCCESS;
    return ret;
}*/
//*Loads the general Queue with the values of constants > variables > Floating val priority
//!! Cannot tokenize successfully with brackets thats why it  debrackets copy of equation in
//!! preparse and then loads values
//!! should do something for functions !!
Result loadVal(char *in, char *end){

    float data;
    Result ret,val;
    char *token = strtok(in,"+-/%*^");
    while(token != NULL && token < end){
        if(token == ""){
            continue;
        }
        if(strlen(token)>=30){
            ret.status = ERROR;
            sprintf(ret.error_info,"Invalid Token %s",token);
            return ret;
        }
        if(token[0] == '$'){
            if(strlen(token)>2){
                ret.status = ERROR;
                sprintf(ret.error_info,"Invalid Default Variable %s",token);
                return ret;
            }else{
                val = getDefVar(token[1]-'0');
                enQVal(val.data);
            }
        }else if(isalpha(token[0])){
            val = getConst(token);
            
            if(val.status != SUCCESS){
                val = getVar(token);
                if(val.status != SUCCESS){
                    return val;
                }
            }

            enQVal(val.data);
        }else if(isdigit(token[0])){
            //val = parseVal(token);
            sscanf(token,"%f",&data);
            ret.data = data;
            /*if (val.status == ERROR){
                ret.status = ERROR;
                sprintf(ret.error_info,"Invalid Token %s",token);
                return ret;
            }else{*/
                enQVal(data);
            //}
            
        }else
        {
            ret.status = ERROR;
            sprintf(ret.error_info,"Invalid Token %s",token);
            return ret;
        }
        token = strtok(NULL,"+-/%*^");   
    }
    ret.status = SUCCESS;
    return ret;




}

//* Should Adjusting for -ve value at start of string done in defferent method ---- YES!!!
int isop(char a){
    
    return a=='+' || a=='-' || a=='*' || a=='/' ||a=='%' || a=='^';
}
//* Adjusts the negations  :- replaces operator-val OR operator-const OR operator-var BY
//*                                operator(0-val) OR operator(0-const) OR operator(0-var)
//* eg. *-3 = *(0-3)
//*Also relpaces negation inside brackets like : (-3) => (0-3)

//!! strlen(in) -> end-in
char *adjustNegetive(char *in, char *end){

    int i=0,j=0,l =0;
    int oNeg =0,open = 0;
    char pre = in[0];
    for(i=0;i<end-in;){
        if(in[i] == '-' && isop(pre) &&(isalnum(in[i+1]) || in[i+1] == '$')){
            buf[j++] = '(';
            buf[j++] = '0';
            buf[j++] = '-';
            i++;
            while(i<end-in && !isop(in[i])){
                pre = in[i];
                buf[j++] = in[i++];
            }
            buf[j++] = ')';
        }else if(in[i] =='-'&& isop(pre) &&(in[i+1] == '(' || in[i+1] == '[' || in[i+1] == '{' )){   
            oNeg =1;open =1;
            i++;
            buf[j++] = '(';
            buf[j++] = '0';
            buf[j++] = '-';
            buf[j++] = in[i++];
            while(i<end-in && oNeg!=0){
                
                if(in[i] == '-' && isop(pre) &&(isalnum(in[i+1]) || in[i+1] == '$')){
                        buf[j++] = '(';
                        buf[j++] = '0';
                        buf[j++] = '-';
                        i++;
                        while(i<end-in && !isop(in[i])){
                            pre = in[i];
                            buf[j++] = in[i++];
                        }
                        buf[j++] = ')';
                }else if(in[i] =='-' && isop(pre) &&(in[i+1] == '(' || in[i+1] == '[' || in[i+1] == '{' )){
                    oNeg++;i++;open++;
                    buf[j++] = '(';
                    buf[j++] = '0';
                    buf[j++] = '-';
                    buf[j++] = in[i++];
                }else if(in[i] == '(' || in[i] == '[' || in[i] == '{' ){
                    open++;
                    buf[j++] = in[i++];
                }else if(in[i] == ')' || in[i] == ']' || in[i] == '}'){
                    open--;
                    buf[j++] = in[i++];
                    if(open<oNeg){
                        buf[j++] = ')';
                        oNeg--;
                    }
                }else{
                    pre = in[i];
                    buf[j++] = in[i++];
                }
                while(oNeg>0 && open<=0){
                    buf[j++] = ')';
                    oNeg--;
                }
            }

        }else{
            pre = in[i];
            buf[j++] = in[i++];
        }
        
    }

    while(oNeg>0 || open>0){
        buf[j++] = ')';
        oNeg--;
        open--;
    }
    return buf;
}

//* Preparsing Functions
Result preparse(char *in ,char *end){

    char pre,buf[150],temp[150];
    int i =0,j=0,t=0;
    Result ret,t1;
    memset(buf,'\0',150);
    memset(temp,'\0',150);
    strcpy(temp,adjustNegetive(in,end));
    
    while(i<strlen(temp)){

        if(isalnum(temp[i]) || temp[i] == '$'){
            infix[j] = 'v';
            i++;j++;
            while(isalnum(temp[i]) || temp[i] == '$' || temp[i] == '.'){
                i++;
            }
        }else{
            infix[j] = temp[i];
            j++;i++;
        }

    }
    for(i=0,j=0;i<strlen(temp);i++){
        /*if(temp[i] == '*' && temp[i+1] == '*' ){
            buf[j] = 'E';
            i++;j++;
        }else*/ if(temp[i] == '(' || temp[i] == ')'||temp[i] == '[' || temp[i] == ']'||temp[i] == '{' || temp[i] == '}'){
            continue;
        }else{
            buf[j] = temp[i];
            j++;
        }
    }
    
    t1 = loadVal(buf,strchr(buf,'\0'));
    if(t1.status != SUCCESS){
        return t1;
    }else{
        ret.status = SUCCESS;
        return ret;
    }


}

#endif
