#include <string.h>
#include "syspara.h"

void cluster2_setting()
{
	int i,c;

	// parameter setup information
	printf("Nx1=%d,Ny1=%d,Nx2=%d,Ny2=%d,Nx3=%d,Ny3=%d,Nx4=%d,Ny4=%d\n",Nx1,Ny1,Nx2,Ny2,Nx3,Ny3,Nx4,Ny4);
	for(i=0;i<MEDIA_SITE;i++) utype[i]=0;
	switch(cluster){
		case 2: // 2 cluster (2path)
			for(i=0 ; i < MEDIA_SITE; i++){
				//if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < 299 )) || 
				//	((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= 301 && i%DX < Nx4 )) 
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 4: // 2 cluster (4path)
			for(i=0 ; i < MEDIA_SITE; i++){
				//if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < 298 )) || 
				// 	((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= 302 && i%DX < Nx4 )) 
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 6: // 2 cluster (6path)
			for(i=0 ; i < MEDIA_SITE; i++){
				//if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < 297 )) || 
				// 	((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= 303 && i%DX < Nx4 )) 
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 8: // 2 cluster (8path)
			for(i=0 ; i < MEDIA_SITE; i++){
				//if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < 296 )) || 
				// 	((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= 304 && i%DX < Nx4 )) 
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 10: // 2 cluster (10path)
			for(i=0 ; i < MEDIA_SITE; i++){
				//if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < 295 )) || 
				// 	((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= 305 && i%DX < Nx4 )) 
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 12: // 2 cluster (12path)
			for(i=0 ; i < MEDIA_SITE; i++){
				//if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < 294 )) || 
				// 	((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= 306 && i%DX < Nx4 )) 
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 14: // 2 cluster (14path)
			for(i=0 ; i < MEDIA_SITE; i++){
				//if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < 293 )) || 
				// 	((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= 307 && i%DX < Nx4 )) 
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 16: // 2 cluster (16path)
			for(i=0 ; i < MEDIA_SITE; i++){
				//if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < 292 )) || 
				// 	((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= 308 && i%DX < Nx4 )) 
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 18: // 2 cluster (18path)
			for(i=0 ; i < MEDIA_SITE; i++){
				//if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < 291 )) || 
				// 	((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= 309 && i%DX < Nx4 )) 
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 20: // 2 cluster (20path)
			for(i=0 ; i < MEDIA_SITE; i++){
				//if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < 290 )) || 
				// 	((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= 310 && i%DX < Nx4 )) 
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 22: // 2 cluster (22path)
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 24: // 2 cluster (24path)
			for(i=0 ; i < MEDIA_SITE; i++){
				//if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < 288 )) || 
				// 	((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= 312 && i%DX < Nx4 )) 
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 26: // 2 cluster (26path)
			for(i=0 ; i < MEDIA_SITE; i++){
				//if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < 287 )) || 
				// 	((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= 313 && i%DX < Nx4 )) 
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 28: // 2 cluster (28path)
			for(i=0 ; i < MEDIA_SITE; i++){
				//if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < 286 )) || 
				// 	((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= 314 && i%DX < Nx4 )) 
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 30: // 2 cluster (30path)
			for(i=0 ; i < MEDIA_SITE; i++){
				//if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < 285 )) || 
				//  	((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= 315 && i%DX < Nx4 )) 
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 32: // 2 cluster (32path)
			for(i=0 ; i < MEDIA_SITE; i++){
				//if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < 284 )) || 
				// 	((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= 316 && i%DX < Nx4 )) 
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 34: // 2 cluster (34path)
			for(i=0 ; i < MEDIA_SITE; i++){
				//if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < 283 )) || 
				//  	((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= 317 && i%DX < Nx4 )) 
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 36: // 2 cluster (36path)
			for(i=0 ; i < MEDIA_SITE; i++){
				//if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < 282 )) || 
				// 	((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= 318 && i%DX < Nx4 )) 
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 38: // 2 cluster (38path)
			for(i=0 ; i < MEDIA_SITE; i++){
				//if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < 281 )) || 
				//	((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= 319 && i%DX < Nx4 )) 
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
		case 40: // 2 cluster (40path)
			for(i=0 ; i < MEDIA_SITE; i++){
				//if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < 280 )) || 
				//	((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= 320 && i%DX < Nx4 )) 
				if( ((i >= Ny1*DX && i < Ny2*DX) && (i%DX >= Nx1 && i%DX < Nx2 )) || 
				  	((i >= Ny3*DX && i < Ny4*DX) && (i%DX >= Nx3 && i%DX < Nx4 )) 
				) {utype[i]=1;	c++;}
			}
		break;
	}

}
