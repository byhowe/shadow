#ifndef NODE_H_
#define NODE_H_

#include <stddef.h>
#include <stdint.h>
#include <sodium/crypto_generichash.h>

#define SH_NODE_ID_SIZE crypto_generichash_BYTES

typedef struct sh_node_t {
    const uint8_t id[SH_NODE_ID_SIZE];
    const char * localpath;
} sh_node_t;

sh_node_t* sh_node_create_from_filepath(const char *filepath);

#endif // NODE_H_
