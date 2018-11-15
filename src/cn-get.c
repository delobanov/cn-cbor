#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "cn-cbor/cn-cbor.h"

cn_cbor* cn_cbor_mapget_int(const cn_cbor* cb_map, int key) {
  cn_cbor* cp;

  if(!cb_map || cb_map->type != CN_CBOR_MAP)
  {
    return false;
  }

  cp = cn_cbor_mapfind_int(cb_map, key);
  if (cp && cp->next){
    return cp->next;
  } else {
    return NULL;
  }
}

cn_cbor* cn_cbor_mapget_string(const cn_cbor* cb_map, const char* key) {
  cn_cbor *cp;

  if(!cb_map || !key || cb_map->type != CN_CBOR_MAP)
  {
    return false;
  }

  cp = cn_cbor_mapfind_string(cb_map, key);
  if (cp && cp->next){
    return cp->next;
  } else {
    return NULL;
  }
}

cn_cbor* cn_cbor_index(const cn_cbor* cb, unsigned int idx) {
  cn_cbor *cp;
  unsigned int i = 0;

  if(!cb)
  {
    return NULL;
  }

  for (cp = cb->first_child; cp; cp = cp->next) {
    if (i == idx) {
      return cp;
    }
    i++;
  }
  return NULL;
}
