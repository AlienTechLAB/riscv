CC = g++

CFLAGS = -std=c++14 -Wall -O0 -g -Iinc -I../riscvm/inc\
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


#src/decode_tests/c.addi4spn_tests.cpp\
#src/decode_tests/c.fld_tests.cpp\
#src/decode_tests/c.lq_tests.cpp\
#src/decode_tests/c.lw_tests.cpp\
#src/decode_tests/c.flw_tests.cpp\
#src/decode_tests/decode_tests.cpp\

UT_SRC = src/c.srli_tests.cpp\
src/decode_tests.cpp\
src/get_set_imm_tests.cpp\
src/main.cpp\
src/memory_tests.cpp\
rv64gc.cpp


RV_SRC = ../riscvm/src/memory.cpp\
../riscvm/src/general.cpp\
../riscvm/src/decoder.cpp

UT_OBJS = $(subst src,obj, $(subst .cpp,.o, $(UT_SRC)))
RM_OBJS = $(subst ../riscvm/src,obj/riscvm, $(subst .cpp,.o, $(RV_SRC)))

all: tests
	bin/tests

tests: $(UT_OBJS) $(RM_OBJS)
	$(CC) $(CFLAGS) $(UT_OBJS) $(RM_OBJS) -o bin/$@

obj/%.o: src/%.cpp mkdirs
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

obj/riscvm/%.o: ../riscvm/src/%.cpp mkdirs
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

mkdirs:
	mkdir -p bin obj

clean:
	$(RM) -rf bin
	$(RM) -rf obj

.PHONY: clean mkdirs