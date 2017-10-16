FLAGS := -O3 -fPIC
CXXFLAGS := $(FLAGS) -std=c++14 -flto
OBJS := unimess.o protocol_config.o chain.o
EXT_OBJS := protocols/*.o api/*.o

all: core protocols api
	$(CXX) $(FLAGS) -shared -o ../target/libunimess.so $(OBJS) $(EXT_OBJS)

core: $(OBJS)

protocols:
	make -C protocols

api:
	make -C api

.PHONY: protocols api
