#include <stdio.h>

#ifndef UTIL
#define UTIL

//* Gets the First occurence of character c, case-ignored in range in->end
char *getCharPos(char *in, char *end,char c){
    char *t = in;

    if(end<in){
        return NULL;
    }
    while(t<=end){
        if(tolower(*t) == tolower(c)){
            return t;
        }else{
            t = t+1;
        }
    }
    return NULL;
}


#endif