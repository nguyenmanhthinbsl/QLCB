#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "mylib.h"

using namespace std;

#define width 156
#define height 44
#define width_title 110
#define height_title 6

#define Top_Right 187
#define Bot_Right 188
#define Top_Left 201
#define Bot_Left 200
#define Horizontal 205
#define Vertical 186
#define Fork_Left_2_Line 204
#define Fork_Right_2_Line 185
#define Fork_Bot_2_Line 202
#define Fork_Top_2_Line 203

void Frame_Drawing(int top, int bot, int left, int right);
void Clear_Frame_Main();
void Clear_Frame_Input();
void Draw_A_Horizontal_Line(int y, int x_left, int x_right);
void Draw_A_Vertical_Line(int x, int y_top, int x_bot);
void Draw_Button(string name_button, int x, int y, int color);
void Draw_Name_Project();
void Draw_GoodBye();
void Show_Message(string type, string mess);
int form_confirm(string mess);
void outtextxy(int x, int y, string mess);

/*Function Deployment*/
void Frame_Drawing(int top, int bot, int left, int right) {
    int i;
    gotoxy(left, top);
    cout << (char)Top_Left;
    gotoxy(left, bot);
    cout << (char)Bot_Left;
    gotoxy(right, top);
    cout << (char)Top_Right;
    gotoxy(right, bot);
    cout << (char)Bot_Right;
    for (i = left + 1; i < right; i++) {
        gotoxy(i, top);
        cout << (char)Horizontal;
        gotoxy(i, bot);
        cout << (char)Horizontal;
    }
    for (i = top + 1; i < bot; i++) {
        gotoxy(left, i);
        cout << (char)Vertical;
        gotoxy(right, i);
        cout << (char)Vertical;
    }
}

void Draw_A_Horizontal_Line(int y, int x_left, int x_right) {
    int i;
    gotoxy(x_left, y);
    cout << (char)Fork_Left_2_Line;
    gotoxy(x_right, y);
    cout << (char)Fork_Right_2_Line;
    for (i = x_left + 1; i < x_right; i++) {
        gotoxy(i, y);
        cout << (char)Horizontal;
    }
}

void Draw_A_Vertical_Line(int x, int y_top, int y_bot) {
    int i;
    gotoxy(x, y_top);
    cout << (char)Fork_Top_2_Line;
    gotoxy(x, y_bot);
    cout << (char)Fork_Bot_2_Line;
    for (i = y_top + 1; i < y_bot; i++) {
        gotoxy(x, i);
        cout << (char)Vertical;
    }
}

void Draw_Button(string name_button, int x, int y, int color) {
    SetColor(color);
    gotoxy(x, y);
    Frame_Drawing(y, y + 2, x, x + name_button.size() + 1);
    gotoxy(x + 1, y + 1);
    cout << name_button;
    SetColor(7);
}

void Draw_Name_Project() {
    int k = 1;
    char data[1000];
    SetColor(6);
    ifstream infile;
    infile.open("./template/logo.txt");
    while (infile.getline(data, 1000)) {
        gotoxy((width_title - strlen(data)) / 2, k++);
        cout << data;
    }
    SetColor(7);
}

void Draw_GoodBye(){
    int k = 20;
    char data[1000];
    SetColor(6);
    ifstream infile;
    infile.open("./template/good_bye.txt");
    while (infile.getline(data, 1000)) {
        gotoxy((width_title - strlen(data)) / 2, k++);
        cout << data;
    }
    SetColor(7);
    getch();
}

void Clear_Frame_Main(){
    ShowCur(false);
    for(int j=7; j<=37;j++){
        gotoxy(1,j);
        cout<<"                                                                                                             ";
    }
}

void Clear_Frame_Input(){
    ShowCur(false);
    for(int j=1; j<=37;j++){
        gotoxy(111,j);
        cout<<"                                             ";
    }
}

void Show_Message(string type, string mess){
	ShowCur(false);
	int x = 110 + ((156-110-mess.size())/2);
	int y = 35;
	if(type=="ERROR") Draw_Button(mess, x, y, 4);
	else Draw_Button(mess, x, y, 3);
	Sleep(1500);
	for(int i=x; i<=x+mess.size()+2;i++){
		for(int j=y;j<=y+4;j++){
			gotoxy(i,j);
			cout<<" ";
		}
	}
}

int form_confirm(string mess){
	int chon = 1;
	ShowCur(false);
	int x = 110+ (156-110-mess.size())/2;
    string space = "";
    for(int i=x;i<=x+mess.size()+1;i++){
        space+=" ";
    }
	Frame_Drawing(25, 32, x, x+mess.size()+1);
	gotoxy(x+1, 26);
	cout<<mess;
	Draw_Button("YES", x+(mess.size()-5)/3+1,28, 3);
	Draw_Button("NO", x+(mess.size()-5)/3*2+4,28, 7);
	char input;
	while(true){
		input=getch();
		if(input==is_press_arrow_key){
			input=getch();
			if(input==LEFT){
				if(chon==1) continue;
				else{
					chon=1;
					Draw_Button("YES", x+(mess.size()-5)/3+1,28, 3);
					Draw_Button("NO", x+(mess.size()-5)/3*2+4,28, 7);
				}
			}
			if(input==RIGHT){
				if(chon==0) continue;
				else{
					chon=0;
					Draw_Button("YES", x+(mess.size()-5)/3+1,28, 7);
					Draw_Button("NO", x+(mess.size()-5)/3*2+4,28, 3);
				}
			}
		}
		if(input==is_press_f){
			getch();
			continue;
		}
		if(input==ESC){
            for (int j = 25; j <= 32; j++)
            {
                gotoxy(x, j);
                cout << space;
            }
            return -1;
        }
		if(input==ENTER){
            for (int j = 25; j <= 32; j++)
            {
                gotoxy(x, j);
                cout << space;
            }
            return chon;
        }
	}
}

void outtextxy(int x, int y, string mess){
    if(x==125){
        gotoxy(x,y);
        cout<<"                              ";
    }
    gotoxy(x,y);
    cout<<mess;
}
