#include<string.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
class SDate
{
private:
int dayOfMonth;
int month;
int year;
int dayNumber;
void toDayNumber();
int isLeapYear(int);
void fromDayNumber();
void isValidDate(const char *dateString,int *isValid,int *d,int *m,int *y);
public:
SDate();
SDate(const char *dateString);
SDate(const SDate &other);
virtual ~SDate();
int getDayOfMonth();
int getMonth();
int getYear();
int isLeapYear();
void getDayOfWeekString(char *dayOfWeekString);
void getDayOfWeekShortString(char *dayOfWeekShortString);
void getMonthString(char *monthString);
void getShortMonthString(char *shortMonthString);
int getDayOfWeek();
SDate & operator=(const SDate &other);
SDate & operator=(const char *dateString);
void operator+=(int);
void operator-=(int);
int operator<(const SDate &other);
int operator>(const SDate &other);
int operator<=(const SDate &other);
int operator>=(const SDate &other);
int operator==(const SDate &other);
int operator!=(const SDate &other);
SDate operator+(int days);
SDate operator-(int days);
};
void SDate::fromDayNumber()
{
if(this->dayNumber<=0)
{
this->dayOfMonth=0;
this->month=0;
this->year=0;
return;
}
int x=dayNumber;
int d,m,y;
int daysInYear;
int daysInMonth;
y=1901;
while(1)
{
if(isLeapYear(y)) daysInYear=366;
else daysInYear=365;
if(x<=daysInYear) break;
x=x-daysInYear;
y=y+1;
}
int mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(isLeapYear(this->year)) mth[1]=29;
m=0;
while(1)
{
daysInMonth=mth[m];
if(x<=daysInMonth) break;
x=x-daysInMonth;
m++;
}
m++;
d=x;
this->dayOfMonth=d;
this->month=m;
this->year=y;
}
SDate::SDate()
{
time_t x;
time(&x);
struct tm *now;
now=localtime(&x);
dayOfMonth=now->tm_mday;
month=now->tm_mon+1;
year=now->tm_year+1900;
this->toDayNumber();
}
SDate::SDate(const char *dateString)
{
int d,m,y,isValid;
isValidDate(dateString,&isValid,&d,&m,&y);
if(isValid)
{
this->dayOfMonth=d;
this->month=m;
this->year=y;
this->toDayNumber();
}
else
{
this->dayNumber=0;
this->dayOfMonth=0;
this->month=0;
this->year=0;
}
}
SDate::~SDate()
{
cout<<"destructor"<<endl;
}
void SDate::isValidDate(const char *dateString,int *isValid,int *d,int *m,int *y)
{
int dd,mm,yy;
int sepIndex1,sepIndex2,i,r;
char mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
char sep;
*isValid=0;
if(dateString==NULL) return;
int x=strlen(dateString);
if(x<8 || x>10) return;
if(!(dateString[1]=='/' || dateString[1]=='-' || dateString[2]=='/' || dateString[2]=='-')) return;
if(dateString[1]=='/' || dateString[1]=='-') sepIndex1=1;
else sepIndex1=2;
sep=dateString[sepIndex1];
if(dateString[0]<48 || dateString[0]>57) return;
if(sepIndex1==2 && (dateString[1]<48 || dateString[2]>57)) return;
if(sepIndex1==1)
{
dd=dateString[0]-48;
if(dd==0) return;
}
else
{
dd=((dateString[0]-48)*10)+(dateString[1]-48);
if(dd==0) return;
}
i=sepIndex1+1;
if(!(dateString[i+1]==sep || dateString[i+2]==sep)) return;
if(dateString[i+1]==sep) sepIndex2=i+1;
else sepIndex2=i+2;
if(dateString[i]<48 || dateString[i]>57) return;
if(sepIndex2==i+2 && (dateString[i+1]<48 || dateString[i+1]>57)) return;
if(sepIndex2==i+1)
{
mm=dateString[i]-48;
}
else
{
mm=((dateString[i]-48)*10)+(dateString[i+1]-48);
}
if(mm<1 || mm>12) return;
i=sepIndex2+1;
yy=0;
r=0;
while(r<=3)
{
if(dateString[i+r]<48 || dateString[i+r]>57) return;
yy=(yy*10)+(dateString[i+r]-48);
r++;
}
if(yy<1901) return;
if(yy%400==0) mth[1]=29;
if(yy%100==0) mth[1]=28;
if(yy%4==0) mth[1]=29;
else mth[1]=28;
if(dd<1 || dd>mth[mm-1]) return;
*d=dd;
*m=mm;
*y=yy;
*isValid=1;
}
int SDate::isLeapYear(int y)
{
if(y%400==0) return 1;
else if(y%100==0) return 0;
else if(y%4==0) return 1;
else return 0;
}
void SDate::toDayNumber()
{
int x=0;
int y=1901;
while(y<this->year)
{
if(isLeapYear(y)) x=x+366;
else x=x+365;
y++;
}
int mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(isLeapYear(this->year)) mth[1]=29;
int ep=this->month-2;
int m=0;
while(m<=ep)
{
x=x+mth[m];
m++;
}
x=x+this->dayOfMonth;
this->dayNumber=x;
}
int SDate::getDayOfMonth()
{
return this->dayOfMonth;
}
int SDate::getMonth()
{
return this->month;
}
int SDate::getYear()
{
return this->year;
}
SDate & SDate::operator=(const SDate &other)
{
this->dayNumber=other.dayNumber;
this->dayOfMonth=other.dayOfMonth;
this->year=other.year;
this->month=other.month;
return *this;
}
SDate::SDate(const SDate &other)
{
this->dayNumber=other.dayNumber;
this->dayOfMonth=other.dayOfMonth;
this->year=other.year;
this->month=other.month;
}
ostream & operator<<(ostream &oo,SDate &sDate)
{
//cout<<date.getDayOfMonth()<<"/"<<date.getMonth()<<"/"<<date.getYear();
oo<<sDate.getDayOfMonth()<<"/"<<sDate.getMonth()<<"/"<<sDate.getYear();
return oo;
}
void SDate::operator+=(int days)
{
if(this->dayNumber==0) return;
this->dayNumber+=days;
this->fromDayNumber();
}
void SDate::operator-=(int days)
{
if(this->dayNumber==0) return;
this->dayNumber-=days;
this->fromDayNumber();
}
int SDate::operator<(const SDate &other)
{
return this->dayNumber<other.dayNumber;
}
int SDate::operator>(const SDate &other)
{
return this->dayNumber>other.dayNumber;
}
int SDate::operator<=(const SDate &other)
{
return this->dayNumber<=other.dayNumber;
}
int SDate::operator>=(const SDate &other)
{
return this->dayNumber>=other.dayNumber;
}
int SDate::operator==(const SDate &other)
{
return this->dayNumber==other.dayNumber;
}
int SDate::operator!=(const SDate &other)
{
return this->dayNumber!=other.dayNumber;
}
int SDate::isLeapYear()
{
if(this->dayNumber==0) return 0;
if(this->year%400==0) return 1;
else if(this->year%100==0) return 0;
else if(this->year%4==0) return 1;
else return 0;
}
void SDate::getDayOfWeekString(char *dayOfWeekString)
{
if(this->dayNumber==0)
{
*dayOfWeekString='\0';
return;
}
int dow=getDayOfWeek();
if(dow==1) strcpy(dayOfWeekString,"Sunday");
if(dow==2) strcpy(dayOfWeekString,"Monday");
if(dow==3) strcpy(dayOfWeekString,"Tuesday");
if(dow==4) strcpy(dayOfWeekString,"Wednesday");
if(dow==5) strcpy(dayOfWeekString,"Thurday");
if(dow==6) strcpy(dayOfWeekString,"Friday");
if(dow==7) strcpy(dayOfWeekString,"saturday");
}
void SDate::getDayOfWeekShortString(char *dayOfWeekShortString)
{
if(this->dayNumber==0)
{
*dayOfWeekShortString='\0';
return;
}
int dow=getDayOfWeek();
if(dow==1) strcpy(dayOfWeekShortString,"Sun");
if(dow==2) strcpy(dayOfWeekShortString,"Mon");
if(dow==3) strcpy(dayOfWeekShortString,"Tue");
if(dow==4) strcpy(dayOfWeekShortString,"Wed");
if(dow==5) strcpy(dayOfWeekShortString,"Thu");
if(dow==6) strcpy(dayOfWeekShortString,"Fri");
if(dow==7) strcpy(dayOfWeekShortString,"sat");
}
void SDate::getMonthString(char *monthString)
{
if(this->dayNumber==0)
{
*monthString='\0';
return;
}
if(month==1) strcpy(monthString,"January");
if(month==2) strcpy(monthString,"February");
if(month==3) strcpy(monthString,"March");
if(month==4) strcpy(monthString,"April");
if(month==5) strcpy(monthString,"May");
if(month==6) strcpy(monthString,"June");
if(month==7) strcpy(monthString,"July");
if(month==8) strcpy(monthString,"August");
if(month==9) strcpy(monthString,"September");
if(month==10) strcpy(monthString,"October");
if(month==11) strcpy(monthString,"November");
if(month==12) strcpy(monthString,"December");
}
void SDate::getShortMonthString(char *shortMonthString)
{
if(this->dayNumber==0)
{
*shortMonthString='\0';
return;
}
if(month==1) strcpy(shortMonthString,"Jan");
if(month==2) strcpy(shortMonthString,"Feb");
if(month==3) strcpy(shortMonthString,"Mar");
if(month==4) strcpy(shortMonthString,"Apr");
if(month==5) strcpy(shortMonthString,"May");
if(month==6) strcpy(shortMonthString,"Jun");
if(month==7) strcpy(shortMonthString,"Jul");
if(month==8) strcpy(shortMonthString,"Aug");
if(month==9) strcpy(shortMonthString,"Sep");
if(month==10) strcpy(shortMonthString,"Oct");
if(month==11) strcpy(shortMonthString,"Nov");
if(month==12) strcpy(shortMonthString,"Dec");
}
int SDate::getDayOfWeek()
{
if(this->dayNumber==0) return 0;
int leftDays=this->dayNumber%7;
int dow=2+leftDays;
if(dow>7) dow=dow%7;
return dow;
}
SDate & SDate::operator=(const char *dateString)
{
int d,m,y,isValid;
isValidDate(dateString,&isValid,&d,&m,&y);
if(isValid)
{
this->dayOfMonth=d;
this->month=m;
this->year=y;
this->toDayNumber();
}
else
{
this->dayNumber=0;
this->dayOfMonth=0;
this->month=0;
this->year=0;
}
return *this;
}
SDate SDate::operator+(int days)
{
if(this->dayNumber==0) return SDate("00/00/0000");
SDate date;
date.dayNumber=this->dayNumber+days;
date.fromDayNumber();
return date;
}
SDate SDate::operator-(int days)
{
if(this->dayNumber==0) return SDate("00/00/0000");
SDate date;
date.dayNumber=this->dayNumber-days;
date.fromDayNumber();
return date;
}
int main()
{
char a[20];
SDate date1="15/05/2005";
date1.getDayOfWeekShortString(a);
cout<<a<<endl;
date1="30/05/2020";
cout<<date1<<endl;
SDate date2;
date2=date1+10;
cout<<date2<<endl;
date2=date1-10;
cout<<date2<<endl;
return 0;
}
