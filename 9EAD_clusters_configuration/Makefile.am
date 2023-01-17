#INCLUDES = syspara.h

bin_PROGRAMS = 2D_Kurata05
2D_Kurata05_CFLAGS = -O2 -Wall -axCORE-AVX2 -mkl -parallel -Winline -inline-level=2 -ip -qopt-mem-layout-trans=3 -pg -qopt-report-phase=all

2D_Kurata05_LDADD = 

2D_Kurata05_SOURCES = ./src/syspara.h ./src/kurata05.c ./src/exptab.c ./src/mem.c ./src/vars_para.c ./src/system.c

