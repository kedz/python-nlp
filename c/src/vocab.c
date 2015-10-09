#include "vocab.h"

NL_vocab *NL_new_vocab(NL_v_memmgr *mgr) {
    NL_vocab *v = NL_allocate_mem_size(mgr, sizeof(NL_vocab));
    if (v != NULL) {
        v->_table = calloc(sizeof(NL_string *), NL_PRIMES[0]);
        v->_ids = malloc(sizeof(size_t) * NL_PRIMES[0]);
        v->size = 0;
        v->_table_prime_index = 0;
        v->flags = 0;
    }
    return v;
}

void NL_deallocate_vocab(NL_v_memmgr *mgr, NL_vocab **v) {

    for (size_t i=0; i < NL_PRIMES[(*v)->_table_prime_index]; i++) {
        if ((*v)->_table[i] != NULL && (*v)->_table[i]->flags & NL_OWN_DATA) {
            //fwrite((*v)->_table[i]->bytes, 1, (*v)->_table[i]->size, stdout);
            //printf(" %lu dealloc\n", (*v)->_ids[i]);
            NL_deallocate_v_mem(mgr, (void **) &(*v)->_table[i]);    
        }
    }

    free((*v)->_table);
    free((*v)->_ids);
    NL_deallocate_v_mem(mgr, (void **) v);

}


int _NL_resize_vocab(NL_v_memmgr *mgr, NL_vocab *vocab) {
    size_t new_prime_index = vocab->_table_prime_index + 1;
    if (new_prime_index >= NL_NUM_PRIMES) {
        return -1;
    } else {
        
        NL_string **new_table = calloc(
            sizeof(NL_string *), NL_PRIMES[new_prime_index]);
        size_t *new_ids = calloc(sizeof(size_t), NL_PRIMES[new_prime_index]);

        if (new_table == NULL || new_ids == NULL) {
            return -1;
        } else {
            size_t tries;
            size_t index;
            size_t total_reinserts = 0;
            NL_hash *hash = NL_allocate_mem_size(mgr, sizeof(uint32_t) * 4);
            NL_string *string;
            for (size_t i =0; i < NL_PRIMES[vocab->_table_prime_index]; i++) {
                if (vocab->_table[i] == NULL) 
                    continue;
                tries = 0;
                string = vocab->_table[i];
                MurmurHash3_x64_128(string->bytes, string->size, 
                        NL_HASH_SEED, hash);
                index = (*(size_t *) hash) % 
                    NL_PRIMES[new_prime_index];
                while (tries < NL_PRIMES[new_prime_index]) {
                    if (new_table[index] == NULL) {
                        new_table[index] = string;
                        new_ids[index] = vocab->_ids[i];
                        total_reinserts++;
                        break; 
                    } else {
                        index++;
                        tries++;
                        if (index >= NL_PRIMES[new_prime_index]) {
                            index = 0;
                        }
                    }
                }
            }
            
            free(vocab->_table);
            free(vocab->_ids);
            NL_deallocate_v_mem(mgr, (void **) &hash);
            vocab->_table = new_table;
            vocab->_ids = new_ids;
            vocab->_table_prime_index++;
            
            return 1;
        }
    }    
    

}

int NL_get_string_id(NL_v_memmgr *mgr, NL_vocab *vocab, 
        NL_string* string, size_t *id) {

    long double load = vocab->size / (long double) 
                       NL_PRIMES[vocab->_table_prime_index];
    if (load > .66) {
        if (_NL_resize_vocab(mgr, vocab) == -1) {
            printf("Warning: COULDN'T ALLOCATE MORE MEMORY\n");
            return NL_VOCAB_MEM_ERROR;
        }
    }

    NL_hash *hash;
    NL_HASH(string->bytes, string->size, mgr, hash)
    size_t tries, index;
    index = (*(size_t *) hash) % NL_PRIMES[vocab->_table_prime_index];
    tries = 0;
    NL_deallocate_v_mem(mgr, (void **) &hash);
    
    unsigned char *found_bytes;
    size_t found_size;



    while (tries < NL_PRIMES[vocab->_table_prime_index]) {
        if (vocab->_table[index] == NULL) {
            vocab->_table[index] = string;
            vocab->_ids[index] = vocab->size;
            vocab->size++;
            *id = vocab->_ids[index];
          //      printf("insert %lu found\n", vocab->_ids[index]);
            return NL_VOCAB_INSERT;
            
        } else {
            found_bytes = vocab->_table[index]->bytes; 
            found_size = vocab->_table[index]->size;
            if (found_size == string->size && 
                    memcmp(found_bytes, string->bytes, found_size) == 0) {
            //    printf("%lu found\n", vocab->_ids[index]);
                *id = vocab->_ids[index];
                return NL_VOCAB_FOUND;
            }
            index++;
            tries++;
            if (index >= NL_PRIMES[vocab->_table_prime_index]) {
                index = 0;
            }
        }
    }
    
   return NL_VOCAB_MEM_ERROR;

}


