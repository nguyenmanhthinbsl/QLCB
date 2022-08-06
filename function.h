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

int dem_CB_ChuaBay(PTR_ChuyenBay list);

bool hanhkhach_chuabay(PTR_ChuyenBay list_CB, char* CMND);
PTR_ChuyenBay check_maCB_chuabay(PTR_ChuyenBay list_CB, char *maCB);
void show_List_CB_chuabay(PTR_ChuyenBay l, int page_now, int count_CB);
int DatVe(PTR_ChuyenBay &First_CB, PTR_HK root_HK);
int HuyVe(PTR_ChuyenBay &First_CB, PTR_HK root_HK);
void show_List_CB(PTR_ChuyenBay First_CB);
void Init_Main(List_MayBay &list_MB, PTR_ChuyenBay &First_CB, PTR_HK &root_HK);
void Handle_Main();
void After_Main(List_MayBay &list_MB, PTR_ChuyenBay &First_CB, PTR_HK &root_HK);

int dem_CB_ChuaBay(PTR_ChuyenBay list){
	int count = 0;
	PTR_ChuyenBay p;
	for(p=list;p!=NULL;p=p->next) if(p->data.trangthai!=HOANTAT&&p->data.trangthai!=HUYCHUYEN) count++;
	return count;
}

void show_List_CB_chuabay(PTR_ChuyenBay l, int page_now, int count_CB){
	int MAXLIST = 10;
	ChuyenBay *temp = new ChuyenBay[count_CB];
	int dem = 0;
	PTR_ChuyenBay p;
	int count_page = (count_CB%MAXLIST==0)? (count_CB/MAXLIST) : (count_CB/MAXLIST+1);
	for(p=l;p!=NULL;p=p->next) if(p->data.trangthai!=HOANTAT)
		temp[dem++] = p->data;
	if(count_CB==0){
		gotoxy(30,11);
		cout<<"KHONG CO CHUYEN BAY NAO CHUA HOAN THANH";
		ShowCur(false);
		delete[] temp;
		return;
	}
	Clear_Frame_Main();
	gotoxy(2,11);
	cout<<"+------------------+---------------------+---------------------+-----------------------+--------------+";
	gotoxy(2,12);
	cout<<"|  MA CHUYEN BAY   |   NGAY GIO BAY      |   SO HIEU MAY BAY   |   SAN BAY DEN         | SO GHE TRONG |";
	if(page_now!=count_page)
		for(int i=(page_now-1)*MAXLIST; i<(page_now)*MAXLIST;i++){
			gotoxy(2,(13+i*2)-(page_now-1)*MAXLIST*2);
			cout<<"+------------------+---------------------+---------------------+-----------------------+--------------+";
			gotoxy(2,(14+i*2)-(page_now-1)*MAXLIST*2);
			cout<<"|"<<temp[i].ma_chuyenbay;
			gotoxy(21, (14+i*2)-(page_now-1)*MAXLIST*2);
			cout<<"|"<<temp[i].ngaykhoihanh.gio<<":"<<temp[i].ngaykhoihanh.phut<<" "<<temp[i].ngaykhoihanh.ngay<<"/"<<temp[i].ngaykhoihanh.thang<<"/"<<temp[i].ngaykhoihanh.nam;
			gotoxy(43,(14+i*2)-(page_now-1)*MAXLIST*2);
			cout<<"|"<<temp[i].sohieu_maybay;
			gotoxy(65, (14+i*2)-(page_now-1)*MAXLIST*2);
			cout<<"|"<<temp[i].sanbayden;
			gotoxy(89, (14+i*2)-(page_now-1)*MAXLIST*2);
			cout<<"|"<<sovechuaban(temp[i]);
			gotoxy(104, (14+i*2)-(page_now-1)*MAXLIST*2);
			cout<<"|";
		}
	else
		for(int i=(page_now-1)*MAXLIST;i<count_CB;i++){
			gotoxy(2,(13+i*2)-(page_now-1)*MAXLIST*2);
			cout<<"+------------------+---------------------+---------------------+-----------------------+--------------+";
			gotoxy(2,(14+i*2)-(page_now-1)*MAXLIST*2);
			cout<<"|"<<temp[i].ma_chuyenbay;
			gotoxy(21, (14+i*2)-(page_now-1)*MAXLIST*2);
			cout<<"|"<<temp[i].ngaykhoihanh.gio<<":"<<temp[i].ngaykhoihanh.phut<<" "<<temp[i].ngaykhoihanh.ngay<<"/"<<temp[i].ngaykhoihanh.thang<<"/"<<temp[i].ngaykhoihanh.nam;
			gotoxy(43,(14+i*2)-(page_now-1)*MAXLIST*2);
			cout<<"|"<<temp[i].sohieu_maybay;
			gotoxy(65, (14+i*2)-(page_now-1)*MAXLIST*2);
			cout<<"|"<<temp[i].sanbayden;
			gotoxy(89, (14+i*2)-(page_now-1)*MAXLIST*2);
			cout<<"|"<<sovechuaban(temp[i]);
			gotoxy(104, (14+i*2)-(page_now-1)*MAXLIST*2);
			cout<<"|";
		}
	gotoxy(2,wherey()+1);
	cout<<"+------------------+---------------------+---------------------+-----------------------+--------------+";
	delete[] temp;
}

bool hanhkhach_chuabay(PTR_ChuyenBay list_CB, char* CMND){
	PTR_ChuyenBay p;
	for(p=list_CB;p!=NULL;p=p->next)
		if(p->data.trangthai!=HUYCHUYEN && p->data.trangthai!=HOANTAT)
			for(int i=1;i<=p->data.soVe;i++){
				if(p->data.danhsachVe[i]==CMND) return true;
			}
	return false;
}

PTR_ChuyenBay check_maCB_chuabay(PTR_ChuyenBay list_CB, char *maCB){
	PTR_ChuyenBay p;
	for(p=list_CB; p!=NULL;p=p->next)
		if(p->data.trangthai!=HUYCHUYEN&&p->data.trangthai!=HOANTAT) if(strcmp(maCB, p->data.ma_chuyenbay)==0) return p;
	return NULL; 
}

int DatVe(PTR_ChuyenBay &First_CB, PTR_HK root_HK){
    Clear_Frame_Main();
    bool is_add_HK = true;
    int page_now = 1;
    int count_CB = dem_CB_ChuaBay(First_CB);
    int count_page = (count_CB%10==0)? (count_CB/10) : (count_CB/10+1);
    show_List_CB_chuabay(First_CB,page_now, count_CB);
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
    char key = 0;
    char maCB[MAX_LENGTH_MACB+1] = "";
    char CMND[MAX_LENGTH_CMND+1] = "";
    char ho[MAX_LENGTH_HO+1] = "";
    char ten[MAX_LENGTH_TEN+1] = "";
    char phai[4]= "";
    int maghe;
    char maghe_str[6]="";
    ShowCur(true);
    gotoxy(125,6);
    int run = 1;
    PTR_ChuyenBay p;
    while(run){
    	int y = wherey();
    	if(key==ESC) break;
		ShowCur(true);
    	switch(y){
    		case 6:{
    			nhapChuoi(maCB, MAX_LENGTH_MACB, key, NO_SPACE);
    			if(key==ESC){
    				run = 0;
    				key = 0;
    				break;
				}else{
					if(key==UP){
						key = 0;
						continue;
					}
					if(key==DOWN||key==ENTER||key==TAB) {
						p = check_maCB_chuabay(First_CB, maCB);
						if(p==NULL){
    						Show_Message("ERROR","KHONG TON TAI CHUYEN BAY");
    						gotoxy(125+strlen(maCB),6);
						}else gotoxy(125+strlen(CMND), 8);
						key = 0;
						continue;
					}
					if(key==PAGEUP){
						key = 0;
						if(page_now==1) continue;
						show_List_CB_chuabay(First_CB,--page_now, count_CB);
						gotoxy(125+strlen(maCB),6);
						continue;
					}
					if(key==PAGEDOWN){
						key = 0;
						if(page_now==count_page) continue;
						show_List_CB_chuabay(First_CB, ++page_now, count_CB);
						gotoxy(125+strlen(maCB),6);
						continue;
					}
				}
				break;
			}
			case 8:{
    			nhapChuoi(CMND, MAX_LENGTH_CMND, key, ONLY_NUMBER);
    			if(key==ESC){
    				run = 0;
    				key = 0;
    				break;
				}else{
					if(key==UP){
						key = 0;
						gotoxy(125+strlen(maCB), 6);
						continue;
					}
					if(key==DOWN||key==ENTER||key==TAB) {
						if(strlen(CMND)!=9&&strlen(CMND)!=12){
    						Show_Message("ERROR","CMND KHONG HOP LE");
    						gotoxy(125+strlen(CMND), 8);
    						key = 0;
    						continue;
   						}
						PTR_HK hk = timkiem_HK(root_HK, CMND);
						if(hk!=NULL){
							is_add_HK = false;
							gotoxy(125,10); cout<<"                              ";
							gotoxy(125,10); cout<<hk->info.ho;
							strcpy(ho, hk->info.ho);
							gotoxy(125,12); cout<<"                    ";
							gotoxy(125,12); cout<<hk->info.ten;
							strcpy(ten, hk->info.ten);
							gotoxy(125,14); cout<<"   ";
							gotoxy(125,14);
							if(hk->info.phai==1){
								cout<<"NAM";
								strcpy(phai,"NAM");
							}
							else{
								cout<<"NU";
								strcpy(phai,"NU");
							}
						}else{
							is_add_HK = true;
						}
						if(!is_add_HK)gotoxy(125+strlen(maghe_str), 16);
						else gotoxy(125+strlen(ho), 10);
						key = 0;
						continue;
					}
					if(key==PAGEUP){
						key = 0;
						if(page_now==1) continue;
						show_List_CB_chuabay(First_CB,--page_now, count_CB);
						gotoxy(125+strlen(CMND),8);
						continue;
					}
					if(key==PAGEDOWN){
						key = 0;
						if(page_now==count_page) continue;
						show_List_CB_chuabay(First_CB, ++page_now, count_CB);
						gotoxy(125+strlen(CMND),8);
						continue;
					}
				}
				break;
			}
			case 10:{
    			nhapChuoi(ho, MAX_LENGTH_HO, key, ONLY_WORD);
    			if(key==ESC){
    				run = 0;
    				key = 0;
    				break;
				}else{
					if(key==UP){
						key = 0;
						gotoxy(125+strlen(CMND), 8);
						continue;
					}
					if(key==DOWN||key==ENTER||key==TAB) {
						LTrim(ho);
    					RTrim(ho);
    					if(strlen(ho)==0){
    						Show_Message("ERROR","HO KHONG HOP LE");
    						gotoxy(125+strlen(ho), 10);
						}else gotoxy(125+strlen(ten), 12);
						key = 0;
						continue;
					}
					if(key==PAGEUP){
						key = 0;
						if(page_now==1) continue;
						show_List_CB_chuabay(First_CB,--page_now, count_CB);
						gotoxy(125+strlen(ho),10);
						continue;
					}
					if(key==PAGEDOWN){
						key = 0;
						if(page_now==count_page) continue;
						show_List_CB_chuabay(First_CB, ++page_now, count_CB);
						gotoxy(125+strlen(ho),10);
						continue;
					}
				}
				break;
			}
			case 12:{
    			nhapChuoi(ten, MAX_LENGTH_TEN, key, ONLY_WORD);
    			if(key==ESC){
    				run = 0;
    				key = 0;
    				break;
				}else{
					if(key==UP){
						key = 0;
						gotoxy(125+strlen(ho), 10);
						continue;
					}
					if(key==DOWN||key==ENTER||key==TAB) {
						LTrim(ten);
    					RTrim(ten);
						if(strlen(ten)==0){
							Show_Message("ERROR", "TEN KHONG HOP LE");
							gotoxy(125+strlen(ten), 12);
						}else gotoxy(125+strlen(phai), 14);
						key = 0;
						continue;
					}
					if(key==PAGEUP){
						key = 0;
						if(page_now==1) continue;
						show_List_CB_chuabay(First_CB,--page_now, count_CB);
						gotoxy(125+strlen(ten),12);
						continue;
					}
					if(key==PAGEDOWN){
						key = 0;
						if(page_now==count_page) continue;
						show_List_CB_chuabay(First_CB, ++page_now, count_CB);
						gotoxy(125+strlen(ten),12);
						continue;
					}
				}
				break;
			}
			case 14:{
    			nhapChuoi(phai, 3, key, NO_SPACE);
    			if(key==ESC){
    				run = 0;
    				key = 0;
					break;
				}else{
					if(key==UP){
						key = 0;
						gotoxy(125+strlen(ten), 12);
						continue;
					}
					if(key==DOWN||key==ENTER||key==TAB) {
						if(strcmp(phai,"NAM")!=0&&strcmp(phai,"NU")!=0){
							Show_Message("ERROR", "PHAI KHONG HOP LE");
							gotoxy(125+strlen(phai), 14);
						} else gotoxy(125+strlen(maghe_str), 16);
						key = 0;
						continue;
					}
					if(key==PAGEUP){
						key = 0;
						if(page_now==1) continue;
						show_List_CB_chuabay(First_CB,--page_now, count_CB);
						gotoxy(125+strlen(phai),14);
						continue;
					}
					if(key==PAGEDOWN){
						key = 0;
						if(page_now==count_page) continue;
						show_List_CB_chuabay(First_CB, ++page_now, count_CB);
						gotoxy(125+strlen(phai),14);
						continue;
					}
				}
				break;
			}
			case 16:{
    			nhapChuoi(maghe_str, 5, key, ONLY_NUMBER);
    			if(key==ESC){
    				run = 0;
    				key = 0;
					break;
				}
    			if(key==ENTER){
    				maghe = toInt(maghe_str);
    				if(maghe<=0||maghe>p->data.soVe){
						Show_Message("ERROR", "MA GHE KHONG DUNG");
						gotoxy(125+strlen(maghe_str), 16);
						key = 0;
						continue;
					}
    				if(p->data.danhsachVe[maghe]!="0"){
    					Show_Message("ERROR", "GHE DA CO NGUOI DANG KI");
						gotoxy(125+strlen(maghe_str), 16);
						key = 0;
						continue;
					}
					
//    				if(is_add_HK){
//    					
//					}else{
//						if(!hanhkhach_chuabay(First_CB, CMND)){
//								
//						}
//						else{
//							
//						}
//					}
				}else{
					if(key==UP){
						if(!is_add_HK) gotoxy(125+strlen(CMND), 8);
						else gotoxy(125+strlen(phai), 14);
						key = 0;
						continue;
					}
					if(key==DOWN) {
						key = 0;
						continue;
					}
					if(key==PAGEUP){
						key = 0;
						if(page_now==1) continue;
						show_List_CB_chuabay(First_CB,--page_now, count_CB);
						gotoxy(125+intToString(maghe).size(), 16);
						continue;
					}
					if(key==PAGEDOWN){
						key = 0;
						if(page_now==count_page) continue;
						show_List_CB_chuabay(First_CB, ++page_now, count_CB);
						gotoxy(125+intToString(maghe).size(), 16);
						continue;
					}
				}
				break;
			}
		}
    	
	}
	
	Clear_Frame_Main();
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

