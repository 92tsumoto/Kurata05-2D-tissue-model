#include <string.h>
#include "syspara.h"

int mode = 1;
int P = 8;
FILE *fopen(), *fpin, *fpin1, *fpin2;
FILE *fp0, *fp1, *fp2, *fp3, *fp4, *fp5;
FILE *fp6, *fp7, *fp8, *fp9, *fp10, *fp11, *fp12, *fp13, *fp14, *fp15;
FILE *fp16, *fp17, *fp18, *fp19, *fp20, *fp21, *fp22, *fp23, *fp24, *fp25;

typedef double Number;
typedef long long Lint;

void eular(int n, double h, double t)
{
    int i,j;  
    double dev,diff_c;
    double vm;

	//#pragma vector aligned

	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) comp_Erev(i);
	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) comp_ina(i);
	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) comp_ito(i);
	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) comp_ical(i);
	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) comp_ikr(i);
	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) comp_iks(i);
	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) comp_ik1(i);
	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) comp_incx(i);
	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) comp_inak(i);
	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) comp_ipca(i);
	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) comp_icab(i);
	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) comp_inab(i);
	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) comp_itot(i);
	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) comp_cicr(i);
	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) comp_jup(i);
	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) comp_jleak(i);
	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) comp_jtr(i);
	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) comp_concentration(i);
	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) comp_diff_current(i);
	#pragma ivdep
	for(i=0;i<MEDIA_SITE;i++) function(i,t);
	//for(i=MEDIA_SITE-1;i>=0;i--) function(i,t);

	#pragma ivdep
	for(j=0;j<NN;j++){
		for(i=0;i<MEDIA_SITE;i++) vmf[j][i] += h*dvmf[j][i];
		//for(i=MEDIA_SITE-1;i>=0;i--) vmf[j][i] += h*dvmf[j][i];
	}
}

void function(int s, double t){

	dvmf[0][s] = -itotal[s] + imo[s]; // Vm
	dvmf[1][s] = (minf[s] - vmf[1][s])/taum[s]; // m
	dvmf[2][s] = (hinf[s] - vmf[2][s])/tauh[s]; // h
	dvmf[3][s] = (dinf[s] - vmf[3][s])/taud[s]; // d
	dvmf[4][s] = (finf[s] - vmf[4][s])/tauf[s]; // f 
	dvmf[5][s] = (rinf[s] - vmf[5][s])/taur[s]; // r
	dvmf[6][s] = (qinf[s] - vmf[6][s])/tauq[s]; // q
	dvmf[7][s] = (pinf[s] - vmf[7][s])/taup[s]; // p
	dvmf[8][s] = (ninf[s] - vmf[8][s])/taun[s]; // n 
	dvmf[9][s] = (drss[s] - vmf[9][s])/tau_dr; // dr
	dvmf[10][s] = (dfss[s] - vmf[10][s])/tau_df; // df
	dvmf[11][s] = kftc*vmf[12][s]*(1.0-vmf[11][s])-kbtc*vmf[11][s]; // ftc
	dvmf[12][s] = bcm[s]*((-jcanet[s]+jrel[s]*vrel - jup[s]*vup + jleak[s]*vup)/vi
		-concTc*(kftc*vmf[12][s]*(1.0-vmf[11][s])-kbtc*vmf[11][s]));
	dvmf[13][s] = bcq[s]*(jtr[s] - jrel[s]);
	dvmf[14][s] = jup[s] - jtr[s]*vrel/vup - jleak[s];
	dvmf[15][s] = -jnanet[s]/vi;
	dvmf[16][s] = -jknet[s]/vi;

}

void comp_diff_current(int site)
{
    int i;  
	double temp,dx,rD,lD,tD;

	dx = del_x;
	rD = rateD;
	lD = Diff_l;
	tD = Diff_t;

	if(site==0){ // site=0
		temp = -rD/dx/dx*(tD*(vmf[0][site] - vmf[0][site+1]) + lD*(vmf[0][site] - vmf[0][site+DX]));
	} else if (site==MEDIA_SITE-1){ //site = 8
		temp =  rD/dx/dx*(tD*(vmf[0][site-1] - vmf[0][site]) + lD*(vmf[0][site-DX] - vmf[0][site]));
	} else if (site==DX-1){ // site == 2
		temp =  rD/dx/dx*(tD*(vmf[0][site-1] - vmf[0][site]) - lD*(vmf[0][site] - vmf[0][site+DX]));
	} else if (site==DX*(DY-1)){ // site == 6
		temp = -rD/dx/dx*(tD*(vmf[0][site] - vmf[0][site+1]) - lD*(vmf[0][site-DX] - vmf[0][site]));
	} else if (site>0 && site<DX-1){ // site == 1
		temp =  rD/dx/dx*(tD*(vmf[0][site-1] - 2.0*vmf[0][site] + vmf[0][site+1]) - lD*(vmf[0][site] - vmf[0][site+DX]));
	} else if (site>DX*(DY-1) && site<DX*DY-1){ // site == 7
		temp =  rD/dx/dx*(tD*(vmf[0][site-1] - 2.0*vmf[0][site] + vmf[0][site+1]) + lD*(vmf[0][site-DX] - vmf[0][site]));
	} else if (site>0 && site%DX==0 && site<DX*DY-1){ // site == 3
		temp = -rD/dx/dx*(tD*(vmf[0][site] - vmf[0][site+1]) - lD*(vmf[0][site-DX] - 2.0*vmf[0][site] + vmf[0][site+DX]));
	} else if (site>DX-1 && site%DX==DX-1 && site<DX*DY-1){ // site == 5
		temp =  rD/dx/dx*(tD*(vmf[0][site-1] - vmf[0][site]) + lD*(vmf[0][site-DX] - 2.0*vmf[0][site] + vmf[0][site+DX]));
	} else { // site == 4
		temp =  rD/dx/dx*(tD*(vmf[0][site-1] - 2.0*vmf[0][site] + vmf[0][site+1]) + lD*(vmf[0][site-DX] - 2.0*vmf[0][site] + vmf[0][site+DX]));
	}
	imo[site] = temp;

}

void comp_itot(int s){

	int i;

	// Total Membrane Current (pA/pF)
	if(stim_sw==0){
		if (s >= 0 && s < DX ){ // row stimulation
		//if(s%100==0) 
			itotal[s] = inaf[s] + ical[s] + ito[s] + ikr[s] + iks[s] + ik1[s]
						+ inab[s] + icab[s] + inak[s] + jncx[s] + ipca[s] + Istim;
		} else {
			itotal[s] = inaf[s] + ical[s] + ito[s] + ikr[s] + iks[s] + ik1[s]
						+ inab[s] + icab[s] + inak[s] + jncx[s] + ipca[s];
		}
	} else if(stim_sw==1){ // column stimulation
		if (s%DX==0){
			itotal[s] = inaf[s] + ical[s] + ito[s] + ikr[s] + iks[s] + ik1[s]
						+ inab[s] + icab[s] + inak[s] + jncx[s] + ipca[s] + Istim;
		} else {
			itotal[s] = inaf[s] + ical[s] + ito[s] + ikr[s] + iks[s] + ik1[s]
						+ inab[s] + icab[s] + inak[s] + jncx[s] + ipca[s];
		}
	} else if(stim_sw==2){	// corner stimulation
		if ((s >= 0 && s < (int)(0.05*DX))||(s%DX<(int)(0.05*DX) && s< (int)(0.05*DY*DX)) ){
			itotal[s] = inaf[s] + ical[s] + ito[s] + ikr[s] + iks[s] + ik1[s]
						+ inab[s] + icab[s] + inak[s] + jncx[s] + ipca[s] + Istim;
		} else {
			itotal[s] = inaf[s] + ical[s] + ito[s] + ikr[s] + iks[s] + ik1[s]
						+ inab[s] + icab[s] + inak[s] + jncx[s] + ipca[s];
		}
	} else if(stim_sw > 2){ // i.e., uncoupled system with all units stimulation
		itotal[s] = inaf[s] + ical[s] + ito[s] + ikr[s] + iks[s] + ik1[s]
						+ inab[s] + icab[s] + inak[s] + jncx[s] + ipca[s] + Istim;
		Diff_l = 0.0; Diff_t = 0.0;
	}

	// Net Ion Fluxes (umol/cell)
	jcanet[s] = (ical[s] + icab[s] - 2.0*jncx[s] + ipca[s])*CapHV/(zca*F);
	jnanet[s] = (inaf[s] + inab[s] + 3.0*inak[s] + 3.0*jncx[s])*CapHV/(zna*F);
	jknet[s] = (ito[s] + ikr[s] + iks[s] + ik1[s] - 2.0*inak[s])*CapHV/(zk*F);

}

void comp_ina(int site)
{
	double am,bm,w1,w2,w3,w4;
	double vm,m,h,gna,ena;
	int iV=0;
	double V1,V2,d1,d2;
	vm = vmf[0][site];
	m = vmf[1][site];
	h = vmf[2][site];
	gna = Gnaf[site];
	ena = Enaf[site];

	V1 = ( vm + Emax )*dvm;
	V2 = (int)V1;
	d1 = V1-V2;
	d2 = 1.0-d1;
	iV = (int)V2;
	
	am = Tam[iV]*d2 + Tam[iV+1]*d1;
	bm = Tbm[iV]*d2 + Tbm[iV+1]*d1;
	minf[site] = am/(am+bm);
	taum[site] = 1.0/(am+bm);
	hinf[site] = Thinf[iV]*d2 + Thinf[iV+1]*d1;
	tauh[site] = Ttauh[iV]*d2 + Ttauh[iV+1]*d1;
	
	inaf[site] = gna*(vm - ena)*m*m*m*h*h;

}

// Ito Transient Outward Current
void comp_ito(int site)
{
	double ar,br,aq2,bq2;
	double aq10,bq10,aq11,bq11,aq12,bq12;
	double vm,r,q,Ek,gto;
	vm = vmf[0][site];
	r = vmf[5][site];
	q = vmf[6][site];
	Ek = Eto[site];
	gto = Gto[site];

	int iV=0;
	double V1,V2,d1,d2;
	V1 = (vm + Emax)*dvm;
	V2 = (int)V1;
	d1 = V1-V2;
	d2 = 1.0-d1;
	iV = (int)V2;

	ar = Tar[iV]*d2 + Tar[iV+1]*d1;
	br = Tbr[iV]*d2 + Tbr[iV+1]*d1;

		rinf[site] = ar/(ar + br);
		taur[site] = 1.0/(ar + br);

	aq10 = Taq10[iV]*d2 + Taq10[iV+1]*d1;
	bq10 = Tbq10[iV]*d2 + Tbq10[iV+1]*d1;
	aq11 = Taq11[iV]*d2 + Taq11[iV+1]*d1;
	bq11 = Tbq11[iV]*d2 + Tbq11[iV+1]*d1;
	aq12 = Taq12[iV]*d2 + Taq12[iV+1]*d1;
	bq12 = Tbq12[iV]*d2 + Tbq12[iV+1]*d1;
	aq2 = Taq2[iV]*d2 + Taq2[iV+1]*d1;
	bq2 = Tbq2[iV]*d2 + Tbq2[iV+1]*d1;

	if(celltype[site]==0){
		qinf[site] = aq10/(aq10+bq10);
	} else if(celltype[site]==1){
		qinf[site] = aq11/(aq11+bq11);
	} else if(celltype[site]==2){
		qinf[site] = aq12/(aq12+bq12);
	}
	tauq[site] = 1.0/(aq2+bq2);
	
	ito[site] = gto*(vm - Ek)*r*q;

}


// L-type calcium current
void comp_ical(int site)
{

	double vm,d,f,fca,Eca;
	double gca,Cai,km;
	double tmp1,tmp2;

	int iV=0;
	double V1,V2,d1,d2;
	vm = vmf[0][site];
	d = vmf[3][site];
	f = vmf[4][site];
	Cai = vmf[12][site];
	//fca = gfCa_inf;
	Eca = Ecal;
	gca = Gca[site];
	km = kmfca;
	fca = km/(km + Cai);
	
	V1 = ( vm + Emax )*dvm;
	V2 = (int)V1;
	d1 = V1-V2;
	d2 = 1.0-d1;
	iV = (int)V2;

	// VDA
	tmp1 = Tdinf[iV]*d2 + Tdinf[iV+1]*d1;
	tmp2 = Ttaud[iV]*d2 + Ttaud[iV+1]*d1;
	dinf[site] = tmp1;
	taud[site] = tmp2;
	// VDI 
	tmp1 = Tfinf[iV]*d2 + Tfinf[iV+1]*d1;
	tmp2 = Ttauf[iV]*d2 + Ttauf[iV+1]*d1;
	finf[site] = tmp1;
	tauf[site] = tmp2;
	// CDI 
	//fca = km/(km + Cai);
	//gfCa_inf = fca;

	ical[site] =gca*(vm - Eca)*d*f*fca;

}

// Rapidly Activating Potassium Current 
void comp_ikr(int site)
{
	double ap,bp,piinf;
	double vm,xr,g_kr,Ekr;
	double grate;
	double tmp1,tmp2;

	int iV=0;	
	double V1,V2,d1,d2;
	vm = vmf[0][site];
	xr = vmf[7][site];
	g_kr = Gkr[site];
	Ekr = Ek[site];
	grate = gkr_rate[site];

	V1 = (vm+Emax)*dvm;
	V2 = (int)V1;
	d1 = V1-V2;
	d2 = 1.0-d1;
	iV = (int)V2;

	tmp1 = Tpinf[iV]*d2 + Tpinf[iV+1]*d1;
	pinf[site] = tmp1;

	ap = Tap[iV]*d2 + Tap[iV+1]*d1;
	bp = Tbp[iV]*d2 + Tbp[iV+1]*d1;
	taup[site] = 1.0/(ap + bp);

	piinf = Tpiinf[iV]*d2 + Tpiinf[iV+1]*d1;

	ikr[site] = grate*g_kr*xr*piinf*(vm - Ekr);

}

// Slowly Activating Potassium Current 
void comp_iks(int site)
{
	double vm,n;
	double gks,eks;
	double tmp1,tmp2;

	int iV=0;
	double V1,V2,d1,d2;
	vm = vmf[0][site];
	n = vmf[8][site];
	gks = Gks[site];
	eks = Eks[site];

	V1 = (vm+Emax)*dvm;
	V2 = (int)V1;
	d1 = V1-V2;
	d2 = 1.0-d1;
	iV = (int)V2;

	tmp1 = Tninf[iV]*d2 + Tninf[iV+1]*d1;
	tmp2 = Ttaun[iV]*d2 + Ttaun[iV+1]*d1;
	ninf[site] = tmp1;
	taun[site] = tmp2;
	
	iks[site] = gks_rate[site]*gks*(vm - eks)*n*n;

}

// Inward rectifier potassium current (Ik1)
void comp_ik1(int site)
{
	double vm,gk1,ek;
	double ak1,bk1,k1inf;

	vm = vmf[0][site];
	ek = Ek[site];
	gk1 = Gk1[site];


	ak1 = 0.1/(1.0+exp(0.06*(vm - ek -200.0)));
	bk1 = (3.0*exp(0.0002*(vm - ek + 100.0))+exp(0.1*(vm - ek -10.0)))/(1.0+exp(-0.5*(vm - ek)));
	k1inf = ak1/(ak1+bk1);
	
	ik1[site] = gk1*k1inf*(vm - ek);

}

// Sodium-Calcium Exchanger V-S

void comp_incx(int site)
{
	double c2,c3,exp0,exp1,Gncx;
	//double vm,Nai,Cai,Nao,Cao;
	double vm;
	vm = vmf[0][site];
	double Nai = vmf[15][site];
	double Cai = vmf[12][site];
	//Nao = var.nao;
	//Cao = var.cao;
	Gncx = kncx[site];

	int iV=0;
	double V1,V2,d1,d2;
	V1 = (vm + Emax)*dvm;
	V2 = (int)V1;
	d1 = V1-V2;
	d2 = 1.0-d1;
	iV = (int)V2;

	exp0 = Tncx0[iV]*d2 + Tncx0[iV+1]*d1;
	exp1 = Tncx1[iV]*d2 + Tncx1[iV+1]*d1;
	c2 = Cao*Nai*Nai*Nai;
	c3 = Nao*Nao*Nao*Cai;

	jncx[site] = Gncx*c1*(c2*exp0 - c3*exp1)/(1.0 + ksat*exp1);

}

// Sodium-Potassium Pump

void comp_inak(int site)
{
	double exp0,exp1,tmp1;
	double vm;
	double gnak,Kmkp,Kmnap;
	double k,rho;

	vm = vmf[0][site];
	double Nai = vmf[15][site];
	gnak = Gnak[site];
	Kmkp = kmkp;
	Kmnap = kmnap;
	k = nna;
	rho = rhonak;

	int iV=0;
	double V1,V2,d1,d2;
	V1 = (vm + Emax)*dvm;
	V2 = (int)V1;
	d1 = V1-V2;
	d2 = 1.0-d1;
	iV = (int)V2;

	//exp0 = Tnak0[iV]*d2 + Tnak0[iV+1]*d1;
	//exp1 = Tnak1[iV]*d2 + Tnak1[iV+1]*d1;
	exp0 = exp(-0.1*FRT*vm);
	exp1 = exp(-1.0*FRT*vm);

	tmp1 = gnak*(Ko/(Ko+Kmkp))/(1.0+pow((Kmnap/Nai),nna))/(1.0+0.1245*exp0+0.0365*rho*exp1);
	inak[site] = tmp1;

}

// Sarcolemmal Ca Pump 

void comp_ipca(int site)
{
	double Cai,w1;
	double gpca = Gpca;
	double kmpca = Km_pca;

	Cai = vmf[12][site];
	w1 = gpca*Cai/(Cai + kmpca);
	ipca[site] = w1;

}

// Ca Background Current 

void comp_icab(int site)
{
	double ECa,vm,w1;
	double gcab = Gcab;

	vm = vmf[0][site];
	ECa = Eca[site];
	w1 = gcab*(vm - ECa);
	icab[site] = w1;

}

// Na Background Current 

void comp_inab(int site)
{
	double ENa,vm,w1;
	double gnab = Gnab;
	
	vm = vmf[0][site];
	ENa = Ena[site];
	w1 = gnab*(vm - ENa);
	inab[site] = w1;

}

void comp_cicr(int site)
{
	double vm,grel,dr,df,k;
	double Ica_total,Ical,Icab,Incx,Ipca;
	double Cai,Ca_sr;

	Ical = ical[site];
	Icab = icab[site];
	Incx = jncx[site];
	Ipca = ipca[site];
	Ica_total = Ical + Icab - 2.0*Incx + Ipca;
	vm = vmf[0][site];
	grel = Grel[site];
	dr = vmf[9][site];
	df = vmf[10][site];
	k = nrel;
	Cai = vmf[12][site];
	Ca_sr = vmf[13][site];

	int iV=0;
	double V1,V2,d1,d2;
	V1 = (vm + Emax)*dvm;
	V2 = (int)V1;
	d1 = V1-V2;
	d2 = 1.0-d1;
	iV = (int)V2;

	drss[site] = Tdinf[iV]*d2 + Tdinf[iV+1]*d1;
	dfss[site] = Tfinf[iV]*d2 + Tfinf[iV+1]*d1;

	jrel[site] = grel/(1.0+exp((Ica_total+5.0)/0.9))*pow(dr*df,k)*(Ca_sr - Cai);

}

void comp_jup(int site)
{
	int i;
	double gup,Kup,Cai;
	Cai = vmf[12][site];
	Kup = kup;
	gup = Gup[site];

	//for(i=0;i<MEDIA_SITE;i++){	
		jup[site] = gup*Cai*Cai/(Cai*Cai + Kup*Kup);
	//}
}

void comp_jleak(int site)
{
	int i;
	double Gleak = pleak;
	double Ca_up,Cai;

	//for(i=0;i<MEDIA_SITE;i++){	
		Cai = vmf[12][site];
		Ca_up = vmf[14][site];
		jleak[site] = Gleak*(Ca_up - Cai);
	//}

}

void comp_jtr(int site)
{

	double tau,Ca_sr,Ca_up;
	tau = tau_tr;
	Ca_sr = vmf[13][site];
	Ca_up = vmf[14][site];
	jtr[site] = (Ca_up - Ca_sr)/tau;
}

void comp_concentration(int site)
{
	double Kdcm,Cam;
	double Kdcq,Ccq;
	double Cai,Ca_sr;
	Cai = vmf[12][site];
	Ca_sr = vmf[13][site];
	Kdcm = kdcm;
	Cam = conccm[site];
	Kdcq = kdcq;
	Ccq = conccq;

	bcm[site]=1.0/( 1.0 + Cam * Kdcm/( (Kdcm + Cai)*(Kdcm + Cai) ) );         // Dfcm=kfCM*Cai*(1-fcm)-kbCM*fcm;
	bcq[site] = 1.0/(1.0 + Ccq * Kdcq/( (Kdcq + Ca_sr)*(Kdcq + Ca_sr) ) );	// Dfcq=kfCQ*Carel*(1-fcq)-kbCQ*fcq;

}


// Reversal potentials */

void comp_Erev(int site)
{
	double Nai,Ki,Cai;
	
	Nai=vmf[15][site];
	Ki=vmf[16][site];
	Cai = vmf[12][site];
	
	Ena[site] = RTF*log(Nao/Nai);
	Ek[site]  = RTF*log(Ko/Ki);
	Eca[site] = (RTF/2.0)*log(Cao/Cai);

	double x1 = pkna;
	double x2 = prnak;
	double x3 = pnato;
	double enaf;

	enaf = RTF*log((Nao+x1*Ko)/(Nai+x1*Ki));
	Enaf[site] = enaf;
	
	double eks;
	eks = RTF*log((x2*Nao+Ko)/(x2*Nai+Ki));
	Eks[site] = eks;

	double eto;
	eto= RTF*log((x3*Nao+Ko)/(x3*Nai+Ki));
	Eto[site] = eto;

}

void make_ExpTable()
{

	int vindex;
	double v;
    
	for(vindex=0;vindex<VNMAX;vindex++){

        v = (double)vindex/dvm-(double)Emax;
		
        /** for ina **/
		if(fabs(v+47.13)<1E-3){
			Tam[vindex] = 0.16*v + 10.7408;
		} else {
			Tam[vindex] = 0.32*(v+47.13)/(1.0-exp(-(v+47.13)/10.0));
		}
		Tbm[vindex] = 0.08*exp(-v/11.0);

		Thinf[vindex] = 0.5*(1.0-tanh(7.74+0.12*v));
		if(v<180){
			Ttauh[vindex] = 0.25+2.24*(1.0-tanh(7.74+0.12*v))/(1.0-tanh(0.07*(v+92.4)));
		} else {
			Ttauh[vindex] = 0.25;
		}

		// ito
		Tar[vindex] = 0.5266*exp(-0.0166*(v-42.2912))/(1.0+exp(-0.0943*(v-42.2912)));
		Tbr[vindex] = (0.5149*exp(-0.1344*(v-5.0027))+0.00005186*v)/(1.0+exp(-0.1348*(v-0.00005186)));
		// for Endo case
		Taq10[vindex] = (0.0721*exp(-0.173*(v+34.2531-dVgq0))+0.00005612*(v-dVgq0))/(1.0+exp(-0.1732*(v+34.2531-dVgq0)));
		Tbq10[vindex] = (0.0767*exp(-0.00000000166*(v+34.0235-dVgq0))+0.0001215*(v-dVgq0))/(1.0+exp(-0.1604*(v+34.0235-dVgq0)));
		// for Epi case
		Taq11[vindex] = (0.0721*exp(-0.173*(v+34.2531-dVgq1))+0.00005612*(v-dVgq1))/(1.0+exp(-0.1732*(v+34.2531-dVgq1)));
		Tbq11[vindex] = (0.0767*exp(-0.00000000166*(v+34.0235-dVgq1))+0.0001215*(v-dVgq1))/(1.0+exp(-0.1604*(v+34.0235-dVgq1)));
		// for Mid case
		Taq12[vindex] = (0.0721*exp(-0.173*(v+34.2531-dVgq2))+0.00005612*(v-dVgq2))/(1.0+exp(-0.1732*(v+34.2531-dVgq2)));
		Tbq12[vindex] = (0.0767*exp(-0.00000000166*(v+34.0235-dVgq2))+0.0001215*(v-dVgq2))/(1.0+exp(-0.1604*(v+34.0235-dVgq2)));

		Taq2[vindex] = (0.0721*exp(-0.173*(v+34.2531))+0.00005612*v)/(1.0+exp(-0.1732*(v+34.2531)));
		Tbq2[vindex] = (0.0767*exp(-0.00000000166*(v+34.0235))+0.0001215*v)/(1.0+exp(-0.1604*(v+34.0235)));

		// for ical
		Tdinf[vindex] = 1.0/(1.0+exp(-(v+7.64)/6.32));
		Ttaud[vindex] = (1.4/(1.0+exp(-(v+35.0)/13.0))+0.25)*1.4/(1.0+exp((v+5.0)/5.0))+1.0/(1.0+exp(-(v-50.0)/20.0));

		Tfinf[vindex] = 1.0/(1.0+exp((v+24.6)/6.9));
		Ttauf[vindex] = 23.9*0.75/(0.1389*exp(-(0.0358*(v-10.9))*(0.0358*(v-10.9)))+0.0519);

		// for ikr 
		Tpinf[vindex] = 1.0/(1.0+exp(-(v+14.0)/7.7));
		if(fabs(v+14.0)<1E-3){
			Tap[vindex] = 0.0015;
		} else {
			Tap[vindex] = 0.0003*(v+14.0)/(1.0-exp(-(v+14.0)/5.0));
		}
		if(fabs(v-3.4328)<1E-3){
			Tbp[vindex] = 11.0/29052.0;
		} else {
			Tbp[vindex] = 0.000073898*(v-3.4328)/(exp((v-3.4328)/5.1237)-1.0);
		}
		Tpiinf[vindex] = 1.0/(1.0+exp((v+15.0)/22.4));

		// for iks 
		Tninf[vindex] = 1.0/sqrt(1.0+exp(-(v-9.4)/11.8));
		Ttaun[vindex] = 555.0/(1.0+exp(-(v+22.0)/11.3))+129.0;

		// ik1 
		//ik1.Tak1[vindex] = 0.1/(1.0+exp(0.06*(v-var.Ek-200.0)));
		//ik1.Tbk1[vindex] = (3.0*exp(0.0002*(v-var.Ek+100.0))+exp(0.1*(v-var.Ek-10.0)))/(1.0+exp(-0.5*(v-var.Ek)));

		// inaca
		Tncx0[vindex] = exp(rncx*FRT*v);
		Tncx1[vindex] = exp((rncx-1.0)*FRT*v);

		// inak 
		//Tnak0[vindex] = exp(-0.1*FRT*v);
		//Tnak1[vindex] = exp(-1.0*FRT*v);

	}
//exit(0);
}

main(int argc, char **argv)
{
	int i,k,m,l,z,u,x,y;
	int ii=0;
	unsigned int count=0;
	double t = 0.0;
	double time;
	double h,R_all,V_all;
	//double v_old[MEDIA_SITE][MEDIA_PATCH],v_old2[MEDIA_SITE][MEDIA_PATCH],dvdt_new[MEDIA_SITE][MEDIA_PATCH];
	double *v_old,*v_old2,*dvdt_new;
	double xx,dxx;
	double d1,d2;
	double v_thre,v_thre2;
	double cut,cut2;
	char *tmpname,*init1,*init2;
	char cmd[BUFSIZ];
	double tp1,tp2;

/* Action Potential Duration and Max. Info */
	double **vmax; // Max. Voltage (mV)
	double **dvdtmax; // Max. dv/dt (mV/ms)
	double **apd; // Action Potential Duration
	double **toneapd; // Time of dv/dt Max.
	double **ttwoapd; // Time of 90% Repolarization
	double **rmbp; // Resting Membrane Potential
	double **nair; // Intracellular Na At Rest
	double **cair; // Intracellular Ca At Rest
	double **kir; // Intracellular K At Rest
	double **caimax; // Peak Intracellular Ca
	double **v_thre_time,**v_thre_time2; // time when AP passes throght the threshold value
	int *thre_flag; // time flag when AP passes throght the threshold value
	int *thre_flag2; // time flag when AP passes throght the threshold value

printf("start\n");
	tmpname = "temp";
	sprintf(cmd, "/usr/bin/cpp -P %s > %s", argv[1],tmpname);
	if(system(cmd) == -1){
		fprintf(stderr,"cannot open %s\n",argv[1]);
		exit(1);
	}
	if((fpin=fopen(tmpname,"r"))==NULL){
		fprintf(stderr,"cannot open %s\n",argv[1]);
		exit(1);
	}

	init1 = "initial_values_set1";
	sprintf(cmd, "/usr/bin/cpp -P %s > %s", argv[2],init1);
	if(system(cmd) == -1){
		fprintf(stderr,"cannot open %s\n",argv[2]);
		exit(1);
	}
	if((fpin1=fopen(init1,"r"))==NULL){
		fprintf(stderr,"cannot open %s\n",argv[2]);
		exit(1);
	}

	init2 = "initial_values_set2";
	sprintf(cmd, "/usr/bin/cpp -P %s > %s", argv[3],init2);
	if(system(cmd) == -1){
		fprintf(stderr,"cannot open %s\n",argv[3]);
		exit(1);
	}
	if((fpin2=fopen(init2,"r"))==NULL){
		fprintf(stderr,"cannot open %s\n",argv[3]);
		exit(1);
	}

	if ((fp1 = fopen("status.out","w")) == NULL){
		printf("Can't open File\n");
		exit(1);
	}
	if ((fp2 = fopen("ndata.out","w")) == NULL){
		printf("Can't open File\n");
		exit(1);
	}
	if ((fp3 = fopen("ndata_final.out","w")) == NULL){
		printf("Can't open File\n");
		exit(1);
	}
	if ((fp4 = fopen("act_time.out","w")) == NULL){ // activation time data
		printf("Can't open File\n");
		exit(1);
	}
	if ((fp5 = fopen("vm_data.out","w")) == NULL){ // Vm map data
		printf("Can't open File\n");
		exit(1);
	}
	if ((fp6 = fopen("initdat.out","w")) == NULL){ // initial value data
		printf("Can't open File\n");
		exit(1);
	}
	if ((fp17 = fopen("utype.out","w")) == NULL){ // unit type map data
		printf("Can't open File\n");
		exit(1);
	} 

	// input initial parameters
	printf("start parameter input\n");
	input_para(fpin);
	printf("end parameterinput\n");

	if (write){
		if ((fp0 = fopen(argv[4],"w"))==NULL){
			fprintf(stderr, "%s cannot open.\n",argv[4]);
			exit(-1);
		}
	}

	for (ii = 0; ii < datas; ii++){
		long j;
		time = 0.0;

		// Eular's step size
		h = 1.0 / div_num;
		// AP threshold value
		v_thre = -40.0;
		v_thre2 = 0.0;
		// a variable for data output	
		switch(reduce){
			case 1:
				cut = div_num/1.0;
				break;
			case 2:
				cut = 5*div_num;
				break;
			case 3:
				cut = 10*div_num;
				break;
		}
		cut2 = div_num/10.0;

		//h *= var.tsign[ii];

	// initialized memory
		printf("start memory initialization\n");
		initial_mem();
        v_old = (double*)malloc(sizeof(Number)*MEDIA_SITE);
        v_old2 = (double*)malloc(sizeof(Number)*MEDIA_SITE);
        dvdt_new = (double*)malloc(sizeof(Number)*MEDIA_SITE);
		if(v_old==NULL || v_old2==NULL || dvdt_new==NULL) exit(1);

        vmax = (double**)malloc2d(sizeof(double*),beats,MEDIA_SITE);
        dvdtmax = (double**)malloc2d(sizeof(double*),beats,MEDIA_SITE);
        apd = (double**)malloc2d(sizeof(double*),beats,MEDIA_SITE);
        toneapd = (double**)malloc2d(sizeof(double*),beats,MEDIA_SITE);
        ttwoapd = (double**)malloc2d(sizeof(double*),beats,MEDIA_SITE);
        rmbp = (double**)malloc2d(sizeof(double*),beats,MEDIA_SITE);
        nair = (double**)malloc2d(sizeof(double*),beats,MEDIA_SITE);
        cair = (double**)malloc2d(sizeof(double*),beats,MEDIA_SITE);
        kir = (double**)malloc2d(sizeof(double*),beats,MEDIA_SITE);
        caimax = (double**)malloc2d(sizeof(double*),beats,MEDIA_SITE);
        v_thre_time = (double**)malloc2d(sizeof(double*),beats,MEDIA_SITE);
        v_thre_time2 = (double**)malloc2d(sizeof(double*),beats,MEDIA_SITE);
		thre_flag=(int *)calloc(MEDIA_SITE,sizeof(int));
		thre_flag2=(int *)calloc(MEDIA_SITE,sizeof(int));
		if(thre_flag==NULL || thre_flag2==NULL) exit(1);
		printf("finished memory initialization\n");

		if(outdata){
			if ((fp7 = fopen("ikr_data.out","w")) == NULL){
				printf("Can't open File\n");
				exit(1);
			}
			if ((fp8 = fopen("iks_data.out","w")) == NULL){
				printf("Can't open File\n");
				exit(1);
			}
			if ((fp9 = fopen("ical_data.out","w")) == NULL){
				printf("Can't open File\n");
				exit(1);
			}
			if ((fp10 = fopen("incx_data.out","w")) == NULL){
				printf("Can't open File\n");
				exit(1);
			}
			if ((fp11 = fopen("inak_data.out","w")) == NULL){
				printf("Can't open File\n");
				exit(1);
			}
			if ((fp12 = fopen("cai_data.out","w")) == NULL){
				printf("Can't open File\n");
				exit(1);
			}
		}	
		if(outdata_plus){
			if ((fp13 = fopen("vmd_data.out","w")) == NULL){ //detailed Vm data
				printf("Can't open File\n");
				exit(1);
			} 
			if ((fp14 = fopen("ito_data.out","w")) == NULL){
				printf("Can't open File\n");
				exit(1);
			}
			if ((fp15 = fopen("ik1_data.out","w")) == NULL){
				printf("Can't open File\n");
				exit(1);
			}
			if ((fp16 = fopen("ipca_data.out","w")) == NULL){
				printf("Can't open File\n");
				exit(1);
			} 
		}	

		// parameter values input.
		val_consts(fp1);
		printf("exit consts paramter inputs\n");
		utype_data(fp17);
		fclose(fp17);

		printf("start initial values inputs\n");
		input_init(fpin1,fpin2);
		printf("end initial values inputs\n");

		// Resistance parameters;
		d1 = length;
		//d2 = var.cleft_width;

		// surface area of Junctional membran unit or cross-section area of myocyte	
		s1 = M_PI*radius*radius;

		// surface area of junctional and non-Junctional membran unit	
		s2 = 2.0*M_PI*radius*d1;
		printf("s2=%e\n",s2);
		fprintf(fp1,"s2=%e\n",s2);

		printf("vcell=%e\n",vcell);
		fprintf(fp1,"vcell=%e\n",vcell);

		printf("unit_volume=%e\n",1000*length*length*length);
		fprintf(fp1,"unit_volume=%e\n",1000*length*length*length);
		printf("unit surface=%e\n",6.0*length*length);
		fprintf(fp1,"unit surface=%e\n",6.0*length*length);
	
		printf("unit length = %e\n",length);
		printf("unit surface area 6*(l*l) = %e\n",6.0*length*length);
		printf("Cross section area l*l = %e\n",length*length);
		printf("intracellular resistance = %e\n",150.0*length/(length*length));
		printf("D_l = %e cm2/ms\n",Diff_l);
		printf("D_t = %e cm2/ms\n",Diff_t);
		printf("Ena=%f, Ek=%f\n",log(Nao/vmf[15][0])*RTF,log(Ko/vmf[16][0])*RTF);

		fprintf(fp1,"unit length = %e\n",length);
		fprintf(fp1,"unit surface area 6*(l*l) = %e\n",6.0*length*length);
		fprintf(fp1,"Cross section area l*l = %e\n",length*length);
		fprintf(fp1,"intracellular resistance = %e\n",150.0*length/(length*length));
		fprintf(fp1,"D_l = %e cm2/ms\n",Diff_l);
		fprintf(fp1,"D_t = %e cm2/ms\n",Diff_t);
		fprintf(fp1,"Ena=%f, Ek=%f\n",log(Nao/vmf[15][0])*RTF,log(Ko/vmf[16][0])*RTF);

	// Tablize exp functions.       
		printf("start tablization\n");
		make_ExpTable();
		printf("finished tablization\n");

	// Initialization time
		time -= h;
		//var.dt = h;
		b_num = 0;
	
		for(b_num=0; b_num < beats; b_num++){

			for (j = 0; j< (div_num * BCL ); j++){
				t = h*j;
				time += h;

				for(k=0;k<MEDIA_SITE;k++){
					v_old[k] = vmf[0][k];
					v_old2[k] = vmf[0][k];
				//	printf("vm0=%lf\n",vmf[0][0]);
				}
					
				if(time-(BCL*(double)b_num+10) >= 0.0 && time-(BCL*(double)b_num+10) < h ){
				//if(time-(BCL*(double)b_num+0) >= 0.0 && time-(BCL*(double)b_num+0) < h ){
					for(k=0;k<MEDIA_SITE;k++){
						rmbp[b_num][k] = vmf[0][k];
						nair[b_num][k] = vmf[15][k]; kir[b_num][k]  = vmf[16][k]; cair[b_num][k] = vmf[12][k];
						thre_flag[k] = 0; thre_flag2[k] = 0;
					}
				}

				if(time-(BCL*(double)b_num+10.0) >= 0.0 && time-(BCL*(double)b_num+10.0) < 1.0){
				//if(time-(BCL*(double)b_num+0.0) >= 0.0 && time-(BCL*(double)b_num+0.0) < 1.0){
					Istim = Istim_base;
				} else {
					Istim = 0.0;
				}

	if(debug){
		for(k=0;k<MEDIA_SITE;k++) printf("%lf ",vmf[0][k]);
		printf("\n");
	}

				//for(k=0;k<MEDIA_SITE;k++) function(k,t);
				eular(NN,h,t);

				for (k=0;k<MEDIA_SITE;k++){

					dvdt_new[k] = (vmf[0][k]-v_old[k])/h; // dvdtnew
					//var.dvdt[k] = dvdt_new[k];

					if(b_num>=0){
						if (vmf[0][k] > vmax[b_num][k] ){
							vmax[b_num][k] = vmf[0][k];
						}
						if (vmf[12][k] > caimax[b_num][k] ){
							caimax[b_num][k] = vmf[12][k];
						}
						if (dvdt_new[k] > dvdtmax[b_num][k] ){
							dvdtmax[b_num][k] = dvdt_new[k];
							toneapd[b_num][k] = time;
						}
						if (vmf[0][k] >= (vmax[b_num][k] -0.9*(vmax[b_num][k] -rmbp[b_num][k] ))){
							ttwoapd[b_num][k] = time;
						}
							
						if( (v_old[k] - v_thre)<0 && (v_old[k] - v_thre)*(vmf[0][k] - v_thre)<0){
							if(thre_flag[k] != 1){
								v_thre_time[b_num][k] = time;
								printf("1st pass thre unit[%d] = %lf\n",k,v_thre_time[b_num][k]);
								fprintf(fp4,"%d %d %d %lf\n",b_num,k,m,v_thre_time[b_num][k]);
								thre_flag[k] = 1;
							}
						}
						if( (v_old2[k] - v_thre2)<0 && (v_old2[k] - v_thre2)*(vmf[0][k] - v_thre2)<0){
							if(thre_flag2[k] != 1){
								v_thre_time2[b_num][k] = time;
								printf("2nd pass thre unit[%d] = %lf\n",k,v_thre_time2[b_num][k]);
								thre_flag2[k] = 1;
							}
						}

						// check end for activation time

						}
				}

				if (time>= (beats-5)*BCL){
					if(j%(int)cut == 0){ // 1.0 ms^-1; To reduce the recording data.
						vm_data(fp5,time);
					}
					if(j%(int)cut2 == 0){ // 0.1 ms^-1; To reduce the recording data.
						// option
						if(outdata){out_data(fp7,fp8,fp9,fp10,fp11,fp12,time);}
						//if(outdata_plus){out_data_plus(fp13,fp14,fp15,fp16,time);}
						if(outdata_plus){out_data_plus(fp13,time);}
					}
				}
				

			} // for-loop end; j

			fprintf(fp6,"beats=%d\n",b_num+1);
			for(m=0;m<MEDIA_SITE;m++){
				for(i=0;i<NN;i++){
					fprintf(fp6,"%16.15e\n",vmf[i][m]);
				}
			}
			fprintf(fp6,"\n");

		} // for-loop end; b_nums

		//printf("data out\n");
		
		for(z=0;z<beats;z++){

			for(m=0;m<MEDIA_SITE;m++){
				apd[z][m] = ttwoapd[z][m] - toneapd[z][m];
			}

			for(m=0;m<MEDIA_SITE;m++){
				fprintf(fp2,"%i\t%g\t%g\t%g\t%g\t%g\t%g\t%g\t%g\t%g\t%g\t%g\n",
					z+1,vmax[z][m],dvdtmax[z][m],v_thre_time[z][m],apd[z][m],toneapd[z][m],ttwoapd[z][m],
						nair[z][m],kir[z][m],cair[z][m],caimax[z][m],rmbp[z][m]);
			}

		}
					
		for(m=0;m<MEDIA_SITE;m++){
			fprintf(fp3,"%i\t%g\t%g\t%g\t%g\t%g\t%g\t%g\t%g\t%g\t%g\t%g\n",
				beats,vmax[beats-1][m],dvdtmax[beats-1][m],v_thre_time[beats-1][m],apd[beats-1][m],
					toneapd[beats-1][m],ttwoapd[beats-1][m],nair[beats-1][m],kir[beats-1][m],cair[beats-1][m],
						caimax[beats-1][m],rmbp[beats-1][m]);
		}


/* -------------------------------------------------------------------- */
/* .. Termination and release of memory. */
/* -------------------------------------------------------------------- */
		//release_of_memory();

		fclose(fp1); fclose(fp2); fclose(fp3);
		fclose(fp4); fclose(fp5);
		fclose(fp6);
		
		if(outdata){
			fclose(fp7); fclose(fp8); fclose(fp9); fclose(fp10); fclose(fp11); fclose(fp12);
		}
		if(outdata_plus){
			fclose(fp13); fclose(fp14); fclose(fp15); fclose(fp16);
		}

		free(v_old); free(v_old2);
		free(vmax); free(dvdtmax); free(apd); free(toneapd); free(ttwoapd);
		free(rmbp); free(nair); free(cair); free(kir); free(caimax);
		free(thre_flag); free(thre_flag2); free(v_thre_time); free(v_thre_time2);

		close_mem();

	}
}

void initial_mem()
{
	int i,k,m,l,z;
	int site;
// initialized memory for state variables and arguments for Eular method 
	vmf=(double**)malloc2d(sizeof(double*),NN,MEDIA_SITE);
	dvmf=(double**)malloc2d(sizeof(double*),NN,MEDIA_SITE);

	//var.u=(double**)malloc2d(sizeof(double*),NN,MEDIA_SITE);
	//var.f=(double**)malloc2d(sizeof(double*),NN,MEDIA_SITE);
	
	imo=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	if(imo==NULL) exit(1);
	itotal=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	if(itotal==NULL) exit(1);
	celltype=(int *)calloc(MEDIA_SITE,sizeof(int));
	if(celltype==NULL) exit(1);
	utype=(int *)calloc(MEDIA_SITE,sizeof(int));
	if(utype==NULL) exit(1);

	Enaf=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	Ena=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	Ek=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	Eto=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	Eks=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	Eca=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	if( Enaf==NULL || Ena== NULL || Ek==NULL || Eto ==NULL || Eks==NULL || Eca==NULL) exit(1);

	jnanet=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	jknet=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	jcanet=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	if(jnanet==NULL || jknet==NULL || jcanet==NULL) exit(1);

// initialized tablization memorys for Exp functions
	// ina_fast
	Tam=(Number *)calloc(VNMAX,sizeof(Number));
	Tbm=(Number *)calloc(VNMAX,sizeof(Number));
	Thinf=(Number *)calloc(VNMAX,sizeof(Number));
	Ttauh=(Number *)calloc(VNMAX,sizeof(Number));
	Gnaf=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	inaf=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	minf=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	hinf=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	taum=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	tauh=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	if( Tam==NULL || Tbm==NULL || Thinf==NULL || Ttauh==NULL || Gnaf==NULL || inaf==NULL || minf==NULL || hinf==NULL || taum ==NULL || tauh == NULL) exit(1);
	// ito
	Tar=(Number *)calloc(VNMAX,sizeof(Number));
	Tbr=(Number *)calloc(VNMAX,sizeof(Number));
	Taq10=(Number *)calloc(VNMAX,sizeof(Number));
	Tbq10=(Number *)calloc(VNMAX,sizeof(Number));
	Taq11=(Number *)calloc(VNMAX,sizeof(Number));
	Tbq11=(Number *)calloc(VNMAX,sizeof(Number));
	Taq12=(Number *)calloc(VNMAX,sizeof(Number));
	Tbq12=(Number *)calloc(VNMAX,sizeof(Number));
	Taq2=(Number *)calloc(VNMAX,sizeof(Number));
	Tbq2=(Number *)calloc(VNMAX,sizeof(Number));
	ito=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	Gto=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	rinf=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	qinf=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	taur=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	tauq=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	if( Tar==NULL || Tbr==NULL || Taq10==NULL || Tbq10==NULL || 
		Taq11==NULL || Tbq11==NULL || Taq12==NULL || Tbq12==NULL || 
		Taq2==NULL || Tbq2==NULL || ito==NULL || Gto==NULL || rinf==NULL || qinf==NULL || taur==NULL || tauq==NULL) exit(1);
	// ical
	Tdinf=(Number *)calloc(VNMAX,sizeof(Number));
	Ttaud=(Number *)calloc(VNMAX,sizeof(Number));
	Tfinf=(Number *)calloc(VNMAX,sizeof(Number));
	Ttauf=(Number *)calloc(VNMAX,sizeof(Number));
	ical=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	Gca=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	dinf=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	finf=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	taud=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	tauf=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	if( Tdinf==NULL || Ttaud==NULL || Tfinf==NULL || Ttauf==NULL || ical==NULL || Gca==NULL || dinf==NULL || finf==NULL || taud==NULL || tauf==NULL) exit(1);
	// ikr
	Tpinf=(Number *)calloc(VNMAX,sizeof(Number));
	Tap=(Number *)calloc(VNMAX,sizeof(Number));
	Tbp=(Number *)calloc(VNMAX,sizeof(Number));
	Tpiinf=(Number *)calloc(VNMAX,sizeof(Number));
	ikr=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	Gkr=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	pinf=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	taup=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	gkr_rate=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	if( Tpinf==NULL || Tap==NULL || Tbp==NULL || Tpiinf==NULL || ikr==NULL || Gkr==NULL || pinf==NULL || taup==NULL || gkr_rate==NULL) exit(1);
	// iks
	Tninf=(Number *)calloc(VNMAX,sizeof(Number));
	Ttaun=(Number *)calloc(VNMAX,sizeof(Number));
	iks=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	Gks=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	ninf=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	taun=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	gks_rate=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	if( Tninf==NULL || Ttaun==NULL || iks==NULL || Gks==NULL || ninf==NULL || taun==NULL || gks_rate==NULL) exit(1);
	// ik1
	ik1=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	Gk1=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	if( ik1 == NULL || Gk1==NULL ) exit(1);
	// NCX
	Tncx0=(Number *)calloc(VNMAX,sizeof(Number));
	Tncx1=(Number *)calloc(VNMAX,sizeof(Number));
	kncx=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	jncx=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	if( Tncx0==NULL || Tncx1==NULL || kncx==NULL || jncx==NULL ) exit(1);
	// NaK 
	Tnak0=(Number *)calloc(VNMAX,sizeof(Number));
	Tnak1=(Number *)calloc(VNMAX,sizeof(Number));
	Gnak=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	inak=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	if( Tnak0==NULL || Tnak1==NULL || Gnak==NULL || inak==NULL ) exit(1);
	// IpCa
	ipca=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	// INaB
	inab=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	// ICaB
	icab=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	if( ipca==NULL || inab==NULL || icab==NULL ) exit(1);
	// Jrel
	drss=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	dfss=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	Grel=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	jrel=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	// Jup
	Gup=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	jup=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	// Jleak
	jleak=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	// Jtr
	jtr=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	if( drss==NULL || dfss==NULL || jrel==NULL || Grel==NULL || jup==NULL || Gup==NULL || jleak==NULL || jtr==NULL) exit(1);
	// Ca Buffer, Calmodulin
	conccm=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	bcm=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	bcq=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	if( conccm==NULL || bcm==NULL || bcq==NULL ) exit(1);

}
		
/* -------------------------------------------------------------------- */
/* .. Termination and release of memory. */
/* -------------------------------------------------------------------- */
void close_mem()
{

	int i,j;

		free(vmf);free(dvmf);
		//free(var.u);//free(var.f);
		free(celltype);free(utype);
		
		free(Ena);free(Ek);free(Eca);
		free(Enaf); free(Eto); free(Eks);
		free(jnanet);free(jknet);free(jcanet);
		free(imo);free(itotal);

		// INa
		free(Tam);free(Tbm);free(Thinf);free(Ttauh);free(Gnaf);free(inaf);free(minf);free(hinf);free(taum);free(tauh);
		// Ito
		free(Tar);free(Tbr);free(Taq10);free(Tbq10);free(Taq11);free(Tbq11);free(Taq12);free(Tbq12);
		free(Taq2);free(Tbq2);free(ito);free(Gto);free(rinf);free(qinf);free(taur);free(tauq);
		// ICaL
		free(Tdinf);free(Ttaud);free(Tfinf);free(Ttauf);free(ical);free(Gca);free(dinf);free(finf);free(taud);free(tauf);
		// IKr
		free(Tpinf);free(Tap);free(Tbp);free(Tpiinf);free(ikr);free(Gkr);free(pinf);free(taup);free(gkr_rate);
		// IKs
		free(Tninf);free(Ttaun);free(iks);free(Gks);free(ninf);free(taun);free(gks_rate);
		// IK1
		free(ik1); free(Gk1);
		// Incx
		free(Tncx0); free(Tncx1);free(kncx);free(jncx);
		// INaK
		free(Tnak0);free(Tnak1);free(Gnak);free(inak);
		free(ipca);free(inab);free(icab);
		// Ca handling
		free(drss);free(dfss);free(jrel);free(Grel);free(jup);free(Gup);free(jleak);free(jtr);
		free(conccm);free(bcm);free(bcq);

}

// メモリ領域が連続な2次元配列
void *malloc2d(size_t size, int row, int col)
{

	char **a, *b;
	int t = size*col;
	int i;

	// インデックスと要素を一気に確保
	a = (char**)malloc((sizeof(*a) + t) * row);

	if (a) {
		// [インデックス, インデックス, ..., 要素, 要素, 要素, ...]と整列させるため要素の開始位置をずらす
		b = (char*)(a + row);

		// 各行の先頭アドレスを与える
		for (i = 0; i < row; i++) {
			a[i] = b;
			b += t; // 要素のサイズ×列の長さの分だけずらす
		}
		return a;
	}

	return NULL;
}

// メモリ領域が連続な3次元配列
void *malloc3d(size_t size, int i, int j, int k)
{

	char ***a, **b, *c;
	int t = size*k;
	int idx1,idx2;

	// インデックスと要素を一気に確保
	a = (char***)malloc((sizeof(*a) + sizeof(**a) * j + t * j) * i);

	if (a) {
		b = (char**)(a + i);
		c = (char *)(b + i * j);

		for (idx1 = 0; idx1 < i; idx1++) {
			a[idx1] = b;
			for (idx2 = 0; idx2 < j; idx2++) {
				b[idx2] = c;
				c += t;
			}
			b += j;
		}
		return a;
	}

	return NULL;
}

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
		case 1: // 1 cluster (equal to ver1.0.0)
			for(i=0;i<MEDIA_SITE;i++){
				if( i>=Ny1*DX && i< Ny2*DX ){
					if( i%DX >=Nx1 && i%DX < Nx2 ) {
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
		case 4: // 4 cluster (symmetry version)
			for(i=0;i<MEDIA_SITE;i++){
				if( (i>=Ny1*DX && i< Ny2*DX) || (i>=Ny3*DX && i< Ny4*DX) ){
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
		case 16: // 4 cluster (symmetry version)
			for(i=0;i<MEDIA_SITE;i++){
				if( (i>=Ny1*DX && i< (Ny1+(Ny2-Ny1-5)/2-5)*DX) || (i>=(Ny1+(Ny2-Ny1-5)/2+5)*DX && i< Ny2*DX)
						|| (i>=Ny3*DX && i< (Ny3+(Ny4-Ny3-5)/2-5)*DX) || (i>=(Ny3+(Ny4-Ny3-5)/2+5)*DX && i< Ny4*DX) ){
					if( (i%DX >=Nx1 && i%DX < Nx1+(Nx2-Nx1-5)/2-5 ) || (i%DX >=Nx1+(Nx2-Nx1-5)/2+5 && i%DX < Nx2)
							|| (i%DX >=Nx3 && i%DX < Nx3+(Nx4-Nx3-5)/2-5 ) || (i%DX >= Nx3+(Nx4-Nx3-5)/2+5 && i%DX < Nx4) ) {
						utype[i]=1;
						c++;
					}
				} 
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

