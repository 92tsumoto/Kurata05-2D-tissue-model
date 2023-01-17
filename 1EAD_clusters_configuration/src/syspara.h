//#ifndef __SYSPARA_H_INCLUDE 
//#define __SYSPARA_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "mkl.h"

#define NN 17
#define BUF 100
#define NUM 60
#define DX 600
#define DY 600
#define MEDIA_SITE DX*DY
#define beats 1

//#define R 8314.472		// J/kmol/K
//#define F 96485.33771638995	// C/mol
//#define T 310.0		// K
#define R 8314400000000000		// J/kmol/K
#define F 96485000000000000	// C/mol
#define T 310.15		// K

#define dvm 50
#define Emax 2000
#define Emin -2000
#define VNMAX (Emax-Emin)*dvm+1

// Ion Valences 
#define zna 1
#define zk 1
#define zca 2

// An invariant constant
	double FRT,RTF;

// Extracellular ion concentrations
	double Nao,Ko,Cao;

// state variables
	double **vmf,**dvmf;

// Reversal potential
	double *Ena,*Ek,*Eca,*Enaf,*Eks,*Eto;
	double prnak;

// Fast and Late sodium currnets (Inaf)
	double *Gnaf,*inaf,pkna;
	double *minf,*taum,*hinf,*tauh;
	double *Tam,*Tbm,*Thinf,*Ttauh;

// Transient Outward Current (Ito)
	double *ito,*Gto;
	double *rinf,*taur,*qinf,*tauq;
	double *Tar,*Tbr,*Taq10,*Tbq10,*Taq11,*Tbq11,*Taq12,*Tbq12,*Taq2,*Tbq2;
	double pnato,dVgq0,dVgq1,dVgq2;

// Rapid activating potassium current (Ikr)
	double *ikr,*Gkr,kr_rate;
	double *pinf,*taup;
	double *Tpinf,*Tap,*Tbp,*Tpiinf;
	double *gkr_rate;

// Slowlactivating potassium current (Iks)
	double *iks,*Gks,ks_rate;
	double *ninf,*taun;
	double *Tninf,*Ttaun;
	double *gks_rate;
		
// Inward rectifier potassium current (Ik1)
	//double ak1,bk1,k1inf;
	double *ik1,*Gk1;

// L-type Calcium channel current (ICaL)
	double *dinf,*taud,*finf,*tauf;
	double *Tdinf,*Ttaud,*Tfinf,*Ttauf;
	double kmfca,gfCa_inf;
	double *ical,*Gca,Ecal;

// Na-Ca exchanger (INCX)
	double *kncx,*jncx;
	double kmnaex,kmcaex,rncx,ksat;
	double *Tncx0,*Tncx1;
	double c1;

// Sodium-Potassium Pump (INaK)
	double *Gnak,*inak;
	double kmnap,kmkp,nna,rhonak;
	double *Tnak0,*Tnak1;

// Sarcolemmal Ca Pump (Iup)
	double Gpca,Km_pca,*ipca;

// Ca Background Current (ICab)
	double Gcab,*icab;

// Na Background Current (INab)
	double Gnab,*inab;

// SR calcium release flux, via RyR (Jrel)
	double *drss,tau_dr;
	double *dfss,tau_df;
	double *jrel,*Grel,nrel;

// Calcium uptake via SERCA pump
	double *jup,*Gup,kup;

// SR Ca leakage flux
	double pleak,*jleak;

// Translocation of Ca Ions from NSR to JSR
	double tau_tr,*jtr;

// Net Ion Fluxes
	double *jcanet,*jnanet,*jknet;

// Troponin Ca Buffering (in Myoplasm)	
	double concTc,rftn,kftc,kbtc;
// Calmodulin Ca Buffering (in Myoplasm) --- Rapid Buffering Approximation	
	double *conccm,kdcm,*bcm;
// Calsequestrin Ca Buffering (in SR) --- Rapid Buffering Approximation
	double conccq,kdcq,*bcq;

// Total membrane currents 
	double *itotal,*imo;
// Base Stimulus Currnt
    double Istim,Istim_base;

// Cell (Unit) Geometry
	double vcell;
	double vi,vup,vrel;
	double CapHV;
	double length,radius,del_x;
	double s1,s2;
	double Diff_l,Diff_t,rateD,span;

// Cell type
	int *celltype,*utype;
	// initial condition pattern control
	int Nx1,Nx2,Nx3,Nx4,Nx5,Nx6,Nx7,Nx8;
	int Ny1,Ny2,Ny3,Ny4,Ny5,Ny6,Ny7,Ny8;

// Stimulus parameters
// simulation type
	int stim_sw,simtype,cluster;
	int b_num; // Number of stimulus
	double BCL;  // Base cycle length = stimulus period
	int div_num; // Number of division for 1 period

// Data output control parameters
    int write0,write,reduce;
	int outdata,outdata_plus;
	int debug;
    int datas;

    double x0[NUM][NN];

// ECG recording parameter
	double ECG;
	double xp,yp,zp; // coordinates of electrode
	double ux,uy,yz; // coordinates on the ventricular tissue

struct varstract {

	// state variables
	//double **u;

} var;

void function(int site, double t);
void comp_Erev(int site);
void comp_ina(int site);
void comp_ito(int site);
void comp_ical(int site);
void comp_ikr(int site);
void comp_iks(int site);
void comp_ik1(int site);
void comp_incx(int site);
void comp_inak(int site);
void comp_ipca(int site);
void comp_icab(int site);
void comp_inab(int site);
void comp_itot(int site);
void comp_cicr(int site);
void comp_jup(int site);
void comp_jleak(int site);
void comp_jtr(int site);
void comp_concentration (int site);
void comp_diff_current(int site);

void val_consts(FILE *);
void utype_data(FILE *);
void make_ExpTable();

double eular2(double h, double x, double dx);
void eular(int n,double h,double t);
void input_para(FILE *);
void input_init(FILE *,FILE *);
void initial_mem();
void close_mem();
void *malloc2d(size_t size, int row, int col);
void *malloc3d(size_t size, int i, int j, int k);
void vm_data(FILE *,double time);
void out_data(FILE *,FILE *,FILE *,FILE *,FILE *,FILE *,double time);
void out_data_plus(FILE *,double time);
void ECG_data(FILE *,double time, double ECG);

int main(int argc,char **argv);
