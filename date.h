#pragma once
#include <ctime>
#include <math.h>
#include <string>
#include <stdlib.h>

int day[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

struct Day_time{
	int nam;
	int thang;
	int ngay;
	int gio;
	int phut;
};

bool LeapYear(int year)
{
    if (year % 400==0) return true;
    else if (year % 100!=0 && year % 4==0) return true;
    return false;
}
bool kt(Day_time a)
{
	if(a.thang<=0||a.thang>12) return false;
	if(a.thang == 2)
	{
		if(LeapYear(a.nam)) // kt nam nhuan
		{
			if(a.ngay > 29) 
			   return false;
		}
		else
		{
			if(a.ngay > 28) 
			   return false;
		}
	}
	else 
	{
		if(a.ngay > day[a.thang])
		  return false;
	}
	if(a.nam<=1900) return false;
	if(a.gio<0||a.gio>23) return false;
	if(a.phut<0||a.phut>59) return false;
	return true;
}

Day_time Time_now(){
	Day_time a_now;
	time_t now = time(0);
	tm *ltm = localtime(&now);
	
	a_now.ngay = ltm -> tm_mday;
	a_now.thang = 1+ltm -> tm_mon;
	a_now.nam = 1900 + ltm -> tm_year;
	a_now.gio = ltm -> tm_hour;
	a_now.phut = ltm -> tm_min;
	
	return a_now;  
}
	
bool TGQK( Day_time qk)
{
	if(kt(qk) == false)
	  return false;
	Day_time ht;
	ht=Time_now();
	if(ht.nam < qk.nam ) return false;
	else if(ht.nam > qk.nam) return true;
	else
	{
		if(ht.thang < qk.thang ) return false;
	    else if(ht.thang > qk.thang) return true;
	    else
	    {
		     if(ht.ngay < qk.ngay ) return false;
	         else if(ht.ngay > qk.ngay) return true;
	         else
	         {
		          if(ht.gio < qk.gio ) return false;
	              else if(ht.gio > qk.gio) return true;
	              else
	              {
		                if(ht.phut < qk.phut ) return false;
                     	else if(ht.phut > qk.phut) return true;
                     	else
                     	   return true;
	              }
	         }
	    }
	}
}

bool TGTL( Day_time tl)
{     
	if(kt(tl) == false)
	return false;
	Day_time ht;
	ht=Time_now();
	if(ht.nam > tl.nam ) return false;
	else if(ht.nam < tl.nam) return true;
	else
	{
		if(ht.thang > tl.thang ) return false;
	    else if(ht.thang < tl.thang) return true;
	    else
	    {
		     if(ht.ngay > tl.ngay ) return false;
	         else if(ht.ngay < tl.ngay) return true;
	         else
	         {
		          if(ht.gio > tl.gio ) return false;
	              else if(ht.gio < tl.gio) return true;
	              else
	              {
		                if(ht.phut > tl.phut ) return false;
                     	else if(ht.phut < tl.phut) return true;
                     	else
                     	return false;
	              }
	         }
	    }
	}
}

unsigned long int datetoday(Day_time Tg) {
        unsigned long int dayofyear =365*(Tg.nam-1) + (Tg.nam-1)/4 - (Tg.nam-1)/100 + (Tg.nam-1)/400; 
		unsigned long int dayofmonth=0;
        for(int i=0;i< Tg.thang;i++)
           {
		       dayofmonth += day[i];
		   }
		if(LeapYear(Tg.nam) && Tg.thang > 2){
			dayofmonth +=1;
		}
        return  dayofyear+ dayofmonth+ Tg.ngay-1;
}
