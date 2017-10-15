FLAGS := -O3 -fPIC
CXXFLAGS := $(FLAGS) -std=c++14
OBJS := unimess.o protocol_config.o chain.o

all: core protocols api

core: $(OBJS)
	$(CXX) $(FLAGS) -shared -o ../target/libunimess.so $(OBJS)

protocols:
	make -C protocols

api:
	make -C api

.PHONY: protocols api
