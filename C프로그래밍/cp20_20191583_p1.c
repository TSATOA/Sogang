/* 공용체와 같은 경우 가장 큰 한 멤버에게 메모리 공간만을 할당한다.
이때 한 멤버를 사용하고 다른 멤버를 사용하면 이전에 사용했던 멤버의 저장값은 사라지고 새로운 멤버의 저장값을 받게 된다. 따라서 한번에 받아 저장할 경우 가장 마지막에 저장된 결과값만 잘 나오게 되는 것이다.*/ 
#include<stdio.h>
#include<string.h>

typedef union{
	char name[20];
	char subject[20];
	int score;
}student;

int main()
{
	student st;
	int sc;
	char na[20];
	char su[20];
	scanf("%s",na);
	scanf("%s",su);
	scanf("%d",&sc);
	strcpy(st.name,na);
	strcpy(st.subject,su);
	st.score=sc;
	printf("Name	: %s\n",st.name);
	printf("Subject	: %s\n",st.subject);
	printf("Score	: %d\n",st.score);
	strcpy(st.name,na);
	printf("Name	: %s\n",st.name);
	strcpy(st.subject,su);
	printf("Subject	: %s\n",st.subject);
	st.score=sc;
	printf("Score	: %d\n",st.score);
	return 0;

}
