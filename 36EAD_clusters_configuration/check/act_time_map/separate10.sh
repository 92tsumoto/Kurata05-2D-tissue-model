#!/usr/bin/csh

cat ../vm_data.out | awk '{if(NR==1) print}' > time0.dat
cat time0.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time0.dat.1
awk -f tmp.awk time0.dat >> time0.dat.1

cat ../vm_data.out | awk '{if(NR==2) print}' > time10.dat
cat time10.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time10.dat.1
awk -f tmp.awk time10.dat >> time10.dat.1

cat ../vm_data.out | awk '{if(NR==3) print}' > time20.dat
cat time20.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time20.dat.1
awk -f tmp.awk time20.dat >> time20.dat.1

cat ../vm_data.out | awk '{if(NR==4) print}' > time30.dat
cat time30.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time30.dat.1
awk -f tmp.awk time30.dat >> time30.dat.1

cat ../vm_data.out | awk '{if(NR==5) print}' > time40.dat
cat time40.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time40.dat.1
awk -f tmp.awk time40.dat >> time40.dat.1

cat ../vm_data.out | awk '{if(NR==6) print}' > time50.dat
cat time50.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time50.dat.1
awk -f tmp.awk time50.dat >> time50.dat.1

cat ../vm_data.out | awk '{if(NR==7) print}' > time60.dat
cat time60.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time60.dat.1
awk -f tmp.awk time60.dat >> time60.dat.1

cat ../vm_data.out | awk '{if(NR==8) print}' > time70.dat
cat time70.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time70.dat.1
awk -f tmp.awk time70.dat >> time70.dat.1

cat ../vm_data.out | awk '{if(NR==9) print}' > time80.dat
cat time80.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time80.dat.1
awk -f tmp.awk time80.dat >> time80.dat.1

cat ../vm_data.out | awk '{if(NR==10) print}' > time90.dat
cat time90.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time90.dat.1
awk -f tmp.awk time90.dat >> time90.dat.1

cat ../vm_data.out | awk '{if(NR==11) print}' > time100.dat
cat time100.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time100.dat.1
awk -f tmp.awk time100.dat >> time100.dat.1

cat ../vm_data.out | awk '{if(NR==12) print}' > time110.dat
cat time110.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time110.dat.1
awk -f tmp.awk time110.dat >> time110.dat.1

cat ../vm_data.out | awk '{if(NR==13) print}' > time120.dat
cat time120.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time120.dat.1
awk -f tmp.awk time120.dat >> time120.dat.1

cat ../vm_data.out | awk '{if(NR==14) print}' > time130.dat
cat time130.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time130.dat.1
awk -f tmp.awk time130.dat >> time130.dat.1

cat ../vm_data.out | awk '{if(NR==15) print}' > time140.dat
cat time140.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time140.dat.1
awk -f tmp.awk time140.dat >> time140.dat.1

cat ../vm_data.out | awk '{if(NR==16) print}' > time150.dat
cat time150.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time150.dat.1
awk -f tmp.awk time150.dat >> time150.dat.1

cat ../vm_data.out | awk '{if(NR==17) print}' > time160.dat
cat time160.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time160.dat.1
awk -f tmp.awk time160.dat >> time160.dat.1

cat ../vm_data.out | awk '{if(NR==18) print}' > time170.dat
cat time170.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time170.dat.1
awk -f tmp.awk time170.dat >> time170.dat.1

cat ../vm_data.out | awk '{if(NR==19) print}' > time180.dat
cat time180.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time180.dat.1
awk -f tmp.awk time180.dat >> time180.dat.1

cat ../vm_data.out | awk '{if(NR==20) print}' > time190.dat
cat time190.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time190.dat.1
awk -f tmp.awk time190.dat >> time190.dat.1

cat ../vm_data.out | awk '{if(NR==21) print}' > time200.dat
cat time200.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time200.dat.1
awk -f tmp.awk time200.dat >> time200.dat.1

cat ../vm_data.out | awk '{if(NR==22) print}' > time210.dat
cat time210.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time210.dat.1
awk -f tmp.awk time210.dat >> time210.dat.1

cat ../vm_data.out | awk '{if(NR==23) print}' > time220.dat
cat time220.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time220.dat.1
awk -f tmp.awk time220.dat >> time220.dat.1

cat ../vm_data.out | awk '{if(NR==24) print}' > time230.dat
cat time230.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time230.dat.1
awk -f tmp.awk time230.dat >> time230.dat.1

cat ../vm_data.out | awk '{if(NR==25) print}' > time240.dat
cat time240.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time240.dat.1
awk -f tmp.awk time240.dat >> time240.dat.1

cat ../vm_data.out | awk '{if(NR==26) print}' > time250.dat
cat time250.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time250.dat.1
awk -f tmp.awk time250.dat >> time250.dat.1

cat ../vm_data.out | awk '{if(NR==27) print}' > time260.dat
cat time260.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time260.dat.1
awk -f tmp.awk time260.dat >> time260.dat.1

cat ../vm_data.out | awk '{if(NR==28) print}' > time270.dat
cat time270.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time270.dat.1
awk -f tmp.awk time270.dat >> time270.dat.1

cat ../vm_data.out | awk '{if(NR==29) print}' > time280.dat
cat time280.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time280.dat.1
awk -f tmp.awk time280.dat >> time280.dat.1

cat ../vm_data.out | awk '{if(NR==30) print}' > time290.dat
cat time290.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time290.dat.1
awk -f tmp.awk time290.dat >> time290.dat.1

cat ../vm_data.out | awk '{if(NR==31) print}' > time300.dat
cat time300.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time300.dat.1
awk -f tmp.awk time300.dat >> time300.dat.1

cat ../vm_data.out | awk '{if(NR==32) print}' > time310.dat
cat time310.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time310.dat.1
awk -f tmp.awk time310.dat >> time310.dat.1

cat ../vm_data.out | awk '{if(NR==33) print}' > time320.dat
cat time320.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time320.dat.1
awk -f tmp.awk time320.dat >> time320.dat.1

cat ../vm_data.out | awk '{if(NR==34) print}' > time330.dat
cat time330.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time330.dat.1
awk -f tmp.awk time330.dat >> time330.dat.1

cat ../vm_data.out | awk '{if(NR==35) print}' > time340.dat
cat time340.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time340.dat.1
awk -f tmp.awk time340.dat >> time340.dat.1

cat ../vm_data.out | awk '{if(NR==36) print}' > time350.dat
cat time350.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time350.dat.1
awk -f tmp.awk time350.dat >> time350.dat.1

cat ../vm_data.out | awk '{if(NR==37) print}' > time360.dat
cat time360.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time360.dat.1
awk -f tmp.awk time360.dat >> time360.dat.1

cat ../vm_data.out | awk '{if(NR==38) print}' > time370.dat
cat time370.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time370.dat.1
awk -f tmp.awk time370.dat >> time370.dat.1

cat ../vm_data.out | awk '{if(NR==39) print}' > time380.dat
cat time380.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time380.dat.1
awk -f tmp.awk time380.dat >> time380.dat.1

cat ../vm_data.out | awk '{if(NR==40) print}' > time390.dat
cat time390.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time390.dat.1
awk -f tmp.awk time390.dat >> time390.dat.1

cat ../vm_data.out | awk '{if(NR==41) print}' > time400.dat
cat time400.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time400.dat.1
awk -f tmp.awk time400.dat >> time400.dat.1

cat ../vm_data.out | awk '{if(NR==42) print}' > time410.dat
cat time410.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time410.dat.1
awk -f tmp.awk time410.dat >> time410.dat.1

cat ../vm_data.out | awk '{if(NR==43) print}' > time420.dat
cat time420.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time420.dat.1
awk -f tmp.awk time420.dat >> time420.dat.1

cat ../vm_data.out | awk '{if(NR==44) print}' > time430.dat
cat time430.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time430.dat.1
awk -f tmp.awk time430.dat >> time430.dat.1

cat ../vm_data.out | awk '{if(NR==45) print}' > time440.dat
cat time440.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time440.dat.1
awk -f tmp.awk time440.dat >> time440.dat.1

cat ../vm_data.out | awk '{if(NR==46) print}' > time450.dat
cat time450.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time450.dat.1
awk -f tmp.awk time450.dat >> time450.dat.1

cat ../vm_data.out | awk '{if(NR==47) print}' > time460.dat
cat time460.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time460.dat.1
awk -f tmp.awk time460.dat >> time460.dat.1

cat ../vm_data.out | awk '{if(NR==48) print}' > time470.dat
cat time470.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time470.dat.1
awk -f tmp.awk time470.dat >> time470.dat.1

cat ../vm_data.out | awk '{if(NR==49) print}' > time480.dat
cat time480.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time480.dat.1
awk -f tmp.awk time480.dat >> time480.dat.1

cat ../vm_data.out | awk '{if(NR==50) print}' > time490.dat
cat time490.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time490.dat.1
awk -f tmp.awk time490.dat >> time490.dat.1

cat ../vm_data.out | awk '{if(NR==51) print}' > time500.dat
cat time500.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time500.dat.1
awk -f tmp.awk time500.dat >> time500.dat.1

cat ../vm_data.out | awk '{if(NR==52) print}' > time510.dat
cat time510.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time510.dat.1
awk -f tmp.awk time510.dat >> time510.dat.1

cat ../vm_data.out | awk '{if(NR==53) print}' > time520.dat
cat time520.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time520.dat.1
awk -f tmp.awk time520.dat >> time520.dat.1

cat ../vm_data.out | awk '{if(NR==54) print}' > time530.dat
cat time530.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time530.dat.1
awk -f tmp.awk time530.dat >> time530.dat.1

cat ../vm_data.out | awk '{if(NR==55) print}' > time540.dat
cat time540.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time540.dat.1
awk -f tmp.awk time540.dat >> time540.dat.1

cat ../vm_data.out | awk '{if(NR==56) print}' > time550.dat
cat time550.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time550.dat.1
awk -f tmp.awk time550.dat >> time550.dat.1

cat ../vm_data.out | awk '{if(NR==57) print}' > time560.dat
cat time560.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time560.dat.1
awk -f tmp.awk time560.dat >> time560.dat.1

cat ../vm_data.out | awk '{if(NR==58) print}' > time570.dat
cat time570.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time570.dat.1
awk -f tmp.awk time570.dat >> time570.dat.1

cat ../vm_data.out | awk '{if(NR==59) print}' > time580.dat
cat time580.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time580.dat.1
awk -f tmp.awk time580.dat >> time580.dat.1

cat ../vm_data.out | awk '{if(NR==60) print}' > time590.dat
cat time590.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time590.dat.1
awk -f tmp.awk time590.dat >> time590.dat.1

cat ../vm_data.out | awk '{if(NR==61) print}' > time600.dat
cat time600.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time600.dat.1
awk -f tmp.awk time600.dat >> time600.dat.1

cat ../vm_data.out | awk '{if(NR==62) print}' > time610.dat
cat time610.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time610.dat.1
awk -f tmp.awk time610.dat >> time610.dat.1

cat ../vm_data.out | awk '{if(NR==63) print}' > time620.dat
cat time620.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time620.dat.1
awk -f tmp.awk time620.dat >> time620.dat.1

cat ../vm_data.out | awk '{if(NR==64) print}' > time630.dat
cat time630.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time630.dat.1
awk -f tmp.awk time630.dat >> time630.dat.1

cat ../vm_data.out | awk '{if(NR==65) print}' > time640.dat
cat time640.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time640.dat.1
awk -f tmp.awk time640.dat >> time640.dat.1

cat ../vm_data.out | awk '{if(NR==66) print}' > time650.dat
cat time650.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time650.dat.1
awk -f tmp.awk time650.dat >> time650.dat.1

cat ../vm_data.out | awk '{if(NR==67) print}' > time660.dat
cat time660.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time660.dat.1
awk -f tmp.awk time660.dat >> time660.dat.1

cat ../vm_data.out | awk '{if(NR==68) print}' > time670.dat
cat time670.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time670.dat.1
awk -f tmp.awk time670.dat >> time670.dat.1

cat ../vm_data.out | awk '{if(NR==69) print}' > time680.dat
cat time680.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time680.dat.1
awk -f tmp.awk time680.dat >> time680.dat.1

cat ../vm_data.out | awk '{if(NR==70) print}' > time690.dat
cat time690.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time690.dat.1
awk -f tmp.awk time690.dat >> time690.dat.1

cat ../vm_data.out | awk '{if(NR==71) print}' > time700.dat
cat time700.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time700.dat.1
awk -f tmp.awk time700.dat >> time700.dat.1

cat ../vm_data.out | awk '{if(NR==72) print}' > time710.dat
cat time710.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time710.dat.1
awk -f tmp.awk time710.dat >> time710.dat.1

cat ../vm_data.out | awk '{if(NR==73) print}' > time720.dat
cat time720.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time720.dat.1
awk -f tmp.awk time720.dat >> time720.dat.1

cat ../vm_data.out | awk '{if(NR==74) print}' > time730.dat
cat time730.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time730.dat.1
awk -f tmp.awk time730.dat >> time730.dat.1

cat ../vm_data.out | awk '{if(NR==75) print}' > time740.dat
cat time740.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time740.dat.1
awk -f tmp.awk time740.dat >> time740.dat.1

cat ../vm_data.out | awk '{if(NR==76) print}' > time750.dat
cat time750.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time750.dat.1
awk -f tmp.awk time750.dat >> time750.dat.1

cat ../vm_data.out | awk '{if(NR==77) print}' > time760.dat
cat time760.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time760.dat.1
awk -f tmp.awk time760.dat >> time760.dat.1

cat ../vm_data.out | awk '{if(NR==78) print}' > time770.dat
cat time770.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time770.dat.1
awk -f tmp.awk time770.dat >> time770.dat.1

cat ../vm_data.out | awk '{if(NR==79) print}' > time780.dat
cat time780.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time780.dat.1
awk -f tmp.awk time780.dat >> time780.dat.1

cat ../vm_data.out | awk '{if(NR==80) print}' > time790.dat
cat time790.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time790.dat.1
awk -f tmp.awk time790.dat >> time790.dat.1

cat ../vm_data.out | awk '{if(NR==81) print}' > time800.dat
cat time800.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time800.dat.1
awk -f tmp.awk time800.dat >> time800.dat.1

cat ../vm_data.out | awk '{if(NR==82) print}' > time810.dat
cat time810.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time810.dat.1
awk -f tmp.awk time810.dat >> time810.dat.1

cat ../vm_data.out | awk '{if(NR==83) print}' > time820.dat
cat time820.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time820.dat.1
awk -f tmp.awk time820.dat >> time820.dat.1

cat ../vm_data.out | awk '{if(NR==84) print}' > time830.dat
cat time830.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time830.dat.1
awk -f tmp.awk time830.dat >> time830.dat.1

cat ../vm_data.out | awk '{if(NR==85) print}' > time840.dat
cat time840.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time840.dat.1
awk -f tmp.awk time840.dat >> time840.dat.1

cat ../vm_data.out | awk '{if(NR==86) print}' > time850.dat
cat time850.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time850.dat.1
awk -f tmp.awk time850.dat >> time850.dat.1

cat ../vm_data.out | awk '{if(NR==87) print}' > time860.dat
cat time860.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time860.dat.1
awk -f tmp.awk time860.dat >> time860.dat.1

cat ../vm_data.out | awk '{if(NR==88) print}' > time870.dat
cat time870.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time870.dat.1
awk -f tmp.awk time870.dat >> time870.dat.1

cat ../vm_data.out | awk '{if(NR==89) print}' > time880.dat
cat time880.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time880.dat.1
awk -f tmp.awk time880.dat >> time880.dat.1

cat ../vm_data.out | awk '{if(NR==90) print}' > time890.dat
cat time890.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time890.dat.1
awk -f tmp.awk time890.dat >> time890.dat.1

cat ../vm_data.out | awk '{if(NR==91) print}' > time900.dat
cat time900.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time900.dat.1
awk -f tmp.awk time900.dat >> time900.dat.1

cat ../vm_data.out | awk '{if(NR==92) print}' > time910.dat
cat time910.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time910.dat.1
awk -f tmp.awk time910.dat >> time910.dat.1

cat ../vm_data.out | awk '{if(NR==93) print}' > time920.dat
cat time920.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time920.dat.1
awk -f tmp.awk time920.dat >> time920.dat.1

cat ../vm_data.out | awk '{if(NR==94) print}' > time930.dat
cat time930.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time930.dat.1
awk -f tmp.awk time930.dat >> time930.dat.1

cat ../vm_data.out | awk '{if(NR==95) print}' > time940.dat
cat time940.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time940.dat.1
awk -f tmp.awk time940.dat >> time940.dat.1

cat ../vm_data.out | awk '{if(NR==96) print}' > time950.dat
cat time950.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time950.dat.1
awk -f tmp.awk time950.dat >> time950.dat.1

cat ../vm_data.out | awk '{if(NR==97) print}' > time960.dat
cat time960.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time960.dat.1
awk -f tmp.awk time960.dat >> time960.dat.1

cat ../vm_data.out | awk '{if(NR==98) print}' > time970.dat
cat time970.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time970.dat.1
awk -f tmp.awk time970.dat >> time970.dat.1

cat ../vm_data.out | awk '{if(NR==99) print}' > time980.dat
cat time980.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time980.dat.1
awk -f tmp.awk time980.dat >> time980.dat.1

cat ../vm_data.out | awk '{if(NR==100) print}' > time990.dat
cat time990.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time990.dat.1
awk -f tmp.awk time990.dat >> time990.dat.1

cat ../vm_data.out | awk '{if(NR==101) print}' > time1000.dat
cat time1000.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1000.dat.1
awk -f tmp.awk time1000.dat >> time1000.dat.1

cat ../vm_data.out | awk '{if(NR==102) print}' > time1010.dat
cat time1010.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1010.dat.1
awk -f tmp.awk time1010.dat >> time1010.dat.1

cat ../vm_data.out | awk '{if(NR==103) print}' > time1020.dat
cat time1020.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1020.dat.1
awk -f tmp.awk time1020.dat >> time1020.dat.1

cat ../vm_data.out | awk '{if(NR==104) print}' > time1030.dat
cat time1030.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1030.dat.1
awk -f tmp.awk time1030.dat >> time1030.dat.1

cat ../vm_data.out | awk '{if(NR==105) print}' > time1040.dat
cat time1040.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1040.dat.1
awk -f tmp.awk time1040.dat >> time1040.dat.1

cat ../vm_data.out | awk '{if(NR==106) print}' > time1050.dat
cat time1050.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1050.dat.1
awk -f tmp.awk time1050.dat >> time1050.dat.1

cat ../vm_data.out | awk '{if(NR==107) print}' > time1060.dat
cat time1060.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1060.dat.1
awk -f tmp.awk time1060.dat >> time1060.dat.1

cat ../vm_data.out | awk '{if(NR==108) print}' > time1070.dat
cat time1070.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1070.dat.1
awk -f tmp.awk time1070.dat >> time1070.dat.1

cat ../vm_data.out | awk '{if(NR==109) print}' > time1080.dat
cat time1080.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1080.dat.1
awk -f tmp.awk time1080.dat >> time1080.dat.1

cat ../vm_data.out | awk '{if(NR==110) print}' > time1090.dat
cat time1090.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1090.dat.1
awk -f tmp.awk time1090.dat >> time1090.dat.1

cat ../vm_data.out | awk '{if(NR==111) print}' > time1100.dat
cat time1100.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1100.dat.1
awk -f tmp.awk time1100.dat >> time1100.dat.1

cat ../vm_data.out | awk '{if(NR==112) print}' > time1110.dat
cat time1110.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1110.dat.1
awk -f tmp.awk time1110.dat >> time1110.dat.1

cat ../vm_data.out | awk '{if(NR==113) print}' > time1120.dat
cat time1120.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1120.dat.1
awk -f tmp.awk time1120.dat >> time1120.dat.1

cat ../vm_data.out | awk '{if(NR==114) print}' > time1130.dat
cat time1130.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1130.dat.1
awk -f tmp.awk time1130.dat >> time1130.dat.1

cat ../vm_data.out | awk '{if(NR==115) print}' > time1140.dat
cat time1140.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1140.dat.1
awk -f tmp.awk time1140.dat >> time1140.dat.1

cat ../vm_data.out | awk '{if(NR==116) print}' > time1150.dat
cat time1150.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1150.dat.1
awk -f tmp.awk time1150.dat >> time1150.dat.1

cat ../vm_data.out | awk '{if(NR==117) print}' > time1160.dat
cat time1160.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1160.dat.1
awk -f tmp.awk time1160.dat >> time1160.dat.1

cat ../vm_data.out | awk '{if(NR==118) print}' > time1170.dat
cat time1170.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1170.dat.1
awk -f tmp.awk time1170.dat >> time1170.dat.1

cat ../vm_data.out | awk '{if(NR==119) print}' > time1180.dat
cat time1180.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1180.dat.1
awk -f tmp.awk time1180.dat >> time1180.dat.1

cat ../vm_data.out | awk '{if(NR==120) print}' > time1190.dat
cat time1190.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1190.dat.1
awk -f tmp.awk time1190.dat >> time1190.dat.1

cat ../vm_data.out | awk '{if(NR==121) print}' > time1200.dat
cat time1200.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1200.dat.1
awk -f tmp.awk time1200.dat >> time1200.dat.1

cat ../vm_data.out | awk '{if(NR==122) print}' > time1210.dat
cat time1210.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1210.dat.1
awk -f tmp.awk time1210.dat >> time1210.dat.1

cat ../vm_data.out | awk '{if(NR==123) print}' > time1220.dat
cat time1220.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1220.dat.1
awk -f tmp.awk time1220.dat >> time1220.dat.1

cat ../vm_data.out | awk '{if(NR==124) print}' > time1230.dat
cat time1230.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1230.dat.1
awk -f tmp.awk time1230.dat >> time1230.dat.1

cat ../vm_data.out | awk '{if(NR==125) print}' > time1240.dat
cat time1240.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1240.dat.1
awk -f tmp.awk time1240.dat >> time1240.dat.1

cat ../vm_data.out | awk '{if(NR==126) print}' > time1250.dat
cat time1250.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1250.dat.1
awk -f tmp.awk time1250.dat >> time1250.dat.1

cat ../vm_data.out | awk '{if(NR==127) print}' > time1260.dat
cat time1260.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1260.dat.1
awk -f tmp.awk time1260.dat >> time1260.dat.1

cat ../vm_data.out | awk '{if(NR==128) print}' > time1270.dat
cat time1270.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1270.dat.1
awk -f tmp.awk time1270.dat >> time1270.dat.1

cat ../vm_data.out | awk '{if(NR==129) print}' > time1280.dat
cat time1280.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1280.dat.1
awk -f tmp.awk time1280.dat >> time1280.dat.1

cat ../vm_data.out | awk '{if(NR==130) print}' > time1290.dat
cat time1290.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1290.dat.1
awk -f tmp.awk time1290.dat >> time1290.dat.1

cat ../vm_data.out | awk '{if(NR==131) print}' > time1300.dat
cat time1300.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1300.dat.1
awk -f tmp.awk time1300.dat >> time1300.dat.1

cat ../vm_data.out | awk '{if(NR==132) print}' > time1310.dat
cat time1310.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1310.dat.1
awk -f tmp.awk time1310.dat >> time1310.dat.1

cat ../vm_data.out | awk '{if(NR==133) print}' > time1320.dat
cat time1320.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1320.dat.1
awk -f tmp.awk time1320.dat >> time1320.dat.1

cat ../vm_data.out | awk '{if(NR==134) print}' > time1330.dat
cat time1330.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1330.dat.1
awk -f tmp.awk time1330.dat >> time1330.dat.1

cat ../vm_data.out | awk '{if(NR==135) print}' > time1340.dat
cat time1340.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1340.dat.1
awk -f tmp.awk time1340.dat >> time1340.dat.1

cat ../vm_data.out | awk '{if(NR==136) print}' > time1350.dat
cat time1350.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1350.dat.1
awk -f tmp.awk time1350.dat >> time1350.dat.1

cat ../vm_data.out | awk '{if(NR==137) print}' > time1360.dat
cat time1360.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1360.dat.1
awk -f tmp.awk time1360.dat >> time1360.dat.1

cat ../vm_data.out | awk '{if(NR==138) print}' > time1370.dat
cat time1370.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1370.dat.1
awk -f tmp.awk time1370.dat >> time1370.dat.1

cat ../vm_data.out | awk '{if(NR==139) print}' > time1380.dat
cat time1380.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1380.dat.1
awk -f tmp.awk time1380.dat >> time1380.dat.1

cat ../vm_data.out | awk '{if(NR==140) print}' > time1390.dat
cat time1390.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1390.dat.1
awk -f tmp.awk time1390.dat >> time1390.dat.1

cat ../vm_data.out | awk '{if(NR==141) print}' > time1400.dat
cat time1400.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1400.dat.1
awk -f tmp.awk time1400.dat >> time1400.dat.1

cat ../vm_data.out | awk '{if(NR==142) print}' > time1410.dat
cat time1410.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1410.dat.1
awk -f tmp.awk time1410.dat >> time1410.dat.1

cat ../vm_data.out | awk '{if(NR==143) print}' > time1420.dat
cat time1420.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1420.dat.1
awk -f tmp.awk time1420.dat >> time1420.dat.1

cat ../vm_data.out | awk '{if(NR==144) print}' > time1430.dat
cat time1430.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1430.dat.1
awk -f tmp.awk time1430.dat >> time1430.dat.1

cat ../vm_data.out | awk '{if(NR==145) print}' > time1440.dat
cat time1440.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1440.dat.1
awk -f tmp.awk time1440.dat >> time1440.dat.1

cat ../vm_data.out | awk '{if(NR==146) print}' > time1450.dat
cat time1450.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1450.dat.1
awk -f tmp.awk time1450.dat >> time1450.dat.1

cat ../vm_data.out | awk '{if(NR==147) print}' > time1460.dat
cat time1460.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1460.dat.1
awk -f tmp.awk time1460.dat >> time1460.dat.1

cat ../vm_data.out | awk '{if(NR==148) print}' > time1470.dat
cat time1470.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1470.dat.1
awk -f tmp.awk time1470.dat >> time1470.dat.1

cat ../vm_data.out | awk '{if(NR==149) print}' > time1480.dat
cat time1480.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1480.dat.1
awk -f tmp.awk time1480.dat >> time1480.dat.1

cat ../vm_data.out | awk '{if(NR==150) print}' > time1490.dat
cat time1490.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1490.dat.1
awk -f tmp.awk time1490.dat >> time1490.dat.1

cat ../vm_data.out | awk '{if(NR==151) print}' > time1500.dat
cat time1500.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1500.dat.1
awk -f tmp.awk time1500.dat >> time1500.dat.1

cat ../vm_data.out | awk '{if(NR==152) print}' > time1510.dat
cat time1510.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1510.dat.1
awk -f tmp.awk time1510.dat >> time1510.dat.1

cat ../vm_data.out | awk '{if(NR==153) print}' > time1520.dat
cat time1520.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1520.dat.1
awk -f tmp.awk time1520.dat >> time1520.dat.1

cat ../vm_data.out | awk '{if(NR==154) print}' > time1530.dat
cat time1530.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1530.dat.1
awk -f tmp.awk time1530.dat >> time1530.dat.1

cat ../vm_data.out | awk '{if(NR==155) print}' > time1540.dat
cat time1540.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1540.dat.1
awk -f tmp.awk time1540.dat >> time1540.dat.1

cat ../vm_data.out | awk '{if(NR==156) print}' > time1550.dat
cat time1550.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1550.dat.1
awk -f tmp.awk time1550.dat >> time1550.dat.1

cat ../vm_data.out | awk '{if(NR==157) print}' > time1560.dat
cat time1560.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1560.dat.1
awk -f tmp.awk time1560.dat >> time1560.dat.1

cat ../vm_data.out | awk '{if(NR==158) print}' > time1570.dat
cat time1570.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1570.dat.1
awk -f tmp.awk time1570.dat >> time1570.dat.1

cat ../vm_data.out | awk '{if(NR==159) print}' > time1580.dat
cat time1580.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1580.dat.1
awk -f tmp.awk time1580.dat >> time1580.dat.1

cat ../vm_data.out | awk '{if(NR==160) print}' > time1590.dat
cat time1590.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1590.dat.1
awk -f tmp.awk time1590.dat >> time1590.dat.1

cat ../vm_data.out | awk '{if(NR==161) print}' > time1600.dat
cat time1600.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1600.dat.1
awk -f tmp.awk time1600.dat >> time1600.dat.1

cat ../vm_data.out | awk '{if(NR==162) print}' > time1610.dat
cat time1610.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1610.dat.1
awk -f tmp.awk time1610.dat >> time1610.dat.1

cat ../vm_data.out | awk '{if(NR==163) print}' > time1620.dat
cat time1620.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1620.dat.1
awk -f tmp.awk time1620.dat >> time1620.dat.1

cat ../vm_data.out | awk '{if(NR==164) print}' > time1630.dat
cat time1630.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1630.dat.1
awk -f tmp.awk time1630.dat >> time1630.dat.1

cat ../vm_data.out | awk '{if(NR==165) print}' > time1640.dat
cat time1640.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1640.dat.1
awk -f tmp.awk time1640.dat >> time1640.dat.1

cat ../vm_data.out | awk '{if(NR==166) print}' > time1650.dat
cat time1650.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1650.dat.1
awk -f tmp.awk time1650.dat >> time1650.dat.1

cat ../vm_data.out | awk '{if(NR==167) print}' > time1660.dat
cat time1660.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1660.dat.1
awk -f tmp.awk time1660.dat >> time1660.dat.1

cat ../vm_data.out | awk '{if(NR==168) print}' > time1670.dat
cat time1670.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1670.dat.1
awk -f tmp.awk time1670.dat >> time1670.dat.1

cat ../vm_data.out | awk '{if(NR==169) print}' > time1680.dat
cat time1680.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1680.dat.1
awk -f tmp.awk time1680.dat >> time1680.dat.1

cat ../vm_data.out | awk '{if(NR==170) print}' > time1690.dat
cat time1690.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1690.dat.1
awk -f tmp.awk time1690.dat >> time1690.dat.1

cat ../vm_data.out | awk '{if(NR==171) print}' > time1700.dat
cat time1700.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1700.dat.1
awk -f tmp.awk time1700.dat >> time1700.dat.1

cat ../vm_data.out | awk '{if(NR==172) print}' > time1710.dat
cat time1710.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1710.dat.1
awk -f tmp.awk time1710.dat >> time1710.dat.1

cat ../vm_data.out | awk '{if(NR==173) print}' > time1720.dat
cat time1720.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1720.dat.1
awk -f tmp.awk time1720.dat >> time1720.dat.1

cat ../vm_data.out | awk '{if(NR==174) print}' > time1730.dat
cat time1730.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1730.dat.1
awk -f tmp.awk time1730.dat >> time1730.dat.1

cat ../vm_data.out | awk '{if(NR==175) print}' > time1740.dat
cat time1740.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1740.dat.1
awk -f tmp.awk time1740.dat >> time1740.dat.1

cat ../vm_data.out | awk '{if(NR==176) print}' > time1750.dat
cat time1750.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1750.dat.1
awk -f tmp.awk time1750.dat >> time1750.dat.1

cat ../vm_data.out | awk '{if(NR==177) print}' > time1760.dat
cat time1760.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1760.dat.1
awk -f tmp.awk time1760.dat >> time1760.dat.1

cat ../vm_data.out | awk '{if(NR==178) print}' > time1770.dat
cat time1770.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1770.dat.1
awk -f tmp.awk time1770.dat >> time1770.dat.1

cat ../vm_data.out | awk '{if(NR==179) print}' > time1780.dat
cat time1780.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1780.dat.1
awk -f tmp.awk time1780.dat >> time1780.dat.1

cat ../vm_data.out | awk '{if(NR==180) print}' > time1790.dat
cat time1790.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1790.dat.1
awk -f tmp.awk time1790.dat >> time1790.dat.1

cat ../vm_data.out | awk '{if(NR==181) print}' > time1800.dat
cat time1800.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1800.dat.1
awk -f tmp.awk time1800.dat >> time1800.dat.1

cat ../vm_data.out | awk '{if(NR==182) print}' > time1810.dat
cat time1810.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1810.dat.1
awk -f tmp.awk time1810.dat >> time1810.dat.1

cat ../vm_data.out | awk '{if(NR==183) print}' > time1820.dat
cat time1820.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1820.dat.1
awk -f tmp.awk time1820.dat >> time1820.dat.1

cat ../vm_data.out | awk '{if(NR==184) print}' > time1830.dat
cat time1830.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1830.dat.1
awk -f tmp.awk time1830.dat >> time1830.dat.1

cat ../vm_data.out | awk '{if(NR==185) print}' > time1840.dat
cat time1840.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1840.dat.1
awk -f tmp.awk time1840.dat >> time1840.dat.1

cat ../vm_data.out | awk '{if(NR==186) print}' > time1850.dat
cat time1850.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1850.dat.1
awk -f tmp.awk time1850.dat >> time1850.dat.1

cat ../vm_data.out | awk '{if(NR==187) print}' > time1860.dat
cat time1860.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1860.dat.1
awk -f tmp.awk time1860.dat >> time1860.dat.1

cat ../vm_data.out | awk '{if(NR==188) print}' > time1870.dat
cat time1870.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1870.dat.1
awk -f tmp.awk time1870.dat >> time1870.dat.1

cat ../vm_data.out | awk '{if(NR==189) print}' > time1880.dat
cat time1880.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1880.dat.1
awk -f tmp.awk time1880.dat >> time1880.dat.1

cat ../vm_data.out | awk '{if(NR==190) print}' > time1890.dat
cat time1890.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1890.dat.1
awk -f tmp.awk time1890.dat >> time1890.dat.1

cat ../vm_data.out | awk '{if(NR==191) print}' > time1900.dat
cat time1900.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1900.dat.1
awk -f tmp.awk time1900.dat >> time1900.dat.1

cat ../vm_data.out | awk '{if(NR==192) print}' > time1910.dat
cat time1910.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1910.dat.1
awk -f tmp.awk time1910.dat >> time1910.dat.1

cat ../vm_data.out | awk '{if(NR==193) print}' > time1920.dat
cat time1920.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1920.dat.1
awk -f tmp.awk time1920.dat >> time1920.dat.1

cat ../vm_data.out | awk '{if(NR==194) print}' > time1930.dat
cat time1930.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1930.dat.1
awk -f tmp.awk time1930.dat >> time1930.dat.1

cat ../vm_data.out | awk '{if(NR==195) print}' > time1940.dat
cat time1940.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1940.dat.1
awk -f tmp.awk time1940.dat >> time1940.dat.1

cat ../vm_data.out | awk '{if(NR==196) print}' > time1950.dat
cat time1950.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1950.dat.1
awk -f tmp.awk time1950.dat >> time1950.dat.1

cat ../vm_data.out | awk '{if(NR==197) print}' > time1960.dat
cat time1960.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1960.dat.1
awk -f tmp.awk time1960.dat >> time1960.dat.1

cat ../vm_data.out | awk '{if(NR==198) print}' > time1970.dat
cat time1970.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1970.dat.1
awk -f tmp.awk time1970.dat >> time1970.dat.1

cat ../vm_data.out | awk '{if(NR==199) print}' > time1980.dat
cat time1980.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1980.dat.1
awk -f tmp.awk time1980.dat >> time1980.dat.1

cat ../vm_data.out | awk '{if(NR==200) print}' > time1990.dat
cat time1990.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1990.dat.1
awk -f tmp.awk time1990.dat >> time1990.dat.1


unix2dos *.dat.1

