#pragma once
#include "entity.h"
#include "mylib.h"
#include "function.h"
#include "entity.h"
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;

Day_time string_to_dayTime(char *str)
{
	Day_time day;
	day.gio = toInt(strtok(str, "`"));
	day.phut = toInt(strtok(NULL, "`"));
	day.ngay = toInt(strtok(NULL, "`"));
	day.thang = toInt(strtok(NULL, "`"));
	day.nam = toInt(strtok(NULL, "`"));
	return day;
}

string *string_to_ListVe(char *str, int sove)
{
	string *listVe = new string[sove + 1];
	listVe[1] = strtok(str, "~");
	for (int i = 2; i <= sove; i++)
	{
		listVe[i] = strtok(NULL, "~");
	}
	return listVe;
}

void Read_File(List_MayBay &list_MB, PTR_ChuyenBay &First_CB, PTR_HK &root_HK)
{

	ifstream infile_MB, infile_CB, infile_HK;
	char input[1000] = "";
	infile_MB.open("file/maybay.txt");
	while (1)
	{
		infile_MB.getline(input, 1000);
		if (strcmp(input, "") == 0)
			break;
		else
		{
			MayBay a;
			strcpy(a.sohieu_maybay, strtok(input, "|"));
			strcpy(a.loai_maybay, strtok(NULL, "|"));
			a.socho = toInt(strtok(NULL, "|"));
			a.sochuyendabay = toInt(strtok(NULL, "|"));
			Add_MB_to_List(list_MB, a);
		}
	}
	infile_MB.close();

	infile_CB.open("file/chuyenbay.txt");
	while (1)
	{
		infile_CB.getline(input, 1000);
		if (strcmp(input, "") == 0)
			break;
		else
		{
			ChuyenBay cb;
			strcpy(cb.ma_chuyenbay, strtok(input, "|"));
			char *date = strtok(NULL, "|");
			strcpy(cb.sanbayden, strtok(NULL, "|"));
			strcpy(cb.sohieu_maybay, strtok(NULL, "|"));
			cb.soVe = toInt(strtok(NULL, "|"));
			cb.trangthai = toInt(strtok(NULL, "|"));
			char *dsve = strtok(NULL, "|");
			cb.ngaykhoihanh = string_to_dayTime(date);
			cb.danhsachVe = string_to_ListVe(dsve, cb.soVe);
			Add_CB_to_List(First_CB, cb);
		}
	}
	infile_CB.close();
	infile_HK.open("file/hanhkhach.txt");
	while (1)
	{
		infile_HK.getline(input, 1000);
		if (strcmp(input, "") == 0)
			break;
		else
		{
			HanhKhach hk;
			strcpy(hk.CMND, strtok(input, "|"));
			strcpy(hk.ho, strtok(NULL, "|"));
			strcpy(hk.ten, strtok(NULL, "|"));
			hk.phai = toInt(strtok(NULL, "|"));
			Add_HK_to_List(root_HK, hk);
		}
	}
	infile_HK.close();
}

string DatetoString(Day_time a)
{
	return (intToString(a.gio) + "`" + intToString(a.phut) + "`" + intToString(a.ngay) + "`" + intToString(a.thang) + "`" + intToString(a.nam));
}

string ListVetoString(string *a, int n)
{
	string temp;
	for (int i = 1; i <= n - 1; i++)
	{
		temp += *(a + i) + "~";
	}
	temp += *(a + n);
	return temp;
}

void Write_HK(PTR_HK &p, ofstream &file)
{
	string output;
	if (p != NULL)
	{
		output = p->info.CMND;
		output += "|";
		output += p->info.ho;
		output += "|";
		output += p->info.ten;
		output += "|";
		output += intToString(p->info.phai);
		file << output << endl;
		Write_HK(p->left, file);
		Write_HK(p->right, file);
	}
}

void Write_File(List_MayBay &list_MB, PTR_ChuyenBay &First_CB, PTR_HK &root_HK)
{
	ofstream outfile_MB, outfile_CB, outfile_HK;
	outfile_MB.open("file/maybay.txt");
	string output;
	for (int i = 0; i < list_MB.soluong; i++)
	{
		output = list_MB.nodes[i]->sohieu_maybay;
		output += "|";
		output += list_MB.nodes[i]->loai_maybay;
		output += "|";
		output += intToString(list_MB.nodes[i]->socho);
		output += "|";
		output += intToString(list_MB.nodes[i]->sochuyendabay);
		outfile_MB << output << endl;
	}
	outfile_MB.close();

	outfile_CB.open("file/chuyenbay.txt");
	for (PTR_ChuyenBay p = First_CB; p != NULL; p = p->next)
	{
		output = p->data.ma_chuyenbay;
		output += "|";
		output += DatetoString(p->data.ngaykhoihanh);
		output += "|";
		output += p->data.sanbayden;
		output += "|";
		output += p->data.sohieu_maybay;
		output += "|";
		output += intToString(p->data.soVe);
		output += "|";
		output += intToString(p->data.trangthai);
		output += "|";
		output += ListVetoString(p->data.danhsachVe, p->data.soVe);
		outfile_CB << output << endl;
	}
	outfile_CB.close();

	outfile_HK.open("file/hanhkhach.txt");
	Write_HK(root_HK, outfile_HK);
	outfile_HK.close();
}
