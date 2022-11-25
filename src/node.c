#include "node.h"

#include <sodium/crypto_generichash.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

sh_node_t* node_create_from_filepath(const char *filepath) {
    struct stat st;
    struct tm *tm;
    crypto_generichash_state state;
    sh_node_t* node = (sh_node_t*)malloc(sizeof(sh_node_t));
    node->localpath = malloc(strlen(filepath) + 1);
    strcpy((char*)node->localpath, filepath);

    if (stat(filepath, &st) == -1)
        return NULL;

    tm = localtime(&st.st_mtime);
    int64_t fsize = st.st_size;

    crypto_generichash_init(&state, NULL, 0, SH_NODE_ID_SIZE);
    crypto_generichash_update(&state, (const unsigned char*)filepath, strlen(filepath));
    crypto_generichash_update(&state, (const unsigned char*)&fsize, sizeof(uint64_t));
    crypto_generichash_update(&state, (const unsigned char*)tm, sizeof(struct tm));
    crypto_generichash_final(&state, (unsigned char*)node->id, SH_NODE_ID_SIZE);

    return node;
}
