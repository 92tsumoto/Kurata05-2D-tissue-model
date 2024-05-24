{
	DX=600;
	m=1;
	for (i=2;i<=NF;++i){
		n=(i-1)-DX*(m-1);
		printf("%d %d %lf\n",n,m,$i)
		if(n==DX){m++;}
	}
}

