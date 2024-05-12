#include<stdio.h>

char* Encryption(char* plaintext,int key);

int main()
{
	char *plaintext;
	int key,i=0;
	printf("Input the Plaintext : ");
	while(1){
		scanf("%c",&plaintext[i]);
		if(plaintext[i]=='\n') break;
		i++;
	}
	
	plaintext[i]='\0';
	printf("Input key : ");
	scanf("%d",&key);
	
	printf("Encrypt(%s) = ",plaintext);
	printf("%s\n",Encryption(plaintext,key));
	printf("Decrypt(%s) = ",plaintext);
	printf("%s\n",Encryption(plaintext,-key));
	

}

char* Encryption(char* plaintext,int key){
	int i=0;
	while(plaintext[i]!='\0'){
		if(plaintext[i]>='A'&&plaintext[i]<='Z'){
			plaintext[i]=plaintext[i]-'A'+key;
			if(plaintext[i]/26==1){
				plaintext[i]=plaintext[i]-26;
			} else if(plaintext[i]<0){
				plaintext[i]=plaintext[i]+26;
			}
			plaintext[i]=plaintext[i]+'A';
		}
		if(plaintext[i]>='a'&&plaintext[i]<='z'){
			plaintext[i]=plaintext[i]-'a'+key;
			if(plaintext[i]/26==1){
				plaintext[i]=plaintext[i]-26;
			} else if(plaintext[i]<0){
				plaintext[i]=plaintext[i]+26;
			}
			plaintext[i]=plaintext[i]+'a';
		}
		i++;
	}
	return plaintext;
}
