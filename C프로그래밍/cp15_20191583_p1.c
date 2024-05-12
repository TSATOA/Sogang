#include<stdio.h>
#include<string.h>

enum Date{mon,tue,wed,thu,fri,sat,sun};
struct Calendar{
	int year,month,day;
	enum Date date;
	char* dateString;
};

enum Date getDate(int y,int m, int d);
char* getDay(enum Date currDate);

int main()
{
	
	struct Calendar x;
	scanf("%d%d%d",&x.year,&x.month,&x.day);
	x.date=getDate(x.year,x.month,x.day);
	x.dateString=getDay(x.date);
	printf("%s\n",x.dateString);
	return 0;

}

enum Date getDate(int y,int m, int d){
	return ((y+y/4-y/100+y/400+(13*m+8)/5+d)-1)%7;
}

char* getDay(enum Date currDate){

	switch(currDate){
		case mon:
			return "Monday";
		case tue:
			return "Tuseday";
		case wed:
			return "Wednesday";
		case thu:
			return "Thursday";
		case fri:
			return "Friday";
			break;
		case sat:
			return "Saterday";
		case sun:
			return "Sunday";
	}
	
}
