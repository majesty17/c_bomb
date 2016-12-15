#include "common.h"
void initBombs(short **bombs,int weight,int height,int count){


	srand(time(0));
	int n=count,i,j;
	while(n){
		j=rand()%weight+1;
		i=rand()%height+1;
		if(bombs[i][j]!=BO_HAVE_BOMB){
			bombs[i][j]=BO_HAVE_BOMB;
			n--;
		}
	}
	for(int i=1;i<=height;i++){
		for(int j=1;j<=weight;j++){
			if(bombs[i][j]==BO_HAVE_BOMB){
				continue;
			}
			else{
				n=0;
				if(bombs[i][j-1]==BO_HAVE_BOMB) n++;
				if(bombs[i-1][j]==BO_HAVE_BOMB) n++;
				if(bombs[i+1][j]==BO_HAVE_BOMB) n++;
				if(bombs[i][j+1]==BO_HAVE_BOMB) n++;
				bombs[i][j]=1<<(n-1);

			}
		}
	}
}


void showBombs(short **bombs,int weight,int height){
	for(int i=1;i<=height;i++){
		for(int j=1;j<=weight;j++){
			if(bombs[i][j]==BO_HAVE_BOMB)
				printf("¡ñ");
//			else if(bombs[i][i]==BO_NOHAVE_BOMB)
//				printf("¡ð");
			else{
				printf("%2d",bombs[i][j]);
			}
		}
		printf("\n");
	}
}
void killBombs(short **bombs,int weight,int height){

}
int clickToOpen(short **bombs,int x,int y){
	printf("%d,%d\n",x,y);
	if(bombs[x][y]==BO_HAVE_BOMB){
		return -1;
	}
	else if(bombs[x][y]==BO_NOHAVE_BOMB){
		///spread
		spreadOpen(bombs,x,y);

	}
	else {
		bombs[x][y] |= 0x0F00;
	}
	return 0;
}
void spreadOpen(short **bombs,int x,int y){
	if( x<1 | x>10 | y<1 | y>10 | bombs[x][y]!=BO_NOHAVE_BOMB ) {
		bombs[x][y]|=0x0F00;
		return;
	}
	bombs[x][y]|=0x0F00;
	spreadOpen(bombs,x,y-1);
	spreadOpen(bombs,x-1,y);
	spreadOpen(bombs,x+1,y);
	spreadOpen(bombs,x,y+1);
}
