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
		case 5080: // 25 cluster (5path) --> 80x80x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  90*DX && i < 170*DX) && (i%DX >=  90 && i%DX < 170 )) || 
				  	((i >=  90*DX && i < 170*DX) && (i%DX >= 175 && i%DX < 255 )) ||
				  	((i >=  90*DX && i < 170*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >=  90*DX && i < 170*DX) && (i%DX >= 345 && i%DX < 425 )) ||
				  	((i >=  90*DX && i < 170*DX) && (i%DX >= 430 && i%DX < 510 )) ||
				  	((i >= 175*DX && i < 255*DX) && (i%DX >=  90 && i%DX < 170 )) ||
				  	((i >= 175*DX && i < 255*DX) && (i%DX >= 175 && i%DX < 255 )) ||
				  	((i >= 175*DX && i < 255*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 175*DX && i < 255*DX) && (i%DX >= 345 && i%DX < 425 )) ||
				  	((i >= 175*DX && i < 255*DX) && (i%DX >= 430 && i%DX < 510 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >=  90 && i%DX < 170 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 175 && i%DX < 255 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 345 && i%DX < 425 )) ||
				  	((i >= 260*DX && i < 345*DX) && (i%DX >= 430 && i%DX < 510 )) ||
				  	((i >= 345*DX && i < 425*DX) && (i%DX >=  90 && i%DX < 170 )) ||
				  	((i >= 345*DX && i < 425*DX) && (i%DX >= 175 && i%DX < 255 )) ||
				  	((i >= 345*DX && i < 425*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 345*DX && i < 425*DX) && (i%DX >= 345 && i%DX < 425 )) ||
				  	((i >= 345*DX && i < 425*DX) && (i%DX >= 430 && i%DX < 510 )) ||
				  	((i >= 430*DX && i < 510*DX) && (i%DX >=  90 && i%DX < 170 )) ||
				  	((i >= 430*DX && i < 510*DX) && (i%DX >= 175 && i%DX < 255 )) ||
				  	((i >= 430*DX && i < 510*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 430*DX && i < 510*DX) && (i%DX >= 345 && i%DX < 425 )) ||
				  	((i >= 430*DX && i < 510*DX) && (i%DX >= 430 && i%DX < 510 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5076: // 25 cluster (5path)
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 176*DX) && (i%DX >= 100 && i%DX < 176 )) || 
				  	((i >= 100*DX && i < 176*DX) && (i%DX >= 181 && i%DX < 257 )) ||
				  	((i >= 100*DX && i < 176*DX) && (i%DX >= 262 && i%DX < 338 )) ||
				  	((i >= 100*DX && i < 176*DX) && (i%DX >= 343 && i%DX < 419 )) ||
				  	((i >= 100*DX && i < 176*DX) && (i%DX >= 424 && i%DX < 500 )) ||
				  	((i >= 181*DX && i < 257*DX) && (i%DX >= 100 && i%DX < 176 )) ||
				  	((i >= 181*DX && i < 257*DX) && (i%DX >= 181 && i%DX < 257 )) ||
				  	((i >= 181*DX && i < 257*DX) && (i%DX >= 262 && i%DX < 338 )) ||
				  	((i >= 181*DX && i < 257*DX) && (i%DX >= 343 && i%DX < 419 )) ||
				  	((i >= 181*DX && i < 257*DX) && (i%DX >= 424 && i%DX < 500 )) ||
				  	((i >= 262*DX && i < 338*DX) && (i%DX >= 100 && i%DX < 176 )) ||
				  	((i >= 262*DX && i < 338*DX) && (i%DX >= 181 && i%DX < 257 )) ||
				  	((i >= 262*DX && i < 338*DX) && (i%DX >= 262 && i%DX < 338 )) ||
				  	((i >= 262*DX && i < 338*DX) && (i%DX >= 343 && i%DX < 419 )) ||
				  	((i >= 262*DX && i < 338*DX) && (i%DX >= 424 && i%DX < 500 )) ||
				  	((i >= 343*DX && i < 419*DX) && (i%DX >= 100 && i%DX < 176 )) ||
				  	((i >= 343*DX && i < 419*DX) && (i%DX >= 181 && i%DX < 257 )) ||
				  	((i >= 343*DX && i < 419*DX) && (i%DX >= 262 && i%DX < 338 )) ||
				  	((i >= 343*DX && i < 419*DX) && (i%DX >= 343 && i%DX < 419 )) ||
				  	((i >= 343*DX && i < 419*DX) && (i%DX >= 424 && i%DX < 500 )) ||
				  	((i >= 424*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 176 )) ||
				  	((i >= 424*DX && i < 500*DX) && (i%DX >= 181 && i%DX < 257 )) ||
				  	((i >= 424*DX && i < 500*DX) && (i%DX >= 262 && i%DX < 338 )) ||
				  	((i >= 424*DX && i < 500*DX) && (i%DX >= 343 && i%DX < 419 )) ||
				  	((i >= 424*DX && i < 500*DX) && (i%DX >= 424 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5070: // 25 cluster (5path) --> 70x70x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 115*DX && i < 185*DX) && (i%DX >= 115 && i%DX < 185 )) || 
				  	((i >= 115*DX && i < 185*DX) && (i%DX >= 190 && i%DX < 260 )) ||
				  	((i >= 115*DX && i < 185*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 115*DX && i < 185*DX) && (i%DX >= 340 && i%DX < 410 )) ||
				  	((i >= 115*DX && i < 185*DX) && (i%DX >= 415 && i%DX < 485 )) ||
				  	((i >= 190*DX && i < 260*DX) && (i%DX >= 115 && i%DX < 185 )) ||
				  	((i >= 190*DX && i < 260*DX) && (i%DX >= 190 && i%DX < 260 )) ||
				  	((i >= 190*DX && i < 260*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 190*DX && i < 260*DX) && (i%DX >= 340 && i%DX < 410 )) ||
				  	((i >= 190*DX && i < 260*DX) && (i%DX >= 415 && i%DX < 485 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 115 && i%DX < 185 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 190 && i%DX < 260 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 340 && i%DX < 410 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 415 && i%DX < 485 )) ||
				  	((i >= 340*DX && i < 410*DX) && (i%DX >= 115 && i%DX < 185 )) ||
				  	((i >= 340*DX && i < 410*DX) && (i%DX >= 190 && i%DX < 260 )) ||
				  	((i >= 340*DX && i < 410*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 340*DX && i < 410*DX) && (i%DX >= 340 && i%DX < 410 )) ||
				  	((i >= 340*DX && i < 410*DX) && (i%DX >= 415 && i%DX < 485 )) ||
				  	((i >= 415*DX && i < 485*DX) && (i%DX >= 115 && i%DX < 185 )) ||
				  	((i >= 415*DX && i < 485*DX) && (i%DX >= 190 && i%DX < 260 )) ||
				  	((i >= 415*DX && i < 485*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 415*DX && i < 485*DX) && (i%DX >= 340 && i%DX < 410 )) ||
				  	((i >= 415*DX && i < 485*DX) && (i%DX >= 415 && i%DX < 485 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5060: // 25 cluster (5path) --> 60x60x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 140*DX && i < 200*DX) && (i%DX >= 140 && i%DX < 200 )) || 
				  	((i >= 140*DX && i < 200*DX) && (i%DX >= 205 && i%DX < 265 )) ||
				  	((i >= 140*DX && i < 200*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 140*DX && i < 200*DX) && (i%DX >= 335 && i%DX < 395 )) ||
				  	((i >= 140*DX && i < 200*DX) && (i%DX >= 400 && i%DX < 460 )) ||
				  	((i >= 205*DX && i < 265*DX) && (i%DX >= 140 && i%DX < 200 )) ||
				  	((i >= 205*DX && i < 265*DX) && (i%DX >= 205 && i%DX < 265 )) ||
				  	((i >= 205*DX && i < 265*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 205*DX && i < 265*DX) && (i%DX >= 335 && i%DX < 395 )) ||
				  	((i >= 205*DX && i < 265*DX) && (i%DX >= 400 && i%DX < 460 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 140 && i%DX < 200 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 205 && i%DX < 265 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 335 && i%DX < 395 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 400 && i%DX < 460 )) ||
				  	((i >= 335*DX && i < 395*DX) && (i%DX >= 140 && i%DX < 200 )) ||
				  	((i >= 335*DX && i < 395*DX) && (i%DX >= 205 && i%DX < 265 )) ||
				  	((i >= 335*DX && i < 395*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 335*DX && i < 395*DX) && (i%DX >= 335 && i%DX < 395 )) ||
				  	((i >= 335*DX && i < 395*DX) && (i%DX >= 400 && i%DX < 460 )) ||
				  	((i >= 400*DX && i < 460*DX) && (i%DX >= 140 && i%DX < 200 )) ||
				  	((i >= 400*DX && i < 460*DX) && (i%DX >= 205 && i%DX < 265 )) ||
				  	((i >= 400*DX && i < 460*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 400*DX && i < 460*DX) && (i%DX >= 335 && i%DX < 395 )) ||
				  	((i >= 400*DX && i < 460*DX) && (i%DX >= 400 && i%DX < 460 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5050: // 25 cluster (5path) --> 50x50x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 165*DX && i < 215*DX) && (i%DX >= 165 && i%DX < 215 )) || 
				  	((i >= 165*DX && i < 215*DX) && (i%DX >= 220 && i%DX < 270 )) ||
				  	((i >= 165*DX && i < 215*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 165*DX && i < 215*DX) && (i%DX >= 330 && i%DX < 380 )) ||
				  	((i >= 165*DX && i < 215*DX) && (i%DX >= 385 && i%DX < 435 )) ||
				  	((i >= 220*DX && i < 270*DX) && (i%DX >= 165 && i%DX < 215 )) ||
				  	((i >= 220*DX && i < 270*DX) && (i%DX >= 220 && i%DX < 270 )) ||
				  	((i >= 220*DX && i < 270*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 220*DX && i < 270*DX) && (i%DX >= 330 && i%DX < 380 )) ||
				  	((i >= 220*DX && i < 270*DX) && (i%DX >= 385 && i%DX < 435 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 165 && i%DX < 215 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 220 && i%DX < 270 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 330 && i%DX < 380 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 385 && i%DX < 435 )) ||
				  	((i >= 330*DX && i < 380*DX) && (i%DX >= 165 && i%DX < 215 )) ||
				  	((i >= 330*DX && i < 380*DX) && (i%DX >= 220 && i%DX < 270 )) ||
				  	((i >= 330*DX && i < 380*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 330*DX && i < 380*DX) && (i%DX >= 330 && i%DX < 380 )) ||
				  	((i >= 330*DX && i < 380*DX) && (i%DX >= 385 && i%DX < 435 )) ||
				  	((i >= 385*DX && i < 435*DX) && (i%DX >= 165 && i%DX < 215 )) ||
				  	((i >= 385*DX && i < 435*DX) && (i%DX >= 220 && i%DX < 270 )) ||
				  	((i >= 385*DX && i < 435*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 385*DX && i < 435*DX) && (i%DX >= 330 && i%DX < 380 )) ||
				  	((i >= 385*DX && i < 435*DX) && (i%DX >= 385 && i%DX < 435 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5040: // 25 cluster (5path) --> 40x40x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 190*DX && i < 230*DX) && (i%DX >= 190 && i%DX < 230 )) || 
				  	((i >= 190*DX && i < 230*DX) && (i%DX >= 235 && i%DX < 275 )) ||
				  	((i >= 190*DX && i < 230*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 190*DX && i < 230*DX) && (i%DX >= 325 && i%DX < 365 )) ||
				  	((i >= 190*DX && i < 230*DX) && (i%DX >= 370 && i%DX < 410 )) ||
				  	((i >= 235*DX && i < 275*DX) && (i%DX >= 190 && i%DX < 230 )) ||
				  	((i >= 235*DX && i < 275*DX) && (i%DX >= 235 && i%DX < 275 )) ||
				  	((i >= 235*DX && i < 275*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 235*DX && i < 275*DX) && (i%DX >= 325 && i%DX < 365 )) ||
				  	((i >= 235*DX && i < 275*DX) && (i%DX >= 370 && i%DX < 410 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 190 && i%DX < 230 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 235 && i%DX < 275 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 325 && i%DX < 365 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 370 && i%DX < 410 )) ||
				  	((i >= 325*DX && i < 365*DX) && (i%DX >= 190 && i%DX < 230 )) ||
				  	((i >= 325*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 275 )) ||
				  	((i >= 325*DX && i < 365*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 325*DX && i < 365*DX) && (i%DX >= 325 && i%DX < 365 )) ||
				  	((i >= 325*DX && i < 365*DX) && (i%DX >= 370 && i%DX < 410 )) ||
				  	((i >= 370*DX && i < 410*DX) && (i%DX >= 190 && i%DX < 230 )) ||
				  	((i >= 370*DX && i < 410*DX) && (i%DX >= 235 && i%DX < 275 )) ||
				  	((i >= 370*DX && i < 410*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 370*DX && i < 410*DX) && (i%DX >= 325 && i%DX < 365 )) ||
				  	((i >= 370*DX && i < 410*DX) && (i%DX >= 370 && i%DX < 410 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 10080: // 25 cluster (10path) --> 80x80x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  80*DX && i < 160*DX) && (i%DX >=  80 && i%DX < 160 )) || 
				  	((i >=  80*DX && i < 160*DX) && (i%DX >= 170 && i%DX < 250 )) ||
				  	((i >=  80*DX && i < 160*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >=  80*DX && i < 160*DX) && (i%DX >= 350 && i%DX < 430 )) ||
				  	((i >=  80*DX && i < 160*DX) && (i%DX >= 440 && i%DX < 520 )) ||
				  	((i >= 170*DX && i < 250*DX) && (i%DX >=  80 && i%DX < 160 )) ||
				  	((i >= 170*DX && i < 250*DX) && (i%DX >= 170 && i%DX < 250 )) ||
				  	((i >= 170*DX && i < 250*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 170*DX && i < 250*DX) && (i%DX >= 350 && i%DX < 430 )) ||
				  	((i >= 170*DX && i < 250*DX) && (i%DX >= 440 && i%DX < 520 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >=  80 && i%DX < 160 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 170 && i%DX < 250 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 350 && i%DX < 430 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 440 && i%DX < 520 )) ||
				  	((i >= 350*DX && i < 430*DX) && (i%DX >=  80 && i%DX < 160 )) ||
				  	((i >= 350*DX && i < 430*DX) && (i%DX >= 170 && i%DX < 250 )) ||
				  	((i >= 350*DX && i < 430*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 350*DX && i < 430*DX) && (i%DX >= 350 && i%DX < 430 )) ||
				  	((i >= 350*DX && i < 430*DX) && (i%DX >= 440 && i%DX < 520 )) ||
				  	((i >= 440*DX && i < 520*DX) && (i%DX >=  80 && i%DX < 160 )) ||
				  	((i >= 440*DX && i < 520*DX) && (i%DX >= 170 && i%DX < 250 )) ||
				  	((i >= 440*DX && i < 520*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 440*DX && i < 520*DX) && (i%DX >= 350 && i%DX < 430 )) ||
				  	((i >= 440*DX && i < 520*DX) && (i%DX >= 440 && i%DX < 520 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 10072: // 25 cluster (10path) --> 72x72x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 172*DX) && (i%DX >= 100 && i%DX < 172 )) || 
				  	((i >= 100*DX && i < 172*DX) && (i%DX >= 182 && i%DX < 254 )) ||
				  	((i >= 100*DX && i < 172*DX) && (i%DX >= 264 && i%DX < 336 )) ||
				  	((i >= 100*DX && i < 172*DX) && (i%DX >= 346 && i%DX < 418 )) ||
				  	((i >= 100*DX && i < 172*DX) && (i%DX >= 428 && i%DX < 500 )) ||
				  	((i >= 182*DX && i < 254*DX) && (i%DX >= 100 && i%DX < 172 )) ||
				  	((i >= 182*DX && i < 254*DX) && (i%DX >= 182 && i%DX < 254 )) ||
				  	((i >= 182*DX && i < 254*DX) && (i%DX >= 264 && i%DX < 336 )) ||
				  	((i >= 182*DX && i < 254*DX) && (i%DX >= 346 && i%DX < 418 )) ||
				  	((i >= 182*DX && i < 254*DX) && (i%DX >= 428 && i%DX < 500 )) ||
				  	((i >= 264*DX && i < 336*DX) && (i%DX >= 100 && i%DX < 172 )) ||
				  	((i >= 264*DX && i < 336*DX) && (i%DX >= 182 && i%DX < 254 )) ||
				  	((i >= 264*DX && i < 336*DX) && (i%DX >= 264 && i%DX < 336 )) ||
				  	((i >= 264*DX && i < 336*DX) && (i%DX >= 346 && i%DX < 418 )) ||
				  	((i >= 264*DX && i < 336*DX) && (i%DX >= 428 && i%DX < 500 )) ||
				  	((i >= 346*DX && i < 418*DX) && (i%DX >= 100 && i%DX < 172 )) ||
				  	((i >= 346*DX && i < 418*DX) && (i%DX >= 182 && i%DX < 254 )) ||
				  	((i >= 346*DX && i < 418*DX) && (i%DX >= 264 && i%DX < 336 )) ||
				  	((i >= 346*DX && i < 418*DX) && (i%DX >= 346 && i%DX < 418 )) ||
				  	((i >= 346*DX && i < 418*DX) && (i%DX >= 428 && i%DX < 500 )) ||
				  	((i >= 428*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 172 )) ||
				  	((i >= 428*DX && i < 500*DX) && (i%DX >= 182 && i%DX < 254 )) ||
				  	((i >= 428*DX && i < 500*DX) && (i%DX >= 264 && i%DX < 336 )) ||
				  	((i >= 428*DX && i < 500*DX) && (i%DX >= 346 && i%DX < 418 )) ||
				  	((i >= 428*DX && i < 500*DX) && (i%DX >= 428 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 10070: // 25 cluster (10path) --> 70x70x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 105*DX && i < 175*DX) && (i%DX >= 105 && i%DX < 175 )) || 
				  	((i >= 105*DX && i < 175*DX) && (i%DX >= 185 && i%DX < 255 )) ||
				  	((i >= 105*DX && i < 175*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 105*DX && i < 175*DX) && (i%DX >= 345 && i%DX < 415 )) ||
				  	((i >= 105*DX && i < 175*DX) && (i%DX >= 425 && i%DX < 495 )) ||
				  	((i >= 185*DX && i < 255*DX) && (i%DX >= 105 && i%DX < 175 )) ||
				  	((i >= 185*DX && i < 255*DX) && (i%DX >= 185 && i%DX < 255 )) ||
				  	((i >= 185*DX && i < 255*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 185*DX && i < 255*DX) && (i%DX >= 345 && i%DX < 415 )) ||
				  	((i >= 185*DX && i < 255*DX) && (i%DX >= 425 && i%DX < 495 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 105 && i%DX < 175 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 185 && i%DX < 255 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 345 && i%DX < 415 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 425 && i%DX < 495 )) ||
				  	((i >= 345*DX && i < 415*DX) && (i%DX >= 105 && i%DX < 175 )) ||
				  	((i >= 345*DX && i < 415*DX) && (i%DX >= 185 && i%DX < 255 )) ||
				  	((i >= 345*DX && i < 415*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 345*DX && i < 415*DX) && (i%DX >= 345 && i%DX < 415 )) ||
				  	((i >= 345*DX && i < 415*DX) && (i%DX >= 425 && i%DX < 495 )) ||
				  	((i >= 425*DX && i < 495*DX) && (i%DX >= 105 && i%DX < 175 )) ||
				  	((i >= 425*DX && i < 495*DX) && (i%DX >= 185 && i%DX < 255 )) ||
				  	((i >= 425*DX && i < 495*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 425*DX && i < 495*DX) && (i%DX >= 345 && i%DX < 415 )) ||
				  	((i >= 425*DX && i < 495*DX) && (i%DX >= 425 && i%DX < 495 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 10060: // 25 cluster (10path) --> 60x60x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 130*DX && i < 190*DX) && (i%DX >= 130 && i%DX < 190 )) || 
				  	((i >= 130*DX && i < 190*DX) && (i%DX >= 200 && i%DX < 260 )) ||
				  	((i >= 130*DX && i < 190*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 130*DX && i < 190*DX) && (i%DX >= 340 && i%DX < 400 )) ||
				  	((i >= 130*DX && i < 190*DX) && (i%DX >= 410 && i%DX < 470 )) ||
				  	((i >= 200*DX && i < 260*DX) && (i%DX >= 130 && i%DX < 190 )) ||
				  	((i >= 200*DX && i < 260*DX) && (i%DX >= 200 && i%DX < 260 )) ||
				  	((i >= 200*DX && i < 260*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 200*DX && i < 260*DX) && (i%DX >= 340 && i%DX < 400 )) ||
				  	((i >= 200*DX && i < 260*DX) && (i%DX >= 410 && i%DX < 470 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 130 && i%DX < 190 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 200 && i%DX < 260 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 340 && i%DX < 400 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 410 && i%DX < 470 )) ||
				  	((i >= 340*DX && i < 400*DX) && (i%DX >= 130 && i%DX < 190 )) ||
				  	((i >= 340*DX && i < 400*DX) && (i%DX >= 200 && i%DX < 260 )) ||
				  	((i >= 340*DX && i < 400*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 340*DX && i < 400*DX) && (i%DX >= 340 && i%DX < 400 )) ||
				  	((i >= 340*DX && i < 400*DX) && (i%DX >= 410 && i%DX < 470 )) ||
				  	((i >= 410*DX && i < 470*DX) && (i%DX >= 130 && i%DX < 190 )) ||
				  	((i >= 410*DX && i < 470*DX) && (i%DX >= 200 && i%DX < 260 )) ||
				  	((i >= 410*DX && i < 470*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 410*DX && i < 470*DX) && (i%DX >= 340 && i%DX < 400 )) ||
				  	((i >= 410*DX && i < 470*DX) && (i%DX >= 410 && i%DX < 470 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 10050: // 25 cluster (10path) --> 50x50x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 155*DX && i < 205*DX) && (i%DX >= 155 && i%DX < 205 )) || 
				  	((i >= 155*DX && i < 205*DX) && (i%DX >= 215 && i%DX < 265 )) ||
				  	((i >= 155*DX && i < 205*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 155*DX && i < 205*DX) && (i%DX >= 335 && i%DX < 385 )) ||
				  	((i >= 155*DX && i < 205*DX) && (i%DX >= 395 && i%DX < 445 )) ||
				  	((i >= 215*DX && i < 265*DX) && (i%DX >= 155 && i%DX < 205 )) ||
				  	((i >= 215*DX && i < 265*DX) && (i%DX >= 215 && i%DX < 265 )) ||
				  	((i >= 215*DX && i < 265*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 215*DX && i < 265*DX) && (i%DX >= 335 && i%DX < 385 )) ||
				  	((i >= 215*DX && i < 265*DX) && (i%DX >= 395 && i%DX < 445 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 155 && i%DX < 205 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 215 && i%DX < 265 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 335 && i%DX < 385 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 395 && i%DX < 445 )) ||
				  	((i >= 335*DX && i < 385*DX) && (i%DX >= 155 && i%DX < 205 )) ||
				  	((i >= 335*DX && i < 385*DX) && (i%DX >= 215 && i%DX < 265 )) ||
				  	((i >= 335*DX && i < 385*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 335*DX && i < 385*DX) && (i%DX >= 335 && i%DX < 385 )) ||
				  	((i >= 335*DX && i < 385*DX) && (i%DX >= 395 && i%DX < 445 )) ||
				  	((i >= 395*DX && i < 445*DX) && (i%DX >= 155 && i%DX < 205 )) ||
				  	((i >= 395*DX && i < 445*DX) && (i%DX >= 215 && i%DX < 265 )) ||
				  	((i >= 395*DX && i < 445*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 395*DX && i < 445*DX) && (i%DX >= 335 && i%DX < 385 )) ||
				  	((i >= 395*DX && i < 445*DX) && (i%DX >= 395 && i%DX < 445 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 10040: // 25 cluster (10path) --> 40x40x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 180*DX && i < 220*DX) && (i%DX >= 180 && i%DX < 220 )) || 
				  	((i >= 180*DX && i < 220*DX) && (i%DX >= 230 && i%DX < 270 )) ||
				  	((i >= 180*DX && i < 220*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 180*DX && i < 220*DX) && (i%DX >= 330 && i%DX < 370 )) ||
				  	((i >= 180*DX && i < 220*DX) && (i%DX >= 380 && i%DX < 420 )) ||
				  	((i >= 230*DX && i < 270*DX) && (i%DX >= 180 && i%DX < 220 )) ||
				  	((i >= 230*DX && i < 270*DX) && (i%DX >= 230 && i%DX < 270 )) ||
				  	((i >= 230*DX && i < 270*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 230*DX && i < 270*DX) && (i%DX >= 330 && i%DX < 370 )) ||
				  	((i >= 230*DX && i < 270*DX) && (i%DX >= 380 && i%DX < 420 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 180 && i%DX < 220 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 230 && i%DX < 270 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 330 && i%DX < 370 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 380 && i%DX < 420 )) ||
				  	((i >= 330*DX && i < 370*DX) && (i%DX >= 180 && i%DX < 220 )) ||
				  	((i >= 330*DX && i < 370*DX) && (i%DX >= 230 && i%DX < 270 )) ||
				  	((i >= 330*DX && i < 370*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 330*DX && i < 370*DX) && (i%DX >= 330 && i%DX < 370 )) ||
				  	((i >= 330*DX && i < 370*DX) && (i%DX >= 380 && i%DX < 420 )) ||
				  	((i >= 380*DX && i < 420*DX) && (i%DX >= 180 && i%DX < 220 )) ||
				  	((i >= 380*DX && i < 420*DX) && (i%DX >= 230 && i%DX < 270 )) ||
				  	((i >= 380*DX && i < 420*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 380*DX && i < 420*DX) && (i%DX >= 330 && i%DX < 370 )) ||
				  	((i >= 380*DX && i < 420*DX) && (i%DX >= 380 && i%DX < 420 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 15080: // 25 cluster (15path) --> 80x80x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  70*DX && i < 150*DX) && (i%DX >=  70 && i%DX < 150 )) || 
				  	((i >=  70*DX && i < 150*DX) && (i%DX >= 165 && i%DX < 245 )) ||
				  	((i >=  70*DX && i < 150*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >=  70*DX && i < 150*DX) && (i%DX >= 355 && i%DX < 435 )) ||
				  	((i >=  70*DX && i < 150*DX) && (i%DX >= 450 && i%DX < 530 )) ||
				  	((i >= 165*DX && i < 245*DX) && (i%DX >=  70 && i%DX < 150 )) ||
				  	((i >= 165*DX && i < 245*DX) && (i%DX >= 165 && i%DX < 245 )) ||
				  	((i >= 165*DX && i < 245*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 165*DX && i < 245*DX) && (i%DX >= 355 && i%DX < 435 )) ||
				  	((i >= 165*DX && i < 245*DX) && (i%DX >= 450 && i%DX < 530 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >=  70 && i%DX < 150 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 165 && i%DX < 245 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 355 && i%DX < 435 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 450 && i%DX < 530 )) ||
				  	((i >= 355*DX && i < 435*DX) && (i%DX >=  70 && i%DX < 150 )) ||
				  	((i >= 355*DX && i < 435*DX) && (i%DX >= 165 && i%DX < 245 )) ||
				  	((i >= 355*DX && i < 435*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 355*DX && i < 435*DX) && (i%DX >= 355 && i%DX < 435 )) ||
				  	((i >= 355*DX && i < 435*DX) && (i%DX >= 450 && i%DX < 530 )) ||
				  	((i >= 450*DX && i < 530*DX) && (i%DX >=  70 && i%DX < 150 )) ||
				  	((i >= 450*DX && i < 530*DX) && (i%DX >= 165 && i%DX < 245 )) ||
				  	((i >= 450*DX && i < 530*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 450*DX && i < 530*DX) && (i%DX >= 355 && i%DX < 435 )) ||
				  	((i >= 450*DX && i < 530*DX) && (i%DX >= 450 && i%DX < 530 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 15070: // 25 cluster (15path) --> 70x70x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  95*DX && i < 165*DX) && (i%DX >=  95 && i%DX < 165 )) || 
				  	((i >=  95*DX && i < 165*DX) && (i%DX >= 180 && i%DX < 250 )) ||
				  	((i >=  95*DX && i < 165*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >=  95*DX && i < 165*DX) && (i%DX >= 350 && i%DX < 420 )) ||
				  	((i >=  95*DX && i < 165*DX) && (i%DX >= 435 && i%DX < 505 )) ||
				  	((i >= 180*DX && i < 250*DX) && (i%DX >=  95 && i%DX < 165 )) ||
				  	((i >= 180*DX && i < 250*DX) && (i%DX >= 180 && i%DX < 250 )) ||
				  	((i >= 180*DX && i < 250*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 180*DX && i < 250*DX) && (i%DX >= 350 && i%DX < 420 )) ||
				  	((i >= 180*DX && i < 250*DX) && (i%DX >= 435 && i%DX < 505 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >=  95 && i%DX < 165 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 180 && i%DX < 250 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 350 && i%DX < 420 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 435 && i%DX < 505 )) ||
				  	((i >= 350*DX && i < 420*DX) && (i%DX >=  95 && i%DX < 165 )) ||
				  	((i >= 350*DX && i < 420*DX) && (i%DX >= 180 && i%DX < 250 )) ||
				  	((i >= 350*DX && i < 420*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 350*DX && i < 420*DX) && (i%DX >= 350 && i%DX < 420 )) ||
				  	((i >= 350*DX && i < 420*DX) && (i%DX >= 435 && i%DX < 505 )) ||
				  	((i >= 435*DX && i < 505*DX) && (i%DX >=  95 && i%DX < 165 )) ||
				  	((i >= 435*DX && i < 505*DX) && (i%DX >= 180 && i%DX < 250 )) ||
				  	((i >= 435*DX && i < 505*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 435*DX && i < 505*DX) && (i%DX >= 350 && i%DX < 420 )) ||
				  	((i >= 435*DX && i < 505*DX) && (i%DX >= 435 && i%DX < 505 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 15068: // 25 cluster (15path) --> 68x68x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 168*DX) && (i%DX >= 100 && i%DX < 168 )) || 
				  	((i >= 100*DX && i < 168*DX) && (i%DX >= 183 && i%DX < 251 )) ||
				  	((i >= 100*DX && i < 168*DX) && (i%DX >= 266 && i%DX < 334 )) ||
				  	((i >= 100*DX && i < 168*DX) && (i%DX >= 349 && i%DX < 417 )) ||
				  	((i >= 100*DX && i < 168*DX) && (i%DX >= 432 && i%DX < 500 )) ||
				  	((i >= 183*DX && i < 251*DX) && (i%DX >= 100 && i%DX < 168 )) ||
				  	((i >= 183*DX && i < 251*DX) && (i%DX >= 183 && i%DX < 251 )) ||
				  	((i >= 183*DX && i < 251*DX) && (i%DX >= 266 && i%DX < 334 )) ||
				  	((i >= 183*DX && i < 251*DX) && (i%DX >= 349 && i%DX < 417 )) ||
				  	((i >= 183*DX && i < 251*DX) && (i%DX >= 432 && i%DX < 500 )) ||
				  	((i >= 266*DX && i < 334*DX) && (i%DX >= 100 && i%DX < 168 )) ||
				  	((i >= 266*DX && i < 334*DX) && (i%DX >= 183 && i%DX < 251 )) ||
				  	((i >= 266*DX && i < 334*DX) && (i%DX >= 266 && i%DX < 334 )) ||
				  	((i >= 266*DX && i < 334*DX) && (i%DX >= 349 && i%DX < 417 )) ||
				  	((i >= 266*DX && i < 334*DX) && (i%DX >= 432 && i%DX < 500 )) ||
				  	((i >= 349*DX && i < 417*DX) && (i%DX >= 100 && i%DX < 168 )) ||
				  	((i >= 349*DX && i < 417*DX) && (i%DX >= 183 && i%DX < 251 )) ||
				  	((i >= 349*DX && i < 417*DX) && (i%DX >= 266 && i%DX < 334 )) ||
				  	((i >= 349*DX && i < 417*DX) && (i%DX >= 349 && i%DX < 417 )) ||
				  	((i >= 349*DX && i < 417*DX) && (i%DX >= 432 && i%DX < 500 )) ||
				  	((i >= 432*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 168 )) ||
				  	((i >= 432*DX && i < 500*DX) && (i%DX >= 183 && i%DX < 251 )) ||
				  	((i >= 432*DX && i < 500*DX) && (i%DX >= 266 && i%DX < 334 )) ||
				  	((i >= 432*DX && i < 500*DX) && (i%DX >= 349 && i%DX < 417 )) ||
				  	((i >= 432*DX && i < 500*DX) && (i%DX >= 432 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 15060: // 25 cluster (15path) --> 60x60x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 120*DX && i < 180*DX) && (i%DX >= 120 && i%DX < 180 )) || 
				  	((i >= 120*DX && i < 180*DX) && (i%DX >= 195 && i%DX < 255 )) ||
				  	((i >= 120*DX && i < 180*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 120*DX && i < 180*DX) && (i%DX >= 345 && i%DX < 405 )) ||
				  	((i >= 120*DX && i < 180*DX) && (i%DX >= 420 && i%DX < 480 )) ||
				  	((i >= 195*DX && i < 255*DX) && (i%DX >= 120 && i%DX < 180 )) ||
				  	((i >= 195*DX && i < 255*DX) && (i%DX >= 195 && i%DX < 255 )) ||
				  	((i >= 195*DX && i < 255*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 195*DX && i < 255*DX) && (i%DX >= 345 && i%DX < 405 )) ||
				  	((i >= 195*DX && i < 255*DX) && (i%DX >= 420 && i%DX < 480 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 120 && i%DX < 180 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 195 && i%DX < 255 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 345 && i%DX < 405 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 420 && i%DX < 480 )) ||
				  	((i >= 345*DX && i < 405*DX) && (i%DX >= 120 && i%DX < 180 )) ||
				  	((i >= 345*DX && i < 405*DX) && (i%DX >= 195 && i%DX < 255 )) ||
				  	((i >= 345*DX && i < 405*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 345*DX && i < 405*DX) && (i%DX >= 345 && i%DX < 405 )) ||
				  	((i >= 345*DX && i < 405*DX) && (i%DX >= 420 && i%DX < 480 )) ||
				  	((i >= 420*DX && i < 480*DX) && (i%DX >= 120 && i%DX < 180 )) ||
				  	((i >= 420*DX && i < 480*DX) && (i%DX >= 195 && i%DX < 255 )) ||
				  	((i >= 420*DX && i < 480*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 420*DX && i < 480*DX) && (i%DX >= 345 && i%DX < 405 )) ||
				  	((i >= 420*DX && i < 480*DX) && (i%DX >= 420 && i%DX < 480 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 15050: // 25 cluster (15path) --> 50x50x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 145*DX && i < 195*DX) && (i%DX >= 145 && i%DX < 195 )) || 
				  	((i >= 145*DX && i < 195*DX) && (i%DX >= 210 && i%DX < 260 )) ||
				  	((i >= 145*DX && i < 195*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 145*DX && i < 195*DX) && (i%DX >= 340 && i%DX < 390 )) ||
				  	((i >= 145*DX && i < 195*DX) && (i%DX >= 405 && i%DX < 455 )) ||
				  	((i >= 210*DX && i < 260*DX) && (i%DX >= 145 && i%DX < 195 )) ||
				  	((i >= 210*DX && i < 260*DX) && (i%DX >= 210 && i%DX < 260 )) ||
				  	((i >= 210*DX && i < 260*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 210*DX && i < 260*DX) && (i%DX >= 340 && i%DX < 390 )) ||
				  	((i >= 210*DX && i < 260*DX) && (i%DX >= 405 && i%DX < 455 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 145 && i%DX < 195 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 210 && i%DX < 260 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 340 && i%DX < 390 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 405 && i%DX < 455 )) ||
				  	((i >= 340*DX && i < 390*DX) && (i%DX >= 145 && i%DX < 195 )) ||
				  	((i >= 340*DX && i < 390*DX) && (i%DX >= 210 && i%DX < 260 )) ||
				  	((i >= 340*DX && i < 390*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 340*DX && i < 390*DX) && (i%DX >= 340 && i%DX < 390 )) ||
				  	((i >= 340*DX && i < 390*DX) && (i%DX >= 405 && i%DX < 455 )) ||
				  	((i >= 405*DX && i < 455*DX) && (i%DX >= 145 && i%DX < 195 )) ||
				  	((i >= 405*DX && i < 455*DX) && (i%DX >= 210 && i%DX < 260 )) ||
				  	((i >= 405*DX && i < 455*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 405*DX && i < 455*DX) && (i%DX >= 340 && i%DX < 390 )) ||
				  	((i >= 405*DX && i < 455*DX) && (i%DX >= 405 && i%DX < 455 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 15040: // 25 cluster (15path) --> 40x40x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 170*DX && i < 210*DX) && (i%DX >= 170 && i%DX < 210 )) || 
				  	((i >= 170*DX && i < 210*DX) && (i%DX >= 225 && i%DX < 265 )) ||
				  	((i >= 170*DX && i < 210*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 170*DX && i < 210*DX) && (i%DX >= 335 && i%DX < 375 )) ||
				  	((i >= 170*DX && i < 210*DX) && (i%DX >= 390 && i%DX < 430 )) ||
				  	((i >= 225*DX && i < 265*DX) && (i%DX >= 170 && i%DX < 210 )) ||
				  	((i >= 225*DX && i < 265*DX) && (i%DX >= 225 && i%DX < 265 )) ||
				  	((i >= 225*DX && i < 265*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 225*DX && i < 265*DX) && (i%DX >= 335 && i%DX < 375 )) ||
				  	((i >= 225*DX && i < 265*DX) && (i%DX >= 390 && i%DX < 430 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 170 && i%DX < 210 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 225 && i%DX < 265 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 335 && i%DX < 375 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 390 && i%DX < 430 )) ||
				  	((i >= 335*DX && i < 375*DX) && (i%DX >= 170 && i%DX < 210 )) ||
				  	((i >= 335*DX && i < 375*DX) && (i%DX >= 225 && i%DX < 265 )) ||
				  	((i >= 335*DX && i < 375*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 335*DX && i < 375*DX) && (i%DX >= 335 && i%DX < 375 )) ||
				  	((i >= 335*DX && i < 375*DX) && (i%DX >= 390 && i%DX < 430 )) ||
				  	((i >= 390*DX && i < 430*DX) && (i%DX >= 170 && i%DX < 210 )) ||
				  	((i >= 390*DX && i < 430*DX) && (i%DX >= 225 && i%DX < 265 )) ||
				  	((i >= 390*DX && i < 430*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 390*DX && i < 430*DX) && (i%DX >= 335 && i%DX < 375 )) ||
				  	((i >= 390*DX && i < 430*DX) && (i%DX >= 390 && i%DX < 430 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20080: // 25 cluster (20path) --> 80x80x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  60*DX && i < 140*DX) && (i%DX >=  60 && i%DX < 140 )) || 
				  	((i >=  60*DX && i < 140*DX) && (i%DX >= 160 && i%DX < 240 )) ||
				  	((i >=  60*DX && i < 140*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >=  60*DX && i < 140*DX) && (i%DX >= 360 && i%DX < 440 )) ||
				  	((i >=  60*DX && i < 140*DX) && (i%DX >= 460 && i%DX < 540 )) ||
				  	((i >= 160*DX && i < 240*DX) && (i%DX >=  60 && i%DX < 140 )) ||
				  	((i >= 160*DX && i < 240*DX) && (i%DX >= 160 && i%DX < 240 )) ||
				  	((i >= 160*DX && i < 240*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 160*DX && i < 240*DX) && (i%DX >= 360 && i%DX < 440 )) ||
				  	((i >= 160*DX && i < 240*DX) && (i%DX >= 460 && i%DX < 540 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >=  60 && i%DX < 140 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 160 && i%DX < 240 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 360 && i%DX < 440 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 460 && i%DX < 540 )) ||
				  	((i >= 360*DX && i < 440*DX) && (i%DX >=  60 && i%DX < 140 )) ||
				  	((i >= 360*DX && i < 440*DX) && (i%DX >= 160 && i%DX < 240 )) ||
				  	((i >= 360*DX && i < 440*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 360*DX && i < 440*DX) && (i%DX >= 360 && i%DX < 440 )) ||
				  	((i >= 360*DX && i < 440*DX) && (i%DX >= 460 && i%DX < 540 )) ||
				  	((i >= 460*DX && i < 540*DX) && (i%DX >=  60 && i%DX < 140 )) ||
				  	((i >= 460*DX && i < 540*DX) && (i%DX >= 160 && i%DX < 240 )) ||
				  	((i >= 460*DX && i < 540*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 460*DX && i < 540*DX) && (i%DX >= 360 && i%DX < 440 )) ||
				  	((i >= 460*DX && i < 540*DX) && (i%DX >= 460 && i%DX < 540 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20070: // 25 cluster (20path) --> 70x70x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  85*DX && i < 155*DX) && (i%DX >=  85 && i%DX < 155 )) || 
				  	((i >=  85*DX && i < 155*DX) && (i%DX >= 175 && i%DX < 245 )) ||
				  	((i >=  85*DX && i < 155*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >=  85*DX && i < 155*DX) && (i%DX >= 355 && i%DX < 425 )) ||
				  	((i >=  85*DX && i < 155*DX) && (i%DX >= 445 && i%DX < 515 )) ||
				  	((i >= 175*DX && i < 245*DX) && (i%DX >=  85 && i%DX < 155 )) ||
				  	((i >= 175*DX && i < 245*DX) && (i%DX >= 175 && i%DX < 245 )) ||
				  	((i >= 175*DX && i < 245*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 175*DX && i < 245*DX) && (i%DX >= 355 && i%DX < 425 )) ||
				  	((i >= 175*DX && i < 245*DX) && (i%DX >= 445 && i%DX < 515 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >=  85 && i%DX < 155 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 175 && i%DX < 245 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 355 && i%DX < 425 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 445 && i%DX < 515 )) ||
				  	((i >= 355*DX && i < 425*DX) && (i%DX >=  85 && i%DX < 155 )) ||
				  	((i >= 355*DX && i < 425*DX) && (i%DX >= 175 && i%DX < 245 )) ||
				  	((i >= 355*DX && i < 425*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 355*DX && i < 425*DX) && (i%DX >= 355 && i%DX < 425 )) ||
				  	((i >= 355*DX && i < 425*DX) && (i%DX >= 445 && i%DX < 515 )) ||
				  	((i >= 445*DX && i < 515*DX) && (i%DX >=  85 && i%DX < 155 )) ||
				  	((i >= 445*DX && i < 515*DX) && (i%DX >= 175 && i%DX < 245 )) ||
				  	((i >= 445*DX && i < 515*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 445*DX && i < 515*DX) && (i%DX >= 355 && i%DX < 425 )) ||
				  	((i >= 445*DX && i < 515*DX) && (i%DX >= 445 && i%DX < 515 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20064: // 25 cluster (20path) --> 64x64x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 164*DX) && (i%DX >= 100 && i%DX < 164 )) || 
				  	((i >= 100*DX && i < 164*DX) && (i%DX >= 184 && i%DX < 248 )) ||
				  	((i >= 100*DX && i < 164*DX) && (i%DX >= 268 && i%DX < 332 )) ||
				  	((i >= 100*DX && i < 164*DX) && (i%DX >= 352 && i%DX < 416 )) ||
				  	((i >= 100*DX && i < 164*DX) && (i%DX >= 436 && i%DX < 500 )) ||
				  	((i >= 184*DX && i < 248*DX) && (i%DX >= 100 && i%DX < 164 )) ||
				  	((i >= 184*DX && i < 248*DX) && (i%DX >= 184 && i%DX < 248 )) ||
				  	((i >= 184*DX && i < 248*DX) && (i%DX >= 268 && i%DX < 332 )) ||
				  	((i >= 184*DX && i < 248*DX) && (i%DX >= 352 && i%DX < 416 )) ||
				  	((i >= 184*DX && i < 248*DX) && (i%DX >= 436 && i%DX < 500 )) ||
				  	((i >= 268*DX && i < 332*DX) && (i%DX >= 100 && i%DX < 164 )) ||
				  	((i >= 268*DX && i < 332*DX) && (i%DX >= 184 && i%DX < 248 )) ||
				  	((i >= 268*DX && i < 332*DX) && (i%DX >= 268 && i%DX < 332 )) ||
				  	((i >= 268*DX && i < 332*DX) && (i%DX >= 352 && i%DX < 416 )) ||
				  	((i >= 268*DX && i < 332*DX) && (i%DX >= 436 && i%DX < 500 )) ||
				  	((i >= 352*DX && i < 416*DX) && (i%DX >= 100 && i%DX < 164 )) ||
				  	((i >= 352*DX && i < 416*DX) && (i%DX >= 184 && i%DX < 248 )) ||
				  	((i >= 352*DX && i < 416*DX) && (i%DX >= 268 && i%DX < 332 )) ||
				  	((i >= 352*DX && i < 416*DX) && (i%DX >= 352 && i%DX < 416 )) ||
				  	((i >= 352*DX && i < 416*DX) && (i%DX >= 436 && i%DX < 500 )) ||
				  	((i >= 436*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 164 )) ||
				  	((i >= 436*DX && i < 500*DX) && (i%DX >= 184 && i%DX < 248 )) ||
				  	((i >= 436*DX && i < 500*DX) && (i%DX >= 268 && i%DX < 332 )) ||
				  	((i >= 436*DX && i < 500*DX) && (i%DX >= 352 && i%DX < 416 )) ||
				  	((i >= 436*DX && i < 500*DX) && (i%DX >= 436 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20060: // 25 cluster (20path) --> 60x60x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 110*DX && i < 170*DX) && (i%DX >= 110 && i%DX < 170 )) || 
				  	((i >= 110*DX && i < 170*DX) && (i%DX >= 190 && i%DX < 250 )) ||
				  	((i >= 110*DX && i < 170*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 110*DX && i < 170*DX) && (i%DX >= 350 && i%DX < 410 )) ||
				  	((i >= 110*DX && i < 170*DX) && (i%DX >= 430 && i%DX < 490 )) ||
				  	((i >= 190*DX && i < 250*DX) && (i%DX >= 110 && i%DX < 170 )) ||
				  	((i >= 190*DX && i < 250*DX) && (i%DX >= 190 && i%DX < 250 )) ||
				  	((i >= 190*DX && i < 250*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 190*DX && i < 250*DX) && (i%DX >= 350 && i%DX < 410 )) ||
				  	((i >= 190*DX && i < 250*DX) && (i%DX >= 430 && i%DX < 490 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 110 && i%DX < 170 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 190 && i%DX < 250 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 350 && i%DX < 410 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 430 && i%DX < 490 )) ||
				  	((i >= 350*DX && i < 410*DX) && (i%DX >= 110 && i%DX < 170 )) ||
				  	((i >= 350*DX && i < 410*DX) && (i%DX >= 190 && i%DX < 250 )) ||
				  	((i >= 350*DX && i < 410*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 350*DX && i < 410*DX) && (i%DX >= 350 && i%DX < 410 )) ||
				  	((i >= 350*DX && i < 410*DX) && (i%DX >= 430 && i%DX < 490 )) ||
				  	((i >= 430*DX && i < 490*DX) && (i%DX >= 110 && i%DX < 170 )) ||
				  	((i >= 430*DX && i < 490*DX) && (i%DX >= 190 && i%DX < 250 )) ||
				  	((i >= 430*DX && i < 490*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 430*DX && i < 490*DX) && (i%DX >= 350 && i%DX < 410 )) ||
				  	((i >= 430*DX && i < 490*DX) && (i%DX >= 430 && i%DX < 490 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20050: // 25 cluster (20path) --> 50x50x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 135*DX && i < 185*DX) && (i%DX >= 135 && i%DX < 185 )) || 
				  	((i >= 135*DX && i < 185*DX) && (i%DX >= 205 && i%DX < 255 )) ||
				  	((i >= 135*DX && i < 185*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 135*DX && i < 185*DX) && (i%DX >= 345 && i%DX < 395 )) ||
				  	((i >= 135*DX && i < 185*DX) && (i%DX >= 415 && i%DX < 465 )) ||
				  	((i >= 205*DX && i < 255*DX) && (i%DX >= 135 && i%DX < 185 )) ||
				  	((i >= 205*DX && i < 255*DX) && (i%DX >= 205 && i%DX < 255 )) ||
				  	((i >= 205*DX && i < 255*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 205*DX && i < 255*DX) && (i%DX >= 345 && i%DX < 395 )) ||
				  	((i >= 205*DX && i < 255*DX) && (i%DX >= 415 && i%DX < 465 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 135 && i%DX < 185 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 205 && i%DX < 255 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 345 && i%DX < 395 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 415 && i%DX < 465 )) ||
				  	((i >= 345*DX && i < 395*DX) && (i%DX >= 135 && i%DX < 185 )) ||
				  	((i >= 345*DX && i < 395*DX) && (i%DX >= 205 && i%DX < 255 )) ||
				  	((i >= 345*DX && i < 395*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 345*DX && i < 395*DX) && (i%DX >= 345 && i%DX < 395 )) ||
				  	((i >= 345*DX && i < 395*DX) && (i%DX >= 415 && i%DX < 465 )) ||
				  	((i >= 415*DX && i < 465*DX) && (i%DX >= 135 && i%DX < 185 )) ||
				  	((i >= 415*DX && i < 465*DX) && (i%DX >= 205 && i%DX < 255 )) ||
				  	((i >= 415*DX && i < 465*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 415*DX && i < 465*DX) && (i%DX >= 345 && i%DX < 395 )) ||
				  	((i >= 415*DX && i < 465*DX) && (i%DX >= 415 && i%DX < 465 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20040: // 25 cluster (20path) --> 40x40x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 160*DX && i < 200*DX) && (i%DX >= 160 && i%DX < 200 )) || 
				  	((i >= 160*DX && i < 200*DX) && (i%DX >= 220 && i%DX < 260 )) ||
				  	((i >= 160*DX && i < 200*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 160*DX && i < 200*DX) && (i%DX >= 340 && i%DX < 380 )) ||
				  	((i >= 160*DX && i < 200*DX) && (i%DX >= 400 && i%DX < 440 )) ||
				  	((i >= 220*DX && i < 260*DX) && (i%DX >= 160 && i%DX < 200 )) ||
				  	((i >= 220*DX && i < 260*DX) && (i%DX >= 220 && i%DX < 260 )) ||
				  	((i >= 220*DX && i < 260*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 220*DX && i < 260*DX) && (i%DX >= 340 && i%DX < 380 )) ||
				  	((i >= 220*DX && i < 260*DX) && (i%DX >= 400 && i%DX < 440 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 160 && i%DX < 200 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 220 && i%DX < 260 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 340 && i%DX < 380 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 400 && i%DX < 440 )) ||
				  	((i >= 340*DX && i < 380*DX) && (i%DX >= 160 && i%DX < 200 )) ||
				  	((i >= 340*DX && i < 380*DX) && (i%DX >= 220 && i%DX < 260 )) ||
				  	((i >= 340*DX && i < 380*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 340*DX && i < 380*DX) && (i%DX >= 340 && i%DX < 380 )) ||
				  	((i >= 340*DX && i < 380*DX) && (i%DX >= 400 && i%DX < 440 )) ||
				  	((i >= 400*DX && i < 440*DX) && (i%DX >= 160 && i%DX < 200 )) ||
				  	((i >= 400*DX && i < 440*DX) && (i%DX >= 220 && i%DX < 260 )) ||
				  	((i >= 400*DX && i < 440*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 400*DX && i < 440*DX) && (i%DX >= 340 && i%DX < 380 )) ||
				  	((i >= 400*DX && i < 440*DX) && (i%DX >= 400 && i%DX < 440 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 25080: // 25 cluster (25path) --> 80x80x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  50*DX && i < 130*DX) && (i%DX >=  50 && i%DX < 130 )) || 
				  	((i >=  50*DX && i < 130*DX) && (i%DX >= 155 && i%DX < 235 )) ||
				  	((i >=  50*DX && i < 130*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >=  50*DX && i < 130*DX) && (i%DX >= 365 && i%DX < 445 )) ||
				  	((i >=  50*DX && i < 130*DX) && (i%DX >= 470 && i%DX < 550 )) ||
				  	((i >= 155*DX && i < 235*DX) && (i%DX >=  50 && i%DX < 130 )) ||
				  	((i >= 155*DX && i < 235*DX) && (i%DX >= 155 && i%DX < 235 )) ||
				  	((i >= 155*DX && i < 235*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 155*DX && i < 235*DX) && (i%DX >= 365 && i%DX < 445 )) ||
				  	((i >= 155*DX && i < 235*DX) && (i%DX >= 470 && i%DX < 550 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >=  50 && i%DX < 130 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 155 && i%DX < 235 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 365 && i%DX < 445 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 470 && i%DX < 550 )) ||
				  	((i >= 365*DX && i < 445*DX) && (i%DX >=  50 && i%DX < 130 )) ||
				  	((i >= 365*DX && i < 445*DX) && (i%DX >= 155 && i%DX < 235 )) ||
				  	((i >= 365*DX && i < 445*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 365*DX && i < 445*DX) && (i%DX >= 365 && i%DX < 445 )) ||
				  	((i >= 365*DX && i < 445*DX) && (i%DX >= 470 && i%DX < 550 )) ||
				  	((i >= 470*DX && i < 550*DX) && (i%DX >=  50 && i%DX < 130 )) ||
				  	((i >= 470*DX && i < 550*DX) && (i%DX >= 155 && i%DX < 235 )) ||
				  	((i >= 470*DX && i < 550*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 470*DX && i < 550*DX) && (i%DX >= 365 && i%DX < 445 )) ||
				  	((i >= 470*DX && i < 550*DX) && (i%DX >= 470 && i%DX < 550 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 25070: // 25 cluster (25path) --> 70x70x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  75*DX && i < 145*DX) && (i%DX >=  75 && i%DX < 145 )) || 
				  	((i >=  75*DX && i < 145*DX) && (i%DX >= 170 && i%DX < 240 )) ||
				  	((i >=  75*DX && i < 145*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >=  75*DX && i < 145*DX) && (i%DX >= 360 && i%DX < 430 )) ||
				  	((i >=  75*DX && i < 145*DX) && (i%DX >= 455 && i%DX < 525 )) ||
				  	((i >= 170*DX && i < 240*DX) && (i%DX >=  75 && i%DX < 145 )) ||
				  	((i >= 170*DX && i < 240*DX) && (i%DX >= 170 && i%DX < 240 )) ||
				  	((i >= 170*DX && i < 240*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 170*DX && i < 240*DX) && (i%DX >= 360 && i%DX < 430 )) ||
				  	((i >= 170*DX && i < 240*DX) && (i%DX >= 455 && i%DX < 525 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >=  75 && i%DX < 145 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 170 && i%DX < 240 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 360 && i%DX < 430 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 455 && i%DX < 525 )) ||
				  	((i >= 360*DX && i < 430*DX) && (i%DX >=  75 && i%DX < 145 )) ||
				  	((i >= 360*DX && i < 430*DX) && (i%DX >= 170 && i%DX < 240 )) ||
				  	((i >= 360*DX && i < 430*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 360*DX && i < 430*DX) && (i%DX >= 360 && i%DX < 430 )) ||
				  	((i >= 360*DX && i < 430*DX) && (i%DX >= 455 && i%DX < 525 )) ||
				  	((i >= 455*DX && i < 525*DX) && (i%DX >=  75 && i%DX < 145 )) ||
				  	((i >= 455*DX && i < 525*DX) && (i%DX >= 170 && i%DX < 240 )) ||
				  	((i >= 455*DX && i < 525*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 455*DX && i < 525*DX) && (i%DX >= 360 && i%DX < 430 )) ||
				  	((i >= 455*DX && i < 525*DX) && (i%DX >= 455 && i%DX < 525 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 25060: // 25 cluster (25path) --> 60x60x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 160*DX) && (i%DX >= 100 && i%DX < 160 )) || 
				  	((i >= 100*DX && i < 160*DX) && (i%DX >= 185 && i%DX < 245 )) ||
				  	((i >= 100*DX && i < 160*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 100*DX && i < 160*DX) && (i%DX >= 355 && i%DX < 415 )) ||
				  	((i >= 100*DX && i < 160*DX) && (i%DX >= 440 && i%DX < 500 )) ||
				  	((i >= 185*DX && i < 245*DX) && (i%DX >= 100 && i%DX < 160 )) ||
				  	((i >= 185*DX && i < 245*DX) && (i%DX >= 185 && i%DX < 245 )) ||
				  	((i >= 185*DX && i < 245*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 185*DX && i < 245*DX) && (i%DX >= 355 && i%DX < 415 )) ||
				  	((i >= 185*DX && i < 245*DX) && (i%DX >= 440 && i%DX < 500 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 100 && i%DX < 160 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 185 && i%DX < 245 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 355 && i%DX < 415 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 440 && i%DX < 500 )) ||
				  	((i >= 355*DX && i < 415*DX) && (i%DX >= 100 && i%DX < 160 )) ||
				  	((i >= 355*DX && i < 415*DX) && (i%DX >= 185 && i%DX < 245 )) ||
				  	((i >= 355*DX && i < 415*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 355*DX && i < 415*DX) && (i%DX >= 355 && i%DX < 415 )) ||
				  	((i >= 355*DX && i < 415*DX) && (i%DX >= 440 && i%DX < 500 )) ||
				  	((i >= 440*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 160 )) ||
				  	((i >= 440*DX && i < 500*DX) && (i%DX >= 185 && i%DX < 245 )) ||
				  	((i >= 440*DX && i < 500*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 440*DX && i < 500*DX) && (i%DX >= 355 && i%DX < 415 )) ||
				  	((i >= 440*DX && i < 500*DX) && (i%DX >= 440 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 25050: // 25 cluster (25path) --> 50x50x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 125*DX && i < 175*DX) && (i%DX >= 125 && i%DX < 175 )) || 
				  	((i >= 125*DX && i < 175*DX) && (i%DX >= 200 && i%DX < 250 )) ||
				  	((i >= 125*DX && i < 175*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 125*DX && i < 175*DX) && (i%DX >= 350 && i%DX < 400 )) ||
				  	((i >= 125*DX && i < 175*DX) && (i%DX >= 425 && i%DX < 475 )) ||
				  	((i >= 200*DX && i < 250*DX) && (i%DX >= 125 && i%DX < 175 )) ||
				  	((i >= 200*DX && i < 250*DX) && (i%DX >= 200 && i%DX < 250 )) ||
				  	((i >= 200*DX && i < 250*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 200*DX && i < 250*DX) && (i%DX >= 350 && i%DX < 400 )) ||
				  	((i >= 200*DX && i < 250*DX) && (i%DX >= 425 && i%DX < 475 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 125 && i%DX < 175 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 200 && i%DX < 250 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 350 && i%DX < 400 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 425 && i%DX < 475 )) ||
				  	((i >= 350*DX && i < 400*DX) && (i%DX >= 125 && i%DX < 175 )) ||
				  	((i >= 350*DX && i < 400*DX) && (i%DX >= 200 && i%DX < 250 )) ||
				  	((i >= 350*DX && i < 400*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 350*DX && i < 400*DX) && (i%DX >= 350 && i%DX < 400 )) ||
				  	((i >= 350*DX && i < 400*DX) && (i%DX >= 425 && i%DX < 475 )) ||
				  	((i >= 425*DX && i < 475*DX) && (i%DX >= 125 && i%DX < 175 )) ||
				  	((i >= 425*DX && i < 475*DX) && (i%DX >= 200 && i%DX < 250 )) ||
				  	((i >= 425*DX && i < 475*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 425*DX && i < 475*DX) && (i%DX >= 350 && i%DX < 400 )) ||
				  	((i >= 425*DX && i < 475*DX) && (i%DX >= 425 && i%DX < 475 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 25040: // 25 cluster (25path) --> 40x40x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 150*DX && i < 190*DX) && (i%DX >= 150 && i%DX < 190 )) || 
				  	((i >= 150*DX && i < 190*DX) && (i%DX >= 215 && i%DX < 255 )) ||
				  	((i >= 150*DX && i < 190*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 150*DX && i < 190*DX) && (i%DX >= 345 && i%DX < 385 )) ||
				  	((i >= 150*DX && i < 190*DX) && (i%DX >= 410 && i%DX < 450 )) ||
				  	((i >= 215*DX && i < 255*DX) && (i%DX >= 150 && i%DX < 190 )) ||
				  	((i >= 215*DX && i < 255*DX) && (i%DX >= 215 && i%DX < 255 )) ||
				  	((i >= 215*DX && i < 255*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 215*DX && i < 255*DX) && (i%DX >= 345 && i%DX < 385 )) ||
				  	((i >= 215*DX && i < 255*DX) && (i%DX >= 410 && i%DX < 450 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 150 && i%DX < 190 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 215 && i%DX < 255 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 345 && i%DX < 385 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 410 && i%DX < 450 )) ||
				  	((i >= 345*DX && i < 385*DX) && (i%DX >= 150 && i%DX < 190 )) ||
				  	((i >= 345*DX && i < 385*DX) && (i%DX >= 215 && i%DX < 255 )) ||
				  	((i >= 345*DX && i < 385*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 345*DX && i < 385*DX) && (i%DX >= 345 && i%DX < 385 )) ||
				  	((i >= 345*DX && i < 385*DX) && (i%DX >= 410 && i%DX < 450 )) ||
				  	((i >= 410*DX && i < 450*DX) && (i%DX >= 150 && i%DX < 190 )) ||
				  	((i >= 410*DX && i < 450*DX) && (i%DX >= 215 && i%DX < 255 )) ||
				  	((i >= 410*DX && i < 450*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 410*DX && i < 450*DX) && (i%DX >= 345 && i%DX < 385 )) ||
				  	((i >= 410*DX && i < 450*DX) && (i%DX >= 410 && i%DX < 450 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 30080: // 25 cluster (30path) --> 80x80x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  40*DX && i < 120*DX) && (i%DX >=  40 && i%DX < 120 )) || 
				  	((i >=  40*DX && i < 120*DX) && (i%DX >= 150 && i%DX < 230 )) ||
				  	((i >=  40*DX && i < 120*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >=  40*DX && i < 120*DX) && (i%DX >= 370 && i%DX < 450 )) ||
				  	((i >=  40*DX && i < 120*DX) && (i%DX >= 480 && i%DX < 560 )) ||
				  	((i >= 150*DX && i < 230*DX) && (i%DX >=  40 && i%DX < 120 )) ||
				  	((i >= 150*DX && i < 230*DX) && (i%DX >= 150 && i%DX < 230 )) ||
				  	((i >= 150*DX && i < 230*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 150*DX && i < 230*DX) && (i%DX >= 370 && i%DX < 450 )) ||
				  	((i >= 150*DX && i < 230*DX) && (i%DX >= 480 && i%DX < 560 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >=  40 && i%DX < 120 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 150 && i%DX < 230 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 370 && i%DX < 450 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 480 && i%DX < 560 )) ||
				  	((i >= 370*DX && i < 450*DX) && (i%DX >=  40 && i%DX < 120 )) ||
				  	((i >= 370*DX && i < 450*DX) && (i%DX >= 150 && i%DX < 230 )) ||
				  	((i >= 370*DX && i < 450*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 370*DX && i < 450*DX) && (i%DX >= 370 && i%DX < 450 )) ||
				  	((i >= 370*DX && i < 450*DX) && (i%DX >= 480 && i%DX < 560 )) ||
				  	((i >= 480*DX && i < 560*DX) && (i%DX >=  40 && i%DX < 120 )) ||
				  	((i >= 480*DX && i < 560*DX) && (i%DX >= 150 && i%DX < 230 )) ||
				  	((i >= 480*DX && i < 560*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 480*DX && i < 560*DX) && (i%DX >= 370 && i%DX < 450 )) ||
				  	((i >= 480*DX && i < 560*DX) && (i%DX >= 480 && i%DX < 560 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 30070: // 25 cluster (30path) --> 70x70x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  65*DX && i < 135*DX) && (i%DX >=  65 && i%DX < 135 )) || 
				  	((i >=  65*DX && i < 135*DX) && (i%DX >= 165 && i%DX < 235 )) ||
				  	((i >=  65*DX && i < 135*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >=  65*DX && i < 135*DX) && (i%DX >= 365 && i%DX < 435 )) ||
				  	((i >=  65*DX && i < 135*DX) && (i%DX >= 465 && i%DX < 535 )) ||
				  	((i >= 165*DX && i < 235*DX) && (i%DX >=  65 && i%DX < 135 )) ||
				  	((i >= 165*DX && i < 235*DX) && (i%DX >= 165 && i%DX < 235 )) ||
				  	((i >= 165*DX && i < 235*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 165*DX && i < 235*DX) && (i%DX >= 365 && i%DX < 435 )) ||
				  	((i >= 165*DX && i < 235*DX) && (i%DX >= 465 && i%DX < 535 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >=  65 && i%DX < 135 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 165 && i%DX < 235 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 365 && i%DX < 435 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 465 && i%DX < 535 )) ||
				  	((i >= 365*DX && i < 435*DX) && (i%DX >=  65 && i%DX < 135 )) ||
				  	((i >= 365*DX && i < 435*DX) && (i%DX >= 165 && i%DX < 235 )) ||
				  	((i >= 365*DX && i < 435*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 365*DX && i < 435*DX) && (i%DX >= 365 && i%DX < 435 )) ||
				  	((i >= 365*DX && i < 435*DX) && (i%DX >= 465 && i%DX < 535 )) ||
				  	((i >= 465*DX && i < 535*DX) && (i%DX >=  65 && i%DX < 135 )) ||
				  	((i >= 465*DX && i < 535*DX) && (i%DX >= 165 && i%DX < 235 )) ||
				  	((i >= 465*DX && i < 535*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 465*DX && i < 535*DX) && (i%DX >= 365 && i%DX < 435 )) ||
				  	((i >= 465*DX && i < 535*DX) && (i%DX >= 465 && i%DX < 535 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 30060: // 25 cluster (30path) --> 60x60x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  90*DX && i < 150*DX) && (i%DX >=  90 && i%DX < 150 )) || 
				  	((i >=  90*DX && i < 150*DX) && (i%DX >= 180 && i%DX < 240 )) ||
				  	((i >=  90*DX && i < 150*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >=  90*DX && i < 150*DX) && (i%DX >= 360 && i%DX < 420 )) ||
				  	((i >=  90*DX && i < 150*DX) && (i%DX >= 450 && i%DX < 510 )) ||
				  	((i >= 180*DX && i < 240*DX) && (i%DX >=  90 && i%DX < 150 )) ||
				  	((i >= 180*DX && i < 240*DX) && (i%DX >= 180 && i%DX < 240 )) ||
				  	((i >= 180*DX && i < 240*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 180*DX && i < 240*DX) && (i%DX >= 360 && i%DX < 420 )) ||
				  	((i >= 180*DX && i < 240*DX) && (i%DX >= 450 && i%DX < 510 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >=  90 && i%DX < 150 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 180 && i%DX < 240 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 360 && i%DX < 420 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 450 && i%DX < 510 )) ||
				  	((i >= 360*DX && i < 420*DX) && (i%DX >=  90 && i%DX < 150 )) ||
				  	((i >= 360*DX && i < 420*DX) && (i%DX >= 180 && i%DX < 240 )) ||
				  	((i >= 360*DX && i < 420*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 360*DX && i < 420*DX) && (i%DX >= 360 && i%DX < 420 )) ||
				  	((i >= 360*DX && i < 420*DX) && (i%DX >= 450 && i%DX < 510 )) ||
				  	((i >= 450*DX && i < 510*DX) && (i%DX >=  90 && i%DX < 150 )) ||
				  	((i >= 450*DX && i < 510*DX) && (i%DX >= 180 && i%DX < 240 )) ||
				  	((i >= 450*DX && i < 510*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 450*DX && i < 510*DX) && (i%DX >= 360 && i%DX < 420 )) ||
				  	((i >= 450*DX && i < 510*DX) && (i%DX >= 450 && i%DX < 510 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 30056: // 25 cluster (30path) --> 56x56x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 156*DX) && (i%DX >= 100 && i%DX < 156 )) || 
				  	((i >= 100*DX && i < 156*DX) && (i%DX >= 186 && i%DX < 242 )) ||
				  	((i >= 100*DX && i < 156*DX) && (i%DX >= 272 && i%DX < 328 )) ||
				  	((i >= 100*DX && i < 156*DX) && (i%DX >= 358 && i%DX < 414 )) ||
				  	((i >= 100*DX && i < 156*DX) && (i%DX >= 444 && i%DX < 500 )) ||
				  	((i >= 186*DX && i < 242*DX) && (i%DX >= 100 && i%DX < 156 )) ||
				  	((i >= 186*DX && i < 242*DX) && (i%DX >= 186 && i%DX < 242 )) ||
				  	((i >= 186*DX && i < 242*DX) && (i%DX >= 272 && i%DX < 328 )) ||
				  	((i >= 186*DX && i < 242*DX) && (i%DX >= 358 && i%DX < 414 )) ||
				  	((i >= 186*DX && i < 242*DX) && (i%DX >= 444 && i%DX < 500 )) ||
				  	((i >= 272*DX && i < 328*DX) && (i%DX >= 100 && i%DX < 156 )) ||
				  	((i >= 272*DX && i < 328*DX) && (i%DX >= 186 && i%DX < 242 )) ||
				  	((i >= 272*DX && i < 328*DX) && (i%DX >= 272 && i%DX < 328 )) ||
				  	((i >= 272*DX && i < 328*DX) && (i%DX >= 358 && i%DX < 414 )) ||
				  	((i >= 272*DX && i < 328*DX) && (i%DX >= 444 && i%DX < 500 )) ||
				  	((i >= 358*DX && i < 414*DX) && (i%DX >= 100 && i%DX < 156 )) ||
				  	((i >= 358*DX && i < 414*DX) && (i%DX >= 186 && i%DX < 242 )) ||
				  	((i >= 358*DX && i < 414*DX) && (i%DX >= 272 && i%DX < 328 )) ||
				  	((i >= 358*DX && i < 414*DX) && (i%DX >= 358 && i%DX < 414 )) ||
				  	((i >= 358*DX && i < 414*DX) && (i%DX >= 444 && i%DX < 500 )) ||
				  	((i >= 444*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 156 )) ||
				  	((i >= 444*DX && i < 500*DX) && (i%DX >= 186 && i%DX < 242 )) ||
				  	((i >= 444*DX && i < 500*DX) && (i%DX >= 272 && i%DX < 328 )) ||
				  	((i >= 444*DX && i < 500*DX) && (i%DX >= 358 && i%DX < 414 )) ||
				  	((i >= 444*DX && i < 500*DX) && (i%DX >= 444 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 30050: // 25 cluster (30path) --> 50x50x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 115*DX && i < 165*DX) && (i%DX >= 115 && i%DX < 165 )) || 
				  	((i >= 115*DX && i < 165*DX) && (i%DX >= 195 && i%DX < 245 )) ||
				  	((i >= 115*DX && i < 165*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 115*DX && i < 165*DX) && (i%DX >= 355 && i%DX < 405 )) ||
				  	((i >= 115*DX && i < 165*DX) && (i%DX >= 435 && i%DX < 485 )) ||
				  	((i >= 195*DX && i < 245*DX) && (i%DX >= 115 && i%DX < 165 )) ||
				  	((i >= 195*DX && i < 245*DX) && (i%DX >= 195 && i%DX < 245 )) ||
				  	((i >= 195*DX && i < 245*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 195*DX && i < 245*DX) && (i%DX >= 355 && i%DX < 405 )) ||
				  	((i >= 195*DX && i < 245*DX) && (i%DX >= 435 && i%DX < 485 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 115 && i%DX < 165 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 195 && i%DX < 245 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 355 && i%DX < 405 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 435 && i%DX < 485 )) ||
				  	((i >= 355*DX && i < 405*DX) && (i%DX >= 115 && i%DX < 165 )) ||
				  	((i >= 355*DX && i < 405*DX) && (i%DX >= 195 && i%DX < 245 )) ||
				  	((i >= 355*DX && i < 405*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 355*DX && i < 405*DX) && (i%DX >= 355 && i%DX < 405 )) ||
				  	((i >= 355*DX && i < 405*DX) && (i%DX >= 435 && i%DX < 485 )) ||
				  	((i >= 435*DX && i < 485*DX) && (i%DX >= 115 && i%DX < 165 )) ||
				  	((i >= 435*DX && i < 485*DX) && (i%DX >= 195 && i%DX < 245 )) ||
				  	((i >= 435*DX && i < 485*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 435*DX && i < 485*DX) && (i%DX >= 355 && i%DX < 405 )) ||
				  	((i >= 435*DX && i < 485*DX) && (i%DX >= 435 && i%DX < 485 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 30040: // 25 cluster (30path) --> 40x40x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 140*DX && i < 180*DX) && (i%DX >= 140 && i%DX < 180 )) || 
				  	((i >= 140*DX && i < 180*DX) && (i%DX >= 210 && i%DX < 250 )) ||
				  	((i >= 140*DX && i < 180*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 140*DX && i < 180*DX) && (i%DX >= 350 && i%DX < 390 )) ||
				  	((i >= 140*DX && i < 180*DX) && (i%DX >= 420 && i%DX < 460 )) ||
				  	((i >= 210*DX && i < 250*DX) && (i%DX >= 140 && i%DX < 180 )) ||
				  	((i >= 210*DX && i < 250*DX) && (i%DX >= 210 && i%DX < 250 )) ||
				  	((i >= 210*DX && i < 250*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 210*DX && i < 250*DX) && (i%DX >= 350 && i%DX < 390 )) ||
				  	((i >= 210*DX && i < 250*DX) && (i%DX >= 420 && i%DX < 460 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 140 && i%DX < 180 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 210 && i%DX < 250 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 350 && i%DX < 390 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 420 && i%DX < 460 )) ||
				  	((i >= 350*DX && i < 390*DX) && (i%DX >= 140 && i%DX < 180 )) ||
				  	((i >= 350*DX && i < 390*DX) && (i%DX >= 210 && i%DX < 250 )) ||
				  	((i >= 350*DX && i < 390*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 350*DX && i < 390*DX) && (i%DX >= 350 && i%DX < 390 )) ||
				  	((i >= 350*DX && i < 390*DX) && (i%DX >= 420 && i%DX < 460 )) ||
				  	((i >= 420*DX && i < 460*DX) && (i%DX >= 140 && i%DX < 180 )) ||
				  	((i >= 420*DX && i < 460*DX) && (i%DX >= 210 && i%DX < 250 )) ||
				  	((i >= 420*DX && i < 460*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 420*DX && i < 460*DX) && (i%DX >= 350 && i%DX < 390 )) ||
				  	((i >= 420*DX && i < 460*DX) && (i%DX >= 420 && i%DX < 460 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 35080: // 25 cluster (35path) --> 80x80x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  30*DX && i < 110*DX) && (i%DX >=  30 && i%DX < 110 )) || 
				  	((i >=  30*DX && i < 110*DX) && (i%DX >= 145 && i%DX < 225 )) ||
				  	((i >=  30*DX && i < 110*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >=  30*DX && i < 110*DX) && (i%DX >= 375 && i%DX < 455 )) ||
				  	((i >=  30*DX && i < 110*DX) && (i%DX >= 490 && i%DX < 570 )) ||
				  	((i >= 145*DX && i < 225*DX) && (i%DX >=  30 && i%DX < 110 )) ||
				  	((i >= 145*DX && i < 225*DX) && (i%DX >= 145 && i%DX < 225 )) ||
				  	((i >= 145*DX && i < 225*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 145*DX && i < 225*DX) && (i%DX >= 375 && i%DX < 455 )) ||
				  	((i >= 145*DX && i < 225*DX) && (i%DX >= 490 && i%DX < 570 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >=  30 && i%DX < 110 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 145 && i%DX < 225 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 375 && i%DX < 455 )) ||
				  	((i >= 260*DX && i < 340*DX) && (i%DX >= 490 && i%DX < 570 )) ||
				  	((i >= 375*DX && i < 455*DX) && (i%DX >=  30 && i%DX < 110 )) ||
				  	((i >= 375*DX && i < 455*DX) && (i%DX >= 145 && i%DX < 225 )) ||
				  	((i >= 375*DX && i < 455*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 375*DX && i < 455*DX) && (i%DX >= 375 && i%DX < 455 )) ||
				  	((i >= 375*DX && i < 455*DX) && (i%DX >= 490 && i%DX < 570 )) ||
				  	((i >= 490*DX && i < 570*DX) && (i%DX >=  30 && i%DX < 110 )) ||
				  	((i >= 490*DX && i < 570*DX) && (i%DX >= 145 && i%DX < 225 )) ||
				  	((i >= 490*DX && i < 570*DX) && (i%DX >= 260 && i%DX < 340 )) ||
				  	((i >= 490*DX && i < 570*DX) && (i%DX >= 375 && i%DX < 455 )) ||
				  	((i >= 490*DX && i < 570*DX) && (i%DX >= 490 && i%DX < 570 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 35070: // 25 cluster (35path) --> 70x70x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  55*DX && i < 125*DX) && (i%DX >=  55 && i%DX < 125 )) || 
				  	((i >=  55*DX && i < 125*DX) && (i%DX >= 160 && i%DX < 230 )) ||
				  	((i >=  55*DX && i < 125*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >=  55*DX && i < 125*DX) && (i%DX >= 370 && i%DX < 440 )) ||
				  	((i >=  55*DX && i < 125*DX) && (i%DX >= 475 && i%DX < 545 )) ||
				  	((i >= 160*DX && i < 230*DX) && (i%DX >=  55 && i%DX < 125 )) ||
				  	((i >= 160*DX && i < 230*DX) && (i%DX >= 160 && i%DX < 230 )) ||
				  	((i >= 160*DX && i < 230*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 160*DX && i < 230*DX) && (i%DX >= 370 && i%DX < 440 )) ||
				  	((i >= 160*DX && i < 230*DX) && (i%DX >= 475 && i%DX < 545 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >=  55 && i%DX < 125 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 160 && i%DX < 230 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 370 && i%DX < 440 )) ||
				  	((i >= 265*DX && i < 335*DX) && (i%DX >= 475 && i%DX < 545 )) ||
				  	((i >= 370*DX && i < 440*DX) && (i%DX >=  55 && i%DX < 125 )) ||
				  	((i >= 370*DX && i < 440*DX) && (i%DX >= 160 && i%DX < 230 )) ||
				  	((i >= 370*DX && i < 440*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 370*DX && i < 440*DX) && (i%DX >= 370 && i%DX < 440 )) ||
				  	((i >= 370*DX && i < 440*DX) && (i%DX >= 475 && i%DX < 545 )) ||
				  	((i >= 475*DX && i < 545*DX) && (i%DX >=  55 && i%DX < 125 )) ||
				  	((i >= 475*DX && i < 545*DX) && (i%DX >= 160 && i%DX < 230 )) ||
				  	((i >= 475*DX && i < 545*DX) && (i%DX >= 265 && i%DX < 335 )) ||
				  	((i >= 475*DX && i < 545*DX) && (i%DX >= 370 && i%DX < 440 )) ||
				  	((i >= 475*DX && i < 545*DX) && (i%DX >= 475 && i%DX < 545 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 35060: // 25 cluster (35path) --> 60x60x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  80*DX && i < 140*DX) && (i%DX >=  80 && i%DX < 140 )) || 
				  	((i >=  80*DX && i < 140*DX) && (i%DX >= 175 && i%DX < 235 )) ||
				  	((i >=  80*DX && i < 140*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >=  80*DX && i < 140*DX) && (i%DX >= 365 && i%DX < 425 )) ||
				  	((i >=  80*DX && i < 140*DX) && (i%DX >= 460 && i%DX < 520 )) ||
				  	((i >= 175*DX && i < 235*DX) && (i%DX >=  80 && i%DX < 140 )) ||
				  	((i >= 175*DX && i < 235*DX) && (i%DX >= 175 && i%DX < 235 )) ||
				  	((i >= 175*DX && i < 235*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 175*DX && i < 235*DX) && (i%DX >= 365 && i%DX < 425 )) ||
				  	((i >= 175*DX && i < 235*DX) && (i%DX >= 460 && i%DX < 520 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >=  80 && i%DX < 140 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 175 && i%DX < 235 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 365 && i%DX < 425 )) ||
				  	((i >= 270*DX && i < 330*DX) && (i%DX >= 460 && i%DX < 520 )) ||
				  	((i >= 365*DX && i < 425*DX) && (i%DX >=  80 && i%DX < 140 )) ||
				  	((i >= 365*DX && i < 425*DX) && (i%DX >= 175 && i%DX < 235 )) ||
				  	((i >= 365*DX && i < 425*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 365*DX && i < 425*DX) && (i%DX >= 365 && i%DX < 425 )) ||
				  	((i >= 365*DX && i < 425*DX) && (i%DX >= 460 && i%DX < 520 )) ||
				  	((i >= 460*DX && i < 520*DX) && (i%DX >=  80 && i%DX < 140 )) ||
				  	((i >= 460*DX && i < 520*DX) && (i%DX >= 175 && i%DX < 235 )) ||
				  	((i >= 460*DX && i < 520*DX) && (i%DX >= 270 && i%DX < 330 )) ||
				  	((i >= 460*DX && i < 520*DX) && (i%DX >= 365 && i%DX < 425 )) ||
				  	((i >= 460*DX && i < 520*DX) && (i%DX >= 460 && i%DX < 520 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 35052: // 25 cluster (35path) --> 52x52x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 152*DX) && (i%DX >= 100 && i%DX < 152 )) || 
				  	((i >= 100*DX && i < 152*DX) && (i%DX >= 187 && i%DX < 239 )) ||
				  	((i >= 100*DX && i < 152*DX) && (i%DX >= 274 && i%DX < 326 )) ||
				  	((i >= 100*DX && i < 152*DX) && (i%DX >= 361 && i%DX < 413 )) ||
				  	((i >= 100*DX && i < 152*DX) && (i%DX >= 448 && i%DX < 500 )) ||
				  	((i >= 187*DX && i < 239*DX) && (i%DX >= 100 && i%DX < 152 )) ||
				  	((i >= 187*DX && i < 239*DX) && (i%DX >= 187 && i%DX < 239 )) ||
				  	((i >= 187*DX && i < 239*DX) && (i%DX >= 274 && i%DX < 326 )) ||
				  	((i >= 187*DX && i < 239*DX) && (i%DX >= 361 && i%DX < 413 )) ||
				  	((i >= 187*DX && i < 239*DX) && (i%DX >= 448 && i%DX < 500 )) ||
				  	((i >= 274*DX && i < 326*DX) && (i%DX >= 100 && i%DX < 152 )) ||
				  	((i >= 274*DX && i < 326*DX) && (i%DX >= 187 && i%DX < 239 )) ||
				  	((i >= 274*DX && i < 326*DX) && (i%DX >= 274 && i%DX < 326 )) ||
				  	((i >= 274*DX && i < 326*DX) && (i%DX >= 361 && i%DX < 413 )) ||
				  	((i >= 274*DX && i < 326*DX) && (i%DX >= 448 && i%DX < 500 )) ||
				  	((i >= 361*DX && i < 413*DX) && (i%DX >= 100 && i%DX < 152 )) ||
				  	((i >= 361*DX && i < 413*DX) && (i%DX >= 187 && i%DX < 239 )) ||
				  	((i >= 361*DX && i < 413*DX) && (i%DX >= 274 && i%DX < 326 )) ||
				  	((i >= 361*DX && i < 413*DX) && (i%DX >= 361 && i%DX < 413 )) ||
				  	((i >= 361*DX && i < 413*DX) && (i%DX >= 448 && i%DX < 500 )) ||
				  	((i >= 448*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 152 )) ||
				  	((i >= 448*DX && i < 500*DX) && (i%DX >= 187 && i%DX < 239 )) ||
				  	((i >= 448*DX && i < 500*DX) && (i%DX >= 274 && i%DX < 326 )) ||
				  	((i >= 448*DX && i < 500*DX) && (i%DX >= 361 && i%DX < 413 )) ||
				  	((i >= 448*DX && i < 500*DX) && (i%DX >= 448 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 35050: // 25 cluster (35path) --> 50x50x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 105*DX && i < 155*DX) && (i%DX >= 105 && i%DX < 155 )) || 
				  	((i >= 105*DX && i < 155*DX) && (i%DX >= 190 && i%DX < 240 )) ||
				  	((i >= 105*DX && i < 155*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 105*DX && i < 155*DX) && (i%DX >= 360 && i%DX < 410 )) ||
				  	((i >= 105*DX && i < 155*DX) && (i%DX >= 445 && i%DX < 495 )) ||
				  	((i >= 190*DX && i < 240*DX) && (i%DX >= 105 && i%DX < 155 )) ||
				  	((i >= 190*DX && i < 240*DX) && (i%DX >= 190 && i%DX < 240 )) ||
				  	((i >= 190*DX && i < 240*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 190*DX && i < 240*DX) && (i%DX >= 360 && i%DX < 410 )) ||
				  	((i >= 190*DX && i < 240*DX) && (i%DX >= 445 && i%DX < 495 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 105 && i%DX < 155 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 190 && i%DX < 240 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 360 && i%DX < 410 )) ||
				  	((i >= 275*DX && i < 325*DX) && (i%DX >= 445 && i%DX < 495 )) ||
				  	((i >= 360*DX && i < 410*DX) && (i%DX >= 105 && i%DX < 155 )) ||
				  	((i >= 360*DX && i < 410*DX) && (i%DX >= 190 && i%DX < 240 )) ||
				  	((i >= 360*DX && i < 410*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 360*DX && i < 410*DX) && (i%DX >= 360 && i%DX < 410 )) ||
				  	((i >= 360*DX && i < 410*DX) && (i%DX >= 445 && i%DX < 495 )) ||
				  	((i >= 445*DX && i < 495*DX) && (i%DX >= 105 && i%DX < 155 )) ||
				  	((i >= 445*DX && i < 495*DX) && (i%DX >= 190 && i%DX < 240 )) ||
				  	((i >= 445*DX && i < 495*DX) && (i%DX >= 275 && i%DX < 325 )) ||
				  	((i >= 445*DX && i < 495*DX) && (i%DX >= 360 && i%DX < 410 )) ||
				  	((i >= 445*DX && i < 495*DX) && (i%DX >= 445 && i%DX < 495 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 35040: // 25 cluster (35path) --> 40x40x25
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 130*DX && i < 170*DX) && (i%DX >= 130 && i%DX < 170 )) || 
				  	((i >= 130*DX && i < 170*DX) && (i%DX >= 205 && i%DX < 245 )) ||
				  	((i >= 130*DX && i < 170*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 130*DX && i < 170*DX) && (i%DX >= 355 && i%DX < 395 )) ||
				  	((i >= 130*DX && i < 170*DX) && (i%DX >= 430 && i%DX < 470 )) ||
				  	((i >= 205*DX && i < 245*DX) && (i%DX >= 130 && i%DX < 170 )) ||
				  	((i >= 205*DX && i < 245*DX) && (i%DX >= 205 && i%DX < 245 )) ||
				  	((i >= 205*DX && i < 245*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 205*DX && i < 245*DX) && (i%DX >= 355 && i%DX < 395 )) ||
				  	((i >= 205*DX && i < 245*DX) && (i%DX >= 430 && i%DX < 470 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 130 && i%DX < 170 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 205 && i%DX < 245 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 355 && i%DX < 395 )) ||
				  	((i >= 280*DX && i < 320*DX) && (i%DX >= 430 && i%DX < 470 )) ||
				  	((i >= 355*DX && i < 395*DX) && (i%DX >= 130 && i%DX < 170 )) ||
				  	((i >= 355*DX && i < 395*DX) && (i%DX >= 205 && i%DX < 245 )) ||
				  	((i >= 355*DX && i < 395*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 355*DX && i < 395*DX) && (i%DX >= 355 && i%DX < 395 )) ||
				  	((i >= 355*DX && i < 395*DX) && (i%DX >= 430 && i%DX < 470 )) ||
				  	((i >= 430*DX && i < 470*DX) && (i%DX >= 130 && i%DX < 170 )) ||
				  	((i >= 430*DX && i < 470*DX) && (i%DX >= 205 && i%DX < 245 )) ||
				  	((i >= 430*DX && i < 470*DX) && (i%DX >= 280 && i%DX < 320 )) ||
				  	((i >= 430*DX && i < 470*DX) && (i%DX >= 355 && i%DX < 395 )) ||
				  	((i >= 430*DX && i < 470*DX) && (i%DX >= 430 && i%DX < 470 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 40: // 25 cluster (40path)
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 148*DX) && (i%DX >= 100 && i%DX < 148 )) || 
				  	((i >= 100*DX && i < 148*DX) && (i%DX >= 188 && i%DX < 236 )) ||
				  	((i >= 100*DX && i < 148*DX) && (i%DX >= 276 && i%DX < 324 )) ||
				  	((i >= 100*DX && i < 148*DX) && (i%DX >= 364 && i%DX < 412 )) ||
				  	((i >= 100*DX && i < 148*DX) && (i%DX >= 452 && i%DX < 500 )) ||
				  	((i >= 188*DX && i < 236*DX) && (i%DX >= 100 && i%DX < 148 )) ||
				  	((i >= 188*DX && i < 236*DX) && (i%DX >= 188 && i%DX < 236 )) ||
				  	((i >= 188*DX && i < 236*DX) && (i%DX >= 276 && i%DX < 324 )) ||
				  	((i >= 188*DX && i < 236*DX) && (i%DX >= 364 && i%DX < 412 )) ||
				  	((i >= 188*DX && i < 236*DX) && (i%DX >= 452 && i%DX < 500 )) ||
				  	((i >= 276*DX && i < 324*DX) && (i%DX >= 100 && i%DX < 148 )) ||
				  	((i >= 276*DX && i < 324*DX) && (i%DX >= 188 && i%DX < 236 )) ||
				  	((i >= 276*DX && i < 324*DX) && (i%DX >= 276 && i%DX < 324 )) ||
				  	((i >= 276*DX && i < 324*DX) && (i%DX >= 364 && i%DX < 412 )) ||
				  	((i >= 276*DX && i < 324*DX) && (i%DX >= 452 && i%DX < 500 )) ||
				  	((i >= 364*DX && i < 412*DX) && (i%DX >= 100 && i%DX < 148 )) ||
				  	((i >= 364*DX && i < 412*DX) && (i%DX >= 188 && i%DX < 236 )) ||
				  	((i >= 364*DX && i < 412*DX) && (i%DX >= 276 && i%DX < 324 )) ||
				  	((i >= 364*DX && i < 412*DX) && (i%DX >= 364 && i%DX < 412 )) ||
				  	((i >= 364*DX && i < 412*DX) && (i%DX >= 452 && i%DX < 500 )) ||
				  	((i >= 452*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 148 )) ||
				  	((i >= 452*DX && i < 500*DX) && (i%DX >= 188 && i%DX < 236 )) ||
				  	((i >= 452*DX && i < 500*DX) && (i%DX >= 276 && i%DX < 324 )) ||
				  	((i >= 452*DX && i < 500*DX) && (i%DX >= 364 && i%DX < 412 )) ||
				  	((i >= 452*DX && i < 500*DX) && (i%DX >= 452 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 45: // 25 cluster (45path)
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
