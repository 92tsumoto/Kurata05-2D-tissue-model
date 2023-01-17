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
		case 7002: // 36 cluster (2path) --> 70x70x36
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  85*DX && i < 155*DX) && (i%DX >=  85 && i%DX < 155 )) || 
				  	((i >=  85*DX && i < 155*DX) && (i%DX >= 157 && i%DX < 227 )) ||
				  	((i >=  85*DX && i < 155*DX) && (i%DX >= 229 && i%DX < 299 )) ||
				  	((i >=  85*DX && i < 155*DX) && (i%DX >= 301 && i%DX < 371 )) ||
				  	((i >=  85*DX && i < 155*DX) && (i%DX >= 373 && i%DX < 443 )) ||
				  	((i >=  85*DX && i < 155*DX) && (i%DX >= 445 && i%DX < 515 )) ||
				  	((i >= 157*DX && i < 227*DX) && (i%DX >=  85 && i%DX < 155 )) ||
				  	((i >= 157*DX && i < 227*DX) && (i%DX >= 157 && i%DX < 227 )) ||
				  	((i >= 157*DX && i < 227*DX) && (i%DX >= 229 && i%DX < 299 )) ||
				  	((i >= 157*DX && i < 227*DX) && (i%DX >= 301 && i%DX < 371 )) ||
				  	((i >= 157*DX && i < 227*DX) && (i%DX >= 373 && i%DX < 443 )) ||
				  	((i >= 157*DX && i < 227*DX) && (i%DX >= 445 && i%DX < 515 )) ||
				  	((i >= 229*DX && i < 299*DX) && (i%DX >=  85 && i%DX < 155 )) ||
				  	((i >= 229*DX && i < 299*DX) && (i%DX >= 157 && i%DX < 227 )) ||
				  	((i >= 229*DX && i < 299*DX) && (i%DX >= 229 && i%DX < 299 )) ||
				  	((i >= 229*DX && i < 299*DX) && (i%DX >= 301 && i%DX < 371 )) ||
				  	((i >= 229*DX && i < 299*DX) && (i%DX >= 373 && i%DX < 443 )) ||
				  	((i >= 229*DX && i < 299*DX) && (i%DX >= 445 && i%DX < 515 )) ||
				  	((i >= 301*DX && i < 371*DX) && (i%DX >=  85 && i%DX < 155 )) ||
				  	((i >= 301*DX && i < 371*DX) && (i%DX >= 157 && i%DX < 227 )) ||
				  	((i >= 301*DX && i < 371*DX) && (i%DX >= 229 && i%DX < 299 )) ||
				  	((i >= 301*DX && i < 371*DX) && (i%DX >= 301 && i%DX < 371 )) ||
				  	((i >= 301*DX && i < 371*DX) && (i%DX >= 373 && i%DX < 443 )) ||
				  	((i >= 301*DX && i < 371*DX) && (i%DX >= 445 && i%DX < 515 )) ||
				  	((i >= 373*DX && i < 443*DX) && (i%DX >=  85 && i%DX < 155 )) ||
				  	((i >= 373*DX && i < 443*DX) && (i%DX >= 157 && i%DX < 227 )) ||
				  	((i >= 373*DX && i < 443*DX) && (i%DX >= 229 && i%DX < 299 )) ||
				  	((i >= 373*DX && i < 443*DX) && (i%DX >= 301 && i%DX < 371 )) ||
				  	((i >= 373*DX && i < 443*DX) && (i%DX >= 373 && i%DX < 443 )) ||
				  	((i >= 373*DX && i < 443*DX) && (i%DX >= 445 && i%DX < 515 )) ||
				  	((i >= 445*DX && i < 515*DX) && (i%DX >=  85 && i%DX < 155 )) ||
				  	((i >= 445*DX && i < 515*DX) && (i%DX >= 157 && i%DX < 227 )) ||
				  	((i >= 445*DX && i < 515*DX) && (i%DX >= 229 && i%DX < 299 )) ||
				  	((i >= 445*DX && i < 515*DX) && (i%DX >= 301 && i%DX < 371 )) ||
				  	((i >= 445*DX && i < 515*DX) && (i%DX >= 373 && i%DX < 443 )) ||
				  	((i >= 445*DX && i < 515*DX) && (i%DX >= 445 && i%DX < 515 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 6502: // 36 cluster (2path) --> 65x65x36 (default)
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 165*DX) && (i%DX >= 100 && i%DX < 165 )) || 
				  	((i >= 100*DX && i < 165*DX) && (i%DX >= 167 && i%DX < 232 )) ||
				  	((i >= 100*DX && i < 165*DX) && (i%DX >= 234 && i%DX < 299 )) ||
				  	((i >= 100*DX && i < 165*DX) && (i%DX >= 301 && i%DX < 366 )) ||
				  	((i >= 100*DX && i < 165*DX) && (i%DX >= 368 && i%DX < 433 )) ||
				  	((i >= 100*DX && i < 165*DX) && (i%DX >= 435 && i%DX < 500 )) ||
				  	((i >= 167*DX && i < 232*DX) && (i%DX >= 100 && i%DX < 165 )) ||
				  	((i >= 167*DX && i < 232*DX) && (i%DX >= 167 && i%DX < 232 )) ||
				  	((i >= 167*DX && i < 232*DX) && (i%DX >= 234 && i%DX < 299 )) ||
				  	((i >= 167*DX && i < 232*DX) && (i%DX >= 301 && i%DX < 366 )) ||
				  	((i >= 167*DX && i < 232*DX) && (i%DX >= 368 && i%DX < 433 )) ||
				  	((i >= 167*DX && i < 232*DX) && (i%DX >= 435 && i%DX < 500 )) ||
				  	((i >= 234*DX && i < 299*DX) && (i%DX >= 100 && i%DX < 165 )) ||
				  	((i >= 234*DX && i < 299*DX) && (i%DX >= 167 && i%DX < 232 )) ||
				  	((i >= 234*DX && i < 299*DX) && (i%DX >= 234 && i%DX < 299 )) ||
				  	((i >= 234*DX && i < 299*DX) && (i%DX >= 301 && i%DX < 366 )) ||
				  	((i >= 234*DX && i < 299*DX) && (i%DX >= 368 && i%DX < 433 )) ||
				  	((i >= 234*DX && i < 299*DX) && (i%DX >= 435 && i%DX < 500 )) ||
				  	((i >= 301*DX && i < 366*DX) && (i%DX >= 100 && i%DX < 165 )) ||
				  	((i >= 301*DX && i < 366*DX) && (i%DX >= 167 && i%DX < 232 )) ||
				  	((i >= 301*DX && i < 366*DX) && (i%DX >= 234 && i%DX < 299 )) ||
				  	((i >= 301*DX && i < 366*DX) && (i%DX >= 301 && i%DX < 366 )) ||
				  	((i >= 301*DX && i < 366*DX) && (i%DX >= 368 && i%DX < 433 )) ||
				  	((i >= 301*DX && i < 366*DX) && (i%DX >= 435 && i%DX < 500 )) ||
				  	((i >= 368*DX && i < 433*DX) && (i%DX >= 100 && i%DX < 165 )) ||
				  	((i >= 368*DX && i < 433*DX) && (i%DX >= 167 && i%DX < 232 )) ||
				  	((i >= 368*DX && i < 433*DX) && (i%DX >= 234 && i%DX < 299 )) ||
				  	((i >= 368*DX && i < 433*DX) && (i%DX >= 301 && i%DX < 366 )) ||
				  	((i >= 368*DX && i < 433*DX) && (i%DX >= 368 && i%DX < 433 )) ||
				  	((i >= 368*DX && i < 433*DX) && (i%DX >= 435 && i%DX < 500 )) ||
				  	((i >= 435*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 165 )) ||
				  	((i >= 435*DX && i < 500*DX) && (i%DX >= 167 && i%DX < 232 )) ||
				  	((i >= 435*DX && i < 500*DX) && (i%DX >= 234 && i%DX < 299 )) ||
				  	((i >= 435*DX && i < 500*DX) && (i%DX >= 301 && i%DX < 366 )) ||
				  	((i >= 435*DX && i < 500*DX) && (i%DX >= 368 && i%DX < 433 )) ||
				  	((i >= 435*DX && i < 500*DX) && (i%DX >= 435 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 6002: // 36 cluster (2path) --> 60x60x36
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 115*DX && i < 175*DX) && (i%DX >= 115 && i%DX < 175 )) || 
				  	((i >= 115*DX && i < 175*DX) && (i%DX >= 177 && i%DX < 237 )) ||
				  	((i >= 115*DX && i < 175*DX) && (i%DX >= 239 && i%DX < 299 )) ||
				  	((i >= 115*DX && i < 175*DX) && (i%DX >= 301 && i%DX < 361 )) ||
				  	((i >= 115*DX && i < 175*DX) && (i%DX >= 363 && i%DX < 423 )) ||
				  	((i >= 115*DX && i < 175*DX) && (i%DX >= 425 && i%DX < 485 )) ||
				  	((i >= 177*DX && i < 237*DX) && (i%DX >= 115 && i%DX < 175 )) ||
				  	((i >= 177*DX && i < 237*DX) && (i%DX >= 177 && i%DX < 237 )) ||
				  	((i >= 177*DX && i < 237*DX) && (i%DX >= 239 && i%DX < 299 )) ||
				  	((i >= 177*DX && i < 237*DX) && (i%DX >= 301 && i%DX < 361 )) ||
				  	((i >= 177*DX && i < 237*DX) && (i%DX >= 363 && i%DX < 423 )) ||
				  	((i >= 177*DX && i < 237*DX) && (i%DX >= 425 && i%DX < 485 )) ||
				  	((i >= 239*DX && i < 299*DX) && (i%DX >= 115 && i%DX < 175 )) ||
				  	((i >= 239*DX && i < 299*DX) && (i%DX >= 177 && i%DX < 237 )) ||
				  	((i >= 239*DX && i < 299*DX) && (i%DX >= 239 && i%DX < 299 )) ||
				  	((i >= 239*DX && i < 299*DX) && (i%DX >= 301 && i%DX < 361 )) ||
				  	((i >= 239*DX && i < 299*DX) && (i%DX >= 363 && i%DX < 423 )) ||
				  	((i >= 239*DX && i < 299*DX) && (i%DX >= 425 && i%DX < 485 )) ||
				  	((i >= 301*DX && i < 361*DX) && (i%DX >= 115 && i%DX < 175 )) ||
				  	((i >= 301*DX && i < 361*DX) && (i%DX >= 177 && i%DX < 237 )) ||
				  	((i >= 301*DX && i < 361*DX) && (i%DX >= 239 && i%DX < 299 )) ||
				  	((i >= 301*DX && i < 361*DX) && (i%DX >= 301 && i%DX < 361 )) ||
				  	((i >= 301*DX && i < 361*DX) && (i%DX >= 363 && i%DX < 423 )) ||
				  	((i >= 301*DX && i < 361*DX) && (i%DX >= 425 && i%DX < 485 )) ||
				  	((i >= 363*DX && i < 423*DX) && (i%DX >= 115 && i%DX < 175 )) ||
				  	((i >= 363*DX && i < 423*DX) && (i%DX >= 177 && i%DX < 237 )) ||
				  	((i >= 363*DX && i < 423*DX) && (i%DX >= 239 && i%DX < 299 )) ||
				  	((i >= 363*DX && i < 423*DX) && (i%DX >= 301 && i%DX < 361 )) ||
				  	((i >= 363*DX && i < 423*DX) && (i%DX >= 363 && i%DX < 423 )) ||
				  	((i >= 363*DX && i < 423*DX) && (i%DX >= 425 && i%DX < 485 )) ||
				  	((i >= 425*DX && i < 485*DX) && (i%DX >= 115 && i%DX < 175 )) ||
				  	((i >= 425*DX && i < 485*DX) && (i%DX >= 177 && i%DX < 237 )) ||
				  	((i >= 425*DX && i < 485*DX) && (i%DX >= 239 && i%DX < 299 )) ||
				  	((i >= 425*DX && i < 485*DX) && (i%DX >= 301 && i%DX < 361 )) ||
				  	((i >= 425*DX && i < 485*DX) && (i%DX >= 363 && i%DX < 423 )) ||
				  	((i >= 425*DX && i < 485*DX) && (i%DX >= 425 && i%DX < 485 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5002: // 36 cluster (2path) --> 50x50x36 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 145*DX && i < 195*DX) && (i%DX >= 145 && i%DX < 195 )) || 
				  	((i >= 145*DX && i < 195*DX) && (i%DX >= 197 && i%DX < 247 )) ||
				  	((i >= 145*DX && i < 195*DX) && (i%DX >= 249 && i%DX < 299 )) ||
				  	((i >= 145*DX && i < 195*DX) && (i%DX >= 301 && i%DX < 351 )) ||
				  	((i >= 145*DX && i < 195*DX) && (i%DX >= 353 && i%DX < 403 )) ||
				  	((i >= 145*DX && i < 195*DX) && (i%DX >= 405 && i%DX < 455 )) ||
				  	((i >= 197*DX && i < 247*DX) && (i%DX >= 145 && i%DX < 195 )) ||
				  	((i >= 197*DX && i < 247*DX) && (i%DX >= 197 && i%DX < 247 )) ||
				  	((i >= 197*DX && i < 247*DX) && (i%DX >= 249 && i%DX < 299 )) ||
				  	((i >= 197*DX && i < 247*DX) && (i%DX >= 301 && i%DX < 351 )) ||
				  	((i >= 197*DX && i < 247*DX) && (i%DX >= 353 && i%DX < 403 )) ||
				  	((i >= 197*DX && i < 247*DX) && (i%DX >= 405 && i%DX < 455 )) ||
				  	((i >= 249*DX && i < 299*DX) && (i%DX >= 145 && i%DX < 195 )) ||
				  	((i >= 249*DX && i < 299*DX) && (i%DX >= 197 && i%DX < 247 )) ||
				  	((i >= 249*DX && i < 299*DX) && (i%DX >= 249 && i%DX < 299 )) ||
				  	((i >= 249*DX && i < 299*DX) && (i%DX >= 301 && i%DX < 351 )) ||
				  	((i >= 249*DX && i < 299*DX) && (i%DX >= 353 && i%DX < 403 )) ||
				  	((i >= 249*DX && i < 299*DX) && (i%DX >= 405 && i%DX < 455 )) ||
				  	((i >= 301*DX && i < 351*DX) && (i%DX >= 145 && i%DX < 195 )) ||
				  	((i >= 301*DX && i < 351*DX) && (i%DX >= 197 && i%DX < 247 )) ||
				  	((i >= 301*DX && i < 351*DX) && (i%DX >= 249 && i%DX < 299 )) ||
				  	((i >= 301*DX && i < 351*DX) && (i%DX >= 301 && i%DX < 351 )) ||
				  	((i >= 301*DX && i < 351*DX) && (i%DX >= 353 && i%DX < 403 )) ||
				  	((i >= 301*DX && i < 351*DX) && (i%DX >= 405 && i%DX < 455 )) ||
				  	((i >= 353*DX && i < 403*DX) && (i%DX >= 145 && i%DX < 195 )) ||
				  	((i >= 353*DX && i < 403*DX) && (i%DX >= 197 && i%DX < 247 )) ||
				  	((i >= 353*DX && i < 403*DX) && (i%DX >= 249 && i%DX < 299 )) ||
				  	((i >= 353*DX && i < 403*DX) && (i%DX >= 301 && i%DX < 351 )) ||
				  	((i >= 353*DX && i < 403*DX) && (i%DX >= 353 && i%DX < 403 )) ||
				  	((i >= 353*DX && i < 403*DX) && (i%DX >= 405 && i%DX < 455 )) ||
				  	((i >= 405*DX && i < 455*DX) && (i%DX >= 145 && i%DX < 195 )) ||
				  	((i >= 405*DX && i < 455*DX) && (i%DX >= 197 && i%DX < 247 )) ||
				  	((i >= 405*DX && i < 455*DX) && (i%DX >= 249 && i%DX < 299 )) ||
				  	((i >= 405*DX && i < 455*DX) && (i%DX >= 301 && i%DX < 351 )) ||
				  	((i >= 405*DX && i < 455*DX) && (i%DX >= 353 && i%DX < 403 )) ||
				  	((i >= 405*DX && i < 455*DX) && (i%DX >= 405 && i%DX < 455 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 4002: // 36 cluster (2path) --> 40x40x36
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 175*DX && i < 215*DX) && (i%DX >= 175 && i%DX < 215 )) || 
				  	((i >= 175*DX && i < 215*DX) && (i%DX >= 217 && i%DX < 257 )) ||
				  	((i >= 175*DX && i < 215*DX) && (i%DX >= 259 && i%DX < 299 )) ||
				  	((i >= 175*DX && i < 215*DX) && (i%DX >= 301 && i%DX < 341 )) ||
				  	((i >= 175*DX && i < 215*DX) && (i%DX >= 343 && i%DX < 383 )) ||
				  	((i >= 175*DX && i < 215*DX) && (i%DX >= 385 && i%DX < 425 )) ||
				  	((i >= 217*DX && i < 257*DX) && (i%DX >= 175 && i%DX < 215 )) ||
				  	((i >= 217*DX && i < 257*DX) && (i%DX >= 217 && i%DX < 257 )) ||
				  	((i >= 217*DX && i < 257*DX) && (i%DX >= 259 && i%DX < 299 )) ||
				  	((i >= 217*DX && i < 257*DX) && (i%DX >= 301 && i%DX < 341 )) ||
				  	((i >= 217*DX && i < 257*DX) && (i%DX >= 343 && i%DX < 383 )) ||
				  	((i >= 217*DX && i < 257*DX) && (i%DX >= 385 && i%DX < 425 )) ||
				  	((i >= 259*DX && i < 299*DX) && (i%DX >= 175 && i%DX < 215 )) ||
				  	((i >= 259*DX && i < 299*DX) && (i%DX >= 217 && i%DX < 257 )) ||
				  	((i >= 259*DX && i < 299*DX) && (i%DX >= 259 && i%DX < 299 )) ||
				  	((i >= 259*DX && i < 299*DX) && (i%DX >= 301 && i%DX < 341 )) ||
				  	((i >= 259*DX && i < 299*DX) && (i%DX >= 343 && i%DX < 383 )) ||
				  	((i >= 259*DX && i < 299*DX) && (i%DX >= 385 && i%DX < 425 )) ||
				  	((i >= 301*DX && i < 341*DX) && (i%DX >= 175 && i%DX < 215 )) ||
				  	((i >= 301*DX && i < 341*DX) && (i%DX >= 217 && i%DX < 257 )) ||
				  	((i >= 301*DX && i < 341*DX) && (i%DX >= 259 && i%DX < 299 )) ||
				  	((i >= 301*DX && i < 341*DX) && (i%DX >= 301 && i%DX < 341 )) ||
				  	((i >= 301*DX && i < 341*DX) && (i%DX >= 343 && i%DX < 383 )) ||
				  	((i >= 301*DX && i < 341*DX) && (i%DX >= 385 && i%DX < 425 )) ||
				  	((i >= 343*DX && i < 383*DX) && (i%DX >= 175 && i%DX < 215 )) ||
				  	((i >= 343*DX && i < 383*DX) && (i%DX >= 217 && i%DX < 257 )) ||
				  	((i >= 343*DX && i < 383*DX) && (i%DX >= 259 && i%DX < 299 )) ||
				  	((i >= 343*DX && i < 383*DX) && (i%DX >= 301 && i%DX < 341 )) ||
				  	((i >= 343*DX && i < 383*DX) && (i%DX >= 343 && i%DX < 383 )) ||
				  	((i >= 343*DX && i < 383*DX) && (i%DX >= 385 && i%DX < 425 )) ||
				  	((i >= 385*DX && i < 425*DX) && (i%DX >= 175 && i%DX < 215 )) ||
				  	((i >= 385*DX && i < 425*DX) && (i%DX >= 217 && i%DX < 257 )) ||
				  	((i >= 385*DX && i < 425*DX) && (i%DX >= 259 && i%DX < 299 )) ||
				  	((i >= 385*DX && i < 425*DX) && (i%DX >= 301 && i%DX < 341 )) ||
				  	((i >= 385*DX && i < 425*DX) && (i%DX >= 343 && i%DX < 383 )) ||
				  	((i >= 385*DX && i < 425*DX) && (i%DX >= 385 && i%DX < 425 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 4008: // 36 cluster (8path) --> 40x40x36
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 160*DX && i < 200*DX) && (i%DX >= 160 && i%DX < 200 )) || 
				  	((i >= 160*DX && i < 200*DX) && (i%DX >= 208 && i%DX < 248 )) ||
				  	((i >= 160*DX && i < 200*DX) && (i%DX >= 256 && i%DX < 296 )) ||
				  	((i >= 160*DX && i < 200*DX) && (i%DX >= 304 && i%DX < 344 )) ||
				  	((i >= 160*DX && i < 200*DX) && (i%DX >= 352 && i%DX < 392 )) ||
				  	((i >= 160*DX && i < 200*DX) && (i%DX >= 400 && i%DX < 440 )) ||
				  	((i >= 208*DX && i < 248*DX) && (i%DX >= 160 && i%DX < 200 )) ||
				  	((i >= 208*DX && i < 248*DX) && (i%DX >= 208 && i%DX < 248 )) ||
				  	((i >= 208*DX && i < 248*DX) && (i%DX >= 256 && i%DX < 296 )) ||
				  	((i >= 208*DX && i < 248*DX) && (i%DX >= 304 && i%DX < 344 )) ||
				  	((i >= 208*DX && i < 248*DX) && (i%DX >= 352 && i%DX < 392 )) ||
				  	((i >= 208*DX && i < 248*DX) && (i%DX >= 400 && i%DX < 440 )) ||
				  	((i >= 256*DX && i < 296*DX) && (i%DX >= 160 && i%DX < 200 )) ||
				  	((i >= 256*DX && i < 296*DX) && (i%DX >= 208 && i%DX < 248 )) ||
				  	((i >= 256*DX && i < 296*DX) && (i%DX >= 256 && i%DX < 296 )) ||
				  	((i >= 256*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 344 )) ||
				  	((i >= 256*DX && i < 296*DX) && (i%DX >= 352 && i%DX < 392 )) ||
				  	((i >= 256*DX && i < 296*DX) && (i%DX >= 400 && i%DX < 440 )) ||
				  	((i >= 304*DX && i < 344*DX) && (i%DX >= 160 && i%DX < 200 )) ||
				  	((i >= 304*DX && i < 344*DX) && (i%DX >= 208 && i%DX < 248 )) ||
				  	((i >= 304*DX && i < 344*DX) && (i%DX >= 256 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 344*DX) && (i%DX >= 304 && i%DX < 344 )) ||
				  	((i >= 304*DX && i < 344*DX) && (i%DX >= 352 && i%DX < 392 )) ||
				  	((i >= 304*DX && i < 344*DX) && (i%DX >= 400 && i%DX < 440 )) ||
				  	((i >= 352*DX && i < 392*DX) && (i%DX >= 160 && i%DX < 200 )) ||
				  	((i >= 352*DX && i < 392*DX) && (i%DX >= 208 && i%DX < 248 )) ||
				  	((i >= 352*DX && i < 392*DX) && (i%DX >= 256 && i%DX < 296 )) ||
				  	((i >= 352*DX && i < 392*DX) && (i%DX >= 304 && i%DX < 344 )) ||
				  	((i >= 352*DX && i < 392*DX) && (i%DX >= 352 && i%DX < 392 )) ||
				  	((i >= 352*DX && i < 392*DX) && (i%DX >= 400 && i%DX < 440 )) ||
				  	((i >= 400*DX && i < 440*DX) && (i%DX >= 160 && i%DX < 200 )) ||
				  	((i >= 400*DX && i < 440*DX) && (i%DX >= 218 && i%DX < 248 )) ||
				  	((i >= 400*DX && i < 440*DX) && (i%DX >= 256 && i%DX < 296 )) ||
				  	((i >= 400*DX && i < 440*DX) && (i%DX >= 304 && i%DX < 344 )) ||
				  	((i >= 400*DX && i < 440*DX) && (i%DX >= 352 && i%DX < 392 )) ||
				  	((i >= 400*DX && i < 440*DX) && (i%DX >= 400 && i%DX < 440 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5008: // 36 cluster (8path) --> 50x50x36
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 130*DX && i < 180*DX) && (i%DX >= 130 && i%DX < 180 )) || 
				  	((i >= 130*DX && i < 180*DX) && (i%DX >= 188 && i%DX < 238 )) ||
				  	((i >= 130*DX && i < 180*DX) && (i%DX >= 246 && i%DX < 296 )) ||
				  	((i >= 130*DX && i < 180*DX) && (i%DX >= 304 && i%DX < 354 )) ||
				  	((i >= 130*DX && i < 180*DX) && (i%DX >= 362 && i%DX < 412 )) ||
				  	((i >= 130*DX && i < 180*DX) && (i%DX >= 420 && i%DX < 470 )) ||
				  	((i >= 188*DX && i < 238*DX) && (i%DX >= 130 && i%DX < 180 )) ||
				  	((i >= 188*DX && i < 238*DX) && (i%DX >= 188 && i%DX < 238 )) ||
				  	((i >= 188*DX && i < 238*DX) && (i%DX >= 246 && i%DX < 296 )) ||
				  	((i >= 188*DX && i < 238*DX) && (i%DX >= 304 && i%DX < 354 )) ||
				  	((i >= 188*DX && i < 238*DX) && (i%DX >= 362 && i%DX < 412 )) ||
				  	((i >= 188*DX && i < 238*DX) && (i%DX >= 420 && i%DX < 470 )) ||
				  	((i >= 246*DX && i < 296*DX) && (i%DX >= 130 && i%DX < 180 )) ||
				  	((i >= 246*DX && i < 296*DX) && (i%DX >= 188 && i%DX < 238 )) ||
				  	((i >= 246*DX && i < 296*DX) && (i%DX >= 246 && i%DX < 296 )) ||
				  	((i >= 246*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 354 )) ||
				  	((i >= 246*DX && i < 296*DX) && (i%DX >= 362 && i%DX < 412 )) ||
				  	((i >= 246*DX && i < 296*DX) && (i%DX >= 420 && i%DX < 470 )) ||
				  	((i >= 304*DX && i < 354*DX) && (i%DX >= 130 && i%DX < 180 )) ||
				  	((i >= 304*DX && i < 354*DX) && (i%DX >= 188 && i%DX < 238 )) ||
				  	((i >= 304*DX && i < 354*DX) && (i%DX >= 246 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 354*DX) && (i%DX >= 304 && i%DX < 354 )) ||
				  	((i >= 304*DX && i < 354*DX) && (i%DX >= 362 && i%DX < 412 )) ||
				  	((i >= 304*DX && i < 354*DX) && (i%DX >= 420 && i%DX < 470 )) ||
				  	((i >= 362*DX && i < 412*DX) && (i%DX >= 130 && i%DX < 180 )) ||
				  	((i >= 362*DX && i < 412*DX) && (i%DX >= 188 && i%DX < 238 )) ||
				  	((i >= 362*DX && i < 412*DX) && (i%DX >= 246 && i%DX < 296 )) ||
				  	((i >= 362*DX && i < 412*DX) && (i%DX >= 304 && i%DX < 354 )) ||
				  	((i >= 362*DX && i < 412*DX) && (i%DX >= 362 && i%DX < 412 )) ||
				  	((i >= 362*DX && i < 412*DX) && (i%DX >= 420 && i%DX < 470 )) ||
				  	((i >= 420*DX && i < 470*DX) && (i%DX >= 130 && i%DX < 180 )) ||
				  	((i >= 420*DX && i < 470*DX) && (i%DX >= 188 && i%DX < 238 )) ||
				  	((i >= 420*DX && i < 470*DX) && (i%DX >= 246 && i%DX < 296 )) ||
				  	((i >= 420*DX && i < 470*DX) && (i%DX >= 304 && i%DX < 354 )) ||
				  	((i >= 420*DX && i < 470*DX) && (i%DX >= 362 && i%DX < 412 )) ||
				  	((i >= 420*DX && i < 470*DX) && (i%DX >= 420 && i%DX < 470 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5508: // 36 cluster (8path) --> 55x55x36
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 115*DX && i < 170*DX) && (i%DX >= 115 && i%DX < 170 )) || 
				  	((i >= 115*DX && i < 170*DX) && (i%DX >= 178 && i%DX < 233 )) ||
				  	((i >= 115*DX && i < 170*DX) && (i%DX >= 241 && i%DX < 296 )) ||
				  	((i >= 115*DX && i < 170*DX) && (i%DX >= 304 && i%DX < 359 )) ||
				  	((i >= 115*DX && i < 170*DX) && (i%DX >= 367 && i%DX < 422 )) ||
				  	((i >= 115*DX && i < 170*DX) && (i%DX >= 430 && i%DX < 485 )) ||
				  	((i >= 178*DX && i < 233*DX) && (i%DX >= 115 && i%DX < 170 )) ||
				  	((i >= 178*DX && i < 233*DX) && (i%DX >= 178 && i%DX < 233 )) ||
				  	((i >= 178*DX && i < 233*DX) && (i%DX >= 241 && i%DX < 296 )) ||
				  	((i >= 178*DX && i < 233*DX) && (i%DX >= 304 && i%DX < 359 )) ||
				  	((i >= 178*DX && i < 233*DX) && (i%DX >= 367 && i%DX < 422 )) ||
				  	((i >= 178*DX && i < 233*DX) && (i%DX >= 430 && i%DX < 485 )) ||
				  	((i >= 241*DX && i < 296*DX) && (i%DX >= 115 && i%DX < 170 )) ||
				  	((i >= 241*DX && i < 296*DX) && (i%DX >= 178 && i%DX < 233 )) ||
				  	((i >= 241*DX && i < 296*DX) && (i%DX >= 241 && i%DX < 296 )) ||
				  	((i >= 241*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 359 )) ||
				  	((i >= 241*DX && i < 296*DX) && (i%DX >= 367 && i%DX < 422 )) ||
				  	((i >= 241*DX && i < 296*DX) && (i%DX >= 430 && i%DX < 485 )) ||
				  	((i >= 304*DX && i < 359*DX) && (i%DX >= 115 && i%DX < 170 )) ||
				  	((i >= 304*DX && i < 359*DX) && (i%DX >= 178 && i%DX < 233 )) ||
				  	((i >= 304*DX && i < 359*DX) && (i%DX >= 241 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 359*DX) && (i%DX >= 304 && i%DX < 359 )) ||
				  	((i >= 304*DX && i < 359*DX) && (i%DX >= 367 && i%DX < 422 )) ||
				  	((i >= 304*DX && i < 359*DX) && (i%DX >= 430 && i%DX < 485 )) ||
				  	((i >= 367*DX && i < 422*DX) && (i%DX >= 115 && i%DX < 170 )) ||
				  	((i >= 367*DX && i < 422*DX) && (i%DX >= 178 && i%DX < 233 )) ||
				  	((i >= 367*DX && i < 422*DX) && (i%DX >= 241 && i%DX < 296 )) ||
				  	((i >= 367*DX && i < 422*DX) && (i%DX >= 304 && i%DX < 359 )) ||
				  	((i >= 367*DX && i < 422*DX) && (i%DX >= 367 && i%DX < 422 )) ||
				  	((i >= 367*DX && i < 422*DX) && (i%DX >= 430 && i%DX < 485 )) ||
				  	((i >= 430*DX && i < 485*DX) && (i%DX >= 115 && i%DX < 170 )) ||
				  	((i >= 430*DX && i < 485*DX) && (i%DX >= 178 && i%DX < 233 )) ||
				  	((i >= 430*DX && i < 485*DX) && (i%DX >= 241 && i%DX < 296 )) ||
				  	((i >= 430*DX && i < 485*DX) && (i%DX >= 304 && i%DX < 359 )) ||
				  	((i >= 430*DX && i < 485*DX) && (i%DX >= 367 && i%DX < 422 )) ||
				  	((i >= 430*DX && i < 485*DX) && (i%DX >= 430 && i%DX < 485 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 6008: // 36 cluster (8path) --> 60x60x36 (default)
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 160*DX) && (i%DX >= 100 && i%DX < 160 )) || 
				  	((i >= 100*DX && i < 160*DX) && (i%DX >= 168 && i%DX < 228 )) ||
				  	((i >= 100*DX && i < 160*DX) && (i%DX >= 236 && i%DX < 296 )) ||
				  	((i >= 100*DX && i < 160*DX) && (i%DX >= 304 && i%DX < 364 )) ||
				  	((i >= 100*DX && i < 160*DX) && (i%DX >= 372 && i%DX < 432 )) ||
				  	((i >= 100*DX && i < 160*DX) && (i%DX >= 440 && i%DX < 500 )) ||
				  	((i >= 168*DX && i < 228*DX) && (i%DX >= 100 && i%DX < 160 )) ||
				  	((i >= 168*DX && i < 228*DX) && (i%DX >= 168 && i%DX < 228 )) ||
				  	((i >= 168*DX && i < 228*DX) && (i%DX >= 236 && i%DX < 296 )) ||
				  	((i >= 168*DX && i < 228*DX) && (i%DX >= 304 && i%DX < 364 )) ||
				  	((i >= 168*DX && i < 228*DX) && (i%DX >= 372 && i%DX < 432 )) ||
				  	((i >= 168*DX && i < 228*DX) && (i%DX >= 440 && i%DX < 500 )) ||
				  	((i >= 236*DX && i < 296*DX) && (i%DX >= 100 && i%DX < 160 )) ||
				  	((i >= 236*DX && i < 296*DX) && (i%DX >= 168 && i%DX < 228 )) ||
				  	((i >= 236*DX && i < 296*DX) && (i%DX >= 236 && i%DX < 296 )) ||
				  	((i >= 236*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 364 )) ||
				  	((i >= 236*DX && i < 296*DX) && (i%DX >= 372 && i%DX < 432 )) ||
				  	((i >= 236*DX && i < 296*DX) && (i%DX >= 440 && i%DX < 500 )) ||
				  	((i >= 304*DX && i < 364*DX) && (i%DX >= 100 && i%DX < 160 )) ||
				  	((i >= 304*DX && i < 364*DX) && (i%DX >= 168 && i%DX < 228 )) ||
				  	((i >= 304*DX && i < 364*DX) && (i%DX >= 236 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 364*DX) && (i%DX >= 304 && i%DX < 364 )) ||
				  	((i >= 304*DX && i < 364*DX) && (i%DX >= 372 && i%DX < 432 )) ||
				  	((i >= 304*DX && i < 364*DX) && (i%DX >= 440 && i%DX < 500 )) ||
				  	((i >= 372*DX && i < 432*DX) && (i%DX >= 100 && i%DX < 160 )) ||
				  	((i >= 372*DX && i < 432*DX) && (i%DX >= 168 && i%DX < 228 )) ||
				  	((i >= 372*DX && i < 432*DX) && (i%DX >= 236 && i%DX < 296 )) ||
				  	((i >= 372*DX && i < 432*DX) && (i%DX >= 304 && i%DX < 364 )) ||
				  	((i >= 372*DX && i < 432*DX) && (i%DX >= 372 && i%DX < 432 )) ||
				  	((i >= 372*DX && i < 432*DX) && (i%DX >= 440 && i%DX < 500 )) ||
				  	((i >= 440*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 160 )) ||
				  	((i >= 440*DX && i < 500*DX) && (i%DX >= 168 && i%DX < 228 )) ||
				  	((i >= 440*DX && i < 500*DX) && (i%DX >= 236 && i%DX < 296 )) ||
				  	((i >= 440*DX && i < 500*DX) && (i%DX >= 304 && i%DX < 364 )) ||
				  	((i >= 440*DX && i < 500*DX) && (i%DX >= 372 && i%DX < 432 )) ||
				  	((i >= 440*DX && i < 500*DX) && (i%DX >= 440 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 6508: // 36 cluster (8path) --> 65x65x36
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  85*DX && i < 150*DX) && (i%DX >=  85 && i%DX < 150 )) || 
				  	((i >=  85*DX && i < 150*DX) && (i%DX >= 158 && i%DX < 223 )) ||
				  	((i >=  85*DX && i < 150*DX) && (i%DX >= 231 && i%DX < 296 )) ||
				  	((i >=  85*DX && i < 150*DX) && (i%DX >= 304 && i%DX < 369 )) ||
				  	((i >=  85*DX && i < 150*DX) && (i%DX >= 377 && i%DX < 442 )) ||
				  	((i >=  85*DX && i < 150*DX) && (i%DX >= 450 && i%DX < 515 )) ||
				  	((i >= 158*DX && i < 223*DX) && (i%DX >=  85 && i%DX < 150 )) ||
				  	((i >= 158*DX && i < 223*DX) && (i%DX >= 158 && i%DX < 223 )) ||
				  	((i >= 158*DX && i < 223*DX) && (i%DX >= 231 && i%DX < 296 )) ||
				  	((i >= 158*DX && i < 223*DX) && (i%DX >= 304 && i%DX < 369 )) ||
				  	((i >= 158*DX && i < 223*DX) && (i%DX >= 377 && i%DX < 442 )) ||
				  	((i >= 158*DX && i < 223*DX) && (i%DX >= 450 && i%DX < 485 )) ||
				  	((i >= 231*DX && i < 296*DX) && (i%DX >=  85 && i%DX < 150 )) ||
				  	((i >= 231*DX && i < 296*DX) && (i%DX >= 158 && i%DX < 223 )) ||
				  	((i >= 231*DX && i < 296*DX) && (i%DX >= 231 && i%DX < 296 )) ||
				  	((i >= 231*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 369 )) ||
				  	((i >= 231*DX && i < 296*DX) && (i%DX >= 377 && i%DX < 442 )) ||
				  	((i >= 231*DX && i < 296*DX) && (i%DX >= 450 && i%DX < 515 )) ||
				  	((i >= 304*DX && i < 369*DX) && (i%DX >=  85 && i%DX < 150 )) ||
				  	((i >= 304*DX && i < 369*DX) && (i%DX >= 158 && i%DX < 223 )) ||
				  	((i >= 304*DX && i < 369*DX) && (i%DX >= 231 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 369*DX) && (i%DX >= 304 && i%DX < 369 )) ||
				  	((i >= 304*DX && i < 369*DX) && (i%DX >= 377 && i%DX < 442 )) ||
				  	((i >= 304*DX && i < 369*DX) && (i%DX >= 450 && i%DX < 515 )) ||
				  	((i >= 377*DX && i < 442*DX) && (i%DX >=  85 && i%DX < 150 )) ||
				  	((i >= 377*DX && i < 442*DX) && (i%DX >= 158 && i%DX < 223 )) ||
				  	((i >= 377*DX && i < 442*DX) && (i%DX >= 231 && i%DX < 296 )) ||
				  	((i >= 377*DX && i < 442*DX) && (i%DX >= 304 && i%DX < 369 )) ||
				  	((i >= 377*DX && i < 442*DX) && (i%DX >= 377 && i%DX < 442 )) ||
				  	((i >= 377*DX && i < 442*DX) && (i%DX >= 450 && i%DX < 515 )) ||
				  	((i >= 450*DX && i < 515*DX) && (i%DX >=  85 && i%DX < 150 )) ||
				  	((i >= 450*DX && i < 515*DX) && (i%DX >= 158 && i%DX < 223 )) ||
				  	((i >= 450*DX && i < 515*DX) && (i%DX >= 231 && i%DX < 296 )) ||
				  	((i >= 450*DX && i < 515*DX) && (i%DX >= 304 && i%DX < 369 )) ||
				  	((i >= 450*DX && i < 515*DX) && (i%DX >= 377 && i%DX < 442 )) ||
				  	((i >= 450*DX && i < 515*DX) && (i%DX >= 450 && i%DX < 515 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 7008: // 36 cluster (8path) --> 70x70x36 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  70*DX && i < 140*DX) && (i%DX >=  70 && i%DX < 140 )) || 
				  	((i >=  70*DX && i < 140*DX) && (i%DX >= 148 && i%DX < 218 )) ||
				  	((i >=  70*DX && i < 140*DX) && (i%DX >= 226 && i%DX < 296 )) ||
				  	((i >=  70*DX && i < 140*DX) && (i%DX >= 304 && i%DX < 374 )) ||
				  	((i >=  70*DX && i < 140*DX) && (i%DX >= 382 && i%DX < 452 )) ||
				  	((i >=  70*DX && i < 140*DX) && (i%DX >= 460 && i%DX < 530 )) ||
				  	((i >= 148*DX && i < 218*DX) && (i%DX >=  70 && i%DX < 140 )) ||
				  	((i >= 148*DX && i < 218*DX) && (i%DX >= 148 && i%DX < 218 )) ||
				  	((i >= 148*DX && i < 218*DX) && (i%DX >= 226 && i%DX < 296 )) ||
				  	((i >= 148*DX && i < 218*DX) && (i%DX >= 304 && i%DX < 374 )) ||
				  	((i >= 148*DX && i < 218*DX) && (i%DX >= 382 && i%DX < 452 )) ||
				  	((i >= 148*DX && i < 218*DX) && (i%DX >= 460 && i%DX < 530 )) ||
				  	((i >= 226*DX && i < 296*DX) && (i%DX >=  70 && i%DX < 140 )) ||
				  	((i >= 226*DX && i < 296*DX) && (i%DX >= 148 && i%DX < 218 )) ||
				  	((i >= 226*DX && i < 296*DX) && (i%DX >= 226 && i%DX < 296 )) ||
				  	((i >= 226*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 374 )) ||
				  	((i >= 226*DX && i < 296*DX) && (i%DX >= 382 && i%DX < 452 )) ||
				  	((i >= 226*DX && i < 296*DX) && (i%DX >= 460 && i%DX < 530 )) ||
				  	((i >= 304*DX && i < 374*DX) && (i%DX >=  70 && i%DX < 140 )) ||
				  	((i >= 304*DX && i < 374*DX) && (i%DX >= 148 && i%DX < 218 )) ||
				  	((i >= 304*DX && i < 374*DX) && (i%DX >= 226 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 374*DX) && (i%DX >= 304 && i%DX < 374 )) ||
				  	((i >= 304*DX && i < 374*DX) && (i%DX >= 382 && i%DX < 452 )) ||
				  	((i >= 304*DX && i < 374*DX) && (i%DX >= 460 && i%DX < 530 )) ||
				  	((i >= 382*DX && i < 452*DX) && (i%DX >=  70 && i%DX < 140 )) ||
				  	((i >= 382*DX && i < 452*DX) && (i%DX >= 148 && i%DX < 218 )) ||
				  	((i >= 382*DX && i < 452*DX) && (i%DX >= 226 && i%DX < 296 )) ||
				  	((i >= 382*DX && i < 452*DX) && (i%DX >= 304 && i%DX < 374 )) ||
				  	((i >= 382*DX && i < 452*DX) && (i%DX >= 382 && i%DX < 452 )) ||
				  	((i >= 382*DX && i < 452*DX) && (i%DX >= 460 && i%DX < 530 )) ||
				  	((i >= 460*DX && i < 530*DX) && (i%DX >=  70 && i%DX < 140 )) ||
				  	((i >= 460*DX && i < 530*DX) && (i%DX >= 148 && i%DX < 218 )) ||
				  	((i >= 460*DX && i < 530*DX) && (i%DX >= 226 && i%DX < 296 )) ||
				  	((i >= 460*DX && i < 530*DX) && (i%DX >= 304 && i%DX < 374 )) ||
				  	((i >= 460*DX && i < 530*DX) && (i%DX >= 382 && i%DX < 452 )) ||
				  	((i >= 460*DX && i < 530*DX) && (i%DX >= 460 && i%DX < 530 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 7014: // 36 cluster (14path) --> 70x70x36
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  55*DX && i < 125*DX) && (i%DX >=  55 && i%DX < 125 )) || 
				  	((i >=  55*DX && i < 125*DX) && (i%DX >= 139 && i%DX < 209 )) ||
				  	((i >=  55*DX && i < 125*DX) && (i%DX >= 223 && i%DX < 293 )) ||
				  	((i >=  55*DX && i < 125*DX) && (i%DX >= 307 && i%DX < 377 )) ||
				  	((i >=  55*DX && i < 125*DX) && (i%DX >= 391 && i%DX < 461 )) ||
				  	((i >=  55*DX && i < 125*DX) && (i%DX >= 475 && i%DX < 545 )) ||
				  	((i >= 139*DX && i < 209*DX) && (i%DX >=  55 && i%DX < 125 )) ||
				  	((i >= 139*DX && i < 209*DX) && (i%DX >= 139 && i%DX < 209 )) ||
				  	((i >= 139*DX && i < 209*DX) && (i%DX >= 223 && i%DX < 293 )) ||
				  	((i >= 139*DX && i < 209*DX) && (i%DX >= 307 && i%DX < 377 )) ||
				  	((i >= 139*DX && i < 209*DX) && (i%DX >= 391 && i%DX < 461 )) ||
				  	((i >= 139*DX && i < 209*DX) && (i%DX >= 475 && i%DX < 545 )) ||
				  	((i >= 223*DX && i < 293*DX) && (i%DX >=  55 && i%DX < 125 )) ||
				  	((i >= 223*DX && i < 293*DX) && (i%DX >= 139 && i%DX < 209 )) ||
				  	((i >= 223*DX && i < 293*DX) && (i%DX >= 223 && i%DX < 293 )) ||
				  	((i >= 223*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 377 )) ||
				  	((i >= 223*DX && i < 293*DX) && (i%DX >= 391 && i%DX < 461 )) ||
				  	((i >= 223*DX && i < 293*DX) && (i%DX >= 475 && i%DX < 545 )) ||
				  	((i >= 307*DX && i < 377*DX) && (i%DX >=  55 && i%DX < 125 )) ||
				  	((i >= 307*DX && i < 377*DX) && (i%DX >= 139 && i%DX < 209 )) ||
				  	((i >= 307*DX && i < 377*DX) && (i%DX >= 223 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 377*DX) && (i%DX >= 307 && i%DX < 377 )) ||
				  	((i >= 307*DX && i < 377*DX) && (i%DX >= 391 && i%DX < 461 )) ||
				  	((i >= 307*DX && i < 377*DX) && (i%DX >= 475 && i%DX < 545 )) ||
				  	((i >= 391*DX && i < 461*DX) && (i%DX >=  55 && i%DX < 125 )) ||
				  	((i >= 391*DX && i < 461*DX) && (i%DX >= 139 && i%DX < 209 )) ||
				  	((i >= 391*DX && i < 461*DX) && (i%DX >= 223 && i%DX < 293 )) ||
				  	((i >= 391*DX && i < 461*DX) && (i%DX >= 307 && i%DX < 377 )) ||
				  	((i >= 391*DX && i < 461*DX) && (i%DX >= 391 && i%DX < 461 )) ||
				  	((i >= 391*DX && i < 461*DX) && (i%DX >= 475 && i%DX < 545 )) ||
				  	((i >= 475*DX && i < 545*DX) && (i%DX >=  55 && i%DX < 125 )) ||
				  	((i >= 475*DX && i < 545*DX) && (i%DX >= 139 && i%DX < 209 )) ||
				  	((i >= 475*DX && i < 545*DX) && (i%DX >= 223 && i%DX < 293 )) ||
				  	((i >= 475*DX && i < 545*DX) && (i%DX >= 307 && i%DX < 377 )) ||
				  	((i >= 475*DX && i < 545*DX) && (i%DX >= 391 && i%DX < 461 )) ||
				  	((i >= 475*DX && i < 545*DX) && (i%DX >= 475 && i%DX < 545 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 6514: // 36 cluster (14path) --> 65x65x36
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  70*DX && i < 135*DX) && (i%DX >=  70 && i%DX < 135 )) || 
				  	((i >=  70*DX && i < 135*DX) && (i%DX >= 149 && i%DX < 214 )) ||
				  	((i >=  70*DX && i < 135*DX) && (i%DX >= 228 && i%DX < 293 )) ||
				  	((i >=  70*DX && i < 135*DX) && (i%DX >= 307 && i%DX < 372 )) ||
				  	((i >=  70*DX && i < 135*DX) && (i%DX >= 386 && i%DX < 451 )) ||
				  	((i >=  70*DX && i < 135*DX) && (i%DX >= 465 && i%DX < 530 )) ||
				  	((i >= 149*DX && i < 214*DX) && (i%DX >=  70 && i%DX < 135 )) ||
				  	((i >= 149*DX && i < 214*DX) && (i%DX >= 149 && i%DX < 214 )) ||
				  	((i >= 149*DX && i < 214*DX) && (i%DX >= 228 && i%DX < 293 )) ||
				  	((i >= 149*DX && i < 214*DX) && (i%DX >= 307 && i%DX < 372 )) ||
				  	((i >= 149*DX && i < 214*DX) && (i%DX >= 386 && i%DX < 451 )) ||
				  	((i >= 149*DX && i < 214*DX) && (i%DX >= 465 && i%DX < 530 )) ||
				  	((i >= 228*DX && i < 293*DX) && (i%DX >=  70 && i%DX < 135 )) ||
				  	((i >= 228*DX && i < 293*DX) && (i%DX >= 149 && i%DX < 214 )) ||
				  	((i >= 228*DX && i < 293*DX) && (i%DX >= 228 && i%DX < 293 )) ||
				  	((i >= 228*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 372 )) ||
				  	((i >= 228*DX && i < 293*DX) && (i%DX >= 386 && i%DX < 451 )) ||
				  	((i >= 228*DX && i < 293*DX) && (i%DX >= 465 && i%DX < 530 )) ||
				  	((i >= 307*DX && i < 372*DX) && (i%DX >=  70 && i%DX < 135 )) ||
				  	((i >= 307*DX && i < 372*DX) && (i%DX >= 149 && i%DX < 214 )) ||
				  	((i >= 307*DX && i < 372*DX) && (i%DX >= 228 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 372*DX) && (i%DX >= 307 && i%DX < 372 )) ||
				  	((i >= 307*DX && i < 372*DX) && (i%DX >= 386 && i%DX < 451 )) ||
				  	((i >= 307*DX && i < 372*DX) && (i%DX >= 465 && i%DX < 530 )) ||
				  	((i >= 386*DX && i < 451*DX) && (i%DX >=  70 && i%DX < 135 )) ||
				  	((i >= 386*DX && i < 451*DX) && (i%DX >= 149 && i%DX < 214 )) ||
				  	((i >= 386*DX && i < 451*DX) && (i%DX >= 228 && i%DX < 293 )) ||
				  	((i >= 386*DX && i < 451*DX) && (i%DX >= 307 && i%DX < 372 )) ||
				  	((i >= 386*DX && i < 451*DX) && (i%DX >= 386 && i%DX < 451 )) ||
				  	((i >= 386*DX && i < 451*DX) && (i%DX >= 465 && i%DX < 530 )) ||
				  	((i >= 465*DX && i < 530*DX) && (i%DX >=  70 && i%DX < 135 )) ||
				  	((i >= 465*DX && i < 530*DX) && (i%DX >= 149 && i%DX < 214 )) ||
				  	((i >= 465*DX && i < 530*DX) && (i%DX >= 228 && i%DX < 293 )) ||
				  	((i >= 465*DX && i < 530*DX) && (i%DX >= 307 && i%DX < 372 )) ||
				  	((i >= 465*DX && i < 530*DX) && (i%DX >= 386 && i%DX < 451 )) ||
				  	((i >= 465*DX && i < 530*DX) && (i%DX >= 465 && i%DX < 530 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 6014: // 36 cluster (14path) --> 60x60x36
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  85*DX && i < 145*DX) && (i%DX >=  85 && i%DX < 145 )) || 
				  	((i >=  85*DX && i < 145*DX) && (i%DX >= 159 && i%DX < 219 )) ||
				  	((i >=  85*DX && i < 145*DX) && (i%DX >= 233 && i%DX < 293 )) ||
				  	((i >=  85*DX && i < 145*DX) && (i%DX >= 307 && i%DX < 367 )) ||
				  	((i >=  85*DX && i < 145*DX) && (i%DX >= 381 && i%DX < 441 )) ||
				  	((i >=  85*DX && i < 145*DX) && (i%DX >= 455 && i%DX < 515 )) ||
				  	((i >= 159*DX && i < 219*DX) && (i%DX >=  85 && i%DX < 145 )) ||
				  	((i >= 159*DX && i < 219*DX) && (i%DX >= 159 && i%DX < 219 )) ||
				  	((i >= 159*DX && i < 219*DX) && (i%DX >= 233 && i%DX < 293 )) ||
				  	((i >= 159*DX && i < 219*DX) && (i%DX >= 307 && i%DX < 367 )) ||
				  	((i >= 159*DX && i < 219*DX) && (i%DX >= 381 && i%DX < 441 )) ||
				  	((i >= 159*DX && i < 219*DX) && (i%DX >= 455 && i%DX < 515 )) ||
				  	((i >= 233*DX && i < 293*DX) && (i%DX >=  85 && i%DX < 145 )) ||
				  	((i >= 233*DX && i < 293*DX) && (i%DX >= 159 && i%DX < 219 )) ||
				  	((i >= 233*DX && i < 293*DX) && (i%DX >= 233 && i%DX < 293 )) ||
				  	((i >= 233*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 367 )) ||
				  	((i >= 233*DX && i < 293*DX) && (i%DX >= 381 && i%DX < 441 )) ||
				  	((i >= 233*DX && i < 293*DX) && (i%DX >= 455 && i%DX < 515 )) ||
				  	((i >= 307*DX && i < 367*DX) && (i%DX >=  85 && i%DX < 145 )) ||
				  	((i >= 307*DX && i < 367*DX) && (i%DX >= 159 && i%DX < 219 )) ||
				  	((i >= 307*DX && i < 367*DX) && (i%DX >= 233 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 367*DX) && (i%DX >= 307 && i%DX < 367 )) ||
				  	((i >= 307*DX && i < 367*DX) && (i%DX >= 381 && i%DX < 441 )) ||
				  	((i >= 307*DX && i < 367*DX) && (i%DX >= 455 && i%DX < 515 )) ||
				  	((i >= 381*DX && i < 441*DX) && (i%DX >=  85 && i%DX < 145 )) ||
				  	((i >= 381*DX && i < 441*DX) && (i%DX >= 159 && i%DX < 219 )) ||
				  	((i >= 381*DX && i < 441*DX) && (i%DX >= 233 && i%DX < 293 )) ||
				  	((i >= 381*DX && i < 441*DX) && (i%DX >= 307 && i%DX < 367 )) ||
				  	((i >= 381*DX && i < 441*DX) && (i%DX >= 381 && i%DX < 441 )) ||
				  	((i >= 381*DX && i < 441*DX) && (i%DX >= 455 && i%DX < 515 )) ||
				  	((i >= 455*DX && i < 515*DX) && (i%DX >=  85 && i%DX < 145 )) ||
				  	((i >= 455*DX && i < 515*DX) && (i%DX >= 159 && i%DX < 219 )) ||
				  	((i >= 455*DX && i < 515*DX) && (i%DX >= 233 && i%DX < 293 )) ||
				  	((i >= 455*DX && i < 515*DX) && (i%DX >= 307 && i%DX < 367 )) ||
				  	((i >= 455*DX && i < 515*DX) && (i%DX >= 381 && i%DX < 441 )) ||
				  	((i >= 455*DX && i < 515*DX) && (i%DX >= 455 && i%DX < 515 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5514: // 36 cluster (14path) --> 55x55x36 (default)
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 155*DX) && (i%DX >= 100 && i%DX < 155 )) || 
				  	((i >= 100*DX && i < 155*DX) && (i%DX >= 169 && i%DX < 224 )) ||
				  	((i >= 100*DX && i < 155*DX) && (i%DX >= 238 && i%DX < 293 )) ||
				  	((i >= 100*DX && i < 155*DX) && (i%DX >= 307 && i%DX < 362 )) ||
				  	((i >= 100*DX && i < 155*DX) && (i%DX >= 376 && i%DX < 431 )) ||
				  	((i >= 100*DX && i < 155*DX) && (i%DX >= 445 && i%DX < 500 )) ||
				  	((i >= 169*DX && i < 224*DX) && (i%DX >= 100 && i%DX < 155 )) ||
				  	((i >= 169*DX && i < 224*DX) && (i%DX >= 169 && i%DX < 224 )) ||
				  	((i >= 169*DX && i < 224*DX) && (i%DX >= 238 && i%DX < 293 )) ||
				  	((i >= 169*DX && i < 224*DX) && (i%DX >= 307 && i%DX < 362 )) ||
				  	((i >= 169*DX && i < 224*DX) && (i%DX >= 376 && i%DX < 431 )) ||
				  	((i >= 169*DX && i < 224*DX) && (i%DX >= 445 && i%DX < 500 )) ||
				  	((i >= 238*DX && i < 293*DX) && (i%DX >= 100 && i%DX < 155 )) ||
				  	((i >= 238*DX && i < 293*DX) && (i%DX >= 169 && i%DX < 224 )) ||
				  	((i >= 238*DX && i < 293*DX) && (i%DX >= 238 && i%DX < 293 )) ||
				  	((i >= 238*DX && i < 293*DX) && (i%DX >= 307 && i%DX < 362 )) ||
				  	((i >= 238*DX && i < 293*DX) && (i%DX >= 376 && i%DX < 431 )) ||
				  	((i >= 238*DX && i < 293*DX) && (i%DX >= 445 && i%DX < 500 )) ||
				  	((i >= 307*DX && i < 362*DX) && (i%DX >= 100 && i%DX < 155 )) ||
				  	((i >= 307*DX && i < 362*DX) && (i%DX >= 169 && i%DX < 224 )) ||
				  	((i >= 307*DX && i < 362*DX) && (i%DX >= 238 && i%DX < 293 )) ||
				  	((i >= 307*DX && i < 362*DX) && (i%DX >= 307 && i%DX < 362 )) ||
				  	((i >= 307*DX && i < 362*DX) && (i%DX >= 376 && i%DX < 431 )) ||
				  	((i >= 307*DX && i < 362*DX) && (i%DX >= 445 && i%DX < 500 )) ||
				  	((i >= 376*DX && i < 431*DX) && (i%DX >= 100 && i%DX < 155 )) ||
				  	((i >= 376*DX && i < 431*DX) && (i%DX >= 169 && i%DX < 224 )) ||
				  	((i >= 376*DX && i < 431*DX) && (i%DX >= 238 && i%DX < 293 )) ||
				  	((i >= 376*DX && i < 431*DX) && (i%DX >= 307 && i%DX < 362 )) ||
				  	((i >= 376*DX && i < 431*DX) && (i%DX >= 376 && i%DX < 431 )) ||
				  	((i >= 376*DX && i < 431*DX) && (i%DX >= 445 && i%DX < 500 )) ||
				  	((i >= 445*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 155 )) ||
				  	((i >= 445*DX && i < 500*DX) && (i%DX >= 169 && i%DX < 224 )) ||
				  	((i >= 445*DX && i < 500*DX) && (i%DX >= 238 && i%DX < 293 )) ||
				  	((i >= 445*DX && i < 500*DX) && (i%DX >= 307 && i%DX < 362 )) ||
				  	((i >= 445*DX && i < 500*DX) && (i%DX >= 376 && i%DX < 431 )) ||
				  	((i >= 445*DX && i < 500*DX) && (i%DX >= 445 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 4020: // 36 cluster (20path) --> 40x40x36
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 130*DX && i < 170*DX) && (i%DX >= 130 && i%DX < 170 )) || 
				  	((i >= 130*DX && i < 170*DX) && (i%DX >= 190 && i%DX < 230 )) ||
				  	((i >= 130*DX && i < 170*DX) && (i%DX >= 250 && i%DX < 290 )) ||
				  	((i >= 130*DX && i < 170*DX) && (i%DX >= 310 && i%DX < 350 )) ||
				  	((i >= 130*DX && i < 170*DX) && (i%DX >= 370 && i%DX < 410 )) ||
				  	((i >= 130*DX && i < 170*DX) && (i%DX >= 430 && i%DX < 470 )) ||
				  	((i >= 190*DX && i < 230*DX) && (i%DX >= 130 && i%DX < 170 )) ||
				  	((i >= 190*DX && i < 230*DX) && (i%DX >= 190 && i%DX < 230 )) ||
				  	((i >= 190*DX && i < 230*DX) && (i%DX >= 250 && i%DX < 290 )) ||
				  	((i >= 190*DX && i < 230*DX) && (i%DX >= 310 && i%DX < 350 )) ||
				  	((i >= 190*DX && i < 230*DX) && (i%DX >= 370 && i%DX < 410 )) ||
				  	((i >= 190*DX && i < 230*DX) && (i%DX >= 430 && i%DX < 470 )) ||
				  	((i >= 250*DX && i < 290*DX) && (i%DX >= 130 && i%DX < 170 )) ||
				  	((i >= 250*DX && i < 290*DX) && (i%DX >= 190 && i%DX < 230 )) ||
				  	((i >= 250*DX && i < 290*DX) && (i%DX >= 250 && i%DX < 290 )) ||
				  	((i >= 250*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 350 )) ||
				  	((i >= 250*DX && i < 290*DX) && (i%DX >= 370 && i%DX < 410 )) ||
				  	((i >= 250*DX && i < 290*DX) && (i%DX >= 430 && i%DX < 470 )) ||
				  	((i >= 310*DX && i < 350*DX) && (i%DX >= 130 && i%DX < 170 )) ||
				  	((i >= 310*DX && i < 350*DX) && (i%DX >= 190 && i%DX < 230 )) ||
				  	((i >= 310*DX && i < 350*DX) && (i%DX >= 250 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 350*DX) && (i%DX >= 310 && i%DX < 350 )) ||
				  	((i >= 310*DX && i < 350*DX) && (i%DX >= 370 && i%DX < 410 )) ||
				  	((i >= 310*DX && i < 350*DX) && (i%DX >= 430 && i%DX < 470 )) ||
				  	((i >= 370*DX && i < 410*DX) && (i%DX >= 130 && i%DX < 170 )) ||
				  	((i >= 370*DX && i < 410*DX) && (i%DX >= 190 && i%DX < 230 )) ||
				  	((i >= 370*DX && i < 410*DX) && (i%DX >= 250 && i%DX < 290 )) ||
				  	((i >= 370*DX && i < 410*DX) && (i%DX >= 310 && i%DX < 350 )) ||
				  	((i >= 370*DX && i < 410*DX) && (i%DX >= 370 && i%DX < 410 )) ||
				  	((i >= 370*DX && i < 410*DX) && (i%DX >= 430 && i%DX < 470 )) ||
				  	((i >= 430*DX && i < 470*DX) && (i%DX >= 130 && i%DX < 170 )) ||
				  	((i >= 430*DX && i < 470*DX) && (i%DX >= 190 && i%DX < 230 )) ||
				  	((i >= 430*DX && i < 470*DX) && (i%DX >= 250 && i%DX < 290 )) ||
				  	((i >= 430*DX && i < 470*DX) && (i%DX >= 310 && i%DX < 350 )) ||
				  	((i >= 430*DX && i < 470*DX) && (i%DX >= 370 && i%DX < 410 )) ||
				  	((i >= 430*DX && i < 470*DX) && (i%DX >= 430 && i%DX < 470 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5020: // 36 cluster (20path) --> 50x50x36 (default)
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 150*DX) && (i%DX >= 100 && i%DX < 150 )) || 
				  	((i >= 100*DX && i < 150*DX) && (i%DX >= 170 && i%DX < 220 )) ||
				  	((i >= 100*DX && i < 150*DX) && (i%DX >= 240 && i%DX < 290 )) ||
				  	((i >= 100*DX && i < 150*DX) && (i%DX >= 310 && i%DX < 360 )) ||
				  	((i >= 100*DX && i < 150*DX) && (i%DX >= 380 && i%DX < 430 )) ||
				  	((i >= 100*DX && i < 150*DX) && (i%DX >= 450 && i%DX < 500 )) ||
				  	((i >= 170*DX && i < 220*DX) && (i%DX >= 100 && i%DX < 150 )) ||
				  	((i >= 170*DX && i < 220*DX) && (i%DX >= 170 && i%DX < 220 )) ||
				  	((i >= 170*DX && i < 220*DX) && (i%DX >= 240 && i%DX < 290 )) ||
				  	((i >= 170*DX && i < 220*DX) && (i%DX >= 310 && i%DX < 360 )) ||
				  	((i >= 170*DX && i < 220*DX) && (i%DX >= 380 && i%DX < 430 )) ||
				  	((i >= 170*DX && i < 220*DX) && (i%DX >= 450 && i%DX < 500 )) ||
				  	((i >= 240*DX && i < 290*DX) && (i%DX >= 100 && i%DX < 150 )) ||
				  	((i >= 240*DX && i < 290*DX) && (i%DX >= 170 && i%DX < 220 )) ||
				  	((i >= 240*DX && i < 290*DX) && (i%DX >= 240 && i%DX < 290 )) ||
				  	((i >= 240*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 360 )) ||
				  	((i >= 240*DX && i < 290*DX) && (i%DX >= 380 && i%DX < 430 )) ||
				  	((i >= 240*DX && i < 290*DX) && (i%DX >= 450 && i%DX < 500 )) ||
				  	((i >= 310*DX && i < 360*DX) && (i%DX >= 100 && i%DX < 150 )) ||
				  	((i >= 310*DX && i < 360*DX) && (i%DX >= 170 && i%DX < 220 )) ||
				  	((i >= 310*DX && i < 360*DX) && (i%DX >= 240 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 360*DX) && (i%DX >= 310 && i%DX < 360 )) ||
				  	((i >= 310*DX && i < 360*DX) && (i%DX >= 380 && i%DX < 430 )) ||
				  	((i >= 310*DX && i < 360*DX) && (i%DX >= 450 && i%DX < 500 )) ||
				  	((i >= 380*DX && i < 430*DX) && (i%DX >= 100 && i%DX < 150 )) ||
				  	((i >= 380*DX && i < 430*DX) && (i%DX >= 170 && i%DX < 220 )) ||
				  	((i >= 380*DX && i < 430*DX) && (i%DX >= 240 && i%DX < 290 )) ||
				  	((i >= 380*DX && i < 430*DX) && (i%DX >= 310 && i%DX < 360 )) ||
				  	((i >= 380*DX && i < 430*DX) && (i%DX >= 380 && i%DX < 430 )) ||
				  	((i >= 380*DX && i < 430*DX) && (i%DX >= 450 && i%DX < 500 )) ||
				  	((i >= 450*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 150 )) ||
				  	((i >= 450*DX && i < 500*DX) && (i%DX >= 170 && i%DX < 220 )) ||
				  	((i >= 450*DX && i < 500*DX) && (i%DX >= 240 && i%DX < 290 )) ||
				  	((i >= 450*DX && i < 500*DX) && (i%DX >= 310 && i%DX < 360 )) ||
				  	((i >= 450*DX && i < 500*DX) && (i%DX >= 380 && i%DX < 430 )) ||
				  	((i >= 450*DX && i < 500*DX) && (i%DX >= 450 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5520: // 36 cluster (20path) --> 55x55x36
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  85*DX && i < 140*DX) && (i%DX >=  85 && i%DX < 140 )) || 
				  	((i >=  85*DX && i < 140*DX) && (i%DX >= 160 && i%DX < 215 )) ||
				  	((i >=  85*DX && i < 140*DX) && (i%DX >= 235 && i%DX < 290 )) ||
				  	((i >=  85*DX && i < 140*DX) && (i%DX >= 310 && i%DX < 365 )) ||
				  	((i >=  85*DX && i < 140*DX) && (i%DX >= 385 && i%DX < 440 )) ||
				  	((i >=  85*DX && i < 140*DX) && (i%DX >= 460 && i%DX < 515 )) ||
				  	((i >= 160*DX && i < 215*DX) && (i%DX >=  85 && i%DX < 140 )) ||
				  	((i >= 160*DX && i < 215*DX) && (i%DX >= 160 && i%DX < 215 )) ||
				  	((i >= 160*DX && i < 215*DX) && (i%DX >= 235 && i%DX < 290 )) ||
				  	((i >= 160*DX && i < 215*DX) && (i%DX >= 310 && i%DX < 365 )) ||
				  	((i >= 160*DX && i < 215*DX) && (i%DX >= 385 && i%DX < 440 )) ||
				  	((i >= 160*DX && i < 215*DX) && (i%DX >= 460 && i%DX < 515 )) ||
				  	((i >= 235*DX && i < 290*DX) && (i%DX >=  85 && i%DX < 140 )) ||
				  	((i >= 235*DX && i < 290*DX) && (i%DX >= 160 && i%DX < 215 )) ||
				  	((i >= 235*DX && i < 290*DX) && (i%DX >= 235 && i%DX < 290 )) ||
				  	((i >= 235*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 365 )) ||
				  	((i >= 235*DX && i < 290*DX) && (i%DX >= 385 && i%DX < 440 )) ||
				  	((i >= 235*DX && i < 290*DX) && (i%DX >= 460 && i%DX < 515 )) ||
				  	((i >= 310*DX && i < 365*DX) && (i%DX >=  85 && i%DX < 140 )) ||
				  	((i >= 310*DX && i < 365*DX) && (i%DX >= 160 && i%DX < 215 )) ||
				  	((i >= 310*DX && i < 365*DX) && (i%DX >= 235 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 365*DX) && (i%DX >= 310 && i%DX < 365 )) ||
				  	((i >= 310*DX && i < 365*DX) && (i%DX >= 385 && i%DX < 440 )) ||
				  	((i >= 310*DX && i < 365*DX) && (i%DX >= 460 && i%DX < 515 )) ||
				  	((i >= 385*DX && i < 440*DX) && (i%DX >=  85 && i%DX < 140 )) ||
				  	((i >= 385*DX && i < 440*DX) && (i%DX >= 160 && i%DX < 215 )) ||
				  	((i >= 385*DX && i < 440*DX) && (i%DX >= 235 && i%DX < 290 )) ||
				  	((i >= 385*DX && i < 440*DX) && (i%DX >= 310 && i%DX < 365 )) ||
				  	((i >= 385*DX && i < 440*DX) && (i%DX >= 385 && i%DX < 440 )) ||
				  	((i >= 385*DX && i < 440*DX) && (i%DX >= 460 && i%DX < 515 )) ||
				  	((i >= 460*DX && i < 515*DX) && (i%DX >=  85 && i%DX < 140 )) ||
				  	((i >= 460*DX && i < 515*DX) && (i%DX >= 160 && i%DX < 215 )) ||
				  	((i >= 460*DX && i < 515*DX) && (i%DX >= 235 && i%DX < 290 )) ||
				  	((i >= 460*DX && i < 515*DX) && (i%DX >= 310 && i%DX < 365 )) ||
				  	((i >= 460*DX && i < 515*DX) && (i%DX >= 385 && i%DX < 440 )) ||
				  	((i >= 460*DX && i < 515*DX) && (i%DX >= 460 && i%DX < 515 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 6020: // 36 cluster (20path) --> 60x60x36
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  70*DX && i < 130*DX) && (i%DX >=  70 && i%DX < 130 )) || 
				  	((i >=  70*DX && i < 130*DX) && (i%DX >= 150 && i%DX < 210 )) ||
				  	((i >=  70*DX && i < 130*DX) && (i%DX >= 230 && i%DX < 290 )) ||
				  	((i >=  70*DX && i < 130*DX) && (i%DX >= 310 && i%DX < 370 )) ||
				  	((i >=  70*DX && i < 130*DX) && (i%DX >= 390 && i%DX < 450 )) ||
				  	((i >=  70*DX && i < 130*DX) && (i%DX >= 470 && i%DX < 530 )) ||
				  	((i >= 150*DX && i < 210*DX) && (i%DX >=  70 && i%DX < 130 )) ||
				  	((i >= 150*DX && i < 210*DX) && (i%DX >= 150 && i%DX < 210 )) ||
				  	((i >= 150*DX && i < 210*DX) && (i%DX >= 230 && i%DX < 290 )) ||
				  	((i >= 150*DX && i < 210*DX) && (i%DX >= 310 && i%DX < 370 )) ||
				  	((i >= 150*DX && i < 210*DX) && (i%DX >= 390 && i%DX < 450 )) ||
				  	((i >= 150*DX && i < 210*DX) && (i%DX >= 470 && i%DX < 530 )) ||
				  	((i >= 230*DX && i < 290*DX) && (i%DX >=  70 && i%DX < 130 )) ||
				  	((i >= 230*DX && i < 290*DX) && (i%DX >= 150 && i%DX < 210 )) ||
				  	((i >= 230*DX && i < 290*DX) && (i%DX >= 230 && i%DX < 290 )) ||
				  	((i >= 230*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 370 )) ||
				  	((i >= 230*DX && i < 290*DX) && (i%DX >= 390 && i%DX < 450 )) ||
				  	((i >= 230*DX && i < 290*DX) && (i%DX >= 470 && i%DX < 530 )) ||
				  	((i >= 310*DX && i < 370*DX) && (i%DX >=  70 && i%DX < 130 )) ||
				  	((i >= 310*DX && i < 370*DX) && (i%DX >= 150 && i%DX < 210 )) ||
				  	((i >= 310*DX && i < 370*DX) && (i%DX >= 230 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 370*DX) && (i%DX >= 310 && i%DX < 370 )) ||
				  	((i >= 310*DX && i < 370*DX) && (i%DX >= 390 && i%DX < 450 )) ||
				  	((i >= 310*DX && i < 370*DX) && (i%DX >= 470 && i%DX < 530 )) ||
				  	((i >= 390*DX && i < 450*DX) && (i%DX >=  70 && i%DX < 130 )) ||
				  	((i >= 390*DX && i < 450*DX) && (i%DX >= 150 && i%DX < 210 )) ||
				  	((i >= 390*DX && i < 450*DX) && (i%DX >= 230 && i%DX < 290 )) ||
				  	((i >= 390*DX && i < 450*DX) && (i%DX >= 310 && i%DX < 370 )) ||
				  	((i >= 390*DX && i < 450*DX) && (i%DX >= 390 && i%DX < 450 )) ||
				  	((i >= 390*DX && i < 450*DX) && (i%DX >= 470 && i%DX < 530 )) ||
				  	((i >= 470*DX && i < 530*DX) && (i%DX >=  70 && i%DX < 130 )) ||
				  	((i >= 470*DX && i < 530*DX) && (i%DX >= 150 && i%DX < 210 )) ||
				  	((i >= 470*DX && i < 530*DX) && (i%DX >= 230 && i%DX < 290 )) ||
				  	((i >= 470*DX && i < 530*DX) && (i%DX >= 310 && i%DX < 370 )) ||
				  	((i >= 470*DX && i < 530*DX) && (i%DX >= 390 && i%DX < 450 )) ||
				  	((i >= 470*DX && i < 530*DX) && (i%DX >= 470 && i%DX < 530 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 6520: // 36 cluster (20path) --> 65x65x36
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  55*DX && i < 120*DX) && (i%DX >=  55 && i%DX < 120 )) || 
				  	((i >=  55*DX && i < 120*DX) && (i%DX >= 140 && i%DX < 205 )) ||
				  	((i >=  55*DX && i < 120*DX) && (i%DX >= 225 && i%DX < 290 )) ||
				  	((i >=  55*DX && i < 120*DX) && (i%DX >= 310 && i%DX < 375 )) ||
				  	((i >=  55*DX && i < 120*DX) && (i%DX >= 395 && i%DX < 460 )) ||
				  	((i >=  55*DX && i < 120*DX) && (i%DX >= 480 && i%DX < 545 )) ||
				  	((i >= 140*DX && i < 205*DX) && (i%DX >=  55 && i%DX < 120 )) ||
				  	((i >= 140*DX && i < 205*DX) && (i%DX >= 140 && i%DX < 205 )) ||
				  	((i >= 140*DX && i < 205*DX) && (i%DX >= 225 && i%DX < 290 )) ||
				  	((i >= 140*DX && i < 205*DX) && (i%DX >= 310 && i%DX < 375 )) ||
				  	((i >= 140*DX && i < 205*DX) && (i%DX >= 395 && i%DX < 460 )) ||
				  	((i >= 140*DX && i < 205*DX) && (i%DX >= 480 && i%DX < 545 )) ||
				  	((i >= 225*DX && i < 290*DX) && (i%DX >=  55 && i%DX < 120 )) ||
				  	((i >= 225*DX && i < 290*DX) && (i%DX >= 140 && i%DX < 205 )) ||
				  	((i >= 225*DX && i < 290*DX) && (i%DX >= 225 && i%DX < 290 )) ||
				  	((i >= 225*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 375 )) ||
				  	((i >= 225*DX && i < 290*DX) && (i%DX >= 395 && i%DX < 460 )) ||
				  	((i >= 225*DX && i < 290*DX) && (i%DX >= 480 && i%DX < 545 )) ||
				  	((i >= 310*DX && i < 375*DX) && (i%DX >=  55 && i%DX < 120 )) ||
				  	((i >= 310*DX && i < 375*DX) && (i%DX >= 140 && i%DX < 205 )) ||
				  	((i >= 310*DX && i < 375*DX) && (i%DX >= 225 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 375*DX) && (i%DX >= 310 && i%DX < 375 )) ||
				  	((i >= 310*DX && i < 375*DX) && (i%DX >= 395 && i%DX < 460 )) ||
				  	((i >= 310*DX && i < 375*DX) && (i%DX >= 480 && i%DX < 545 )) ||
				  	((i >= 395*DX && i < 460*DX) && (i%DX >=  55 && i%DX < 120 )) ||
				  	((i >= 395*DX && i < 460*DX) && (i%DX >= 140 && i%DX < 205 )) ||
				  	((i >= 395*DX && i < 460*DX) && (i%DX >= 225 && i%DX < 290 )) ||
				  	((i >= 395*DX && i < 460*DX) && (i%DX >= 310 && i%DX < 375 )) ||
				  	((i >= 395*DX && i < 460*DX) && (i%DX >= 395 && i%DX < 460 )) ||
				  	((i >= 395*DX && i < 460*DX) && (i%DX >= 480 && i%DX < 545 )) ||
				  	((i >= 480*DX && i < 545*DX) && (i%DX >=  55 && i%DX < 120 )) ||
				  	((i >= 480*DX && i < 545*DX) && (i%DX >= 140 && i%DX < 205 )) ||
				  	((i >= 480*DX && i < 545*DX) && (i%DX >= 225 && i%DX < 290 )) ||
				  	((i >= 480*DX && i < 545*DX) && (i%DX >= 310 && i%DX < 375 )) ||
				  	((i >= 480*DX && i < 545*DX) && (i%DX >= 395 && i%DX < 460 )) ||
				  	((i >= 480*DX && i < 545*DX) && (i%DX >= 480 && i%DX < 545 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 4026: // 36 cluster (26path) --> 40x40x36
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 115*DX && i < 155*DX) && (i%DX >= 115 && i%DX < 155 )) || 
				  	((i >= 115*DX && i < 155*DX) && (i%DX >= 181 && i%DX < 221 )) ||
				  	((i >= 115*DX && i < 155*DX) && (i%DX >= 247 && i%DX < 287 )) ||
				  	((i >= 115*DX && i < 155*DX) && (i%DX >= 313 && i%DX < 353 )) ||
				  	((i >= 115*DX && i < 155*DX) && (i%DX >= 379 && i%DX < 419 )) ||
				  	((i >= 115*DX && i < 155*DX) && (i%DX >= 445 && i%DX < 485 )) ||
				  	((i >= 181*DX && i < 221*DX) && (i%DX >= 115 && i%DX < 155 )) ||
				  	((i >= 181*DX && i < 221*DX) && (i%DX >= 181 && i%DX < 221 )) ||
				  	((i >= 181*DX && i < 221*DX) && (i%DX >= 247 && i%DX < 287 )) ||
				  	((i >= 181*DX && i < 221*DX) && (i%DX >= 313 && i%DX < 353 )) ||
				  	((i >= 181*DX && i < 221*DX) && (i%DX >= 379 && i%DX < 419 )) ||
				  	((i >= 181*DX && i < 221*DX) && (i%DX >= 445 && i%DX < 485 )) ||
				  	((i >= 247*DX && i < 287*DX) && (i%DX >= 115 && i%DX < 155 )) ||
				  	((i >= 247*DX && i < 287*DX) && (i%DX >= 181 && i%DX < 221 )) ||
				  	((i >= 247*DX && i < 287*DX) && (i%DX >= 247 && i%DX < 287 )) ||
				  	((i >= 247*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 353 )) ||
				  	((i >= 247*DX && i < 287*DX) && (i%DX >= 379 && i%DX < 419 )) ||
				  	((i >= 247*DX && i < 287*DX) && (i%DX >= 445 && i%DX < 485 )) ||
				  	((i >= 313*DX && i < 353*DX) && (i%DX >= 115 && i%DX < 155 )) ||
				  	((i >= 313*DX && i < 353*DX) && (i%DX >= 181 && i%DX < 221 )) ||
				  	((i >= 313*DX && i < 353*DX) && (i%DX >= 247 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 353*DX) && (i%DX >= 313 && i%DX < 353 )) ||
				  	((i >= 313*DX && i < 353*DX) && (i%DX >= 379 && i%DX < 419 )) ||
				  	((i >= 313*DX && i < 353*DX) && (i%DX >= 445 && i%DX < 485 )) ||
				  	((i >= 379*DX && i < 419*DX) && (i%DX >= 115 && i%DX < 155 )) ||
				  	((i >= 379*DX && i < 419*DX) && (i%DX >= 181 && i%DX < 221 )) ||
				  	((i >= 379*DX && i < 419*DX) && (i%DX >= 247 && i%DX < 287 )) ||
				  	((i >= 379*DX && i < 419*DX) && (i%DX >= 313 && i%DX < 353 )) ||
				  	((i >= 379*DX && i < 419*DX) && (i%DX >= 379 && i%DX < 419 )) ||
				  	((i >= 379*DX && i < 419*DX) && (i%DX >= 445 && i%DX < 485 )) ||
				  	((i >= 445*DX && i < 485*DX) && (i%DX >= 115 && i%DX < 155 )) ||
				  	((i >= 445*DX && i < 485*DX) && (i%DX >= 181 && i%DX < 221 )) ||
				  	((i >= 445*DX && i < 485*DX) && (i%DX >= 247 && i%DX < 287 )) ||
				  	((i >= 445*DX && i < 485*DX) && (i%DX >= 313 && i%DX < 353 )) ||
				  	((i >= 445*DX && i < 485*DX) && (i%DX >= 379 && i%DX < 419 )) ||
				  	((i >= 445*DX && i < 485*DX) && (i%DX >= 445 && i%DX < 485 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 4526: // 36 cluster (26path) --> 45x45x36 (default)
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 145*DX) && (i%DX >= 100 && i%DX < 145 )) || 
				  	((i >= 100*DX && i < 145*DX) && (i%DX >= 171 && i%DX < 216 )) ||
				  	((i >= 100*DX && i < 145*DX) && (i%DX >= 242 && i%DX < 287 )) ||
				  	((i >= 100*DX && i < 145*DX) && (i%DX >= 313 && i%DX < 358 )) ||
				  	((i >= 100*DX && i < 145*DX) && (i%DX >= 384 && i%DX < 429 )) ||
				  	((i >= 100*DX && i < 145*DX) && (i%DX >= 455 && i%DX < 500 )) ||
				  	((i >= 171*DX && i < 216*DX) && (i%DX >= 100 && i%DX < 145 )) ||
				  	((i >= 171*DX && i < 216*DX) && (i%DX >= 171 && i%DX < 216 )) ||
				  	((i >= 171*DX && i < 216*DX) && (i%DX >= 242 && i%DX < 287 )) ||
				  	((i >= 171*DX && i < 216*DX) && (i%DX >= 313 && i%DX < 358 )) ||
				  	((i >= 171*DX && i < 216*DX) && (i%DX >= 384 && i%DX < 429 )) ||
				  	((i >= 171*DX && i < 216*DX) && (i%DX >= 455 && i%DX < 500 )) ||
				  	((i >= 242*DX && i < 287*DX) && (i%DX >= 100 && i%DX < 145 )) ||
				  	((i >= 242*DX && i < 287*DX) && (i%DX >= 171 && i%DX < 216 )) ||
				  	((i >= 242*DX && i < 287*DX) && (i%DX >= 242 && i%DX < 287 )) ||
				  	((i >= 242*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 358 )) ||
				  	((i >= 242*DX && i < 287*DX) && (i%DX >= 384 && i%DX < 429 )) ||
				  	((i >= 242*DX && i < 287*DX) && (i%DX >= 455 && i%DX < 500 )) ||
				  	((i >= 313*DX && i < 358*DX) && (i%DX >= 100 && i%DX < 145 )) ||
				  	((i >= 313*DX && i < 358*DX) && (i%DX >= 171 && i%DX < 216 )) ||
				  	((i >= 313*DX && i < 358*DX) && (i%DX >= 242 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 358*DX) && (i%DX >= 313 && i%DX < 358 )) ||
				  	((i >= 313*DX && i < 358*DX) && (i%DX >= 384 && i%DX < 429 )) ||
				  	((i >= 313*DX && i < 358*DX) && (i%DX >= 455 && i%DX < 500 )) ||
				  	((i >= 384*DX && i < 429*DX) && (i%DX >= 100 && i%DX < 145 )) ||
				  	((i >= 384*DX && i < 429*DX) && (i%DX >= 171 && i%DX < 216 )) ||
				  	((i >= 384*DX && i < 429*DX) && (i%DX >= 242 && i%DX < 287 )) ||
				  	((i >= 384*DX && i < 429*DX) && (i%DX >= 313 && i%DX < 358 )) ||
				  	((i >= 384*DX && i < 429*DX) && (i%DX >= 384 && i%DX < 429 )) ||
				  	((i >= 384*DX && i < 429*DX) && (i%DX >= 455 && i%DX < 500 )) ||
				  	((i >= 455*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 145 )) ||
				  	((i >= 455*DX && i < 500*DX) && (i%DX >= 171 && i%DX < 216 )) ||
				  	((i >= 455*DX && i < 500*DX) && (i%DX >= 242 && i%DX < 287 )) ||
				  	((i >= 455*DX && i < 500*DX) && (i%DX >= 313 && i%DX < 358 )) ||
				  	((i >= 455*DX && i < 500*DX) && (i%DX >= 384 && i%DX < 429 )) ||
				  	((i >= 455*DX && i < 500*DX) && (i%DX >= 455 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 5026: // 36 cluster (26path) --> 50x50x36
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  85*DX && i < 135*DX) && (i%DX >=  85 && i%DX < 135 )) || 
				  	((i >=  85*DX && i < 135*DX) && (i%DX >= 161 && i%DX < 211 )) ||
				  	((i >=  85*DX && i < 135*DX) && (i%DX >= 237 && i%DX < 287 )) ||
				  	((i >=  85*DX && i < 135*DX) && (i%DX >= 313 && i%DX < 363 )) ||
				  	((i >=  85*DX && i < 135*DX) && (i%DX >= 389 && i%DX < 439 )) ||
				  	((i >=  85*DX && i < 135*DX) && (i%DX >= 465 && i%DX < 515 )) ||
				  	((i >= 161*DX && i < 211*DX) && (i%DX >=  85 && i%DX < 135 )) ||
				  	((i >= 161*DX && i < 211*DX) && (i%DX >= 161 && i%DX < 211 )) ||
				  	((i >= 161*DX && i < 211*DX) && (i%DX >= 237 && i%DX < 287 )) ||
				  	((i >= 161*DX && i < 211*DX) && (i%DX >= 313 && i%DX < 363 )) ||
				  	((i >= 161*DX && i < 211*DX) && (i%DX >= 389 && i%DX < 439 )) ||
				  	((i >= 161*DX && i < 211*DX) && (i%DX >= 465 && i%DX < 515 )) ||
				  	((i >= 237*DX && i < 287*DX) && (i%DX >=  85 && i%DX < 135 )) ||
				  	((i >= 237*DX && i < 287*DX) && (i%DX >= 161 && i%DX < 211 )) ||
				  	((i >= 237*DX && i < 287*DX) && (i%DX >= 237 && i%DX < 287 )) ||
				  	((i >= 237*DX && i < 287*DX) && (i%DX >= 313 && i%DX < 363 )) ||
				  	((i >= 237*DX && i < 287*DX) && (i%DX >= 389 && i%DX < 439 )) ||
				  	((i >= 237*DX && i < 287*DX) && (i%DX >= 465 && i%DX < 515 )) ||
				  	((i >= 313*DX && i < 363*DX) && (i%DX >=  85 && i%DX < 135 )) ||
				  	((i >= 313*DX && i < 363*DX) && (i%DX >= 161 && i%DX < 211 )) ||
				  	((i >= 313*DX && i < 363*DX) && (i%DX >= 237 && i%DX < 287 )) ||
				  	((i >= 313*DX && i < 363*DX) && (i%DX >= 313 && i%DX < 363 )) ||
				  	((i >= 313*DX && i < 363*DX) && (i%DX >= 389 && i%DX < 439 )) ||
				  	((i >= 313*DX && i < 363*DX) && (i%DX >= 465 && i%DX < 515 )) ||
				  	((i >= 389*DX && i < 439*DX) && (i%DX >=  85 && i%DX < 135 )) ||
				  	((i >= 389*DX && i < 439*DX) && (i%DX >= 161 && i%DX < 211 )) ||
				  	((i >= 389*DX && i < 439*DX) && (i%DX >= 237 && i%DX < 287 )) ||
				  	((i >= 389*DX && i < 439*DX) && (i%DX >= 313 && i%DX < 363 )) ||
				  	((i >= 389*DX && i < 439*DX) && (i%DX >= 389 && i%DX < 439 )) ||
				  	((i >= 389*DX && i < 439*DX) && (i%DX >= 465 && i%DX < 515 )) ||
				  	((i >= 465*DX && i < 515*DX) && (i%DX >=  85 && i%DX < 135 )) ||
				  	((i >= 465*DX && i < 515*DX) && (i%DX >= 161 && i%DX < 211 )) ||
				  	((i >= 465*DX && i < 515*DX) && (i%DX >= 237 && i%DX < 287 )) ||
				  	((i >= 465*DX && i < 515*DX) && (i%DX >= 313 && i%DX < 363 )) ||
				  	((i >= 465*DX && i < 515*DX) && (i%DX >= 389 && i%DX < 439 )) ||
				  	((i >= 465*DX && i < 515*DX) && (i%DX >= 465 && i%DX < 515 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 32: // 36 cluster (32path)
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 140*DX) && (i%DX >= 100 && i%DX < 140 )) || 
				  	((i >= 100*DX && i < 140*DX) && (i%DX >= 172 && i%DX < 212 )) ||
				  	((i >= 100*DX && i < 140*DX) && (i%DX >= 244 && i%DX < 284 )) ||
				  	((i >= 100*DX && i < 140*DX) && (i%DX >= 316 && i%DX < 356 )) ||
				  	((i >= 100*DX && i < 140*DX) && (i%DX >= 388 && i%DX < 428 )) ||
				  	((i >= 100*DX && i < 140*DX) && (i%DX >= 460 && i%DX < 500 )) ||
				  	((i >= 172*DX && i < 212*DX) && (i%DX >= 100 && i%DX < 140 )) ||
				  	((i >= 172*DX && i < 212*DX) && (i%DX >= 172 && i%DX < 212 )) ||
				  	((i >= 172*DX && i < 212*DX) && (i%DX >= 244 && i%DX < 284 )) ||
				  	((i >= 172*DX && i < 212*DX) && (i%DX >= 316 && i%DX < 356 )) ||
				  	((i >= 172*DX && i < 212*DX) && (i%DX >= 388 && i%DX < 428 )) ||
				  	((i >= 172*DX && i < 212*DX) && (i%DX >= 460 && i%DX < 500 )) ||
				  	((i >= 244*DX && i < 284*DX) && (i%DX >= 100 && i%DX < 140 )) ||
				  	((i >= 244*DX && i < 284*DX) && (i%DX >= 172 && i%DX < 212 )) ||
				  	((i >= 244*DX && i < 284*DX) && (i%DX >= 244 && i%DX < 284 )) ||
				  	((i >= 244*DX && i < 284*DX) && (i%DX >= 316 && i%DX < 356 )) ||
				  	((i >= 244*DX && i < 284*DX) && (i%DX >= 388 && i%DX < 428 )) ||
				  	((i >= 244*DX && i < 284*DX) && (i%DX >= 460 && i%DX < 500 )) ||
				  	((i >= 316*DX && i < 356*DX) && (i%DX >= 100 && i%DX < 140 )) ||
				  	((i >= 316*DX && i < 356*DX) && (i%DX >= 172 && i%DX < 212 )) ||
				  	((i >= 316*DX && i < 356*DX) && (i%DX >= 244 && i%DX < 284 )) ||
				  	((i >= 316*DX && i < 356*DX) && (i%DX >= 316 && i%DX < 356 )) ||
				  	((i >= 316*DX && i < 356*DX) && (i%DX >= 388 && i%DX < 428 )) ||
				  	((i >= 316*DX && i < 356*DX) && (i%DX >= 460 && i%DX < 500 )) ||
				  	((i >= 388*DX && i < 428*DX) && (i%DX >= 100 && i%DX < 140 )) ||
				  	((i >= 388*DX && i < 428*DX) && (i%DX >= 172 && i%DX < 212 )) ||
				  	((i >= 388*DX && i < 428*DX) && (i%DX >= 244 && i%DX < 284 )) ||
				  	((i >= 388*DX && i < 428*DX) && (i%DX >= 316 && i%DX < 356 )) ||
				  	((i >= 388*DX && i < 428*DX) && (i%DX >= 388 && i%DX < 428 )) ||
				  	((i >= 388*DX && i < 428*DX) && (i%DX >= 460 && i%DX < 500 )) ||
				  	((i >= 460*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 140 )) ||
				  	((i >= 460*DX && i < 500*DX) && (i%DX >= 172 && i%DX < 212 )) ||
				  	((i >= 460*DX && i < 500*DX) && (i%DX >= 244 && i%DX < 284 )) ||
				  	((i >= 460*DX && i < 500*DX) && (i%DX >= 316 && i%DX < 356 )) ||
				  	((i >= 460*DX && i < 500*DX) && (i%DX >= 388 && i%DX < 428 )) ||
				  	((i >= 460*DX && i < 500*DX) && (i%DX >= 460 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 38: // 36 cluster (38path)
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 135*DX) && (i%DX >= 100 && i%DX < 135 )) || 
				  	((i >= 100*DX && i < 135*DX) && (i%DX >= 173 && i%DX < 208 )) ||
				  	((i >= 100*DX && i < 135*DX) && (i%DX >= 246 && i%DX < 281 )) ||
				  	((i >= 100*DX && i < 135*DX) && (i%DX >= 319 && i%DX < 354 )) ||
				  	((i >= 100*DX && i < 135*DX) && (i%DX >= 392 && i%DX < 427 )) ||
				  	((i >= 100*DX && i < 135*DX) && (i%DX >= 465 && i%DX < 500 )) ||
				  	((i >= 173*DX && i < 208*DX) && (i%DX >= 100 && i%DX < 135 )) ||
				  	((i >= 173*DX && i < 208*DX) && (i%DX >= 173 && i%DX < 208 )) ||
				  	((i >= 173*DX && i < 208*DX) && (i%DX >= 246 && i%DX < 281 )) ||
				  	((i >= 173*DX && i < 208*DX) && (i%DX >= 319 && i%DX < 354 )) ||
				  	((i >= 173*DX && i < 208*DX) && (i%DX >= 392 && i%DX < 427 )) ||
				  	((i >= 173*DX && i < 208*DX) && (i%DX >= 465 && i%DX < 500 )) ||
				  	((i >= 246*DX && i < 281*DX) && (i%DX >= 100 && i%DX < 135 )) ||
				  	((i >= 246*DX && i < 281*DX) && (i%DX >= 173 && i%DX < 208 )) ||
				  	((i >= 246*DX && i < 281*DX) && (i%DX >= 246 && i%DX < 281 )) ||
				  	((i >= 246*DX && i < 281*DX) && (i%DX >= 319 && i%DX < 354 )) ||
				  	((i >= 246*DX && i < 281*DX) && (i%DX >= 392 && i%DX < 427 )) ||
				  	((i >= 246*DX && i < 281*DX) && (i%DX >= 465 && i%DX < 500 )) ||
				  	((i >= 319*DX && i < 354*DX) && (i%DX >= 100 && i%DX < 135 )) ||
				  	((i >= 319*DX && i < 354*DX) && (i%DX >= 173 && i%DX < 208 )) ||
				  	((i >= 319*DX && i < 354*DX) && (i%DX >= 246 && i%DX < 281 )) ||
				  	((i >= 319*DX && i < 354*DX) && (i%DX >= 319 && i%DX < 354 )) ||
				  	((i >= 319*DX && i < 354*DX) && (i%DX >= 392 && i%DX < 427 )) ||
				  	((i >= 319*DX && i < 354*DX) && (i%DX >= 465 && i%DX < 500 )) ||
				  	((i >= 392*DX && i < 427*DX) && (i%DX >= 100 && i%DX < 135 )) ||
				  	((i >= 392*DX && i < 427*DX) && (i%DX >= 173 && i%DX < 208 )) ||
				  	((i >= 392*DX && i < 427*DX) && (i%DX >= 246 && i%DX < 281 )) ||
				  	((i >= 392*DX && i < 427*DX) && (i%DX >= 319 && i%DX < 354 )) ||
				  	((i >= 392*DX && i < 427*DX) && (i%DX >= 392 && i%DX < 427 )) ||
				  	((i >= 392*DX && i < 427*DX) && (i%DX >= 465 && i%DX < 500 )) ||
				  	((i >= 465*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 135 )) ||
				  	((i >= 465*DX && i < 500*DX) && (i%DX >= 173 && i%DX < 208 )) ||
				  	((i >= 465*DX && i < 500*DX) && (i%DX >= 246 && i%DX < 281 )) ||
				  	((i >= 465*DX && i < 500*DX) && (i%DX >= 319 && i%DX < 354 )) ||
				  	((i >= 465*DX && i < 500*DX) && (i%DX >= 392 && i%DX < 427 )) ||
				  	((i >= 465*DX && i < 500*DX) && (i%DX >= 465 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;

		case 44: // 36 cluster (44path)
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
