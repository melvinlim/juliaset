#include<stdio.h>
#include<SDL/SDL.h>

#ifdef __EMSCRIPTEN__
#include<emscripten.h>
#endif

#define ALPHA 255	//ALPHA is ignored.
#define XLEN 512
#define YLEN 512

#define CXINIT -0.835
#define CYINIT -0.230

#define MAXITER 96
//#define HISTOGRAM

SDL_Surface *screen;

void draw(const double cx,const double cy){
#ifdef HISTOGRAM
	int histogram[MAXITER]={0};
#endif
	int iter;
	double zx,zy,zxs,zys;
	double tmp;
	double red,green,blue;

//SDL_Surface *screen = SDL_SetVideoMode(XLEN, YLEN, 32, SDL_SWSURFACE);
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
				zy=2*zx*zy+cy;
				zx=tmp+cx;
				zys=zy*zy;
				zxs=zx*zx;
				iter++;
			}
#ifdef HISTOGRAM
			histogram[iter]++;
#endif
			if(iter<=32){
				red=(iter<<3)-1;
				green=blue=0;
			//	red=green=blue=iter/90.0*255;
			}else if(iter<=64){
				green=((iter-32)<<3)-1;
//				red=255;
				red=0;
				blue=0;
			}else{
				blue=((iter-64)<<3)-1;
//				red=green=255;
				red=green=0;
				//red=green=blue=0;
			}
			*((Uint32*)screen->pixels+i*XLEN+j)=SDL_MapRGBA(screen->format,red,green,blue,ALPHA);
//			*((Uint32*)screen->pixels+i*XLEN+j)=SDL_MapRGBA(screen->format,i*255.0/YLEN,j*255.0/XLEN,255-i*255.0/YLEN,ALPHA);
		}
	}

#ifdef HISTOGRAM
	for(int i=0;i<MAXITER;i++){
		if(histogram[i]>0){
			printf("%d:%d\n",i,histogram[i]);
		}
	}
#endif

	if(SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
	//  SDL_Flip(screen); 
//	 SDL_Quit();

}

int main(){
	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(XLEN, YLEN, 32, SDL_SWSURFACE);
	draw(CXINIT,CYINIT);
	printf("Graph of the Julia Set.  Written in C.  Converted to Javascript through Emscripten.\n");
	printf("Move the sliders to change the picture.\n");
	return 0;
}
