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

unsigned long long ChangeCharToNum (const char str[]);
int toInt(string s);
int toInt(char* s);
string intToString(int i);
void nhapChuoi(char* str,int length, char &key, int type);
void LTrim(char* S);
void RTrim(char* S);
void Trim(char* S);
void Upper(char* S);
string concat(string a, string b);

/*Function Deployment*/

unsigned long long ChangeCharToNum (const char str[]){
	
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

void nhapChuoi(char* str, int length, char &key, int type){
    char input;
    int x,y;
    while((input = getch())!=ENTER){
    	if(input==TAB||input==ESC){
    		key=input;
    		return;
		}
    	if(input==is_press_f ){
    		input=getch();
            if(input==F4) {
                key=F4;
    		    continue;
            }
		}
		if(input==is_press_arrow_key){
			key = getch();
			return;
		}
        if(input==BACKSPACE){
            if(strlen(str)==0) continue;
            else{
                x = wherex();
                y = wherey();
                gotoxy(x-1,y);
                cout<<" ";
                gotoxy(x-1,y);
                str[strlen(str)-1] = '\0';
            }
        }else{
            if(strlen(str)==length) continue;
            if(type==ONLY_NUMBER){
            	if(input<'0'||input>'9') continue;
			}else if(type==ONLY_WORD){
				if((input<'A'||input>'Z')&&(input<'a'||input>'z')&&input!=' ') continue;
			}else if(type==NO_SPACE){
				if(input==' ') continue;
			}
			if(input==' '){
				if(str[strlen(str)-1]==' ') continue;
			}
			if(input>='a'&&input<='z')
            input = input - 32;
            cout<<input;
            str[strlen(str)] = input;
        }
    }
    key = ENTER;
}

void LTrim(char* S){
    while(S[0]==' '&&strlen(S)!=0){
        for(int i=1;i<strlen(S);i++){
            S[i-1] = S[i];
        }
        S[strlen(S)-1] = '\0';
    }
}

void RTrim(char* S){
    while(S[strlen(S)-1]==' '&&strlen(S)!=0){
        S[strlen(S)-1] = '\0';
    }
}

void Trim(char* S){
    for(int i=0;i<strlen(S);i++)
        if(S[i]==' '){
            for(int j=i+1;j<strlen(S);j++)
                S[j-1] = S[j];
            S[strlen(S)-1] = '\0';
            i--;
        }
}

void Upper(char* S){
    for(int i=0;i<strlen(S);i++)
        if(S[i]>='a'&&S[i]<='z')
            S[i] = S[i] - 32;
}

string concat(string a, string b){
    return a+b;
}
