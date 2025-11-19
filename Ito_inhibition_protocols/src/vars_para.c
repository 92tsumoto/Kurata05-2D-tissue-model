#include <string.h>
#include "syspara.h"

void input_para(FILE *fpin)
{
	int i,ii;

	fscanf(fpin,"%d",&simtype);
	fscanf(fpin,"%d",&cnum);
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
	fscanf(fpin,"%lf",&to_rate);
	fscanf(fpin,"%lf",&to_time);
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
	int i,c=0;

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
	switch(cnum){
		case 1:
			break;
		case 2:
			cluster2_setting();
			break;
		case 4:
			cluster4_setting();
			break;
		case 9:
			cluster9_setting();
			break;
		case 16:
			cluster16_setting();
			break;
		case 25:
			cluster25_setting();
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
		for (i=0;i<MEDIA_SITE;i++){
			gto_rate[i] = to_rate;
		}
		printf("gto_rate[%d]=%lf\n",0,gto_rate[0]);


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

	int i;

	fprintf(fp17,"%lf ",0.0);
	for (i=0;i<MEDIA_SITE;i++){
		fprintf(fp17,"%d ",utype[i]);
	}
	fprintf(fp17,"\n");

} 

void vm_data(FILE *fp5, double time)
{

	int i;

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
