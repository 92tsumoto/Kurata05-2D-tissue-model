#include <string.h>
#include "syspara.h"

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
}

