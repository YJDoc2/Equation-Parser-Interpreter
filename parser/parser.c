#include <stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include "./typedef.c"
#include "./preparser.c"
#include "./stacks.c"
#include "./queues.c"

#ifndef PARSER
#define PARSER

//printf("\nError in Parsing Expression %s at %d :: %s\n",inS,pos,ret.error_info);
#define CHECK(ret,inS,pos)({\
            if(ret.status != SUCCESS){\
                return ret;\
            }\
        })

char postfix[150];
int linear= 0,poly =0;

int priority(char c){
    if(c == '^'){
        return 4;
    }else if(c =='*'||c=='/'||c == '%'){
        return 3;
    }else if(c =='+'||c =='-'){
        return 2;
    }else {
        return 1;
    }
}


//*converts infix expression which is in terms of v and operators
//* into a postfix expression.
Result convert(char in[],char *end){

    int i =0,j=0,len=0;
    float val =0.0;
    char x,t;
    Result temp;
    if(end<in){
        temp.status = ERROR;
        strcpy(temp.error_info,"End Pointer Greater Than Start");
        return temp;
    }
    temp = preparse(in,end);
    CHECK(temp,in,0);
    memset(buf,'\0',150);
    for(i=0,j=0;i<strlen(infix);i++){
        /*if(infix[i] == '*' && infix[i+1] == '*' ){
            buf[j] = 'E';
            i++;j++;
        }else*/{
            buf[j] = infix[i];
            j++;
        }
    }
    strcpy(infix,buf);
    x = infix[0];
    i =0;j=0;
    while(x!='\0'){

        if(x =='v'){
            postfix[j++] = x;
        }else if(x =='(' || x =='[' ||x =='{'  ){
            pushOp(x);
        }else if(x==')' || x ==']' || x =='}'){
            temp = popOp();
            CHECK(temp,infix,i+1);
            t=(char)temp.data;
            
            while(t != '(' && t !='[' && t !='{'  ){
               
                postfix[j] = t;
                j++;
                temp = popOp();
                CHECK(temp,infix,i+1);
                t = (char)temp.data;
            }
        }else if(x == '+'||x == '-'||x == '*'||x == '/'||x == '%'||x == '^'){
            if(opTop ==NULL||priority(x)>priority((char)peekOp().data)){
                pushOp(x);
            }else{
                while(opTop!=NULL && priority(x)<=priority((char)peekOp().data)){

                    temp = popOp();
                    CHECK(temp,infix,i+1);
                    t = (char)temp.data;
                    postfix[j] = t;
                    j++;
                }
                
                pushOp(x);
            }
        }
        i++;
        x = infix[i];
       

        
    }
    
     while(opTop!= NULL){
        temp = popOp();
        CHECK(temp,infix,i+1);
        t = (char)temp.data;
        postfix[j] = t;
        j++;
     }
    temp.status = SUCCESS;
    return temp;

}

//*Evaluates a postfix expression expressed in v and operators 
//*by using values enqued in loadVal of preparser
Result eval(){
    int temp =0,i=0;
    char op;
    float t =0.0,op1,op2;
    op = postfix[i];
    Result r,ret;
    while( op != '\0'){
        if(postfix[i] == 'v'){
            r = deQVal();
            CHECK(r,postfix,i+1); 
            push(r.data);
        }else{
            r = pop();
            CHECK(r,postfix,i+1);
            op2 = r.data;
            r = pop();
            CHECK(r,postfix,i+1);
            op1 = r.data;
            switch(op){
                case '+':{ 
                    push(op1+op2);
                    break;
                    }
                case '-':{
                    push(op1-op2);
                    break;
                    }
                case '*':{
                    push(op1*op2);
                    break;
                    }
                case '/':{
                    if(-1E-36<op2 && op2<1E-36){
                        ret.status = MATH_ERROR;
                        sprintf(ret.error_info,"Cannot divide by Very small number,almost equal to zero");
                        return ret;
                    }
                    push(op1/op2);
                    break;
                    }
                case '%':{
                    if((float)-1E-36<op2 && op2<(float)1E-36){
                        ret.status = MATH_ERROR;
                        sprintf(ret.error_info,"Cannot Take remainder by Very small number,almost equal to zero");
                        return ret;
                    }
                    push(fmodf(op1,op2));
                    break;
                    }
                case '^' : {
                    if(op1<0){
                        ret.status = MATH_ERROR;
                        sprintf(ret.error_info,"Cannot Exponentiate Negetive number to a fraction power");
                        return ret;
                    }
                    push(pow(op1,op2));
                    break;
                    }
            }
        }
        op = postfix[++i];
    }
    r = pop();
    CHECK(r,postfix,i);
    ret.status = SUCCESS;
    ret.data = r.data;
    return ret;


}

Result bracketCheck(char *in,char *end){
    char temp;
    int l = end-in;
    int i, flag=1;
    Result ret;
    gStack *iniTop = getTop();
    for(i = 0; i<l ;i++)
    {
        if(in[i]=='(' || in[i]=='[' || in[i]=='{')
            push(in[i]);
        if(in[i]==')' || in[i]==']' || in[i]=='}')
            if(getTop() == NULL)
                flag=0;
            else
            {
                temp=(char)(pop()).data;
                if(in[i]==')' && (temp=='[' || temp=='{'))
                    flag=0;
                if(in[i]=='}' && (temp=='(' || temp=='['))
                    flag=0;
                if(in[i]==']' && (temp=='(' || temp=='{'))
                    flag=0;
            }
    }
    if(getTop() != iniTop)
        flag=0;
    setTop(iniTop);
    if(flag==1){
        ret.status = SUCCESS;
        return ret;
    }else{
        ret.status = ERROR;
        sprintf(ret.error_info,"All Brackets Are not matched");
        return ret;
    }
        
}

Result parse(char *in, char *end){
    Result temp;
    char c[10];
    char *start = in;
    initPreparse();

    temp = getVar("Ans");
    if(temp.status == VARIABLE_NOT_DEFINED){
        setVar("Ans",0.0);
    }

    memset(postfix,'\0',150);
    removeSpaces(in);
    temp = bracketCheck(in,end);
    if(temp.status != SUCCESS){
        flushQVal();
        return temp;
    }
    temp = checkAssign(in);
    if(temp.status != SUCCESS){
        flushQVal();
        return temp;
    }
    if(ASSIGN != -1){
        start = strchr(in,'=')+1;
    }else{
        start = in;
    }
    temp = convert(start,end);
    if(temp.status != SUCCESS){
        flushQVal();
        return temp;
        
    }
    temp = eval();
    if(temp.status != SUCCESS){
        flushQVal();
        return temp;
    }
    if(!linear && !poly){setVar("Ans",temp.data);}
    if(ASSIGN != -1){
        if(DEFAULT != -1){
            setDefVar(DEFAULT,temp.data);
        }else{
            if(EXISTING == -1){
                setVar(v_name,temp.data);
            }else{
                printf("Re-Write Existing Variable...? Y/N > > > ");
                fgets(c,10,stdin);
                if(c[0] == 'n' || c[0] == 'N'){
                    printf("Value Not Assigned...\n");
                }else{
                    setVar(v_name,temp.data);
                }
            }
        }
    }
    return temp;

}
#endif