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

#define CXMAX 1.0
#define CXMIN -2.5
#define CYMAX 1.0
#define CYMIN -1.0

#define MAXITER 96
//#define HISTOGRAM
#define STEPSIZE 0.005

Uint32 tc,t0;

int forward;
int automatic;
int autodelay;
SDL_Surface *screen;
double cx,cy;

void updateParameters(const double ucx,const double ucy){
	cx=ucx;
	cy=ucy;
}

void setDelay(const int delay){
	autodelay=delay;
}

void checkbox(){
	if(automatic){
		automatic=0;
	}else{
		automatic=1;
	}
}

void draw_loop(){
#ifdef HISTOGRAM
	int histogram[MAXITER]={0};
#endif
	int iter;
	double zx,zy,zxs,zys;
	double red,green,blue;

	if(automatic){
		if((SDL_GetTicks()-t0)>autodelay){
			if(forward){
				cx+=STEPSIZE;
				if(cx>CXMAX){
					cx=cx-2*STEPSIZE;
					forward=0;
				}
			}else{
				cx-=STEPSIZE;
				if(cx<CXMIN){
					cx=cx+2*STEPSIZE;
					forward=1;
				}
			}
			t0=SDL_GetTicks();
		}
	}

//SDL_Surface *screen = SDL_SetVideoMode(XLEN, YLEN, 32, SDL_SWSURFACE);
	if(SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);

	for(int i=0;i<YLEN;i++){
		for(int j=0;j<XLEN;j++){
			iter=0;
			zx=((j<<2)*1.0/XLEN)-2.0;
			zy=((i<<1)*1.0/YLEN)-1.0;
			zxs=zx*zx;
			zys=zy*zy;
			while(((zxs+zys)<4.0)&&(iter<MAXITER)){
				zy=(2.0*zx*zy)+cy;
				zx=zxs-zys+cx;
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
}

int main(){
	t0=0;
	forward=1;
	automatic=0;
	checkbox();
	setDelay(100);
	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(XLEN, YLEN, 32, SDL_SWSURFACE);
	updateParameters(CXINIT,CYINIT);
	emscripten_set_main_loop(draw_loop,0,0);
//	emscripten_set_main_loop_timing(EM_TIMING_RAF,10);
	printf("Graph of the Julia Set.  Written in C.  Converted to WebASM through Emscripten.\n");
	printf("Move the sliders to change the picture.\n");
	return 0;
}
