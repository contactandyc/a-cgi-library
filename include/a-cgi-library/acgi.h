/*
Copyright 2019 Andy Curtis

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef _acgi_H
#define _acgi_H

#include "a-memory-library/aml_pool.h"
#include "a-json-library/ajson.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
  cgi is commonly used within URLs.  This object is meant to aid in parsing
  URLs and finding the values of cgi arguments.
*/

struct acgi_s;
typedef struct acgi_s acgi_t;

/* initialize a cgi object using a pool (no destroy method exists) */
acgi_t *acgi_init(aml_pool_t *pool, const char *q);

/* initialize json object from cgi */
ajson_t *acgi_to_json(aml_pool_t *pool, const char *q);

/* get the original cgi query passed to init */
const char *acgi_query(acgi_t *h);

/* get a NULL terminated array of decoded values from key */
char **acgi_strs(acgi_t *h, const char *key);

/* get the first decoded string from key as a string */
const char *acgi_str(acgi_t *h, const char *key, const char *default_value);

/* get the first decoded string from key as a bool */
bool acgi_bool(acgi_t *h, const char *key, bool default_value);

/* get the first decoded string from key as an int */
int acgi_int(acgi_t *h, const char *key, int default_value);

/* get the first decoded string from key as an long */
long acgi_long(acgi_t *h, const char *key, long default_value);

/* get the first decoded string from key as an double */
double acgi_double(acgi_t *h, const char *key, double default_value);

/* returns int32_t if value is not NULL and valid, otherwise default_value */
int32_t acgi_int32(acgi_t *h, const char *key, int32_t default_value);

/* returns uint32_t if value is not NULL and valid, otherwise default_value */
uint32_t acgi_uint32(acgi_t *h, const char *key, uint32_t default_value);

/* returns int64_t if value is not NULL and valid, otherwise default_value */
int64_t acgi_int64(acgi_t *h, const char *key, int64_t default_value);

/* returns uint64_t if value is not NULL and valid, otherwise default_value */
uint64_t acgi_uint64(acgi_t *h, const char *key, uint64_t default_value);

/* decode cgi text */
char *acgi_decode(aml_pool_t *pool, char *s);

#ifdef __cplusplus
}
#endif

#endif
