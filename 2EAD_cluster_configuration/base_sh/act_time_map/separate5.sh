#!/usr/bin/csh

cat ../vm_data.out | awk '{if(NR==1) print}' > time0.dat
cat time0.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time0.dat.1
awk -f tmp.awk time0.dat >> time0.dat.1

cat ../vm_data.out | awk '{if(NR==2) print}' > time5.dat
cat time5.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time5.dat.1
awk -f tmp.awk time5.dat >> time5.dat.1

cat ../vm_data.out | awk '{if(NR==3) print}' > time10.dat
cat time10.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time10.dat.1
awk -f tmp.awk time10.dat >> time10.dat.1

cat ../vm_data.out | awk '{if(NR==4) print}' > time15.dat
cat time15.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time15.dat.1
awk -f tmp.awk time15.dat >> time15.dat.1

cat ../vm_data.out | awk '{if(NR==5) print}' > time20.dat
cat time20.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time20.dat.1
awk -f tmp.awk time20.dat >> time20.dat.1

cat ../vm_data.out | awk '{if(NR==6) print}' > time25.dat
cat time25.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time25.dat.1
awk -f tmp.awk time25.dat >> time25.dat.1

cat ../vm_data.out | awk '{if(NR==7) print}' > time30.dat
cat time30.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time30.dat.1
awk -f tmp.awk time30.dat >> time30.dat.1

cat ../vm_data.out | awk '{if(NR==8) print}' > time35.dat
cat time35.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time35.dat.1
awk -f tmp.awk time35.dat >> time35.dat.1

cat ../vm_data.out | awk '{if(NR==9) print}' > time40.dat
cat time40.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time40.dat.1
awk -f tmp.awk time40.dat >> time40.dat.1

cat ../vm_data.out | awk '{if(NR==10) print}' > time45.dat
cat time45.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time45.dat.1
awk -f tmp.awk time45.dat >> time45.dat.1

cat ../vm_data.out | awk '{if(NR==11) print}' > time50.dat
cat time50.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time50.dat.1
awk -f tmp.awk time50.dat >> time50.dat.1

cat ../vm_data.out | awk '{if(NR==12) print}' > time55.dat
cat time55.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time55.dat.1
awk -f tmp.awk time55.dat >> time55.dat.1

cat ../vm_data.out | awk '{if(NR==13) print}' > time60.dat
cat time60.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time60.dat.1
awk -f tmp.awk time60.dat >> time60.dat.1

cat ../vm_data.out | awk '{if(NR==14) print}' > time65.dat
cat time65.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time65.dat.1
awk -f tmp.awk time65.dat >> time65.dat.1

cat ../vm_data.out | awk '{if(NR==15) print}' > time70.dat
cat time70.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time70.dat.1
awk -f tmp.awk time70.dat >> time70.dat.1

cat ../vm_data.out | awk '{if(NR==16) print}' > time75.dat
cat time75.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time75.dat.1
awk -f tmp.awk time75.dat >> time75.dat.1

cat ../vm_data.out | awk '{if(NR==17) print}' > time80.dat
cat time80.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time80.dat.1
awk -f tmp.awk time80.dat >> time80.dat.1

cat ../vm_data.out | awk '{if(NR==18) print}' > time85.dat
cat time85.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time85.dat.1
awk -f tmp.awk time85.dat >> time85.dat.1

cat ../vm_data.out | awk '{if(NR==19) print}' > time90.dat
cat time90.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time90.dat.1
awk -f tmp.awk time90.dat >> time90.dat.1

cat ../vm_data.out | awk '{if(NR==20) print}' > time95.dat
cat time95.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time95.dat.1
awk -f tmp.awk time95.dat >> time95.dat.1

cat ../vm_data.out | awk '{if(NR==21) print}' > time100.dat
cat time100.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time100.dat.1
awk -f tmp.awk time100.dat >> time100.dat.1

cat ../vm_data.out | awk '{if(NR==22) print}' > time105.dat
cat time105.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time105.dat.1
awk -f tmp.awk time105.dat >> time105.dat.1

cat ../vm_data.out | awk '{if(NR==23) print}' > time110.dat
cat time110.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time110.dat.1
awk -f tmp.awk time110.dat >> time110.dat.1

cat ../vm_data.out | awk '{if(NR==24) print}' > time115.dat
cat time115.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time115.dat.1
awk -f tmp.awk time115.dat >> time115.dat.1

cat ../vm_data.out | awk '{if(NR==25) print}' > time120.dat
cat time120.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time120.dat.1
awk -f tmp.awk time120.dat >> time120.dat.1

cat ../vm_data.out | awk '{if(NR==26) print}' > time125.dat
cat time125.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time125.dat.1
awk -f tmp.awk time125.dat >> time125.dat.1

cat ../vm_data.out | awk '{if(NR==27) print}' > time130.dat
cat time130.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time130.dat.1
awk -f tmp.awk time130.dat >> time130.dat.1

cat ../vm_data.out | awk '{if(NR==28) print}' > time135.dat
cat time135.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time135.dat.1
awk -f tmp.awk time135.dat >> time135.dat.1

cat ../vm_data.out | awk '{if(NR==29) print}' > time140.dat
cat time140.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time140.dat.1
awk -f tmp.awk time140.dat >> time140.dat.1

cat ../vm_data.out | awk '{if(NR==30) print}' > time145.dat
cat time145.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time145.dat.1
awk -f tmp.awk time145.dat >> time145.dat.1

cat ../vm_data.out | awk '{if(NR==31) print}' > time150.dat
cat time150.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time150.dat.1
awk -f tmp.awk time150.dat >> time150.dat.1

cat ../vm_data.out | awk '{if(NR==32) print}' > time155.dat
cat time155.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time155.dat.1
awk -f tmp.awk time155.dat >> time155.dat.1

cat ../vm_data.out | awk '{if(NR==33) print}' > time160.dat
cat time160.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time160.dat.1
awk -f tmp.awk time160.dat >> time160.dat.1

cat ../vm_data.out | awk '{if(NR==34) print}' > time165.dat
cat time165.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time165.dat.1
awk -f tmp.awk time165.dat >> time165.dat.1

cat ../vm_data.out | awk '{if(NR==35) print}' > time170.dat
cat time170.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time170.dat.1
awk -f tmp.awk time170.dat >> time170.dat.1

cat ../vm_data.out | awk '{if(NR==36) print}' > time175.dat
cat time175.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time175.dat.1
awk -f tmp.awk time175.dat >> time175.dat.1

cat ../vm_data.out | awk '{if(NR==37) print}' > time180.dat
cat time180.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time180.dat.1
awk -f tmp.awk time180.dat >> time180.dat.1

cat ../vm_data.out | awk '{if(NR==38) print}' > time185.dat
cat time185.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time185.dat.1
awk -f tmp.awk time185.dat >> time185.dat.1

cat ../vm_data.out | awk '{if(NR==39) print}' > time190.dat
cat time190.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time190.dat.1
awk -f tmp.awk time190.dat >> time190.dat.1

cat ../vm_data.out | awk '{if(NR==40) print}' > time195.dat
cat time195.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time195.dat.1
awk -f tmp.awk time195.dat >> time195.dat.1

cat ../vm_data.out | awk '{if(NR==41) print}' > time200.dat
cat time200.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time200.dat.1
awk -f tmp.awk time200.dat >> time200.dat.1

cat ../vm_data.out | awk '{if(NR==42) print}' > time205.dat
cat time205.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time205.dat.1
awk -f tmp.awk time205.dat >> time205.dat.1

cat ../vm_data.out | awk '{if(NR==43) print}' > time210.dat
cat time210.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time210.dat.1
awk -f tmp.awk time210.dat >> time210.dat.1

cat ../vm_data.out | awk '{if(NR==44) print}' > time215.dat
cat time215.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time215.dat.1
awk -f tmp.awk time215.dat >> time215.dat.1

cat ../vm_data.out | awk '{if(NR==45) print}' > time220.dat
cat time220.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time220.dat.1
awk -f tmp.awk time220.dat >> time220.dat.1

cat ../vm_data.out | awk '{if(NR==46) print}' > time225.dat
cat time225.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time225.dat.1
awk -f tmp.awk time225.dat >> time225.dat.1

cat ../vm_data.out | awk '{if(NR==47) print}' > time230.dat
cat time230.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time230.dat.1
awk -f tmp.awk time230.dat >> time230.dat.1

cat ../vm_data.out | awk '{if(NR==48) print}' > time235.dat
cat time235.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time235.dat.1
awk -f tmp.awk time235.dat >> time235.dat.1

cat ../vm_data.out | awk '{if(NR==49) print}' > time240.dat
cat time240.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time240.dat.1
awk -f tmp.awk time240.dat >> time240.dat.1

cat ../vm_data.out | awk '{if(NR==50) print}' > time245.dat
cat time245.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time245.dat.1
awk -f tmp.awk time245.dat >> time245.dat.1

cat ../vm_data.out | awk '{if(NR==51) print}' > time250.dat
cat time250.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time250.dat.1
awk -f tmp.awk time250.dat >> time250.dat.1

cat ../vm_data.out | awk '{if(NR==52) print}' > time255.dat
cat time255.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time255.dat.1
awk -f tmp.awk time255.dat >> time255.dat.1

cat ../vm_data.out | awk '{if(NR==53) print}' > time260.dat
cat time260.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time260.dat.1
awk -f tmp.awk time260.dat >> time260.dat.1

cat ../vm_data.out | awk '{if(NR==54) print}' > time265.dat
cat time265.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time265.dat.1
awk -f tmp.awk time265.dat >> time265.dat.1

cat ../vm_data.out | awk '{if(NR==55) print}' > time270.dat
cat time270.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time270.dat.1
awk -f tmp.awk time270.dat >> time270.dat.1

cat ../vm_data.out | awk '{if(NR==56) print}' > time275.dat
cat time275.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time275.dat.1
awk -f tmp.awk time275.dat >> time275.dat.1

cat ../vm_data.out | awk '{if(NR==57) print}' > time280.dat
cat time280.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time280.dat.1
awk -f tmp.awk time280.dat >> time280.dat.1

cat ../vm_data.out | awk '{if(NR==58) print}' > time285.dat
cat time285.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time285.dat.1
awk -f tmp.awk time285.dat >> time285.dat.1

cat ../vm_data.out | awk '{if(NR==59) print}' > time290.dat
cat time290.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time290.dat.1
awk -f tmp.awk time290.dat >> time290.dat.1

cat ../vm_data.out | awk '{if(NR==60) print}' > time295.dat
cat time295.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time295.dat.1
awk -f tmp.awk time295.dat >> time295.dat.1

cat ../vm_data.out | awk '{if(NR==61) print}' > time300.dat
cat time300.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time300.dat.1
awk -f tmp.awk time300.dat >> time300.dat.1

cat ../vm_data.out | awk '{if(NR==62) print}' > time305.dat
cat time305.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time305.dat.1
awk -f tmp.awk time305.dat >> time305.dat.1

cat ../vm_data.out | awk '{if(NR==63) print}' > time310.dat
cat time310.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time310.dat.1
awk -f tmp.awk time310.dat >> time310.dat.1

cat ../vm_data.out | awk '{if(NR==64) print}' > time315.dat
cat time315.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time315.dat.1
awk -f tmp.awk time315.dat >> time315.dat.1

cat ../vm_data.out | awk '{if(NR==65) print}' > time320.dat
cat time320.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time320.dat.1
awk -f tmp.awk time320.dat >> time320.dat.1

cat ../vm_data.out | awk '{if(NR==66) print}' > time325.dat
cat time325.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time325.dat.1
awk -f tmp.awk time325.dat >> time325.dat.1

cat ../vm_data.out | awk '{if(NR==67) print}' > time330.dat
cat time330.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time330.dat.1
awk -f tmp.awk time330.dat >> time330.dat.1

cat ../vm_data.out | awk '{if(NR==68) print}' > time335.dat
cat time335.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time335.dat.1
awk -f tmp.awk time335.dat >> time335.dat.1

cat ../vm_data.out | awk '{if(NR==69) print}' > time340.dat
cat time340.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time340.dat.1
awk -f tmp.awk time340.dat >> time340.dat.1

cat ../vm_data.out | awk '{if(NR==70) print}' > time345.dat
cat time345.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time345.dat.1
awk -f tmp.awk time345.dat >> time345.dat.1

cat ../vm_data.out | awk '{if(NR==71) print}' > time350.dat
cat time350.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time350.dat.1
awk -f tmp.awk time350.dat >> time350.dat.1

cat ../vm_data.out | awk '{if(NR==72) print}' > time355.dat
cat time355.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time355.dat.1
awk -f tmp.awk time355.dat >> time355.dat.1

cat ../vm_data.out | awk '{if(NR==73) print}' > time360.dat
cat time360.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time360.dat.1
awk -f tmp.awk time360.dat >> time360.dat.1

cat ../vm_data.out | awk '{if(NR==74) print}' > time365.dat
cat time365.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time365.dat.1
awk -f tmp.awk time365.dat >> time365.dat.1

cat ../vm_data.out | awk '{if(NR==75) print}' > time370.dat
cat time370.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time370.dat.1
awk -f tmp.awk time370.dat >> time370.dat.1

cat ../vm_data.out | awk '{if(NR==76) print}' > time375.dat
cat time375.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time375.dat.1
awk -f tmp.awk time375.dat >> time375.dat.1

cat ../vm_data.out | awk '{if(NR==77) print}' > time380.dat
cat time380.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time380.dat.1
awk -f tmp.awk time380.dat >> time380.dat.1

cat ../vm_data.out | awk '{if(NR==78) print}' > time385.dat
cat time385.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time385.dat.1
awk -f tmp.awk time385.dat >> time385.dat.1

cat ../vm_data.out | awk '{if(NR==79) print}' > time390.dat
cat time390.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time390.dat.1
awk -f tmp.awk time390.dat >> time390.dat.1

cat ../vm_data.out | awk '{if(NR==80) print}' > time395.dat
cat time395.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time395.dat.1
awk -f tmp.awk time395.dat >> time395.dat.1

cat ../vm_data.out | awk '{if(NR==81) print}' > time400.dat
cat time400.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time400.dat.1
awk -f tmp.awk time400.dat >> time400.dat.1

cat ../vm_data.out | awk '{if(NR==82) print}' > time405.dat
cat time405.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time405.dat.1
awk -f tmp.awk time405.dat >> time405.dat.1

cat ../vm_data.out | awk '{if(NR==83) print}' > time410.dat
cat time410.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time410.dat.1
awk -f tmp.awk time410.dat >> time410.dat.1

cat ../vm_data.out | awk '{if(NR==84) print}' > time415.dat
cat time415.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time415.dat.1
awk -f tmp.awk time415.dat >> time415.dat.1

cat ../vm_data.out | awk '{if(NR==85) print}' > time420.dat
cat time420.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time420.dat.1
awk -f tmp.awk time420.dat >> time420.dat.1

cat ../vm_data.out | awk '{if(NR==86) print}' > time425.dat
cat time425.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time425.dat.1
awk -f tmp.awk time425.dat >> time425.dat.1

cat ../vm_data.out | awk '{if(NR==87) print}' > time430.dat
cat time430.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time430.dat.1
awk -f tmp.awk time430.dat >> time430.dat.1

cat ../vm_data.out | awk '{if(NR==88) print}' > time435.dat
cat time435.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time435.dat.1
awk -f tmp.awk time435.dat >> time435.dat.1

cat ../vm_data.out | awk '{if(NR==89) print}' > time440.dat
cat time440.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time440.dat.1
awk -f tmp.awk time440.dat >> time440.dat.1

cat ../vm_data.out | awk '{if(NR==90) print}' > time445.dat
cat time445.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time445.dat.1
awk -f tmp.awk time445.dat >> time445.dat.1

cat ../vm_data.out | awk '{if(NR==91) print}' > time450.dat
cat time450.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time450.dat.1
awk -f tmp.awk time450.dat >> time450.dat.1

cat ../vm_data.out | awk '{if(NR==92) print}' > time455.dat
cat time455.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time455.dat.1
awk -f tmp.awk time455.dat >> time455.dat.1

cat ../vm_data.out | awk '{if(NR==93) print}' > time460.dat
cat time460.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time460.dat.1
awk -f tmp.awk time460.dat >> time460.dat.1

cat ../vm_data.out | awk '{if(NR==94) print}' > time465.dat
cat time465.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time465.dat.1
awk -f tmp.awk time465.dat >> time465.dat.1

cat ../vm_data.out | awk '{if(NR==95) print}' > time470.dat
cat time470.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time470.dat.1
awk -f tmp.awk time470.dat >> time470.dat.1

cat ../vm_data.out | awk '{if(NR==96) print}' > time475.dat
cat time475.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time475.dat.1
awk -f tmp.awk time475.dat >> time475.dat.1

cat ../vm_data.out | awk '{if(NR==97) print}' > time480.dat
cat time480.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time480.dat.1
awk -f tmp.awk time480.dat >> time480.dat.1

cat ../vm_data.out | awk '{if(NR==98) print}' > time485.dat
cat time485.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time485.dat.1
awk -f tmp.awk time485.dat >> time485.dat.1

cat ../vm_data.out | awk '{if(NR==99) print}' > time490.dat
cat time490.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time490.dat.1
awk -f tmp.awk time490.dat >> time490.dat.1

cat ../vm_data.out | awk '{if(NR==100) print}' > time495.dat
cat time495.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time495.dat.1
awk -f tmp.awk time495.dat >> time495.dat.1

cat ../vm_data.out | awk '{if(NR==101) print}' > time500.dat
cat time500.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time500.dat.1
awk -f tmp.awk time500.dat >> time500.dat.1

cat ../vm_data.out | awk '{if(NR==102) print}' > time505.dat
cat time505.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time505.dat.1
awk -f tmp.awk time505.dat >> time505.dat.1

cat ../vm_data.out | awk '{if(NR==103) print}' > time510.dat
cat time510.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time510.dat.1
awk -f tmp.awk time510.dat >> time510.dat.1

cat ../vm_data.out | awk '{if(NR==104) print}' > time515.dat
cat time515.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time515.dat.1
awk -f tmp.awk time515.dat >> time515.dat.1

cat ../vm_data.out | awk '{if(NR==105) print}' > time520.dat
cat time520.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time520.dat.1
awk -f tmp.awk time520.dat >> time520.dat.1

cat ../vm_data.out | awk '{if(NR==106) print}' > time525.dat
cat time525.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time525.dat.1
awk -f tmp.awk time525.dat >> time525.dat.1

cat ../vm_data.out | awk '{if(NR==107) print}' > time530.dat
cat time530.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time530.dat.1
awk -f tmp.awk time530.dat >> time530.dat.1

cat ../vm_data.out | awk '{if(NR==108) print}' > time535.dat
cat time535.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time535.dat.1
awk -f tmp.awk time535.dat >> time535.dat.1

cat ../vm_data.out | awk '{if(NR==109) print}' > time540.dat
cat time540.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time540.dat.1
awk -f tmp.awk time540.dat >> time540.dat.1

cat ../vm_data.out | awk '{if(NR==110) print}' > time545.dat
cat time545.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time545.dat.1
awk -f tmp.awk time545.dat >> time545.dat.1

cat ../vm_data.out | awk '{if(NR==111) print}' > time550.dat
cat time550.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time550.dat.1
awk -f tmp.awk time550.dat >> time550.dat.1

cat ../vm_data.out | awk '{if(NR==112) print}' > time555.dat
cat time555.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time555.dat.1
awk -f tmp.awk time555.dat >> time555.dat.1

cat ../vm_data.out | awk '{if(NR==113) print}' > time560.dat
cat time560.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time560.dat.1
awk -f tmp.awk time560.dat >> time560.dat.1

cat ../vm_data.out | awk '{if(NR==114) print}' > time565.dat
cat time565.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time565.dat.1
awk -f tmp.awk time565.dat >> time565.dat.1

cat ../vm_data.out | awk '{if(NR==115) print}' > time570.dat
cat time570.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time570.dat.1
awk -f tmp.awk time570.dat >> time570.dat.1

cat ../vm_data.out | awk '{if(NR==116) print}' > time575.dat
cat time575.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time575.dat.1
awk -f tmp.awk time575.dat >> time575.dat.1

cat ../vm_data.out | awk '{if(NR==117) print}' > time580.dat
cat time580.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time580.dat.1
awk -f tmp.awk time580.dat >> time580.dat.1

cat ../vm_data.out | awk '{if(NR==118) print}' > time585.dat
cat time585.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time585.dat.1
awk -f tmp.awk time585.dat >> time585.dat.1

cat ../vm_data.out | awk '{if(NR==119) print}' > time590.dat
cat time590.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time590.dat.1
awk -f tmp.awk time590.dat >> time590.dat.1

cat ../vm_data.out | awk '{if(NR==120) print}' > time595.dat
cat time595.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time595.dat.1
awk -f tmp.awk time595.dat >> time595.dat.1

cat ../vm_data.out | awk '{if(NR==121) print}' > time600.dat
cat time600.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time600.dat.1
awk -f tmp.awk time600.dat >> time600.dat.1

cat ../vm_data.out | awk '{if(NR==122) print}' > time605.dat
cat time605.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time605.dat.1
awk -f tmp.awk time605.dat >> time605.dat.1

cat ../vm_data.out | awk '{if(NR==123) print}' > time610.dat
cat time610.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time610.dat.1
awk -f tmp.awk time610.dat >> time610.dat.1

cat ../vm_data.out | awk '{if(NR==124) print}' > time615.dat
cat time615.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time615.dat.1
awk -f tmp.awk time615.dat >> time615.dat.1

cat ../vm_data.out | awk '{if(NR==125) print}' > time620.dat
cat time620.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time620.dat.1
awk -f tmp.awk time620.dat >> time620.dat.1

cat ../vm_data.out | awk '{if(NR==126) print}' > time625.dat
cat time625.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time625.dat.1
awk -f tmp.awk time625.dat >> time625.dat.1

cat ../vm_data.out | awk '{if(NR==127) print}' > time630.dat
cat time630.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time630.dat.1
awk -f tmp.awk time630.dat >> time630.dat.1

cat ../vm_data.out | awk '{if(NR==128) print}' > time635.dat
cat time635.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time635.dat.1
awk -f tmp.awk time635.dat >> time635.dat.1

cat ../vm_data.out | awk '{if(NR==129) print}' > time640.dat
cat time640.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time640.dat.1
awk -f tmp.awk time640.dat >> time640.dat.1

cat ../vm_data.out | awk '{if(NR==130) print}' > time645.dat
cat time645.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time645.dat.1
awk -f tmp.awk time645.dat >> time645.dat.1

cat ../vm_data.out | awk '{if(NR==131) print}' > time650.dat
cat time650.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time650.dat.1
awk -f tmp.awk time650.dat >> time650.dat.1

cat ../vm_data.out | awk '{if(NR==132) print}' > time655.dat
cat time655.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time655.dat.1
awk -f tmp.awk time655.dat >> time655.dat.1

cat ../vm_data.out | awk '{if(NR==133) print}' > time660.dat
cat time660.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time660.dat.1
awk -f tmp.awk time660.dat >> time660.dat.1

cat ../vm_data.out | awk '{if(NR==134) print}' > time665.dat
cat time665.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time665.dat.1
awk -f tmp.awk time665.dat >> time665.dat.1

cat ../vm_data.out | awk '{if(NR==135) print}' > time670.dat
cat time670.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time670.dat.1
awk -f tmp.awk time670.dat >> time670.dat.1

cat ../vm_data.out | awk '{if(NR==136) print}' > time675.dat
cat time675.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time675.dat.1
awk -f tmp.awk time675.dat >> time675.dat.1

cat ../vm_data.out | awk '{if(NR==137) print}' > time680.dat
cat time680.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time680.dat.1
awk -f tmp.awk time680.dat >> time680.dat.1

cat ../vm_data.out | awk '{if(NR==138) print}' > time685.dat
cat time685.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time685.dat.1
awk -f tmp.awk time685.dat >> time685.dat.1

cat ../vm_data.out | awk '{if(NR==139) print}' > time690.dat
cat time690.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time690.dat.1
awk -f tmp.awk time690.dat >> time690.dat.1

cat ../vm_data.out | awk '{if(NR==140) print}' > time695.dat
cat time695.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time695.dat.1
awk -f tmp.awk time695.dat >> time695.dat.1

cat ../vm_data.out | awk '{if(NR==141) print}' > time700.dat
cat time700.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time700.dat.1
awk -f tmp.awk time700.dat >> time700.dat.1

cat ../vm_data.out | awk '{if(NR==142) print}' > time705.dat
cat time705.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time705.dat.1
awk -f tmp.awk time705.dat >> time705.dat.1

cat ../vm_data.out | awk '{if(NR==143) print}' > time710.dat
cat time710.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time710.dat.1
awk -f tmp.awk time710.dat >> time710.dat.1

cat ../vm_data.out | awk '{if(NR==144) print}' > time715.dat
cat time715.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time715.dat.1
awk -f tmp.awk time715.dat >> time715.dat.1

cat ../vm_data.out | awk '{if(NR==145) print}' > time720.dat
cat time720.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time720.dat.1
awk -f tmp.awk time720.dat >> time720.dat.1

cat ../vm_data.out | awk '{if(NR==146) print}' > time725.dat
cat time725.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time725.dat.1
awk -f tmp.awk time725.dat >> time725.dat.1

cat ../vm_data.out | awk '{if(NR==147) print}' > time730.dat
cat time730.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time730.dat.1
awk -f tmp.awk time730.dat >> time730.dat.1

cat ../vm_data.out | awk '{if(NR==148) print}' > time735.dat
cat time735.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time735.dat.1
awk -f tmp.awk time735.dat >> time735.dat.1

cat ../vm_data.out | awk '{if(NR==149) print}' > time740.dat
cat time740.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time740.dat.1
awk -f tmp.awk time740.dat >> time740.dat.1

cat ../vm_data.out | awk '{if(NR==150) print}' > time745.dat
cat time745.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time745.dat.1
awk -f tmp.awk time745.dat >> time745.dat.1

cat ../vm_data.out | awk '{if(NR==151) print}' > time750.dat
cat time750.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time750.dat.1
awk -f tmp.awk time750.dat >> time750.dat.1

cat ../vm_data.out | awk '{if(NR==152) print}' > time755.dat
cat time755.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time755.dat.1
awk -f tmp.awk time755.dat >> time755.dat.1

cat ../vm_data.out | awk '{if(NR==153) print}' > time760.dat
cat time760.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time760.dat.1
awk -f tmp.awk time760.dat >> time760.dat.1

cat ../vm_data.out | awk '{if(NR==154) print}' > time765.dat
cat time765.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time765.dat.1
awk -f tmp.awk time765.dat >> time765.dat.1

cat ../vm_data.out | awk '{if(NR==155) print}' > time770.dat
cat time770.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time770.dat.1
awk -f tmp.awk time770.dat >> time770.dat.1

cat ../vm_data.out | awk '{if(NR==156) print}' > time775.dat
cat time775.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time775.dat.1
awk -f tmp.awk time775.dat >> time775.dat.1

cat ../vm_data.out | awk '{if(NR==157) print}' > time780.dat
cat time780.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time780.dat.1
awk -f tmp.awk time780.dat >> time780.dat.1

cat ../vm_data.out | awk '{if(NR==158) print}' > time785.dat
cat time785.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time785.dat.1
awk -f tmp.awk time785.dat >> time785.dat.1

cat ../vm_data.out | awk '{if(NR==159) print}' > time790.dat
cat time790.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time790.dat.1
awk -f tmp.awk time790.dat >> time790.dat.1

cat ../vm_data.out | awk '{if(NR==160) print}' > time795.dat
cat time795.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time795.dat.1
awk -f tmp.awk time795.dat >> time795.dat.1

cat ../vm_data.out | awk '{if(NR==161) print}' > time800.dat
cat time800.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time800.dat.1
awk -f tmp.awk time800.dat >> time800.dat.1

cat ../vm_data.out | awk '{if(NR==162) print}' > time805.dat
cat time805.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time805.dat.1
awk -f tmp.awk time805.dat >> time805.dat.1

cat ../vm_data.out | awk '{if(NR==163) print}' > time810.dat
cat time810.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time810.dat.1
awk -f tmp.awk time810.dat >> time810.dat.1

cat ../vm_data.out | awk '{if(NR==164) print}' > time815.dat
cat time815.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time815.dat.1
awk -f tmp.awk time815.dat >> time815.dat.1

cat ../vm_data.out | awk '{if(NR==165) print}' > time820.dat
cat time820.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time820.dat.1
awk -f tmp.awk time820.dat >> time820.dat.1

cat ../vm_data.out | awk '{if(NR==166) print}' > time825.dat
cat time825.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time825.dat.1
awk -f tmp.awk time825.dat >> time825.dat.1

cat ../vm_data.out | awk '{if(NR==167) print}' > time830.dat
cat time830.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time830.dat.1
awk -f tmp.awk time830.dat >> time830.dat.1

cat ../vm_data.out | awk '{if(NR==168) print}' > time835.dat
cat time835.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time835.dat.1
awk -f tmp.awk time835.dat >> time835.dat.1

cat ../vm_data.out | awk '{if(NR==169) print}' > time840.dat
cat time840.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time840.dat.1
awk -f tmp.awk time840.dat >> time840.dat.1

cat ../vm_data.out | awk '{if(NR==170) print}' > time845.dat
cat time845.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time845.dat.1
awk -f tmp.awk time845.dat >> time845.dat.1

cat ../vm_data.out | awk '{if(NR==171) print}' > time850.dat
cat time850.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time850.dat.1
awk -f tmp.awk time850.dat >> time850.dat.1

cat ../vm_data.out | awk '{if(NR==172) print}' > time855.dat
cat time855.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time855.dat.1
awk -f tmp.awk time855.dat >> time855.dat.1

cat ../vm_data.out | awk '{if(NR==173) print}' > time860.dat
cat time860.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time860.dat.1
awk -f tmp.awk time860.dat >> time860.dat.1

cat ../vm_data.out | awk '{if(NR==174) print}' > time865.dat
cat time865.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time865.dat.1
awk -f tmp.awk time865.dat >> time865.dat.1

cat ../vm_data.out | awk '{if(NR==175) print}' > time870.dat
cat time870.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time870.dat.1
awk -f tmp.awk time870.dat >> time870.dat.1

cat ../vm_data.out | awk '{if(NR==176) print}' > time875.dat
cat time875.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time875.dat.1
awk -f tmp.awk time875.dat >> time875.dat.1

cat ../vm_data.out | awk '{if(NR==177) print}' > time880.dat
cat time880.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time880.dat.1
awk -f tmp.awk time880.dat >> time880.dat.1

cat ../vm_data.out | awk '{if(NR==178) print}' > time885.dat
cat time885.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time885.dat.1
awk -f tmp.awk time885.dat >> time885.dat.1

cat ../vm_data.out | awk '{if(NR==179) print}' > time890.dat
cat time890.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time890.dat.1
awk -f tmp.awk time890.dat >> time890.dat.1

cat ../vm_data.out | awk '{if(NR==180) print}' > time895.dat
cat time895.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time895.dat.1
awk -f tmp.awk time895.dat >> time895.dat.1

cat ../vm_data.out | awk '{if(NR==181) print}' > time900.dat
cat time900.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time900.dat.1
awk -f tmp.awk time900.dat >> time900.dat.1

cat ../vm_data.out | awk '{if(NR==182) print}' > time905.dat
cat time905.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time905.dat.1
awk -f tmp.awk time905.dat >> time905.dat.1

cat ../vm_data.out | awk '{if(NR==183) print}' > time910.dat
cat time910.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time910.dat.1
awk -f tmp.awk time910.dat >> time910.dat.1

cat ../vm_data.out | awk '{if(NR==184) print}' > time915.dat
cat time915.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time915.dat.1
awk -f tmp.awk time915.dat >> time915.dat.1

cat ../vm_data.out | awk '{if(NR==185) print}' > time920.dat
cat time920.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time920.dat.1
awk -f tmp.awk time920.dat >> time920.dat.1

cat ../vm_data.out | awk '{if(NR==186) print}' > time925.dat
cat time925.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time925.dat.1
awk -f tmp.awk time925.dat >> time925.dat.1

cat ../vm_data.out | awk '{if(NR==187) print}' > time930.dat
cat time930.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time930.dat.1
awk -f tmp.awk time930.dat >> time930.dat.1

cat ../vm_data.out | awk '{if(NR==188) print}' > time935.dat
cat time935.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time935.dat.1
awk -f tmp.awk time935.dat >> time935.dat.1

cat ../vm_data.out | awk '{if(NR==189) print}' > time940.dat
cat time940.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time940.dat.1
awk -f tmp.awk time940.dat >> time940.dat.1

cat ../vm_data.out | awk '{if(NR==190) print}' > time945.dat
cat time945.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time945.dat.1
awk -f tmp.awk time945.dat >> time945.dat.1

cat ../vm_data.out | awk '{if(NR==191) print}' > time950.dat
cat time950.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time950.dat.1
awk -f tmp.awk time950.dat >> time950.dat.1

cat ../vm_data.out | awk '{if(NR==192) print}' > time955.dat
cat time955.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time955.dat.1
awk -f tmp.awk time955.dat >> time955.dat.1

cat ../vm_data.out | awk '{if(NR==193) print}' > time960.dat
cat time960.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time960.dat.1
awk -f tmp.awk time960.dat >> time960.dat.1

cat ../vm_data.out | awk '{if(NR==194) print}' > time965.dat
cat time965.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time965.dat.1
awk -f tmp.awk time965.dat >> time965.dat.1

cat ../vm_data.out | awk '{if(NR==195) print}' > time970.dat
cat time970.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time970.dat.1
awk -f tmp.awk time970.dat >> time970.dat.1

cat ../vm_data.out | awk '{if(NR==196) print}' > time975.dat
cat time975.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time975.dat.1
awk -f tmp.awk time975.dat >> time975.dat.1

cat ../vm_data.out | awk '{if(NR==197) print}' > time980.dat
cat time980.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time980.dat.1
awk -f tmp.awk time980.dat >> time980.dat.1

cat ../vm_data.out | awk '{if(NR==198) print}' > time985.dat
cat time985.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time985.dat.1
awk -f tmp.awk time985.dat >> time985.dat.1

cat ../vm_data.out | awk '{if(NR==199) print}' > time990.dat
cat time990.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time990.dat.1
awk -f tmp.awk time990.dat >> time990.dat.1

cat ../vm_data.out | awk '{if(NR==200) print}' > time995.dat
cat time995.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time995.dat.1
awk -f tmp.awk time995.dat >> time995.dat.1




unix2dos *.dat.1

