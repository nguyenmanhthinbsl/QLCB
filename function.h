#pragma once
#include <conio.h>
#include <cstring>
#include "console.h"
#include "entity.h"
#include "file.h"

int SelectLV1();
int SelectLV2_1();
int SelectLV2_2();
int Insert_MB(List_MayBay &list, MayBay* maybay);
void show_List_MB(List_MayBay list);
void Deletedequi(PTR_HK &root_HK);
int dem_CB(PTR_ChuyenBay list, string status);
PTR_ChuyenBay hanhkhach_chuahoanthanhchuyenbay(PTR_ChuyenBay list_CB, char* CMND);
PTR_ChuyenBay check_maCB_chuabay(PTR_ChuyenBay list_CB, char *maCB);
void show_List_CB(PTR_ChuyenBay l, int page_now, int count_CB, string status);
int DatVe(PTR_ChuyenBay &First_CB, PTR_HK root_HK);
int HuyVe(PTR_ChuyenBay &First_CB, PTR_HK root_HK);
void Init_Main(List_MayBay &list_MB, PTR_ChuyenBay &First_CB, PTR_HK &root_HK);
void Handle_Main();
void After_Main(List_MayBay &list_MB, PTR_ChuyenBay &First_CB, PTR_HK &root_HK);
void show_dsVe(PTR_ChuyenBay &p,PTR_HK root, int page_now);
void XuLyCB(PTR_ChuyenBay &p, PTR_HK root);
void XuLyDSChuyenBay(PTR_ChuyenBay &First_CB, PTR_HK root);

int dem_CB(PTR_ChuyenBay list, string status){
	int count = 0;
	PTR_ChuyenBay p;
	if(status==CHUABAY){
		for(p=list;p!=NULL;p=p->next) if(p->data.trangthai!=HOANTAT&&p->data.trangthai!=HUYCHUYEN) count++;
	}else if(status==TATCA){
		for(p=list;p!=NULL;p=p->next) count++;
	}
	return count;
}

void show_List_CB(PTR_ChuyenBay l, int page_now, int count_CB, string status){
	int MAXLIST = 10;
	ChuyenBay *temp = new ChuyenBay[count_CB];
	int dem = 0;
	PTR_ChuyenBay p;
	int count_page = (count_CB%MAXLIST==0)? (count_CB/MAXLIST) : (count_CB/MAXLIST+1);
	if(status==CHUABAY){
		for(p=l;p!=NULL;p=p->next) if(p->data.trangthai!=HOANTAT&&p->data.trangthai!=HUYCHUYEN)
			temp[dem++] = p->data;
	}else if(status==TATCA){
		for(p=l;p!=NULL;p=p->next)
			temp[dem++] = p->data;
	}
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
			cout<<"|";
			printDay_time(temp[i].ngaykhoihanh);
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
			cout<<"|";
			printDay_time(temp[i].ngaykhoihanh);
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

PTR_ChuyenBay hanhkhach_chuahoanthanhchuyenbay(PTR_ChuyenBay list_CB, char* CMND){
	PTR_ChuyenBay p;
	for(p=list_CB;p!=NULL;p=p->next)
		if(p->data.trangthai!=HUYCHUYEN && p->data.trangthai!=HOANTAT)
			for(int i=1;i<=p->data.soVe;i++){
				if(p->data.danhsachVe[i]==CMND) return p;
			}
	return NULL;
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
    int count_CB = dem_CB(First_CB,CHUABAY);
    int count_page = (count_CB%10==0)? (count_CB/10) : (count_CB/10+1);
    show_List_CB(First_CB,page_now, count_CB,CHUABAY);
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
						show_List_CB(First_CB,--page_now, count_CB,CHUABAY);
						gotoxy(125+strlen(maCB),6);
						continue;
					}
					if(key==PAGEDOWN){
						key = 0;
						if(page_now==count_page) continue;
						show_List_CB(First_CB, ++page_now, count_CB,CHUABAY);
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
							if(hanhkhach_chuahoanthanhchuyenbay(First_CB, CMND)!=NULL){
   								Show_Message("ERROR","HANH KHACH DANG CO CHUYEN BAY");
   								gotoxy(125+strlen(CMND), 8);
    							key = 0;
    							continue;
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
						show_List_CB(First_CB,--page_now, count_CB,CHUABAY);
						gotoxy(125+strlen(CMND),8);
						continue;
					}
					if(key==PAGEDOWN){
						key = 0;
						if(page_now==count_page) continue;
						show_List_CB(First_CB, ++page_now, count_CB,CHUABAY);
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
						show_List_CB(First_CB,--page_now, count_CB,CHUABAY);
						gotoxy(125+strlen(ho),10);
						continue;
					}
					if(key==PAGEDOWN){
						key = 0;
						if(page_now==count_page) continue;
						show_List_CB(First_CB, ++page_now, count_CB,CHUABAY);
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
						show_List_CB(First_CB,--page_now, count_CB,CHUABAY);
						gotoxy(125+strlen(ten),12);
						continue;
					}
					if(key==PAGEDOWN){
						key = 0;
						if(page_now==count_page) continue;
						show_List_CB(First_CB, ++page_now, count_CB,CHUABAY);
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
						show_List_CB(First_CB,--page_now, count_CB, CHUABAY);
						gotoxy(125+strlen(phai),14);
						continue;
					}
					if(key==PAGEDOWN){
						key = 0;
						if(page_now==count_page) continue;
						show_List_CB(First_CB, ++page_now, count_CB,CHUABAY);
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
    				if(is_add_HK){
    					p->data.danhsachVe[maghe] = CMND;
    					HanhKhach newHK;
    					strcpy(newHK.CMND, CMND);
    					strcpy(newHK.ho, ho);
    					strcpy(newHK.ten, ten);
    					if(strcpy(phai, "NAM")==0) newHK.phai = 1;
    					else newHK.phai = 0;
    					Add_HK_to_List(root_HK, newHK);
					}else{
						p->data.danhsachVe[maghe] = CMND;
					}
					Show_Message("SUCCESS","MUA VE THANH CONG");
					show_List_CB(First_CB, page_now, count_CB,CHUABAY);
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
						show_List_CB(First_CB,--page_now, count_CB,CHUABAY);
						gotoxy(125+intToString(maghe).size(), 16);
						continue;
					}
					if(key==PAGEDOWN){
						key = 0;
						if(page_now==count_page) continue;
						show_List_CB(First_CB, ++page_now, count_CB,CHUABAY);
						gotoxy(125+intToString(maghe).size(), 16);
						continue;
					}
				}
				break;
			}
			default:{
				gotoxy(125+strlen(maCB), 6);
			}
		}
    	
	}
}

int HuyVe(PTR_ChuyenBay &First_CB, PTR_HK root_HK){
    Clear_Frame_Main();
    int page_now = 1;
    int count_CB = dem_CB(First_CB,CHUABAY);
    int count_page = (count_CB%10==0)? (count_CB/10) : (count_CB/10+1);
    show_List_CB(First_CB,page_now, count_CB,CHUABAY);
    gotoxy(115, 6);
    cout<<"CMND: ";
    gotoxy(115, 8);
    cout<<"Ho: ";
    gotoxy(115,10);
    cout<<"Ten: ";
    gotoxy(115, 12);
    cout<<"Phai: ";
    gotoxy(115,14);
    cout<<"Ma CB: ";
    gotoxy(115,16);
    cout<<"Ma Ghe: ";
    gotoxy(115,18);
    cout<<"SB Den: ";
    gotoxy(115, 20);
    cout<<"Time: ";
    char key = 0;
    char CMND[MAX_LENGTH_CMND+1] = "";
    gotoxy(125,6);
    PTR_ChuyenBay p;
    int run = 1;
    int soghe = 0;
    while(run){
    	int y = wherey();
    	ShowCur(true);
    	switch(y){
    		case 6: {
    			nhapChuoi(CMND, MAX_LENGTH_CMND, key, ONLY_NUMBER);
    			if(key==ESC){
    				run = 0;
    				key = 0;
    				break;
				}
				if(key==ENTER){
					if(strlen(CMND)!=9&&strlen(CMND)!=12){
    					Show_Message("ERROR","CMND KHONG HOP LE");
    					gotoxy(125+strlen(CMND), 6);
    					key = 0;
    					continue;
   					}
   					PTR_HK hk = timkiem_HK(root_HK, CMND);
   					if(hk!=NULL){
   						gotoxy(125,8);
   						cout<<"                              ";
   						gotoxy(125,8);
   						cout<<hk->info.ho;
   						gotoxy(125,10); cout<<"                    ";
						gotoxy(125,10); cout<<hk->info.ten;
						gotoxy(125,12); cout<<"   ";
						gotoxy(125,12);
						if(hk->info.phai==1) cout<<"NAM";
						else cout<<"NU";
						PTR_ChuyenBay p = hanhkhach_chuahoanthanhchuyenbay(First_CB, CMND);
						if(p!=NULL){
							gotoxy(125, 14); cout<<"               ";
							gotoxy(125, 14); cout<<p->data.ma_chuyenbay;
							gotoxy(125, 16); cout<<"     ";
							gotoxy(125, 16);
							for(int i=1;i<=p->data.soVe;i++)
								if(p->data.danhsachVe[i]==CMND){
									cout<<i; 
									soghe=i;
									break;
								}
							gotoxy(125, 18); cout<<"                              ";
							gotoxy(125, 18); cout<<p->data.sanbayden;
							gotoxy(125 ,20); cout<<"                              ";
							gotoxy(125, 20); printDay_time(p->data.ngaykhoihanh);
							int chon = form_confirm("BAN CO MUON HUY VE KHONG");
							if(chon==-1){
								run = 0;
    							key = 0;
    							break;
							}else if(chon ==1){
								p->data.danhsachVe[soghe]="0";
								Show_Message("SUCCESS","HUY VE THANH CONG");
								show_List_CB(First_CB,page_now, count_CB,CHUABAY);
								gotoxy(125, 14); cout<<"               ";
								gotoxy(125, 16); cout<<"     ";
								gotoxy(125, 18); cout<<"                              ";
								gotoxy(125, 20); cout<<"                              ";
							}else break;
							
						}else{
							gotoxy(125, 14); cout<<"               ";
							gotoxy(125, 16); cout<<"     ";
			
							gotoxy(125, 18); cout<<"                              ";
							gotoxy(125, 20); cout<<"                              ";
							Show_Message("ERROR","HANH KHACH CHUA DAT VE");
    						gotoxy(125+strlen(CMND), 6);
    						key = 0;
    						continue;
						}
				    }else {
				    	gotoxy(125,8);
   						cout<<"                              ";
   						gotoxy(125,10); cout<<"                    ";
						gotoxy(125,12); cout<<"   ";
						gotoxy(125, 14); cout<<"               ";
						gotoxy(125, 16); cout<<"     ";
						gotoxy(125, 18); cout<<"                              ";
						gotoxy(125, 20); cout<<"                              ";
				    	Show_Message("ERROR","HANH KHACH CHUA DAT VE");
    					gotoxy(125+strlen(CMND), 6);
    					key = 0;
    					continue;
					}
				}
				if(key==PAGEUP){
					key = 0;
					if(page_now==1) continue;
					show_List_CB(First_CB,--page_now, count_CB,CHUABAY);
					gotoxy(125+strlen(CMND),6);
					continue;
				}
				if(key==PAGEDOWN){
					key = 0;
					if(page_now==count_page) continue;
					show_List_CB(First_CB, ++page_now, count_CB,CHUABAY);
					gotoxy(125+strlen(CMND),6);
					continue;
				}
				break;
			}
			default:{
				gotoxy(125+strlen(CMND),6);
				continue;
				break;
			}
		}
    }
}

void show_dsVe(PTR_ChuyenBay &p,PTR_HK root, int page_now){
	int soluongvedaban = p->data.soVe - sovechuaban(p->data);
	int count_page;
	if(soluongvedaban%10==0) count_page = soluongvedaban/10;
	else count_page = soluongvedaban/10+1;
	int stt = 0;
	if(soluongvedaban==0){
		gotoxy(30,11);
		cout<<"KHONG CO HANH KHACH NAO";
		ShowCur(false);
		return;
	}
	Clear_Frame_Main();
	gotoxy(2,11);
	cout<<"+--------+-----------+-------------------+------------------------------+--------------+------+";
	gotoxy(2,12);
	cout<<"|  STT   |   SO VE   |      SO CMND      |            HO                |      TEN     | PHAI |";
	int y;
	for (int i = 1; i <= p->data.soVe; i++){
		if (p->data.danhsachVe[i] != "0"){
			++stt;
			if (stt <= page_now * 10){
				if (stt > (page_now - 1) * 10){
					if(stt<page_now*10) y = 11 + (stt % 10) * 2;
					else y = 11+10*2;
					gotoxy(2, y);
					cout << "+--------+-----------+-------------------+------------------------------+--------------+------+";
					gotoxy(2, y+1);
					cout << "|" << stt;
					gotoxy(11, y+1);
					cout << "|" << i;
					gotoxy(23, y+1);
					cout << "|" << p->data.danhsachVe[i];
					gotoxy(43, y+1);
					PTR_HK hk = timkiem_HK(root, p->data.danhsachVe[i].c_str());
					cout << "|" << hk->info.ho;
					gotoxy(74, y+1);
					cout << "|" << hk->info.ten;
					gotoxy(89, y+1);
					cout << "|";
					if (hk->info.phai == 1)
						cout << "NAM";
					else
						cout << "NU";
					gotoxy(96, y+1);
					cout << "|";
				}
			}
			else
				break;
		}
	}

	gotoxy(2,wherey()+1);
	cout<<"+--------+-----------+-------------------+------------------------------+--------------+------+";
}

void XuLyCB(PTR_ChuyenBay &p, PTR_HK root){
	int soluongvedaban = p->data.soVe - sovechuaban(p->data);
	int count_page;
	if(soluongvedaban%10==0) count_page = soluongvedaban/10;
	else count_page = soluongvedaban/10+1;
	int page_now = 1;
	show_dsVe(p, root, page_now);
	char input;
	int run = 1;
	while(run){
		input=getch();
		switch(input){
			case ENTER:{
				break;
			}
			case ESC:{
				run = 0;
				break;
			}
			case is_press_arrow_key:{
				input=getch();
				if(input==PAGEUP){
					if(page_now==1) continue;
					show_dsVe(p, root, --page_now);
				}else if(input==PAGEDOWN){
					if(page_now==count_page) continue;
					show_dsVe(p, root, ++page_now);
				}else if(input==BUTTON_DELETE){
					int chon = form_confirm("BAN CO MUON HUY CHUYEN BAY");
					if(chon==-1){
						run = 0;
						break;
					}else if(chon==1){
						if(p->data.trangthai==HOANTAT||p->data.trangthai==HUYCHUYEN){
							Show_Message("ERROR","KHONG THE HUY CHUYEN BAY NAY");
						}else{
							p->data.trangthai = HUYCHUYEN;
							
							gotoxy(125, 14);
							cout<<"                              ";
							gotoxy(125, 14);
							cout<<"HUY CHUYEN";
							Show_Message("SUCCESS","HUY CHUYEN BAY THANH CONG");
						}
					}else if(chon==0){
						break;
					}
				}
				break;
			}
			case is_press_f:{
				input=getch();
				if(input==F4){
					if(p->data.trangthai==HOANTAT||p->data.trangthai==HUYCHUYEN) Show_Message("ERROR","KHONG THE HIEU CHINH");
					else{
						Show_Message("SUCCESS","HIEU CHINH THANH CONG");
					}
				}
				break;
			}
		}
	}
}

void XuLyDSChuyenBay(PTR_ChuyenBay &First_CB, PTR_HK root){
	Clear_Frame_Main();
    int page_now = 1;
    int count_CB = dem_CB(First_CB,TATCA);
    int count_page = (count_CB%10==0)? (count_CB/10) : (count_CB/10+1);
    show_List_CB(First_CB,page_now, count_CB,TATCA);
    gotoxy(115, 6);
    cout<<"MA CB: ";
    gotoxy(115, 8);
    cout<<"SB DEN: ";
    gotoxy(115,10);
    cout<<"Time: ";
    gotoxy(115, 12);
    cout<<"SHMB: ";
    gotoxy(115,14);
    cout<<"Status: ";
    char key = 0;
    char MaCB[MAX_LENGTH_MACB+1] = "";
    gotoxy(125,6);
    int run = 1;
	PTR_ChuyenBay p;
	while(run){
		ShowCur(true);
		gotoxy(125+strlen(MaCB), 6);
		nhapChuoi(MaCB, MAX_LENGTH_MACB, key, NO_SPACE);
		switch(key){
			case ENTER:{
				p = timcb_MACB(First_CB, MaCB);
				if(p==NULL)
					Show_Message("ERROR","KHONG TIM THAY CHUYEN BAY");
				else{
					gotoxy(125,8);
					cout<<"                              ";
					gotoxy(125,8);
					cout<<p->data.sanbayden;
					gotoxy(125, 10);
					cout<<"                              ";
					gotoxy(125, 10);
					printDay_time(p->data.ngaykhoihanh);
					gotoxy(125, 12);
					cout<<"                              ";
					gotoxy(125, 12);
					cout<<p->data.sohieu_maybay;
					gotoxy(125, 14);
					cout<<"                              ";
					gotoxy(125, 14);
					if(p->data.trangthai==HUYCHUYEN) cout<<"HUY CHUYEN";
					else if(p->data.trangthai==HOANTAT) cout<<"HOAN TAT";
					else if(p->data.trangthai==CONVE) cout<<"CON VE";
					else if(p->data.trangthai==HETVE) cout<<"HET VE";
					XuLyCB(p, root);
					
					show_List_CB(First_CB,page_now, count_CB,TATCA);
				}
				break;
			}
			case ESC:{
				key = 0;
				run = 0;
				break;
			}
			case INSERT:{
				break;
			}
			case PAGEUP:{
				if(page_now==1) continue;
				show_List_CB(First_CB,--page_now, count_CB,TATCA);
				break;
			}
			case PAGEDOWN:{
				if(page_now==count_page) continue;
				show_List_CB(First_CB, ++page_now, count_CB, TATCA);
				break;
			}
		}
	}
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
    string listMenu_2[5] = {" DANH SACH CHUYEN BAY ",
                            "        DAT VE        ",
                            "        HUY VE        ",
							"  DANH SACH GHE TRONG ",
							"THONG KE SO CHUYEN BAY"};
    for (int i = 0; i < 5; i++)
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
            else if (input == DOWN && key != 4)
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

