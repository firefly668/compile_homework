#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
char c;
char token[50];
FILE* file;
typedef struct node{
    char token[50];
    char outForm[50];
}reservedWord;
reservedWord RW[15];
int symbol=0;
int num=0;
int resultValue=0;
void init(){
    strcpy(RW[1].token,"BEGIN");
    strcpy(RW[2].token,"END");
    strcpy(RW[3].token,"FOR");
    strcpy(RW[4].token,"IF");
    strcpy(RW[5].token,"THEN");
    strcpy(RW[6].token,"ELSE");
    strcpy(RW[7].token,":");
    strcpy(RW[8].token,"+");
    strcpy(RW[9].token,"*");
    strcpy(RW[10].token,",");
    strcpy(RW[11].token,"(");
    strcpy(RW[12].token,")");
    strcpy(RW[13].token,":=");
    strcpy(RW[1].outForm,"Begin");
    strcpy(RW[2].outForm,"End");
    strcpy(RW[3].outForm,"For");
    strcpy(RW[4].outForm,"If");
    strcpy(RW[5].outForm,"Then");
    strcpy(RW[6].outForm,"Else");
    strcpy(RW[7].outForm,"Colon");
    strcpy(RW[8].outForm,"Plus");
    strcpy(RW[9].outForm,"Star");
    strcpy(RW[10].outForm,"Comma");
    strcpy(RW[11].outForm,"LParenthesis");
    strcpy(RW[12].outForm,"RParenthesis");
    strcpy(RW[13].outForm,"Assign");
}
int isColon(){
    if(c==':') return 1;
    else return 0;
}
int isPlus(){
    if(c=='+') return 1;
    else return 0;
}
int isStar(){
    if(c=='*') return 1;
    else return 0;
}
int isComma(){
    if(c==',') return 1;
    else return 0;
}
int isLParenthesis(){
    if(c=='(') return 1;
    else return 0;
}
int isRParenthesis(){
    if(c==')') return 1;
    else return 0;
}
int isEqual(){
    if(c=='=') return 1;
    else return 0;
}
void getChar(){
    c=fgetc(file);
}
void unGetCh(){
    fseek(file,-1,SEEK_CUR);
}
void getNbc(){
    while(isspace(c=fgetc(file)));
    unGetCh();
}
void cat(){
    token[strlen(token)]=c;
}
int reserve(){
    for(int i=1;i<=6;i++)
        if(strcmp(RW[i].token,token)) return i;
    return 0;
}
void error(){
    printf("Unknown\n");
}
int getToken(){
    getNbc();
    getChar();
    if(isalpha(c)){
        while(isalpha(c)||isalnum(c)){
            cat();
            getChar();
        }
        unGetCh();
        resultValue = reserve();
    }
    else if(isalnum(c)){
        while(isalnum(c)){
            cat();
            getChar();
        }
        unGetCh();
        num=atoi(token);
        symbol=1;
    }
    else if(isColon()){
        getChar();
        if(isEqual()) resultValue=13;
        else {
            unGetCh(); resultValue=7;
        }
    }
    else if(isPlus()) resultValue=8;
    else if(isStar()) resultValue=9;
    else if(isComma()) resultValue=10;
    else if(isLParenthesis()) resultValue=11;
    else if(isRParenthesis()) resultValue=12;
    else error();
    if(resultValue){
        printf("%s\n",RW[resultValue].outForm);
    }
    else if(symbol=1){
        printf("Int(%d)\n",num);
    }
    else{
        printf("Ident(%s)\n",token);
    }
}
int main(int argc,char** argv){
    file = fopen(argv[1],"rt");
    while(1){
        int flag = getToken();
        if(flag!=1) break;
    }
    return 0;
} 