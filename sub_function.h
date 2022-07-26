#pragma once
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <cstring>
#include <sstream>
#include "mylib.h"

using namespace std;

unsigned long long ChangeCharToNum (char str[]);
int toInt(string s);
int toInt(char* s);
string intToString(int i);
int nhapSo();
char* nhapChuoi(int length);
char* LTrim(char* S);
char* RTrim(char* S);
char* Trim(char* S);
char* Upper(char* S);

/*Function Deployment*/

unsigned long long ChangeCharToNum (char str[]){
	
	unsigned long long n = 0;
	for(int i = 0; i<strlen(str); i++){
		
		n = n * 10;
		n += (str[i]-48);
	}
	return n;
}

int toInt(string s) {
    int num = 0;
    for (int i = 0; i < s.size(); i++) {
        num = num * 10 + s[i] - 48;
    }
    return num;
}

int toInt(char* s) {
    int num = 0;
    for (int i = 0; i < strlen(s); i++) {
        num = num * 10 + s[i] - 48;
    }
    return num;
}

string intToString(int i){
	stringstream ss;
	ss<<i;
	return ss.str();
}

int nhapSo(){
    int ret = 0;
    int x,y;
    char input;
    char str[100] = {'\0'};
    while((input = getch())!=ENTER){
        if((input<'0'||input>'9')&&input!=BACKSPACE) continue;
        if(input==BACKSPACE){
            if(strlen(str)==0) continue;
            else{
                x = wherex();
                y = wherey();
                gotoxy(x-1,y);
                cout<<" ";
                gotoxy(x-1,y);
                ret/=10;
                str[strlen(str)-1] = '\0';
            }
        }else{
            cout<<input;
            ret = ret*10+(int)input-'0';
            str[strlen(str)] = input;
        }
    }
    cout<<"\n";
    return ret;
}

char* nhapChuoi(int lenght){
    char ret[lenght+1] = {'\0'};
    cout<<strlen(ret);
    char input;
    int x,y;
    while((input = getch())!=ENTER){
        if(input==BACKSPACE){
            if(strlen(ret)==0) continue;
            else{
                x = wherex();
                y = wherey();
                gotoxy(x-1,y);
                cout<<" ";
                gotoxy(x-1,y);
                ret[strlen(ret)-1] = '\0';
            }
        }else{
            if(strlen(ret)==lenght) continue;
            cout<<input;
            ret[strlen(ret)] = input;
        }
    }
    cout<<endl;
    return ret;
}

char* LTrim(char* S){
    while(S[0]==' '&&strlen(S)!=0){
        for(int i=1;i<strlen(S);i++){
            S[i-1] = S[i];
        }
        S[strlen(S)-1] = '\0';
    }
    return S;
}

char* RTrim(char* S){
    while(S[strlen(S)-1]==' '&&strlen(S)!=0){
        S[strlen(S)-1] = '\0';
    }
    return S;
}

char* Trim(char* S){
    for(int i=0;i<strlen(S);i++)
        if(S[i]==' '){
            for(int j=i+1;j<strlen(S);j++)
                S[j-1] = S[j];
            S[strlen(S)-1] = '\0';
            i--;
        }
}

char* Upper(char* S){
    for(int i=0;i<strlen(S);i++)
        if(S[i]>='a'&&S[i]<='z')
            S[i] = S[i] - 32;
    return S;
}

