#include <string.h>
#include "syspara.h"

void cluster4_setting()
{

	int i,c;

	// parameter setup information
	printf("Nx1=%d,Ny1=%d,Nx2=%d,Ny2=%d,Nx3=%d,Ny3=%d,Nx4=%d,Ny4=%d\n",Nx1,Ny1,Nx2,Ny2,Nx3,Ny3,Nx4,Ny4);
	for(i=0;i<MEDIA_SITE;i++) utype[i]=0;
	switch(cluster){
		case 1: // 1 cluster
			for(i = 0; i < MEDIA_SITE; i++){
				if( i >= 99*DX && i < 500*DX ){
					if( i%DX >= 99 && i%DX < 500 ) {
						utype[i]=1;
						c++;
					}
				} 
			}
			break;
		case 2: // 2 cluster
			for(i=0;i<MEDIA_SITE;i++){
				if( i>=Ny1*DX && i< Ny2*DX ){
					if( (i%DX >=Nx1 && i%DX < Nx2) || (i%DX >=Nx3 && i%DX < Nx4) ) {
						utype[i]=1;
						c++;
					}
				} 
			}
			break;

		case 5: // 4 cluster (asymmetry version) test1
			for(i=0;i<MEDIA_SITE;i++){
				if( (i>=Ny1*DX && i< Ny2*DX) ){
					if( (i%DX >=Nx1 && i%DX < Nx2) ) {
						utype[i]=1;
						c++;
					}
				} else if( (i>=Ny3*DX && i< Ny4*DX) ){
					if( (i%DX >=Nx3 && i%DX < Nx4) ) {
						utype[i]=1;
						c++;
					}
				} 
			}
		break;
		case 82002: // 4 cluster (8path) --> 200x200x4 left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=   8*DX && i < 208*DX) && (i%DX >=   8 && i%DX < 208 )) || 
				  	((i >=   8*DX && i < 208*DX) && (i%DX >= 216 && i%DX < 416 )) ||
				  	((i >= 216*DX && i < 416*DX) && (i%DX >=   8 && i%DX < 208 )) ||
				  	((i >= 216*DX && i < 416*DX) && (i%DX >= 216 && i%DX < 416 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8200: // 4 cluster (8path) --> 200x200x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  96*DX && i < 296*DX) && (i%DX >=  96 && i%DX < 296 )) || 
				  	((i >=  96*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 504 )) ||
				  	((i >= 304*DX && i < 504*DX) && (i%DX >=  96 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 504*DX) && (i%DX >= 304 && i%DX < 504 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8196: // 4 cluster (8path) --> 196x196x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 296*DX) && (i%DX >= 100 && i%DX < 296 )) || 
				  	((i >= 100*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 500 )) ||
				  	((i >= 304*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 500*DX) && (i%DX >= 304 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8190: // 4 cluster (8path) --> 190x190x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 106*DX && i < 296*DX) && (i%DX >= 106 && i%DX < 296 )) || 
				  	((i >= 106*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 494 )) ||
				  	((i >= 304*DX && i < 494*DX) && (i%DX >= 106 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 494*DX) && (i%DX >= 304 && i%DX < 494 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8180: // 4 cluster (8path) --> 180x180x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 116*DX && i < 296*DX) && (i%DX >= 116 && i%DX < 296 )) || 
				  	((i >= 116*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 484 )) ||
				  	((i >= 304*DX && i < 484*DX) && (i%DX >= 116 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 484*DX) && (i%DX >= 304 && i%DX < 484 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8170: // 4 cluster (8path) --> 170x170x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 126*DX && i < 296*DX) && (i%DX >= 126 && i%DX < 296 )) || 
				  	((i >= 126*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 474 )) ||
				  	((i >= 304*DX && i < 474*DX) && (i%DX >= 126 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 474*DX) && (i%DX >= 304 && i%DX < 474 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8160: // 4 cluster (8path) --> 160x160x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 136*DX && i < 296*DX) && (i%DX >= 136 && i%DX < 296 )) || 
				  	((i >= 136*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 464 )) ||
				  	((i >= 304*DX && i < 464*DX) && (i%DX >= 136 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 464*DX) && (i%DX >= 304 && i%DX < 464 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8150: // 4 cluster (8path) --> 160x160x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 146*DX && i < 296*DX) && (i%DX >= 146 && i%DX < 296 )) || 
				  	((i >= 146*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 454 )) ||
				  	((i >= 304*DX && i < 454*DX) && (i%DX >= 146 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 454*DX) && (i%DX >= 304 && i%DX < 454 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8140: // 4 cluster (8path) --> 140x140x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 156*DX && i < 296*DX) && (i%DX >= 156 && i%DX < 296 )) || 
				  	((i >= 156*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 444 )) ||
				  	((i >= 304*DX && i < 444*DX) && (i%DX >= 156 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 444*DX) && (i%DX >= 304 && i%DX < 444 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8138: // 4 cluster (8path) --> 138x138x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 158*DX && i < 296*DX) && (i%DX >= 158 && i%DX < 296 )) || 
				  	((i >= 158*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 442 )) ||
				  	((i >= 304*DX && i < 442*DX) && (i%DX >= 158 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 442*DX) && (i%DX >= 304 && i%DX < 442 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8136: // 4 cluster (8path) --> 136x136x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 160*DX && i < 296*DX) && (i%DX >= 160 && i%DX < 296 )) || 
				  	((i >= 160*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 440 )) ||
				  	((i >= 304*DX && i < 440*DX) && (i%DX >= 160 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 440*DX) && (i%DX >= 304 && i%DX < 440 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8134: // 4 cluster (8path) --> 134x134x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 162*DX && i < 296*DX) && (i%DX >= 162 && i%DX < 296 )) || 
				  	((i >= 162*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 438 )) ||
				  	((i >= 304*DX && i < 438*DX) && (i%DX >= 162 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 438*DX) && (i%DX >= 304 && i%DX < 438 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8132: // 4 cluster (8path) --> 132x132x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 164*DX && i < 296*DX) && (i%DX >= 164 && i%DX < 296 )) || 
				  	((i >= 164*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 436 )) ||
				  	((i >= 304*DX && i < 436*DX) && (i%DX >= 164 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 436*DX) && (i%DX >= 304 && i%DX < 436 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8130: // 4 cluster (8path) --> 130x130x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 166*DX && i < 296*DX) && (i%DX >= 166 && i%DX < 296 )) || 
				  	((i >= 166*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 434 )) ||
				  	((i >= 304*DX && i < 434*DX) && (i%DX >= 166 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 434*DX) && (i%DX >= 304 && i%DX < 434 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8128: // 4 cluster (8path) --> 128x128x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 168*DX && i < 296*DX) && (i%DX >= 168 && i%DX < 296 )) || 
				  	((i >= 168*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 432 )) ||
				  	((i >= 304*DX && i < 432*DX) && (i%DX >= 168 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 432*DX) && (i%DX >= 304 && i%DX < 432 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8126: // 4 cluster (8path) --> 126x126x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 170*DX && i < 296*DX) && (i%DX >= 170 && i%DX < 296 )) || 
				  	((i >= 170*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 430 )) ||
				  	((i >= 304*DX && i < 430*DX) && (i%DX >= 170 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 430*DX) && (i%DX >= 304 && i%DX < 430 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8124: // 4 cluster (8path) --> 124x124x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 172*DX && i < 296*DX) && (i%DX >= 172 && i%DX < 296 )) || 
				  	((i >= 172*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 428 )) ||
				  	((i >= 304*DX && i < 428*DX) && (i%DX >= 172 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 428*DX) && (i%DX >= 304 && i%DX < 428 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8122: // 4 cluster (8path) --> 120x122x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 174*DX && i < 296*DX) && (i%DX >= 174 && i%DX < 296 )) || 
				  	((i >= 174*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 426 )) ||
				  	((i >= 304*DX && i < 426*DX) && (i%DX >= 174 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 426*DX) && (i%DX >= 304 && i%DX < 426 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8120: // 4 cluster (8path) --> 120x120x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 176*DX && i < 296*DX) && (i%DX >= 176 && i%DX < 296 )) || 
				  	((i >= 176*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 424 )) ||
				  	((i >= 304*DX && i < 424*DX) && (i%DX >= 176 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 424*DX) && (i%DX >= 304 && i%DX < 424 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8100: // 4 cluster (8path) --> 100x100x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 196*DX && i < 296*DX) && (i%DX >= 196 && i%DX < 296 )) || 
				  	((i >= 196*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 404 )) ||
				  	((i >= 304*DX && i < 404*DX) && (i%DX >= 196 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 404*DX) && (i%DX >= 304 && i%DX < 404 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8080: // 4 cluster (8path) -->  80x 80x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 216*DX && i < 296*DX) && (i%DX >= 216 && i%DX < 296 )) || 
				  	((i >= 216*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 384 )) ||
				  	((i >= 304*DX && i < 384*DX) && (i%DX >= 216 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 384*DX) && (i%DX >= 304 && i%DX < 384 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8060: // 4 cluster (8path) -->  60x 60x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 236*DX && i < 296*DX) && (i%DX >= 236 && i%DX < 296 )) || 
				  	((i >= 236*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 364 )) ||
				  	((i >= 304*DX && i < 364*DX) && (i%DX >= 236 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 364*DX) && (i%DX >= 304 && i%DX < 364 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 102001: // 18path --> 200x200x4 top left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 190*DX && i < 390*DX) && (i%DX >=   0 && i%DX < 200 )) || 
				  	((i >= 190*DX && i < 390*DX) && (i%DX >= 210 && i%DX < 410 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >=   0 && i%DX < 200 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >= 210 && i%DX < 410 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 102002: // 4 cluster (10path) --> 200x200x4 left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  10*DX && i < 210*DX) && (i%DX >=  10 && i%DX < 210 )) || 
				  	((i >=  10*DX && i < 210*DX) && (i%DX >= 220 && i%DX < 420 )) ||
				  	((i >= 220*DX && i < 420*DX) && (i%DX >=  10 && i%DX < 210 )) ||
				  	((i >= 220*DX && i < 420*DX) && (i%DX >= 220 && i%DX < 420 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10200: // 4 cluster (10path) --> 200x200x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  95*DX && i < 295*DX) && (i%DX >=  95 && i%DX < 295 )) || 
				  	((i >=  95*DX && i < 295*DX) && (i%DX >= 305 && i%DX < 505 )) ||
				  	((i >= 305*DX && i < 505*DX) && (i%DX >=  95 && i%DX < 295 )) ||
				  	((i >= 305*DX && i < 505*DX) && (i%DX >= 305 && i%DX < 505 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10195: // 4 cluster (10path) --> 195x195x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 295*DX) && (i%DX >= 100 && i%DX < 295 )) || 
				  	((i >= 100*DX && i < 295*DX) && (i%DX >= 305 && i%DX < 500 )) ||
				  	((i >= 305*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 295 )) ||
				  	((i >= 305*DX && i < 500*DX) && (i%DX >= 305 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10190: // 4 cluster (10path) --> 190x190x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 105*DX && i < 295*DX) && (i%DX >= 105 && i%DX < 295 )) || 
				  	((i >= 105*DX && i < 295*DX) && (i%DX >= 305 && i%DX < 495 )) ||
				  	((i >= 305*DX && i < 495*DX) && (i%DX >= 105 && i%DX < 295 )) ||
				  	((i >= 305*DX && i < 495*DX) && (i%DX >= 305 && i%DX < 495 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10180: // 4 cluster (10path) --> 180x180x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 115*DX && i < 295*DX) && (i%DX >= 115 && i%DX < 295 )) || 
				  	((i >= 115*DX && i < 295*DX) && (i%DX >= 305 && i%DX < 485 )) ||
				  	((i >= 305*DX && i < 485*DX) && (i%DX >= 115 && i%DX < 295 )) ||
				  	((i >= 305*DX && i < 485*DX) && (i%DX >= 305 && i%DX < 485 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10170: // 4 cluster (10path) --> 170x170x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 125*DX && i < 295*DX) && (i%DX >= 125 && i%DX < 295 )) || 
				  	((i >= 125*DX && i < 295*DX) && (i%DX >= 305 && i%DX < 475 )) ||
				  	((i >= 305*DX && i < 475*DX) && (i%DX >= 125 && i%DX < 295 )) ||
				  	((i >= 305*DX && i < 475*DX) && (i%DX >= 305 && i%DX < 475 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10160: // 4 cluster (10path) --> 160x160x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 135*DX && i < 295*DX) && (i%DX >= 135 && i%DX < 295 )) || 
				  	((i >= 135*DX && i < 295*DX) && (i%DX >= 305 && i%DX < 465 )) ||
				  	((i >= 305*DX && i < 465*DX) && (i%DX >= 135 && i%DX < 295 )) ||
				  	((i >= 305*DX && i < 465*DX) && (i%DX >= 305 && i%DX < 465 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10150: // 4 cluster (10path) --> 150x150x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 145*DX && i < 295*DX) && (i%DX >= 145 && i%DX < 295 )) || 
				  	((i >= 145*DX && i < 295*DX) && (i%DX >= 305 && i%DX < 455 )) ||
				  	((i >= 305*DX && i < 455*DX) && (i%DX >= 145 && i%DX < 295 )) ||
				  	((i >= 305*DX && i < 455*DX) && (i%DX >= 305 && i%DX < 455 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10140: // 4 cluster (10path) --> 140x140x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 155*DX && i < 295*DX) && (i%DX >= 155 && i%DX < 295 )) || 
				  	((i >= 155*DX && i < 295*DX) && (i%DX >= 305 && i%DX < 445 )) ||
				  	((i >= 305*DX && i < 445*DX) && (i%DX >= 155 && i%DX < 295 )) ||
				  	((i >= 305*DX && i < 445*DX) && (i%DX >= 305 && i%DX < 445 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10135: // 4 cluster (10path) --> 135x135x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 160*DX && i < 295*DX) && (i%DX >= 160 && i%DX < 295 )) || 
				  	((i >= 160*DX && i < 295*DX) && (i%DX >= 305 && i%DX < 440 )) ||
				  	((i >= 305*DX && i < 440*DX) && (i%DX >= 160 && i%DX < 295 )) ||
				  	((i >= 305*DX && i < 440*DX) && (i%DX >= 305 && i%DX < 440 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10133: // 4 cluster (10path) --> 133x133x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 162*DX && i < 295*DX) && (i%DX >= 162 && i%DX < 295 )) || 
				  	((i >= 162*DX && i < 295*DX) && (i%DX >= 305 && i%DX < 438 )) ||
				  	((i >= 305*DX && i < 438*DX) && (i%DX >= 162 && i%DX < 295 )) ||
				  	((i >= 305*DX && i < 438*DX) && (i%DX >= 305 && i%DX < 438 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10130: // 4 cluster (10path) --> 130x130x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 165*DX && i < 295*DX) && (i%DX >= 165 && i%DX < 295 )) || 
				  	((i >= 165*DX && i < 295*DX) && (i%DX >= 305 && i%DX < 435 )) ||
				  	((i >= 305*DX && i < 435*DX) && (i%DX >= 165 && i%DX < 295 )) ||
				  	((i >= 305*DX && i < 435*DX) && (i%DX >= 305 && i%DX < 435 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10128: // 4 cluster (10path) --> 125x125x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 167*DX && i < 295*DX) && (i%DX >= 167 && i%DX < 295 )) || 
				  	((i >= 167*DX && i < 295*DX) && (i%DX >= 305 && i%DX < 433 )) ||
				  	((i >= 305*DX && i < 433*DX) && (i%DX >= 167 && i%DX < 295 )) ||
				  	((i >= 305*DX && i < 433*DX) && (i%DX >= 305 && i%DX < 433 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10126: // 4 cluster (10path) --> 126x126x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 169*DX && i < 295*DX) && (i%DX >= 169 && i%DX < 295 )) || 
				  	((i >= 169*DX && i < 295*DX) && (i%DX >= 305 && i%DX < 431 )) ||
				  	((i >= 305*DX && i < 431*DX) && (i%DX >= 169 && i%DX < 295 )) ||
				  	((i >= 305*DX && i < 431*DX) && (i%DX >= 305 && i%DX < 431 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10125: // 4 cluster (10path) --> 125x125x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 170*DX && i < 295*DX) && (i%DX >= 170 && i%DX < 295 )) || 
				  	((i >= 170*DX && i < 295*DX) && (i%DX >= 305 && i%DX < 430 )) ||
				  	((i >= 305*DX && i < 430*DX) && (i%DX >= 170 && i%DX < 295 )) ||
				  	((i >= 305*DX && i < 430*DX) && (i%DX >= 305 && i%DX < 430 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10124: // 4 cluster (10path) --> 124x124x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 171*DX && i < 295*DX) && (i%DX >= 171 && i%DX < 295 )) || 
				  	((i >= 171*DX && i < 295*DX) && (i%DX >= 305 && i%DX < 429 )) ||
				  	((i >= 305*DX && i < 429*DX) && (i%DX >= 171 && i%DX < 295 )) ||
				  	((i >= 305*DX && i < 429*DX) && (i%DX >= 305 && i%DX < 429 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10122: // 4 cluster (10path) --> 122x122x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 173*DX && i < 295*DX) && (i%DX >= 173 && i%DX < 295 )) || 
				  	((i >= 173*DX && i < 295*DX) && (i%DX >= 305 && i%DX < 427 )) ||
				  	((i >= 305*DX && i < 427*DX) && (i%DX >= 173 && i%DX < 295 )) ||
				  	((i >= 305*DX && i < 427*DX) && (i%DX >= 305 && i%DX < 427 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10120: // 4 cluster (10path) --> 120x120x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 175*DX && i < 295*DX) && (i%DX >= 175 && i%DX < 295 )) || 
				  	((i >= 175*DX && i < 295*DX) && (i%DX >= 305 && i%DX < 425 )) ||
				  	((i >= 305*DX && i < 425*DX) && (i%DX >= 175 && i%DX < 295 )) ||
				  	((i >= 305*DX && i < 425*DX) && (i%DX >= 305 && i%DX < 425 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10100: // 4 cluster (10path) --> 100x100x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 195*DX && i < 295*DX) && (i%DX >= 195 && i%DX < 295 )) || 
				  	((i >= 195*DX && i < 295*DX) && (i%DX >= 305 && i%DX < 405 )) ||
				  	((i >= 305*DX && i < 405*DX) && (i%DX >= 195 && i%DX < 295 )) ||
				  	((i >= 305*DX && i < 405*DX) && (i%DX >= 305 && i%DX < 405 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10080: // 4 cluster (10path) -->  80x 80x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 215*DX && i < 295*DX) && (i%DX >= 215 && i%DX < 295 )) || 
				  	((i >= 215*DX && i < 295*DX) && (i%DX >= 305 && i%DX < 385 )) ||
				  	((i >= 305*DX && i < 385*DX) && (i%DX >= 215 && i%DX < 295 )) ||
				  	((i >= 305*DX && i < 385*DX) && (i%DX >= 305 && i%DX < 385 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 122001: // 12path --> 200x200x4 top left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 188*DX && i < 388*DX) && (i%DX >=   0 && i%DX < 200 )) || 
				  	((i >= 188*DX && i < 388*DX) && (i%DX >= 212 && i%DX < 412 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >=   0 && i%DX < 200 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >= 212 && i%DX < 412 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 122002: // 4 cluster (12path) --> 200x200x4 left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  12*DX && i < 212*DX) && (i%DX >=  12 && i%DX < 212 )) || 
				  	((i >=  12*DX && i < 212*DX) && (i%DX >= 224 && i%DX < 424 )) ||
				  	((i >= 224*DX && i < 424*DX) && (i%DX >=  12 && i%DX < 212 )) ||
				  	((i >= 224*DX && i < 424*DX) && (i%DX >= 224 && i%DX < 424 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12200: // 4 cluster (12path) --> 200x200x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  94*DX && i < 294*DX) && (i%DX >=  94 && i%DX < 294 )) || 
				  	((i >=  94*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 506 )) ||
				  	((i >= 306*DX && i < 506*DX) && (i%DX >=  94 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 506*DX) && (i%DX >= 306 && i%DX < 506 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12194: // 4 cluster (12path) --> 194x194x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 294*DX) && (i%DX >= 100 && i%DX < 294 )) || 
				  	((i >= 100*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 500 )) ||
				  	((i >= 306*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 500*DX) && (i%DX >= 306 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12190: // 4 cluster (12path) --> 190x190x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 104*DX && i < 294*DX) && (i%DX >= 104 && i%DX < 294 )) || 
				  	((i >= 104*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 496 )) ||
				  	((i >= 306*DX && i < 496*DX) && (i%DX >= 104 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 496*DX) && (i%DX >= 306 && i%DX < 496 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12180: // 4 cluster (12path) --> 180x180x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 114*DX && i < 294*DX) && (i%DX >= 114 && i%DX < 294 )) || 
				  	((i >= 114*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 486 )) ||
				  	((i >= 306*DX && i < 486*DX) && (i%DX >= 114 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 486*DX) && (i%DX >= 306 && i%DX < 486 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12170: // 4 cluster (12path) --> 170x170x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 124*DX && i < 294*DX) && (i%DX >= 124 && i%DX < 294 )) || 
				  	((i >= 124*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 476 )) ||
				  	((i >= 306*DX && i < 476*DX) && (i%DX >= 124 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 476*DX) && (i%DX >= 306 && i%DX < 476 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12160: // 4 cluster (12path) --> 160x160x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 134*DX && i < 294*DX) && (i%DX >= 134 && i%DX < 294 )) || 
				  	((i >= 134*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 466 )) ||
				  	((i >= 306*DX && i < 466*DX) && (i%DX >= 134 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 466*DX) && (i%DX >= 306 && i%DX < 466 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12140: // 4 cluster (12path) --> 140x140x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 154*DX && i < 294*DX) && (i%DX >= 154 && i%DX < 294 )) || 
				  	((i >= 154*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 446 )) ||
				  	((i >= 306*DX && i < 446*DX) && (i%DX >= 154 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 446*DX) && (i%DX >= 306 && i%DX < 446 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12138: // 4 cluster (12path) --> 138x138x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 156*DX && i < 294*DX) && (i%DX >= 156 && i%DX < 294 )) || 
				  	((i >= 156*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 444 )) ||
				  	((i >= 306*DX && i < 444*DX) && (i%DX >= 156 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 444*DX) && (i%DX >= 306 && i%DX < 444 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12136: // 4 cluster (12path) --> 136x136x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 158*DX && i < 294*DX) && (i%DX >= 158 && i%DX < 294 )) || 
				  	((i >= 158*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 442 )) ||
				  	((i >= 306*DX && i < 442*DX) && (i%DX >= 158 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 442*DX) && (i%DX >= 306 && i%DX < 442 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12134: // 4 cluster (12path) --> 134x134x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 160*DX && i < 294*DX) && (i%DX >= 160 && i%DX < 294 )) || 
				  	((i >= 160*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 440 )) ||
				  	((i >= 306*DX && i < 440*DX) && (i%DX >= 160 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 440*DX) && (i%DX >= 306 && i%DX < 440 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12132: // 4 cluster (12path) --> 132x132x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 162*DX && i < 294*DX) && (i%DX >= 162 && i%DX < 294 )) || 
				  	((i >= 162*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 438 )) ||
				  	((i >= 306*DX && i < 438*DX) && (i%DX >= 162 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 438*DX) && (i%DX >= 306 && i%DX < 438 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12130: // 4 cluster (12path) --> 130x130x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 164*DX && i < 294*DX) && (i%DX >= 164 && i%DX < 294 )) || 
				  	((i >= 164*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 436 )) ||
				  	((i >= 306*DX && i < 436*DX) && (i%DX >= 164 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 436*DX) && (i%DX >= 306 && i%DX < 436 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12128: // 4 cluster (12path) --> 128x128x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 166*DX && i < 294*DX) && (i%DX >= 166 && i%DX < 294 )) || 
				  	((i >= 166*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 434 )) ||
				  	((i >= 306*DX && i < 434*DX) && (i%DX >= 166 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 434*DX) && (i%DX >= 306 && i%DX < 434 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12126: // 4 cluster (12path) --> 126x126x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 168*DX && i < 294*DX) && (i%DX >= 168 && i%DX < 294 )) || 
				  	((i >= 168*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 432 )) ||
				  	((i >= 306*DX && i < 432*DX) && (i%DX >= 168 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 432*DX) && (i%DX >= 306 && i%DX < 432 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12124: // 4 cluster (12path) --> 124x124x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 170*DX && i < 294*DX) && (i%DX >= 170 && i%DX < 294 )) || 
				  	((i >= 170*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 430 )) ||
				  	((i >= 306*DX && i < 430*DX) && (i%DX >= 170 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 430*DX) && (i%DX >= 306 && i%DX < 430 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12122: // 4 cluster (12path) --> 122x122x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 172*DX && i < 294*DX) && (i%DX >= 172 && i%DX < 294 )) || 
				  	((i >= 172*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 428 )) ||
				  	((i >= 306*DX && i < 428*DX) && (i%DX >= 172 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 428*DX) && (i%DX >= 306 && i%DX < 428 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12120: // 4 cluster (12path) --> 120x120x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 174*DX && i < 294*DX) && (i%DX >= 174 && i%DX < 294 )) || 
				  	((i >= 174*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 426 )) ||
				  	((i >= 306*DX && i < 426*DX) && (i%DX >= 174 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 426*DX) && (i%DX >= 306 && i%DX < 426 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12100: // 4 cluster (12path) --> 100x100x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 194*DX && i < 294*DX) && (i%DX >= 194 && i%DX < 294 )) || 
				  	((i >= 194*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 406 )) ||
				  	((i >= 306*DX && i < 406*DX) && (i%DX >= 194 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 406*DX) && (i%DX >= 306 && i%DX < 406 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12080: // 4 cluster (12path) -->  80x 80x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 214*DX && i < 294*DX) && (i%DX >= 214 && i%DX < 294 )) || 
				  	((i >= 214*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 386 )) ||
				  	((i >= 306*DX && i < 386*DX) && (i%DX >= 214 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 386*DX) && (i%DX >= 306 && i%DX < 386 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 142001: // 14path --> 200x200x4 top left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 186*DX && i < 386*DX) && (i%DX >=   0 && i%DX < 200 )) || 
				  	((i >= 186*DX && i < 386*DX) && (i%DX >= 214 && i%DX < 414 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >=   0 && i%DX < 200 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >= 214 && i%DX < 414 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 142002: // 4 cluster (14path) --> 200x200x4 left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  14*DX && i < 214*DX) && (i%DX >=  14 && i%DX < 214 )) || 
				  	((i >=  14*DX && i < 214*DX) && (i%DX >= 228 && i%DX < 428 )) ||
				  	((i >= 228*DX && i < 428*DX) && (i%DX >=  14 && i%DX < 214 )) ||
				  	((i >= 228*DX && i < 428*DX) && (i%DX >= 228 && i%DX < 428 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14200: // 4 cluster (14path) --> 200x200x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  93*DX && i < 293*DX) && (i%DX >=  93 && i%DX < 293 )) || 
				  	((i >=  93*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 507 )) ||
				  	((i >= 307*DX && i < 507*DX) && (i%DX >=  93 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 507*DX) && (i%DX >= 307 && i%DX < 507 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14193: // 4 cluster (14path) --> 193x193x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 293*DX) && (i%DX >= 100 && i%DX < 293 )) || 
				  	((i >= 100*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 500 )) ||
				  	((i >= 307*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 500*DX) && (i%DX >= 307 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14190: // 4 cluster (14path) --> 190x190x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 103*DX && i < 293*DX) && (i%DX >= 103 && i%DX < 293 )) || 
				  	((i >= 103*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 497 )) ||
				  	((i >= 307*DX && i < 497*DX) && (i%DX >= 103 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 497*DX) && (i%DX >= 307 && i%DX < 497 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14180: // 4 cluster (14path) --> 180x180x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 113*DX && i < 293*DX) && (i%DX >= 113 && i%DX < 293 )) || 
				  	((i >= 113*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 487 )) ||
				  	((i >= 307*DX && i < 487*DX) && (i%DX >= 113 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 487*DX) && (i%DX >= 307 && i%DX < 487 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14170: // 4 cluster (14path) --> 160x160x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 123*DX && i < 293*DX) && (i%DX >= 123 && i%DX < 293 )) || 
				  	((i >= 123*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 477 )) ||
				  	((i >= 307*DX && i < 477*DX) && (i%DX >= 123 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 477*DX) && (i%DX >= 307 && i%DX < 477 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14160: // 4 cluster (14path) --> 160x160x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 133*DX && i < 293*DX) && (i%DX >= 133 && i%DX < 293 )) || 
				  	((i >= 133*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 467 )) ||
				  	((i >= 307*DX && i < 467*DX) && (i%DX >= 133 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 467*DX) && (i%DX >= 307 && i%DX < 467 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14150: // 4 cluster (14path) --> 150x150x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 143*DX && i < 293*DX) && (i%DX >= 143 && i%DX < 293 )) || 
				  	((i >= 143*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 457 )) ||
				  	((i >= 307*DX && i < 457*DX) && (i%DX >= 143 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 457*DX) && (i%DX >= 307 && i%DX < 457 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14148: // 4 cluster (14path) --> 148x148x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 145*DX && i < 293*DX) && (i%DX >= 145 && i%DX < 293 )) || 
				  	((i >= 145*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 455 )) ||
				  	((i >= 307*DX && i < 455*DX) && (i%DX >= 145 && i%DX < 251 )) ||
				  	((i >= 307*DX && i < 455*DX) && (i%DX >= 307 && i%DX < 455 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14146: // 4 cluster (14path) --> 146x146x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 147*DX && i < 293*DX) && (i%DX >= 147 && i%DX < 293 )) || 
				  	((i >= 147*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 453 )) ||
				  	((i >= 307*DX && i < 453*DX) && (i%DX >= 147 && i%DX < 251 )) ||
				  	((i >= 307*DX && i < 453*DX) && (i%DX >= 307 && i%DX < 453 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14144: // 4 cluster (14path) --> 144x144x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 149*DX && i < 293*DX) && (i%DX >= 149 && i%DX < 293 )) || 
				  	((i >= 149*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 451 )) ||
				  	((i >= 307*DX && i < 451*DX) && (i%DX >= 149 && i%DX < 251 )) ||
				  	((i >= 307*DX && i < 451*DX) && (i%DX >= 307 && i%DX < 451 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14142: // 4 cluster (14path) --> 142x142x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 151*DX && i < 293*DX) && (i%DX >= 151 && i%DX < 293 )) || 
				  	((i >= 151*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 449 )) ||
				  	((i >= 307*DX && i < 449*DX) && (i%DX >= 151 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 449*DX) && (i%DX >= 307 && i%DX < 449 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14141: // 4 cluster (14path) --> 141x141x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 152*DX && i < 293*DX) && (i%DX >= 152 && i%DX < 293 )) || 
				  	((i >= 152*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 448 )) ||
				  	((i >= 307*DX && i < 448*DX) && (i%DX >= 152 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 448*DX) && (i%DX >= 307 && i%DX < 448 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14140: // 4 cluster (14path) --> 140x140x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 153*DX && i < 293*DX) && (i%DX >= 153 && i%DX < 293 )) || 
				  	((i >= 153*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 447 )) ||
				  	((i >= 307*DX && i < 447*DX) && (i%DX >= 153 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 447*DX) && (i%DX >= 307 && i%DX < 447 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14138: // 4 cluster (14path) --> 138x138x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 155*DX && i < 293*DX) && (i%DX >= 155 && i%DX < 293 )) || 
				  	((i >= 155*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 445 )) ||
				  	((i >= 307*DX && i < 445*DX) && (i%DX >= 155 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 445*DX) && (i%DX >= 307 && i%DX < 445 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14136: // 4 cluster (14path) --> 136x136x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 157*DX && i < 293*DX) && (i%DX >= 157 && i%DX < 293 )) || 
				  	((i >= 157*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 443 )) ||
				  	((i >= 307*DX && i < 443*DX) && (i%DX >= 157 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 443*DX) && (i%DX >= 307 && i%DX < 443 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14134: // 4 cluster (14path) --> 134x134x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 159*DX && i < 293*DX) && (i%DX >= 159 && i%DX < 293 )) || 
				  	((i >= 159*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 441 )) ||
				  	((i >= 307*DX && i < 441*DX) && (i%DX >= 159 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 441*DX) && (i%DX >= 307 && i%DX < 441 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14133: // 4 cluster (14path) --> 133x133x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 160*DX && i < 293*DX) && (i%DX >= 160 && i%DX < 293 )) || 
				  	((i >= 160*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 440 )) ||
				  	((i >= 307*DX && i < 440*DX) && (i%DX >= 160 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 440*DX) && (i%DX >= 307 && i%DX < 440 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14132: // 4 cluster (14path) --> 132x132x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 161*DX && i < 293*DX) && (i%DX >= 161 && i%DX < 293 )) || 
				  	((i >= 161*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 439 )) ||
				  	((i >= 307*DX && i < 439*DX) && (i%DX >= 161 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 439*DX) && (i%DX >= 307 && i%DX < 439 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14130: // 4 cluster (14path) --> 130x130x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 163*DX && i < 293*DX) && (i%DX >= 163 && i%DX < 293 )) || 
				  	((i >= 163*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 437 )) ||
				  	((i >= 307*DX && i < 437*DX) && (i%DX >= 163 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 437*DX) && (i%DX >= 307 && i%DX < 437 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14120: // 4 cluster (14path) --> 120x120x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 173*DX && i < 293*DX) && (i%DX >= 173 && i%DX < 293 )) || 
				  	((i >= 173*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 427 )) ||
				  	((i >= 307*DX && i < 427*DX) && (i%DX >= 173 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 427*DX) && (i%DX >= 307 && i%DX < 427 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14100: // 4 cluster (14path) --> 100x100x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 193*DX && i < 293*DX) && (i%DX >= 193 && i%DX < 293 )) || 
				  	((i >= 193*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 407 )) ||
				  	((i >= 307*DX && i < 407*DX) && (i%DX >= 193 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 407*DX) && (i%DX >= 307 && i%DX < 407 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 162001: // 16path --> 200x200x4 top left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 184*DX && i < 384*DX) && (i%DX >=   0 && i%DX < 200 )) || 
				  	((i >= 184*DX && i < 384*DX) && (i%DX >= 216 && i%DX < 416 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >=   0 && i%DX < 200 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >= 216 && i%DX < 416 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 162002: // 4 cluster (16path) --> 200x200x4 left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  16*DX && i < 216*DX) && (i%DX >=  16 && i%DX < 216 )) || 
				  	((i >=  16*DX && i < 216*DX) && (i%DX >= 232 && i%DX < 432 )) ||
				  	((i >= 232*DX && i < 432*DX) && (i%DX >=  16 && i%DX < 216 )) ||
				  	((i >= 232*DX && i < 432*DX) && (i%DX >= 232 && i%DX < 432 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 16200: // 4 cluster (16path) --> 200x200x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  92*DX && i < 292*DX) && (i%DX >=  92 && i%DX < 292 )) || 
				  	((i >=  92*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 508 )) ||
				  	((i >= 308*DX && i < 508*DX) && (i%DX >=  92 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 508*DX) && (i%DX >= 308 && i%DX < 508 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 16192: // 4 cluster (16path) --> 192x192x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 292*DX) && (i%DX >= 100 && i%DX < 292 )) || 
				  	((i >= 100*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 500 )) ||
				  	((i >= 308*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 500*DX) && (i%DX >= 308 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 16190: // 4 cluster (16path) --> 190x190x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 102*DX && i < 292*DX) && (i%DX >= 102 && i%DX < 292 )) || 
				  	((i >= 102*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 498 )) ||
				  	((i >= 308*DX && i < 498*DX) && (i%DX >= 102 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 498*DX) && (i%DX >= 308 && i%DX < 498 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 16180: // 4 cluster (16path) --> 180x180x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 112*DX && i < 292*DX) && (i%DX >= 112 && i%DX < 292 )) || 
				  	((i >= 112*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 488 )) ||
				  	((i >= 308*DX && i < 488*DX) && (i%DX >= 112 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 488*DX) && (i%DX >= 308 && i%DX < 488 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 16170: // 4 cluster (16path) --> 170x170x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 122*DX && i < 292*DX) && (i%DX >= 122 && i%DX < 292 )) || 
				  	((i >= 122*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 478 )) ||
				  	((i >= 308*DX && i < 478*DX) && (i%DX >= 122 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 478*DX) && (i%DX >= 308 && i%DX < 478 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 16160: // 4 cluster (16path) --> 160x160x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 132*DX && i < 292*DX) && (i%DX >= 132 && i%DX < 292 )) || 
				  	((i >= 132*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 468 )) ||
				  	((i >= 308*DX && i < 468*DX) && (i%DX >= 132 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 468*DX) && (i%DX >= 308 && i%DX < 468 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 16150: // 4 cluster (16path) --> 150x150x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 142*DX && i < 292*DX) && (i%DX >= 142 && i%DX < 292 )) || 
				  	((i >= 142*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 458 )) ||
				  	((i >= 308*DX && i < 458*DX) && (i%DX >= 142 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 458*DX) && (i%DX >= 308 && i%DX < 458 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 16140: // 4 cluster (16path) --> 140x140x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 152*DX && i < 292*DX) && (i%DX >= 152 && i%DX < 292 )) || 
				  	((i >= 152*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 448 )) ||
				  	((i >= 308*DX && i < 448*DX) && (i%DX >= 152 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 448*DX) && (i%DX >= 308 && i%DX < 448 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 16139: // 4 cluster (16path) --> 139x139x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 153*DX && i < 292*DX) && (i%DX >= 153 && i%DX < 292 )) || 
				  	((i >= 153*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 447 )) ||
				  	((i >= 308*DX && i < 447*DX) && (i%DX >= 153 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 447*DX) && (i%DX >= 308 && i%DX < 447 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 16138: // 4 cluster (16path) --> 138x138x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 154*DX && i < 292*DX) && (i%DX >= 154 && i%DX < 292 )) || 
				  	((i >= 154*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 446 )) ||
				  	((i >= 308*DX && i < 446*DX) && (i%DX >= 154 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 446*DX) && (i%DX >= 308 && i%DX < 446 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 16136: // 4 cluster (16path) --> 136x136x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 156*DX && i < 292*DX) && (i%DX >= 156 && i%DX < 292 )) || 
				  	((i >= 156*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 444 )) ||
				  	((i >= 308*DX && i < 444*DX) && (i%DX >= 156 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 444*DX) && (i%DX >= 308 && i%DX < 444 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 16134: // 4 cluster (16path) --> 134x134x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 158*DX && i < 292*DX) && (i%DX >= 158 && i%DX < 292 )) || 
				  	((i >= 158*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 442 )) ||
				  	((i >= 308*DX && i < 442*DX) && (i%DX >= 158 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 442*DX) && (i%DX >= 308 && i%DX < 442 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 16132: // 4 cluster (16path) --> 132x132x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 160*DX && i < 292*DX) && (i%DX >= 160 && i%DX < 292 )) || 
				  	((i >= 160*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 440 )) ||
				  	((i >= 308*DX && i < 440*DX) && (i%DX >= 160 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 440*DX) && (i%DX >= 308 && i%DX < 440 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 16130: // 4 cluster (16path) --> 130x130x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 162*DX && i < 292*DX) && (i%DX >= 162 && i%DX < 292 )) || 
				  	((i >= 162*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 438 )) ||
				  	((i >= 308*DX && i < 438*DX) && (i%DX >= 162 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 438*DX) && (i%DX >= 308 && i%DX < 438 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 16120: // 4 cluster (16path) --> 120x120x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 172*DX && i < 292*DX) && (i%DX >= 172 && i%DX < 292 )) || 
				  	((i >= 172*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 428 )) ||
				  	((i >= 308*DX && i < 428*DX) && (i%DX >= 172 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 428*DX) && (i%DX >= 308 && i%DX < 428 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 16110: // 4 cluster (16path) --> 110x110x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 182*DX && i < 292*DX) && (i%DX >= 182 && i%DX < 292 )) || 
				  	((i >= 182*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 418 )) ||
				  	((i >= 308*DX && i < 418*DX) && (i%DX >= 182 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 418*DX) && (i%DX >= 308 && i%DX < 418 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 16100: // 4 cluster (16path) --> 100x100x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 192*DX && i < 292*DX) && (i%DX >= 192 && i%DX < 292 )) || 
				  	((i >= 192*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 408 )) ||
				  	((i >= 308*DX && i < 408*DX) && (i%DX >= 192 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 408*DX) && (i%DX >= 308 && i%DX < 408 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 182001: // 18path --> 200x200x4 top left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 182*DX && i < 382*DX) && (i%DX >=   0 && i%DX < 200 )) || 
				  	((i >= 182*DX && i < 382*DX) && (i%DX >= 218 && i%DX < 418 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >=   0 && i%DX < 200 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >= 218 && i%DX < 418 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 182002: // 4 cluster (18path) --> 200x200x4 left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  18*DX && i < 218*DX) && (i%DX >=  18 && i%DX < 218 )) || 
				  	((i >=  18*DX && i < 218*DX) && (i%DX >= 236 && i%DX < 436 )) ||
				  	((i >= 236*DX && i < 436*DX) && (i%DX >=  18 && i%DX < 218 )) ||
				  	((i >= 236*DX && i < 436*DX) && (i%DX >= 236 && i%DX < 436 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18200: // 4 cluster (18path) --> 200x200x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  91*DX && i < 291*DX) && (i%DX >=  91 && i%DX < 291 )) || 
				  	((i >=  91*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 509 )) ||
				  	((i >= 309*DX && i < 509*DX) && (i%DX >=  91 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 509*DX) && (i%DX >= 309 && i%DX < 509 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18191: // 4 cluster (18path) --> 191x191x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 291*DX) && (i%DX >= 100 && i%DX < 291 )) || 
				  	((i >= 100*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 500 )) ||
				  	((i >= 309*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 500*DX) && (i%DX >= 309 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18190: // 4 cluster (18path) --> 190x190x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 101*DX && i < 291*DX) && (i%DX >= 101 && i%DX < 291 )) || 
				  	((i >= 101*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 499 )) ||
				  	((i >= 309*DX && i < 499*DX) && (i%DX >= 101 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 499*DX) && (i%DX >= 309 && i%DX < 499 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18180: // 4 cluster (18path) --> 180x180x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 111*DX && i < 291*DX) && (i%DX >= 111 && i%DX < 291 )) || 
				  	((i >= 111*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 489 )) ||
				  	((i >= 309*DX && i < 489*DX) && (i%DX >= 111 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 489*DX) && (i%DX >= 309 && i%DX < 489 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18170: // 4 cluster (18path) --> 170x170x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 121*DX && i < 291*DX) && (i%DX >= 121 && i%DX < 291 )) || 
				  	((i >= 121*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 479 )) ||
				  	((i >= 309*DX && i < 479*DX) && (i%DX >= 121 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 479*DX) && (i%DX >= 309 && i%DX < 479 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18160: // 4 cluster (18path) --> 160x160x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 131*DX && i < 291*DX) && (i%DX >= 131 && i%DX < 291 )) || 
				  	((i >= 131*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 469 )) ||
				  	((i >= 309*DX && i < 469*DX) && (i%DX >= 131 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 469*DX) && (i%DX >= 309 && i%DX < 469 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18150: // 4 cluster (18path) --> 150x150x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 141*DX && i < 291*DX) && (i%DX >= 141 && i%DX < 291 )) || 
				  	((i >= 141*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 459 )) ||
				  	((i >= 309*DX && i < 459*DX) && (i%DX >= 141 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 459*DX) && (i%DX >= 309 && i%DX < 459 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18149: // 4 cluster (18path) --> 149x149x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 142*DX && i < 291*DX) && (i%DX >= 142 && i%DX < 291 )) || 
				  	((i >= 142*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 458 )) ||
				  	((i >= 309*DX && i < 458*DX) && (i%DX >= 142 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 458*DX) && (i%DX >= 309 && i%DX < 458 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18148: // 4 cluster (18path) --> 148x148x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 143*DX && i < 291*DX) && (i%DX >= 143 && i%DX < 291 )) || 
				  	((i >= 143*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 457 )) ||
				  	((i >= 309*DX && i < 457*DX) && (i%DX >= 143 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 457*DX) && (i%DX >= 309 && i%DX < 457 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18147: // 4 cluster (18path) --> 147x147x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 144*DX && i < 291*DX) && (i%DX >= 144 && i%DX < 291 )) || 
				  	((i >= 144*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 456 )) ||
				  	((i >= 309*DX && i < 456*DX) && (i%DX >= 144 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 456*DX) && (i%DX >= 309 && i%DX < 456 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18146: // 4 cluster (18path) --> 146x146x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 145*DX && i < 291*DX) && (i%DX >= 145 && i%DX < 291 )) || 
				  	((i >= 145*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 455 )) ||
				  	((i >= 309*DX && i < 455*DX) && (i%DX >= 145 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 455*DX) && (i%DX >= 309 && i%DX < 455 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18145: // 4 cluster (18path) --> 145x145x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 146*DX && i < 291*DX) && (i%DX >= 146 && i%DX < 291 )) || 
				  	((i >= 146*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 454 )) ||
				  	((i >= 309*DX && i < 454*DX) && (i%DX >= 146 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 454*DX) && (i%DX >= 309 && i%DX < 454 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18144: // 4 cluster (18path) --> 144x144x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 147*DX && i < 291*DX) && (i%DX >= 147 && i%DX < 291 )) || 
				  	((i >= 147*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 453 )) ||
				  	((i >= 309*DX && i < 453*DX) && (i%DX >= 147 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 453*DX) && (i%DX >= 309 && i%DX < 453 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18143: // 4 cluster (18path) --> 143x143x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 148*DX && i < 291*DX) && (i%DX >= 148 && i%DX < 291 )) || 
				  	((i >= 148*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 452 )) ||
				  	((i >= 309*DX && i < 452*DX) && (i%DX >= 148 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 452*DX) && (i%DX >= 309 && i%DX < 452 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18142: // 4 cluster (18path) --> 142x142x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 149*DX && i < 291*DX) && (i%DX >= 149 && i%DX < 291 )) || 
				  	((i >= 149*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 451 )) ||
				  	((i >= 309*DX && i < 451*DX) && (i%DX >= 149 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 451*DX) && (i%DX >= 309 && i%DX < 451 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18141: // 4 cluster (18path) --> 142x142x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 150*DX && i < 291*DX) && (i%DX >= 150 && i%DX < 291 )) || 
				  	((i >= 150*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 450 )) ||
				  	((i >= 309*DX && i < 450*DX) && (i%DX >= 150 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 450*DX) && (i%DX >= 309 && i%DX < 450 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18140: // 4 cluster (18path) --> 140x140x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 151*DX && i < 291*DX) && (i%DX >= 151 && i%DX < 291 )) || 
				  	((i >= 151*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 449 )) ||
				  	((i >= 309*DX && i < 449*DX) && (i%DX >= 151 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 449*DX) && (i%DX >= 309 && i%DX < 449 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18130: // 4 cluster (18path) --> 130x130x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 161*DX && i < 291*DX) && (i%DX >= 161 && i%DX < 291 )) || 
				  	((i >= 161*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 439 )) ||
				  	((i >= 309*DX && i < 439*DX) && (i%DX >= 161 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 439*DX) && (i%DX >= 309 && i%DX < 439 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18120: // 4 cluster (18path) --> 120x120x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 171*DX && i < 291*DX) && (i%DX >= 171 && i%DX < 291 )) || 
				  	((i >= 171*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 429 )) ||
				  	((i >= 309*DX && i < 429*DX) && (i%DX >= 171 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 429*DX) && (i%DX >= 309 && i%DX < 429 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18100: // 4 cluster (18path) --> 100x100x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 191*DX && i < 291*DX) && (i%DX >= 191 && i%DX < 291 )) || 
				  	((i >= 191*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 409 )) ||
				  	((i >= 309*DX && i < 409*DX) && (i%DX >= 191 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 409*DX) && (i%DX >= 309 && i%DX < 409 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18080: // 4 cluster (18path) -->  80x 80x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 211*DX && i < 291*DX) && (i%DX >= 211 && i%DX < 291 )) || 
				  	((i >= 211*DX && i < 291*DX) && (i%DX >= 309 && i%DX < 389 )) ||
				  	((i >= 309*DX && i < 389*DX) && (i%DX >= 211 && i%DX < 291 )) ||
				  	((i >= 309*DX && i < 389*DX) && (i%DX >= 309 && i%DX < 389 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 202001: // 20path --> 200x200x4 top left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 180*DX && i < 380*DX) && (i%DX >=   0 && i%DX < 200 )) || 
				  	((i >= 180*DX && i < 380*DX) && (i%DX >= 220 && i%DX < 420 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >=   0 && i%DX < 200 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >= 220 && i%DX < 420 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 202002: // 20path --> 200x200x4 bottom left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  20*DX && i < 220*DX) && (i%DX >=  20 && i%DX < 220 )) || 
				  	((i >=  20*DX && i < 220*DX) && (i%DX >= 240 && i%DX < 440 )) ||
				  	((i >= 240*DX && i < 440*DX) && (i%DX >=  20 && i%DX < 220 )) ||
				  	((i >= 240*DX && i < 440*DX) && (i%DX >= 240 && i%DX < 440 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 201802: // 20path --> 180x180x4 left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  20*DX && i < 200*DX) && (i%DX >=  20 && i%DX < 200 )) || 
				  	((i >=  20*DX && i < 200*DX) && (i%DX >= 220 && i%DX < 400 )) ||
				  	((i >= 220*DX && i < 400*DX) && (i%DX >=  20 && i%DX < 200 )) ||
				  	((i >= 220*DX && i < 400*DX) && (i%DX >= 220 && i%DX < 400 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 20200: // 4 cluster (20path) --> 200x200x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  90*DX && i < 290*DX) && (i%DX >=  90 && i%DX < 290 )) || 
				  	((i >=  90*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 510 )) ||
				  	((i >= 310*DX && i < 510*DX) && (i%DX >=  90 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 510*DX) && (i%DX >= 310 && i%DX < 510 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 20190: // 4 cluster (20path) --> 190x190x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 290*DX) && (i%DX >= 100 && i%DX < 290 )) || 
				  	((i >= 100*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 500 )) ||
				  	((i >= 310*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 500*DX) && (i%DX >= 310 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 20180: // 4 cluster (20path) --> 180x180x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 110*DX && i < 290*DX) && (i%DX >= 110 && i%DX < 290 )) || 
				  	((i >= 110*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 490 )) ||
				  	((i >= 310*DX && i < 490*DX) && (i%DX >= 110 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 490*DX) && (i%DX >= 310 && i%DX < 490 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 20170: // 4 cluster (20path) --> 170x170x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 120*DX && i < 290*DX) && (i%DX >= 120 && i%DX < 290 )) || 
				  	((i >= 120*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 480 )) ||
				  	((i >= 310*DX && i < 480*DX) && (i%DX >= 120 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 480*DX) && (i%DX >= 310 && i%DX < 480 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 20160: // 4 cluster (20path) --> 160x160x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 130*DX && i < 290*DX) && (i%DX >= 130 && i%DX < 290 )) || 
				  	((i >= 130*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 470 )) ||
				  	((i >= 310*DX && i < 470*DX) && (i%DX >= 130 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 470*DX) && (i%DX >= 310 && i%DX < 470 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 20159: // 4 cluster (20path) --> 158x158x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 131*DX && i < 290*DX) && (i%DX >= 131 && i%DX < 290 )) || 
				  	((i >= 131*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 469 )) ||
				  	((i >= 310*DX && i < 469*DX) && (i%DX >= 131 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 469*DX) && (i%DX >= 310 && i%DX < 469 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 20158: // 4 cluster (20path) --> 158x158x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 132*DX && i < 290*DX) && (i%DX >= 132 && i%DX < 290 )) || 
				  	((i >= 132*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 468 )) ||
				  	((i >= 310*DX && i < 468*DX) && (i%DX >= 132 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 468*DX) && (i%DX >= 310 && i%DX < 468 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 20156: // 4 cluster (20path) --> 158x158x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 134*DX && i < 290*DX) && (i%DX >= 134 && i%DX < 290 )) || 
				  	((i >= 134*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 466 )) ||
				  	((i >= 310*DX && i < 466*DX) && (i%DX >= 134 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 466*DX) && (i%DX >= 310 && i%DX < 466 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 20154: // 4 cluster (20path) --> 158x158x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 136*DX && i < 290*DX) && (i%DX >= 136 && i%DX < 290 )) || 
				  	((i >= 136*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 464 )) ||
				  	((i >= 310*DX && i < 464*DX) && (i%DX >= 136 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 464*DX) && (i%DX >= 310 && i%DX < 464 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 20152: // 4 cluster (20path) --> 158x158x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 138*DX && i < 290*DX) && (i%DX >= 138 && i%DX < 290 )) || 
				  	((i >= 138*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 462 )) ||
				  	((i >= 310*DX && i < 462*DX) && (i%DX >= 138 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 462*DX) && (i%DX >= 310 && i%DX < 462 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 20150: // 4 cluster (20path) --> 150x150x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 140*DX && i < 290*DX) && (i%DX >= 140 && i%DX < 290 )) || 
				  	((i >= 140*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 460 )) ||
				  	((i >= 310*DX && i < 460*DX) && (i%DX >= 140 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 460*DX) && (i%DX >= 310 && i%DX < 460 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 20140: // 4 cluster (20path) --> 140x140x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 150*DX && i < 290*DX) && (i%DX >= 150 && i%DX < 290 )) || 
				  	((i >= 150*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 450 )) ||
				  	((i >= 310*DX && i < 450*DX) && (i%DX >= 150 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 450*DX) && (i%DX >= 310 && i%DX < 450 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 20130: // 4 cluster (20path) --> 130x130x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 160*DX && i < 290*DX) && (i%DX >= 160 && i%DX < 290 )) || 
				  	((i >= 160*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 440 )) ||
				  	((i >= 310*DX && i < 440*DX) && (i%DX >= 160 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 440*DX) && (i%DX >= 310 && i%DX < 440 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 20120: // 4 cluster (20path) --> 120x120x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 170*DX && i < 290*DX) && (i%DX >= 170 && i%DX < 290 )) || 
				  	((i >= 170*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 430 )) ||
				  	((i >= 310*DX && i < 430*DX) && (i%DX >= 170 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 430*DX) && (i%DX >= 310 && i%DX < 430 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 20110: // 4 cluster (20path) --> 110x110x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 180*DX && i < 290*DX) && (i%DX >= 180 && i%DX < 290 )) || 
				  	((i >= 180*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 420 )) ||
				  	((i >= 310*DX && i < 420*DX) && (i%DX >= 180 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 420*DX) && (i%DX >= 310 && i%DX < 420 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 20100: // 4 cluster (20path) --> 100x100x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 190*DX && i < 290*DX) && (i%DX >= 190 && i%DX < 290 )) || 
				  	((i >= 190*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 410 )) ||
				  	((i >= 310*DX && i < 410*DX) && (i%DX >= 190 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 410*DX) && (i%DX >= 310 && i%DX < 410 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 222001: // 22path --> 200x200x4 top left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 178*DX && i < 378*DX) && (i%DX >=   0 && i%DX < 200 )) || 
				  	((i >= 178*DX && i < 378*DX) && (i%DX >= 222 && i%DX < 422 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >=   0 && i%DX < 200 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >= 222 && i%DX < 422 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 222002: // 4 cluster (22path) --> 200x200x4 left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  22*DX && i < 222*DX) && (i%DX >=  22 && i%DX < 222 )) || 
				  	((i >=  22*DX && i < 222*DX) && (i%DX >= 244 && i%DX < 444 )) ||
				  	((i >= 244*DX && i < 444*DX) && (i%DX >=  22 && i%DX < 222 )) ||
				  	((i >= 244*DX && i < 444*DX) && (i%DX >= 244 && i%DX < 444 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22200: // 4 cluster (22path) --> 200x200x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  89*DX && i < 289*DX) && (i%DX >=  89 && i%DX < 289 )) || 
				  	((i >=  89*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 511 )) ||
				  	((i >= 311*DX && i < 511*DX) && (i%DX >=  89 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 511*DX) && (i%DX >= 311 && i%DX < 511 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22190: // 4 cluster (22path) --> 190x190x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  99*DX && i < 289*DX) && (i%DX >=  99 && i%DX < 289 )) || 
				  	((i >=  99*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 501 )) ||
				  	((i >= 311*DX && i < 501*DX) && (i%DX >=  99 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 501*DX) && (i%DX >= 311 && i%DX < 501 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22189: // 4 cluster (22path) --> 189x189x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 289*DX) && (i%DX >= 100 && i%DX < 289 )) || 
				  	((i >= 100*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 500 )) ||
				  	((i >= 311*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 500*DX) && (i%DX >= 311 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22180: // 4 cluster (22path) --> 180x180x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 109*DX && i < 289*DX) && (i%DX >= 109 && i%DX < 289 )) || 
				  	((i >= 109*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 491 )) ||
				  	((i >= 311*DX && i < 491*DX) && (i%DX >= 109 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 491*DX) && (i%DX >= 311 && i%DX < 491 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22179: // 4 cluster (22path) --> 179x179x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 110*DX && i < 289*DX) && (i%DX >= 110 && i%DX < 289 )) || 
				  	((i >= 110*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 490 )) ||
				  	((i >= 311*DX && i < 490*DX) && (i%DX >= 110 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 490*DX) && (i%DX >= 311 && i%DX < 490 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22177: // 4 cluster (22path) --> 177x177x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 112*DX && i < 289*DX) && (i%DX >= 112 && i%DX < 289 )) || 
				  	((i >= 112*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 488 )) ||
				  	((i >= 311*DX && i < 488*DX) && (i%DX >= 112 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 488*DX) && (i%DX >= 311 && i%DX < 488 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22175: // 4 cluster (22path) --> 175x175x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 114*DX && i < 289*DX) && (i%DX >= 114 && i%DX < 289 )) || 
				  	((i >= 114*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 486 )) ||
				  	((i >= 311*DX && i < 486*DX) && (i%DX >= 114 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 486*DX) && (i%DX >= 311 && i%DX < 486 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22173: // 4 cluster (22path) --> 173x173x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 116*DX && i < 289*DX) && (i%DX >= 116 && i%DX < 289 )) || 
				  	((i >= 116*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 484 )) ||
				  	((i >= 311*DX && i < 484*DX) && (i%DX >= 116 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 484*DX) && (i%DX >= 311 && i%DX < 484 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22171: // 4 cluster (22path) --> 171x171x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 118*DX && i < 289*DX) && (i%DX >= 118 && i%DX < 289 )) || 
				  	((i >= 118*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 482 )) ||
				  	((i >= 311*DX && i < 482*DX) && (i%DX >= 118 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 482*DX) && (i%DX >= 311 && i%DX < 482 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22178: // 4 cluster (22path) --> 178x178x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 111*DX && i < 289*DX) && (i%DX >= 111 && i%DX < 289 )) || 
				  	((i >= 111*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 489 )) ||
				  	((i >= 311*DX && i < 489*DX) && (i%DX >= 111 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 489*DX) && (i%DX >= 311 && i%DX < 489 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22176: // 4 cluster (22path) --> 176x176x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 113*DX && i < 289*DX) && (i%DX >= 113 && i%DX < 289 )) || 
				  	((i >= 113*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 487 )) ||
				  	((i >= 311*DX && i < 487*DX) && (i%DX >= 113 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 487*DX) && (i%DX >= 311 && i%DX < 487 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22174: // 4 cluster (22path) --> 174x174x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 115*DX && i < 289*DX) && (i%DX >= 115 && i%DX < 289 )) || 
				  	((i >= 115*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 485 )) ||
				  	((i >= 311*DX && i < 485*DX) && (i%DX >= 115 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 485*DX) && (i%DX >= 311 && i%DX < 485 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22172: // 4 cluster (22path) --> 172x172x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 117*DX && i < 289*DX) && (i%DX >= 117 && i%DX < 289 )) || 
				  	((i >= 117*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 483 )) ||
				  	((i >= 311*DX && i < 483*DX) && (i%DX >= 117 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 483*DX) && (i%DX >= 311 && i%DX < 483 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22170: // 4 cluster (22path) --> 170x170x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 119*DX && i < 289*DX) && (i%DX >= 119 && i%DX < 289 )) || 
				  	((i >= 119*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 481 )) ||
				  	((i >= 311*DX && i < 481*DX) && (i%DX >= 119 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 481*DX) && (i%DX >= 311 && i%DX < 481 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22160: // 4 cluster (22path) --> 160x160x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 129*DX && i < 289*DX) && (i%DX >= 129 && i%DX < 289 )) || 
				  	((i >= 129*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 471 )) ||
				  	((i >= 311*DX && i < 471*DX) && (i%DX >= 129 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 471*DX) && (i%DX >= 311 && i%DX < 471 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22150: // 4 cluster (22path) --> 150x150x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 139*DX && i < 289*DX) && (i%DX >= 139 && i%DX < 289 )) || 
				  	((i >= 139*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 461 )) ||
				  	((i >= 311*DX && i < 461*DX) && (i%DX >= 139 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 461*DX) && (i%DX >= 311 && i%DX < 461 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22140: // 4 cluster (22path) --> 140x140x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 149*DX && i < 289*DX) && (i%DX >= 149 && i%DX < 289 )) || 
				  	((i >= 149*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 451 )) ||
				  	((i >= 311*DX && i < 451*DX) && (i%DX >= 149 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 451*DX) && (i%DX >= 311 && i%DX < 451 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22130: // 4 cluster (22path) --> 130x130x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 159*DX && i < 289*DX) && (i%DX >= 159 && i%DX < 289 )) || 
				  	((i >= 159*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 441 )) ||
				  	((i >= 311*DX && i < 441*DX) && (i%DX >= 159 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 441*DX) && (i%DX >= 311 && i%DX < 441 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22120: // 4 cluster (22path) --> 120x120x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 169*DX && i < 289*DX) && (i%DX >= 169 && i%DX < 289 )) || 
				  	((i >= 169*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 431 )) ||
				  	((i >= 311*DX && i < 431*DX) && (i%DX >= 169 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 431*DX) && (i%DX >= 311 && i%DX < 431 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22100: // 4 cluster (22path) --> 100x100x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 189*DX && i < 289*DX) && (i%DX >= 189 && i%DX < 289 )) || 
				  	((i >= 189*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 411 )) ||
				  	((i >= 311*DX && i < 411*DX) && (i%DX >= 189 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 411*DX) && (i%DX >= 311 && i%DX < 411 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22080: // 4 cluster (22path) -->  80x 80x4 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 209*DX && i < 289*DX) && (i%DX >= 209 && i%DX < 289 )) || 
				  	((i >= 209*DX && i < 289*DX) && (i%DX >= 311 && i%DX < 391 )) ||
				  	((i >= 311*DX && i < 391*DX) && (i%DX >= 209 && i%DX < 289 )) ||
				  	((i >= 311*DX && i < 391*DX) && (i%DX >= 311 && i%DX < 391 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 242001: // 24path --> 200x200x4 top left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 176*DX && i < 376*DX) && (i%DX >=   0 && i%DX < 200 )) || 
				  	((i >= 176*DX && i < 376*DX) && (i%DX >= 224 && i%DX < 424 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >=   0 && i%DX < 200 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >= 224 && i%DX < 424 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 242002: // 4 cluster (24path) --> 200x200x4 left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  24*DX && i < 224*DX) && (i%DX >=  24 && i%DX < 224 )) || 
				  	((i >=  24*DX && i < 224*DX) && (i%DX >= 248 && i%DX < 448 )) ||
				  	((i >= 248*DX && i < 448*DX) && (i%DX >=  24 && i%DX < 224 )) ||
				  	((i >= 248*DX && i < 448*DX) && (i%DX >= 248 && i%DX < 448 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24188: // 4 cluster (24path) --> 188x188x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 288*DX) && (i%DX >= 100 && i%DX < 288 )) || 
				  	((i >= 100*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 500 )) ||
				  	((i >= 312*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 500*DX) && (i%DX >= 312 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24180: // 4 cluster (24path) --> 180x180x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 108*DX && i < 288*DX) && (i%DX >= 108 && i%DX < 288 )) || 
				  	((i >= 108*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 492 )) ||
				  	((i >= 312*DX && i < 492*DX) && (i%DX >= 108 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 492*DX) && (i%DX >= 312 && i%DX < 492 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24170: // 4 cluster (24path) --> 170x170x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 118*DX && i < 288*DX) && (i%DX >= 118 && i%DX < 288 )) || 
				  	((i >= 118*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 482 )) ||
				  	((i >= 312*DX && i < 482*DX) && (i%DX >= 118 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 482*DX) && (i%DX >= 312 && i%DX < 482 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24150: // 4 cluster (24path) --> 150x150x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 138*DX && i < 288*DX) && (i%DX >= 138 && i%DX < 288 )) || 
				  	((i >= 138*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 462 )) ||
				  	((i >= 312*DX && i < 462*DX) && (i%DX >= 138 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 462*DX) && (i%DX >= 312 && i%DX < 462 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24160: // 4 cluster (24path) --> 160x160x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 128*DX && i < 288*DX) && (i%DX >= 128 && i%DX < 288 )) || 
				  	((i >= 128*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 472 )) ||
				  	((i >= 312*DX && i < 472*DX) && (i%DX >= 128 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 472*DX) && (i%DX >= 312 && i%DX < 472 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24140: // 4 cluster (24path) --> 140x140x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 148*DX && i < 288*DX) && (i%DX >= 148 && i%DX < 288 )) || 
				  	((i >= 148*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 452 )) ||
				  	((i >= 312*DX && i < 452*DX) && (i%DX >= 148 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 452*DX) && (i%DX >= 312 && i%DX < 452 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24120: // 4 cluster (24path) --> 120x120x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 168*DX && i < 288*DX) && (i%DX >= 168 && i%DX < 288 )) || 
				  	((i >= 168*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 432 )) ||
				  	((i >= 312*DX && i < 432*DX) && (i%DX >= 168 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 432*DX) && (i%DX >= 312 && i%DX < 432 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24100: // 4 cluster (24path) --> 100x100x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 188*DX && i < 288*DX) && (i%DX >= 188 && i%DX < 288 )) || 
				  	((i >= 188*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 412 )) ||
				  	((i >= 312*DX && i < 412*DX) && (i%DX >= 188 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 412*DX) && (i%DX >= 312 && i%DX < 462 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24190: // 4 cluster (24path) --> 190x190x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  98*DX && i < 288*DX) && (i%DX >=  98 && i%DX < 288 )) || 
				  	((i >=  98*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 502 )) ||
				  	((i >= 312*DX && i < 502*DX) && (i%DX >=  98 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 502*DX) && (i%DX >= 312 && i%DX < 502 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24192: // 4 cluster (24path) --> 192x192x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  96*DX && i < 288*DX) && (i%DX >=  96 && i%DX < 288 )) || 
				  	((i >=  96*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 504 )) ||
				  	((i >= 312*DX && i < 504*DX) && (i%DX >=  96 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 504*DX) && (i%DX >= 312 && i%DX < 504 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24193: // 4 cluster (24path) --> 193x193x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  95*DX && i < 288*DX) && (i%DX >=  95 && i%DX < 288 )) || 
				  	((i >=  95*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 505 )) ||
				  	((i >= 312*DX && i < 505*DX) && (i%DX >=  95 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 505*DX) && (i%DX >= 312 && i%DX < 505 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24194: // 4 cluster (24path) --> 194x194x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  94*DX && i < 288*DX) && (i%DX >=  94 && i%DX < 288 )) || 
				  	((i >=  94*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 506 )) ||
				  	((i >= 312*DX && i < 506*DX) && (i%DX >=  94 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 506*DX) && (i%DX >= 312 && i%DX < 506 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24196: // 4 cluster (24path) --> 196x196x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  92*DX && i < 288*DX) && (i%DX >=  92 && i%DX < 288 )) || 
				  	((i >=  92*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 508 )) ||
				  	((i >= 312*DX && i < 508*DX) && (i%DX >=  92 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 508*DX) && (i%DX >= 312 && i%DX < 508 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24198: // 4 cluster (24path) --> 198x198x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  90*DX && i < 288*DX) && (i%DX >=  90 && i%DX < 288 )) || 
				  	((i >=  90*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 510 )) ||
				  	((i >= 312*DX && i < 510*DX) && (i%DX >=  90 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 510*DX) && (i%DX >= 312 && i%DX < 510 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24200: // 4 cluster (24path) --> 200x200x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  88*DX && i < 288*DX) && (i%DX >=  88 && i%DX < 288 )) || 
				  	((i >=  88*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 512 )) ||
				  	((i >= 312*DX && i < 512*DX) && (i%DX >=  88 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 512*DX) && (i%DX >= 312 && i%DX < 512 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24210: // 4 cluster (24path) --> 210x210x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  78*DX && i < 288*DX) && (i%DX >=  78 && i%DX < 288 )) || 
				  	((i >=  78*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 522 )) ||
				  	((i >= 312*DX && i < 522*DX) && (i%DX >=  78 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 522*DX) && (i%DX >= 312 && i%DX < 522 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24220: // 4 cluster (24path) --> 220x220x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  68*DX && i < 288*DX) && (i%DX >=  68 && i%DX < 288 )) || 
				  	((i >=  68*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 532 )) ||
				  	((i >= 312*DX && i < 532*DX) && (i%DX >=  68 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 532*DX) && (i%DX >= 312 && i%DX < 532 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24230: // 4 cluster (24path) --> 220x220x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  58*DX && i < 288*DX) && (i%DX >=  58 && i%DX < 288 )) || 
				  	((i >=  58*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 542 )) ||
				  	((i >= 312*DX && i < 542*DX) && (i%DX >=  58 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 542*DX) && (i%DX >= 312 && i%DX < 542 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24238: // 4 cluster (24path) --> 238x238x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  50*DX && i < 288*DX) && (i%DX >=  50 && i%DX < 288 )) || 
				  	((i >=  50*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 550 )) ||
				  	((i >= 312*DX && i < 550*DX) && (i%DX >=  50 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 550*DX) && (i%DX >= 312 && i%DX < 550 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 262001: // 26path --> 200x200x4 top left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 174*DX && i < 374*DX) && (i%DX >=   0 && i%DX < 200 )) || 
				  	((i >= 174*DX && i < 374*DX) && (i%DX >= 226 && i%DX < 426 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >=   0 && i%DX < 200 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >= 226 && i%DX < 426 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 262002: // 4 cluster (26path) --> 200x200x4 left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  26*DX && i < 226*DX) && (i%DX >=  26 && i%DX < 226 )) || 
				  	((i >=  26*DX && i < 226*DX) && (i%DX >= 252 && i%DX < 452 )) ||
				  	((i >= 252*DX && i < 452*DX) && (i%DX >=  26 && i%DX < 226 )) ||
				  	((i >= 252*DX && i < 452*DX) && (i%DX >= 252 && i%DX < 452 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 26187: // 4 cluster (26path) --> 187x187x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 287*DX) && (i%DX >= 100 && i%DX < 287 )) || 
				  	((i >= 100*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 500 )) ||
				  	((i >= 313*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 500*DX) && (i%DX >= 313 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 26180: // 4 cluster (26path) --> 180x180x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 107*DX && i < 287*DX) && (i%DX >= 107 && i%DX < 287 )) || 
				  	((i >= 107*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 493 )) ||
				  	((i >= 313*DX && i < 493*DX) && (i%DX >= 107 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 493*DX) && (i%DX >= 313 && i%DX < 493 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 26170: // 4 cluster (26path) --> 170x170x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 117*DX && i < 287*DX) && (i%DX >= 117 && i%DX < 287 )) || 
				  	((i >= 117*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 483 )) ||
				  	((i >= 313*DX && i < 483*DX) && (i%DX >= 117 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 483*DX) && (i%DX >= 313 && i%DX < 483 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 26160: // 4 cluster (26path) --> 160x160x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 127*DX && i < 287*DX) && (i%DX >= 127 && i%DX < 287 )) || 
				  	((i >= 127*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 473 )) ||
				  	((i >= 313*DX && i < 473*DX) && (i%DX >= 127 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 473*DX) && (i%DX >= 313 && i%DX < 473 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 26140: // 4 cluster (26path) --> 140x140x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 147*DX && i < 287*DX) && (i%DX >= 147 && i%DX < 287 )) || 
				  	((i >= 147*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 453 )) ||
				  	((i >= 313*DX && i < 453*DX) && (i%DX >= 147 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 453*DX) && (i%DX >= 313 && i%DX < 453 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 26120: // 4 cluster (26path) --> 120x120x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 167*DX && i < 287*DX) && (i%DX >= 167 && i%DX < 287 )) || 
				  	((i >= 167*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 433 )) ||
				  	((i >= 313*DX && i < 433*DX) && (i%DX >= 167 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 433*DX) && (i%DX >= 313 && i%DX < 433 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 26100: // 4 cluster (26path) --> 100x100x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 187*DX && i < 287*DX) && (i%DX >= 187 && i%DX < 287 )) || 
				  	((i >= 187*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 413 )) ||
				  	((i >= 313*DX && i < 413*DX) && (i%DX >= 187 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 413*DX) && (i%DX >= 313 && i%DX < 413 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 26190: // 4 cluster (26path) --> 190x190x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  97*DX && i < 287*DX) && (i%DX >=  97 && i%DX < 287 )) || 
				  	((i >=  97*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 503 )) ||
				  	((i >= 313*DX && i < 503*DX) && (i%DX >=  97 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 503*DX) && (i%DX >= 313 && i%DX < 503 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 26200: // 4 cluster (26path) --> 200x200x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  87*DX && i < 287*DX) && (i%DX >=  87 && i%DX < 287 )) || 
				  	((i >=  87*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 513 )) ||
				  	((i >= 313*DX && i < 513*DX) && (i%DX >=  87 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 513*DX) && (i%DX >= 313 && i%DX < 513 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 26210: // 4 cluster (26path) --> 210x210x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  77*DX && i < 287*DX) && (i%DX >=  77 && i%DX < 287 )) || 
				  	((i >=  77*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 523 )) ||
				  	((i >= 313*DX && i < 523*DX) && (i%DX >=  77 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 523*DX) && (i%DX >= 313 && i%DX < 523 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 26220: // 4 cluster (26path) --> 220x220x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  67*DX && i < 287*DX) && (i%DX >=  67 && i%DX < 287 )) || 
				  	((i >=  67*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 533 )) ||
				  	((i >= 313*DX && i < 533*DX) && (i%DX >=  67 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 533*DX) && (i%DX >= 313 && i%DX < 533 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 26222: // 4 cluster (26path) --> 222x222x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  65*DX && i < 287*DX) && (i%DX >=  65 && i%DX < 287 )) || 
				  	((i >=  65*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 535 )) ||
				  	((i >= 313*DX && i < 535*DX) && (i%DX >=  65 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 535*DX) && (i%DX >= 313 && i%DX < 535 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 26223: // 4 cluster (26path) --> 223x223x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  64*DX && i < 287*DX) && (i%DX >=  64 && i%DX < 287 )) || 
				  	((i >=  64*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 536 )) ||
				  	((i >= 313*DX && i < 536*DX) && (i%DX >=  64 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 536*DX) && (i%DX >= 313 && i%DX < 536 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 26224: // 4 cluster (26path) --> 224x224x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  63*DX && i < 287*DX) && (i%DX >=  63 && i%DX < 287 )) || 
				  	((i >=  63*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 537 )) ||
				  	((i >= 313*DX && i < 537*DX) && (i%DX >=  63 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 537*DX) && (i%DX >= 313 && i%DX < 537 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 26226: // 4 cluster (26path) --> 226x226x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  61*DX && i < 287*DX) && (i%DX >=  61 && i%DX < 287 )) || 
				  	((i >=  61*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 539 )) ||
				  	((i >= 313*DX && i < 539*DX) && (i%DX >=  61 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 539*DX) && (i%DX >= 313 && i%DX < 539 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 26228: // 4 cluster (26path) --> 228x228x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  59*DX && i < 287*DX) && (i%DX >=  59 && i%DX < 287 )) || 
				  	((i >=  59*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 541 )) ||
				  	((i >= 313*DX && i < 541*DX) && (i%DX >=  59 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 541*DX) && (i%DX >= 313 && i%DX < 541 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 26230: // 4 cluster (26path) --> 230x230x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  57*DX && i < 287*DX) && (i%DX >=  57 && i%DX < 287 )) || 
				  	((i >=  57*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 543 )) ||
				  	((i >= 313*DX && i < 543*DX) && (i%DX >=  57 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 543*DX) && (i%DX >= 313 && i%DX < 543 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 26237: // 4 cluster (26path) --> 237x237x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  50*DX && i < 287*DX) && (i%DX >=  50 && i%DX < 287 )) || 
				  	((i >=  50*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 550 )) ||
				  	((i >= 313*DX && i < 550*DX) && (i%DX >=  50 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 550*DX) && (i%DX >= 313 && i%DX < 550 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 282001: // 28path --> 200x200x4 top left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 172*DX && i < 372*DX) && (i%DX >=   0 && i%DX < 200 )) || 
				  	((i >= 172*DX && i < 372*DX) && (i%DX >= 228 && i%DX < 428 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >=   0 && i%DX < 200 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >= 228 && i%DX < 428 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 282002: // 4 cluster (28path) --> 200x200x4 left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  28*DX && i < 228*DX) && (i%DX >=  28 && i%DX < 228 )) || 
				  	((i >=  28*DX && i < 228*DX) && (i%DX >= 256 && i%DX < 456 )) ||
				  	((i >= 256*DX && i < 456*DX) && (i%DX >=  28 && i%DX < 228 )) ||
				  	((i >= 256*DX && i < 456*DX) && (i%DX >= 256 && i%DX < 456 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 28186: // 4 cluster (28path) --> 186x186x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 286*DX) && (i%DX >= 100 && i%DX < 286 )) || 
				  	((i >= 100*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 500 )) ||
				  	((i >= 314*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 500*DX) && (i%DX >= 314 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 28180: // 4 cluster (28path) --> 180x180x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 106*DX && i < 286*DX) && (i%DX >= 106 && i%DX < 286 )) || 
				  	((i >= 106*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 494 )) ||
				  	((i >= 314*DX && i < 494*DX) && (i%DX >= 106 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 494*DX) && (i%DX >= 314 && i%DX < 494 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 28170: // 4 cluster (28path) --> 170x170x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 116*DX && i < 286*DX) && (i%DX >= 116 && i%DX < 286 )) || 
				  	((i >= 116*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 484 )) ||
				  	((i >= 314*DX && i < 484*DX) && (i%DX >= 116 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 484*DX) && (i%DX >= 314 && i%DX < 484 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 28160: // 4 cluster (28path) --> 160x160x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 126*DX && i < 286*DX) && (i%DX >= 126 && i%DX < 286 )) || 
				  	((i >= 126*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 474 )) ||
				  	((i >= 314*DX && i < 474*DX) && (i%DX >= 126 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 474*DX) && (i%DX >= 314 && i%DX < 474 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 28140: // 4 cluster (28path) --> 140x140x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 146*DX && i < 286*DX) && (i%DX >= 146 && i%DX < 286 )) || 
				  	((i >= 146*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 454 )) ||
				  	((i >= 314*DX && i < 454*DX) && (i%DX >= 146 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 454*DX) && (i%DX >= 314 && i%DX < 454 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 28120: // 4 cluster (28path) --> 120x120x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 166*DX && i < 286*DX) && (i%DX >= 166 && i%DX < 286 )) || 
				  	((i >= 166*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 434 )) ||
				  	((i >= 314*DX && i < 434*DX) && (i%DX >= 166 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 434*DX) && (i%DX >= 314 && i%DX < 434 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 28100: // 4 cluster (28path) --> 100x100x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 186*DX && i < 286*DX) && (i%DX >= 186 && i%DX < 286 )) || 
				  	((i >= 186*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 414 )) ||
				  	((i >= 314*DX && i < 414*DX) && (i%DX >= 186 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 414*DX) && (i%DX >= 314 && i%DX < 414 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 28190: // 4 cluster (28path) --> 190x190x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  96*DX && i < 286*DX) && (i%DX >=  96 && i%DX < 286 )) || 
				  	((i >=  96*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 504 )) ||
				  	((i >= 314*DX && i < 504*DX) && (i%DX >=  96 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 504*DX) && (i%DX >= 314 && i%DX < 504 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 28200: // 4 cluster (28path) --> 200x200x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  86*DX && i < 286*DX) && (i%DX >=  86 && i%DX < 286 )) || 
				  	((i >=  86*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 514 )) ||
				  	((i >= 314*DX && i < 514*DX) && (i%DX >=  86 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 514*DX) && (i%DX >= 314 && i%DX < 514 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 28210: // 4 cluster (28path) --> 210x210x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  76*DX && i < 286*DX) && (i%DX >=  76 && i%DX < 286 )) || 
				  	((i >=  76*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 524 )) ||
				  	((i >= 314*DX && i < 524*DX) && (i%DX >=  76 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 524*DX) && (i%DX >= 314 && i%DX < 524 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 28220: // 4 cluster (28path) --> 220x220x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  66*DX && i < 286*DX) && (i%DX >=  66 && i%DX < 286 )) || 
				  	((i >=  66*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 534 )) ||
				  	((i >= 314*DX && i < 534*DX) && (i%DX >=  66 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 534*DX) && (i%DX >= 314 && i%DX < 534 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 28230: // 4 cluster (28path) --> 230x230x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  56*DX && i < 286*DX) && (i%DX >=  56 && i%DX < 286 )) || 
				  	((i >=  56*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 544 )) ||
				  	((i >= 314*DX && i < 544*DX) && (i%DX >=  56 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 544*DX) && (i%DX >= 314 && i%DX < 544 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 28231: // 4 cluster (28path) --> 231x231x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  55*DX && i < 286*DX) && (i%DX >=  55 && i%DX < 286 )) || 
				  	((i >=  55*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 545 )) ||
				  	((i >= 314*DX && i < 545*DX) && (i%DX >=  55 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 545*DX) && (i%DX >= 314 && i%DX < 545 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 28232: // 4 cluster (28path) --> 232x232x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  54*DX && i < 286*DX) && (i%DX >=  54 && i%DX < 286 )) || 
				  	((i >=  54*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 546 )) ||
				  	((i >= 314*DX && i < 546*DX) && (i%DX >=  54 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 546*DX) && (i%DX >= 314 && i%DX < 546 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 28233: // 4 cluster (28path) --> 233x233x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  53*DX && i < 286*DX) && (i%DX >=  53 && i%DX < 286 )) || 
				  	((i >=  53*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 547 )) ||
				  	((i >= 314*DX && i < 547*DX) && (i%DX >=  53 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 547*DX) && (i%DX >= 314 && i%DX < 547 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 28234: // 4 cluster (28path) --> 234x234x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  52*DX && i < 286*DX) && (i%DX >=  52 && i%DX < 286 )) || 
				  	((i >=  52*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 548 )) ||
				  	((i >= 314*DX && i < 548*DX) && (i%DX >=  52 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 548*DX) && (i%DX >= 314 && i%DX < 548 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 28235: // 4 cluster (28path) --> 235x235x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  51*DX && i < 286*DX) && (i%DX >=  51 && i%DX < 286 )) || 
				  	((i >=  51*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 549 )) ||
				  	((i >= 314*DX && i < 549*DX) && (i%DX >=  51 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 549*DX) && (i%DX >= 314 && i%DX < 549 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 28236: // 4 cluster (28path) --> 236x236x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  50*DX && i < 286*DX) && (i%DX >=  50 && i%DX < 286 )) || 
				  	((i >=  50*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 550 )) ||
				  	((i >= 314*DX && i < 550*DX) && (i%DX >=  50 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 550*DX) && (i%DX >= 314 && i%DX < 550 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 302001: // 30path --> 200x200x4 top left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 170*DX && i < 370*DX) && (i%DX >=   0 && i%DX < 200 )) || 
				  	((i >= 170*DX && i < 370*DX) && (i%DX >= 230 && i%DX < 430 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >=   0 && i%DX < 200 )) ||
				  	((i >= 400*DX && i < 600*DX) && (i%DX >= 230 && i%DX < 430 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 302002: // 4 cluster (30path) --> 200x200x4 left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  30*DX && i < 230*DX) && (i%DX >=  30 && i%DX < 230 )) || 
				  	((i >=  30*DX && i < 230*DX) && (i%DX >= 270 && i%DX < 470 )) ||
				  	((i >= 270*DX && i < 470*DX) && (i%DX >=  30 && i%DX < 230 )) ||
				  	((i >= 270*DX && i < 470*DX) && (i%DX >= 270 && i%DX < 470 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 30185: // 4 cluster (30path) --> 185x185x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 285*DX) && (i%DX >= 100 && i%DX < 285 )) || 
				  	((i >= 100*DX && i < 285*DX) && (i%DX >= 315 && i%DX < 500 )) ||
				  	((i >= 315*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 285 )) ||
				  	((i >= 315*DX && i < 500*DX) && (i%DX >= 315 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 30180: // 4 cluster (30path) --> 180x180x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 105*DX && i < 285*DX) && (i%DX >= 105 && i%DX < 285 )) || 
				  	((i >= 105*DX && i < 285*DX) && (i%DX >= 315 && i%DX < 495 )) ||
				  	((i >= 315*DX && i < 495*DX) && (i%DX >= 105 && i%DX < 285 )) ||
				  	((i >= 315*DX && i < 495*DX) && (i%DX >= 315 && i%DX < 495 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 30170: // 4 cluster (30path) --> 170x170x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 115*DX && i < 285*DX) && (i%DX >= 115 && i%DX < 285 )) || 
				  	((i >= 115*DX && i < 285*DX) && (i%DX >= 315 && i%DX < 485 )) ||
				  	((i >= 315*DX && i < 485*DX) && (i%DX >= 115 && i%DX < 285 )) ||
				  	((i >= 315*DX && i < 485*DX) && (i%DX >= 315 && i%DX < 485 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 30160: // 4 cluster (30path) --> 160x160x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 125*DX && i < 285*DX) && (i%DX >= 125 && i%DX < 285 )) || 
				  	((i >= 125*DX && i < 285*DX) && (i%DX >= 315 && i%DX < 475 )) ||
				  	((i >= 315*DX && i < 475*DX) && (i%DX >= 125 && i%DX < 285 )) ||
				  	((i >= 315*DX && i < 475*DX) && (i%DX >= 315 && i%DX < 475 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 30140: // 4 cluster (30path) --> 140x140x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 145*DX && i < 285*DX) && (i%DX >= 145 && i%DX < 285 )) || 
				  	((i >= 145*DX && i < 285*DX) && (i%DX >= 315 && i%DX < 455 )) ||
				  	((i >= 315*DX && i < 455*DX) && (i%DX >= 145 && i%DX < 285 )) ||
				  	((i >= 315*DX && i < 455*DX) && (i%DX >= 315 && i%DX < 455 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 30120: // 4 cluster (30path) --> 120x120x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 165*DX && i < 285*DX) && (i%DX >= 165 && i%DX < 285 )) || 
				  	((i >= 165*DX && i < 285*DX) && (i%DX >= 315 && i%DX < 435 )) ||
				  	((i >= 315*DX && i < 435*DX) && (i%DX >= 165 && i%DX < 285 )) ||
				  	((i >= 315*DX && i < 435*DX) && (i%DX >= 315 && i%DX < 435 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 30100: // 4 cluster (30path) --> 100x100x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 185*DX && i < 285*DX) && (i%DX >= 185 && i%DX < 285 )) || 
				  	((i >= 185*DX && i < 285*DX) && (i%DX >= 315 && i%DX < 415 )) ||
				  	((i >= 315*DX && i < 415*DX) && (i%DX >= 185 && i%DX < 285 )) ||
				  	((i >= 315*DX && i < 415*DX) && (i%DX >= 315 && i%DX < 415 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 30190: // 4 cluster (30path) --> 190x190x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  95*DX && i < 285*DX) && (i%DX >=  95 && i%DX < 285 )) || 
				  	((i >=  95*DX && i < 285*DX) && (i%DX >= 315 && i%DX < 505 )) ||
				  	((i >= 315*DX && i < 505*DX) && (i%DX >=  95 && i%DX < 285 )) ||
				  	((i >= 315*DX && i < 505*DX) && (i%DX >= 315 && i%DX < 505 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 30200: // 4 cluster (30path) --> 200x200x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  85*DX && i < 285*DX) && (i%DX >=  85 && i%DX < 285 )) || 
				  	((i >=  85*DX && i < 285*DX) && (i%DX >= 315 && i%DX < 515 )) ||
				  	((i >= 315*DX && i < 515*DX) && (i%DX >=  85 && i%DX < 285 )) ||
				  	((i >= 315*DX && i < 515*DX) && (i%DX >= 315 && i%DX < 515 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 30210: // 4 cluster (30path) --> 210x210x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  75*DX && i < 285*DX) && (i%DX >=  75 && i%DX < 285 )) || 
				  	((i >=  75*DX && i < 285*DX) && (i%DX >= 315 && i%DX < 525 )) ||
				  	((i >= 315*DX && i < 525*DX) && (i%DX >=  75 && i%DX < 285 )) ||
				  	((i >= 315*DX && i < 525*DX) && (i%DX >= 315 && i%DX < 525 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 30220: // 4 cluster (30path) --> 220x220x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  65*DX && i < 285*DX) && (i%DX >=  65 && i%DX < 285 )) || 
				  	((i >=  65*DX && i < 285*DX) && (i%DX >= 315 && i%DX < 535 )) ||
				  	((i >= 315*DX && i < 535*DX) && (i%DX >=  65 && i%DX < 285 )) ||
				  	((i >= 315*DX && i < 535*DX) && (i%DX >= 315 && i%DX < 535 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 30230: // 4 cluster (30path) --> 230x230x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  55*DX && i < 285*DX) && (i%DX >=  55 && i%DX < 285 )) || 
				  	((i >=  55*DX && i < 285*DX) && (i%DX >= 315 && i%DX < 545 )) ||
				  	((i >= 315*DX && i < 545*DX) && (i%DX >=  55 && i%DX < 285 )) ||
				  	((i >= 315*DX && i < 545*DX) && (i%DX >= 315 && i%DX < 545 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 30235: // 4 cluster (30path) --> 235x235x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  50*DX && i < 285*DX) && (i%DX >=  50 && i%DX < 285 )) || 
				  	((i >=  50*DX && i < 285*DX) && (i%DX >= 315 && i%DX < 550 )) ||
				  	((i >= 315*DX && i < 550*DX) && (i%DX >=  50 && i%DX < 285 )) ||
				  	((i >= 315*DX && i < 550*DX) && (i%DX >= 315 && i%DX < 550 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 322002: // 4 cluster (32path) --> 200x200x4 bottom left corner
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  32*DX && i < 232*DX) && (i%DX >=  32 && i%DX < 232 )) || 
				  	((i >=  32*DX && i < 232*DX) && (i%DX >= 264 && i%DX < 464 )) ||
				  	((i >= 264*DX && i < 464*DX) && (i%DX >=  32 && i%DX < 232 )) ||
				  	((i >= 264*DX && i < 464*DX) && (i%DX >= 264 && i%DX < 464 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 32184: // 4 cluster (32path) --> 184x184x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 284*DX) && (i%DX >= 100 && i%DX < 284 )) || 
				  	((i >= 100*DX && i < 284*DX) && (i%DX >= 316 && i%DX < 500 )) ||
				  	((i >= 316*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 284 )) ||
				  	((i >= 316*DX && i < 500*DX) && (i%DX >= 316 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 32180: // 4 cluster (32path) --> 180x180x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 104*DX && i < 284*DX) && (i%DX >= 104 && i%DX < 284 )) || 
				  	((i >= 104*DX && i < 284*DX) && (i%DX >= 316 && i%DX < 496 )) ||
				  	((i >= 316*DX && i < 496*DX) && (i%DX >= 104 && i%DX < 284 )) ||
				  	((i >= 316*DX && i < 496*DX) && (i%DX >= 316 && i%DX < 496 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 32170: // 4 cluster (32path) --> 160x160x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 114*DX && i < 284*DX) && (i%DX >= 114 && i%DX < 284 )) || 
				  	((i >= 114*DX && i < 284*DX) && (i%DX >= 316 && i%DX < 486 )) ||
				  	((i >= 316*DX && i < 486*DX) && (i%DX >= 114 && i%DX < 284 )) ||
				  	((i >= 316*DX && i < 486*DX) && (i%DX >= 316 && i%DX < 486 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 32160: // 4 cluster (32path) --> 160x160x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 124*DX && i < 284*DX) && (i%DX >= 124 && i%DX < 284 )) || 
				  	((i >= 124*DX && i < 284*DX) && (i%DX >= 316 && i%DX < 476 )) ||
				  	((i >= 316*DX && i < 476*DX) && (i%DX >= 124 && i%DX < 284 )) ||
				  	((i >= 316*DX && i < 476*DX) && (i%DX >= 316 && i%DX < 476 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 32140: // 4 cluster (32path) --> 140x140x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 144*DX && i < 284*DX) && (i%DX >= 144 && i%DX < 284 )) || 
				  	((i >= 144*DX && i < 284*DX) && (i%DX >= 316 && i%DX < 456 )) ||
				  	((i >= 316*DX && i < 456*DX) && (i%DX >= 144 && i%DX < 284 )) ||
				  	((i >= 316*DX && i < 456*DX) && (i%DX >= 316 && i%DX < 456 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 32120: // 4 cluster (32path) --> 120x120x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 164*DX && i < 284*DX) && (i%DX >= 164 && i%DX < 284 )) || 
				  	((i >= 164*DX && i < 284*DX) && (i%DX >= 316 && i%DX < 436 )) ||
				  	((i >= 316*DX && i < 436*DX) && (i%DX >= 164 && i%DX < 284 )) ||
				  	((i >= 316*DX && i < 436*DX) && (i%DX >= 316 && i%DX < 436 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 32100: // 4 cluster (32path) --> 100x100x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 184*DX && i < 284*DX) && (i%DX >= 184 && i%DX < 284 )) || 
				  	((i >= 184*DX && i < 284*DX) && (i%DX >= 316 && i%DX < 416 )) ||
				  	((i >= 316*DX && i < 416*DX) && (i%DX >= 184 && i%DX < 284 )) ||
				  	((i >= 316*DX && i < 416*DX) && (i%DX >= 316 && i%DX < 416 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 32190: // 4 cluster (32path) --> 190x190x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  94*DX && i < 284*DX) && (i%DX >=  94 && i%DX < 284 )) || 
				  	((i >=  94*DX && i < 284*DX) && (i%DX >= 316 && i%DX < 506 )) ||
				  	((i >= 316*DX && i < 506*DX) && (i%DX >=  94 && i%DX < 284 )) ||
				  	((i >= 316*DX && i < 506*DX) && (i%DX >= 316 && i%DX < 506 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 32200: // 4 cluster (32path) --> 200x200x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  84*DX && i < 284*DX) && (i%DX >=  84 && i%DX < 284 )) || 
				  	((i >=  84*DX && i < 284*DX) && (i%DX >= 316 && i%DX < 516 )) ||
				  	((i >= 316*DX && i < 516*DX) && (i%DX >=  84 && i%DX < 284 )) ||
				  	((i >= 316*DX && i < 516*DX) && (i%DX >= 316 && i%DX < 516 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 32210: // 4 cluster (32path) --> 210x210x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  74*DX && i < 284*DX) && (i%DX >=  74 && i%DX < 284 )) || 
				  	((i >=  74*DX && i < 284*DX) && (i%DX >= 316 && i%DX < 526 )) ||
				  	((i >= 316*DX && i < 526*DX) && (i%DX >=  74 && i%DX < 284 )) ||
				  	((i >= 316*DX && i < 526*DX) && (i%DX >= 316 && i%DX < 526 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 32220: // 4 cluster (32path) --> 220x220x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  64*DX && i < 284*DX) && (i%DX >=  64 && i%DX < 284 )) || 
				  	((i >=  64*DX && i < 284*DX) && (i%DX >= 316 && i%DX < 536 )) ||
				  	((i >= 316*DX && i < 536*DX) && (i%DX >=  64 && i%DX < 284 )) ||
				  	((i >= 316*DX && i < 536*DX) && (i%DX >= 316 && i%DX < 536 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 32230: // 4 cluster (32path) --> 230x230x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  54*DX && i < 284*DX) && (i%DX >=  54 && i%DX < 284 )) || 
				  	((i >=  54*DX && i < 284*DX) && (i%DX >= 316 && i%DX < 546 )) ||
				  	((i >= 316*DX && i < 546*DX) && (i%DX >=  54 && i%DX < 284 )) ||
				  	((i >= 316*DX && i < 546*DX) && (i%DX >= 316 && i%DX < 546 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 32234: // 4 cluster (32path) --> 234x234x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  50*DX && i < 284*DX) && (i%DX >=  50 && i%DX < 284 )) || 
				  	((i >=  50*DX && i < 284*DX) && (i%DX >= 316 && i%DX < 550 )) ||
				  	((i >= 316*DX && i < 550*DX) && (i%DX >=  50 && i%DX < 284 )) ||
				  	((i >= 316*DX && i < 550*DX) && (i%DX >= 316 && i%DX < 550 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 34: // 4 cluster (34path)
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 283*DX) && (i%DX >= 100 && i%DX < 283 )) || 
				  	((i >= 100*DX && i < 283*DX) && (i%DX >= 317 && i%DX < 500 )) ||
				  	((i >= 317*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 283 )) ||
				  	((i >= 317*DX && i < 500*DX) && (i%DX >= 317 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 36: // 4 cluster (36path)
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 282*DX) && (i%DX >= 100 && i%DX < 282 )) || 
				  	((i >= 100*DX && i < 282*DX) && (i%DX >= 318 && i%DX < 500 )) ||
				  	((i >= 318*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 282 )) ||
				  	((i >= 318*DX && i < 500*DX) && (i%DX >= 318 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 38: // 4 cluster (38path)
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 281*DX) && (i%DX >= 100 && i%DX < 281 )) || 
				  	((i >= 100*DX && i < 281*DX) && (i%DX >= 319 && i%DX < 500 )) ||
				  	((i >= 319*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 281 )) ||
				  	((i >= 319*DX && i < 500*DX) && (i%DX >= 319 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 40100: // 4 cluster (40path) --> 100x100x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 180*DX && i < 280*DX) && (i%DX >= 180 && i%DX < 280 )) || 
				  	((i >= 180*DX && i < 280*DX) && (i%DX >= 320 && i%DX < 420 )) ||
				  	((i >= 320*DX && i < 420*DX) && (i%DX >= 180 && i%DX < 280 )) ||
				  	((i >= 320*DX && i < 420*DX) && (i%DX >= 320 && i%DX < 420 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 40120: // 4 cluster (40path) --> 120x120x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 160*DX && i < 280*DX) && (i%DX >= 160 && i%DX < 280 )) || 
				  	((i >= 160*DX && i < 280*DX) && (i%DX >= 320 && i%DX < 440 )) ||
				  	((i >= 320*DX && i < 440*DX) && (i%DX >= 160 && i%DX < 280 )) ||
				  	((i >= 320*DX && i < 440*DX) && (i%DX >= 320 && i%DX < 440 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 40140: // 4 cluster (40path) --> 140x140x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 140*DX && i < 280*DX) && (i%DX >= 140 && i%DX < 280 )) || 
				  	((i >= 140*DX && i < 280*DX) && (i%DX >= 320 && i%DX < 460 )) ||
				  	((i >= 320*DX && i < 460*DX) && (i%DX >= 140 && i%DX < 280 )) ||
				  	((i >= 320*DX && i < 460*DX) && (i%DX >= 320 && i%DX < 460 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 40160: // 4 cluster (40path) --> 160x160x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 120*DX && i < 280*DX) && (i%DX >= 120 && i%DX < 280 )) || 
				  	((i >= 120*DX && i < 280*DX) && (i%DX >= 320 && i%DX < 480 )) ||
				  	((i >= 320*DX && i < 480*DX) && (i%DX >= 120 && i%DX < 280 )) ||
				  	((i >= 320*DX && i < 480*DX) && (i%DX >= 320 && i%DX < 480 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 40170: // 4 cluster (40path) --> 170x170x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 110*DX && i < 280*DX) && (i%DX >= 110 && i%DX < 280 )) || 
				  	((i >= 110*DX && i < 280*DX) && (i%DX >= 320 && i%DX < 490 )) ||
				  	((i >= 320*DX && i < 490*DX) && (i%DX >= 110 && i%DX < 280 )) ||
				  	((i >= 320*DX && i < 490*DX) && (i%DX >= 320 && i%DX < 490 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 40180: // 4 cluster (40path) --> 180x180x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 280*DX) && (i%DX >= 100 && i%DX < 280 )) || 
				  	((i >= 100*DX && i < 280*DX) && (i%DX >= 320 && i%DX < 500 )) ||
				  	((i >= 320*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 280 )) ||
				  	((i >= 320*DX && i < 500*DX) && (i%DX >= 320 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 40190: // 4 cluster (40path) --> 190x190x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  90*DX && i < 280*DX) && (i%DX >=  90 && i%DX < 280 )) || 
				  	((i >=  90*DX && i < 280*DX) && (i%DX >= 320 && i%DX < 510 )) ||
				  	((i >= 320*DX && i < 510*DX) && (i%DX >=  90 && i%DX < 280 )) ||
				  	((i >= 320*DX && i < 510*DX) && (i%DX >= 320 && i%DX < 510 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 40200: // 4 cluster (40path) --> 200x200x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  80*DX && i < 280*DX) && (i%DX >=  80 && i%DX < 280 )) || 
				  	((i >=  80*DX && i < 280*DX) && (i%DX >= 320 && i%DX < 520 )) ||
				  	((i >= 320*DX && i < 520*DX) && (i%DX >=  80 && i%DX < 280 )) ||
				  	((i >= 320*DX && i < 520*DX) && (i%DX >= 320 && i%DX < 520 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 40210: // 4 cluster (40path) --> 210x210x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  70*DX && i < 280*DX) && (i%DX >=  70 && i%DX < 280 )) || 
				  	((i >=  70*DX && i < 280*DX) && (i%DX >= 320 && i%DX < 530 )) ||
				  	((i >= 320*DX && i < 530*DX) && (i%DX >=  70 && i%DX < 280 )) ||
				  	((i >= 320*DX && i < 530*DX) && (i%DX >= 320 && i%DX < 530 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 40220: // 4 cluster (40path) --> 220x220x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  60*DX && i < 280*DX) && (i%DX >=  60 && i%DX < 280 )) || 
				  	((i >=  60*DX && i < 280*DX) && (i%DX >= 320 && i%DX < 540 )) ||
				  	((i >= 320*DX && i < 540*DX) && (i%DX >=  60 && i%DX < 280 )) ||
				  	((i >= 320*DX && i < 540*DX) && (i%DX >= 320 && i%DX < 540 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 40230: // 4 cluster (40path) --> 230x230x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  50*DX && i < 280*DX) && (i%DX >=  50 && i%DX < 280 )) || 
				  	((i >=  50*DX && i < 280*DX) && (i%DX >= 320 && i%DX < 550 )) ||
				  	((i >= 320*DX && i < 550*DX) && (i%DX >=  50 && i%DX < 280 )) ||
				  	((i >= 320*DX && i < 550*DX) && (i%DX >= 320 && i%DX < 550 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 42: // 4 cluster (42path)
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 279*DX) && (i%DX >= 100 && i%DX < 279 )) || 
				  	((i >= 100*DX && i < 279*DX) && (i%DX >= 321 && i%DX < 500 )) ||
				  	((i >= 321*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 279 )) ||
				  	((i >= 321*DX && i < 500*DX) && (i%DX >= 321 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 44: // 4 cluster (44path)
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 278*DX) && (i%DX >= 100 && i%DX < 278 )) || 
				  	((i >= 100*DX && i < 278*DX) && (i%DX >= 322 && i%DX < 500 )) ||
				  	((i >= 322*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 278 )) ||
				  	((i >= 322*DX && i < 500*DX) && (i%DX >= 322 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 46: // 4 cluster (46path)
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 277*DX) && (i%DX >= 100 && i%DX < 277 )) || 
				  	((i >= 100*DX && i < 277*DX) && (i%DX >= 323 && i%DX < 500 )) ||
				  	((i >= 323*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 277 )) ||
				  	((i >= 323*DX && i < 500*DX) && (i%DX >= 323 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 48: // 4 cluster (48path)
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 276*DX) && (i%DX >= 100 && i%DX < 276 )) || 
				  	((i >= 100*DX && i < 276*DX) && (i%DX >= 324 && i%DX < 500 )) ||
				  	((i >= 324*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 276 )) ||
				  	((i >= 324*DX && i < 500*DX) && (i%DX >= 324 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 50100: // 4 cluster (50path) --> 100x100x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 175*DX && i < 275*DX) && (i%DX >= 175 && i%DX < 275 )) || 
				  	((i >= 175*DX && i < 275*DX) && (i%DX >= 325 && i%DX < 425 )) ||
				  	((i >= 325*DX && i < 425*DX) && (i%DX >= 175 && i%DX < 275 )) ||
				  	((i >= 325*DX && i < 425*DX) && (i%DX >= 325 && i%DX < 425 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 50120: // 4 cluster (50path) --> 120x120x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 155*DX && i < 275*DX) && (i%DX >= 155 && i%DX < 275 )) || 
				  	((i >= 155*DX && i < 275*DX) && (i%DX >= 325 && i%DX < 445 )) ||
				  	((i >= 325*DX && i < 445*DX) && (i%DX >= 155 && i%DX < 275 )) ||
				  	((i >= 325*DX && i < 445*DX) && (i%DX >= 325 && i%DX < 445 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 50140: // 4 cluster (50path) --> 140x140x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 135*DX && i < 275*DX) && (i%DX >= 135 && i%DX < 275 )) || 
				  	((i >= 135*DX && i < 275*DX) && (i%DX >= 325 && i%DX < 465 )) ||
				  	((i >= 325*DX && i < 465*DX) && (i%DX >= 135 && i%DX < 275 )) ||
				  	((i >= 325*DX && i < 465*DX) && (i%DX >= 325 && i%DX < 465 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 50160: // 4 cluster (50path) --> 160x160x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 115*DX && i < 275*DX) && (i%DX >= 115 && i%DX < 275 )) || 
				  	((i >= 115*DX && i < 275*DX) && (i%DX >= 325 && i%DX < 485 )) ||
				  	((i >= 325*DX && i < 485*DX) && (i%DX >= 115 && i%DX < 275 )) ||
				  	((i >= 325*DX && i < 485*DX) && (i%DX >= 325 && i%DX < 485 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 50170: // 4 cluster (50path) --> 170x170x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 105*DX && i < 275*DX) && (i%DX >= 105 && i%DX < 275 )) || 
				  	((i >= 105*DX && i < 275*DX) && (i%DX >= 325 && i%DX < 495 )) ||
				  	((i >= 325*DX && i < 495*DX) && (i%DX >= 105 && i%DX < 275 )) ||
				  	((i >= 325*DX && i < 495*DX) && (i%DX >= 325 && i%DX < 495 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 50175: // 4 cluster (50path) --> 175x175x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 275*DX) && (i%DX >= 100 && i%DX < 275 )) || 
				  	((i >= 100*DX && i < 275*DX) && (i%DX >= 325 && i%DX < 500 )) ||
				  	((i >= 325*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 275 )) ||
				  	((i >= 325*DX && i < 500*DX) && (i%DX >= 325 && i%DX < 500 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 50180: // 4 cluster (50path) --> 180x180x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  95*DX && i < 275*DX) && (i%DX >=  95 && i%DX < 275 )) || 
				  	((i >=  95*DX && i < 275*DX) && (i%DX >= 325 && i%DX < 505 )) ||
				  	((i >= 325*DX && i < 505*DX) && (i%DX >=  95 && i%DX < 275 )) ||
				  	((i >= 325*DX && i < 505*DX) && (i%DX >= 325 && i%DX < 505 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 50190: // 4 cluster (50path) --> 190x190x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  85*DX && i < 275*DX) && (i%DX >=  85 && i%DX < 275 )) || 
				  	((i >=  85*DX && i < 275*DX) && (i%DX >= 325 && i%DX < 515 )) ||
				  	((i >= 325*DX && i < 515*DX) && (i%DX >=  85 && i%DX < 275 )) ||
				  	((i >= 325*DX && i < 515*DX) && (i%DX >= 325 && i%DX < 515 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 50200: // 4 cluster (50path) --> 200x200x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  75*DX && i < 275*DX) && (i%DX >=  75 && i%DX < 275 )) || 
				  	((i >=  75*DX && i < 275*DX) && (i%DX >= 325 && i%DX < 525 )) ||
				  	((i >= 325*DX && i < 525*DX) && (i%DX >=  75 && i%DX < 275 )) ||
				  	((i >= 325*DX && i < 525*DX) && (i%DX >= 325 && i%DX < 525 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 50210: // 4 cluster (50path) --> 210x210x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  65*DX && i < 275*DX) && (i%DX >=  65 && i%DX < 275 )) || 
				  	((i >=  65*DX && i < 275*DX) && (i%DX >= 325 && i%DX < 535 )) ||
				  	((i >= 325*DX && i < 535*DX) && (i%DX >=  65 && i%DX < 275 )) ||
				  	((i >= 325*DX && i < 535*DX) && (i%DX >= 325 && i%DX < 535 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 50220: // 4 cluster (50path) --> 220x220x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  55*DX && i < 275*DX) && (i%DX >=  55 && i%DX < 275 )) || 
				  	((i >=  55*DX && i < 275*DX) && (i%DX >= 325 && i%DX < 545 )) ||
				  	((i >= 325*DX && i < 545*DX) && (i%DX >=  55 && i%DX < 275 )) ||
				  	((i >= 325*DX && i < 545*DX) && (i%DX >= 325 && i%DX < 545 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 50225: // 4 cluster (50path) --> 225x225x4
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  50*DX && i < 275*DX) && (i%DX >=  50 && i%DX < 275 )) || 
				  	((i >=  50*DX && i < 275*DX) && (i%DX >= 325 && i%DX < 550 )) ||
				  	((i >= 325*DX && i < 550*DX) && (i%DX >=  50 && i%DX < 275 )) ||
				  	((i >= 325*DX && i < 550*DX) && (i%DX >= 325 && i%DX < 550 )) 
				) {utype[i]=1;	c++;}
			}
		break;

	}

}
