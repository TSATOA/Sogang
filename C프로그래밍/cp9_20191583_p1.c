#include<stdio.h>
#include<stdlib.h>

int main()
{
	int i=0,j=1;
	int cnt=0;
	char* charr=(char*)calloc(1,sizeof(char));
	printf("Input string :");
	while(1){
		scanf("%c",&charr[i]);
		cnt++;
		if(charr[i]!='\n'){
			i++;
			if(i==j){
				j=j*2;
				charr=(char*)realloc(charr,sizeof(char)*j);
			}
		} else{
			break;
		}
	}
	printf("Output string :");
	for(i=cnt-2;i>=0;i--){

		printf("%c",charr[i]);
	}
	free(charr);
	printf("\n");
	return 0;
}
