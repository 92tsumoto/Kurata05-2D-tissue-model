#INCLUDES = syspara.h

bin_PROGRAMS = 2D_Kurata05
2D_Kurata05_CFLAGS = -O3 -xCORE-AVX512 -qopt-zmm-usage=high -parallel -Winline -inline-level=2 -ip -qopt-mem-layout-trans=3 -pg -qopt-report-phase=all -qopt-report-annotate

#2D_Kurata05_LDADD = 

2D_Kurata05_SOURCES = ./src/syspara.h ./src/kurata05.c ./src/exptab.c ./src/mem.c ./src/vars_para.c ./src/cluster4_setting.c ./src/cluster9_setting.c ./src/cluster16_setting.c ./src/cluster25_setting.c ./src/cluster2_setting.c ./src/system.c

