#include<stdio.h>
#include<SDL/SDL.h>

#ifdef __EMSCRIPTEN__
#include<emscripten.h>
#endif

#define ALPHA 255	//ALPHA is ignored.
#define XLEN 512
#define YLEN 512

#define CXINIT -0.835

#define MAXITER 255

void draw(double cx){
	int histogram[256]={0};
	int iter;
	double zx,zy,zxs,zys;
	double cy;
	double tmp;
	double red,green,blue;
	cy=-0.2321;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *screen = SDL_SetVideoMode(XLEN, YLEN, 32, SDL_SWSURFACE);
	if(SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);

	for(int i=0;i<YLEN;i++){
		for(int j=0;j<XLEN;j++){
			iter=0;
			zx=(j*3.5/XLEN)-2.5;
			zy=(i*2.0/YLEN)-1;
			zxs=zx*zx;
			zys=zy*zy;
			while(((zxs+zys)<4.0)&&(iter<MAXITER)){
				tmp=zxs-zys;
//				zy=2*zx*zy+cy;
//				zx=tmp+cx;
				zys=2*zx*zy+cy;
				zys=zys*zys;
				zxs=tmp+cx;
				zxs=zxs*zxs;
				iter++;
			}
			histogram[iter]++;
/*
			if(iter>=MAXITER){
				red=green=blue=0;
			}else if (iter==1){
				red=green=blue=200;
			}else if (iter==2){
				red=green=blue=150;
			}else if (iter==3){
				red=green=blue=100;
			}else if (iter==4){
				red=green=blue=50;
			}else{
				red=green=blue=25;
				//red=green=blue=255.0-iter;
//				if((i==YLEN/2))
//					printf("%d %d: %f\n",i,j,red);
			}
*/
			if(iter<=90)
				red=green=blue=iter/90.0*255;
			else
				red=green=blue=0;
			*((Uint32*)screen->pixels+i*XLEN+j)=SDL_MapRGBA(screen->format,red,green,blue,ALPHA);
//			*((Uint32*)screen->pixels+i*XLEN+j)=SDL_MapRGBA(screen->format,i*255.0/YLEN,j*255.0/XLEN,255-i*255.0/YLEN,ALPHA);
		}
	}

//	for(int i=0;i<MAXITER;i++){
//		if(histogram[i]>0){
//			printf("%d:%d\n",i,histogram[i]);
//		}
//	}

	if(SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
	//  SDL_Flip(screen); 
//	 SDL_Quit();

	printf("Graph of the Julia Set.  Written in C.  Converted to Javascript through Emscripten.\n");
}
