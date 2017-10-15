import cffi

ffi = cffi.FFI()
ffi.cdef('''
void unimess_init();
void * unimess_config_chain_generate(unsigned int size);
unsigned char * unimess_config_chain_dump(void *cc, unsigned int *len_out);
void * unimess_config_chain_load(unsigned char *data, unsigned int len);
void unimess_config_chain_destroy(void *cc);
void * unimess_config_chain_get_protocol_chain(void *cc);
unsigned char * unimess_protocol_chain_encode_packet(void *cc, unsigned int *len_out, unsigned char *pkt, unsigned int len);
unsigned char * unimess_protocol_chain_decode_packet(void *cc, unsigned int *len_out, unsigned char *pkt, unsigned int len);
void unimess_protocol_chain_destroy(void *pc);
void unimess_binary_buffer_destroy(unsigned char *buf);
''')

lib = ffi.dlopen("libunimess.so")
lib.unimess_init()
