LIBRARY := SUHH2HOTVRStudies
LHAPDFINC=$(shell scram tool tag lhapdf INCLUDE)
LHAPDFLIB=$(shell scram tool tag LHAPDF LIBDIR)
FJINC=/nfs/dust/cms/user/albrecha/uhh2_102X/fastjet-install/include
FJLIB=/nfs/dust/cms/user/albrecha/uhh2_102X/fastjet-install/lib
USERCXXFLAGS := -I${LHAPDFINC} -I${FJINC}
USERLDFLAGS := -lSUHH2core -lSUHH2common -lGenVector -lSUHH2JetMETObjects -lSUHH2HOTVR -L${LHAPDFLIB} -lLHAPDF -lfastjet -lfastjettools -L${FJLIB} -lHOTVR -lRecursiveTools -lVariableR -lNsubjettiness
# enable par creation; this is necessary for all packages containing AnalysisModules
# to be loaded from by AnalysisModuleRunner.
PAR := 1
include ../Makefile.common
