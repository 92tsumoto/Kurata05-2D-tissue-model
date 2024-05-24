#!/usr/bin/csh

cat ../utype.out | awk '{if(NR==1) print}' > time00.dat
cat time00.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time00.dat.1
awk -f tmp.awk time00.dat >> time00.dat.1

cat ../vm_data.out | awk '{if(NR==1) print}' > time0.dat
cat time0.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time0.dat.1
awk -f tmp.awk time0.dat >> time0.dat.1

cat ../vm_data.out | awk '{if(NR==3) print}' > time2.dat
cat time2.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time2.dat.1
awk -f tmp.awk time2.dat >> time2.dat.1

cat ../vm_data.out | awk '{if(NR==5) print}' > time4.dat
cat time4.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time4.dat.1
awk -f tmp.awk time4.dat >> time4.dat.1

cat ../vm_data.out | awk '{if(NR==7) print}' > time6.dat
cat time6.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time6.dat.1
awk -f tmp.awk time6.dat >> time6.dat.1

cat ../vm_data.out | awk '{if(NR==9) print}' > time8.dat
cat time8.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time8.dat.1
awk -f tmp.awk time8.dat >> time8.dat.1

cat ../vm_data.out | awk '{if(NR==11) print}' > time10.dat
cat time10.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time10.dat.1
awk -f tmp.awk time10.dat >> time10.dat.1

cat ../vm_data.out | awk '{if(NR==13) print}' > time12.dat
cat time12.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time12.dat.1
awk -f tmp.awk time12.dat >> time12.dat.1

cat ../vm_data.out | awk '{if(NR==15) print}' > time14.dat
cat time14.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time14.dat.1
awk -f tmp.awk time14.dat >> time14.dat.1

cat ../vm_data.out | awk '{if(NR==17) print}' > time16.dat
cat time16.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time16.dat.1
awk -f tmp.awk time16.dat >> time16.dat.1

cat ../vm_data.out | awk '{if(NR==19) print}' > time18.dat
cat time18.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time18.dat.1
awk -f tmp.awk time18.dat >> time18.dat.1

cat ../vm_data.out | awk '{if(NR==21) print}' > time20.dat
cat time20.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time20.dat.1
awk -f tmp.awk time20.dat >> time20.dat.1

cat ../vm_data.out | awk '{if(NR==23) print}' > time22.dat
cat time22.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time22.dat.1
awk -f tmp.awk time22.dat >> time22.dat.1

cat ../vm_data.out | awk '{if(NR==25) print}' > time24.dat
cat time24.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time24.dat.1
awk -f tmp.awk time24.dat >> time24.dat.1

cat ../vm_data.out | awk '{if(NR==27) print}' > time26.dat
cat time26.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time26.dat.1
awk -f tmp.awk time26.dat >> time26.dat.1

cat ../vm_data.out | awk '{if(NR==29) print}' > time28.dat
cat time28.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time28.dat.1
awk -f tmp.awk time28.dat >> time28.dat.1

cat ../vm_data.out | awk '{if(NR==31) print}' > time30.dat
cat time30.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time30.dat.1
awk -f tmp.awk time30.dat >> time30.dat.1

cat ../vm_data.out | awk '{if(NR==33) print}' > time32.dat
cat time32.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time32.dat.1
awk -f tmp.awk time32.dat >> time32.dat.1

cat ../vm_data.out | awk '{if(NR==35) print}' > time34.dat
cat time34.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time34.dat.1
awk -f tmp.awk time34.dat >> time34.dat.1

cat ../vm_data.out | awk '{if(NR==37) print}' > time36.dat
cat time36.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time36.dat.1
awk -f tmp.awk time36.dat >> time36.dat.1

cat ../vm_data.out | awk '{if(NR==39) print}' > time38.dat
cat time38.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time38.dat.1
awk -f tmp.awk time38.dat >> time38.dat.1

cat ../vm_data.out | awk '{if(NR==41) print}' > time40.dat
cat time40.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time40.dat.1
awk -f tmp.awk time40.dat >> time40.dat.1

cat ../vm_data.out | awk '{if(NR==43) print}' > time42.dat
cat time42.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time42.dat.1
awk -f tmp.awk time42.dat >> time42.dat.1

cat ../vm_data.out | awk '{if(NR==45) print}' > time44.dat
cat time44.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time44.dat.1
awk -f tmp.awk time44.dat >> time44.dat.1

cat ../vm_data.out | awk '{if(NR==47) print}' > time46.dat
cat time46.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time46.dat.1
awk -f tmp.awk time46.dat >> time46.dat.1

cat ../vm_data.out | awk '{if(NR==49) print}' > time48.dat
cat time48.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time48.dat.1
awk -f tmp.awk time48.dat >> time48.dat.1

cat ../vm_data.out | awk '{if(NR==51) print}' > time50.dat
cat time50.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time50.dat.1
awk -f tmp.awk time50.dat >> time50.dat.1

cat ../vm_data.out | awk '{if(NR==53) print}' > time52.dat
cat time52.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time52.dat.1
awk -f tmp.awk time52.dat >> time52.dat.1

cat ../vm_data.out | awk '{if(NR==55) print}' > time54.dat
cat time54.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time54.dat.1
awk -f tmp.awk time54.dat >> time54.dat.1

cat ../vm_data.out | awk '{if(NR==57) print}' > time56.dat
cat time56.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time56.dat.1
awk -f tmp.awk time56.dat >> time56.dat.1

cat ../vm_data.out | awk '{if(NR==59) print}' > time58.dat
cat time58.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time58.dat.1
awk -f tmp.awk time58.dat >> time58.dat.1

cat ../vm_data.out | awk '{if(NR==61) print}' > time60.dat
cat time60.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time60.dat.1
awk -f tmp.awk time60.dat >> time60.dat.1

cat ../vm_data.out | awk '{if(NR==63) print}' > time62.dat
cat time62.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time62.dat.1
awk -f tmp.awk time62.dat >> time62.dat.1

cat ../vm_data.out | awk '{if(NR==65) print}' > time64.dat
cat time64.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time64.dat.1
awk -f tmp.awk time64.dat >> time64.dat.1

cat ../vm_data.out | awk '{if(NR==67) print}' > time66.dat
cat time66.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time66.dat.1
awk -f tmp.awk time66.dat >> time66.dat.1

cat ../vm_data.out | awk '{if(NR==69) print}' > time68.dat
cat time68.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time68.dat.1
awk -f tmp.awk time68.dat >> time68.dat.1

cat ../vm_data.out | awk '{if(NR==71) print}' > time70.dat
cat time70.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time70.dat.1
awk -f tmp.awk time70.dat >> time70.dat.1

cat ../vm_data.out | awk '{if(NR==73) print}' > time72.dat
cat time72.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time72.dat.1
awk -f tmp.awk time72.dat >> time72.dat.1

cat ../vm_data.out | awk '{if(NR==75) print}' > time74.dat
cat time74.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time74.dat.1
awk -f tmp.awk time74.dat >> time74.dat.1

cat ../vm_data.out | awk '{if(NR==77) print}' > time76.dat
cat time76.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time76.dat.1
awk -f tmp.awk time76.dat >> time76.dat.1

cat ../vm_data.out | awk '{if(NR==79) print}' > time78.dat
cat time78.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time78.dat.1
awk -f tmp.awk time78.dat >> time78.dat.1

cat ../vm_data.out | awk '{if(NR==81) print}' > time80.dat
cat time80.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time80.dat.1
awk -f tmp.awk time80.dat >> time80.dat.1

cat ../vm_data.out | awk '{if(NR==83) print}' > time82.dat
cat time82.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time82.dat.1
awk -f tmp.awk time82.dat >> time82.dat.1

cat ../vm_data.out | awk '{if(NR==85) print}' > time84.dat
cat time84.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time84.dat.1
awk -f tmp.awk time84.dat >> time84.dat.1

cat ../vm_data.out | awk '{if(NR==87) print}' > time86.dat
cat time86.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time86.dat.1
awk -f tmp.awk time86.dat >> time86.dat.1

cat ../vm_data.out | awk '{if(NR==89) print}' > time88.dat
cat time88.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time88.dat.1
awk -f tmp.awk time88.dat >> time88.dat.1

cat ../vm_data.out | awk '{if(NR==91) print}' > time90.dat
cat time90.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time90.dat.1
awk -f tmp.awk time90.dat >> time90.dat.1

cat ../vm_data.out | awk '{if(NR==93) print}' > time92.dat
cat time92.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time92.dat.1
awk -f tmp.awk time92.dat >> time92.dat.1

cat ../vm_data.out | awk '{if(NR==95) print}' > time94.dat
cat time94.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time94.dat.1
awk -f tmp.awk time94.dat >> time94.dat.1

cat ../vm_data.out | awk '{if(NR==97) print}' > time96.dat
cat time96.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time96.dat.1
awk -f tmp.awk time96.dat >> time96.dat.1

cat ../vm_data.out | awk '{if(NR==99) print}' > time98.dat
cat time98.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time98.dat.1
awk -f tmp.awk time98.dat >> time98.dat.1

cat ../vm_data.out | awk '{if(NR==101) print}' > time100.dat
cat time100.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time100.dat.1
awk -f tmp.awk time100.dat >> time100.dat.1

cat ../vm_data.out | awk '{if(NR==103) print}' > time102.dat
cat time102.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time102.dat.1
awk -f tmp.awk time102.dat >> time102.dat.1

cat ../vm_data.out | awk '{if(NR==105) print}' > time104.dat
cat time104.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time104.dat.1
awk -f tmp.awk time104.dat >> time104.dat.1

cat ../vm_data.out | awk '{if(NR==107) print}' > time106.dat
cat time106.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time106.dat.1
awk -f tmp.awk time106.dat >> time106.dat.1

cat ../vm_data.out | awk '{if(NR==109) print}' > time108.dat
cat time108.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time108.dat.1
awk -f tmp.awk time108.dat >> time108.dat.1

cat ../vm_data.out | awk '{if(NR==111) print}' > time110.dat
cat time110.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time110.dat.1
awk -f tmp.awk time110.dat >> time110.dat.1

cat ../vm_data.out | awk '{if(NR==113) print}' > time112.dat
cat time112.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time112.dat.1
awk -f tmp.awk time112.dat >> time112.dat.1

cat ../vm_data.out | awk '{if(NR==115) print}' > time114.dat
cat time114.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time114.dat.1
awk -f tmp.awk time114.dat >> time114.dat.1

cat ../vm_data.out | awk '{if(NR==117) print}' > time116.dat
cat time116.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time116.dat.1
awk -f tmp.awk time116.dat >> time116.dat.1

cat ../vm_data.out | awk '{if(NR==119) print}' > time118.dat
cat time118.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time118.dat.1
awk -f tmp.awk time118.dat >> time118.dat.1

cat ../vm_data.out | awk '{if(NR==121) print}' > time120.dat
cat time120.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time120.dat.1
awk -f tmp.awk time120.dat >> time120.dat.1

cat ../vm_data.out | awk '{if(NR==123) print}' > time122.dat
cat time122.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time122.dat.1
awk -f tmp.awk time122.dat >> time122.dat.1

cat ../vm_data.out | awk '{if(NR==125) print}' > time124.dat
cat time124.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time124.dat.1
awk -f tmp.awk time124.dat >> time124.dat.1

cat ../vm_data.out | awk '{if(NR==127) print}' > time126.dat
cat time126.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time126.dat.1
awk -f tmp.awk time126.dat >> time126.dat.1

cat ../vm_data.out | awk '{if(NR==129) print}' > time128.dat
cat time128.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time128.dat.1
awk -f tmp.awk time128.dat >> time128.dat.1

cat ../vm_data.out | awk '{if(NR==131) print}' > time130.dat
cat time130.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time130.dat.1
awk -f tmp.awk time130.dat >> time130.dat.1

cat ../vm_data.out | awk '{if(NR==133) print}' > time132.dat
cat time132.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time132.dat.1
awk -f tmp.awk time132.dat >> time132.dat.1

cat ../vm_data.out | awk '{if(NR==135) print}' > time134.dat
cat time134.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time134.dat.1
awk -f tmp.awk time134.dat >> time134.dat.1

cat ../vm_data.out | awk '{if(NR==137) print}' > time136.dat
cat time136.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time136.dat.1
awk -f tmp.awk time136.dat >> time136.dat.1

cat ../vm_data.out | awk '{if(NR==139) print}' > time138.dat
cat time138.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time138.dat.1
awk -f tmp.awk time138.dat >> time138.dat.1

cat ../vm_data.out | awk '{if(NR==141) print}' > time140.dat
cat time140.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time140.dat.1
awk -f tmp.awk time140.dat >> time140.dat.1

cat ../vm_data.out | awk '{if(NR==143) print}' > time142.dat
cat time142.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time142.dat.1
awk -f tmp.awk time142.dat >> time142.dat.1

cat ../vm_data.out | awk '{if(NR==145) print}' > time144.dat
cat time144.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time144.dat.1
awk -f tmp.awk time144.dat >> time144.dat.1

cat ../vm_data.out | awk '{if(NR==147) print}' > time146.dat
cat time146.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time146.dat.1
awk -f tmp.awk time146.dat >> time146.dat.1

cat ../vm_data.out | awk '{if(NR==149) print}' > time148.dat
cat time148.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time148.dat.1
awk -f tmp.awk time148.dat >> time148.dat.1

cat ../vm_data.out | awk '{if(NR==151) print}' > time150.dat
cat time150.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time150.dat.1
awk -f tmp.awk time150.dat >> time150.dat.1

cat ../vm_data.out | awk '{if(NR==153) print}' > time152.dat
cat time152.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time152.dat.1
awk -f tmp.awk time152.dat >> time152.dat.1

cat ../vm_data.out | awk '{if(NR==155) print}' > time154.dat
cat time154.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time154.dat.1
awk -f tmp.awk time154.dat >> time154.dat.1

cat ../vm_data.out | awk '{if(NR==157) print}' > time156.dat
cat time156.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time156.dat.1
awk -f tmp.awk time156.dat >> time156.dat.1

cat ../vm_data.out | awk '{if(NR==159) print}' > time158.dat
cat time158.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time158.dat.1
awk -f tmp.awk time158.dat >> time158.dat.1

cat ../vm_data.out | awk '{if(NR==161) print}' > time160.dat
cat time160.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time160.dat.1
awk -f tmp.awk time160.dat >> time160.dat.1

cat ../vm_data.out | awk '{if(NR==163) print}' > time162.dat
cat time162.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time162.dat.1
awk -f tmp.awk time162.dat >> time162.dat.1

cat ../vm_data.out | awk '{if(NR==165) print}' > time164.dat
cat time164.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time164.dat.1
awk -f tmp.awk time164.dat >> time164.dat.1

cat ../vm_data.out | awk '{if(NR==167) print}' > time166.dat
cat time166.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time166.dat.1
awk -f tmp.awk time166.dat >> time166.dat.1

cat ../vm_data.out | awk '{if(NR==169) print}' > time168.dat
cat time168.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time168.dat.1
awk -f tmp.awk time168.dat >> time168.dat.1

cat ../vm_data.out | awk '{if(NR==171) print}' > time170.dat
cat time170.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time170.dat.1
awk -f tmp.awk time170.dat >> time170.dat.1

cat ../vm_data.out | awk '{if(NR==173) print}' > time172.dat
cat time172.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time172.dat.1
awk -f tmp.awk time172.dat >> time172.dat.1

cat ../vm_data.out | awk '{if(NR==175) print}' > time174.dat
cat time172.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time174.dat.1
awk -f tmp.awk time174.dat >> time174.dat.1

cat ../vm_data.out | awk '{if(NR==177) print}' > time176.dat
cat time172.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time176.dat.1
awk -f tmp.awk time176.dat >> time176.dat.1

cat ../vm_data.out | awk '{if(NR==179) print}' > time178.dat
cat time172.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time178.dat.1
awk -f tmp.awk time178.dat >> time178.dat.1

cat ../vm_data.out | awk '{if(NR==181) print}' > time180.dat
cat time180.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time180.dat.1
awk -f tmp.awk time180.dat >> time180.dat.1

cat ../vm_data.out | awk '{if(NR==183) print}' > time182.dat
cat time182.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time182.dat.1
awk -f tmp.awk time182.dat >> time182.dat.1

cat ../vm_data.out | awk '{if(NR==185) print}' > time184.dat
cat time184.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time184.dat.1
awk -f tmp.awk time184.dat >> time184.dat.1

cat ../vm_data.out | awk '{if(NR==187) print}' > time186.dat
cat time186.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time186.dat.1
awk -f tmp.awk time186.dat >> time186.dat.1

cat ../vm_data.out | awk '{if(NR==189) print}' > time188.dat
cat time188.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time188.dat.1
awk -f tmp.awk time188.dat >> time188.dat.1

cat ../vm_data.out | awk '{if(NR==191) print}' > time190.dat
cat time190.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time190.dat.1
awk -f tmp.awk time190.dat >> time190.dat.1

cat ../vm_data.out | awk '{if(NR==193) print}' > time192.dat
cat time192.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time192.dat.1
awk -f tmp.awk time192.dat >> time192.dat.1

cat ../vm_data.out | awk '{if(NR==195) print}' > time194.dat
cat time194.dat | awk '{print "L4bels 250,30 t="$1"(ms)"}' > time194.dat.1
awk -f tmp.awk time194.dat >> time194.dat.1

cat ../vm_data.out | awk '{if(NR==197) print}' > time196.dat
cat time196.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time196.dat.1
awk -f tmp.awk time196.dat >> time196.dat.1

cat ../vm_data.out | awk '{if(NR==199) print}' > time198.dat
cat time198.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time198.dat.1
awk -f tmp.awk time198.dat >> time198.dat.1

cat ../vm_data.out | awk '{if(NR==201) print}' > time200.dat
cat time200.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time200.dat.1
awk -f tmp.awk time200.dat >> time200.dat.1

cat ../vm_data.out | awk '{if(NR==203) print}' > time202.dat
cat time202.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time202.dat.1
awk -f tmp.awk time202.dat >> time202.dat.1

cat ../vm_data.out | awk '{if(NR==205) print}' > time204.dat
cat time204.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time204.dat.1
awk -f tmp.awk time204.dat >> time204.dat.1

cat ../vm_data.out | awk '{if(NR==207) print}' > time206.dat
cat time206.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time206.dat.1
awk -f tmp.awk time206.dat >> time206.dat.1

cat ../vm_data.out | awk '{if(NR==209) print}' > time208.dat
cat time208.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time208.dat.1
awk -f tmp.awk time208.dat >> time208.dat.1

cat ../vm_data.out | awk '{if(NR==211) print}' > time210.dat
cat time210.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time210.dat.1
awk -f tmp.awk time210.dat >> time210.dat.1

cat ../vm_data.out | awk '{if(NR==213) print}' > time212.dat
cat time212.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time212.dat.1
awk -f tmp.awk time212.dat >> time212.dat.1

cat ../vm_data.out | awk '{if(NR==215) print}' > time214.dat
cat time214.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time214.dat.1
awk -f tmp.awk time214.dat >> time214.dat.1

cat ../vm_data.out | awk '{if(NR==217) print}' > time216.dat
cat time216.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time216.dat.1
awk -f tmp.awk time216.dat >> time216.dat.1

cat ../vm_data.out | awk '{if(NR==219) print}' > time218.dat
cat time218.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time218.dat.1
awk -f tmp.awk time218.dat >> time218.dat.1

cat ../vm_data.out | awk '{if(NR==221) print}' > time220.dat
cat time220.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time220.dat.1
awk -f tmp.awk time220.dat >> time220.dat.1

cat ../vm_data.out | awk '{if(NR==223) print}' > time222.dat
cat time222.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time222.dat.1
awk -f tmp.awk time222.dat >> time222.dat.1

cat ../vm_data.out | awk '{if(NR==225) print}' > time224.dat
cat time224.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time224.dat.1
awk -f tmp.awk time224.dat >> time224.dat.1

cat ../vm_data.out | awk '{if(NR==227) print}' > time226.dat
cat time226.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time226.dat.1
awk -f tmp.awk time226.dat >> time226.dat.1

cat ../vm_data.out | awk '{if(NR==229) print}' > time228.dat
cat time228.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time228.dat.1
awk -f tmp.awk time228.dat >> time228.dat.1

cat ../vm_data.out | awk '{if(NR==231) print}' > time230.dat
cat time230.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time230.dat.1
awk -f tmp.awk time230.dat >> time230.dat.1

cat ../vm_data.out | awk '{if(NR==233) print}' > time232.dat
cat time232.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time232.dat.1
awk -f tmp.awk time232.dat >> time232.dat.1

cat ../vm_data.out | awk '{if(NR==235) print}' > time234.dat
cat time234.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time234.dat.1
awk -f tmp.awk time234.dat >> time234.dat.1

cat ../vm_data.out | awk '{if(NR==237) print}' > time236.dat
cat time236.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time236.dat.1
awk -f tmp.awk time236.dat >> time236.dat.1

cat ../vm_data.out | awk '{if(NR==239) print}' > time238.dat
cat time238.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time238.dat.1
awk -f tmp.awk time238.dat >> time238.dat.1

cat ../vm_data.out | awk '{if(NR==241) print}' > time240.dat
cat time240.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time240.dat.1
awk -f tmp.awk time240.dat >> time240.dat.1

cat ../vm_data.out | awk '{if(NR==243) print}' > time242.dat
cat time242.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time242.dat.1
awk -f tmp.awk time242.dat >> time242.dat.1

cat ../vm_data.out | awk '{if(NR==245) print}' > time244.dat
cat time244.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time244.dat.1
awk -f tmp.awk time244.dat >> time244.dat.1

cat ../vm_data.out | awk '{if(NR==247) print}' > time246.dat
cat time246.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time246.dat.1
awk -f tmp.awk time246.dat >> time246.dat.1

cat ../vm_data.out | awk '{if(NR==249) print}' > time248.dat
cat time248.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time248.dat.1
awk -f tmp.awk time248.dat >> time248.dat.1

cat ../vm_data.out | awk '{if(NR==251) print}' > time250.dat
cat time250.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time250.dat.1
awk -f tmp.awk time250.dat >> time250.dat.1

cat ../vm_data.out | awk '{if(NR==253) print}' > time252.dat
cat time252.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time252.dat.1
awk -f tmp.awk time252.dat >> time252.dat.1

cat ../vm_data.out | awk '{if(NR==255) print}' > time254.dat
cat time254.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time254.dat.1
awk -f tmp.awk time254.dat >> time254.dat.1

cat ../vm_data.out | awk '{if(NR==257) print}' > time256.dat
cat time256.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time256.dat.1
awk -f tmp.awk time256.dat >> time256.dat.1

cat ../vm_data.out | awk '{if(NR==259) print}' > time258.dat
cat time258.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time258.dat.1
awk -f tmp.awk time258.dat >> time258.dat.1

cat ../vm_data.out | awk '{if(NR==261) print}' > time260.dat
cat time260.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time260.dat.1
awk -f tmp.awk time260.dat >> time260.dat.1

cat ../vm_data.out | awk '{if(NR==263) print}' > time262.dat
cat time262.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time262.dat.1
awk -f tmp.awk time262.dat >> time262.dat.1

cat ../vm_data.out | awk '{if(NR==265) print}' > time264.dat
cat time264.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time264.dat.1
awk -f tmp.awk time264.dat >> time264.dat.1

cat ../vm_data.out | awk '{if(NR==267) print}' > time266.dat
cat time266.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time266.dat.1
awk -f tmp.awk time266.dat >> time266.dat.1

cat ../vm_data.out | awk '{if(NR==269) print}' > time268.dat
cat time268.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time268.dat.1
awk -f tmp.awk time268.dat >> time268.dat.1

cat ../vm_data.out | awk '{if(NR==271) print}' > time270.dat
cat time270.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time270.dat.1
awk -f tmp.awk time270.dat >> time270.dat.1

cat ../vm_data.out | awk '{if(NR==273) print}' > time272.dat
cat time272.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time272.dat.1
awk -f tmp.awk time272.dat >> time272.dat.1

cat ../vm_data.out | awk '{if(NR==275) print}' > time274.dat
cat time274.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time274.dat.1
awk -f tmp.awk time274.dat >> time274.dat.1

cat ../vm_data.out | awk '{if(NR==277) print}' > time276.dat
cat time276.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time276.dat.1
awk -f tmp.awk time276.dat >> time276.dat.1

cat ../vm_data.out | awk '{if(NR==279) print}' > time278.dat
cat time278.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time278.dat.1
awk -f tmp.awk time278.dat >> time278.dat.1

cat ../vm_data.out | awk '{if(NR==281) print}' > time280.dat
cat time280.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time280.dat.1
awk -f tmp.awk time280.dat >> time280.dat.1

cat ../vm_data.out | awk '{if(NR==283) print}' > time282.dat
cat time282.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time282.dat.1
awk -f tmp.awk time282.dat >> time282.dat.1

cat ../vm_data.out | awk '{if(NR==285) print}' > time284.dat
cat time284.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time284.dat.1
awk -f tmp.awk time284.dat >> time284.dat.1

cat ../vm_data.out | awk '{if(NR==287) print}' > time286.dat
cat time286.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time286.dat.1
awk -f tmp.awk time286.dat >> time286.dat.1

cat ../vm_data.out | awk '{if(NR==289) print}' > time288.dat
cat time288.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time288.dat.1
awk -f tmp.awk time288.dat >> time288.dat.1

cat ../vm_data.out | awk '{if(NR==291) print}' > time290.dat
cat time290.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time290.dat.1
awk -f tmp.awk time290.dat >> time290.dat.1

cat ../vm_data.out | awk '{if(NR==293) print}' > time292.dat
cat time292.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time292.dat.1
awk -f tmp.awk time292.dat >> time292.dat.1

cat ../vm_data.out | awk '{if(NR==295) print}' > time294.dat
cat time294.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time294.dat.1
awk -f tmp.awk time294.dat >> time294.dat.1

cat ../vm_data.out | awk '{if(NR==297) print}' > time296.dat
cat time296.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time296.dat.1
awk -f tmp.awk time296.dat >> time296.dat.1

cat ../vm_data.out | awk '{if(NR==299) print}' > time298.dat
cat time298.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time298.dat.1
awk -f tmp.awk time298.dat >> time298.dat.1

cat ../vm_data.out | awk '{if(NR==301) print}' > time300.dat
cat time300.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time300.dat.1
awk -f tmp.awk time300.dat >> time300.dat.1

cat ../vm_data.out | awk '{if(NR==303) print}' > time302.dat
cat time302.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time302.dat.1
awk -f tmp.awk time302.dat >> time302.dat.1

cat ../vm_data.out | awk '{if(NR==305) print}' > time304.dat
cat time304.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time304.dat.1
awk -f tmp.awk time304.dat >> time304.dat.1

cat ../vm_data.out | awk '{if(NR==307) print}' > time306.dat
cat time306.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time306.dat.1
awk -f tmp.awk time306.dat >> time306.dat.1

cat ../vm_data.out | awk '{if(NR==309) print}' > time308.dat
cat time308.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time308.dat.1
awk -f tmp.awk time308.dat >> time308.dat.1

cat ../vm_data.out | awk '{if(NR==311) print}' > time310.dat
cat time310.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time310.dat.1
awk -f tmp.awk time310.dat >> time310.dat.1

cat ../vm_data.out | awk '{if(NR==313) print}' > time312.dat
cat time312.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time312.dat.1
awk -f tmp.awk time312.dat >> time312.dat.1

cat ../vm_data.out | awk '{if(NR==315) print}' > time314.dat
cat time314.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time314.dat.1
awk -f tmp.awk time314.dat >> time314.dat.1

cat ../vm_data.out | awk '{if(NR==317) print}' > time316.dat
cat time316.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time316.dat.1
awk -f tmp.awk time316.dat >> time316.dat.1

cat ../vm_data.out | awk '{if(NR==319) print}' > time318.dat
cat time318.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time318.dat.1
awk -f tmp.awk time318.dat >> time318.dat.1

cat ../vm_data.out | awk '{if(NR==321) print}' > time320.dat
cat time320.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time320.dat.1
awk -f tmp.awk time320.dat >> time320.dat.1

cat ../vm_data.out | awk '{if(NR==323) print}' > time322.dat
cat time322.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time322.dat.1
awk -f tmp.awk time322.dat >> time322.dat.1

cat ../vm_data.out | awk '{if(NR==325) print}' > time324.dat
cat time324.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time324.dat.1
awk -f tmp.awk time324.dat >> time324.dat.1

cat ../vm_data.out | awk '{if(NR==327) print}' > time326.dat
cat time326.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time326.dat.1
awk -f tmp.awk time326.dat >> time326.dat.1

cat ../vm_data.out | awk '{if(NR==329) print}' > time328.dat
cat time328.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time328.dat.1
awk -f tmp.awk time328.dat >> time328.dat.1

cat ../vm_data.out | awk '{if(NR==331) print}' > time330.dat
cat time330.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time330.dat.1
awk -f tmp.awk time330.dat >> time330.dat.1

cat ../vm_data.out | awk '{if(NR==333) print}' > time332.dat
cat time332.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time332.dat.1
awk -f tmp.awk time332.dat >> time332.dat.1

cat ../vm_data.out | awk '{if(NR==335) print}' > time334.dat
cat time334.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time334.dat.1
awk -f tmp.awk time334.dat >> time334.dat.1

cat ../vm_data.out | awk '{if(NR==337) print}' > time336.dat
cat time336.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time336.dat.1
awk -f tmp.awk time336.dat >> time336.dat.1

cat ../vm_data.out | awk '{if(NR==339) print}' > time338.dat
cat time338.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time338.dat.1
awk -f tmp.awk time338.dat >> time338.dat.1

cat ../vm_data.out | awk '{if(NR==341) print}' > time340.dat
cat time340.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time340.dat.1
awk -f tmp.awk time340.dat >> time340.dat.1

cat ../vm_data.out | awk '{if(NR==343) print}' > time342.dat
cat time342.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time342.dat.1
awk -f tmp.awk time342.dat >> time342.dat.1

cat ../vm_data.out | awk '{if(NR==345) print}' > time344.dat
cat time344.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time344.dat.1
awk -f tmp.awk time344.dat >> time344.dat.1

cat ../vm_data.out | awk '{if(NR==347) print}' > time346.dat
cat time346.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time346.dat.1
awk -f tmp.awk time346.dat >> time346.dat.1

cat ../vm_data.out | awk '{if(NR==349) print}' > time348.dat
cat time348.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time348.dat.1
awk -f tmp.awk time348.dat >> time348.dat.1

cat ../vm_data.out | awk '{if(NR==351) print}' > time350.dat
cat time350.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time350.dat.1
awk -f tmp.awk time350.dat >> time350.dat.1

cat ../vm_data.out | awk '{if(NR==353) print}' > time352.dat
cat time352.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time352.dat.1
awk -f tmp.awk time352.dat >> time352.dat.1

cat ../vm_data.out | awk '{if(NR==355) print}' > time354.dat
cat time354.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time354.dat.1
awk -f tmp.awk time354.dat >> time354.dat.1

cat ../vm_data.out | awk '{if(NR==357) print}' > time356.dat
cat time356.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time356.dat.1
awk -f tmp.awk time356.dat >> time356.dat.1

cat ../vm_data.out | awk '{if(NR==359) print}' > time358.dat
cat time358.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time358.dat.1
awk -f tmp.awk time358.dat >> time358.dat.1

cat ../vm_data.out | awk '{if(NR==361) print}' > time360.dat
cat time360.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time360.dat.1
awk -f tmp.awk time360.dat >> time360.dat.1

cat ../vm_data.out | awk '{if(NR==363) print}' > time362.dat
cat time362.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time362.dat.1
awk -f tmp.awk time362.dat >> time362.dat.1

cat ../vm_data.out | awk '{if(NR==365) print}' > time364.dat
cat time364.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time364.dat.1
awk -f tmp.awk time364.dat >> time364.dat.1

cat ../vm_data.out | awk '{if(NR==367) print}' > time366.dat
cat time366.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time366.dat.1
awk -f tmp.awk time366.dat >> time366.dat.1

cat ../vm_data.out | awk '{if(NR==369) print}' > time368.dat
cat time368.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time368.dat.1
awk -f tmp.awk time368.dat >> time368.dat.1

cat ../vm_data.out | awk '{if(NR==371) print}' > time370.dat
cat time370.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time370.dat.1
awk -f tmp.awk time370.dat >> time370.dat.1

cat ../vm_data.out | awk '{if(NR==373) print}' > time372.dat
cat time372.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time372.dat.1
awk -f tmp.awk time372.dat >> time372.dat.1

cat ../vm_data.out | awk '{if(NR==375) print}' > time374.dat
cat time374.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time374.dat.1
awk -f tmp.awk time374.dat >> time374.dat.1

cat ../vm_data.out | awk '{if(NR==377) print}' > time376.dat
cat time376.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time376.dat.1
awk -f tmp.awk time376.dat >> time376.dat.1

cat ../vm_data.out | awk '{if(NR==379) print}' > time378.dat
cat time378.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time378.dat.1
awk -f tmp.awk time378.dat >> time378.dat.1

cat ../vm_data.out | awk '{if(NR==381) print}' > time380.dat
cat time380.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time380.dat.1
awk -f tmp.awk time380.dat >> time380.dat.1

cat ../vm_data.out | awk '{if(NR==383) print}' > time382.dat
cat time382.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time382.dat.1
awk -f tmp.awk time382.dat >> time382.dat.1

cat ../vm_data.out | awk '{if(NR==385) print}' > time384.dat
cat time384.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time384.dat.1
awk -f tmp.awk time384.dat >> time384.dat.1

cat ../vm_data.out | awk '{if(NR==387) print}' > time386.dat
cat time386.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time386.dat.1
awk -f tmp.awk time386.dat >> time386.dat.1

cat ../vm_data.out | awk '{if(NR==389) print}' > time388.dat
cat time388.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time388.dat.1
awk -f tmp.awk time388.dat >> time388.dat.1

cat ../vm_data.out | awk '{if(NR==391) print}' > time390.dat
cat time390.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time390.dat.1
awk -f tmp.awk time390.dat >> time390.dat.1

cat ../vm_data.out | awk '{if(NR==393) print}' > time392.dat
cat time392.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time392.dat.1
awk -f tmp.awk time392.dat >> time392.dat.1

cat ../vm_data.out | awk '{if(NR==395) print}' > time394.dat
cat time394.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time394.dat.1
awk -f tmp.awk time394.dat >> time394.dat.1

cat ../vm_data.out | awk '{if(NR==397) print}' > time396.dat
cat time396.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time396.dat.1
awk -f tmp.awk time396.dat >> time396.dat.1

cat ../vm_data.out | awk '{if(NR==399) print}' > time398.dat
cat time398.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time398.dat.1
awk -f tmp.awk time398.dat >> time398.dat.1

cat ../vm_data.out | awk '{if(NR==401) print}' > time400.dat
cat time400.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time400.dat.1
awk -f tmp.awk time400.dat >> time400.dat.1

cat ../vm_data.out | awk '{if(NR==403) print}' > time402.dat
cat time402.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time402.dat.1
awk -f tmp.awk time402.dat >> time402.dat.1

cat ../vm_data.out | awk '{if(NR==405) print}' > time404.dat
cat time404.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time404.dat.1
awk -f tmp.awk time404.dat >> time404.dat.1

cat ../vm_data.out | awk '{if(NR==407) print}' > time406.dat
cat time406.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time406.dat.1
awk -f tmp.awk time406.dat >> time406.dat.1

cat ../vm_data.out | awk '{if(NR==409) print}' > time408.dat
cat time408.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time408.dat.1
awk -f tmp.awk time408.dat >> time408.dat.1

cat ../vm_data.out | awk '{if(NR==411) print}' > time410.dat
cat time410.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time410.dat.1
awk -f tmp.awk time410.dat >> time410.dat.1

cat ../vm_data.out | awk '{if(NR==413) print}' > time412.dat
cat time412.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time412.dat.1
awk -f tmp.awk time412.dat >> time412.dat.1

cat ../vm_data.out | awk '{if(NR==415) print}' > time414.dat
cat time414.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time414.dat.1
awk -f tmp.awk time414.dat >> time414.dat.1

cat ../vm_data.out | awk '{if(NR==417) print}' > time416.dat
cat time416.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time416.dat.1
awk -f tmp.awk time416.dat >> time416.dat.1

cat ../vm_data.out | awk '{if(NR==419) print}' > time418.dat
cat time418.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time418.dat.1
awk -f tmp.awk time418.dat >> time418.dat.1

cat ../vm_data.out | awk '{if(NR==421) print}' > time420.dat
cat time420.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time420.dat.1
awk -f tmp.awk time420.dat >> time420.dat.1

cat ../vm_data.out | awk '{if(NR==423) print}' > time422.dat
cat time422.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time422.dat.1
awk -f tmp.awk time422.dat >> time422.dat.1

cat ../vm_data.out | awk '{if(NR==425) print}' > time424.dat
cat time424.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time424.dat.1
awk -f tmp.awk time424.dat >> time424.dat.1

cat ../vm_data.out | awk '{if(NR==427) print}' > time426.dat
cat time426.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time426.dat.1
awk -f tmp.awk time426.dat >> time426.dat.1

cat ../vm_data.out | awk '{if(NR==429) print}' > time428.dat
cat time428.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time428.dat.1
awk -f tmp.awk time428.dat >> time428.dat.1

cat ../vm_data.out | awk '{if(NR==431) print}' > time430.dat
cat time430.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time430.dat.1
awk -f tmp.awk time430.dat >> time430.dat.1

cat ../vm_data.out | awk '{if(NR==433) print}' > time432.dat
cat time432.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time432.dat.1
awk -f tmp.awk time432.dat >> time432.dat.1

cat ../vm_data.out | awk '{if(NR==435) print}' > time434.dat
cat time434.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time434.dat.1
awk -f tmp.awk time434.dat >> time434.dat.1

cat ../vm_data.out | awk '{if(NR==437) print}' > time436.dat
cat time436.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time436.dat.1
awk -f tmp.awk time436.dat >> time436.dat.1

cat ../vm_data.out | awk '{if(NR==439) print}' > time438.dat
cat time438.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time438.dat.1
awk -f tmp.awk time438.dat >> time438.dat.1

cat ../vm_data.out | awk '{if(NR==441) print}' > time440.dat
cat time440.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time440.dat.1
awk -f tmp.awk time440.dat >> time440.dat.1

cat ../vm_data.out | awk '{if(NR==443) print}' > time442.dat
cat time442.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time442.dat.1
awk -f tmp.awk time442.dat >> time442.dat.1

cat ../vm_data.out | awk '{if(NR==445) print}' > time444.dat
cat time444.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time444.dat.1
awk -f tmp.awk time444.dat >> time444.dat.1

cat ../vm_data.out | awk '{if(NR==447) print}' > time446.dat
cat time446.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time446.dat.1
awk -f tmp.awk time446.dat >> time446.dat.1

cat ../vm_data.out | awk '{if(NR==449) print}' > time448.dat
cat time448.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time448.dat.1
awk -f tmp.awk time448.dat >> time448.dat.1

cat ../vm_data.out | awk '{if(NR==451) print}' > time450.dat
cat time450.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time450.dat.1
awk -f tmp.awk time450.dat >> time450.dat.1

cat ../vm_data.out | awk '{if(NR==463) print}' > time460.dat
cat time460.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time460.dat.1
awk -f tmp.awk time460.dat >> time460.dat.1

cat ../vm_data.out | awk '{if(NR==481) print}' > time480.dat
cat time480.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time480.dat.1
awk -f tmp.awk time480.dat >> time480.dat.1

cat ../vm_data.out | awk '{if(NR==501) print}' > time500.dat
cat time500.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time500.dat.1
awk -f tmp.awk time500.dat >> time500.dat.1

cat ../vm_data.out | awk '{if(NR==521) print}' > time520.dat
cat time520.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time520.dat.1
awk -f tmp.awk time520.dat >> time520.dat.1

cat ../vm_data.out | awk '{if(NR==541) print}' > time540.dat
cat time540.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time540.dat.1
awk -f tmp.awk time540.dat >> time540.dat.1

cat ../vm_data.out | awk '{if(NR==561) print}' > time560.dat
cat time560.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time560.dat.1
awk -f tmp.awk time560.dat >> time560.dat.1

cat ../vm_data.out | awk '{if(NR==581) print}' > time580.dat
cat time580.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time580.dat.1
awk -f tmp.awk time580.dat >> time580.dat.1

cat ../vm_data.out | awk '{if(NR==601) print}' > time600.dat
cat time600.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time600.dat.1
awk -f tmp.awk time600.dat >> time600.dat.1

cat ../vm_data.out | awk '{if(NR==621) print}' > time620.dat
cat time620.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time620.dat.1
awk -f tmp.awk time620.dat >> time620.dat.1

cat ../vm_data.out | awk '{if(NR==641) print}' > time640.dat
cat time640.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time640.dat.1
awk -f tmp.awk time640.dat >> time640.dat.1

cat ../vm_data.out | awk '{if(NR==661) print}' > time660.dat
cat time660.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time660.dat.1
awk -f tmp.awk time660.dat >> time660.dat.1

cat ../vm_data.out | awk '{if(NR==681) print}' > time680.dat
cat time680.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time680.dat.1
awk -f tmp.awk time680.dat >> time680.dat.1

cat ../vm_data.out | awk '{if(NR==701) print}' > time700.dat
cat time700.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time700.dat.1
awk -f tmp.awk time700.dat >> time700.dat.1

cat ../vm_data.out | awk '{if(NR==721) print}' > time720.dat
cat time720.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time720.dat.1
awk -f tmp.awk time720.dat >> time720.dat.1

cat ../vm_data.out | awk '{if(NR==741) print}' > time740.dat
cat time740.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time740.dat.1
awk -f tmp.awk time740.dat >> time740.dat.1

cat ../vm_data.out | awk '{if(NR==761) print}' > time760.dat
cat time760.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time760.dat.1
awk -f tmp.awk time760.dat >> time760.dat.1

cat ../vm_data.out | awk '{if(NR==781) print}' > time780.dat
cat time780.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time780.dat.1
awk -f tmp.awk time780.dat >> time780.dat.1

cat ../vm_data.out | awk '{if(NR==801) print}' > time800.dat
cat time800.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time800.dat.1
awk -f tmp.awk time800.dat >> time800.dat.1

cat ../vm_data.out | awk '{if(NR==803) print}' > time802.dat
cat time802.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time802.dat.1
awk -f tmp.awk time802.dat >> time802.dat.1

cat ../vm_data.out | awk '{if(NR==805) print}' > time804.dat
cat time804.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time804.dat.1
awk -f tmp.awk time804.dat >> time804.dat.1

cat ../vm_data.out | awk '{if(NR==807) print}' > time806.dat
cat time806.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time806.dat.1
awk -f tmp.awk time806.dat >> time806.dat.1

cat ../vm_data.out | awk '{if(NR==809) print}' > time808.dat
cat time808.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time808.dat.1
awk -f tmp.awk time808.dat >> time808.dat.1

cat ../vm_data.out | awk '{if(NR==811) print}' > time810.dat
cat time810.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time810.dat.1
awk -f tmp.awk time810.dat >> time810.dat.1

cat ../vm_data.out | awk '{if(NR==813) print}' > time812.dat
cat time812.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time812.dat.1
awk -f tmp.awk time812.dat >> time812.dat.1

cat ../vm_data.out | awk '{if(NR==815) print}' > time814.dat
cat time814.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time814.dat.1
awk -f tmp.awk time814.dat >> time814.dat.1

cat ../vm_data.out | awk '{if(NR==817) print}' > time816.dat
cat time816.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time816.dat.1
awk -f tmp.awk time816.dat >> time816.dat.1

cat ../vm_data.out | awk '{if(NR==819) print}' > time818.dat
cat time818.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time818.dat.1
awk -f tmp.awk time818.dat >> time818.dat.1

cat ../vm_data.out | awk '{if(NR==821) print}' > time820.dat
cat time820.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time820.dat.1
awk -f tmp.awk time820.dat >> time820.dat.1

cat ../vm_data.out | awk '{if(NR==823) print}' > time822.dat
cat time822.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time822.dat.1
awk -f tmp.awk time822.dat >> time822.dat.1

cat ../vm_data.out | awk '{if(NR==825) print}' > time824.dat
cat time824.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time824.dat.1
awk -f tmp.awk time824.dat >> time824.dat.1

cat ../vm_data.out | awk '{if(NR==827) print}' > time826.dat
cat time826.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time826.dat.1
awk -f tmp.awk time826.dat >> time826.dat.1

cat ../vm_data.out | awk '{if(NR==829) print}' > time828.dat
cat time828.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time828.dat.1
awk -f tmp.awk time828.dat >> time828.dat.1

cat ../vm_data.out | awk '{if(NR==831) print}' > time830.dat
cat time830.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time830.dat.1
awk -f tmp.awk time830.dat >> time830.dat.1

cat ../vm_data.out | awk '{if(NR==833) print}' > time832.dat
cat time832.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time832.dat.1
awk -f tmp.awk time832.dat >> time832.dat.1

cat ../vm_data.out | awk '{if(NR==835) print}' > time834.dat
cat time834.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time834.dat.1
awk -f tmp.awk time834.dat >> time834.dat.1

cat ../vm_data.out | awk '{if(NR==837) print}' > time836.dat
cat time836.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time836.dat.1
awk -f tmp.awk time836.dat >> time836.dat.1

cat ../vm_data.out | awk '{if(NR==839) print}' > time838.dat
cat time838.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time838.dat.1
awk -f tmp.awk time838.dat >> time838.dat.1

cat ../vm_data.out | awk '{if(NR==841) print}' > time840.dat
cat time840.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time840.dat.1
awk -f tmp.awk time840.dat >> time840.dat.1

cat ../vm_data.out | awk '{if(NR==843) print}' > time842.dat
cat time842.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time842.dat.1
awk -f tmp.awk time842.dat >> time842.dat.1

cat ../vm_data.out | awk '{if(NR==845) print}' > time844.dat
cat time844.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time844.dat.1
awk -f tmp.awk time844.dat >> time844.dat.1

cat ../vm_data.out | awk '{if(NR==847) print}' > time846.dat
cat time846.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time846.dat.1
awk -f tmp.awk time846.dat >> time846.dat.1

cat ../vm_data.out | awk '{if(NR==849) print}' > time848.dat
cat time848.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time848.dat.1
awk -f tmp.awk time848.dat >> time848.dat.1

cat ../vm_data.out | awk '{if(NR==851) print}' > time850.dat
cat time850.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time850.dat.1
awk -f tmp.awk time850.dat >> time850.dat.1

cat ../vm_data.out | awk '{if(NR==861) print}' > time860.dat
cat time860.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time860.dat.1
awk -f tmp.awk time860.dat >> time860.dat.1

cat ../vm_data.out | awk '{if(NR==881) print}' > time880.dat
cat time880.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time880.dat.1
awk -f tmp.awk time880.dat >> time880.dat.1

cat ../vm_data.out | awk '{if(NR==901) print}' > time900.dat
cat time900.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time900.dat.1
awk -f tmp.awk time900.dat >> time900.dat.1

cat ../vm_data.out | awk '{if(NR==921) print}' > time920.dat
cat time920.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time920.dat.1
awk -f tmp.awk time920.dat >> time920.dat.1

cat ../vm_data.out | awk '{if(NR==941) print}' > time940.dat
cat time940.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time940.dat.1
awk -f tmp.awk time940.dat >> time940.dat.1

cat ../vm_data.out | awk '{if(NR==961) print}' > time960.dat
cat time960.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time960.dat.1
awk -f tmp.awk time960.dat >> time960.dat.1

cat ../vm_data.out | awk '{if(NR==981) print}' > time980.dat
cat time980.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time980.dat.1
awk -f tmp.awk time980.dat >> time980.dat.1

cat ../vm_data.out | awk '{if(NR==1001) print}' > time1000.dat
cat time1000.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1000.dat.1
awk -f tmp.awk time1000.dat >> time1000.dat.1

cat ../vm_data.out | awk '{if(NR==1021) print}' > time1020.dat
cat time1020.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1020.dat.1
awk -f tmp.awk time1020.dat >> time1020.dat.1

cat ../vm_data.out | awk '{if(NR==1041) print}' > time1040.dat
cat time1040.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1040.dat.1
awk -f tmp.awk time1040.dat >> time1040.dat.1

cat ../vm_data.out | awk '{if(NR==1061) print}' > time1060.dat
cat time1060.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1060.dat.1
awk -f tmp.awk time1060.dat >> time1060.dat.1

cat ../vm_data.out | awk '{if(NR==1081) print}' > time1080.dat
cat time1080.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1080.dat.1
awk -f tmp.awk time1080.dat >> time1080.dat.1

cat ../vm_data.out | awk '{if(NR==1101) print}' > time1100.dat
cat time1100.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1100.dat.1
awk -f tmp.awk time1100.dat >> time1100.dat.1

cat ../vm_data.out | awk '{if(NR==1121) print}' > time1120.dat
cat time1120.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1120.dat.1
awk -f tmp.awk time1120.dat >> time1120.dat.1

cat ../vm_data.out | awk '{if(NR==1141) print}' > time1140.dat
cat time1140.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1140.dat.1
awk -f tmp.awk time1140.dat >> time1140.dat.1

cat ../vm_data.out | awk '{if(NR==1161) print}' > time1160.dat
cat time1160.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1160.dat.1
awk -f tmp.awk time1160.dat >> time1160.dat.1

cat ../vm_data.out | awk '{if(NR==1181) print}' > time1180.dat
cat time1180.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1180.dat.1
awk -f tmp.awk time1180.dat >> time1180.dat.1

cat ../vm_data.out | awk '{if(NR==1201) print}' > time1200.dat
cat time1200.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1200.dat.1
awk -f tmp.awk time1200.dat >> time1200.dat.1

cat ../vm_data.out | awk '{if(NR==1203) print}' > time1202.dat
cat time1202.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1202.dat.1
awk -f tmp.awk time1202.dat >> time1202.dat.1

cat ../vm_data.out | awk '{if(NR==1205) print}' > time1204.dat
cat time1204.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1204.dat.1
awk -f tmp.awk time1204.dat >> time1204.dat.1

cat ../vm_data.out | awk '{if(NR==1207) print}' > time1206.dat
cat time1206.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1206.dat.1
awk -f tmp.awk time1206.dat >> time1206.dat.1

cat ../vm_data.out | awk '{if(NR==1209) print}' > time1208.dat
cat time1208.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1208.dat.1
awk -f tmp.awk time1208.dat >> time1208.dat.1

cat ../vm_data.out | awk '{if(NR==1211) print}' > time1210.dat
cat time1210.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1210.dat.1
awk -f tmp.awk time1210.dat >> time1210.dat.1

cat ../vm_data.out | awk '{if(NR==1213) print}' > time1212.dat
cat time1212.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1212.dat.1
awk -f tmp.awk time1212.dat >> time1212.dat.1

cat ../vm_data.out | awk '{if(NR==1215) print}' > time1214.dat
cat time1214.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1214.dat.1
awk -f tmp.awk time1214.dat >> time1214.dat.1

cat ../vm_data.out | awk '{if(NR==1217) print}' > time1216.dat
cat time1216.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1216.dat.1
awk -f tmp.awk time1216.dat >> time1216.dat.1

cat ../vm_data.out | awk '{if(NR==1219) print}' > time1218.dat
cat time1218.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1218.dat.1
awk -f tmp.awk time1218.dat >> time1218.dat.1

cat ../vm_data.out | awk '{if(NR==1221) print}' > time1220.dat
cat time1220.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1220.dat.1
awk -f tmp.awk time1220.dat >> time1220.dat.1

cat ../vm_data.out | awk '{if(NR==1223) print}' > time1222.dat
cat time1222.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1222.dat.1
awk -f tmp.awk time1222.dat >> time1222.dat.1

cat ../vm_data.out | awk '{if(NR==1225) print}' > time1224.dat
cat time1224.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1224.dat.1
awk -f tmp.awk time1224.dat >> time1224.dat.1

cat ../vm_data.out | awk '{if(NR==1227) print}' > time1226.dat
cat time1226.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1226.dat.1
awk -f tmp.awk time1226.dat >> time1226.dat.1

cat ../vm_data.out | awk '{if(NR==1229) print}' > time1228.dat
cat time1228.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1228.dat.1
awk -f tmp.awk time1228.dat >> time1228.dat.1

cat ../vm_data.out | awk '{if(NR==1231) print}' > time1230.dat
cat time1230.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1230.dat.1
awk -f tmp.awk time1230.dat >> time1230.dat.1

cat ../vm_data.out | awk '{if(NR==1233) print}' > time1232.dat
cat time1232.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1232.dat.1
awk -f tmp.awk time1232.dat >> time1232.dat.1

cat ../vm_data.out | awk '{if(NR==1235) print}' > time1234.dat
cat time1234.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1234.dat.1
awk -f tmp.awk time1234.dat >> time1234.dat.1

cat ../vm_data.out | awk '{if(NR==1237) print}' > time1236.dat
cat time1236.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1236.dat.1
awk -f tmp.awk time1236.dat >> time1236.dat.1

cat ../vm_data.out | awk '{if(NR==1239) print}' > time1238.dat
cat time1238.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1238.dat.1
awk -f tmp.awk time1238.dat >> time1238.dat.1

cat ../vm_data.out | awk '{if(NR==1241) print}' > time1240.dat
cat time1240.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1240.dat.1
awk -f tmp.awk time1240.dat >> time1240.dat.1

cat ../vm_data.out | awk '{if(NR==1243) print}' > time1242.dat
cat time1242.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1242.dat.1
awk -f tmp.awk time1242.dat >> time1242.dat.1

cat ../vm_data.out | awk '{if(NR==1245) print}' > time1244.dat
cat time1244.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1244.dat.1
awk -f tmp.awk time1244.dat >> time1244.dat.1

cat ../vm_data.out | awk '{if(NR==1247) print}' > time1246.dat
cat time1246.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1246.dat.1
awk -f tmp.awk time1246.dat >> time1246.dat.1

cat ../vm_data.out | awk '{if(NR==1249) print}' > time1248.dat
cat time1248.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1248.dat.1
awk -f tmp.awk time1248.dat >> time1248.dat.1

cat ../vm_data.out | awk '{if(NR==1251) print}' > time1250.dat
cat time1250.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1250.dat.1
awk -f tmp.awk time1250.dat >> time1250.dat.1

cat ../vm_data.out | awk '{if(NR==1261) print}' > time1260.dat
cat time1260.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1260.dat.1
awk -f tmp.awk time1260.dat >> time1260.dat.1

cat ../vm_data.out | awk '{if(NR==1281) print}' > time1280.dat
cat time1280.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1280.dat.1
awk -f tmp.awk time1280.dat >> time1280.dat.1

cat ../vm_data.out | awk '{if(NR==1301) print}' > time1300.dat
cat time1300.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1300.dat.1
awk -f tmp.awk time1300.dat >> time1300.dat.1

cat ../vm_data.out | awk '{if(NR==1321) print}' > time1320.dat
cat time1320.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1320.dat.1
awk -f tmp.awk time1320.dat >> time1320.dat.1

cat ../vm_data.out | awk '{if(NR==1341) print}' > time1340.dat
cat time1340.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1340.dat.1
awk -f tmp.awk time1340.dat >> time1340.dat.1

cat ../vm_data.out | awk '{if(NR==1361) print}' > time1360.dat
cat time1360.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1360.dat.1
awk -f tmp.awk time1360.dat >> time1360.dat.1

cat ../vm_data.out | awk '{if(NR==1381) print}' > time1380.dat
cat time1380.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1380.dat.1
awk -f tmp.awk time1380.dat >> time1380.dat.1

cat ../vm_data.out | awk '{if(NR==1401) print}' > time1400.dat
cat time1400.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1400.dat.1
awk -f tmp.awk time1400.dat >> time1400.dat.1

cat ../vm_data.out | awk '{if(NR==1421) print}' > time1420.dat
cat time1420.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1420.dat.1
awk -f tmp.awk time1420.dat >> time1420.dat.1

cat ../vm_data.out | awk '{if(NR==1441) print}' > time1440.dat
cat time1440.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1440.dat.1
awk -f tmp.awk time1440.dat >> time1440.dat.1

cat ../vm_data.out | awk '{if(NR==1461) print}' > time1460.dat
cat time1460.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1460.dat.1
awk -f tmp.awk time1460.dat >> time1460.dat.1

cat ../vm_data.out | awk '{if(NR==1481) print}' > time1480.dat
cat time1480.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1480.dat.1
awk -f tmp.awk time1480.dat >> time1480.dat.1

cat ../vm_data.out | awk '{if(NR==1501) print}' > time1500.dat
cat time1500.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1500.dat.1
awk -f tmp.awk time1500.dat >> time1500.dat.1

cat ../vm_data.out | awk '{if(NR==1521) print}' > time1520.dat
cat time1520.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1520.dat.1
awk -f tmp.awk time1520.dat >> time1520.dat.1

cat ../vm_data.out | awk '{if(NR==1541) print}' > time1540.dat
cat time1540.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1540.dat.1
awk -f tmp.awk time1540.dat >> time1540.dat.1

cat ../vm_data.out | awk '{if(NR==1561) print}' > time1560.dat
cat time1560.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1560.dat.1
awk -f tmp.awk time1560.dat >> time1560.dat.1

cat ../vm_data.out | awk '{if(NR==1581) print}' > time1580.dat
cat time1580.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1580.dat.1
awk -f tmp.awk time1580.dat >> time1580.dat.1

cat ../vm_data.out | awk '{if(NR==1601) print}' > time1600.dat
cat time1600.dat | awk '{print "Labels 250,30 t="$1"(ms)"}' > time1600.dat.1
awk -f tmp.awk time1600.dat >> time1600.dat.1

unix2dos *.dat.1

