#include <string.h>
#include "syspara.h"

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
	//#pragma ivdep
	#pragma omp parallel for simd
	for(i=0;i<MEDIA_SITE;i++) function(i,t);
	//for(i=MEDIA_SITE-1;i>=0;i--) function(i,t);

	#pragma ivdep
	for(j=0;j<NN;j++){
		#pragma omp parallel for simd
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
	} else if (site > 0 && site%DX == 0 && site < DX*(DY-1)){ // site == 3
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
		//if ((s >= 0 && s < (int)(0.05*DX))||(s%DX<(int)(0.05*DX) && s< (int)(0.05*DY*DX)) ){
		if( (s >= 0*DX && s < 30*DX) && (s%DX >= 0 && s%DX < 30 )){
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

