#pragma once
#include <conio.h>
#include "console.h"
#include "entity.h"
#include "file.h"

int SelectLV1();
int SelectLV2_1();
int SelectLV2_2();
int Insert_MB(List_MayBay &list, MayBay* maybay);
void show_List_MB(List_MayBay list);
void Deletedequi(PTR_HK &root_HK);
int DatVe(PTR_ChuyenBay &First_CB, PTR_HK root_HK);
int HuyVe(PTR_ChuyenBay &First_CB, PTR_HK root_HK);
void show_List_CB(PTR_ChuyenBay First_CB);
void Init_Main(List_MayBay &list_MB, PTR_ChuyenBay &First_CB, PTR_HK &root_HK);
void Handle_Main();
void After_Main(List_MayBay &list_MB, PTR_ChuyenBay &First_CB, PTR_HK &root_HK);

int DatVe(PTR_ChuyenBay &First_CB, PTR_HK root_HK){
    Clear_Frame_Main();
    gotoxy(115, 6);
    cout<<"Ma CB: ";
    gotoxy(115, 8);
    cout<<"CMND: ";
    gotoxy(115,10);
    cout<<"Ho: ";
    gotoxy(115, 12);
    cout<<"Ten: ";
    gotoxy(115,14);
    cout<<"Phai: ";
    gotoxy(115,16);
    cout<<"Ma Ghe: ";
}

int HuyVe(PTR_ChuyenBay &First_CB, PTR_HK root_HK){
    Clear_Frame_Main();
    gotoxy(115, 6);
    cout<<"Ma CB: ";
    gotoxy(115, 8);
    cout<<"CMND: ";
    gotoxy(115,10);
    cout<<"Ho: ";
    gotoxy(115, 12);
    cout<<"Ten: ";
    gotoxy(115,14);
    cout<<"Phai: ";
    gotoxy(115,16);
    cout<<"Ma Ghe: ";
}

/*Function Deployment*/
void Init_Main(List_MayBay &list_MB, PTR_ChuyenBay &First_CB, PTR_HK &root_HK)
{   
    

    int x = 4;
    resizeConsole(1300, 760);
    DisableResizeWindow();
    Remove_Scrollbars();
    DisableCtrButton(0, 1, 1);
    ShowCur(false);
    Frame_Drawing(0, height, 0, width);
    Draw_A_Horizontal_Line(height - 4, 0, width);
    Draw_A_Vertical_Line(width_title, 0, height - 4);
    Draw_A_Horizontal_Line(height_title, 0, width_title);
    Draw_Name_Project();
    Draw_Button("ESC:THOAT", x, height - 3, 7);
    x = wherex() + 2;
    Draw_Button("ENTER:CHON", x, height - 3, 7);
    x = wherex() + 2;
    Draw_Button("UP:LEN", x, height - 3, 7);
    x = wherex() + 2;
    Draw_Button("DOWN:XUONG", x, height - 3, 7);
    x = wherex() + 2;
    Draw_Button("PAGEUP:TRANG TRUOC", x, height - 3, 7);
    x = wherex() + 2;
    Draw_Button("PAGEDOWN:TRANG SAU", x, height - 3, 7);
    x = wherex() + 2;
    Draw_Button("INSERT:THEM", x, height - 3, 7);
    x = wherex() + 2;
    Draw_Button("DELETE:XOA", x, height - 3, 7);
    x = wherex() + 2;
    Draw_Button("CTRL+F:TIM KIEM", x, height - 3, 7);
    x = wherex() + 2;
    Draw_Button("F4:CHINH SUA", x, height - 3, 7);
    
    Read_File(list_MB, First_CB, root_HK);
}

void show_List_MB(List_MayBay list){
	gotoxy(0,0);
	for(int i=0;i<list.soluong;i++){
		cout<<list.nodes[i]->loai_maybay<<"\t"<<list.nodes[i]->sohieu_maybay<<"\t"<<list.nodes[i]->socho<<"\t"<<list.nodes[i]->sochuyendabay<<"\n";
	}
}



void show_List_CB(PTR_ChuyenBay First){
	PTR_ChuyenBay p;
	for(p = First;p!=NULL;p=p->next){
		cout<<p->data.ma_chuyenbay<<endl;
		print_TG(p->data.ngaykhoihanh);
		for(int i=1;i<=p->data.soVe;i++){
			cout<<p->data.danhsachVe[i]<<" ";
		}
		cout<<endl;
	}
}

void Deletedequi(PTR_HK &root_HK){
	if(root_HK != NULL){
		Deletedequi(root_HK->left);
		Deletedequi(root_HK->right);
	    delete root_HK;
	}
}

void After_Main(List_MayBay &list_MB, PTR_ChuyenBay &First_CB, PTR_HK &root_HK)
{
	
	Write_File(list_MB, First_CB, root_HK);
    
    //Delete Memory List May Bay
    for(int i=0;i<list_MB.soluong;i++){
        if(list_MB.nodes[i]==NULL) break;
        delete list_MB.nodes[i];
    }

    //Delete Memory List Chuyen Bay
    while(First_CB!=NULL){
        PTR_ChuyenBay temp = First_CB;
        First_CB = First_CB->next;
        delete[] temp->data.danhsachVe;
        delete temp;
    }
	
	//Delete Memory List Hanh Khach
    Deletedequi(root_HK);

    Clear_Frame_Main();
    Clear_Frame_Input();
    Draw_GoodBye();
}

int SelectLV1()
{
    string listMenu[2] = {" QUAN LY MAY BAY  ", "QUAN LY CHUYEN BAY"};
    for (int i = 0; i < 2; i++)
    {
        Draw_Button(listMenu[i], 40, 15 + i * 4, 7);
    }
    int key = 0;
    Draw_Button(listMenu[key], 40, 15, 6);
    char input;
    while (1)
    {
        input = getch();
        if (input == ENTER)
            break;
        if (input == ESC)
            return -1;
        if (input == is_press_arrow_key)
        {
            input = getch();
            if (input == UP && key != 0)
            {
                Draw_Button(listMenu[key], 40, 15+key*4, 7);
                --key;
                Draw_Button(listMenu[key], 40, 15, 6);
                continue;
            }
            else if (input == DOWN && key != 1)
            {
                Draw_Button(listMenu[key], 40, 15, 7);
                ++key;
                Draw_Button(listMenu[key], 40, 15+key*4, 6);
                continue;
            }
            else
                continue;
        }
    }
    return key;
}

int SelectLV2_1()
{
    Clear_Frame_Main();
    Clear_Frame_Input();
    string listMenu_1[1] = {"DANH SACH MAY BAY"};
    for (int i = 0; i < 1; i++)
    {
        Draw_Button(listMenu_1[i], 40, 15 + i * 4, 7);
    }
    Draw_Button(listMenu_1[0], 40, 15, 6);
    char input;
    while ((input = getch()) != ENTER)
    {
        if (input == ESC)
            return -1;
        else continue;
    }
    return 1;
}

int SelectLV2_2()
{
    Clear_Frame_Main();
    Clear_Frame_Input();
    string listMenu_2[3] = {"DANH SACH CHUYEN BAY",
                            "       DAT VE       ",
                            "       HUY VE       "};
    for (int i = 0; i < 3; i++)
    {
        Draw_Button(listMenu_2[i], 40, 15 + i * 4, 7);
    }
    int key = 0;
    Draw_Button(listMenu_2[key], 40, 15+4*key, 6);
    char input;
    while (1)
    {
        input = getch();
        if (input == ENTER)
            break;
        if (input == ESC)
            return -1;
        if (input == is_press_arrow_key)
        {
            input = getch();
            if (input == UP && key != 0)
            {
                Draw_Button(listMenu_2[key], 40, 15+4*key, 7);
                --key;
                Draw_Button(listMenu_2[key], 40, 15+4*key, 6);
                continue;
            }
            else if (input == DOWN && key != 2)
            {
                Draw_Button(listMenu_2[key], 40, 15+4*key, 7);
                ++key;
                Draw_Button(listMenu_2[key], 40, 15+4*key, 6);
                continue;
            }
            else
                continue;
        }
    }
    return key;
}

