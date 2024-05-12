#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	unsigned char RGB[3];
	unsigned char mean;
} rgbpixel;

typedef struct{
	char mg1;
	int mg2;
	int width;
	int height;
	rgbpixel **pixels;
	int max;
}rgb_image;



int resize(rgb_image *src,rgb_image *dst,char *cmd);
void rotate(rgb_image *src,rgb_image *dst,char *cmd);
void flip(rgb_image *src,rgb_image *dst,char *cmd);
void grayscale(rgb_image *scr,rgb_image *dst);
void smooth(rgb_image *src,rgb_image *dst);
void same(rgb_image *src,rgb_image *dst);

int main(int argc,char **argv){
	FILE *fp,*np;
	int i,j,k,n,p=1;
	char work[20],perform[20];
	rgb_image image;
	rgb_image res;

	fp=fopen(argv[1],"r");
	np=fopen("res.ppm","w");
	
	/* 입력된 파일의 정보를 읽는다. */
	fscanf(fp,"%c%d",&image.mg1,&image.mg2);
	fscanf(fp,"%d%d",&image.width,&image.height);
	fscanf(fp,"%d%*c",&image.max);

	image.pixels=(rgbpixel**)malloc(sizeof(rgbpixel*)*image.height);
	for(i=0;i<image.height;i++) image.pixels[i]=(rgbpixel*)malloc(sizeof(rgbpixel)*image.width);

	for(i=0;i<image.height;i++){
		for(j=0;j<image.width;j++){
				for(k=0;k<3;k++){
				fread(&image.pixels[i][j].RGB[k],sizeof(unsigned char),1,fp);
			}
		}
	}

	/* 수행할 작업을 입력받는다. */
	printf("몇개의 작업을 원하십니까?(resize,rotate,flip,grayscale,smooth) : ");
	scanf("%d",&n);
	for(i=0;i<n;i++){
		printf("원하시는 작업을 입력해 주세요(resize,rotate,flip,grayscale,smooth) : ");
		scanf("%s",work);
		if(!strcmp(work,"resize")){
			while(1){
				printf("scaleup 과 scaledown 중 어느 작업을 하실건가요? : ");
				scanf("%s",perform);
				if(!strcmp(perform,"scaleup")){
					p=resize(&image,&res,"scaleup");
					perform[0]='\0';
					break;
				} else if(!strcmp(perform,"scaledown")){
					p=resize(&image,&res,"scaledown");
					perform[0]='\0';
					break;
				} else{
					printf("잘못 입력하였습니다. 다시 입력해주세요.\n");
					perform[0]='\0';
				}
			}
			work[0]='\0';
		} else if(!strcmp(work,"rotate")){
			while(1){
				printf("left 와 right 중 어느 작업을 하실건가요? : ");
				scanf("%s",perform);
				if(!strcmp(perform,"left")){
					rotate(&image,&res,"left");
					perform[0]='\0';
					break;
				} else if(!strcmp(perform,"right")){
					rotate(&image,&res,"right");
					perform[0]='\0';
					break;
				} else{
					printf("잘못 입력하였습니다. 다시 입력해주세요.\n");
					perform[0]='\0';
				}
			}
			work[0]='\0';
		} else if(!strcmp(work,"flip")){
				while(1){
				printf("horizon 과 vertical 중 어느 작업을 하실건가요? : ");
				scanf("%s",perform);
				if(!strcmp(perform,"horizon")){
					flip(&image,&res,"horizon");
					perform[0]='\0';
					break;
				} else if(!strcmp(perform,"vertical")){
					flip(&image,&res,"vertical");
					perform[0]='\0';
					break;
				} else{
					printf("잘못 입력하였습니다. 다시 입력해주세요.\n");
					perform[0]='\0';
				}
			}
			work[0]='\0';
		} else if(!strcmp(work,"grayscale")){
			grayscale(&image,&res);
			work[0]='\0';
		} else if(!strcmp(work,"smooth")){
			smooth(&image,&res);
			work[0]='\0';
		} else{
			printf("잘못 입력하였습니다. 다시 입력해주세요.\n");
			work[0]='\0';
			i--;
		}

	}

	/* 위의 작업을 좀더 간편화 시킨 것이다.(위의 입력을 주석처리하고 밑의 주석을 풀면 바로 실행된다.) */
	//p=resize(&image,&res,"scaleup");
	//p=resize(&image,&res,"scaledown");
	//rotate(&image,&res,"left");
	//rotate(&image,&res,"right");
	//flip(&image,&res,"horizon");
	//flip(&image,&res,"vertical");
	//grayscale(&image,&res);
	//smooth(&image,&res);


	/* 수행 과정 중 이미지의 크기가 1보다 작아지면 error를 출력하고 종료한.다 */
	if(p==0){
		printf("error : 사이즈 축소 과정에서 가로 혹은 세로의 길이가 1보다 작아졌습니다.\n");
		for(i=0;i<image.height;i++) free(image.pixels[i]);
		free(image.pixels);
		fclose(fp);
		fclose(np);
		return 0;
	}

	/* 수행된 작업 결과를 res.ppm파일에 입력하고 저장한다. */
	fprintf(np,"%c%d\n",image.mg1,image.mg2-3);
	fprintf(np,"%d %d\n",image.width,image.height);
	fprintf(np,"%d\n",image.max);
	for(i=0;i<image.height;i++){
		for(j=0;j<image.width;j++){
				fprintf(np,"%u ",(unsigned char)image.pixels[i][j].RGB[0]);
				fprintf(np,"%u ",(unsigned char)image.pixels[i][j].RGB[1]);
				fprintf(np,"%u ",(unsigned char)image.pixels[i][j].RGB[2]);
		}
		fprintf(np,"\n");
	
	}
	

	/* image를 받을 때 동적할당한 부분을 초기화 시키고 파일을 닫느다. */
	for(i=0;i<image.height;i++) free(image.pixels[i]);
	free(image.pixels);

	fclose(fp);
	fclose(np);

	
	
}

/* 이미지의 크기 변경 */
int resize(rgb_image *src,rgb_image *dst,char *cmd){
	int i,j,k;
	if(!strcmp(cmd,"scaleup")){
		(*dst).height=(*src).height*2;
		(*dst).width=(*src).width*2;
		(*dst).pixels=(rgbpixel**)malloc(sizeof(rgbpixel*)*(*dst).height);
		for(i=0;i<(*dst).height;i++) (*dst).pixels[i]=(rgbpixel*)malloc(sizeof(rgbpixel)*(*dst).width);
		for(i=0;i<(*dst).height;i++){
			for(j=0;j<(*dst).width;j++){
				for(k=0;k<3;k++){
					(*dst).pixels[i][j].RGB[k]=(*src).pixels[i/2][j/2].RGB[k];
				}
			}
		}
	}
	if(!strcmp(cmd,"scaledown")){
		(*dst).height=(*src).height/2;
		(*dst).width=(*src).width/2;
		if((*dst).height<1||(*dst).width<1) return 0;
		(*dst).pixels=(rgbpixel**)malloc(sizeof(rgbpixel*)*(*dst).height);
		for(i=0;i<(*dst).height;i++) (*dst).pixels[i]=(rgbpixel*)malloc(sizeof(rgbpixel)*(*dst).width);
		for(i=0;i<(*dst).height;i++){
			for(j=0;j<(*dst).width;j++){
				for(k=0;k<3;k++){
					(*dst).pixels[i][j].RGB[k]=((*src).pixels[i*2][j*2].RGB[k]+(*src).pixels[i*2+1][j*2].RGB[k]+(*src).pixels[i*2][j*2+1].RGB[k]+(*src).pixels[i*2+1][j*2+1].RGB[k])/4;
				}
			}
		}
	}
	same(src,dst);
	return 1;
}

/* 이미지의 회전 */
void rotate(rgb_image *src,rgb_image *dst,char *cmd){
	int i,j,k;
	(*dst).height=(*src).width;
	(*dst).width=(*src).height;
	(*dst).pixels=(rgbpixel**)malloc(sizeof(rgbpixel*)*(*dst).height);
	for(i=0;i<(*dst).height;i++) (*dst).pixels[i]=(rgbpixel*)malloc(sizeof(rgbpixel)*(*dst).width);
	if(!strcmp(cmd,"left")){
		for(i=0;i<(*dst).height;i++){
			for(j=0;j<(*dst).width;j++){
				for(k=0;k<3;k++){
					(*dst).pixels[i][j].RGB[k]=(*src).pixels[j][(*src).width-1-i].RGB[k];
				}
			}
		}
	}

	if(!strcmp(cmd,"right")){
		for(i=0;i<(*dst).height;i++){
			for(j=0;j<(*dst).width;j++){
				for(k=0;k<3;k++){
					(*dst).pixels[i][j].RGB[k]=(*src).pixels[(*src).height-1-j][i].RGB[k];
				}
			}
		}
	}
	same(src,dst);
	
}

/* 이미지의 반전 */
void flip(rgb_image *src,rgb_image *dst,char *cmd){
	int i,j,k;
	(*dst).height=(*src).height;
	(*dst).width=(*src).width;
	(*dst).pixels=(rgbpixel**)malloc(sizeof(rgbpixel*)*(*dst).height);
	for(i=0;i<(*dst).height;i++) (*dst).pixels[i]=(rgbpixel*)malloc(sizeof(rgbpixel)*(*dst).width);
	if(!strcmp(cmd,"horizon")){
		for(i=0;i<(*dst).height;i++){
			for(j=0;j<(*dst).width;j++){
				for(k=0;k<3;k++){
					(*dst).pixels[i][j].RGB[k]=(*src).pixels[(*dst).height-1-i][j].RGB[k];
				}
			}
		}
	}
	if(!strcmp(cmd,"vertical")){
		for(i=0;i<(*dst).height;i++){
			for(j=0;j<(*dst).width;j++){
				for(k=0;k<3;k++){
					(*dst).pixels[i][j].RGB[k]=(*src).pixels[i][(*dst).width-1-j].RGB[k];
				}
			}
		}
	}
	same(src,dst);
}

/* 이미지의 흑백 전환 */
void grayscale(rgb_image *src,rgb_image *dst){
	int i,j,k;
	(*dst).height=(*src).height;
	(*dst).width=(*src).width;
	(*dst).pixels=(rgbpixel**)malloc(sizeof(rgbpixel*)*(*dst).height);
	for(i=0;i<(*dst).height;i++) (*dst).pixels[i]=(rgbpixel*)malloc(sizeof(rgbpixel)*(*dst).width);
	for(i=0;i<(*dst).height;i++){
		for(j=0;j<(*dst).width;j++){
			(*dst).pixels[i][j].mean=(((*src).pixels[i][j].RGB[0]+(*src).pixels[i][j].RGB[1]+(*src).pixels[i][j].RGB[2])/3);
			for(k=0;k<3;k++) (*dst).pixels[i][j].RGB[k]=(*dst).pixels[i][j].mean;
		}
	}
	same(src,dst);
}

/* 이미지 스무딩 */
void smooth(rgb_image *src,rgb_image *dst){
	int mask[3][3]={{1,2,1},
					{2,4,2},
					{1,2,1}};
	int i,j,k,x,y,sum,cnt;
	(*dst).height=(*src).height;
	(*dst).width=(*src).width;
	(*dst).pixels=(rgbpixel**)malloc(sizeof(rgbpixel*)*(*dst).height);
	for(i=0;i<(*dst).height;i++) (*dst).pixels[i]=(rgbpixel*)malloc(sizeof(rgbpixel)*(*dst).width);

	for(i=0;i<(*dst).height;i++){
		for(j=0;j<(*dst).width;j++){
			for(k=0;k<3;k++){
				sum=0;
				cnt=0;
				for(y=0;y<3;y++){
					for(x=0;x<3;x++){
						if((i-1+y)>=0&&(j-1+x)>=0&&(i-1+y)<(*src).height&&(j-1+x)<(*src).width){
							sum+=(*src).pixels[i-1+y][j-1+x].RGB[k]*mask[y][x];
							cnt=cnt+mask[y][x];
						}
					}
				}
				sum=sum/cnt;
				(*dst).pixels[i][j].RGB[k]=sum;
			}
		}
	}
	same(src,dst);
}

/* dst이미지 초기화(여러 작업을 수행할 때 필요, 함수 내 dst 동적할당 초기화) */
void same(rgb_image *src,rgb_image *dst){
	int i,j,k;
	for(i=0;i<(*src).height;i++) free((*src).pixels[i]);
	free((*src).pixels);
	(*src).height=(*dst).height;
	(*src).width=(*dst).width;
	(*src).pixels=(rgbpixel**)malloc(sizeof(rgbpixel*)*(*src).height);
	for(i=0;i<(*src).height;i++) (*src).pixels[i]=(rgbpixel*)malloc(sizeof(rgbpixel)*(*src).width);
	for(i=0;i<(*src).height;i++){
		for(j=0;j<(*src).width;j++){
			for(k=0;k<3;k++){
				(*src).pixels[i][j].RGB[k]=(*dst).pixels[i][j].RGB[k];
			}
		}
	}
	for(i=0;i<(*dst).height;i++) free((*dst).pixels[i]);
	free((*dst).pixels);
	
}
