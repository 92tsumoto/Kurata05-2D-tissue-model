#include <string.h>
#include "syspara.h"

typedef double Number;
typedef long long Lint;

void initial_mem()
{
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
	gto_rate=(Number *)calloc(MEDIA_SITE,sizeof(Number));
	if( Tar==NULL || Tbr==NULL || Taq10==NULL || Tbq10==NULL || 
		Taq11==NULL || Tbq11==NULL || Taq12==NULL || Tbq12==NULL || 
		Taq2==NULL || Tbq2==NULL || ito==NULL || Gto==NULL || rinf==NULL || qinf==NULL || taur==NULL || tauq==NULL || gto_rate==NULL) exit(1);
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
	free(Taq2);free(Tbq2);free(ito);free(Gto);free(rinf);free(qinf);free(taur);free(tauq);free(gto_rate);
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

