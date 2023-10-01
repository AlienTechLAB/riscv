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
RVM_SRC = Main.cpp\
Memory.cpp\
RiscvCpu.cpp\
General.cpp
RVM_SRCS = $(addprefix $(RVM_SRCPATH), $(RVM_SRC))
RVM_OBJS = $(addprefix $(RVM_OBJPATH), $(subst .cpp,.o, $(RVM_SRC)))

riscvm: $(RVM_OBJS) vmmkdirs
	$(CC) $(CFLAGS) $(RVM_OBJS) -o $(RVM_BINPATH)$@
$(RVM_OBJPATH)%.o: $(RVM_SRCPATH)%.cpp vmmkdirs
	$(CC) $(CFLAGS) -I$(RVM_INC) -c $< -o $@
vmmkdirs:
	mkdir -p $(RVM_BINPATH) $(RVM_OBJPATH)



UT_SRCPATH = unittests/src/
UT_OBJPATH = unittests/obj/
UT_BINPATH = unittests/bin/
UT_INC = unittests/inc/
UT_SRC = unittests/src/Main.cpp\
unittests/src/MemoryTests.cpp\
riscvm/src/Memory.cpp\
riscvm/src/General.cpp
UT_OBJS = $(subst src,obj, $(subst .cpp,.o, $(UT_SRC)))

unittests: $(UT_OBJS) utmkdirs
	$(CC) $(CFLAGS) $(UT_OBJS) -o $(UT_BINPATH)$@
$(UT_OBJPATH)%.o: $(UT_SRCPATH)%.cpp utmkdirs
	$(CC) $(CFLAGS) -I$(RVM_INC) -I$(UT_INC) -c $< -o $@
utmkdirs:
	mkdir -p $(UT_BINPATH) $(UT_OBJPATH)



clean:
	$(RM) -rf $(RVM_BINPATH)
	$(RM) -rf $(RVM_OBJPATH)
	$(RM) -rf $(UT_BINPATH)
	$(RM) -rf $(UT_OBJPATH)

.PHONY: clean utmkdirs vmmkdirs