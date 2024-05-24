#INCLUDES = syspara.h

bin_PROGRAMS = 2D_Kurata05
#for OCTOPUS
#2D_Kurata05_CFLAGS = -O3 -xCORE-AVX2 -qopt-zmm-usage=high -qmkl -parallel -qopenmp -Winline -inline-level=2 -ipo -qopt-mem-layout-trans=3 -pg -qopt-report-phase=all -qopt-report=5 -qopt-report-annotate
#for newest intel oneAPI
2D_Kurata05_CFLAGS = -fcommon -fiopenmp -fopenmp-targets=spir64 -Wall -O3 -xCORE-AVX2 -qopt-zmm-usage=high -qmkl=parallel -Winline -inline-level=2 -ipo -pg -qopt-report-stdout -flto -qopt-report-annotate

#2D_Kurata05_LDADD = -L/opt/intel/oneapi/mkl/lib/intel64 -liomp5 -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core
2D_Kurata05_LDADD = 

2D_Kurata05_SOURCES = ./src/syspara.h ./src/kurata05.c ./src/exptab.c ./src/mem.c ./src/vars_para.c ./src/system.c

