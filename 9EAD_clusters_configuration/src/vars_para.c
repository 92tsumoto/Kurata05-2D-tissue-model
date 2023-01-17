#include <string.h>
#include "syspara.h"

void input_para(FILE *fpin)
{
	int i,ii;

	fscanf(fpin,"%d",&simtype);
	fscanf(fpin,"%d",&cluster);
	fscanf(fpin,"%d",&Nx1);
	fscanf(fpin,"%d",&Nx2);
	fscanf(fpin,"%d",&Nx3);
	fscanf(fpin,"%d",&Nx4);
	fscanf(fpin,"%d",&Ny1);
	fscanf(fpin,"%d",&Ny2);
	fscanf(fpin,"%d",&Ny3);
	fscanf(fpin,"%d",&Ny4);
	fscanf(fpin,"%lf",&Diff_l);
	fscanf(fpin,"%lf",&Diff_t);
	fscanf(fpin,"%lf",&rateD);
	fscanf(fpin,"%lf",&BCL);
	fscanf(fpin,"%lf",&kr_rate);
	fscanf(fpin,"%lf",&ks_rate);
	fscanf(fpin,"%lf",&Istim_base);
	fscanf(fpin,"%d",&stim_sw);
	fscanf(fpin,"%d",&datas);
	for (ii = 0; ii < datas; ii++){
		for (i=0;i<NN;i++){
			fscanf(fpin,"%lf",&x0[ii][i]);
		}
	}
	fscanf(fpin,"%d",&div_num);
	fscanf(fpin,"%d",&write);
	fscanf(fpin,"%d",&reduce);
	fscanf(fpin,"%d",&outdata);
	fscanf(fpin,"%d",&outdata_plus);
	fscanf(fpin,"%d",&debug);

}

void input_init(FILE *fpin1, FILE *fpin2)
{

	int i,j;
	int check1=0,check2=0;
	double init1[NN],init2[NN];

	printf("input init, middle point=%d\n",MEDIA_SITE/2);

	for (i=0;i<NN;i++){
		fscanf(fpin1,"%lf",&init1[i]);
	}

	for (i=0;i<NN;i++){
		fscanf(fpin2,"%lf",&init2[i]);
	}

	for (i=0;i<MEDIA_SITE;i++){
		if(utype[i]==1){
			if(check1==0) printf("EAD unit initial values\n");
			for (j=0;j<NN;j++){
				//var.u[j][i]=init2[j];
				vmf[j][i]=init2[j];
				//if(check1==0) printf("x[%d][%d] = %lf\n",j,i,var.u[j][i]);
				if(check1==0) printf("x[%d][%d] = %lf\n",j,i,vmf[j][i]);
			} check1++;
			printf("%d, ",i);
		} else if(utype[i]==0){
			if(check2==0) printf("noEAD unit initial values\n");
			for (j=0;j<NN;j++){
				//var.u[j][i]=init1[j];
				vmf[j][i]=init1[j];
				//if(check2==0) printf("x[%d][%d] = %lf\n",j,i,var.u[j][i]);
				if(check2==0) printf("x[%d][%d] = %lf\n",j,i,vmf[j][i]);
			} check2++;
		}
	}
	printf("\n");

}

void val_consts(FILE *fp1)
{
	int i,w,c;
	double v_old,dvdt,dvdt_new;

	// Cell Geometry */
		radius = 0.0011;
		length = 0.01;
		del_x = length;
		CapHV = 153.4;  // Membrane Capacitance (pF)
		vcell = 38.0*0.000000000001; // Cell Volume:3.801e-5 (uL)
		vi = vcell*0.68;      // Myoplasm volume (uL) = 68% for Cell volume
		vup = vcell*0.0552;    // NSR volume (uL)
		vrel = vcell*0.0048;    // JSR volume (uL)

	// invariant constant
		FRT = F/(R*T);
		RTF = R*T/F;

	// Extracellular Concentrations
		Nao = 140.0;    // (mM) 
		Ko = 5.4;      // (mM)
		Cao = 2.0;     // (mM)

		prnak = 0.01833;     // Na/K Permiability Ratio
		pkna = 0.12;     // Na/K Permiability Ratio

	// Equilibrium Potentials (mV)
	//	var.Ek = (RTF/var.zk)*log(var.ko/var.ki);
		if(simtype==0){ // only Endo cell unit myofiber
			for(i=0;i<MEDIA_SITE;i++) celltype[i]=0;	
		} else if(simtype==1){ // only Epi cell unit myofiber
			for(i=0;i<MEDIA_SITE;i++) celltype[i]=1;	
		} else if(simtype==2){ // only Mid cell unit myofiber
			for(i=0;i<MEDIA_SITE;i++) celltype[i]=2;	
		} else if(simtype==5){ // Transmural case (#100 units)
			for(i=0;i<15;i++) celltype[i]=0;	
			for(i=15;i<70;i++) celltype[i]=2;	
			for(i=70;i<100;i++) celltype[i]=1;	
		}
	
	// parameter setup information
	printf("Nx1=%d,Ny1=%d,Nx2=%d,Ny2=%d,Nx3=%d,Ny3=%d,Nx4=%d,Ny4=%d\n",Nx1,Ny1,Nx2,Ny2,Nx3,Ny3,Nx4,Ny4);
	for(i=0;i<MEDIA_SITE;i++) utype[i]=0;
	switch(cluster){
	/*	case 1: // 1 cluster (equal to ver1.0.0)
			for(i=0;i<MEDIA_SITE;i++){
				if( i>=Ny1*DX && i< Ny2*DX ){
					if( i%DX >=Nx1 && i%DX < Nx2 ) {
						utype[i]=1;
						c++;
					}
				} 
			}
			break;
	*/	
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

		case 2140: // 9 cluster (2path) --> 140x140x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  88*DX && i < 228*DX) && (i%DX >=  88 && i%DX < 228 )) || 
				  	((i >=  88*DX && i < 228*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >=  88*DX && i < 228*DX) && (i%DX >= 372 && i%DX < 512 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >=  88 && i%DX < 228 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 372 && i%DX < 512 )) ||
				  	((i >= 372*DX && i < 512*DX) && (i%DX >=  88 && i%DX < 228 )) ||
				  	((i >= 372*DX && i < 512*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 372*DX && i < 512*DX) && (i%DX >= 372 && i%DX < 512 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 2132: // 9 cluster (2path) --> 132x132x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 232*DX) && (i%DX >= 100 && i%DX < 232 )) || 
				  	((i >= 100*DX && i < 232*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 100*DX && i < 232*DX) && (i%DX >= 368 && i%DX < 500 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 100 && i%DX < 232 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 368 && i%DX < 500 )) ||
				  	((i >= 368*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 232 )) ||
				  	((i >= 368*DX && i < 500*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 368*DX && i < 500*DX) && (i%DX >= 368 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 2130: // 9 cluster (2path) --> 130x130x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 103*DX && i < 233*DX) && (i%DX >= 103 && i%DX < 233 )) || 
				  	((i >= 103*DX && i < 233*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 103*DX && i < 233*DX) && (i%DX >= 367 && i%DX < 497 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 103 && i%DX < 233 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 367 && i%DX < 497 )) ||
				  	((i >= 367*DX && i < 497*DX) && (i%DX >= 103 && i%DX < 233 )) ||
				  	((i >= 367*DX && i < 497*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 367*DX && i < 497*DX) && (i%DX >= 367 && i%DX < 497 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 2120: // 9 cluster (2path) --> 120x120x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 118*DX && i < 238*DX) && (i%DX >= 118 && i%DX < 238 )) || 
				  	((i >= 118*DX && i < 238*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 118*DX && i < 238*DX) && (i%DX >= 362 && i%DX < 482 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 118 && i%DX < 238 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 362 && i%DX < 482 )) ||
				  	((i >= 362*DX && i < 482*DX) && (i%DX >= 118 && i%DX < 238 )) ||
				  	((i >= 362*DX && i < 482*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 362*DX && i < 482*DX) && (i%DX >= 362 && i%DX < 482 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 2110: // 9 cluster (2path) --> 110x110x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 133*DX && i < 243*DX) && (i%DX >= 133 && i%DX < 243 )) || 
				  	((i >= 133*DX && i < 243*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 133*DX && i < 243*DX) && (i%DX >= 357 && i%DX < 467 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 133 && i%DX < 243 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 357 && i%DX < 467 )) ||
				  	((i >= 357*DX && i < 467*DX) && (i%DX >= 133 && i%DX < 243 )) ||
				  	((i >= 357*DX && i < 467*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 357*DX && i < 467*DX) && (i%DX >= 357 && i%DX < 467 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 2100: // 9 cluster (2path) --> 100x100x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 148*DX && i < 248*DX) && (i%DX >= 148 && i%DX < 248 )) || 
				  	((i >= 148*DX && i < 248*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 148*DX && i < 248*DX) && (i%DX >= 352 && i%DX < 452 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 148 && i%DX < 248 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 352 && i%DX < 452 )) ||
				  	((i >= 352*DX && i < 452*DX) && (i%DX >= 148 && i%DX < 248 )) ||
				  	((i >= 352*DX && i < 452*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 352*DX && i < 452*DX) && (i%DX >= 352 && i%DX < 452 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 2080: // 9 cluster (2path) -->  80x 80x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 178*DX && i < 258*DX) && (i%DX >= 178 && i%DX < 258 )) || 
				  	((i >= 178*DX && i < 258*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 178*DX && i < 258*DX) && (i%DX >= 342 && i%DX < 422 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 178 && i%DX < 258 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 342 && i%DX < 422 )) ||
				  	((i >= 342*DX && i < 422*DX) && (i%DX >= 178 && i%DX < 258 )) ||
				  	((i >= 342*DX && i < 422*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 342*DX && i < 422*DX) && (i%DX >= 342 && i%DX < 422 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 2060: // 9 cluster (2path) -->  60x 60x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 208*DX && i < 268*DX) && (i%DX >= 208 && i%DX < 268 )) || 
				  	((i >= 208*DX && i < 268*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 208*DX && i < 268*DX) && (i%DX >= 332 && i%DX < 392 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 208 && i%DX < 268 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 332 && i%DX < 392 )) ||
				  	((i >= 332*DX && i < 392*DX) && (i%DX >= 208 && i%DX < 268 )) ||
				  	((i >= 332*DX && i < 392*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 332*DX && i < 392*DX) && (i%DX >= 332 && i%DX < 392 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 2040: // 9 cluster (2path) -->  40x 40x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 238*DX && i < 278*DX) && (i%DX >= 238 && i%DX < 278 )) || 
				  	((i >= 238*DX && i < 278*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 238*DX && i < 278*DX) && (i%DX >= 322 && i%DX < 362 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 238 && i%DX < 278 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 322 && i%DX < 362 )) ||
				  	((i >= 322*DX && i < 362*DX) && (i%DX >= 238 && i%DX < 278 )) ||
				  	((i >= 322*DX && i < 362*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 322*DX && i < 362*DX) && (i%DX >= 322 && i%DX < 362 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 2020: // 9 cluster (2path) -->  20x 20x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 268*DX && i < 288*DX) && (i%DX >= 268 && i%DX < 288 )) || 
				  	((i >= 268*DX && i < 288*DX) && (i%DX >= 290 && i%DX < 310 )) ||
				  	((i >= 268*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 332 )) ||
				  	((i >= 290*DX && i < 310*DX) && (i%DX >= 268 && i%DX < 288 )) ||
				  	((i >= 290*DX && i < 310*DX) && (i%DX >= 290 && i%DX < 310 )) ||
				  	((i >= 290*DX && i < 310*DX) && (i%DX >= 312 && i%DX < 332 )) ||
				  	((i >= 312*DX && i < 332*DX) && (i%DX >= 268 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 332*DX) && (i%DX >= 290 && i%DX < 310 )) ||
				  	((i >= 312*DX && i < 332*DX) && (i%DX >= 312 && i%DX < 332 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5140: // 9 cluster (5path) --> 140x140x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  85*DX && i < 225*DX) && (i%DX >=  85 && i%DX < 225 )) || 
				  	((i >=  85*DX && i < 225*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >=  85*DX && i < 225*DX) && (i%DX >= 375 && i%DX < 515 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >=  85 && i%DX < 225 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 375 && i%DX < 515 )) ||
				  	((i >= 375*DX && i < 515*DX) && (i%DX >=  85 && i%DX < 225 )) ||
				  	((i >= 375*DX && i < 515*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 375*DX && i < 515*DX) && (i%DX >= 375 && i%DX < 515 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5132: // 9 cluster (5path) --> 132x132x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  97*DX && i < 229*DX) && (i%DX >=  97 && i%DX < 229 )) || 
				  	((i >=  97*DX && i < 229*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >=  97*DX && i < 229*DX) && (i%DX >= 371 && i%DX < 503 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >=  97 && i%DX < 229 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 371 && i%DX < 503 )) ||
				  	((i >= 371*DX && i < 503*DX) && (i%DX >=  97 && i%DX < 229 )) ||
				  	((i >= 371*DX && i < 503*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 371*DX && i < 503*DX) && (i%DX >= 371 && i%DX < 503 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5130: // 9 cluster (5path) --> 130x130x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 230*DX) && (i%DX >= 100 && i%DX < 230 )) || 
				  	((i >= 100*DX && i < 230*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 100*DX && i < 230*DX) && (i%DX >= 370 && i%DX < 500 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 100 && i%DX < 230 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 370 && i%DX < 500 )) ||
				  	((i >= 370*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 230 )) ||
				  	((i >= 370*DX && i < 500*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 370*DX && i < 500*DX) && (i%DX >= 370 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5120: // 9 cluster (5path) --> 120x120x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 115*DX && i < 235*DX) && (i%DX >= 115 && i%DX < 235 )) || 
				  	((i >= 115*DX && i < 235*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 115*DX && i < 235*DX) && (i%DX >= 365 && i%DX < 485 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 115 && i%DX < 235 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 365 && i%DX < 485 )) ||
				  	((i >= 365*DX && i < 485*DX) && (i%DX >= 115 && i%DX < 235 )) ||
				  	((i >= 365*DX && i < 485*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 365*DX && i < 485*DX) && (i%DX >= 365 && i%DX < 485 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5110: // 9 cluster (5path) --> 110x110x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 130*DX && i < 240*DX) && (i%DX >= 130 && i%DX < 240 )) || 
				  	((i >= 130*DX && i < 240*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 130*DX && i < 240*DX) && (i%DX >= 360 && i%DX < 470 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 130 && i%DX < 240 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 360 && i%DX < 470 )) ||
				  	((i >= 360*DX && i < 470*DX) && (i%DX >= 130 && i%DX < 240 )) ||
				  	((i >= 360*DX && i < 470*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 360*DX && i < 470*DX) && (i%DX >= 360 && i%DX < 470 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5100: // 9 cluster (5path) --> 100x100x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 145*DX && i < 245*DX) && (i%DX >= 145 && i%DX < 245 )) || 
				  	((i >= 145*DX && i < 245*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 145*DX && i < 245*DX) && (i%DX >= 355 && i%DX < 455 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 145 && i%DX < 245 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 355 && i%DX < 455 )) ||
				  	((i >= 355*DX && i < 455*DX) && (i%DX >= 145 && i%DX < 245 )) ||
				  	((i >= 355*DX && i < 455*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 355*DX && i < 455*DX) && (i%DX >= 355 && i%DX < 455 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5080: // 9 cluster (5path) -->  80x 80x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 175*DX && i < 255*DX) && (i%DX >= 175 && i%DX < 255 )) || 
				  	((i >= 175*DX && i < 255*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 175*DX && i < 255*DX) && (i%DX >= 345 && i%DX < 425 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 175 && i%DX < 255 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 345 && i%DX < 425 )) ||
				  	((i >= 345*DX && i < 425*DX) && (i%DX >= 175 && i%DX < 255 )) ||
				  	((i >= 345*DX && i < 425*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 345*DX && i < 425*DX) && (i%DX >= 345 && i%DX < 425 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5060: // 9 cluster (5path) -->  60x 60x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 205*DX && i < 265*DX) && (i%DX >= 205 && i%DX < 265 )) || 
				  	((i >= 205*DX && i < 265*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 205*DX && i < 265*DX) && (i%DX >= 335 && i%DX < 395 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 205 && i%DX < 265 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 335 && i%DX < 395 )) ||
				  	((i >= 335*DX && i < 395*DX) && (i%DX >= 205 && i%DX < 265 )) ||
				  	((i >= 335*DX && i < 395*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 335*DX && i < 395*DX) && (i%DX >= 335 && i%DX < 395 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5040: // 9 cluster (5path) -->  40x 40x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 235*DX && i < 275*DX) && (i%DX >= 235 && i%DX < 275 )) || 
				  	((i >= 235*DX && i < 275*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 235*DX && i < 275*DX) && (i%DX >= 325 && i%DX < 365 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 235 && i%DX < 275 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 325 && i%DX < 365 )) ||
				  	((i >= 325*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 275 )) ||
				  	((i >= 325*DX && i < 365*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 325*DX && i < 365*DX) && (i%DX >= 325 && i%DX < 365 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5020: // 9 cluster (5path) -->  20x 20x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 265*DX && i < 285*DX) && (i%DX >= 265 && i%DX < 285 )) || 
				  	((i >= 265*DX && i < 285*DX) && (i%DX >= 290 && i%DX < 310 )) ||
				  	((i >= 265*DX && i < 285*DX) && (i%DX >= 315 && i%DX < 335 )) ||
				  	((i >= 290*DX && i < 310*DX) && (i%DX >= 265 && i%DX < 285 )) ||
				  	((i >= 290*DX && i < 310*DX) && (i%DX >= 290 && i%DX < 310 )) ||
				  	((i >= 290*DX && i < 310*DX) && (i%DX >= 315 && i%DX < 335 )) ||
				  	((i >= 315*DX && i < 335*DX) && (i%DX >= 265 && i%DX < 285 )) ||
				  	((i >= 315*DX && i < 335*DX) && (i%DX >= 290 && i%DX < 310 )) ||
				  	((i >= 315*DX && i < 335*DX) && (i%DX >= 315 && i%DX < 335 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 8140: // 9 cluster (8path) --> 140x140x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  82*DX && i < 222*DX) && (i%DX >=  82 && i%DX < 222 )) || 
				  	((i >=  82*DX && i < 222*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >=  82*DX && i < 222*DX) && (i%DX >= 378 && i%DX < 518 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >=  82 && i%DX < 222 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 378 && i%DX < 518 )) ||
				  	((i >= 378*DX && i < 518*DX) && (i%DX >=  82 && i%DX < 222 )) ||
				  	((i >= 378*DX && i < 518*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 378*DX && i < 518*DX) && (i%DX >= 378 && i%DX < 518 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 8132: // 9 cluster (8path) --> 132x132x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  94*DX && i < 226*DX) && (i%DX >=  94 && i%DX < 226 )) || 
				  	((i >=  94*DX && i < 226*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >=  94*DX && i < 226*DX) && (i%DX >= 374 && i%DX < 506 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >=  94 && i%DX < 226 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 374 && i%DX < 506 )) ||
				  	((i >= 374*DX && i < 506*DX) && (i%DX >=  94 && i%DX < 226 )) ||
				  	((i >= 374*DX && i < 506*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 374*DX && i < 506*DX) && (i%DX >= 374 && i%DX < 506 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 8130: // 9 cluster (8path) --> 130x130x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  97*DX && i < 227*DX) && (i%DX >=  97 && i%DX < 227 )) || 
				  	((i >=  97*DX && i < 227*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >=  97*DX && i < 227*DX) && (i%DX >= 373 && i%DX < 503 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >=  97 && i%DX < 227 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 373 && i%DX < 503 )) ||
				  	((i >= 373*DX && i < 503*DX) && (i%DX >=  97 && i%DX < 227 )) ||
				  	((i >= 373*DX && i < 503*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 373*DX && i < 503*DX) && (i%DX >= 373 && i%DX < 503 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 8128: // 9 cluster (8path) --> 128x128x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 228*DX) && (i%DX >= 100 && i%DX < 228 )) || 
				  	((i >= 100*DX && i < 228*DX) && (i%DX >= 235 && i%DX < 364 )) ||
				  	((i >= 100*DX && i < 228*DX) && (i%DX >= 371 && i%DX < 500 )) ||
				  	((i >= 236*DX && i < 364*DX) && (i%DX >= 100 && i%DX < 228 )) ||
				  	((i >= 236*DX && i < 364*DX) && (i%DX >= 235 && i%DX < 364 )) ||
				  	((i >= 236*DX && i < 364*DX) && (i%DX >= 371 && i%DX < 500 )) ||
				  	((i >= 372*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 228 )) ||
				  	((i >= 372*DX && i < 500*DX) && (i%DX >= 235 && i%DX < 364 )) ||
				  	((i >= 372*DX && i < 500*DX) && (i%DX >= 371 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 8120: // 9 cluster (8path) --> 120x120x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 112*DX && i < 232*DX) && (i%DX >= 112 && i%DX < 232 )) || 
				  	((i >= 112*DX && i < 232*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 112*DX && i < 232*DX) && (i%DX >= 368 && i%DX < 488 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 112 && i%DX < 232 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 368 && i%DX < 488 )) ||
				  	((i >= 368*DX && i < 488*DX) && (i%DX >= 112 && i%DX < 232 )) ||
				  	((i >= 368*DX && i < 488*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 368*DX && i < 488*DX) && (i%DX >= 368 && i%DX < 488 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 8110: // 9 cluster (8path) --> 110x110x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 127*DX && i < 237*DX) && (i%DX >= 127 && i%DX < 237 )) || 
				  	((i >= 127*DX && i < 237*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 127*DX && i < 237*DX) && (i%DX >= 363 && i%DX < 473 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 127 && i%DX < 237 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 363 && i%DX < 473 )) ||
				  	((i >= 363*DX && i < 473*DX) && (i%DX >= 127 && i%DX < 237 )) ||
				  	((i >= 363*DX && i < 473*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 363*DX && i < 473*DX) && (i%DX >= 363 && i%DX < 473 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 8100: // 9 cluster (8path) --> 100x100x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 142*DX && i < 242*DX) && (i%DX >= 142 && i%DX < 242 )) || 
				  	((i >= 142*DX && i < 242*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 142*DX && i < 242*DX) && (i%DX >= 358 && i%DX < 458 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 142 && i%DX < 242 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 358 && i%DX < 458 )) ||
				  	((i >= 358*DX && i < 458*DX) && (i%DX >= 142 && i%DX < 242 )) ||
				  	((i >= 358*DX && i < 458*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 358*DX && i < 458*DX) && (i%DX >= 358 && i%DX < 458 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 8080: // 9 cluster (8path) -->  80x 80x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 172*DX && i < 252*DX) && (i%DX >= 172 && i%DX < 252 )) || 
				  	((i >= 172*DX && i < 252*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 172*DX && i < 252*DX) && (i%DX >= 348 && i%DX < 428 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 172 && i%DX < 252 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 348 && i%DX < 428 )) ||
				  	((i >= 348*DX && i < 428*DX) && (i%DX >= 172 && i%DX < 252 )) ||
				  	((i >= 348*DX && i < 428*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 348*DX && i < 428*DX) && (i%DX >= 348 && i%DX < 428 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 8060: // 9 cluster (8path) -->  60x 60x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 202*DX && i < 262*DX) && (i%DX >= 202 && i%DX < 262 )) || 
				  	((i >= 202*DX && i < 262*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 202*DX && i < 262*DX) && (i%DX >= 338 && i%DX < 398 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 202 && i%DX < 262 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 338 && i%DX < 398 )) ||
				  	((i >= 338*DX && i < 398*DX) && (i%DX >= 202 && i%DX < 262 )) ||
				  	((i >= 338*DX && i < 398*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 338*DX && i < 398*DX) && (i%DX >= 338 && i%DX < 398 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 8040: // 9 cluster (8path) -->  40x 40x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 232*DX && i < 272*DX) && (i%DX >= 232 && i%DX < 272 )) || 
				  	((i >= 232*DX && i < 272*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 232*DX && i < 272*DX) && (i%DX >= 328 && i%DX < 368 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 232 && i%DX < 272 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 328 && i%DX < 368 )) ||
				  	((i >= 328*DX && i < 368*DX) && (i%DX >= 232 && i%DX < 272 )) ||
				  	((i >= 328*DX && i < 368*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 328*DX && i < 368*DX) && (i%DX >= 328 && i%DX < 368 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 8020: // 9 cluster (8path) -->  20x 20x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 262*DX && i < 282*DX) && (i%DX >= 262 && i%DX < 282 )) || 
				  	((i >= 262*DX && i < 282*DX) && (i%DX >= 290 && i%DX < 310 )) ||
				  	((i >= 262*DX && i < 282*DX) && (i%DX >= 318 && i%DX < 338 )) ||
				  	((i >= 290*DX && i < 310*DX) && (i%DX >= 262 && i%DX < 282 )) ||
				  	((i >= 290*DX && i < 310*DX) && (i%DX >= 290 && i%DX < 310 )) ||
				  	((i >= 290*DX && i < 310*DX) && (i%DX >= 318 && i%DX < 338 )) ||
				  	((i >= 318*DX && i < 338*DX) && (i%DX >= 262 && i%DX < 282 )) ||
				  	((i >= 318*DX && i < 338*DX) && (i%DX >= 290 && i%DX < 310 )) ||
				  	((i >= 318*DX && i < 338*DX) && (i%DX >= 318 && i%DX < 338 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 11140: // 9 cluster (11path) --> 140x140x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  79*DX && i < 219*DX) && (i%DX >=  79 && i%DX < 219 )) || 
				  	((i >=  79*DX && i < 219*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >=  79*DX && i < 219*DX) && (i%DX >= 381 && i%DX < 521 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >=  79 && i%DX < 219 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 381 && i%DX < 521 )) ||
				  	((i >= 381*DX && i < 521*DX) && (i%DX >=  79 && i%DX < 219 )) ||
				  	((i >= 381*DX && i < 521*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 381*DX && i < 521*DX) && (i%DX >= 381 && i%DX < 521 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 11132: // 9 cluster (11path) --> 132x132x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  91*DX && i < 223*DX) && (i%DX >=  91 && i%DX < 223 )) || 
				  	((i >=  91*DX && i < 223*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >=  91*DX && i < 223*DX) && (i%DX >= 377 && i%DX < 509 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >=  91 && i%DX < 223 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 377 && i%DX < 509 )) ||
				  	((i >= 377*DX && i < 509*DX) && (i%DX >=  91 && i%DX < 223 )) ||
				  	((i >= 377*DX && i < 509*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 377*DX && i < 509*DX) && (i%DX >= 377 && i%DX < 509 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 11130: // 9 cluster (11path) --> 130x130x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  94*DX && i < 224*DX) && (i%DX >=  94 && i%DX < 224 )) || 
				  	((i >=  94*DX && i < 224*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >=  94*DX && i < 224*DX) && (i%DX >= 376 && i%DX < 506 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >=  94 && i%DX < 224 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 376 && i%DX < 506 )) ||
				  	((i >= 376*DX && i < 506*DX) && (i%DX >=  94 && i%DX < 224 )) ||
				  	((i >= 376*DX && i < 506*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 376*DX && i < 506*DX) && (i%DX >= 376 && i%DX < 506 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 11126: // 9 cluster (11path) --> 126x126x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 226*DX) && (i%DX >= 100 && i%DX < 226 )) || 
				  	((i >= 100*DX && i < 226*DX) && (i%DX >= 237 && i%DX < 363 )) ||
				  	((i >= 100*DX && i < 226*DX) && (i%DX >= 374 && i%DX < 500 )) ||
				  	((i >= 237*DX && i < 363*DX) && (i%DX >= 100 && i%DX < 226 )) ||
				  	((i >= 237*DX && i < 363*DX) && (i%DX >= 237 && i%DX < 363 )) ||
				  	((i >= 237*DX && i < 363*DX) && (i%DX >= 374 && i%DX < 500 )) ||
				  	((i >= 374*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 226 )) ||
				  	((i >= 374*DX && i < 500*DX) && (i%DX >= 237 && i%DX < 363 )) ||
				  	((i >= 374*DX && i < 500*DX) && (i%DX >= 374 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 11124: // 9 cluster (11path) --> 124x124x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 103*DX && i < 227*DX) && (i%DX >= 103 && i%DX < 227 )) || 
				  	((i >= 103*DX && i < 227*DX) && (i%DX >= 238 && i%DX < 362 )) ||
				  	((i >= 103*DX && i < 227*DX) && (i%DX >= 373 && i%DX < 497 )) ||
				  	((i >= 238*DX && i < 362*DX) && (i%DX >= 103 && i%DX < 227 )) ||
				  	((i >= 238*DX && i < 362*DX) && (i%DX >= 238 && i%DX < 362 )) ||
				  	((i >= 238*DX && i < 362*DX) && (i%DX >= 373 && i%DX < 497 )) ||
				  	((i >= 373*DX && i < 497*DX) && (i%DX >= 103 && i%DX < 227 )) ||
				  	((i >= 373*DX && i < 497*DX) && (i%DX >= 238 && i%DX < 362 )) ||
				  	((i >= 373*DX && i < 497*DX) && (i%DX >= 373 && i%DX < 497 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 11122: // 9 cluster (11path) --> 122x122x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 106*DX && i < 228*DX) && (i%DX >= 106 && i%DX < 228 )) || 
				  	((i >= 106*DX && i < 228*DX) && (i%DX >= 239 && i%DX < 361 )) ||
				  	((i >= 106*DX && i < 228*DX) && (i%DX >= 372 && i%DX < 494 )) ||
				  	((i >= 239*DX && i < 361*DX) && (i%DX >= 106 && i%DX < 228 )) ||
				  	((i >= 239*DX && i < 361*DX) && (i%DX >= 239 && i%DX < 361 )) ||
				  	((i >= 239*DX && i < 361*DX) && (i%DX >= 372 && i%DX < 494 )) ||
				  	((i >= 372*DX && i < 494*DX) && (i%DX >= 106 && i%DX < 228 )) ||
				  	((i >= 372*DX && i < 494*DX) && (i%DX >= 239 && i%DX < 361 )) ||
				  	((i >= 372*DX && i < 494*DX) && (i%DX >= 372 && i%DX < 494 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 11120: // 9 cluster (11path) --> 120x120x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 109*DX && i < 229*DX) && (i%DX >= 109 && i%DX < 229 )) || 
				  	((i >= 109*DX && i < 229*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 109*DX && i < 229*DX) && (i%DX >= 371 && i%DX < 491 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 109 && i%DX < 229 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 371 && i%DX < 491 )) ||
				  	((i >= 371*DX && i < 491*DX) && (i%DX >= 109 && i%DX < 229 )) ||
				  	((i >= 371*DX && i < 491*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 371*DX && i < 491*DX) && (i%DX >= 371 && i%DX < 491 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 11110: // 9 cluster (11path) --> 110x110x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 124*DX && i < 234*DX) && (i%DX >= 124 && i%DX < 234 )) || 
				  	((i >= 124*DX && i < 234*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 124*DX && i < 234*DX) && (i%DX >= 366 && i%DX < 476 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 124 && i%DX < 234 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 366 && i%DX < 476 )) ||
				  	((i >= 366*DX && i < 476*DX) && (i%DX >= 124 && i%DX < 234 )) ||
				  	((i >= 366*DX && i < 476*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 366*DX && i < 476*DX) && (i%DX >= 366 && i%DX < 476 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 11100: // 9 cluster (11path) --> 100x100x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 139*DX && i < 239*DX) && (i%DX >= 139 && i%DX < 239 )) || 
				  	((i >= 139*DX && i < 239*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 139*DX && i < 239*DX) && (i%DX >= 361 && i%DX < 461 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 139 && i%DX < 239 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 361 && i%DX < 461 )) ||
				  	((i >= 361*DX && i < 461*DX) && (i%DX >= 139 && i%DX < 239 )) ||
				  	((i >= 361*DX && i < 461*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 361*DX && i < 461*DX) && (i%DX >= 361 && i%DX < 461 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 11080: // 9 cluster (11path) -->  80x 80x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 169*DX && i < 249*DX) && (i%DX >= 169 && i%DX < 249 )) || 
				  	((i >= 169*DX && i < 249*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 169*DX && i < 249*DX) && (i%DX >= 351 && i%DX < 431 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 169 && i%DX < 249 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 351 && i%DX < 431 )) ||
				  	((i >= 351*DX && i < 431*DX) && (i%DX >= 169 && i%DX < 249 )) ||
				  	((i >= 351*DX && i < 431*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 351*DX && i < 431*DX) && (i%DX >= 351 && i%DX < 431 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 11060: // 9 cluster (11path) -->  60x 60x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 199*DX && i < 259*DX) && (i%DX >= 199 && i%DX < 259 )) || 
				  	((i >= 199*DX && i < 259*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 199*DX && i < 259*DX) && (i%DX >= 341 && i%DX < 401 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 199 && i%DX < 259 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 341 && i%DX < 401 )) ||
				  	((i >= 341*DX && i < 401*DX) && (i%DX >= 199 && i%DX < 259 )) ||
				  	((i >= 341*DX && i < 401*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 341*DX && i < 401*DX) && (i%DX >= 341 && i%DX < 401 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 11040: // 9 cluster (11path) -->  40x 40x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 229*DX && i < 269*DX) && (i%DX >= 229 && i%DX < 269 )) || 
				  	((i >= 229*DX && i < 269*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 229*DX && i < 269*DX) && (i%DX >= 331 && i%DX < 371 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 229 && i%DX < 269 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 331 && i%DX < 371 )) ||
				  	((i >= 331*DX && i < 371*DX) && (i%DX >= 229 && i%DX < 269 )) ||
				  	((i >= 331*DX && i < 371*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 331*DX && i < 371*DX) && (i%DX >= 331 && i%DX < 371 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 11020: // 9 cluster (11path) -->  20x 20x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 259*DX && i < 279*DX) && (i%DX >= 259 && i%DX < 279 )) || 
				  	((i >= 259*DX && i < 279*DX) && (i%DX >= 290 && i%DX < 310 )) ||
				  	((i >= 259*DX && i < 279*DX) && (i%DX >= 321 && i%DX < 341 )) ||
				  	((i >= 290*DX && i < 310*DX) && (i%DX >= 259 && i%DX < 279 )) ||
				  	((i >= 290*DX && i < 310*DX) && (i%DX >= 290 && i%DX < 310 )) ||
				  	((i >= 290*DX && i < 310*DX) && (i%DX >= 321 && i%DX < 341 )) ||
				  	((i >= 321*DX && i < 341*DX) && (i%DX >= 259 && i%DX < 279 )) ||
				  	((i >= 321*DX && i < 341*DX) && (i%DX >= 290 && i%DX < 310 )) ||
				  	((i >= 321*DX && i < 341*DX) && (i%DX >= 321 && i%DX < 341 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 14140: // 9 cluster (14path) --> 120x120x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  76*DX && i < 216*DX) && (i%DX >=  76 && i%DX < 216 )) || 
				  	((i >=  76*DX && i < 216*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >=  76*DX && i < 216*DX) && (i%DX >= 384 && i%DX < 524 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >=  76 && i%DX < 216 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 384 && i%DX < 524 )) ||
				  	((i >= 384*DX && i < 524*DX) && (i%DX >=  76 && i%DX < 216 )) ||
				  	((i >= 384*DX && i < 524*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 384*DX && i < 524*DX) && (i%DX >= 384 && i%DX < 524 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 14132: // 9 cluster (14path) --> 132x132x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  88*DX && i < 220*DX) && (i%DX >=  88 && i%DX < 220 )) || 
				  	((i >=  88*DX && i < 220*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >=  88*DX && i < 220*DX) && (i%DX >= 380 && i%DX < 512 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >=  88 && i%DX < 220 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 380 && i%DX < 512 )) ||
				  	((i >= 380*DX && i < 512*DX) && (i%DX >=  88 && i%DX < 220 )) ||
				  	((i >= 380*DX && i < 512*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 380*DX && i < 512*DX) && (i%DX >= 380 && i%DX < 512 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 14130: // 9 cluster (14path) --> 130x130x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  91*DX && i < 221*DX) && (i%DX >=  91 && i%DX < 221 )) || 
				  	((i >=  91*DX && i < 221*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >=  91*DX && i < 221*DX) && (i%DX >= 379 && i%DX < 509 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >=  91 && i%DX < 221 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 379 && i%DX < 509 )) ||
				  	((i >= 379*DX && i < 509*DX) && (i%DX >=  91 && i%DX < 221 )) ||
				  	((i >= 379*DX && i < 509*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 379*DX && i < 509*DX) && (i%DX >= 379 && i%DX < 509 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 14124: // 9 cluster (14path) --> 124x124x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 224*DX) && (i%DX >= 100 && i%DX < 224 )) || 
				  	((i >= 100*DX && i < 224*DX) && (i%DX >= 238 && i%DX < 362 )) ||
				  	((i >= 100*DX && i < 224*DX) && (i%DX >= 376 && i%DX < 500 )) ||
				  	((i >= 238*DX && i < 362*DX) && (i%DX >= 100 && i%DX < 224 )) ||
				  	((i >= 238*DX && i < 362*DX) && (i%DX >= 238 && i%DX < 362 )) ||
				  	((i >= 238*DX && i < 362*DX) && (i%DX >= 376 && i%DX < 500 )) ||
				  	((i >= 376*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 224 )) ||
				  	((i >= 376*DX && i < 500*DX) && (i%DX >= 238 && i%DX < 362 )) ||
				  	((i >= 376*DX && i < 500*DX) && (i%DX >= 376 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 14122: // 9 cluster (14path) --> 122x122x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 103*DX && i < 225*DX) && (i%DX >= 103 && i%DX < 225 )) || 
				  	((i >= 103*DX && i < 225*DX) && (i%DX >= 239 && i%DX < 361 )) ||
				  	((i >= 103*DX && i < 225*DX) && (i%DX >= 375 && i%DX < 497 )) ||
				  	((i >= 239*DX && i < 361*DX) && (i%DX >= 103 && i%DX < 225 )) ||
				  	((i >= 239*DX && i < 361*DX) && (i%DX >= 239 && i%DX < 361 )) ||
				  	((i >= 239*DX && i < 361*DX) && (i%DX >= 375 && i%DX < 497 )) ||
				  	((i >= 375*DX && i < 497*DX) && (i%DX >= 103 && i%DX < 225 )) ||
				  	((i >= 375*DX && i < 497*DX) && (i%DX >= 239 && i%DX < 361 )) ||
				  	((i >= 375*DX && i < 497*DX) && (i%DX >= 375 && i%DX < 497 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 14120: // 9 cluster (14path) --> 120x120x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 106*DX && i < 226*DX) && (i%DX >= 106 && i%DX < 226 )) || 
				  	((i >= 106*DX && i < 226*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 106*DX && i < 226*DX) && (i%DX >= 374 && i%DX < 494 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 106 && i%DX < 226 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 374 && i%DX < 494 )) ||
				  	((i >= 374*DX && i < 494*DX) && (i%DX >= 106 && i%DX < 226 )) ||
				  	((i >= 374*DX && i < 494*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 374*DX && i < 494*DX) && (i%DX >= 374 && i%DX < 494 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 14110: // 9 cluster (14path) --> 110x110x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 121*DX && i < 231*DX) && (i%DX >= 121 && i%DX < 231 )) || 
				  	((i >= 121*DX && i < 231*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 121*DX && i < 231*DX) && (i%DX >= 369 && i%DX < 479 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 121 && i%DX < 231 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 369 && i%DX < 479 )) ||
				  	((i >= 369*DX && i < 479*DX) && (i%DX >= 121 && i%DX < 231 )) ||
				  	((i >= 369*DX && i < 479*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 369*DX && i < 479*DX) && (i%DX >= 369 && i%DX < 479 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 14108: // 9 cluster (14path) --> 108x108x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 124*DX && i < 232*DX) && (i%DX >= 124 && i%DX < 232 )) || 
				  	((i >= 124*DX && i < 232*DX) && (i%DX >= 246 && i%DX < 354 )) ||
				  	((i >= 124*DX && i < 232*DX) && (i%DX >= 368 && i%DX < 476 )) ||
				  	((i >= 246*DX && i < 354*DX) && (i%DX >= 124 && i%DX < 232 )) ||
				  	((i >= 246*DX && i < 354*DX) && (i%DX >= 246 && i%DX < 354 )) ||
				  	((i >= 246*DX && i < 354*DX) && (i%DX >= 368 && i%DX < 476 )) ||
				  	((i >= 368*DX && i < 476*DX) && (i%DX >= 124 && i%DX < 232 )) ||
				  	((i >= 368*DX && i < 476*DX) && (i%DX >= 246 && i%DX < 354 )) ||
				  	((i >= 368*DX && i < 476*DX) && (i%DX >= 368 && i%DX < 476 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 14106: // 9 cluster (14path) --> 106x106x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 127*DX && i < 233*DX) && (i%DX >= 127 && i%DX < 233 )) || 
				  	((i >= 127*DX && i < 233*DX) && (i%DX >= 247 && i%DX < 353 )) ||
				  	((i >= 127*DX && i < 233*DX) && (i%DX >= 367 && i%DX < 473 )) ||
				  	((i >= 247*DX && i < 353*DX) && (i%DX >= 127 && i%DX < 233 )) ||
				  	((i >= 247*DX && i < 353*DX) && (i%DX >= 247 && i%DX < 353 )) ||
				  	((i >= 247*DX && i < 353*DX) && (i%DX >= 367 && i%DX < 473 )) ||
				  	((i >= 367*DX && i < 473*DX) && (i%DX >= 127 && i%DX < 233 )) ||
				  	((i >= 367*DX && i < 473*DX) && (i%DX >= 247 && i%DX < 353 )) ||
				  	((i >= 367*DX && i < 473*DX) && (i%DX >= 367 && i%DX < 473 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 14104: // 9 cluster (14path) --> 104x104x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 130*DX && i < 234*DX) && (i%DX >= 130 && i%DX < 234 )) || 
				  	((i >= 130*DX && i < 234*DX) && (i%DX >= 248 && i%DX < 352 )) ||
				  	((i >= 130*DX && i < 234*DX) && (i%DX >= 366 && i%DX < 470 )) ||
				  	((i >= 248*DX && i < 352*DX) && (i%DX >= 130 && i%DX < 234 )) ||
				  	((i >= 248*DX && i < 352*DX) && (i%DX >= 248 && i%DX < 352 )) ||
				  	((i >= 248*DX && i < 352*DX) && (i%DX >= 366 && i%DX < 470 )) ||
				  	((i >= 366*DX && i < 470*DX) && (i%DX >= 130 && i%DX < 234 )) ||
				  	((i >= 366*DX && i < 470*DX) && (i%DX >= 248 && i%DX < 352 )) ||
				  	((i >= 366*DX && i < 470*DX) && (i%DX >= 366 && i%DX < 470 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 14102: // 9 cluster (14path) --> 102x102x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 133*DX && i < 235*DX) && (i%DX >= 133 && i%DX < 235 )) || 
				  	((i >= 133*DX && i < 235*DX) && (i%DX >= 249 && i%DX < 351 )) ||
				  	((i >= 133*DX && i < 235*DX) && (i%DX >= 365 && i%DX < 467 )) ||
				  	((i >= 249*DX && i < 351*DX) && (i%DX >= 133 && i%DX < 235 )) ||
				  	((i >= 249*DX && i < 351*DX) && (i%DX >= 249 && i%DX < 351 )) ||
				  	((i >= 249*DX && i < 351*DX) && (i%DX >= 365 && i%DX < 467 )) ||
				  	((i >= 365*DX && i < 467*DX) && (i%DX >= 133 && i%DX < 235 )) ||
				  	((i >= 365*DX && i < 467*DX) && (i%DX >= 249 && i%DX < 351 )) ||
				  	((i >= 365*DX && i < 467*DX) && (i%DX >= 365 && i%DX < 467 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 14100: // 9 cluster (14path) --> 100x100x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 136*DX && i < 236*DX) && (i%DX >= 136 && i%DX < 236 )) || 
				  	((i >= 136*DX && i < 236*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 136*DX && i < 236*DX) && (i%DX >= 364 && i%DX < 464 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 136 && i%DX < 236 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 364 && i%DX < 464 )) ||
				  	((i >= 364*DX && i < 464*DX) && (i%DX >= 136 && i%DX < 236 )) ||
				  	((i >= 364*DX && i < 464*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 364*DX && i < 464*DX) && (i%DX >= 364 && i%DX < 464 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 14090: // 9 cluster (14path) -->  90x 90x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 151*DX && i < 241*DX) && (i%DX >= 151 && i%DX < 241 )) || 
				  	((i >= 151*DX && i < 241*DX) && (i%DX >= 255 && i%DX < 345 )) ||
				  	((i >= 151*DX && i < 241*DX) && (i%DX >= 359 && i%DX < 449 )) ||
				  	((i >= 255*DX && i < 345*DX) && (i%DX >= 151 && i%DX < 241 )) ||
				  	((i >= 255*DX && i < 345*DX) && (i%DX >= 255 && i%DX < 345 )) ||
				  	((i >= 255*DX && i < 345*DX) && (i%DX >= 359 && i%DX < 449 )) ||
				  	((i >= 359*DX && i < 449*DX) && (i%DX >= 151 && i%DX < 241 )) ||
				  	((i >= 359*DX && i < 449*DX) && (i%DX >= 255 && i%DX < 345 )) ||
				  	((i >= 359*DX && i < 449*DX) && (i%DX >= 359 && i%DX < 449 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 14080: // 9 cluster (14path) -->  80x 80x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 166*DX && i < 246*DX) && (i%DX >= 166 && i%DX < 246 )) || 
				  	((i >= 166*DX && i < 246*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 166*DX && i < 246*DX) && (i%DX >= 354 && i%DX < 434 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 166 && i%DX < 246 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 354 && i%DX < 434 )) ||
				  	((i >= 354*DX && i < 434*DX) && (i%DX >= 166 && i%DX < 246 )) ||
				  	((i >= 354*DX && i < 434*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 354*DX && i < 434*DX) && (i%DX >= 354 && i%DX < 434 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 14070: // 9 cluster (14path) -->  70x 70x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 181*DX && i < 251*DX) && (i%DX >= 181 && i%DX < 251 )) || 
				  	((i >= 181*DX && i < 251*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 181*DX && i < 251*DX) && (i%DX >= 349 && i%DX < 419 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 181 && i%DX < 251 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 349 && i%DX < 419 )) ||
				  	((i >= 349*DX && i < 419*DX) && (i%DX >= 181 && i%DX < 251 )) ||
				  	((i >= 349*DX && i < 419*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 349*DX && i < 419*DX) && (i%DX >= 349 && i%DX < 419 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 14060: // 9 cluster (14path) -->  60x 60x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 196*DX && i < 256*DX) && (i%DX >= 196 && i%DX < 256 )) || 
				  	((i >= 196*DX && i < 256*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 196*DX && i < 256*DX) && (i%DX >= 344 && i%DX < 404 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 196 && i%DX < 256 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 344 && i%DX < 404 )) ||
				  	((i >= 344*DX && i < 404*DX) && (i%DX >= 196 && i%DX < 256 )) ||
				  	((i >= 344*DX && i < 404*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 344*DX && i < 404*DX) && (i%DX >= 344 && i%DX < 404 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 14050: // 9 cluster (14path) -->  50x 50x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 211*DX && i < 261*DX) && (i%DX >= 211 && i%DX < 261 )) || 
				  	((i >= 211*DX && i < 261*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 211*DX && i < 261*DX) && (i%DX >= 339 && i%DX < 389 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 211 && i%DX < 261 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 339 && i%DX < 389 )) ||
				  	((i >= 339*DX && i < 389*DX) && (i%DX >= 211 && i%DX < 261 )) ||
				  	((i >= 339*DX && i < 389*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 339*DX && i < 389*DX) && (i%DX >= 339 && i%DX < 389 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17140: // 9 cluster (17path) --> 140x140x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  73*DX && i < 213*DX) && (i%DX >=  73 && i%DX < 213 )) || 
				  	((i >=  73*DX && i < 213*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >=  73*DX && i < 213*DX) && (i%DX >= 387 && i%DX < 527 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >=  73 && i%DX < 213 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 387 && i%DX < 527 )) ||
				  	((i >= 387*DX && i < 527*DX) && (i%DX >=  73 && i%DX < 213 )) ||
				  	((i >= 387*DX && i < 527*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 387*DX && i < 527*DX) && (i%DX >= 387 && i%DX < 527 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17132: // 9 cluster (17path) --> 132x132x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  85*DX && i < 217*DX) && (i%DX >=  85 && i%DX < 217 )) || 
				  	((i >=  85*DX && i < 217*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >=  85*DX && i < 217*DX) && (i%DX >= 383 && i%DX < 515 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >=  85 && i%DX < 217 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 383 && i%DX < 515 )) ||
				  	((i >= 383*DX && i < 515*DX) && (i%DX >=  85 && i%DX < 217 )) ||
				  	((i >= 383*DX && i < 515*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 383*DX && i < 515*DX) && (i%DX >= 383 && i%DX < 515 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17130: // 9 cluster (17path) --> 130x130x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  88*DX && i < 218*DX) && (i%DX >=  88 && i%DX < 218 )) || 
				  	((i >=  88*DX && i < 218*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >=  88*DX && i < 218*DX) && (i%DX >= 382 && i%DX < 512 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >=  88 && i%DX < 218 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 382 && i%DX < 512 )) ||
				  	((i >= 382*DX && i < 512*DX) && (i%DX >=  88 && i%DX < 218 )) ||
				  	((i >= 382*DX && i < 512*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 382*DX && i < 512*DX) && (i%DX >= 382 && i%DX < 512 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17122: // 9 cluster (17path) --> 122x122x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 222*DX) && (i%DX >= 100 && i%DX < 222 )) || 
				  	((i >= 100*DX && i < 222*DX) && (i%DX >= 239 && i%DX < 361 )) ||
				  	((i >= 100*DX && i < 222*DX) && (i%DX >= 378 && i%DX < 500 )) ||
				  	((i >= 239*DX && i < 361*DX) && (i%DX >= 100 && i%DX < 222 )) ||
				  	((i >= 239*DX && i < 361*DX) && (i%DX >= 239 && i%DX < 361 )) ||
				  	((i >= 239*DX && i < 361*DX) && (i%DX >= 378 && i%DX < 500 )) ||
				  	((i >= 378*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 222 )) ||
				  	((i >= 378*DX && i < 500*DX) && (i%DX >= 239 && i%DX < 361 )) ||
				  	((i >= 378*DX && i < 500*DX) && (i%DX >= 378 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17120: // 9 cluster (17path) --> 120x120x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 103*DX && i < 223*DX) && (i%DX >= 103 && i%DX < 223 )) || 
				  	((i >= 103*DX && i < 223*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 103*DX && i < 223*DX) && (i%DX >= 377 && i%DX < 497 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 103 && i%DX < 223 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 377 && i%DX < 497 )) ||
				  	((i >= 377*DX && i < 497*DX) && (i%DX >= 103 && i%DX < 223 )) ||
				  	((i >= 377*DX && i < 497*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 377*DX && i < 497*DX) && (i%DX >= 377 && i%DX < 497 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17118: // 9 cluster (17path) --> 118x118x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 106*DX && i < 224*DX) && (i%DX >= 106 && i%DX < 224 )) || 
				  	((i >= 106*DX && i < 224*DX) && (i%DX >= 241 && i%DX < 359 )) ||
				  	((i >= 106*DX && i < 224*DX) && (i%DX >= 376 && i%DX < 494 )) ||
				  	((i >= 241*DX && i < 359*DX) && (i%DX >= 106 && i%DX < 224 )) ||
				  	((i >= 241*DX && i < 359*DX) && (i%DX >= 241 && i%DX < 359 )) ||
				  	((i >= 241*DX && i < 359*DX) && (i%DX >= 376 && i%DX < 494 )) ||
				  	((i >= 376*DX && i < 494*DX) && (i%DX >= 106 && i%DX < 224 )) ||
				  	((i >= 376*DX && i < 494*DX) && (i%DX >= 241 && i%DX < 359 )) ||
				  	((i >= 376*DX && i < 494*DX) && (i%DX >= 376 && i%DX < 494 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17116: // 9 cluster (17path) --> 116x116x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 109*DX && i < 225*DX) && (i%DX >= 109 && i%DX < 225 )) || 
				  	((i >= 109*DX && i < 225*DX) && (i%DX >= 242 && i%DX < 358 )) ||
				  	((i >= 109*DX && i < 225*DX) && (i%DX >= 375 && i%DX < 491 )) ||
				  	((i >= 242*DX && i < 358*DX) && (i%DX >= 109 && i%DX < 225 )) ||
				  	((i >= 242*DX && i < 358*DX) && (i%DX >= 242 && i%DX < 358 )) ||
				  	((i >= 242*DX && i < 358*DX) && (i%DX >= 375 && i%DX < 491 )) ||
				  	((i >= 375*DX && i < 491*DX) && (i%DX >= 109 && i%DX < 225 )) ||
				  	((i >= 375*DX && i < 491*DX) && (i%DX >= 242 && i%DX < 358 )) ||
				  	((i >= 375*DX && i < 491*DX) && (i%DX >= 375 && i%DX < 491 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17114: // 9 cluster (17path) --> 114x114x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 112*DX && i < 226*DX) && (i%DX >= 112 && i%DX < 226 )) || 
				  	((i >= 112*DX && i < 226*DX) && (i%DX >= 243 && i%DX < 357 )) ||
				  	((i >= 112*DX && i < 226*DX) && (i%DX >= 374 && i%DX < 488 )) ||
				  	((i >= 243*DX && i < 357*DX) && (i%DX >= 112 && i%DX < 226 )) ||
				  	((i >= 243*DX && i < 357*DX) && (i%DX >= 243 && i%DX < 357 )) ||
				  	((i >= 243*DX && i < 357*DX) && (i%DX >= 374 && i%DX < 488 )) ||
				  	((i >= 374*DX && i < 488*DX) && (i%DX >= 112 && i%DX < 226 )) ||
				  	((i >= 374*DX && i < 488*DX) && (i%DX >= 243 && i%DX < 357 )) ||
				  	((i >= 374*DX && i < 488*DX) && (i%DX >= 374 && i%DX < 488 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17112: // 9 cluster (17path) --> 112x112x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 115*DX && i < 227*DX) && (i%DX >= 115 && i%DX < 227 )) || 
				  	((i >= 115*DX && i < 227*DX) && (i%DX >= 244 && i%DX < 356 )) ||
				  	((i >= 115*DX && i < 227*DX) && (i%DX >= 373 && i%DX < 485 )) ||
				  	((i >= 244*DX && i < 356*DX) && (i%DX >= 115 && i%DX < 227 )) ||
				  	((i >= 244*DX && i < 356*DX) && (i%DX >= 244 && i%DX < 356 )) ||
				  	((i >= 244*DX && i < 356*DX) && (i%DX >= 373 && i%DX < 485 )) ||
				  	((i >= 373*DX && i < 485*DX) && (i%DX >= 115 && i%DX < 227 )) ||
				  	((i >= 373*DX && i < 485*DX) && (i%DX >= 244 && i%DX < 356 )) ||
				  	((i >= 373*DX && i < 485*DX) && (i%DX >= 373 && i%DX < 485 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17110: // 9 cluster (17path) --> 110x110x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 118*DX && i < 228*DX) && (i%DX >= 118 && i%DX < 228 )) || 
				  	((i >= 118*DX && i < 228*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 118*DX && i < 228*DX) && (i%DX >= 372 && i%DX < 482 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 118 && i%DX < 228 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 372 && i%DX < 482 )) ||
				  	((i >= 372*DX && i < 482*DX) && (i%DX >= 118 && i%DX < 228 )) ||
				  	((i >= 372*DX && i < 482*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 372*DX && i < 482*DX) && (i%DX >= 372 && i%DX < 482 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17108: // 9 cluster (17path) --> 108x108x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 121*DX && i < 229*DX) && (i%DX >= 121 && i%DX < 229 )) || 
				  	((i >= 121*DX && i < 229*DX) && (i%DX >= 246 && i%DX < 354 )) ||
				  	((i >= 121*DX && i < 229*DX) && (i%DX >= 371 && i%DX < 479 )) ||
				  	((i >= 246*DX && i < 354*DX) && (i%DX >= 121 && i%DX < 229 )) ||
				  	((i >= 246*DX && i < 354*DX) && (i%DX >= 246 && i%DX < 354 )) ||
				  	((i >= 246*DX && i < 354*DX) && (i%DX >= 371 && i%DX < 479 )) ||
				  	((i >= 371*DX && i < 479*DX) && (i%DX >= 121 && i%DX < 229 )) ||
				  	((i >= 371*DX && i < 479*DX) && (i%DX >= 246 && i%DX < 354 )) ||
				  	((i >= 371*DX && i < 479*DX) && (i%DX >= 371 && i%DX < 479 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17106: // 9 cluster (17path) --> 106x106x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 124*DX && i < 230*DX) && (i%DX >= 124 && i%DX < 230 )) || 
				  	((i >= 124*DX && i < 230*DX) && (i%DX >= 247 && i%DX < 353 )) ||
				  	((i >= 124*DX && i < 230*DX) && (i%DX >= 370 && i%DX < 476 )) ||
				  	((i >= 247*DX && i < 353*DX) && (i%DX >= 124 && i%DX < 230 )) ||
				  	((i >= 247*DX && i < 353*DX) && (i%DX >= 247 && i%DX < 353 )) ||
				  	((i >= 247*DX && i < 353*DX) && (i%DX >= 370 && i%DX < 476 )) ||
				  	((i >= 370*DX && i < 476*DX) && (i%DX >= 124 && i%DX < 230 )) ||
				  	((i >= 370*DX && i < 476*DX) && (i%DX >= 247 && i%DX < 353 )) ||
				  	((i >= 370*DX && i < 476*DX) && (i%DX >= 370 && i%DX < 476 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17104: // 9 cluster (17path) --> 104x104x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 127*DX && i < 231*DX) && (i%DX >= 127 && i%DX < 231 )) || 
				  	((i >= 127*DX && i < 231*DX) && (i%DX >= 248 && i%DX < 352 )) ||
				  	((i >= 127*DX && i < 231*DX) && (i%DX >= 369 && i%DX < 473 )) ||
				  	((i >= 248*DX && i < 352*DX) && (i%DX >= 127 && i%DX < 231 )) ||
				  	((i >= 248*DX && i < 352*DX) && (i%DX >= 248 && i%DX < 352 )) ||
				  	((i >= 248*DX && i < 352*DX) && (i%DX >= 369 && i%DX < 473 )) ||
				  	((i >= 369*DX && i < 473*DX) && (i%DX >= 127 && i%DX < 231 )) ||
				  	((i >= 369*DX && i < 473*DX) && (i%DX >= 248 && i%DX < 352 )) ||
				  	((i >= 369*DX && i < 473*DX) && (i%DX >= 369 && i%DX < 473 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17102: // 9 cluster (17path) --> 102x102x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 130*DX && i < 232*DX) && (i%DX >= 130 && i%DX < 232 )) || 
				  	((i >= 130*DX && i < 232*DX) && (i%DX >= 249 && i%DX < 351 )) ||
				  	((i >= 130*DX && i < 232*DX) && (i%DX >= 368 && i%DX < 470 )) ||
				  	((i >= 249*DX && i < 351*DX) && (i%DX >= 130 && i%DX < 232 )) ||
				  	((i >= 249*DX && i < 351*DX) && (i%DX >= 249 && i%DX < 351 )) ||
				  	((i >= 249*DX && i < 351*DX) && (i%DX >= 368 && i%DX < 470 )) ||
				  	((i >= 368*DX && i < 470*DX) && (i%DX >= 130 && i%DX < 232 )) ||
				  	((i >= 368*DX && i < 470*DX) && (i%DX >= 249 && i%DX < 351 )) ||
				  	((i >= 368*DX && i < 470*DX) && (i%DX >= 368 && i%DX < 470 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17100: // 9 cluster (17path) --> 100x100x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 133*DX && i < 233*DX) && (i%DX >= 133 && i%DX < 233 )) || 
				  	((i >= 133*DX && i < 233*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 133*DX && i < 233*DX) && (i%DX >= 367 && i%DX < 467 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 133 && i%DX < 233 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 367 && i%DX < 467 )) ||
				  	((i >= 367*DX && i < 467*DX) && (i%DX >= 133 && i%DX < 233 )) ||
				  	((i >= 367*DX && i < 467*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 367*DX && i < 467*DX) && (i%DX >= 367 && i%DX < 467 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17090: // 9 cluster (17path) -->  90x 90x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 148*DX && i < 238*DX) && (i%DX >= 148 && i%DX < 238 )) || 
				  	((i >= 148*DX && i < 238*DX) && (i%DX >= 255 && i%DX < 345 )) ||
				  	((i >= 148*DX && i < 238*DX) && (i%DX >= 362 && i%DX < 452 )) ||
				  	((i >= 255*DX && i < 345*DX) && (i%DX >= 148 && i%DX < 238 )) ||
				  	((i >= 255*DX && i < 345*DX) && (i%DX >= 255 && i%DX < 345 )) ||
				  	((i >= 255*DX && i < 345*DX) && (i%DX >= 362 && i%DX < 452 )) ||
				  	((i >= 362*DX && i < 452*DX) && (i%DX >= 148 && i%DX < 238 )) ||
				  	((i >= 362*DX && i < 452*DX) && (i%DX >= 255 && i%DX < 345 )) ||
				  	((i >= 362*DX && i < 452*DX) && (i%DX >= 362 && i%DX < 452 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17080: // 9 cluster (17path) -->  80x 80x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 163*DX && i < 243*DX) && (i%DX >= 163 && i%DX < 243 )) || 
				  	((i >= 163*DX && i < 243*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 163*DX && i < 243*DX) && (i%DX >= 357 && i%DX < 437 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 163 && i%DX < 243 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 357 && i%DX < 437 )) ||
				  	((i >= 357*DX && i < 437*DX) && (i%DX >= 163 && i%DX < 243 )) ||
				  	((i >= 357*DX && i < 437*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 357*DX && i < 437*DX) && (i%DX >= 357 && i%DX < 437 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17070: // 9 cluster (17path) -->  70x 70x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 178*DX && i < 248*DX) && (i%DX >= 178 && i%DX < 248 )) || 
				  	((i >= 178*DX && i < 248*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 178*DX && i < 248*DX) && (i%DX >= 352 && i%DX < 422 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 178 && i%DX < 248 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 352 && i%DX < 422 )) ||
				  	((i >= 352*DX && i < 422*DX) && (i%DX >= 178 && i%DX < 248 )) ||
				  	((i >= 352*DX && i < 422*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 352*DX && i < 422*DX) && (i%DX >= 352 && i%DX < 422 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17060: // 9 cluster (17path) -->  60x 60x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 193*DX && i < 253*DX) && (i%DX >= 193 && i%DX < 253 )) || 
				  	((i >= 193*DX && i < 253*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 193*DX && i < 253*DX) && (i%DX >= 347 && i%DX < 407 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 193 && i%DX < 253 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 347 && i%DX < 407 )) ||
				  	((i >= 347*DX && i < 407*DX) && (i%DX >= 193 && i%DX < 253 )) ||
				  	((i >= 347*DX && i < 407*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 347*DX && i < 407*DX) && (i%DX >= 347 && i%DX < 407 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 17050: // 9 cluster (17path) -->  50x 50x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 208*DX && i < 258*DX) && (i%DX >= 208 && i%DX < 258 )) || 
				  	((i >= 208*DX && i < 258*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 208*DX && i < 258*DX) && (i%DX >= 342 && i%DX < 392 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 208 && i%DX < 258 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 342 && i%DX < 392 )) ||
				  	((i >= 342*DX && i < 392*DX) && (i%DX >= 208 && i%DX < 258 )) ||
				  	((i >= 342*DX && i < 392*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 342*DX && i < 392*DX) && (i%DX >= 342 && i%DX < 392 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20120: // 9 cluster (20path) --> 120x120x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 220*DX) && (i%DX >= 100 && i%DX < 220 )) || 
				  	((i >= 100*DX && i < 220*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 100*DX && i < 220*DX) && (i%DX >= 380 && i%DX < 500 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 100 && i%DX < 220 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 380 && i%DX < 500 )) ||
				  	((i >= 380*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 220 )) ||
				  	((i >= 380*DX && i < 500*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 380*DX && i < 500*DX) && (i%DX >= 380 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20118: // 9 cluster (20path) --> 118x118x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 103*DX && i < 221*DX) && (i%DX >= 103 && i%DX < 221 )) || 
				  	((i >= 103*DX && i < 221*DX) && (i%DX >= 241 && i%DX < 359 )) ||
				  	((i >= 103*DX && i < 221*DX) && (i%DX >= 379 && i%DX < 497 )) ||
				  	((i >= 241*DX && i < 359*DX) && (i%DX >= 103 && i%DX < 221 )) ||
				  	((i >= 241*DX && i < 359*DX) && (i%DX >= 241 && i%DX < 359 )) ||
				  	((i >= 241*DX && i < 359*DX) && (i%DX >= 379 && i%DX < 497 )) ||
				  	((i >= 379*DX && i < 497*DX) && (i%DX >= 103 && i%DX < 221 )) ||
				  	((i >= 379*DX && i < 497*DX) && (i%DX >= 241 && i%DX < 359 )) ||
				  	((i >= 379*DX && i < 497*DX) && (i%DX >= 379 && i%DX < 497 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20116: // 9 cluster (20path) --> 116x116x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 106*DX && i < 222*DX) && (i%DX >= 106 && i%DX < 222 )) || 
				  	((i >= 106*DX && i < 222*DX) && (i%DX >= 242 && i%DX < 358 )) ||
				  	((i >= 106*DX && i < 222*DX) && (i%DX >= 378 && i%DX < 494 )) ||
				  	((i >= 242*DX && i < 358*DX) && (i%DX >= 106 && i%DX < 222 )) ||
				  	((i >= 242*DX && i < 358*DX) && (i%DX >= 242 && i%DX < 358 )) ||
				  	((i >= 242*DX && i < 358*DX) && (i%DX >= 378 && i%DX < 494 )) ||
				  	((i >= 378*DX && i < 494*DX) && (i%DX >= 106 && i%DX < 222 )) ||
				  	((i >= 378*DX && i < 494*DX) && (i%DX >= 242 && i%DX < 358 )) ||
				  	((i >= 378*DX && i < 494*DX) && (i%DX >= 378 && i%DX < 494 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20114: // 9 cluster (20path) --> 114x114x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 109*DX && i < 223*DX) && (i%DX >= 109 && i%DX < 223 )) || 
				  	((i >= 109*DX && i < 223*DX) && (i%DX >= 243 && i%DX < 357 )) ||
				  	((i >= 109*DX && i < 223*DX) && (i%DX >= 377 && i%DX < 491 )) ||
				  	((i >= 243*DX && i < 357*DX) && (i%DX >= 109 && i%DX < 223 )) ||
				  	((i >= 243*DX && i < 357*DX) && (i%DX >= 243 && i%DX < 357 )) ||
				  	((i >= 243*DX && i < 357*DX) && (i%DX >= 377 && i%DX < 491 )) ||
				  	((i >= 377*DX && i < 491*DX) && (i%DX >= 109 && i%DX < 223 )) ||
				  	((i >= 377*DX && i < 491*DX) && (i%DX >= 243 && i%DX < 357 )) ||
				  	((i >= 377*DX && i < 491*DX) && (i%DX >= 377 && i%DX < 491 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20112: // 9 cluster (20path) --> 112x112x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 112*DX && i < 224*DX) && (i%DX >= 112 && i%DX < 224 )) || 
				  	((i >= 112*DX && i < 224*DX) && (i%DX >= 244 && i%DX < 356 )) ||
				  	((i >= 112*DX && i < 224*DX) && (i%DX >= 376 && i%DX < 488 )) ||
				  	((i >= 244*DX && i < 356*DX) && (i%DX >= 112 && i%DX < 224 )) ||
				  	((i >= 244*DX && i < 356*DX) && (i%DX >= 244 && i%DX < 356 )) ||
				  	((i >= 244*DX && i < 356*DX) && (i%DX >= 376 && i%DX < 488 )) ||
				  	((i >= 376*DX && i < 488*DX) && (i%DX >= 112 && i%DX < 224 )) ||
				  	((i >= 376*DX && i < 488*DX) && (i%DX >= 244 && i%DX < 356 )) ||
				  	((i >= 376*DX && i < 488*DX) && (i%DX >= 376 && i%DX < 488 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20110: // 9 cluster (20path) --> 110x110x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 115*DX && i < 225*DX) && (i%DX >= 115 && i%DX < 225 )) || 
				  	((i >= 115*DX && i < 225*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 115*DX && i < 225*DX) && (i%DX >= 375 && i%DX < 485 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 115 && i%DX < 225 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 375 && i%DX < 485 )) ||
				  	((i >= 375*DX && i < 485*DX) && (i%DX >= 115 && i%DX < 225 )) ||
				  	((i >= 375*DX && i < 485*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 375*DX && i < 485*DX) && (i%DX >= 375 && i%DX < 485 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20100: // 9 cluster (20path) --> 100x100x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 130*DX && i < 230*DX) && (i%DX >= 130 && i%DX < 230 )) || 
				  	((i >= 130*DX && i < 230*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 130*DX && i < 230*DX) && (i%DX >= 370 && i%DX < 470 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 130 && i%DX < 230 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 370 && i%DX < 470 )) ||
				  	((i >= 370*DX && i < 470*DX) && (i%DX >= 130 && i%DX < 230 )) ||
				  	((i >= 370*DX && i < 470*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 370*DX && i < 470*DX) && (i%DX >= 370 && i%DX < 470 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20132: // 9 cluster (20path) --> 132x132x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  82*DX && i < 214*DX) && (i%DX >=  82 && i%DX < 214 )) || 
				  	((i >=  82*DX && i < 214*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >=  82*DX && i < 214*DX) && (i%DX >= 386 && i%DX < 518 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >=  82 && i%DX < 214 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 386 && i%DX < 518 )) ||
				  	((i >= 386*DX && i < 518*DX) && (i%DX >=  82 && i%DX < 214 )) ||
				  	((i >= 386*DX && i < 518*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 386*DX && i < 518*DX) && (i%DX >= 386 && i%DX < 518 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20130: // 9 cluster (20path) --> 130x130x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  85*DX && i < 215*DX) && (i%DX >=  85 && i%DX < 215 )) || 
				  	((i >=  85*DX && i < 215*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >=  85*DX && i < 215*DX) && (i%DX >= 385 && i%DX < 515 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >=  85 && i%DX < 215 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 385 && i%DX < 515 )) ||
				  	((i >= 385*DX && i < 515*DX) && (i%DX >=  85 && i%DX < 215 )) ||
				  	((i >= 385*DX && i < 515*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 385*DX && i < 515*DX) && (i%DX >= 385 && i%DX < 515 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20140: // 9 cluster (20path) --> 140x140x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  70*DX && i < 210*DX) && (i%DX >=  70 && i%DX < 210 )) || 
				  	((i >=  70*DX && i < 210*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >=  70*DX && i < 210*DX) && (i%DX >= 390 && i%DX < 530 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >=  70 && i%DX < 210 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 390 && i%DX < 530 )) ||
				  	((i >= 390*DX && i < 530*DX) && (i%DX >=  70 && i%DX < 210 )) ||
				  	((i >= 390*DX && i < 530*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 390*DX && i < 530*DX) && (i%DX >= 390 && i%DX < 530 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20150: // 9 cluster (20path) --> 150x150x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  55*DX && i < 205*DX) && (i%DX >=  55 && i%DX < 205 )) || 
				  	((i >=  55*DX && i < 205*DX) && (i%DX >= 225 && i%DX < 375 )) ||
				  	((i >=  55*DX && i < 205*DX) && (i%DX >= 395 && i%DX < 545 )) ||
				  	((i >= 225*DX && i < 375*DX) && (i%DX >=  55 && i%DX < 205 )) ||
				  	((i >= 225*DX && i < 375*DX) && (i%DX >= 225 && i%DX < 375 )) ||
				  	((i >= 225*DX && i < 375*DX) && (i%DX >= 395 && i%DX < 545 )) ||
				  	((i >= 395*DX && i < 545*DX) && (i%DX >=  55 && i%DX < 205 )) ||
				  	((i >= 395*DX && i < 545*DX) && (i%DX >= 225 && i%DX < 375 )) ||
				  	((i >= 395*DX && i < 545*DX) && (i%DX >= 395 && i%DX < 545 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20152: // 9 cluster (20path) --> 152x152x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  52*DX && i < 204*DX) && (i%DX >=  52 && i%DX < 204 )) || 
				  	((i >=  52*DX && i < 204*DX) && (i%DX >= 224 && i%DX < 376 )) ||
				  	((i >=  52*DX && i < 204*DX) && (i%DX >= 396 && i%DX < 548 )) ||
				  	((i >= 224*DX && i < 376*DX) && (i%DX >=  52 && i%DX < 204 )) ||
				  	((i >= 224*DX && i < 376*DX) && (i%DX >= 224 && i%DX < 376 )) ||
				  	((i >= 224*DX && i < 376*DX) && (i%DX >= 396 && i%DX < 548 )) ||
				  	((i >= 396*DX && i < 548*DX) && (i%DX >=  52 && i%DX < 204 )) ||
				  	((i >= 396*DX && i < 548*DX) && (i%DX >= 224 && i%DX < 376 )) ||
				  	((i >= 396*DX && i < 548*DX) && (i%DX >= 396 && i%DX < 548 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 23140: // 9 cluster (23path) 140x140x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  67*DX && i < 207*DX) && (i%DX >=  67 && i%DX < 207 )) || 
				  	((i >=  67*DX && i < 207*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >=  67*DX && i < 207*DX) && (i%DX >= 393 && i%DX < 533 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >=  67 && i%DX < 207 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 393 && i%DX < 533 )) ||
				  	((i >= 393*DX && i < 533*DX) && (i%DX >=  67 && i%DX < 207 )) ||
				  	((i >= 393*DX && i < 533*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 393*DX && i < 533*DX) && (i%DX >= 393 && i%DX < 533 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 23132: // 9 cluster (23path) 132x132x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  79*DX && i < 211*DX) && (i%DX >=  79 && i%DX < 211 )) || 
				  	((i >=  79*DX && i < 211*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >=  79*DX && i < 211*DX) && (i%DX >= 389 && i%DX < 521 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >=  79 && i%DX < 211 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 389 && i%DX < 521 )) ||
				  	((i >= 389*DX && i < 521*DX) && (i%DX >=  79 && i%DX < 211 )) ||
				  	((i >= 389*DX && i < 521*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 389*DX && i < 521*DX) && (i%DX >= 389 && i%DX < 521 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 23130: // 9 cluster (23path) 130x130x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  82*DX && i < 212*DX) && (i%DX >=  82 && i%DX < 212 )) || 
				  	((i >=  82*DX && i < 212*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >=  82*DX && i < 212*DX) && (i%DX >= 388 && i%DX < 518 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >=  82 && i%DX < 212 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 388 && i%DX < 518 )) ||
				  	((i >= 388*DX && i < 518*DX) && (i%DX >=  82 && i%DX < 212 )) ||
				  	((i >= 388*DX && i < 518*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 388*DX && i < 518*DX) && (i%DX >= 388 && i%DX < 518 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 23120: // 9 cluster (23path) 120x120x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  97*DX && i < 217*DX) && (i%DX >=  97 && i%DX < 217 )) || 
				  	((i >=  97*DX && i < 217*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >=  97*DX && i < 217*DX) && (i%DX >= 383 && i%DX < 503 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >=  97 && i%DX < 217 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 383 && i%DX < 503 )) ||
				  	((i >= 383*DX && i < 503*DX) && (i%DX >=  97 && i%DX < 217 )) ||
				  	((i >= 383*DX && i < 503*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 383*DX && i < 503*DX) && (i%DX >= 383 && i%DX < 503 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 23118: // 9 cluster (23path) 118x118x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 218*DX) && (i%DX >= 100 && i%DX < 218 )) || 
				  	((i >= 100*DX && i < 218*DX) && (i%DX >= 241 && i%DX < 359 )) ||
				  	((i >= 100*DX && i < 218*DX) && (i%DX >= 382 && i%DX < 500 )) ||
				  	((i >= 241*DX && i < 359*DX) && (i%DX >= 100 && i%DX < 218 )) ||
				  	((i >= 241*DX && i < 359*DX) && (i%DX >= 241 && i%DX < 359 )) ||
				  	((i >= 241*DX && i < 359*DX) && (i%DX >= 382 && i%DX < 500 )) ||
				  	((i >= 382*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 218 )) ||
				  	((i >= 382*DX && i < 500*DX) && (i%DX >= 241 && i%DX < 359 )) ||
				  	((i >= 382*DX && i < 500*DX) && (i%DX >= 382 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 23110: // 9 cluster (23path) 110x110x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 112*DX && i < 222*DX) && (i%DX >= 112 && i%DX < 222 )) || 
				  	((i >= 112*DX && i < 222*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 112*DX && i < 222*DX) && (i%DX >= 378 && i%DX < 488 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 112 && i%DX < 222 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 378 && i%DX < 488 )) ||
				  	((i >= 378*DX && i < 488*DX) && (i%DX >= 112 && i%DX < 222 )) ||
				  	((i >= 378*DX && i < 488*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 378*DX && i < 488*DX) && (i%DX >= 378 && i%DX < 488 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 23100: // 9 cluster (23path) 100x100x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 127*DX && i < 227*DX) && (i%DX >= 127 && i%DX < 227 )) || 
				  	((i >= 127*DX && i < 227*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 127*DX && i < 227*DX) && (i%DX >= 373 && i%DX < 473 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 127 && i%DX < 227 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 373 && i%DX < 473 )) ||
				  	((i >= 373*DX && i < 473*DX) && (i%DX >= 127 && i%DX < 227 )) ||
				  	((i >= 373*DX && i < 473*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 373*DX && i < 473*DX) && (i%DX >= 373 && i%DX < 473 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 26140: // 9 cluster (26path) --> 140x140x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  64*DX && i < 204*DX) && (i%DX >=  64 && i%DX < 204 )) || 
				  	((i >=  64*DX && i < 204*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >=  64*DX && i < 204*DX) && (i%DX >= 396 && i%DX < 536 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >=  64 && i%DX < 204 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 396 && i%DX < 536 )) ||
				  	((i >= 396*DX && i < 536*DX) && (i%DX >=  64 && i%DX < 204 )) ||
				  	((i >= 396*DX && i < 536*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 396*DX && i < 536*DX) && (i%DX >= 396 && i%DX < 536 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 26132: // 9 cluster (26path) --> 132x132x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  76*DX && i < 208*DX) && (i%DX >=  76 && i%DX < 208 )) || 
				  	((i >=  76*DX && i < 208*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >=  76*DX && i < 208*DX) && (i%DX >= 392 && i%DX < 524 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >=  76 && i%DX < 208 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 392 && i%DX < 524 )) ||
				  	((i >= 392*DX && i < 524*DX) && (i%DX >=  76 && i%DX < 208 )) ||
				  	((i >= 392*DX && i < 524*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 392*DX && i < 524*DX) && (i%DX >= 392 && i%DX < 524 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 26130: // 9 cluster (26path) --> 130x130x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  79*DX && i < 209*DX) && (i%DX >=  79 && i%DX < 209 )) || 
				  	((i >=  79*DX && i < 209*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >=  79*DX && i < 209*DX) && (i%DX >= 391 && i%DX < 521 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >=  79 && i%DX < 209 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 391 && i%DX < 521 )) ||
				  	((i >= 391*DX && i < 521*DX) && (i%DX >=  79 && i%DX < 209 )) ||
				  	((i >= 391*DX && i < 521*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 391*DX && i < 521*DX) && (i%DX >= 391 && i%DX < 521 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 26120: // 9 cluster (26path) --> 120x120x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  94*DX && i < 214*DX) && (i%DX >=  94 && i%DX < 214 )) || 
				  	((i >=  94*DX && i < 214*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >=  94*DX && i < 214*DX) && (i%DX >= 386 && i%DX < 506 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >=  94 && i%DX < 214 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 386 && i%DX < 506 )) ||
				  	((i >= 386*DX && i < 506*DX) && (i%DX >=  94 && i%DX < 214 )) ||
				  	((i >= 386*DX && i < 506*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 386*DX && i < 506*DX) && (i%DX >= 386 && i%DX < 506 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 26116: // 9 cluster (26path) --> 116x116x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 216*DX) && (i%DX >= 100 && i%DX < 216 )) || 
				  	((i >= 100*DX && i < 216*DX) && (i%DX >= 242 && i%DX < 358 )) ||
				  	((i >= 100*DX && i < 216*DX) && (i%DX >= 384 && i%DX < 500 )) ||
				  	((i >= 242*DX && i < 358*DX) && (i%DX >= 100 && i%DX < 216 )) ||
				  	((i >= 242*DX && i < 358*DX) && (i%DX >= 242 && i%DX < 358 )) ||
				  	((i >= 242*DX && i < 358*DX) && (i%DX >= 384 && i%DX < 500 )) ||
				  	((i >= 384*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 216 )) ||
				  	((i >= 384*DX && i < 500*DX) && (i%DX >= 242 && i%DX < 358 )) ||
				  	((i >= 384*DX && i < 500*DX) && (i%DX >= 384 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 26110: // 9 cluster (26path) --> 110x110x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 109*DX && i < 219*DX) && (i%DX >= 109 && i%DX < 219 )) || 
				  	((i >= 109*DX && i < 219*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 109*DX && i < 219*DX) && (i%DX >= 381 && i%DX < 491 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 109 && i%DX < 219 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 381 && i%DX < 491 )) ||
				  	((i >= 381*DX && i < 491*DX) && (i%DX >= 109 && i%DX < 219 )) ||
				  	((i >= 381*DX && i < 491*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 381*DX && i < 491*DX) && (i%DX >= 381 && i%DX < 491 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 26100: // 9 cluster (26path) --> 100x100x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 124*DX && i < 224*DX) && (i%DX >= 124 && i%DX < 224 )) || 
				  	((i >= 124*DX && i < 224*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 124*DX && i < 224*DX) && (i%DX >= 376 && i%DX < 476 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 124 && i%DX < 224 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 376 && i%DX < 476 )) ||
				  	((i >= 376*DX && i < 476*DX) && (i%DX >= 124 && i%DX < 224 )) ||
				  	((i >= 376*DX && i < 476*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 376*DX && i < 476*DX) && (i%DX >= 376 && i%DX < 476 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 29140: // 9 cluster (29path) --> 140x140x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  61*DX && i < 201*DX) && (i%DX >=  61 && i%DX < 201 )) || 
				  	((i >=  61*DX && i < 201*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >=  61*DX && i < 201*DX) && (i%DX >= 399 && i%DX < 539 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >=  61 && i%DX < 201 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 399 && i%DX < 539 )) ||
				  	((i >= 399*DX && i < 539*DX) && (i%DX >=  61 && i%DX < 201 )) ||
				  	((i >= 399*DX && i < 539*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 399*DX && i < 539*DX) && (i%DX >= 399 && i%DX < 539 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 29132: // 9 cluster (29path) --> 132x132x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  73*DX && i < 205*DX) && (i%DX >=  73 && i%DX < 205 )) || 
				  	((i >=  73*DX && i < 205*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >=  73*DX && i < 205*DX) && (i%DX >= 395 && i%DX < 527 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >=  73 && i%DX < 205 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 234*DX && i < 366*DX) && (i%DX >= 395 && i%DX < 527 )) ||
				  	((i >= 395*DX && i < 527*DX) && (i%DX >=  73 && i%DX < 205 )) ||
				  	((i >= 395*DX && i < 527*DX) && (i%DX >= 234 && i%DX < 366 )) ||
				  	((i >= 395*DX && i < 527*DX) && (i%DX >= 395 && i%DX < 527 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 29130: // 9 cluster (29path) --> 130x130x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  76*DX && i < 206*DX) && (i%DX >=  76 && i%DX < 206 )) || 
				  	((i >=  76*DX && i < 206*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >=  76*DX && i < 206*DX) && (i%DX >= 394 && i%DX < 524 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >=  76 && i%DX < 206 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 394 && i%DX < 524 )) ||
				  	((i >= 394*DX && i < 524*DX) && (i%DX >=  76 && i%DX < 206 )) ||
				  	((i >= 394*DX && i < 524*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 394*DX && i < 524*DX) && (i%DX >= 394 && i%DX < 524 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 29120: // 9 cluster (29path) --> 120x120x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  91*DX && i < 211*DX) && (i%DX >=  91 && i%DX < 211 )) || 
				  	((i >=  91*DX && i < 211*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >=  91*DX && i < 211*DX) && (i%DX >= 389 && i%DX < 509 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >=  91 && i%DX < 211 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 389 && i%DX < 509 )) ||
				  	((i >= 389*DX && i < 509*DX) && (i%DX >=  91 && i%DX < 211 )) ||
				  	((i >= 389*DX && i < 509*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 389*DX && i < 509*DX) && (i%DX >= 389 && i%DX < 509 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 29114: // 9 cluster (29path) --> 114x114x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 214*DX) && (i%DX >= 100 && i%DX < 214 )) || 
				  	((i >= 100*DX && i < 214*DX) && (i%DX >= 243 && i%DX < 357 )) ||
				  	((i >= 100*DX && i < 214*DX) && (i%DX >= 386 && i%DX < 500 )) ||
				  	((i >= 243*DX && i < 357*DX) && (i%DX >= 100 && i%DX < 214 )) ||
				  	((i >= 243*DX && i < 357*DX) && (i%DX >= 243 && i%DX < 357 )) ||
				  	((i >= 243*DX && i < 357*DX) && (i%DX >= 386 && i%DX < 500 )) ||
				  	((i >= 386*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 214 )) ||
				  	((i >= 386*DX && i < 500*DX) && (i%DX >= 243 && i%DX < 357 )) ||
				  	((i >= 386*DX && i < 500*DX) && (i%DX >= 386 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 29110: // 9 cluster (29path) --> 110x110x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 106*DX && i < 216*DX) && (i%DX >= 106 && i%DX < 216 )) || 
				  	((i >= 106*DX && i < 216*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 106*DX && i < 216*DX) && (i%DX >= 384 && i%DX < 494 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 106 && i%DX < 216 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 384 && i%DX < 494 )) ||
				  	((i >= 384*DX && i < 494*DX) && (i%DX >= 106 && i%DX < 216 )) ||
				  	((i >= 384*DX && i < 494*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 384*DX && i < 494*DX) && (i%DX >= 384 && i%DX < 494 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 29100: // 9 cluster (29path) --> 100x100x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 121*DX && i < 221*DX) && (i%DX >= 121 && i%DX < 221 )) || 
				  	((i >= 121*DX && i < 221*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 121*DX && i < 221*DX) && (i%DX >= 379 && i%DX < 479 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 121 && i%DX < 221 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 379 && i%DX < 479 )) ||
				  	((i >= 379*DX && i < 479*DX) && (i%DX >= 121 && i%DX < 221 )) ||
				  	((i >= 379*DX && i < 479*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 379*DX && i < 479*DX) && (i%DX >= 379 && i%DX < 479 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 32140: // 9 cluster (32path) --> 140x140x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  58*DX && i < 198*DX) && (i%DX >=  58 && i%DX < 198 )) || 
				  	((i >=  58*DX && i < 198*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >=  58*DX && i < 198*DX) && (i%DX >= 402 && i%DX < 542 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >=  58 && i%DX < 198 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 230*DX && i < 370*DX) && (i%DX >= 402 && i%DX < 542 )) ||
				  	((i >= 402*DX && i < 542*DX) && (i%DX >=  58 && i%DX < 198 )) ||
				  	((i >= 402*DX && i < 542*DX) && (i%DX >= 230 && i%DX < 370 )) ||
				  	((i >= 402*DX && i < 542*DX) && (i%DX >= 402 && i%DX < 542 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 32130: // 9 cluster (32path) --> 130x130x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  73*DX && i < 203*DX) && (i%DX >=  73 && i%DX < 203 )) || 
				  	((i >=  73*DX && i < 203*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >=  73*DX && i < 203*DX) && (i%DX >= 397 && i%DX < 527 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >=  73 && i%DX < 203 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 397 && i%DX < 527 )) ||
				  	((i >= 397*DX && i < 527*DX) && (i%DX >=  73 && i%DX < 203 )) ||
				  	((i >= 397*DX && i < 527*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 397*DX && i < 527*DX) && (i%DX >= 397 && i%DX < 527 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 32120: // 9 cluster (32path) --> 120x120x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  88*DX && i < 208*DX) && (i%DX >=  88 && i%DX < 208 )) || 
				  	((i >=  88*DX && i < 208*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >=  88*DX && i < 208*DX) && (i%DX >= 392 && i%DX < 512 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >=  88 && i%DX < 208 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 392 && i%DX < 512 )) ||
				  	((i >= 392*DX && i < 512*DX) && (i%DX >=  88 && i%DX < 208 )) ||
				  	((i >= 392*DX && i < 512*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 392*DX && i < 512*DX) && (i%DX >= 392 && i%DX < 512 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 32112: // 9 cluster (32path) --> 112x112x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 212*DX) && (i%DX >= 100 && i%DX < 212 )) || 
				  	((i >= 100*DX && i < 212*DX) && (i%DX >= 244 && i%DX < 356 )) ||
				  	((i >= 100*DX && i < 212*DX) && (i%DX >= 388 && i%DX < 500 )) ||
				  	((i >= 244*DX && i < 356*DX) && (i%DX >= 100 && i%DX < 212 )) ||
				  	((i >= 244*DX && i < 356*DX) && (i%DX >= 244 && i%DX < 356 )) ||
				  	((i >= 244*DX && i < 356*DX) && (i%DX >= 388 && i%DX < 500 )) ||
				  	((i >= 388*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 212 )) ||
				  	((i >= 388*DX && i < 500*DX) && (i%DX >= 244 && i%DX < 356 )) ||
				  	((i >= 388*DX && i < 500*DX) && (i%DX >= 388 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 32110: // 9 cluster (32path) --> 110x110x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 103*DX && i < 213*DX) && (i%DX >= 103 && i%DX < 213 )) || 
				  	((i >= 103*DX && i < 213*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 103*DX && i < 213*DX) && (i%DX >= 387 && i%DX < 497 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 103 && i%DX < 213 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 387 && i%DX < 497 )) ||
				  	((i >= 387*DX && i < 497*DX) && (i%DX >= 103 && i%DX < 213 )) ||
				  	((i >= 387*DX && i < 497*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 387*DX && i < 497*DX) && (i%DX >= 387 && i%DX < 497 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 32100: // 9 cluster (32path) --> 100x100x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 118*DX && i < 218*DX) && (i%DX >= 118 && i%DX < 218 )) || 
				  	((i >= 118*DX && i < 218*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 118*DX && i < 218*DX) && (i%DX >= 382 && i%DX < 482 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 118 && i%DX < 218 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 382 && i%DX < 482 )) ||
				  	((i >= 382*DX && i < 482*DX) && (i%DX >= 118 && i%DX < 218 )) ||
				  	((i >= 382*DX && i < 482*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 382*DX && i < 482*DX) && (i%DX >= 382 && i%DX < 482 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 35130: // 9 cluster (35path) --> 130x130x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  70*DX && i < 200*DX) && (i%DX >=  70 && i%DX < 200 )) || 
				  	((i >=  70*DX && i < 200*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >=  70*DX && i < 200*DX) && (i%DX >= 400 && i%DX < 530 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >=  70 && i%DX < 200 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 400 && i%DX < 530 )) ||
				  	((i >= 400*DX && i < 530*DX) && (i%DX >=  70 && i%DX < 200 )) ||
				  	((i >= 400*DX && i < 530*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 400*DX && i < 530*DX) && (i%DX >= 400 && i%DX < 530 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 35120: // 9 cluster (35path) --> 120x120x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  85*DX && i < 205*DX) && (i%DX >=  85 && i%DX < 205 )) || 
				  	((i >=  85*DX && i < 205*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >=  85*DX && i < 205*DX) && (i%DX >= 395 && i%DX < 515 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >=  85 && i%DX < 205 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 395 && i%DX < 515 )) ||
				  	((i >= 395*DX && i < 515*DX) && (i%DX >=  85 && i%DX < 205 )) ||
				  	((i >= 395*DX && i < 515*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 395*DX && i < 515*DX) && (i%DX >= 395 && i%DX < 515 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 35110: // 9 cluster (35path) --> 110x110x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 210*DX) && (i%DX >= 100 && i%DX < 210 )) || 
				  	((i >= 100*DX && i < 210*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 100*DX && i < 210*DX) && (i%DX >= 390 && i%DX < 500 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 100 && i%DX < 210 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 390 && i%DX < 500 )) ||
				  	((i >= 390*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 210 )) ||
				  	((i >= 390*DX && i < 500*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 390*DX && i < 500*DX) && (i%DX >= 390 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 35100: // 9 cluster (35path) --> 100x100x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 115*DX && i < 215*DX) && (i%DX >= 115 && i%DX < 215 )) || 
				  	((i >= 115*DX && i < 215*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 115*DX && i < 215*DX) && (i%DX >= 385 && i%DX < 485 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 115 && i%DX < 215 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 385 && i%DX < 485 )) ||
				  	((i >= 385*DX && i < 485*DX) && (i%DX >= 115 && i%DX < 215 )) ||
				  	((i >= 385*DX && i < 485*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 385*DX && i < 485*DX) && (i%DX >= 385 && i%DX < 485 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 38130: // 9 cluster (38path) --> 130x130x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  67*DX && i < 197*DX) && (i%DX >=  67 && i%DX < 197 )) || 
				  	((i >=  67*DX && i < 197*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >=  67*DX && i < 197*DX) && (i%DX >= 403 && i%DX < 533 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >=  67 && i%DX < 197 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 403 && i%DX < 533 )) ||
				  	((i >= 403*DX && i < 533*DX) && (i%DX >=  67 && i%DX < 197 )) ||
				  	((i >= 403*DX && i < 533*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 403*DX && i < 533*DX) && (i%DX >= 403 && i%DX < 533 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 38120: // 9 cluster (38path) --> 120x120x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  82*DX && i < 202*DX) && (i%DX >=  82 && i%DX < 202 )) || 
				  	((i >=  82*DX && i < 202*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >=  82*DX && i < 202*DX) && (i%DX >= 398 && i%DX < 518 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >=  82 && i%DX < 202 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 398 && i%DX < 518 )) ||
				  	((i >= 398*DX && i < 518*DX) && (i%DX >=  82 && i%DX < 202 )) ||
				  	((i >= 398*DX && i < 518*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 398*DX && i < 518*DX) && (i%DX >= 398 && i%DX < 518 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 38110: // 9 cluster (38path) --> 110x110x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  97*DX && i < 207*DX) && (i%DX >=  97 && i%DX < 207 )) || 
				  	((i >=  97*DX && i < 207*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >=  97*DX && i < 207*DX) && (i%DX >= 393 && i%DX < 503 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >=  97 && i%DX < 207 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 393 && i%DX < 503 )) ||
				  	((i >= 393*DX && i < 503*DX) && (i%DX >=  97 && i%DX < 207 )) ||
				  	((i >= 393*DX && i < 503*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 393*DX && i < 503*DX) && (i%DX >= 393 && i%DX < 503 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 38108: // 9 cluster (38path) --> 108x108x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 208*DX) && (i%DX >= 100 && i%DX < 208 )) || 
				  	((i >= 100*DX && i < 208*DX) && (i%DX >= 246 && i%DX < 354 )) ||
				  	((i >= 100*DX && i < 208*DX) && (i%DX >= 392 && i%DX < 500 )) ||
				  	((i >= 246*DX && i < 354*DX) && (i%DX >= 100 && i%DX < 208 )) ||
				  	((i >= 246*DX && i < 354*DX) && (i%DX >= 246 && i%DX < 354 )) ||
				  	((i >= 246*DX && i < 354*DX) && (i%DX >= 392 && i%DX < 500 )) ||
				  	((i >= 392*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 208 )) ||
				  	((i >= 392*DX && i < 500*DX) && (i%DX >= 246 && i%DX < 354 )) ||
				  	((i >= 392*DX && i < 500*DX) && (i%DX >= 392 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 38100: // 9 cluster (38path) --> 100x100x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 112*DX && i < 212*DX) && (i%DX >= 112 && i%DX < 212 )) || 
				  	((i >= 112*DX && i < 212*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 112*DX && i < 212*DX) && (i%DX >= 388 && i%DX < 488 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 112 && i%DX < 212 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 388 && i%DX < 488 )) ||
				  	((i >= 388*DX && i < 488*DX) && (i%DX >= 112 && i%DX < 212 )) ||
				  	((i >= 388*DX && i < 488*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 388*DX && i < 488*DX) && (i%DX >= 388 && i%DX < 488 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 41130: // 9 cluster (41path) --> 130x130x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  64*DX && i < 194*DX) && (i%DX >=  64 && i%DX < 194 )) || 
				  	((i >=  64*DX && i < 194*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >=  64*DX && i < 194*DX) && (i%DX >= 406 && i%DX < 536 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >=  64 && i%DX < 194 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 406 && i%DX < 536 )) ||
				  	((i >= 406*DX && i < 536*DX) && (i%DX >=  64 && i%DX < 194 )) ||
				  	((i >= 406*DX && i < 536*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 406*DX && i < 536*DX) && (i%DX >= 406 && i%DX < 536 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 41120: // 9 cluster (41path) --> 120x120x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  79*DX && i < 199*DX) && (i%DX >=  79 && i%DX < 199 )) || 
				  	((i >=  79*DX && i < 199*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >=  79*DX && i < 199*DX) && (i%DX >= 401 && i%DX < 521 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >=  79 && i%DX < 199 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 401 && i%DX < 521 )) ||
				  	((i >= 401*DX && i < 521*DX) && (i%DX >=  79 && i%DX < 199 )) ||
				  	((i >= 401*DX && i < 521*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 401*DX && i < 521*DX) && (i%DX >= 401 && i%DX < 521 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 41110: // 9 cluster (41path) --> 110x110x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  94*DX && i < 204*DX) && (i%DX >=  94 && i%DX < 204 )) || 
				  	((i >=  94*DX && i < 204*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >=  94*DX && i < 204*DX) && (i%DX >= 396 && i%DX < 506 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >=  94 && i%DX < 204 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 396 && i%DX < 506 )) ||
				  	((i >= 396*DX && i < 506*DX) && (i%DX >=  94 && i%DX < 204 )) ||
				  	((i >= 396*DX && i < 506*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 396*DX && i < 506*DX) && (i%DX >= 396 && i%DX < 506 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 41106: // 9 cluster (41path) --> 106x106x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 206*DX) && (i%DX >= 100 && i%DX < 206 )) || 
				  	((i >= 100*DX && i < 206*DX) && (i%DX >= 247 && i%DX < 353 )) ||
				  	((i >= 100*DX && i < 206*DX) && (i%DX >= 394 && i%DX < 500 )) ||
				  	((i >= 247*DX && i < 353*DX) && (i%DX >= 100 && i%DX < 206 )) ||
				  	((i >= 247*DX && i < 353*DX) && (i%DX >= 247 && i%DX < 353 )) ||
				  	((i >= 247*DX && i < 353*DX) && (i%DX >= 394 && i%DX < 500 )) ||
				  	((i >= 394*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 206 )) ||
				  	((i >= 394*DX && i < 500*DX) && (i%DX >= 247 && i%DX < 353 )) ||
				  	((i >= 394*DX && i < 500*DX) && (i%DX >= 394 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 41100: // 9 cluster (41path) --> 100x100x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 109*DX && i < 209*DX) && (i%DX >= 109 && i%DX < 209 )) || 
				  	((i >= 109*DX && i < 209*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 109*DX && i < 209*DX) && (i%DX >= 391 && i%DX < 491 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 109 && i%DX < 209 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 391 && i%DX < 491 )) ||
				  	((i >= 391*DX && i < 491*DX) && (i%DX >= 109 && i%DX < 209 )) ||
				  	((i >= 391*DX && i < 491*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 391*DX && i < 491*DX) && (i%DX >= 391 && i%DX < 491 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 44130: // 9 cluster (44path) --> 130x130x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  61*DX && i < 191*DX) && (i%DX >=  61 && i%DX < 191 )) || 
				  	((i >=  61*DX && i < 191*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >=  61*DX && i < 191*DX) && (i%DX >= 409 && i%DX < 539 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >=  61 && i%DX < 191 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 409 && i%DX < 539 )) ||
				  	((i >= 409*DX && i < 539*DX) && (i%DX >=  61 && i%DX < 191 )) ||
				  	((i >= 409*DX && i < 539*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 409*DX && i < 539*DX) && (i%DX >= 409 && i%DX < 539 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 44120: // 9 cluster (44path) --> 120x120x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  76*DX && i < 196*DX) && (i%DX >=  76 && i%DX < 196 )) || 
				  	((i >=  76*DX && i < 196*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >=  76*DX && i < 196*DX) && (i%DX >= 404 && i%DX < 524 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >=  76 && i%DX < 196 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 404 && i%DX < 524 )) ||
				  	((i >= 404*DX && i < 524*DX) && (i%DX >=  76 && i%DX < 196 )) ||
				  	((i >= 404*DX && i < 524*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 404*DX && i < 524*DX) && (i%DX >= 404 && i%DX < 524 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 44110: // 9 cluster (44path) --> 110x110x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  91*DX && i < 201*DX) && (i%DX >=  91 && i%DX < 201 )) || 
				  	((i >=  91*DX && i < 201*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >=  91*DX && i < 201*DX) && (i%DX >= 399 && i%DX < 509 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >=  91 && i%DX < 201 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 399 && i%DX < 509 )) ||
				  	((i >= 399*DX && i < 509*DX) && (i%DX >=  91 && i%DX < 201 )) ||
				  	((i >= 399*DX && i < 509*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 399*DX && i < 509*DX) && (i%DX >= 399 && i%DX < 509 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 44104: // 9 cluster (44path) --> 104x104x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 204*DX) && (i%DX >= 100 && i%DX < 204 )) || 
				  	((i >= 100*DX && i < 204*DX) && (i%DX >= 248 && i%DX < 352 )) ||
				  	((i >= 100*DX && i < 204*DX) && (i%DX >= 396 && i%DX < 500 )) ||
				  	((i >= 248*DX && i < 352*DX) && (i%DX >= 100 && i%DX < 204 )) ||
				  	((i >= 248*DX && i < 352*DX) && (i%DX >= 248 && i%DX < 352 )) ||
				  	((i >= 248*DX && i < 352*DX) && (i%DX >= 396 && i%DX < 500 )) ||
				  	((i >= 396*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 204 )) ||
				  	((i >= 396*DX && i < 500*DX) && (i%DX >= 248 && i%DX < 352 )) ||
				  	((i >= 396*DX && i < 500*DX) && (i%DX >= 396 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 44100: // 9 cluster (44path) --> 100x100x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 106*DX && i < 206*DX) && (i%DX >= 106 && i%DX < 206 )) || 
				  	((i >= 106*DX && i < 206*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 106*DX && i < 206*DX) && (i%DX >= 394 && i%DX < 494 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 106 && i%DX < 206 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 394 && i%DX < 494 )) ||
				  	((i >= 394*DX && i < 494*DX) && (i%DX >= 106 && i%DX < 206 )) ||
				  	((i >= 394*DX && i < 494*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 394*DX && i < 494*DX) && (i%DX >= 394 && i%DX < 494 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 47102: // 9 cluster (47path) --> 102x102x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 202*DX) && (i%DX >= 100 && i%DX < 202 )) || 
				  	((i >= 100*DX && i < 202*DX) && (i%DX >= 249 && i%DX < 351 )) ||
				  	((i >= 100*DX && i < 202*DX) && (i%DX >= 398 && i%DX < 500 )) ||
				  	((i >= 249*DX && i < 351*DX) && (i%DX >= 100 && i%DX < 202 )) ||
				  	((i >= 249*DX && i < 351*DX) && (i%DX >= 249 && i%DX < 351 )) ||
				  	((i >= 249*DX && i < 351*DX) && (i%DX >= 398 && i%DX < 500 )) ||
				  	((i >= 398*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 202 )) ||
				  	((i >= 398*DX && i < 500*DX) && (i%DX >= 249 && i%DX < 351 )) ||
				  	((i >= 398*DX && i < 500*DX) && (i%DX >= 398 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 47123: // 9 cluster (47path) --> 130x130x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  58*DX && i < 188*DX) && (i%DX >=  58 && i%DX < 188 )) || 
				  	((i >=  58*DX && i < 188*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >=  58*DX && i < 188*DX) && (i%DX >= 412 && i%DX < 542 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >=  58 && i%DX < 188 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 412 && i%DX < 542 )) ||
				  	((i >= 412*DX && i < 542*DX) && (i%DX >=  58 && i%DX < 188 )) ||
				  	((i >= 412*DX && i < 542*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 412*DX && i < 542*DX) && (i%DX >= 412 && i%DX < 542 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 47120: // 9 cluster (47path) --> 120x120x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  73*DX && i < 193*DX) && (i%DX >=  73 && i%DX < 193 )) || 
				  	((i >=  73*DX && i < 193*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >=  73*DX && i < 193*DX) && (i%DX >= 407 && i%DX < 527 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >=  73 && i%DX < 193 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 407 && i%DX < 527 )) ||
				  	((i >= 407*DX && i < 527*DX) && (i%DX >=  73 && i%DX < 193 )) ||
				  	((i >= 407*DX && i < 527*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 407*DX && i < 527*DX) && (i%DX >= 407 && i%DX < 527 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 47110: // 9 cluster (47path) --> 110x110x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  88*DX && i < 198*DX) && (i%DX >=  88 && i%DX < 198 )) || 
				  	((i >=  88*DX && i < 198*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >=  88*DX && i < 198*DX) && (i%DX >= 402 && i%DX < 512 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >=  88 && i%DX < 198 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 402 && i%DX < 512 )) ||
				  	((i >= 402*DX && i < 512*DX) && (i%DX >=  88 && i%DX < 198 )) ||
				  	((i >= 402*DX && i < 512*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 402*DX && i < 512*DX) && (i%DX >= 402 && i%DX < 512 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 47100: // 9 cluster (47path) --> 100x100x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 103*DX && i < 203*DX) && (i%DX >= 103 && i%DX < 203 )) || 
				  	((i >= 103*DX && i < 203*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 103*DX && i < 203*DX) && (i%DX >= 397 && i%DX < 497 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 103 && i%DX < 203 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 397 && i%DX < 497 )) ||
				  	((i >= 397*DX && i < 497*DX) && (i%DX >= 103 && i%DX < 203 )) ||
				  	((i >= 397*DX && i < 497*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 397*DX && i < 497*DX) && (i%DX >= 397 && i%DX < 497 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 50130: // 9 cluster (50path) --> 130x130x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  55*DX && i < 185*DX) && (i%DX >=  55 && i%DX < 185 )) || 
				  	((i >=  55*DX && i < 185*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >=  55*DX && i < 185*DX) && (i%DX >= 415 && i%DX < 545 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >=  55 && i%DX < 185 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 235*DX && i < 365*DX) && (i%DX >= 415 && i%DX < 545 )) ||
				  	((i >= 415*DX && i < 545*DX) && (i%DX >=  55 && i%DX < 185 )) ||
				  	((i >= 415*DX && i < 545*DX) && (i%DX >= 235 && i%DX < 365 )) ||
				  	((i >= 415*DX && i < 545*DX) && (i%DX >= 415 && i%DX < 545 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 50120: // 9 cluster (50path) --> 120x120x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  70*DX && i < 190*DX) && (i%DX >=  70 && i%DX < 190 )) || 
				  	((i >=  70*DX && i < 190*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >=  70*DX && i < 190*DX) && (i%DX >= 410 && i%DX < 530 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >=  70 && i%DX < 190 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 240*DX && i < 360*DX) && (i%DX >= 410 && i%DX < 530 )) ||
				  	((i >= 410*DX && i < 530*DX) && (i%DX >=  70 && i%DX < 190 )) ||
				  	((i >= 410*DX && i < 530*DX) && (i%DX >= 240 && i%DX < 360 )) ||
				  	((i >= 410*DX && i < 530*DX) && (i%DX >= 410 && i%DX < 530 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 50110: // 9 cluster (50path) --> 110x110x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  85*DX && i < 195*DX) && (i%DX >=  85 && i%DX < 195 )) || 
				  	((i >=  85*DX && i < 195*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >=  85*DX && i < 195*DX) && (i%DX >= 405 && i%DX < 515 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >=  85 && i%DX < 195 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 245*DX && i < 355*DX) && (i%DX >= 405 && i%DX < 515 )) ||
				  	((i >= 405*DX && i < 515*DX) && (i%DX >=  85 && i%DX < 195 )) ||
				  	((i >= 405*DX && i < 515*DX) && (i%DX >= 245 && i%DX < 355 )) ||
				  	((i >= 405*DX && i < 515*DX) && (i%DX >= 405 && i%DX < 515 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 50100: // 9 cluster (50path) --> 100x100x9
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 200*DX) && (i%DX >= 100 && i%DX < 200 )) || 
				  	((i >= 100*DX && i < 200*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 100*DX && i < 200*DX) && (i%DX >= 400 && i%DX < 500 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 100 && i%DX < 200 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 250*DX && i < 350*DX) && (i%DX >= 400 && i%DX < 500 )) ||
				  	((i >= 400*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 200 )) ||
				  	((i >= 400*DX && i < 500*DX) && (i%DX >= 250 && i%DX < 350 )) ||
				  	((i >= 400*DX && i < 500*DX) && (i%DX >= 400 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;

	}

	// Fast sodium current
		for(i=0;i<MEDIA_SITE;i++){
			Gnaf[i] = 7.8;	// (mS/uF).
		}
		
	// Transient outward current
		pnato = 0.043;
		
		dVgq0= -12.0; //gating variables (q/r) % Endo (from Bernus 2002 model)
		dVgq1 = 0.0; //gating variables (q/r) % Epi (default for Kurata 2005 model)
		dVgq2 = -4.0; //gating variables (q/r) % Mid (from Bernus 2002 model)

		for(i=0;i<MEDIA_SITE;i++){
			if(celltype[i]==0){
				Gto[i] = 0.13;	// Endo (from Bernus 2002 model).
			} else if(celltype[i]==1){
				Gto[i] = 0.4;	// Epi (default for Kurata 2005 model).
			} else if(celltype[i]==2){
				Gto[i] = 0.35;	// Mid (from Bernus 2002 model).
			}
		}

	// L-type calcium current
		kmfca = 0.00035;
		Ecal = 52.8; // (mV)

		for(i=0;i<MEDIA_SITE;i++){
			if(celltype[i] == 0){			// Endo (based on O'Hara-Rudy 2011 model)
				Gca[i] = 0.064*3.9*(1/1.2);
			} else if (celltype[i] == 1){ 	// Epi (Default for Kurata 2005 model)
				Gca[i] = 0.064*3.9;      	
			} else if (celltype[i] == 2){	// Mid (based on O'Hara-Rudy 2011 model)
				Gca[i] = 0.064*3.9*(2.5/1.2);
			}
		}

	// Rapid delayed rectifier potassium current (Ikr)
		for(i=0;i<MEDIA_SITE;i++){
			if(celltype[i] == 0){
				Gkr[i] = 0.012*(1.0/1.3);	//Endo (based on O'Hara-Rudy 2011 model)
			} else if(celltype[i] == 1){
				Gkr[i] = 0.012;  			// Epi (default for Kurata 2005 model)
			} else if(celltype[i] == 2){
				Gkr[i] = 0.012*(0.8/1.3);	// Mid (based on O'Hara-Rudy 2011 model)
			}
		}

		for (i=0;i<MEDIA_SITE;i++){
			gkr_rate[i]=kr_rate;
		}
		printf("gkr_rate[%d]=%lf\n",0,gkr_rate[0]);

	// Slow delayed rectifier potassium current (Iks)
		for(i=0;i<MEDIA_SITE;i++){
			if(celltype[i] == 0){
				Gks[i] = 0.024*1.5*(1.0/1.4);	// Endo (based on O'Hara-Rudy 2011 model)
			} else if(celltype[i] == 1){
				Gks[i] = 0.024*1.5;				// Epi (default for Kurata 2005 model)
			} else if(celltype[i] == 2){
				Gks[i] = 0.024*1.5*(1.0/1.4);	// Mid (based on O'Hara-Rudy 2011 model)
			}
		}	

		for (i=0;i<MEDIA_SITE;i++){
			gks_rate[i]=ks_rate;
		}
		printf("gks_rate[%d]=%lf\n",0,gks_rate[0]);
	
	// Inward rectifier K current: Ik1
		for(i=0;i<MEDIA_SITE;i++){
			if(celltype[i] == 0){
				Gk1[i] = 3.9*(1.0/1.2);		// Endo (based on O'Hara-Rudy 2011 model)
			} else if(celltype[i] == 1){
				Gk1[i] = 3.9;				// Epi (default for Kurata 2005 model)
			} else if(celltype[i] == 2){
				Gk1[i] = 3.9*(1.3/1.2);		// Mid (based on O'Hara-Rudy 2011 model)
			}
		}

	// Sodium-Calcium Exchanger V-S
		kmnaex = 87.5;
		kmcaex = 1.38;
		rncx = 0.35;
		ksat = 0.1;

		for(i=0;i<MEDIA_SITE;i++){
			if(celltype[i] == 0){
				kncx[i] = 1000.0*(1.0/1.1);	// Endo (based on O'Hara-Rudy 2011 model);
			} else {
				kncx[i] = 1000.0;				// Epi (default for Kurata 2005 model) or Mid;
			}
		}
		c1 = 1.0/(pow(kmnaex,3)+pow(Nao,3))/(kmcaex + Cao);

	// Sodium-Potassium Pump
		kmnap = 10.0;
		kmkp = 1.5;
		nna = 1.5;

		for(i=0;i<MEDIA_SITE;i++){
			if(celltype[i] == 0){
				Gnak[i] = 1.3*0.68*(1.0/0.9);	// Endo (based on O'Hara-Rudy 2011 model)
			} else if(celltype[i] == 1){
				Gnak[i] = 1.3*0.68;				// Epi (default for Kurata 2005 model)
			} else if(celltype[i] == 2){
				Gnak[i] = 1.3*0.68;				// Mid (based on O'Hara-Rudy 2011 model)
			}
		}
		rhonak = (exp(Nao/67.3)-1.0)/7.0;

	// Sarcolemmal Ca Pump
		Gpca = 0.275*0.4;		// Max. Ca current through sarcolemmal Ca pump (mS/uF)
		Km_pca = 0.0005;		// Half-saturation concentration of sarcolemmal Ca pump (mM)

	// Ca Background Current 
		Gcab = 0.00085*0.6;	// (cm/s)

	// Na Background Current 
		Gnab = 0.001;

	// SR calcium release flux, via RyR (Jrel)
		nrel = 3.0;
		for(i=0;i<MEDIA_SITE;i++){
			if(celltype[i]!=2){
				Grel[i] = 50.0;	// Epi (default for Kurata 2005 model) or Endo
			} else {
				Grel[i] = 50.0*1.7;	// Mid (based on O'Hara-Rudy 2011 model)
			}
		}
		tau_dr = 1.0*4.0;
		tau_df = 4.0*4.0;

	// calcium uptake via SERCA pump (Jup)
		kup = 0.00025;
		for(i=0;i<MEDIA_SITE;i++){
			if(celltype[i] != 1){
				Gup[i] = 0.000425*5.2*(1.0/1.3);	// Mid or Endo (based on O'Hara-Rudy 2011 model)
			} else {
				Gup[i] = 0.000425*5.2;				// Epi (default for Kurata 2005 model)
			}
		}

	// Translocation of Ca Ions from NSR to JSR
		tau_tr = 180.0;      // Time constant of Ca transfer from NSR to JSR (ms)

	// Ca leakage from SR to Cytoplasm
		pleak = 0.00026;

	//Troponin Ca Buffering (in Myoplasm)
		concTc = 0.07;
		rftn = 10.0;
		kftc = 40.0*rftn;
		kbtc = 0.02*rftn;
		
	//Calmodulin Ca Buffering (in Myoplasm) --- Rapid Buffering Approximation
		for(i=0;i<MEDIA_SITE;i++){
			if(celltype[i] != 1){
				conccm[i] = 0.05*(1.0/1.3);  //% Mid or Endo (based on O'Hara-Rudy 2011 model)
			} else {
				conccm[i] = 0.05;   //% Epi (default for Kurata 2005 model)
			}
		}
		kdcm = 0.00238;	// % Kd for Ca-binding to Calmoduline 

	//Calsequestrin Ca Buffering (in SR) --- Rapid Buffering Approximation	
		conccq = 10.0;     // Max. [Ca] buffered in CSQN (mM)
		kdcq = 0.8;     // % Kd for Ca-binding to Calsequestrin

}

void utype_data(FILE *fp17)
{

	int i,j;

	fprintf(fp17,"%lf ",0.0);
	for (i=0;i<MEDIA_SITE;i++){
		fprintf(fp17,"%d ",utype[i]);
	}
	fprintf(fp17,"\n");

} 

void vm_data(FILE *fp5, double time)
{

	int i,j;

	fprintf(fp5,"%lf ",time);
	for (i=0;i<MEDIA_SITE;i++){
		//fprintf(fp5,"%lf ",var.u[0][i]);
		fprintf(fp5,"%lf ",vmf[0][i]);
	}
	fprintf(fp5,"\n");

} 

void out_data(FILE *fp7, FILE *fp8, FILE *fp9, FILE *fp10, FILE *fp11, FILE *fp12, double time)
{
	int i;

// ikr
	fprintf(fp7,"%lf ",time);
	for (i=0;i<MEDIA_SITE;i++){
		fprintf(fp7,"%lf ",ikr[i]);
	}
	fprintf(fp7,"\n");

// iks
	fprintf(fp8,"%lf ",time);
	for (i=0;i<MEDIA_SITE;i++){
		fprintf(fp8,"%lf ",iks[i]);
	}
	fprintf(fp8,"\n");

// ical
	fprintf(fp9,"%lf ",time);
	for (i=0;i<MEDIA_SITE;i++){
		fprintf(fp9,"%lf ",ical[i]);
	}
	fprintf(fp9,"\n");

// incx
	fprintf(fp10,"%lf ",time);
	for (i=0;i<MEDIA_SITE;i++){
		fprintf(fp10,"%lf ",jncx[i]);
	}
	fprintf(fp10,"\n");

// inak
	fprintf(fp11,"%lf ",time);
	for (i=0;i<MEDIA_SITE;i++){
		fprintf(fp11,"%lf ",inak[i]);
	}
	fprintf(fp11,"\n");

// Cai
	fprintf(fp12,"%lf ",time);
	for (i=0;i<MEDIA_SITE;i++){
		//fprintf(fp12,"%lf ",var.u[12][i]);
		fprintf(fp12,"%lf ",vmf[12][i]);
	}
	fprintf(fp12,"\n");

}

//void out_data_plus(FILE *fp13, FILE *fp14, FILE *fp15, FILE *fp16, double time)
void out_data_plus(FILE *fp13, double time)
{
	int i;

// detailed Vm data
	fprintf(fp13,"%lf ",time);
	for (i=0;i<MEDIA_SITE;i++){
		//fprintf(fp13,"%lf ",var.u[0][i]);
		fprintf(fp13,"%lf ",vmf[0][i]);
	}
	fprintf(fp13,"\n");
/*	
// ito
	fprintf(fp14,"%lf ",time);
	for (i=0;i<MEDIA_SITE;i++){
		fprintf(fp14,"%lf ",ito[i]);
	}
	fprintf(fp14,"\n");

// ik1
	fprintf(fp15,"%lf ",time);
	for (i=0;i<MEDIA_SITE;i++){
		fprintf(fp15,"%lf ",ik1.ik[i]);
	}
	fprintf(fp15,"\n");

// ipca
	fprintf(fp16,"%lf ",time);
	for (i=0;i<MEDIA_SITE;i++){
		fprintf(fp16,"%lf ",ipca.ca[i]);
	}
	fprintf(fp16,"\n");
*/ 
}

void ECG_data(FILE *fp18, double time, double ECG)
{
	fprintf(fp18,"%lf %lf\n",time,ECG);
}
