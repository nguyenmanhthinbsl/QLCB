#pragma once
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <cstring>
#include <sstream>
#include "mylib.h"
#include "date.h"

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
char* tocharDate(Day_time &mytime);
void input_date(char* date, char &key);

/*Function Deployment*/

char* tocharDate(Day_time &mytime)
{
	char *temp = new char[100];
	temp[0] = '\0';
	
	if (mytime.ngay < 10)  
	 	strcat(temp, "0");
    strcpy(temp, concat(temp, intToString(mytime.ngay)).c_str());
	strcat(temp, "/");
	if (mytime.thang < 10) 
		strcat(temp, "0");
    strcpy(temp, concat(temp, intToString(mytime.thang)).c_str());
	strcat(temp, "/");
	if (mytime.nam < 10)
		strcat(temp, "0");
	if (mytime.nam < 100)
		strcat(temp, "0");
	if (mytime.nam < 1000)
		strcat(temp, "0");
    strcpy(temp, concat(temp, intToString(mytime.nam)).c_str());
	strcat(temp, " ");
	if (mytime.gio < 10)  
	 	strcat(temp, "0");
    strcpy(temp, concat(temp, intToString(mytime.gio)).c_str());
	strcat(temp, ":");
	if (mytime.phut < 10)  
	 	strcat(temp, "0");
    strcpy(temp, concat(temp, intToString(mytime.phut)).c_str());
	return temp;
}


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
    ShowCur(true);
    char input;
    int x,y;
    while((input = getch())!=ENTER){
    	if(input==TAB||input==ESC){
    		key=input;
    		return;
		}
		if(input==is_press_arrow_key||input==is_press_f){
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
            if(type==ONLY_NUMBER)
            	if(input<'0'||input>'9') continue;
			else if(type==ONLY_WORD)
				if((input<'A'||input>'Z')&&(input<'a'||input>'z')&&input!=' ') continue;
			else if(type==NO_SPACE)
				if(input==' ') continue;
			if(input==' ')
				if(str[strlen(str)-1]==' ') continue;
			if(input>='a'&&input<='z')
                input = input - 32;
            cout<<input;
            str[strlen(str)] = input;
            str[strlen(str)] = '\0';
        }
    }
    key = ENTER;
}

void input_date(char* date, char &key){
	ShowCur(true);
	char input;
	while(1){
		input=getch();
		if(input==ESC||input==ENTER||input==TAB){
			key = input;
			return;
		}else if(input==is_press_arrow_key||input==is_press_f){
			key = getch();
			return;
		}else if(input==BACKSPACE){
			if(strlen(date)==0) continue;
			else if(strlen(date)==15||strlen(date)==12||strlen(date)==7||strlen(date)==4){
				outtextxy(wherex()-2, wherey(),"  ");
				gotoxy(wherex()-2, wherey());
				date[strlen(date)-1]='\0';
				date[strlen(date)-1]='\0';
			}else{
				outtextxy(wherex()-1, wherey(), " ");
				gotoxy(wherex()-1, wherey());
				date[strlen(date)-1]='\0';
			}
		}else if(input>='0'&&input<='9'){
			if(strlen(date)==16) continue;
			else if(strlen(date)==1||strlen(date)==4){
				cout<<input<<"/";
				date[strlen(date)]=input;
				date[strlen(date)]='/';
			}else if(strlen(date)==9){
				cout<<input<<" ";
				date[strlen(date)]=input;
				date[strlen(date)]=' ';
			}else if(strlen(date)==12){
				cout<<input<<":";
				date[strlen(date)]=input;
				date[strlen(date)]=':';
			}else if(strlen(date)==2||strlen(date)==5){
				cout<<"/"<<input;
				date[strlen(date)]='/';
				date[strlen(date)]=input;
			}else if(strlen(date)==10){
				cout<<" "<<input;
				date[strlen(date)]=' ';
				date[strlen(date)] = input;
			}else if(strlen(date)==13){
				cout<<":"<<input;
				date[strlen(date)]=':';
				date[strlen(date)]=input;
			}else{
				cout<<input;
				date[strlen(date)]=input;
			}
		}
	}
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
