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
	if ((fp18 = fopen("ECG_data.out","w")) == NULL){ // unit type map data
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
	// Location of unipolar electrogram
		xp = DX*del_x/2; yp = DY*del_x + 4.0;
		
		for(b_num=0; b_num < beats; b_num++){

			for (j = 0; j< (div_num * BCL ); j++){
				t = h*j;
				time += h;

				for(k=0;k<MEDIA_SITE;k++){
					v_old[k] = vmf[0][k];
					v_old2[k] = vmf[0][k];
				//	printf("vm0=%lf\n",vmf[0][0]);
				}
				// for calculation of ECG
				ECG = 0.0; 
				for (i=0; i<MEDIA_SITE;i++){
					ux = (i%DX)*del_x; uy = (i/DX)*del_x;
					if(i==0){
						ECG += ((- vmf[0][i] + vmf[0][i+1]) + (- vmf[0][i] + vmf[0][i+DX]))/del_x/del_x/sqrt((xp-ux)*(xp-ux)+(yp-uy)*(yp-uy))*del_x*del_x;
					} else if (i == MEDIA_SITE-1){ //site = 8
						ECG += ((vmf[0][i-1] - vmf[0][i]) + (vmf[0][i-DX] - vmf[0][i]))/del_x/del_x/sqrt((xp-ux)*(xp-ux)+(yp-uy)*(yp-uy))*del_x*del_x;
					} else if (i == DX - 1 ){ // site == 2
						ECG += ((vmf[0][i-1] - vmf[0][i]) + (- vmf[0][i] + vmf[0][i+DX]))/del_x/del_x/sqrt((xp-ux)*(xp-ux)+(yp-uy)*(yp-uy))*del_x*del_x;
					} else if (i == DX*(DY-1)){ // site == 6
						ECG += ((- vmf[0][i] + vmf[0][i+1]) + (vmf[0][i-DX] - vmf[0][i]))/del_x/del_x/sqrt((xp-ux)*(xp-ux)+(yp-uy)*(yp-uy))*del_x*del_x;
					} else if (i > 0 && i < DX - 1 ){ // site == 1
						ECG += ((vmf[0][i-1] - 2.0*vmf[0][i] + vmf[0][i+1]) + (- vmf[0][i] + vmf[0][i+DX]))/del_x/del_x/sqrt((xp-ux)*(xp-ux)+(yp-uy)*(yp-uy))*del_x*del_x;
					} else if (i > DX*(DY-1) && i < DX*DY-1 ){ // site == 7
						ECG += ((vmf[0][i-1] - 2.0*vmf[0][i] + vmf[0][i+1]) + (vmf[0][i-DX] - vmf[0][i]))/del_x/del_x/sqrt((xp-ux)*(xp-ux)+(yp-uy)*(yp-uy))*del_x*del_x;
					} else if (i > 0 && i%DX == 0 && i < DX*(DY-1) ){ // site == 3
						ECG += ((- vmf[0][i] + vmf[0][i+1]) + (vmf[0][i-DX] - 2.0*vmf[0][i] + vmf[0][i+DX]))/del_x/del_x/sqrt((xp-ux)*(xp-ux)+(yp-uy)*(yp-uy))*del_x*del_x;
					} else if (i > DX-1 && i%DX == DX - 1 && i < DX*DY-1 ){ // site == 5
						ECG += ((vmf[0][i-1] - vmf[0][i]) + (vmf[0][i-DX] - 2.0*vmf[0][i] + vmf[0][i+DX]))/del_x/del_x/sqrt((xp-ux)*(xp-ux)+(yp-uy)*(yp-uy))*del_x*del_x;
					} else { // site == 4
						ECG += ((vmf[0][i-1] - 2.0*vmf[0][i] + vmf[0][i+1]) + (vmf[0][i-DX] - 2.0*vmf[0][i] + vmf[0][i+DX]))/del_x/del_x/sqrt((xp-ux)*(xp-ux)+(yp-uy)*(yp-uy))*del_x*del_x;
					}
				}
				if(j%10==0){
					//printf("%lf ECG=%lf dx=%lf 1/sqrt=%lf\n",time,ECG,del_x,1.0/sqrt((xp-ux)*(xp-ux)+(yp-uy)*(yp-uy))*del_x*del_x);
					ECG_data(fp18,time,ECG);
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
		fclose(fp18);

		free(v_old); free(v_old2);
		free(vmax); free(dvdtmax); free(apd); free(toneapd); free(ttwoapd);
		free(rmbp); free(nair); free(cair); free(kir); free(caimax);
		free(thre_flag); free(thre_flag2); free(v_thre_time); free(v_thre_time2);

		close_mem();

	}
}

