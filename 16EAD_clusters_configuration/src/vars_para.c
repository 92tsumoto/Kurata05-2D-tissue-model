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
	/*	case 1: // 1 cluster
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
	*/
		case 4080: // 16 cluster (4path) --> 80x80x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 134*DX && i < 214*DX) && (i%DX >= 134 && i%DX < 214 )) || 
				  	((i >= 134*DX && i < 214*DX) && (i%DX >= 218 && i%DX < 298 )) ||
				  	((i >= 134*DX && i < 214*DX) && (i%DX >= 302 && i%DX < 382 )) ||
				  	((i >= 134*DX && i < 214*DX) && (i%DX >= 386 && i%DX < 466 )) ||
				  	((i >= 218*DX && i < 298*DX) && (i%DX >= 134 && i%DX < 214 )) ||
				  	((i >= 218*DX && i < 298*DX) && (i%DX >= 218 && i%DX < 298 )) ||
				  	((i >= 218*DX && i < 298*DX) && (i%DX >= 302 && i%DX < 382 )) ||
				  	((i >= 218*DX && i < 298*DX) && (i%DX >= 386 && i%DX < 466 )) ||
				  	((i >= 302*DX && i < 382*DX) && (i%DX >= 134 && i%DX < 214 )) ||
				  	((i >= 302*DX && i < 382*DX) && (i%DX >= 218 && i%DX < 298 )) ||
				  	((i >= 302*DX && i < 382*DX) && (i%DX >= 302 && i%DX < 382 )) ||
				  	((i >= 302*DX && i < 382*DX) && (i%DX >= 386 && i%DX < 466 )) ||
				  	((i >= 386*DX && i < 466*DX) && (i%DX >= 134 && i%DX < 214 )) ||
				  	((i >= 386*DX && i < 466*DX) && (i%DX >= 218 && i%DX < 298 )) ||
				  	((i >= 386*DX && i < 466*DX) && (i%DX >= 302 && i%DX < 382 )) ||
				  	((i >= 386*DX && i < 466*DX) && (i%DX >= 386 && i%DX < 466 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 4090: // 16 cluster (4path) --> 90x90x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 114*DX && i < 204*DX) && (i%DX >= 114 && i%DX < 204 )) || 
				  	((i >= 114*DX && i < 204*DX) && (i%DX >= 208 && i%DX < 298 )) ||
				  	((i >= 114*DX && i < 204*DX) && (i%DX >= 302 && i%DX < 392 )) ||
				  	((i >= 114*DX && i < 204*DX) && (i%DX >= 396 && i%DX < 486 )) ||
				  	((i >= 208*DX && i < 298*DX) && (i%DX >= 114 && i%DX < 204 )) ||
				  	((i >= 208*DX && i < 298*DX) && (i%DX >= 208 && i%DX < 298 )) ||
				  	((i >= 208*DX && i < 298*DX) && (i%DX >= 302 && i%DX < 392 )) ||
				  	((i >= 208*DX && i < 298*DX) && (i%DX >= 396 && i%DX < 486 )) ||
				  	((i >= 302*DX && i < 392*DX) && (i%DX >= 114 && i%DX < 204 )) ||
				  	((i >= 302*DX && i < 392*DX) && (i%DX >= 208 && i%DX < 298 )) ||
				  	((i >= 302*DX && i < 392*DX) && (i%DX >= 302 && i%DX < 392 )) ||
				  	((i >= 302*DX && i < 392*DX) && (i%DX >= 396 && i%DX < 486 )) ||
				  	((i >= 396*DX && i < 486*DX) && (i%DX >= 114 && i%DX < 204 )) ||
				  	((i >= 396*DX && i < 486*DX) && (i%DX >= 208 && i%DX < 298 )) ||
				  	((i >= 396*DX && i < 486*DX) && (i%DX >= 302 && i%DX < 392 )) ||
				  	((i >= 396*DX && i < 486*DX) && (i%DX >= 396 && i%DX < 486 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 4097: // 16 cluster (4path) --> 97x97x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 197*DX) && (i%DX >= 100 && i%DX < 197 )) || 
				  	((i >= 100*DX && i < 197*DX) && (i%DX >= 201 && i%DX < 298 )) ||
				  	((i >= 100*DX && i < 197*DX) && (i%DX >= 302 && i%DX < 399 )) ||
				  	((i >= 100*DX && i < 197*DX) && (i%DX >= 403 && i%DX < 500 )) ||
				  	((i >= 201*DX && i < 298*DX) && (i%DX >= 100 && i%DX < 197 )) ||
				  	((i >= 201*DX && i < 298*DX) && (i%DX >= 201 && i%DX < 298 )) ||
				  	((i >= 201*DX && i < 298*DX) && (i%DX >= 302 && i%DX < 399 )) ||
				  	((i >= 201*DX && i < 298*DX) && (i%DX >= 403 && i%DX < 500 )) ||
				  	((i >= 302*DX && i < 399*DX) && (i%DX >= 100 && i%DX < 197 )) ||
				  	((i >= 302*DX && i < 399*DX) && (i%DX >= 201 && i%DX < 298 )) ||
				  	((i >= 302*DX && i < 399*DX) && (i%DX >= 302 && i%DX < 399 )) ||
				  	((i >= 302*DX && i < 399*DX) && (i%DX >= 403 && i%DX < 500 )) ||
				  	((i >= 403*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 197 )) ||
				  	((i >= 403*DX && i < 500*DX) && (i%DX >= 201 && i%DX < 298 )) ||
				  	((i >= 403*DX && i < 500*DX) && (i%DX >= 302 && i%DX < 399 )) ||
				  	((i >= 403*DX && i < 500*DX) && (i%DX >= 403 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 4100: // 16 cluster (4path) --> 100x100x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  94*DX && i < 194*DX) && (i%DX >=  94 && i%DX < 194 )) || 
				  	((i >=  94*DX && i < 194*DX) && (i%DX >= 198 && i%DX < 298 )) ||
				  	((i >=  94*DX && i < 194*DX) && (i%DX >= 302 && i%DX < 402 )) ||
				  	((i >=  94*DX && i < 194*DX) && (i%DX >= 406 && i%DX < 506 )) ||
				  	((i >= 198*DX && i < 298*DX) && (i%DX >=  94 && i%DX < 194 )) ||
				  	((i >= 198*DX && i < 298*DX) && (i%DX >= 198 && i%DX < 298 )) ||
				  	((i >= 198*DX && i < 298*DX) && (i%DX >= 302 && i%DX < 402 )) ||
				  	((i >= 198*DX && i < 298*DX) && (i%DX >= 406 && i%DX < 506 )) ||
				  	((i >= 302*DX && i < 402*DX) && (i%DX >=  94 && i%DX < 194 )) ||
				  	((i >= 302*DX && i < 402*DX) && (i%DX >= 198 && i%DX < 298 )) ||
				  	((i >= 302*DX && i < 402*DX) && (i%DX >= 302 && i%DX < 402 )) ||
				  	((i >= 302*DX && i < 402*DX) && (i%DX >= 406 && i%DX < 506 )) ||
				  	((i >= 406*DX && i < 506*DX) && (i%DX >=  94 && i%DX < 194 )) ||
				  	((i >= 406*DX && i < 506*DX) && (i%DX >= 198 && i%DX < 298 )) ||
				  	((i >= 406*DX && i < 506*DX) && (i%DX >= 302 && i%DX < 402 )) ||
				  	((i >= 406*DX && i < 506*DX) && (i%DX >= 406 && i%DX < 506 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 4110: // 16 cluster (4path) --> 110x110x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  74*DX && i < 184*DX) && (i%DX >=  74 && i%DX < 184 )) || 
				  	((i >=  74*DX && i < 184*DX) && (i%DX >= 188 && i%DX < 298 )) ||
				  	((i >=  74*DX && i < 184*DX) && (i%DX >= 302 && i%DX < 412 )) ||
				  	((i >=  74*DX && i < 184*DX) && (i%DX >= 416 && i%DX < 526 )) ||
				  	((i >= 188*DX && i < 298*DX) && (i%DX >=  74 && i%DX < 184 )) ||
				  	((i >= 188*DX && i < 298*DX) && (i%DX >= 188 && i%DX < 298 )) ||
				  	((i >= 188*DX && i < 298*DX) && (i%DX >= 302 && i%DX < 412 )) ||
				  	((i >= 188*DX && i < 298*DX) && (i%DX >= 416 && i%DX < 526 )) ||
				  	((i >= 302*DX && i < 412*DX) && (i%DX >=  74 && i%DX < 184 )) ||
				  	((i >= 302*DX && i < 412*DX) && (i%DX >= 188 && i%DX < 298 )) ||
				  	((i >= 302*DX && i < 412*DX) && (i%DX >= 302 && i%DX < 412 )) ||
				  	((i >= 302*DX && i < 412*DX) && (i%DX >= 416 && i%DX < 526 )) ||
				  	((i >= 416*DX && i < 526*DX) && (i%DX >=  74 && i%DX < 184 )) ||
				  	((i >= 416*DX && i < 526*DX) && (i%DX >= 188 && i%DX < 298 )) ||
				  	((i >= 416*DX && i < 526*DX) && (i%DX >= 302 && i%DX < 412 )) ||
				  	((i >= 416*DX && i < 526*DX) && (i%DX >= 416 && i%DX < 526 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 8110: // 16 cluster (8path) --> 110x110x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  68*DX && i < 178*DX) && (i%DX >=  68 && i%DX < 178 )) || 
				  	((i >=  68*DX && i < 178*DX) && (i%DX >= 186 && i%DX < 296 )) ||
				  	((i >=  68*DX && i < 178*DX) && (i%DX >= 304 && i%DX < 414 )) ||
				  	((i >=  68*DX && i < 178*DX) && (i%DX >= 422 && i%DX < 532 )) ||
				  	((i >= 186*DX && i < 296*DX) && (i%DX >=  68 && i%DX < 178 )) ||
				  	((i >= 186*DX && i < 296*DX) && (i%DX >= 186 && i%DX < 296 )) ||
				  	((i >= 186*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 414 )) ||
				  	((i >= 186*DX && i < 296*DX) && (i%DX >= 422 && i%DX < 532 )) ||
				  	((i >= 304*DX && i < 414*DX) && (i%DX >=  68 && i%DX < 178 )) ||
				  	((i >= 304*DX && i < 414*DX) && (i%DX >= 186 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 414*DX) && (i%DX >= 304 && i%DX < 414 )) ||
				  	((i >= 304*DX && i < 414*DX) && (i%DX >= 422 && i%DX < 532 )) ||
				  	((i >= 422*DX && i < 532*DX) && (i%DX >=  68 && i%DX < 178 )) ||
				  	((i >= 422*DX && i < 532*DX) && (i%DX >= 186 && i%DX < 296 )) ||
				  	((i >= 422*DX && i < 532*DX) && (i%DX >= 304 && i%DX < 414 )) ||
				  	((i >= 422*DX && i < 532*DX) && (i%DX >= 422 && i%DX < 532 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 8100: // 16 cluster (8path) --> 100x100x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  88*DX && i < 188*DX) && (i%DX >=  88 && i%DX < 188 )) || 
				  	((i >=  88*DX && i < 188*DX) && (i%DX >= 196 && i%DX < 296 )) ||
				  	((i >=  88*DX && i < 188*DX) && (i%DX >= 304 && i%DX < 404 )) ||
				  	((i >=  88*DX && i < 188*DX) && (i%DX >= 412 && i%DX < 512 )) ||
				  	((i >= 196*DX && i < 296*DX) && (i%DX >=  88 && i%DX < 188 )) ||
				  	((i >= 196*DX && i < 296*DX) && (i%DX >= 196 && i%DX < 296 )) ||
				  	((i >= 196*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 404 )) ||
				  	((i >= 196*DX && i < 296*DX) && (i%DX >= 412 && i%DX < 512 )) ||
				  	((i >= 304*DX && i < 404*DX) && (i%DX >=  88 && i%DX < 188 )) ||
				  	((i >= 304*DX && i < 404*DX) && (i%DX >= 196 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 404*DX) && (i%DX >= 304 && i%DX < 404 )) ||
				  	((i >= 304*DX && i < 404*DX) && (i%DX >= 412 && i%DX < 512 )) ||
				  	((i >= 412*DX && i < 512*DX) && (i%DX >=  88 && i%DX < 188 )) ||
				  	((i >= 412*DX && i < 512*DX) && (i%DX >= 196 && i%DX < 296 )) ||
				  	((i >= 412*DX && i < 512*DX) && (i%DX >= 304 && i%DX < 404 )) ||
				  	((i >= 412*DX && i < 512*DX) && (i%DX >= 412 && i%DX < 512 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 8094: // 16 cluster (8path) --> 94x94x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 194*DX) && (i%DX >= 100 && i%DX < 194 )) || 
				  	((i >= 100*DX && i < 194*DX) && (i%DX >= 202 && i%DX < 296 )) ||
				  	((i >= 100*DX && i < 194*DX) && (i%DX >= 304 && i%DX < 398 )) ||
				  	((i >= 100*DX && i < 194*DX) && (i%DX >= 406 && i%DX < 500 )) ||
				  	((i >= 202*DX && i < 296*DX) && (i%DX >= 100 && i%DX < 194 )) ||
				  	((i >= 202*DX && i < 296*DX) && (i%DX >= 202 && i%DX < 296 )) ||
				  	((i >= 202*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 398 )) ||
				  	((i >= 202*DX && i < 296*DX) && (i%DX >= 406 && i%DX < 500 )) ||
				  	((i >= 304*DX && i < 398*DX) && (i%DX >= 100 && i%DX < 194 )) ||
				  	((i >= 304*DX && i < 398*DX) && (i%DX >= 202 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 398*DX) && (i%DX >= 304 && i%DX < 398 )) ||
				  	((i >= 304*DX && i < 398*DX) && (i%DX >= 406 && i%DX < 500 )) ||
				  	((i >= 406*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 194 )) ||
				  	((i >= 406*DX && i < 500*DX) && (i%DX >= 202 && i%DX < 296 )) ||
				  	((i >= 406*DX && i < 500*DX) && (i%DX >= 304 && i%DX < 398 )) ||
				  	((i >= 406*DX && i < 500*DX) && (i%DX >= 406 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 8090: // 16 cluster (8path) --> 90x90x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 108*DX && i < 198*DX) && (i%DX >= 108 && i%DX < 198 )) || 
				  	((i >= 108*DX && i < 198*DX) && (i%DX >= 206 && i%DX < 296 )) ||
				  	((i >= 108*DX && i < 198*DX) && (i%DX >= 304 && i%DX < 394 )) ||
				  	((i >= 108*DX && i < 198*DX) && (i%DX >= 402 && i%DX < 492 )) ||
				  	((i >= 206*DX && i < 296*DX) && (i%DX >= 108 && i%DX < 198 )) ||
				  	((i >= 206*DX && i < 296*DX) && (i%DX >= 206 && i%DX < 296 )) ||
				  	((i >= 206*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 394 )) ||
				  	((i >= 206*DX && i < 296*DX) && (i%DX >= 402 && i%DX < 492 )) ||
				  	((i >= 304*DX && i < 394*DX) && (i%DX >= 108 && i%DX < 198 )) ||
				  	((i >= 304*DX && i < 394*DX) && (i%DX >= 206 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 394*DX) && (i%DX >= 304 && i%DX < 394 )) ||
				  	((i >= 304*DX && i < 394*DX) && (i%DX >= 402 && i%DX < 492 )) ||
				  	((i >= 402*DX && i < 492*DX) && (i%DX >= 108 && i%DX < 198 )) ||
				  	((i >= 402*DX && i < 492*DX) && (i%DX >= 206 && i%DX < 296 )) ||
				  	((i >= 402*DX && i < 492*DX) && (i%DX >= 304 && i%DX < 394 )) ||
				  	((i >= 402*DX && i < 492*DX) && (i%DX >= 402 && i%DX < 492 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 8080: // 16 cluster (8path) --> 80x80x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 128*DX && i < 208*DX) && (i%DX >= 128 && i%DX < 208 )) || 
				  	((i >= 128*DX && i < 208*DX) && (i%DX >= 216 && i%DX < 296 )) ||
				  	((i >= 128*DX && i < 208*DX) && (i%DX >= 304 && i%DX < 384 )) ||
				  	((i >= 128*DX && i < 208*DX) && (i%DX >= 392 && i%DX < 472 )) ||
				  	((i >= 216*DX && i < 296*DX) && (i%DX >= 128 && i%DX < 208 )) ||
				  	((i >= 216*DX && i < 296*DX) && (i%DX >= 216 && i%DX < 296 )) ||
				  	((i >= 216*DX && i < 296*DX) && (i%DX >= 304 && i%DX < 384 )) ||
				  	((i >= 216*DX && i < 296*DX) && (i%DX >= 392 && i%DX < 472 )) ||
				  	((i >= 304*DX && i < 384*DX) && (i%DX >= 128 && i%DX < 208 )) ||
				  	((i >= 304*DX && i < 384*DX) && (i%DX >= 216 && i%DX < 296 )) ||
				  	((i >= 304*DX && i < 384*DX) && (i%DX >= 304 && i%DX < 384 )) ||
				  	((i >= 304*DX && i < 384*DX) && (i%DX >= 392 && i%DX < 472 )) ||
				  	((i >= 392*DX && i < 472*DX) && (i%DX >= 128 && i%DX < 208 )) ||
				  	((i >= 392*DX && i < 472*DX) && (i%DX >= 216 && i%DX < 296 )) ||
				  	((i >= 392*DX && i < 472*DX) && (i%DX >= 304 && i%DX < 384 )) ||
				  	((i >= 392*DX && i < 472*DX) && (i%DX >= 392 && i%DX < 472 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 12110: // 16 cluster (12path) --> 110x110x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  62*DX && i < 172*DX) && (i%DX >=  62 && i%DX < 172 )) || 
				  	((i >=  62*DX && i < 172*DX) && (i%DX >= 184 && i%DX < 294 )) ||
				  	((i >=  62*DX && i < 172*DX) && (i%DX >= 306 && i%DX < 416 )) ||
				  	((i >=  62*DX && i < 172*DX) && (i%DX >= 428 && i%DX < 538 )) ||
				  	((i >= 184*DX && i < 294*DX) && (i%DX >=  62 && i%DX < 172 )) ||
				  	((i >= 184*DX && i < 294*DX) && (i%DX >= 184 && i%DX < 294 )) ||
				  	((i >= 184*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 416 )) ||
				  	((i >= 184*DX && i < 294*DX) && (i%DX >= 428 && i%DX < 538 )) ||
				  	((i >= 306*DX && i < 416*DX) && (i%DX >=  62 && i%DX < 172 )) ||
				  	((i >= 306*DX && i < 416*DX) && (i%DX >= 184 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 416*DX) && (i%DX >= 306 && i%DX < 416 )) ||
				  	((i >= 306*DX && i < 416*DX) && (i%DX >= 428 && i%DX < 538 )) ||
				  	((i >= 428*DX && i < 538*DX) && (i%DX >=  62 && i%DX < 172 )) ||
				  	((i >= 428*DX && i < 538*DX) && (i%DX >= 184 && i%DX < 294 )) ||
				  	((i >= 428*DX && i < 538*DX) && (i%DX >= 306 && i%DX < 416 )) ||
				  	((i >= 428*DX && i < 538*DX) && (i%DX >= 428 && i%DX < 538 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 12100: // 16 cluster (12path) --> 100x100x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  82*DX && i < 182*DX) && (i%DX >=  82 && i%DX < 182 )) || 
				  	((i >=  82*DX && i < 182*DX) && (i%DX >= 194 && i%DX < 294 )) ||
				  	((i >=  82*DX && i < 182*DX) && (i%DX >= 306 && i%DX < 406 )) ||
				  	((i >=  82*DX && i < 182*DX) && (i%DX >= 418 && i%DX < 518 )) ||
				  	((i >= 194*DX && i < 294*DX) && (i%DX >=  82 && i%DX < 182 )) ||
				  	((i >= 194*DX && i < 294*DX) && (i%DX >= 194 && i%DX < 294 )) ||
				  	((i >= 194*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 406 )) ||
				  	((i >= 194*DX && i < 294*DX) && (i%DX >= 418 && i%DX < 518 )) ||
				  	((i >= 306*DX && i < 406*DX) && (i%DX >=  82 && i%DX < 182 )) ||
				  	((i >= 306*DX && i < 406*DX) && (i%DX >= 194 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 406*DX) && (i%DX >= 306 && i%DX < 406 )) ||
				  	((i >= 306*DX && i < 406*DX) && (i%DX >= 418 && i%DX < 518 )) ||
				  	((i >= 418*DX && i < 518*DX) && (i%DX >=  82 && i%DX < 182 )) ||
				  	((i >= 418*DX && i < 518*DX) && (i%DX >= 194 && i%DX < 294 )) ||
				  	((i >= 418*DX && i < 518*DX) && (i%DX >= 306 && i%DX < 406 )) ||
				  	((i >= 418*DX && i < 518*DX) && (i%DX >= 418 && i%DX < 518 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 12091: // 16 cluster (12path) --> 91x91x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 191*DX) && (i%DX >= 100 && i%DX < 191 )) || 
				  	((i >= 100*DX && i < 191*DX) && (i%DX >= 203 && i%DX < 294 )) ||
				  	((i >= 100*DX && i < 191*DX) && (i%DX >= 306 && i%DX < 397 )) ||
				  	((i >= 100*DX && i < 191*DX) && (i%DX >= 409 && i%DX < 500 )) ||
				  	((i >= 203*DX && i < 294*DX) && (i%DX >= 100 && i%DX < 191 )) ||
				  	((i >= 203*DX && i < 294*DX) && (i%DX >= 203 && i%DX < 294 )) ||
				  	((i >= 203*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 397 )) ||
				  	((i >= 203*DX && i < 294*DX) && (i%DX >= 409 && i%DX < 500 )) ||
				  	((i >= 306*DX && i < 397*DX) && (i%DX >= 100 && i%DX < 191 )) ||
				  	((i >= 306*DX && i < 397*DX) && (i%DX >= 203 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 397*DX) && (i%DX >= 306 && i%DX < 397 )) ||
				  	((i >= 306*DX && i < 397*DX) && (i%DX >= 409 && i%DX < 500 )) ||
				  	((i >= 409*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 191 )) ||
				  	((i >= 409*DX && i < 500*DX) && (i%DX >= 203 && i%DX < 294 )) ||
				  	((i >= 409*DX && i < 500*DX) && (i%DX >= 306 && i%DX < 397 )) ||
				  	((i >= 409*DX && i < 500*DX) && (i%DX >= 409 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 12090: // 16 cluster (12path) --> 90x90x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 102*DX && i < 192*DX) && (i%DX >= 102 && i%DX < 192 )) || 
				  	((i >= 102*DX && i < 192*DX) && (i%DX >= 204 && i%DX < 294 )) ||
				  	((i >= 102*DX && i < 192*DX) && (i%DX >= 306 && i%DX < 396 )) ||
				  	((i >= 102*DX && i < 192*DX) && (i%DX >= 408 && i%DX < 498 )) ||
				  	((i >= 204*DX && i < 294*DX) && (i%DX >= 102 && i%DX < 192 )) ||
				  	((i >= 204*DX && i < 294*DX) && (i%DX >= 204 && i%DX < 294 )) ||
				  	((i >= 204*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 396 )) ||
				  	((i >= 204*DX && i < 294*DX) && (i%DX >= 408 && i%DX < 498 )) ||
				  	((i >= 306*DX && i < 396*DX) && (i%DX >= 102 && i%DX < 192 )) ||
				  	((i >= 306*DX && i < 396*DX) && (i%DX >= 204 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 396*DX) && (i%DX >= 306 && i%DX < 396 )) ||
				  	((i >= 306*DX && i < 396*DX) && (i%DX >= 408 && i%DX < 498 )) ||
				  	((i >= 408*DX && i < 498*DX) && (i%DX >= 102 && i%DX < 192 )) ||
				  	((i >= 408*DX && i < 498*DX) && (i%DX >= 204 && i%DX < 294 )) ||
				  	((i >= 408*DX && i < 498*DX) && (i%DX >= 306 && i%DX < 396 )) ||
				  	((i >= 408*DX && i < 498*DX) && (i%DX >= 408 && i%DX < 498 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 12080: // 16 cluster (12path) --> 80x80x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 122*DX && i < 202*DX) && (i%DX >= 122 && i%DX < 202 )) || 
				  	((i >= 122*DX && i < 202*DX) && (i%DX >= 214 && i%DX < 294 )) ||
				  	((i >= 122*DX && i < 202*DX) && (i%DX >= 306 && i%DX < 386 )) ||
				  	((i >= 122*DX && i < 202*DX) && (i%DX >= 398 && i%DX < 478 )) ||
				  	((i >= 214*DX && i < 294*DX) && (i%DX >= 122 && i%DX < 202 )) ||
				  	((i >= 214*DX && i < 294*DX) && (i%DX >= 214 && i%DX < 294 )) ||
				  	((i >= 214*DX && i < 294*DX) && (i%DX >= 306 && i%DX < 386 )) ||
				  	((i >= 214*DX && i < 294*DX) && (i%DX >= 398 && i%DX < 478 )) ||
				  	((i >= 306*DX && i < 386*DX) && (i%DX >= 122 && i%DX < 202 )) ||
				  	((i >= 306*DX && i < 386*DX) && (i%DX >= 214 && i%DX < 294 )) ||
				  	((i >= 306*DX && i < 386*DX) && (i%DX >= 306 && i%DX < 386 )) ||
				  	((i >= 306*DX && i < 386*DX) && (i%DX >= 398 && i%DX < 478 )) ||
				  	((i >= 398*DX && i < 478*DX) && (i%DX >= 122 && i%DX < 202 )) ||
				  	((i >= 398*DX && i < 478*DX) && (i%DX >= 214 && i%DX < 294 )) ||
				  	((i >= 398*DX && i < 478*DX) && (i%DX >= 306 && i%DX < 386 )) ||
				  	((i >= 398*DX && i < 478*DX) && (i%DX >= 398 && i%DX < 478 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 16110: // 16 cluster (16path) --> 110x110x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  56*DX && i < 166*DX) && (i%DX >=  56 && i%DX < 166 )) || 
				  	((i >=  56*DX && i < 166*DX) && (i%DX >= 182 && i%DX < 292 )) ||
				  	((i >=  56*DX && i < 166*DX) && (i%DX >= 308 && i%DX < 418 )) ||
				  	((i >=  56*DX && i < 166*DX) && (i%DX >= 434 && i%DX < 544 )) ||
				  	((i >= 182*DX && i < 292*DX) && (i%DX >=  56 && i%DX < 166 )) ||
				  	((i >= 182*DX && i < 292*DX) && (i%DX >= 182 && i%DX < 292 )) ||
				  	((i >= 182*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 418 )) ||
				  	((i >= 182*DX && i < 292*DX) && (i%DX >= 434 && i%DX < 544 )) ||
				  	((i >= 308*DX && i < 418*DX) && (i%DX >=  56 && i%DX < 166 )) ||
				  	((i >= 308*DX && i < 418*DX) && (i%DX >= 182 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 418*DX) && (i%DX >= 308 && i%DX < 418 )) ||
				  	((i >= 308*DX && i < 418*DX) && (i%DX >= 434 && i%DX < 544 )) ||
				  	((i >= 434*DX && i < 544*DX) && (i%DX >=  56 && i%DX < 166 )) ||
				  	((i >= 434*DX && i < 544*DX) && (i%DX >= 182 && i%DX < 292 )) ||
				  	((i >= 434*DX && i < 544*DX) && (i%DX >= 308 && i%DX < 418 )) ||
				  	((i >= 434*DX && i < 544*DX) && (i%DX >= 434 && i%DX < 544 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 16100: // 16 cluster (16path) --> 100x100x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  76*DX && i < 176*DX) && (i%DX >=  76 && i%DX < 176 )) || 
				  	((i >=  76*DX && i < 176*DX) && (i%DX >= 192 && i%DX < 292 )) ||
				  	((i >=  76*DX && i < 176*DX) && (i%DX >= 308 && i%DX < 408 )) ||
				  	((i >=  76*DX && i < 176*DX) && (i%DX >= 424 && i%DX < 524 )) ||
				  	((i >= 192*DX && i < 292*DX) && (i%DX >=  76 && i%DX < 176 )) ||
				  	((i >= 192*DX && i < 292*DX) && (i%DX >= 192 && i%DX < 292 )) ||
				  	((i >= 192*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 408 )) ||
				  	((i >= 192*DX && i < 292*DX) && (i%DX >= 424 && i%DX < 524 )) ||
				  	((i >= 308*DX && i < 408*DX) && (i%DX >=  76 && i%DX < 176 )) ||
				  	((i >= 308*DX && i < 408*DX) && (i%DX >= 192 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 408*DX) && (i%DX >= 308 && i%DX < 408 )) ||
				  	((i >= 308*DX && i < 408*DX) && (i%DX >= 424 && i%DX < 524 )) ||
				  	((i >= 424*DX && i < 524*DX) && (i%DX >=  76 && i%DX < 176 )) ||
				  	((i >= 424*DX && i < 524*DX) && (i%DX >= 192 && i%DX < 292 )) ||
				  	((i >= 424*DX && i < 524*DX) && (i%DX >= 308 && i%DX < 408 )) ||
				  	((i >= 424*DX && i < 524*DX) && (i%DX >= 424 && i%DX < 524 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 16090: // 16 cluster (16path) --> 90x90x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  96*DX && i < 186*DX) && (i%DX >=  96 && i%DX < 186 )) || 
				  	((i >=  96*DX && i < 186*DX) && (i%DX >= 202 && i%DX < 292 )) ||
				  	((i >=  96*DX && i < 186*DX) && (i%DX >= 308 && i%DX < 398 )) ||
				  	((i >=  96*DX && i < 186*DX) && (i%DX >= 414 && i%DX < 504 )) ||
				  	((i >= 202*DX && i < 292*DX) && (i%DX >=  96 && i%DX < 186 )) ||
				  	((i >= 202*DX && i < 292*DX) && (i%DX >= 202 && i%DX < 292 )) ||
				  	((i >= 202*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 398 )) ||
				  	((i >= 202*DX && i < 292*DX) && (i%DX >= 414 && i%DX < 504 )) ||
				  	((i >= 308*DX && i < 398*DX) && (i%DX >=  96 && i%DX < 186 )) ||
				  	((i >= 308*DX && i < 398*DX) && (i%DX >= 202 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 398*DX) && (i%DX >= 308 && i%DX < 398 )) ||
				  	((i >= 308*DX && i < 398*DX) && (i%DX >= 414 && i%DX < 504 )) ||
				  	((i >= 414*DX && i < 504*DX) && (i%DX >=  96 && i%DX < 186 )) ||
				  	((i >= 414*DX && i < 504*DX) && (i%DX >= 202 && i%DX < 292 )) ||
				  	((i >= 414*DX && i < 504*DX) && (i%DX >= 308 && i%DX < 398 )) ||
				  	((i >= 414*DX && i < 504*DX) && (i%DX >= 414 && i%DX < 504 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 16088: // 16 cluster (16path) --> 88x88x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 188*DX) && (i%DX >= 100 && i%DX < 188 )) || 
				  	((i >= 100*DX && i < 188*DX) && (i%DX >= 204 && i%DX < 292 )) ||
				  	((i >= 100*DX && i < 188*DX) && (i%DX >= 308 && i%DX < 396 )) ||
				  	((i >= 100*DX && i < 188*DX) && (i%DX >= 412 && i%DX < 500 )) ||
				  	((i >= 204*DX && i < 292*DX) && (i%DX >= 100 && i%DX < 188 )) ||
				  	((i >= 204*DX && i < 292*DX) && (i%DX >= 204 && i%DX < 292 )) ||
				  	((i >= 204*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 396 )) ||
				  	((i >= 204*DX && i < 292*DX) && (i%DX >= 412 && i%DX < 500 )) ||
				  	((i >= 308*DX && i < 396*DX) && (i%DX >= 100 && i%DX < 188 )) ||
				  	((i >= 308*DX && i < 396*DX) && (i%DX >= 204 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 396*DX) && (i%DX >= 308 && i%DX < 396 )) ||
				  	((i >= 308*DX && i < 396*DX) && (i%DX >= 412 && i%DX < 500 )) ||
				  	((i >= 412*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 188 )) ||
				  	((i >= 412*DX && i < 500*DX) && (i%DX >= 204 && i%DX < 292 )) ||
				  	((i >= 412*DX && i < 500*DX) && (i%DX >= 308 && i%DX < 396 )) ||
				  	((i >= 412*DX && i < 500*DX) && (i%DX >= 412 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 16080: // 16 cluster (16path) --> 80x80x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 116*DX && i < 196*DX) && (i%DX >= 116 && i%DX < 196 )) || 
				  	((i >= 116*DX && i < 196*DX) && (i%DX >= 212 && i%DX < 292 )) ||
				  	((i >= 116*DX && i < 196*DX) && (i%DX >= 308 && i%DX < 388 )) ||
				  	((i >= 116*DX && i < 196*DX) && (i%DX >= 404 && i%DX < 484 )) ||
				  	((i >= 212*DX && i < 292*DX) && (i%DX >= 116 && i%DX < 196 )) ||
				  	((i >= 212*DX && i < 292*DX) && (i%DX >= 212 && i%DX < 292 )) ||
				  	((i >= 212*DX && i < 292*DX) && (i%DX >= 308 && i%DX < 388 )) ||
				  	((i >= 212*DX && i < 292*DX) && (i%DX >= 404 && i%DX < 484 )) ||
				  	((i >= 308*DX && i < 388*DX) && (i%DX >= 116 && i%DX < 196 )) ||
				  	((i >= 308*DX && i < 388*DX) && (i%DX >= 212 && i%DX < 292 )) ||
				  	((i >= 308*DX && i < 388*DX) && (i%DX >= 308 && i%DX < 388 )) ||
				  	((i >= 308*DX && i < 388*DX) && (i%DX >= 404 && i%DX < 484 )) ||
				  	((i >= 404*DX && i < 484*DX) && (i%DX >= 116 && i%DX < 196 )) ||
				  	((i >= 404*DX && i < 484*DX) && (i%DX >= 212 && i%DX < 292 )) ||
				  	((i >= 404*DX && i < 484*DX) && (i%DX >= 308 && i%DX < 388 )) ||
				  	((i >= 404*DX && i < 484*DX) && (i%DX >= 404 && i%DX < 484 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20110: // 16 cluster (20path) --> 110x110x16 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  50*DX && i < 160*DX) && (i%DX >=  50 && i%DX < 160 )) || 
				  	((i >=  50*DX && i < 160*DX) && (i%DX >= 180 && i%DX < 290 )) ||
				  	((i >=  50*DX && i < 160*DX) && (i%DX >= 310 && i%DX < 420 )) ||
				  	((i >=  50*DX && i < 160*DX) && (i%DX >= 440 && i%DX < 550 )) ||
				  	((i >= 180*DX && i < 290*DX) && (i%DX >=  50 && i%DX < 160 )) ||
				  	((i >= 180*DX && i < 290*DX) && (i%DX >= 180 && i%DX < 290 )) ||
				  	((i >= 180*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 420 )) ||
				  	((i >= 180*DX && i < 290*DX) && (i%DX >= 440 && i%DX < 550 )) ||
				  	((i >= 310*DX && i < 420*DX) && (i%DX >=  50 && i%DX < 160 )) ||
				  	((i >= 310*DX && i < 420*DX) && (i%DX >= 180 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 420*DX) && (i%DX >= 310 && i%DX < 420 )) ||
				  	((i >= 310*DX && i < 420*DX) && (i%DX >= 440 && i%DX < 550 )) ||
				  	((i >= 440*DX && i < 550*DX) && (i%DX >=  50 && i%DX < 160 )) ||
				  	((i >= 440*DX && i < 550*DX) && (i%DX >= 180 && i%DX < 290 )) ||
				  	((i >= 440*DX && i < 550*DX) && (i%DX >= 310 && i%DX < 420 )) ||
				  	((i >= 440*DX && i < 550*DX) && (i%DX >= 440 && i%DX < 550 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20100: // 16 cluster (20path) --> 100x100x16 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  70*DX && i < 170*DX) && (i%DX >=  70 && i%DX < 170 )) || 
				  	((i >=  70*DX && i < 170*DX) && (i%DX >= 190 && i%DX < 290 )) ||
				  	((i >=  70*DX && i < 170*DX) && (i%DX >= 310 && i%DX < 410 )) ||
				  	((i >=  70*DX && i < 170*DX) && (i%DX >= 430 && i%DX < 530 )) ||
				  	((i >= 190*DX && i < 290*DX) && (i%DX >=  70 && i%DX < 170 )) ||
				  	((i >= 190*DX && i < 290*DX) && (i%DX >= 190 && i%DX < 290 )) ||
				  	((i >= 190*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 410 )) ||
				  	((i >= 190*DX && i < 290*DX) && (i%DX >= 430 && i%DX < 530 )) ||
				  	((i >= 310*DX && i < 410*DX) && (i%DX >=  70 && i%DX < 170 )) ||
				  	((i >= 310*DX && i < 410*DX) && (i%DX >= 190 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 410*DX) && (i%DX >= 310 && i%DX < 410 )) ||
				  	((i >= 310*DX && i < 410*DX) && (i%DX >= 430 && i%DX < 530 )) ||
				  	((i >= 430*DX && i < 530*DX) && (i%DX >=  70 && i%DX < 170 )) ||
				  	((i >= 430*DX && i < 530*DX) && (i%DX >= 190 && i%DX < 290 )) ||
				  	((i >= 430*DX && i < 530*DX) && (i%DX >= 310 && i%DX < 410 )) ||
				  	((i >= 430*DX && i < 530*DX) && (i%DX >= 430 && i%DX < 530 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20090: // 16 cluster (20path) --> 90x90x16 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  90*DX && i < 180*DX) && (i%DX >=  90 && i%DX < 180 )) || 
				  	((i >=  90*DX && i < 180*DX) && (i%DX >= 200 && i%DX < 290 )) ||
				  	((i >=  90*DX && i < 180*DX) && (i%DX >= 310 && i%DX < 400 )) ||
				  	((i >=  90*DX && i < 180*DX) && (i%DX >= 420 && i%DX < 510 )) ||
				  	((i >= 200*DX && i < 290*DX) && (i%DX >=  90 && i%DX < 180 )) ||
				  	((i >= 200*DX && i < 290*DX) && (i%DX >= 200 && i%DX < 290 )) ||
				  	((i >= 200*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 400 )) ||
				  	((i >= 200*DX && i < 290*DX) && (i%DX >= 420 && i%DX < 510 )) ||
				  	((i >= 310*DX && i < 400*DX) && (i%DX >=  90 && i%DX < 180 )) ||
				  	((i >= 310*DX && i < 400*DX) && (i%DX >= 200 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 400*DX) && (i%DX >= 310 && i%DX < 400 )) ||
				  	((i >= 310*DX && i < 400*DX) && (i%DX >= 420 && i%DX < 510 )) ||
				  	((i >= 420*DX && i < 510*DX) && (i%DX >=  90 && i%DX < 180 )) ||
				  	((i >= 420*DX && i < 510*DX) && (i%DX >= 200 && i%DX < 290 )) ||
				  	((i >= 420*DX && i < 510*DX) && (i%DX >= 310 && i%DX < 400 )) ||
				  	((i >= 420*DX && i < 510*DX) && (i%DX >= 420 && i%DX < 510 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20085: // 16 cluster (20path) --> 85x85x16 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 185*DX) && (i%DX >= 100 && i%DX < 185 )) || 
				  	((i >= 100*DX && i < 185*DX) && (i%DX >= 205 && i%DX < 290 )) ||
				  	((i >= 100*DX && i < 185*DX) && (i%DX >= 310 && i%DX < 395 )) ||
				  	((i >= 100*DX && i < 185*DX) && (i%DX >= 415 && i%DX < 500 )) ||
				  	((i >= 205*DX && i < 290*DX) && (i%DX >= 100 && i%DX < 185 )) ||
				  	((i >= 205*DX && i < 290*DX) && (i%DX >= 205 && i%DX < 290 )) ||
				  	((i >= 205*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 395 )) ||
				  	((i >= 205*DX && i < 290*DX) && (i%DX >= 415 && i%DX < 500 )) ||
				  	((i >= 310*DX && i < 395*DX) && (i%DX >= 100 && i%DX < 185 )) ||
				  	((i >= 310*DX && i < 395*DX) && (i%DX >= 205 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 395*DX) && (i%DX >= 310 && i%DX < 395 )) ||
				  	((i >= 310*DX && i < 395*DX) && (i%DX >= 415 && i%DX < 500 )) ||
				  	((i >= 415*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 185 )) ||
				  	((i >= 415*DX && i < 500*DX) && (i%DX >= 205 && i%DX < 290 )) ||
				  	((i >= 415*DX && i < 500*DX) && (i%DX >= 310 && i%DX < 395 )) ||
				  	((i >= 415*DX && i < 500*DX) && (i%DX >= 415 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 20080: // 16 cluster (20path) --> 80x80x16 
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 110*DX && i < 190*DX) && (i%DX >= 110 && i%DX < 190 )) || 
				  	((i >= 110*DX && i < 190*DX) && (i%DX >= 210 && i%DX < 290 )) ||
				  	((i >= 110*DX && i < 190*DX) && (i%DX >= 310 && i%DX < 390 )) ||
				  	((i >= 110*DX && i < 190*DX) && (i%DX >= 410 && i%DX < 490 )) ||
				  	((i >= 210*DX && i < 290*DX) && (i%DX >= 110 && i%DX < 190 )) ||
				  	((i >= 210*DX && i < 290*DX) && (i%DX >= 210 && i%DX < 290 )) ||
				  	((i >= 210*DX && i < 290*DX) && (i%DX >= 310 && i%DX < 390 )) ||
				  	((i >= 210*DX && i < 290*DX) && (i%DX >= 410 && i%DX < 490 )) ||
				  	((i >= 310*DX && i < 390*DX) && (i%DX >= 110 && i%DX < 190 )) ||
				  	((i >= 310*DX && i < 390*DX) && (i%DX >= 210 && i%DX < 290 )) ||
				  	((i >= 310*DX && i < 390*DX) && (i%DX >= 310 && i%DX < 390 )) ||
				  	((i >= 310*DX && i < 390*DX) && (i%DX >= 410 && i%DX < 490 )) ||
				  	((i >= 410*DX && i < 490*DX) && (i%DX >= 110 && i%DX < 190 )) ||
				  	((i >= 410*DX && i < 490*DX) && (i%DX >= 210 && i%DX < 290 )) ||
				  	((i >= 410*DX && i < 490*DX) && (i%DX >= 310 && i%DX < 390 )) ||
				  	((i >= 410*DX && i < 490*DX) && (i%DX >= 410 && i%DX < 490 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 24110: // 16 cluster (24path) --> 110x110x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  44*DX && i < 154*DX) && (i%DX >=  44 && i%DX < 154 )) || 
				  	((i >=  44*DX && i < 154*DX) && (i%DX >= 178 && i%DX < 288 )) ||
				  	((i >=  44*DX && i < 154*DX) && (i%DX >= 312 && i%DX < 422 )) ||
				  	((i >=  44*DX && i < 154*DX) && (i%DX >= 446 && i%DX < 556 )) ||
				  	((i >= 178*DX && i < 288*DX) && (i%DX >=  44 && i%DX < 154 )) ||
				  	((i >= 178*DX && i < 288*DX) && (i%DX >= 178 && i%DX < 288 )) ||
				  	((i >= 178*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 422 )) ||
				  	((i >= 178*DX && i < 288*DX) && (i%DX >= 446 && i%DX < 556 )) ||
				  	((i >= 312*DX && i < 422*DX) && (i%DX >=  44 && i%DX < 154 )) ||
				  	((i >= 312*DX && i < 422*DX) && (i%DX >= 178 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 422*DX) && (i%DX >= 312 && i%DX < 422 )) ||
				  	((i >= 312*DX && i < 422*DX) && (i%DX >= 446 && i%DX < 556 )) ||
				  	((i >= 446*DX && i < 556*DX) && (i%DX >=  44 && i%DX < 154 )) ||
				  	((i >= 446*DX && i < 556*DX) && (i%DX >= 178 && i%DX < 288 )) ||
				  	((i >= 446*DX && i < 556*DX) && (i%DX >= 312 && i%DX < 422 )) ||
				  	((i >= 446*DX && i < 556*DX) && (i%DX >= 446 && i%DX < 556 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 24100: // 16 cluster (24path) --> 100x100x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  64*DX && i < 164*DX) && (i%DX >=  64 && i%DX < 164 )) || 
				  	((i >=  64*DX && i < 164*DX) && (i%DX >= 188 && i%DX < 288 )) ||
				  	((i >=  64*DX && i < 164*DX) && (i%DX >= 312 && i%DX < 412 )) ||
				  	((i >=  64*DX && i < 164*DX) && (i%DX >= 436 && i%DX < 536 )) ||
				  	((i >= 188*DX && i < 288*DX) && (i%DX >=  64 && i%DX < 164 )) ||
				  	((i >= 188*DX && i < 288*DX) && (i%DX >= 188 && i%DX < 288 )) ||
				  	((i >= 188*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 412 )) ||
				  	((i >= 188*DX && i < 288*DX) && (i%DX >= 436 && i%DX < 536 )) ||
				  	((i >= 312*DX && i < 412*DX) && (i%DX >=  64 && i%DX < 164 )) ||
				  	((i >= 312*DX && i < 412*DX) && (i%DX >= 188 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 412*DX) && (i%DX >= 312 && i%DX < 412 )) ||
				  	((i >= 312*DX && i < 412*DX) && (i%DX >= 436 && i%DX < 536 )) ||
				  	((i >= 436*DX && i < 536*DX) && (i%DX >=  64 && i%DX < 164 )) ||
				  	((i >= 436*DX && i < 536*DX) && (i%DX >= 188 && i%DX < 288 )) ||
				  	((i >= 436*DX && i < 536*DX) && (i%DX >= 312 && i%DX < 412 )) ||
				  	((i >= 436*DX && i < 536*DX) && (i%DX >= 436 && i%DX < 536 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 24090: // 16 cluster (24path) --> 90x90x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  84*DX && i < 174*DX) && (i%DX >=  84 && i%DX < 174 )) || 
				  	((i >=  84*DX && i < 174*DX) && (i%DX >= 198 && i%DX < 288 )) ||
				  	((i >=  84*DX && i < 174*DX) && (i%DX >= 312 && i%DX < 402 )) ||
				  	((i >=  84*DX && i < 174*DX) && (i%DX >= 426 && i%DX < 516 )) ||
				  	((i >= 198*DX && i < 288*DX) && (i%DX >=  84 && i%DX < 174 )) ||
				  	((i >= 198*DX && i < 288*DX) && (i%DX >= 198 && i%DX < 288 )) ||
				  	((i >= 198*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 402 )) ||
				  	((i >= 198*DX && i < 288*DX) && (i%DX >= 426 && i%DX < 516 )) ||
				  	((i >= 312*DX && i < 402*DX) && (i%DX >=  84 && i%DX < 174 )) ||
				  	((i >= 312*DX && i < 402*DX) && (i%DX >= 198 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 402*DX) && (i%DX >= 312 && i%DX < 402 )) ||
				  	((i >= 312*DX && i < 402*DX) && (i%DX >= 426 && i%DX < 516 )) ||
				  	((i >= 426*DX && i < 516*DX) && (i%DX >=  84 && i%DX < 174 )) ||
				  	((i >= 426*DX && i < 516*DX) && (i%DX >= 198 && i%DX < 288 )) ||
				  	((i >= 426*DX && i < 516*DX) && (i%DX >= 312 && i%DX < 402 )) ||
				  	((i >= 426*DX && i < 516*DX) && (i%DX >= 426 && i%DX < 516 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 24082: // 16 cluster (24path) --> 82x82x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 182*DX) && (i%DX >= 100 && i%DX < 182 )) || 
				  	((i >= 100*DX && i < 182*DX) && (i%DX >= 206 && i%DX < 288 )) ||
				  	((i >= 100*DX && i < 182*DX) && (i%DX >= 312 && i%DX < 394 )) ||
				  	((i >= 100*DX && i < 182*DX) && (i%DX >= 418 && i%DX < 500 )) ||
				  	((i >= 206*DX && i < 288*DX) && (i%DX >= 100 && i%DX < 182 )) ||
				  	((i >= 206*DX && i < 288*DX) && (i%DX >= 206 && i%DX < 288 )) ||
				  	((i >= 206*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 394 )) ||
				  	((i >= 206*DX && i < 288*DX) && (i%DX >= 418 && i%DX < 500 )) ||
				  	((i >= 312*DX && i < 394*DX) && (i%DX >= 100 && i%DX < 182 )) ||
				  	((i >= 312*DX && i < 394*DX) && (i%DX >= 206 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 394*DX) && (i%DX >= 312 && i%DX < 394 )) ||
				  	((i >= 312*DX && i < 394*DX) && (i%DX >= 418 && i%DX < 500 )) ||
				  	((i >= 418*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 182 )) ||
				  	((i >= 418*DX && i < 500*DX) && (i%DX >= 206 && i%DX < 288 )) ||
				  	((i >= 418*DX && i < 500*DX) && (i%DX >= 312 && i%DX < 394 )) ||
				  	((i >= 418*DX && i < 500*DX) && (i%DX >= 418 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 24080: // 16 cluster (24path) --> 80x80x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 104*DX && i < 184*DX) && (i%DX >= 104 && i%DX < 184 )) || 
				  	((i >= 104*DX && i < 184*DX) && (i%DX >= 208 && i%DX < 288 )) ||
				  	((i >= 104*DX && i < 184*DX) && (i%DX >= 312 && i%DX < 392 )) ||
				  	((i >= 104*DX && i < 184*DX) && (i%DX >= 416 && i%DX < 496 )) ||
				  	((i >= 208*DX && i < 288*DX) && (i%DX >= 104 && i%DX < 184 )) ||
				  	((i >= 208*DX && i < 288*DX) && (i%DX >= 208 && i%DX < 288 )) ||
				  	((i >= 208*DX && i < 288*DX) && (i%DX >= 312 && i%DX < 392 )) ||
				  	((i >= 208*DX && i < 288*DX) && (i%DX >= 416 && i%DX < 496 )) ||
				  	((i >= 312*DX && i < 392*DX) && (i%DX >= 104 && i%DX < 184 )) ||
				  	((i >= 312*DX && i < 392*DX) && (i%DX >= 208 && i%DX < 288 )) ||
				  	((i >= 312*DX && i < 392*DX) && (i%DX >= 312 && i%DX < 392 )) ||
				  	((i >= 312*DX && i < 392*DX) && (i%DX >= 416 && i%DX < 496 )) ||
				  	((i >= 416*DX && i < 496*DX) && (i%DX >= 104 && i%DX < 184 )) ||
				  	((i >= 416*DX && i < 496*DX) && (i%DX >= 208 && i%DX < 288 )) ||
				  	((i >= 416*DX && i < 496*DX) && (i%DX >= 312 && i%DX < 392 )) ||
				  	((i >= 416*DX && i < 496*DX) && (i%DX >= 416 && i%DX < 496 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 28110: // 16 cluster (28path) --> 110x110x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  38*DX && i < 148*DX) && (i%DX >=  38 && i%DX < 148 )) || 
				  	((i >=  38*DX && i < 148*DX) && (i%DX >= 176 && i%DX < 286 )) ||
				  	((i >=  38*DX && i < 148*DX) && (i%DX >= 314 && i%DX < 424 )) ||
				  	((i >=  38*DX && i < 148*DX) && (i%DX >= 452 && i%DX < 562 )) ||
				  	((i >= 176*DX && i < 286*DX) && (i%DX >=  38 && i%DX < 148 )) ||
				  	((i >= 176*DX && i < 286*DX) && (i%DX >= 176 && i%DX < 286 )) ||
				  	((i >= 176*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 424 )) ||
				  	((i >= 176*DX && i < 286*DX) && (i%DX >= 452 && i%DX < 562 )) ||
				  	((i >= 314*DX && i < 424*DX) && (i%DX >=  38 && i%DX < 148 )) ||
				  	((i >= 314*DX && i < 424*DX) && (i%DX >= 176 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 424*DX) && (i%DX >= 314 && i%DX < 424 )) ||
				  	((i >= 314*DX && i < 424*DX) && (i%DX >= 452 && i%DX < 562 )) ||
				  	((i >= 452*DX && i < 562*DX) && (i%DX >=  38 && i%DX < 148 )) ||
				  	((i >= 452*DX && i < 562*DX) && (i%DX >= 176 && i%DX < 286 )) ||
				  	((i >= 452*DX && i < 562*DX) && (i%DX >= 314 && i%DX < 424 )) ||
				  	((i >= 452*DX && i < 562*DX) && (i%DX >= 452 && i%DX < 562 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 28100: // 16 cluster (28path) --> 100x100x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  58*DX && i < 158*DX) && (i%DX >=  58 && i%DX < 158 )) || 
				  	((i >=  58*DX && i < 158*DX) && (i%DX >= 186 && i%DX < 286 )) ||
				  	((i >=  58*DX && i < 158*DX) && (i%DX >= 314 && i%DX < 414 )) ||
				  	((i >=  58*DX && i < 158*DX) && (i%DX >= 442 && i%DX < 542 )) ||
				  	((i >= 186*DX && i < 286*DX) && (i%DX >=  58 && i%DX < 158 )) ||
				  	((i >= 186*DX && i < 286*DX) && (i%DX >= 186 && i%DX < 286 )) ||
				  	((i >= 186*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 414 )) ||
				  	((i >= 186*DX && i < 286*DX) && (i%DX >= 442 && i%DX < 542 )) ||
				  	((i >= 314*DX && i < 414*DX) && (i%DX >=  58 && i%DX < 158 )) ||
				  	((i >= 314*DX && i < 414*DX) && (i%DX >= 186 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 414*DX) && (i%DX >= 314 && i%DX < 414 )) ||
				  	((i >= 314*DX && i < 414*DX) && (i%DX >= 442 && i%DX < 542 )) ||
				  	((i >= 442*DX && i < 542*DX) && (i%DX >=  58 && i%DX < 158 )) ||
				  	((i >= 442*DX && i < 542*DX) && (i%DX >= 186 && i%DX < 286 )) ||
				  	((i >= 442*DX && i < 542*DX) && (i%DX >= 314 && i%DX < 414 )) ||
				  	((i >= 442*DX && i < 542*DX) && (i%DX >= 442 && i%DX < 542 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 28090: // 16 cluster (28path) --> 90x90x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  78*DX && i < 168*DX) && (i%DX >=  78 && i%DX < 168 )) || 
				  	((i >=  78*DX && i < 168*DX) && (i%DX >= 196 && i%DX < 286 )) ||
				  	((i >=  78*DX && i < 168*DX) && (i%DX >= 314 && i%DX < 404 )) ||
				  	((i >=  78*DX && i < 168*DX) && (i%DX >= 432 && i%DX < 522 )) ||
				  	((i >= 196*DX && i < 286*DX) && (i%DX >=  78 && i%DX < 168 )) ||
				  	((i >= 196*DX && i < 286*DX) && (i%DX >= 196 && i%DX < 286 )) ||
				  	((i >= 196*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 404 )) ||
				  	((i >= 196*DX && i < 286*DX) && (i%DX >= 432 && i%DX < 522 )) ||
				  	((i >= 314*DX && i < 404*DX) && (i%DX >=  78 && i%DX < 168 )) ||
				  	((i >= 314*DX && i < 404*DX) && (i%DX >= 196 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 404*DX) && (i%DX >= 314 && i%DX < 404 )) ||
				  	((i >= 314*DX && i < 404*DX) && (i%DX >= 432 && i%DX < 522 )) ||
				  	((i >= 432*DX && i < 522*DX) && (i%DX >=  78 && i%DX < 168 )) ||
				  	((i >= 432*DX && i < 522*DX) && (i%DX >= 196 && i%DX < 286 )) ||
				  	((i >= 432*DX && i < 522*DX) && (i%DX >= 314 && i%DX < 404 )) ||
				  	((i >= 432*DX && i < 522*DX) && (i%DX >= 432 && i%DX < 522 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 28080: // 16 cluster (28path) --> 80x80x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  98*DX && i < 178*DX) && (i%DX >=  98 && i%DX < 178 )) || 
				  	((i >=  98*DX && i < 178*DX) && (i%DX >= 206 && i%DX < 286 )) ||
				  	((i >=  98*DX && i < 178*DX) && (i%DX >= 314 && i%DX < 394 )) ||
				  	((i >=  98*DX && i < 178*DX) && (i%DX >= 422 && i%DX < 502 )) ||
				  	((i >= 206*DX && i < 286*DX) && (i%DX >=  98 && i%DX < 178 )) ||
				  	((i >= 206*DX && i < 286*DX) && (i%DX >= 206 && i%DX < 286 )) ||
				  	((i >= 206*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 394 )) ||
				  	((i >= 206*DX && i < 286*DX) && (i%DX >= 422 && i%DX < 502 )) ||
				  	((i >= 314*DX && i < 394*DX) && (i%DX >=  98 && i%DX < 178 )) ||
				  	((i >= 314*DX && i < 394*DX) && (i%DX >= 206 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 394*DX) && (i%DX >= 314 && i%DX < 394 )) ||
				  	((i >= 314*DX && i < 394*DX) && (i%DX >= 422 && i%DX < 502 )) ||
				  	((i >= 422*DX && i < 502*DX) && (i%DX >=  98 && i%DX < 178 )) ||
				  	((i >= 422*DX && i < 502*DX) && (i%DX >= 206 && i%DX < 286 )) ||
				  	((i >= 422*DX && i < 502*DX) && (i%DX >= 314 && i%DX < 394 )) ||
				  	((i >= 422*DX && i < 502*DX) && (i%DX >= 422 && i%DX < 502 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 28079: // 16 cluster (28path) --> 79x79x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 179*DX) && (i%DX >= 100 && i%DX < 179 )) || 
				  	((i >= 100*DX && i < 179*DX) && (i%DX >= 207 && i%DX < 286 )) ||
				  	((i >= 100*DX && i < 179*DX) && (i%DX >= 314 && i%DX < 393 )) ||
				  	((i >= 100*DX && i < 179*DX) && (i%DX >= 421 && i%DX < 500 )) ||
				  	((i >= 207*DX && i < 286*DX) && (i%DX >= 100 && i%DX < 179 )) ||
				  	((i >= 207*DX && i < 286*DX) && (i%DX >= 207 && i%DX < 286 )) ||
				  	((i >= 207*DX && i < 286*DX) && (i%DX >= 314 && i%DX < 393 )) ||
				  	((i >= 207*DX && i < 286*DX) && (i%DX >= 421 && i%DX < 500 )) ||
				  	((i >= 314*DX && i < 393*DX) && (i%DX >= 100 && i%DX < 179 )) ||
				  	((i >= 314*DX && i < 393*DX) && (i%DX >= 207 && i%DX < 286 )) ||
				  	((i >= 314*DX && i < 393*DX) && (i%DX >= 314 && i%DX < 393 )) ||
				  	((i >= 314*DX && i < 393*DX) && (i%DX >= 421 && i%DX < 500 )) ||
				  	((i >= 421*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 179 )) ||
				  	((i >= 421*DX && i < 500*DX) && (i%DX >= 207 && i%DX < 286 )) ||
				  	((i >= 421*DX && i < 500*DX) && (i%DX >= 314 && i%DX < 393 )) ||
				  	((i >= 421*DX && i < 500*DX) && (i%DX >= 421 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 32100: // 16 cluster (32path) --> 100x100x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  52*DX && i < 152*DX) && (i%DX >=  52 && i%DX < 152 )) || 
				  	((i >=  52*DX && i < 152*DX) && (i%DX >= 184 && i%DX < 284 )) ||
				  	((i >=  52*DX && i < 152*DX) && (i%DX >= 316 && i%DX < 416 )) ||
				  	((i >=  52*DX && i < 152*DX) && (i%DX >= 448 && i%DX < 548 )) ||
				  	((i >= 184*DX && i < 284*DX) && (i%DX >=  52 && i%DX < 152 )) ||
				  	((i >= 184*DX && i < 284*DX) && (i%DX >= 184 && i%DX < 284 )) ||
				  	((i >= 184*DX && i < 284*DX) && (i%DX >= 316 && i%DX < 416 )) ||
				  	((i >= 184*DX && i < 284*DX) && (i%DX >= 448 && i%DX < 548 )) ||
				  	((i >= 316*DX && i < 416*DX) && (i%DX >=  52 && i%DX < 152 )) ||
				  	((i >= 316*DX && i < 416*DX) && (i%DX >= 184 && i%DX < 284 )) ||
				  	((i >= 316*DX && i < 416*DX) && (i%DX >= 316 && i%DX < 416 )) ||
				  	((i >= 316*DX && i < 416*DX) && (i%DX >= 448 && i%DX < 548 )) ||
				  	((i >= 448*DX && i < 548*DX) && (i%DX >=  52 && i%DX < 152 )) ||
				  	((i >= 448*DX && i < 548*DX) && (i%DX >= 184 && i%DX < 284 )) ||
				  	((i >= 448*DX && i < 548*DX) && (i%DX >= 316 && i%DX < 416 )) ||
				  	((i >= 448*DX && i < 548*DX) && (i%DX >= 448 && i%DX < 548 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 32090: // 16 cluster (32path) --> 90x90x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  72*DX && i < 162*DX) && (i%DX >=  72 && i%DX < 162 )) || 
				  	((i >=  72*DX && i < 162*DX) && (i%DX >= 194 && i%DX < 284 )) ||
				  	((i >=  72*DX && i < 162*DX) && (i%DX >= 316 && i%DX < 406 )) ||
				  	((i >=  72*DX && i < 162*DX) && (i%DX >= 438 && i%DX < 528 )) ||
				  	((i >= 194*DX && i < 284*DX) && (i%DX >=  72 && i%DX < 162 )) ||
				  	((i >= 194*DX && i < 284*DX) && (i%DX >= 194 && i%DX < 284 )) ||
				  	((i >= 194*DX && i < 284*DX) && (i%DX >= 316 && i%DX < 406 )) ||
				  	((i >= 194*DX && i < 284*DX) && (i%DX >= 438 && i%DX < 528 )) ||
				  	((i >= 316*DX && i < 406*DX) && (i%DX >=  72 && i%DX < 162 )) ||
				  	((i >= 316*DX && i < 406*DX) && (i%DX >= 194 && i%DX < 284 )) ||
				  	((i >= 316*DX && i < 406*DX) && (i%DX >= 316 && i%DX < 406 )) ||
				  	((i >= 316*DX && i < 406*DX) && (i%DX >= 438 && i%DX < 528 )) ||
				  	((i >= 438*DX && i < 528*DX) && (i%DX >=  72 && i%DX < 162 )) ||
				  	((i >= 438*DX && i < 528*DX) && (i%DX >= 194 && i%DX < 284 )) ||
				  	((i >= 438*DX && i < 528*DX) && (i%DX >= 316 && i%DX < 406 )) ||
				  	((i >= 438*DX && i < 528*DX) && (i%DX >= 438 && i%DX < 528 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 32080: // 16 cluster (32path) --> 80x80x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  92*DX && i < 172*DX) && (i%DX >=  92 && i%DX < 172 )) || 
				  	((i >=  92*DX && i < 172*DX) && (i%DX >= 204 && i%DX < 284 )) ||
				  	((i >=  92*DX && i < 172*DX) && (i%DX >= 316 && i%DX < 396 )) ||
				  	((i >=  92*DX && i < 172*DX) && (i%DX >= 428 && i%DX < 508 )) ||
				  	((i >= 204*DX && i < 284*DX) && (i%DX >=  92 && i%DX < 172 )) ||
				  	((i >= 204*DX && i < 284*DX) && (i%DX >= 204 && i%DX < 284 )) ||
				  	((i >= 204*DX && i < 284*DX) && (i%DX >= 316 && i%DX < 396 )) ||
				  	((i >= 204*DX && i < 284*DX) && (i%DX >= 428 && i%DX < 508 )) ||
				  	((i >= 316*DX && i < 396*DX) && (i%DX >=  92 && i%DX < 172 )) ||
				  	((i >= 316*DX && i < 396*DX) && (i%DX >= 204 && i%DX < 284 )) ||
				  	((i >= 316*DX && i < 396*DX) && (i%DX >= 316 && i%DX < 396 )) ||
				  	((i >= 316*DX && i < 396*DX) && (i%DX >= 428 && i%DX < 508 )) ||
				  	((i >= 428*DX && i < 508*DX) && (i%DX >=  92 && i%DX < 172 )) ||
				  	((i >= 428*DX && i < 508*DX) && (i%DX >= 204 && i%DX < 284 )) ||
				  	((i >= 428*DX && i < 508*DX) && (i%DX >= 316 && i%DX < 396 )) ||
				  	((i >= 428*DX && i < 508*DX) && (i%DX >= 428 && i%DX < 508 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 32076: // 16 cluster (32path) --> 76x76x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 176*DX) && (i%DX >= 100 && i%DX < 176 )) || 
				  	((i >= 100*DX && i < 176*DX) && (i%DX >= 208 && i%DX < 284 )) ||
				  	((i >= 100*DX && i < 176*DX) && (i%DX >= 316 && i%DX < 392 )) ||
				  	((i >= 100*DX && i < 176*DX) && (i%DX >= 424 && i%DX < 500 )) ||
				  	((i >= 208*DX && i < 284*DX) && (i%DX >= 100 && i%DX < 176 )) ||
				  	((i >= 208*DX && i < 284*DX) && (i%DX >= 208 && i%DX < 284 )) ||
				  	((i >= 208*DX && i < 284*DX) && (i%DX >= 316 && i%DX < 392 )) ||
				  	((i >= 208*DX && i < 284*DX) && (i%DX >= 424 && i%DX < 500 )) ||
				  	((i >= 316*DX && i < 392*DX) && (i%DX >= 100 && i%DX < 176 )) ||
				  	((i >= 316*DX && i < 392*DX) && (i%DX >= 208 && i%DX < 284 )) ||
				  	((i >= 316*DX && i < 392*DX) && (i%DX >= 316 && i%DX < 392 )) ||
				  	((i >= 316*DX && i < 392*DX) && (i%DX >= 424 && i%DX < 500 )) ||
				  	((i >= 424*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 176 )) ||
				  	((i >= 424*DX && i < 500*DX) && (i%DX >= 208 && i%DX < 284 )) ||
				  	((i >= 424*DX && i < 500*DX) && (i%DX >= 316 && i%DX < 392 )) ||
				  	((i >= 424*DX && i < 500*DX) && (i%DX >= 424 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 36110: // 16 cluster (36path) --> 110x110x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  26*DX && i < 136*DX) && (i%DX >=  26 && i%DX < 136 )) || 
				  	((i >=  26*DX && i < 136*DX) && (i%DX >= 172 && i%DX < 282 )) ||
				  	((i >=  26*DX && i < 136*DX) && (i%DX >= 318 && i%DX < 428 )) ||
				  	((i >=  26*DX && i < 136*DX) && (i%DX >= 464 && i%DX < 574 )) ||
				  	((i >= 172*DX && i < 282*DX) && (i%DX >=  26 && i%DX < 136 )) ||
				  	((i >= 172*DX && i < 282*DX) && (i%DX >= 172 && i%DX < 282 )) ||
				  	((i >= 172*DX && i < 282*DX) && (i%DX >= 318 && i%DX < 428 )) ||
				  	((i >= 172*DX && i < 282*DX) && (i%DX >= 464 && i%DX < 574 )) ||
				  	((i >= 318*DX && i < 428*DX) && (i%DX >=  26 && i%DX < 136 )) ||
				  	((i >= 318*DX && i < 428*DX) && (i%DX >= 172 && i%DX < 282 )) ||
				  	((i >= 318*DX && i < 428*DX) && (i%DX >= 318 && i%DX < 428 )) ||
				  	((i >= 318*DX && i < 428*DX) && (i%DX >= 464 && i%DX < 574 )) ||
				  	((i >= 464*DX && i < 574*DX) && (i%DX >=  26 && i%DX < 136 )) ||
				  	((i >= 464*DX && i < 574*DX) && (i%DX >= 172 && i%DX < 282 )) ||
				  	((i >= 464*DX && i < 574*DX) && (i%DX >= 318 && i%DX < 428 )) ||
				  	((i >= 464*DX && i < 574*DX) && (i%DX >= 464 && i%DX < 574 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 36100: // 16 cluster (36path) --> 100x100x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  46*DX && i < 146*DX) && (i%DX >=  46 && i%DX < 146 )) || 
				  	((i >=  46*DX && i < 146*DX) && (i%DX >= 182 && i%DX < 282 )) ||
				  	((i >=  46*DX && i < 146*DX) && (i%DX >= 318 && i%DX < 418 )) ||
				  	((i >=  46*DX && i < 146*DX) && (i%DX >= 454 && i%DX < 554 )) ||
				  	((i >= 182*DX && i < 282*DX) && (i%DX >=  46 && i%DX < 146 )) ||
				  	((i >= 182*DX && i < 282*DX) && (i%DX >= 182 && i%DX < 282 )) ||
				  	((i >= 182*DX && i < 282*DX) && (i%DX >= 318 && i%DX < 418 )) ||
				  	((i >= 182*DX && i < 282*DX) && (i%DX >= 454 && i%DX < 554 )) ||
				  	((i >= 318*DX && i < 418*DX) && (i%DX >=  46 && i%DX < 146 )) ||
				  	((i >= 318*DX && i < 418*DX) && (i%DX >= 182 && i%DX < 282 )) ||
				  	((i >= 318*DX && i < 418*DX) && (i%DX >= 318 && i%DX < 418 )) ||
				  	((i >= 318*DX && i < 418*DX) && (i%DX >= 454 && i%DX < 554 )) ||
				  	((i >= 454*DX && i < 554*DX) && (i%DX >=  46 && i%DX < 146 )) ||
				  	((i >= 454*DX && i < 554*DX) && (i%DX >= 182 && i%DX < 282 )) ||
				  	((i >= 454*DX && i < 554*DX) && (i%DX >= 318 && i%DX < 418 )) ||
				  	((i >= 454*DX && i < 554*DX) && (i%DX >= 454 && i%DX < 554 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 36090: // 16 cluster (36path) --> 90x90x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  66*DX && i < 156*DX) && (i%DX >=  66 && i%DX < 156 )) || 
				  	((i >=  66*DX && i < 156*DX) && (i%DX >= 192 && i%DX < 282 )) ||
				  	((i >=  66*DX && i < 156*DX) && (i%DX >= 318 && i%DX < 408 )) ||
				  	((i >=  66*DX && i < 156*DX) && (i%DX >= 444 && i%DX < 534 )) ||
				  	((i >= 192*DX && i < 282*DX) && (i%DX >=  66 && i%DX < 156 )) ||
				  	((i >= 192*DX && i < 282*DX) && (i%DX >= 192 && i%DX < 282 )) ||
				  	((i >= 192*DX && i < 282*DX) && (i%DX >= 318 && i%DX < 408 )) ||
				  	((i >= 192*DX && i < 282*DX) && (i%DX >= 444 && i%DX < 534 )) ||
				  	((i >= 318*DX && i < 408*DX) && (i%DX >=  66 && i%DX < 156 )) ||
				  	((i >= 318*DX && i < 408*DX) && (i%DX >= 192 && i%DX < 282 )) ||
				  	((i >= 318*DX && i < 408*DX) && (i%DX >= 318 && i%DX < 408 )) ||
				  	((i >= 318*DX && i < 408*DX) && (i%DX >= 444 && i%DX < 534 )) ||
				  	((i >= 444*DX && i < 534*DX) && (i%DX >=  66 && i%DX < 156 )) ||
				  	((i >= 444*DX && i < 534*DX) && (i%DX >= 192 && i%DX < 282 )) ||
				  	((i >= 444*DX && i < 534*DX) && (i%DX >= 318 && i%DX < 408 )) ||
				  	((i >= 444*DX && i < 534*DX) && (i%DX >= 444 && i%DX < 534 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 36080: // 16 cluster (36path) --> 80x80x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  86*DX && i < 166*DX) && (i%DX >=  86 && i%DX < 166 )) || 
				  	((i >=  86*DX && i < 166*DX) && (i%DX >= 202 && i%DX < 282 )) ||
				  	((i >=  86*DX && i < 166*DX) && (i%DX >= 318 && i%DX < 398 )) ||
				  	((i >=  86*DX && i < 166*DX) && (i%DX >= 434 && i%DX < 514 )) ||
				  	((i >= 202*DX && i < 282*DX) && (i%DX >=  86 && i%DX < 166 )) ||
				  	((i >= 202*DX && i < 282*DX) && (i%DX >= 202 && i%DX < 282 )) ||
				  	((i >= 202*DX && i < 282*DX) && (i%DX >= 318 && i%DX < 398 )) ||
				  	((i >= 202*DX && i < 282*DX) && (i%DX >= 434 && i%DX < 514 )) ||
				  	((i >= 318*DX && i < 398*DX) && (i%DX >=  86 && i%DX < 166 )) ||
				  	((i >= 318*DX && i < 398*DX) && (i%DX >= 202 && i%DX < 282 )) ||
				  	((i >= 318*DX && i < 398*DX) && (i%DX >= 318 && i%DX < 398 )) ||
				  	((i >= 318*DX && i < 398*DX) && (i%DX >= 434 && i%DX < 514 )) ||
				  	((i >= 434*DX && i < 514*DX) && (i%DX >=  86 && i%DX < 166 )) ||
				  	((i >= 434*DX && i < 514*DX) && (i%DX >= 202 && i%DX < 282 )) ||
				  	((i >= 434*DX && i < 514*DX) && (i%DX >= 318 && i%DX < 398 )) ||
				  	((i >= 434*DX && i < 514*DX) && (i%DX >= 434 && i%DX < 514 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 36073: // 16 cluster (36path) --> 73x73x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 173*DX) && (i%DX >= 100 && i%DX < 173 )) || 
				  	((i >= 100*DX && i < 173*DX) && (i%DX >= 209 && i%DX < 282 )) ||
				  	((i >= 100*DX && i < 173*DX) && (i%DX >= 318 && i%DX < 391 )) ||
				  	((i >= 100*DX && i < 173*DX) && (i%DX >= 427 && i%DX < 500 )) ||
				  	((i >= 209*DX && i < 282*DX) && (i%DX >= 100 && i%DX < 173 )) ||
				  	((i >= 209*DX && i < 282*DX) && (i%DX >= 209 && i%DX < 282 )) ||
				  	((i >= 209*DX && i < 282*DX) && (i%DX >= 318 && i%DX < 391 )) ||
				  	((i >= 209*DX && i < 282*DX) && (i%DX >= 427 && i%DX < 500 )) ||
				  	((i >= 318*DX && i < 391*DX) && (i%DX >= 100 && i%DX < 173 )) ||
				  	((i >= 318*DX && i < 391*DX) && (i%DX >= 209 && i%DX < 282 )) ||
				  	((i >= 318*DX && i < 391*DX) && (i%DX >= 318 && i%DX < 391 )) ||
				  	((i >= 318*DX && i < 391*DX) && (i%DX >= 427 && i%DX < 500 )) ||
				  	((i >= 427*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 173 )) ||
				  	((i >= 427*DX && i < 500*DX) && (i%DX >= 209 && i%DX < 282 )) ||
				  	((i >= 427*DX && i < 500*DX) && (i%DX >= 318 && i%DX < 391 )) ||
				  	((i >= 427*DX && i < 500*DX) && (i%DX >= 427 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 40110: // 16 cluster (40path) --> 110x110x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  20*DX && i < 130*DX) && (i%DX >=  20 && i%DX < 130 )) || 
				  	((i >=  20*DX && i < 130*DX) && (i%DX >= 170 && i%DX < 280 )) ||
				  	((i >=  20*DX && i < 130*DX) && (i%DX >= 320 && i%DX < 430 )) ||
				  	((i >=  20*DX && i < 130*DX) && (i%DX >= 470 && i%DX < 580 )) ||
				  	((i >= 170*DX && i < 280*DX) && (i%DX >=  20 && i%DX < 130 )) ||
				  	((i >= 170*DX && i < 280*DX) && (i%DX >= 170 && i%DX < 280 )) ||
				  	((i >= 170*DX && i < 280*DX) && (i%DX >= 320 && i%DX < 430 )) ||
				  	((i >= 170*DX && i < 280*DX) && (i%DX >= 470 && i%DX < 580 )) ||
				  	((i >= 320*DX && i < 430*DX) && (i%DX >=  20 && i%DX < 130 )) ||
				  	((i >= 320*DX && i < 430*DX) && (i%DX >= 170 && i%DX < 280 )) ||
				  	((i >= 320*DX && i < 430*DX) && (i%DX >= 320 && i%DX < 430 )) ||
				  	((i >= 320*DX && i < 430*DX) && (i%DX >= 470 && i%DX < 580 )) ||
				  	((i >= 470*DX && i < 580*DX) && (i%DX >=  20 && i%DX < 130 )) ||
				  	((i >= 470*DX && i < 580*DX) && (i%DX >= 170 && i%DX < 280 )) ||
				  	((i >= 470*DX && i < 580*DX) && (i%DX >= 320 && i%DX < 430 )) ||
				  	((i >= 470*DX && i < 580*DX) && (i%DX >= 470 && i%DX < 580 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 40100: // 16 cluster (40path) --> 100x100x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  40*DX && i < 140*DX) && (i%DX >=  40 && i%DX < 140 )) || 
				  	((i >=  40*DX && i < 140*DX) && (i%DX >= 180 && i%DX < 280 )) ||
				  	((i >=  40*DX && i < 140*DX) && (i%DX >= 320 && i%DX < 420 )) ||
				  	((i >=  40*DX && i < 140*DX) && (i%DX >= 460 && i%DX < 560 )) ||
				  	((i >= 180*DX && i < 280*DX) && (i%DX >=  40 && i%DX < 140 )) ||
				  	((i >= 180*DX && i < 280*DX) && (i%DX >= 180 && i%DX < 280 )) ||
				  	((i >= 180*DX && i < 280*DX) && (i%DX >= 320 && i%DX < 420 )) ||
				  	((i >= 180*DX && i < 280*DX) && (i%DX >= 460 && i%DX < 560 )) ||
				  	((i >= 320*DX && i < 420*DX) && (i%DX >=  40 && i%DX < 140 )) ||
				  	((i >= 320*DX && i < 420*DX) && (i%DX >= 180 && i%DX < 280 )) ||
				  	((i >= 320*DX && i < 420*DX) && (i%DX >= 320 && i%DX < 420 )) ||
				  	((i >= 320*DX && i < 420*DX) && (i%DX >= 460 && i%DX < 560 )) ||
				  	((i >= 460*DX && i < 560*DX) && (i%DX >=  40 && i%DX < 140 )) ||
				  	((i >= 460*DX && i < 560*DX) && (i%DX >= 180 && i%DX < 280 )) ||
				  	((i >= 460*DX && i < 560*DX) && (i%DX >= 320 && i%DX < 420 )) ||
				  	((i >= 460*DX && i < 560*DX) && (i%DX >= 460 && i%DX < 560 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 40090: // 16 cluster (40path) --> 90x90x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  60*DX && i < 150*DX) && (i%DX >=  60 && i%DX < 150 )) || 
				  	((i >=  60*DX && i < 150*DX) && (i%DX >= 190 && i%DX < 280 )) ||
				  	((i >=  60*DX && i < 150*DX) && (i%DX >= 320 && i%DX < 410 )) ||
				  	((i >=  60*DX && i < 150*DX) && (i%DX >= 450 && i%DX < 540 )) ||
				  	((i >= 190*DX && i < 280*DX) && (i%DX >=  60 && i%DX < 150 )) ||
				  	((i >= 190*DX && i < 280*DX) && (i%DX >= 190 && i%DX < 280 )) ||
				  	((i >= 190*DX && i < 280*DX) && (i%DX >= 320 && i%DX < 410 )) ||
				  	((i >= 190*DX && i < 280*DX) && (i%DX >= 450 && i%DX < 540 )) ||
				  	((i >= 320*DX && i < 410*DX) && (i%DX >=  60 && i%DX < 150 )) ||
				  	((i >= 320*DX && i < 410*DX) && (i%DX >= 190 && i%DX < 280 )) ||
				  	((i >= 320*DX && i < 410*DX) && (i%DX >= 320 && i%DX < 410 )) ||
				  	((i >= 320*DX && i < 410*DX) && (i%DX >= 450 && i%DX < 540 )) ||
				  	((i >= 450*DX && i < 540*DX) && (i%DX >=  60 && i%DX < 150 )) ||
				  	((i >= 450*DX && i < 540*DX) && (i%DX >= 190 && i%DX < 280 )) ||
				  	((i >= 450*DX && i < 540*DX) && (i%DX >= 320 && i%DX < 410 )) ||
				  	((i >= 450*DX && i < 540*DX) && (i%DX >= 450 && i%DX < 540 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 40080: // 16 cluster (40path) --> 80x80x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >=  80*DX && i < 160*DX) && (i%DX >=  80 && i%DX < 160 )) || 
				  	((i >=  80*DX && i < 160*DX) && (i%DX >= 200 && i%DX < 280 )) ||
				  	((i >=  80*DX && i < 160*DX) && (i%DX >= 320 && i%DX < 400 )) ||
				  	((i >=  80*DX && i < 160*DX) && (i%DX >= 440 && i%DX < 520 )) ||
				  	((i >= 200*DX && i < 280*DX) && (i%DX >=  80 && i%DX < 160 )) ||
				  	((i >= 200*DX && i < 280*DX) && (i%DX >= 200 && i%DX < 280 )) ||
				  	((i >= 200*DX && i < 280*DX) && (i%DX >= 320 && i%DX < 400 )) ||
				  	((i >= 200*DX && i < 280*DX) && (i%DX >= 440 && i%DX < 520 )) ||
				  	((i >= 320*DX && i < 400*DX) && (i%DX >=  80 && i%DX < 160 )) ||
				  	((i >= 320*DX && i < 400*DX) && (i%DX >= 200 && i%DX < 280 )) ||
				  	((i >= 320*DX && i < 400*DX) && (i%DX >= 320 && i%DX < 400 )) ||
				  	((i >= 320*DX && i < 400*DX) && (i%DX >= 440 && i%DX < 520 )) ||
				  	((i >= 440*DX && i < 520*DX) && (i%DX >=  80 && i%DX < 160 )) ||
				  	((i >= 440*DX && i < 520*DX) && (i%DX >= 200 && i%DX < 280 )) ||
				  	((i >= 440*DX && i < 520*DX) && (i%DX >= 320 && i%DX < 400 )) ||
				  	((i >= 440*DX && i < 520*DX) && (i%DX >= 440 && i%DX < 520 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 40070: // 16 cluster (40path) --> 70x70x16
			for(i=0 ; i < MEDIA_SITE; i++){
				if( ((i >= 100*DX && i < 170*DX) && (i%DX >= 100 && i%DX < 170 )) || 
				  	((i >= 100*DX && i < 170*DX) && (i%DX >= 210 && i%DX < 280 )) ||
				  	((i >= 100*DX && i < 170*DX) && (i%DX >= 320 && i%DX < 390 )) ||
				  	((i >= 100*DX && i < 170*DX) && (i%DX >= 430 && i%DX < 500 )) ||
				  	((i >= 210*DX && i < 280*DX) && (i%DX >= 100 && i%DX < 170 )) ||
				  	((i >= 210*DX && i < 280*DX) && (i%DX >= 210 && i%DX < 280 )) ||
				  	((i >= 210*DX && i < 280*DX) && (i%DX >= 320 && i%DX < 390 )) ||
				  	((i >= 210*DX && i < 280*DX) && (i%DX >= 430 && i%DX < 500 )) ||
				  	((i >= 320*DX && i < 390*DX) && (i%DX >= 100 && i%DX < 170 )) ||
				  	((i >= 320*DX && i < 390*DX) && (i%DX >= 210 && i%DX < 280 )) ||
				  	((i >= 320*DX && i < 390*DX) && (i%DX >= 320 && i%DX < 390 )) ||
				  	((i >= 320*DX && i < 390*DX) && (i%DX >= 430 && i%DX < 500 )) ||
				  	((i >= 430*DX && i < 500*DX) && (i%DX >= 100 && i%DX < 170 )) ||
				  	((i >= 430*DX && i < 500*DX) && (i%DX >= 210 && i%DX < 280 )) ||
				  	((i >= 430*DX && i < 500*DX) && (i%DX >= 320 && i%DX < 390 )) ||
				  	((i >= 430*DX && i < 500*DX) && (i%DX >= 430 && i%DX < 500 ))
				) {utype[i]=1;	c++;}
			}
		break;
		case 44: // 16 cluster (44path)
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
