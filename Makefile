CC = g++

CFLAGS = -std=c++14 -Wall -I../\
-pedantic\
-Wcast-align\
-Wdouble-promotion\
-Wduplicated-cond\
-Wnon-virtual-dtor\
-Woverloaded-virtual\
-Wuseless-cast\
-Wshadow\
-Wzero-as-null-pointer-constant\
-Walloc-zero\
-Wdangling-else\
-Wduplicated-branches\
-Wempty-body\
-Wimplicit-fallthrough\
-Wmissing-declarations\
-Wmissing-field-initializers\
-Wmissing-include-dirs\
-Wsuggest-override\
-Wtype-limits\
-Wnull-dereference\
-Wcast-qual\
-Wfloat-equal\
-Wno-virtual-move-assign\
-Wshift-negative-value\
-Wdisabled-optimization\
-Wunused

ifeq ($(DEBUG), 1)
	CFLAGS += -O0 -g
else
	CFLAGS += -O2 -flto
endif


all: riscvm unittests
	unittests/bin/unittests


RVM_SRCPATH = riscvm/src/
RVM_OBJPATH = riscvm/obj/
RVM_BINPATH = riscvm/bin/
RVM_INC = riscvm/inc/
RVM_SRC = main.cpp\
memory.cpp\
RiscvCpu.cpp\
general.cpp
RVM_SRCS = $(addprefix $(RVM_SRCPATH), $(RVM_SRC))
RVM_OBJS = $(addprefix $(RVM_OBJPATH), $(subst .cpp,.o, $(RVM_SRC)))

riscvm: $(RVM_OBJS) vmmkdirs
	$(CC) $(CFLAGS) $(RVM_OBJS) -o $(RVM_BINPATH)$@
$(RVM_OBJPATH)%.o: $(RVM_SRCPATH)%.cpp vmmkdirs
	$(CC) $(CFLAGS) -I$(RVM_INC) -c $< -o $@
vmmkdirs:
	mkdir -p $(RVM_BINPATH) $(RVM_OBJPATH)



UTSRCPATH = unittests/src/
UTOBJPATH = unittests/obj/
UTBINPATH = unittests/bin/
UTSRCS = unittests/src/main.cpp\
riscvm/src/memory.cpp\
riscvm/src/general.cpp
UTOBJS = $(subst src,obj, $(subst .cpp,.o, $(UTSRCS)))

unittests: $(UTOBJS) utmkdirs
	$(CC) $(CFLAGS) $(UTOBJS) -o $(UTBINPATH)$@
$(UTOBJPATH)%.o: $(UTSRCPATH)%.cpp utmkdirs
	$(CC) $(CFLAGS) -I$(RVM_INC) -c $< -o $@
utmkdirs:
	mkdir -p $(UTBINPATH) $(UTOBJPATH)



clean:
	$(RM) -rf $(RVM_BINPATH)
	$(RM) -rf $(RVM_OBJPATH)
	$(RM) -rf $(UTBINPATH)
	$(RM) -rf $(UTOBJPATH)

.PHONY: clean utmkdirs vmmkdirs