LIBRARY := SUHH2HOTVRStudies
LHAPDFINC=$(shell scram tool tag lhapdf INCLUDE)
LHAPDFLIB=$(shell scram tool tag LHAPDF LIBDIR)
TFLOWLIB= $(shell scram tool tag tensorflow LIBDIR)
TFLOWINC= $(shell scram tool tag tensorflow INCLUDE)
PBUFLIB= $(shell scram tool tag protobuf LIBDIR)
PBUFINC= $(shell scram tool tag protobuf INCLUDE)
EigenINC= $(shell scram tool tag Eigen INCLUDE)
FJINC=$(shell scram tool tag FASTJET INCLUDE)
FJLIB=$(shell scram tool tag FASTJET LIBDIR)
USERCXXFLAGS := -I${LHAPDFINC} -I/cvmfs/cms.cern.ch/${SCRAM_ARCH}/cms/cmssw/${CMSSW_VERSION}/src -I${TFLOWINC} -I${PBUFINC} -I${EigenINC} -I${FJINC}
USERLDFLAGS := -lSUHH2core  -lSUHH2common -lSUHH2HOTVR -lGenVector -lSUHH2JetMETObjects -L${LHAPDFLIB} -lLHAPDF -L/cvmfs/cms.cern.ch/${SCRAM_ARCH}/cms/cmssw/${CMSSW_VERSION}/lib/${SCRAM_ARCH} -lPhysicsToolsTensorFlow -L${TFLOWLIB} -ltensorflow_framework -L${PBUFLIB} -lfastjet -lfastjettools -L${FJLIB} -lHOTVR -lRecursiveTools -lVariableR -lNsubjettiness
# enable par creation; this is necessary for all packages containing AnalysisModules
# to be loaded from by AnalysisModuleRunner.
PAR := 1
include ../Makefile.common
