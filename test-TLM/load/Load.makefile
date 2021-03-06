# Makefile generated by OpenModelica

# Simulations use -O3 by default
CC=/usr/bin/clang
CXX=/usr/bin/clang++
LINK=/usr/bin/clang -single_module -dynamiclib -flat_namespace
EXEEXT=
DLLEXT=.dylib
CFLAGS_BASED_ON_INIT_FILE=
DEBUG_FLAGS=
CFLAGS=$(CFLAGS_BASED_ON_INIT_FILE) $(DEBUG_FLAGS)  -O0 -march=native ${MODELICAUSERCFLAGS}    
CPPFLAGS="-I/Users/spinhalf/Documents/Modelica/OMTLMSimulator/bin/OpenModelica/Resources/Include" -I"/opt/openmodelica/include/omc/c" -I. -DOPENMODELICA_XML_FROM_FILE_AT_RUNTIME -DOMC_MODEL_PREFIX=Load -DOMC_NUM_MIXED_SYSTEMS=0 -DOMC_NUM_LINEAR_SYSTEMS=0 -DOMC_NUM_NONLINEAR_SYSTEMS=0 -DOMC_NDELAY_EXPRESSIONS=0 -DOMC_NVAR_STRING=0
LDFLAGS=-L"/Users/spinhalf/Documents/Modelica/test/load" -L"/opt/openmodelica/lib/x86_64-darwin15.4.0/omc" -L"/opt/openmodelica/lib" -Wl,-rpath,"/opt/openmodelica/lib/x86_64-darwin15.4.0/omc" -Wl,-rpath,"/opt/openmodelica/lib"   -L/usr/lib64 -lstdc++ -L/opt/openmodelica/lib -Wl,-headerpad_max_install_names -arch x86_64 -lSimulationRuntimeC -llapack -lblas -lm -lomcgc 
MAINFILE=Load.c
MAINOBJ=Load.o
CFILES=Load_functions.c Load_records.c \
Load_01exo.c Load_02nls.c Load_03lsy.c Load_04set.c Load_05evt.c Load_06inz.c Load_07dly.c \
Load_08bnd.c Load_09alg.c Load_10asr.c Load_11mix.c Load_12jac.c Load_13opt.c Load_14lnz.c \
Load_15syn.c Load_16dae.c Load_17inl.c 

OFILES=$(CFILES:.c=.o)
GENERATEDFILES=$(MAINFILE) Load.makefile Load_literals.h Load_functions.h $(CFILES)

.PHONY: omc_main_target clean bundle

# This is to make sure that Load_*.c are always compiled.
.PHONY: $(CFILES)

omc_main_target: $(MAINOBJ) Load_functions.h Load_literals.h $(OFILES)
	$(CC) -I. -o Load$(EXEEXT) $(MAINOBJ) $(OFILES) $(CPPFLAGS) -L"/Users/spinhalf/Documents/Modelica/test/load"  "-L/opt/openmodelica/lib/x86_64-darwin15.4.0/omc" "-L/opt/openmodelica/lib/" "-L/Users/spinhalf/.openmodelica/binaries/TLM" "-L/Users/spinhalf/Documents/Modelica/OMTLMSimulator/bin/OpenModelica/Resources/Library/x86_64-darwin" "-L/Users/spinhalf/Documents/Modelica/OMTLMSimulator/bin/OpenModelica/Resources/Library/darwin64" "-L/Users/spinhalf/Documents/Modelica/OMTLMSimulator/bin/OpenModelica/Resources/Library" -ltlmopenmodelica $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
clean:
	@rm -f Load_records.o $(MAINOBJ)

bundle:
	@tar -cvf Load_Files.tar $(GENERATEDFILES)