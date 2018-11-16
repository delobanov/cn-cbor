#include <stdlib.h>
#include <string.h>

#include "cn-cbor/cn-cbor.h"
#include "cbor.h"

bool cn_cbor_mapset_int(cn_cbor* cb_map,
                        int64_t key, cn_cbor* cb_value
                        CBOR_CONTEXT,
                        cn_cbor_errback *errp) {
    cn_cbor* cb_key;

    //Make sure input is a map. Otherwise
    if(!cb_map || !cb_value || cb_map->type != CN_CBOR_MAP)
    {
        if (errp) {errp->err = CN_CBOR_ERR_INVALID_PARAMETER;}
        return false;
    }

    cb_key = cn_cbor_mapfind_int(cb_map, key);

    if (!cb_key || !cb_key->next) {
        return cn_cbor_mapput_int(cb_map, key, cb_value, errp);
    }

    cb_value->next = cb_key->next->next;
    cb_value->parent = cb_key->next->parent;

    if (cb_key->parent->last_child == cb_key->next){
        cb_key->parent->last_child = cb_value;
    }
    cb_key->next->parent = NULL;
    cn_cbor_free(cb_key->next);

    cb_key->next = cb_value;

    return true;
}

bool cn_cbor_mapset_string(cn_cbor* cb_map,
                           const char* key, cn_cbor* cb_value
                           CBOR_CONTEXT,
                           cn_cbor_errback *errp) {
    cn_cbor* cb_key;

    //Make sure input is a map. Otherwise
    if(!cb_map || !cb_value || cb_map->type != CN_CBOR_MAP)
    {
        if (errp) {errp->err = CN_CBOR_ERR_INVALID_PARAMETER;}
        return false;
    }

    cb_key = cn_cbor_mapfind_string(cb_map, key);

    if (!cb_key || !cb_key->next) {
        return cn_cbor_mapput_string(cb_map, key, cb_value, errp);
    }

    cb_value->next = cb_key->next->next;
    cb_value->parent = cb_key->next->parent;

    if (cb_key->parent->last_child == cb_key->next){
        cb_key->parent->last_child = cb_value;
    }
    cb_key->next->parent = NULL;
    cn_cbor_free(cb_key->next);

    cb_key->next = cb_value;

    return true;
}
