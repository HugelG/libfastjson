/*
 * Copyright (c) 2004, 2005 Metaparadigm Pte. Ltd.
 * Michael Clark <michael@metaparadigm.com>
 * Copyright (c) 2015 Rainer Gerhards
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See COPYING for details.
 *
 */

#ifndef _fj_json_object_private_h_
#define _fj_json_object_private_h_

#include "atomic.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LEN_DIRECT_STRING_DATA 32 /**< how many bytes are directly stored in fjson_object for strings? */

typedef void (fjson_object_private_delete_fn)(struct fjson_object *o);

struct fjson_object
{
	enum fjson_type o_type;
	fjson_object_private_delete_fn *_delete;
	fjson_object_to_json_string_fn *_to_json_string;
	int _ref_count;
	struct printbuf *_pb;
	union data {
		fjson_bool c_boolean;
		double c_double;
		int64_t c_int64;
		struct lh_table *c_object;
		struct array_list *c_array;
		struct {
			union {
			/* optimize: if we have small strings, we can store them
			* directly. This saves considerable CPU cycles AND memory.
			*/
			char *ptr;
			char data[LEN_DIRECT_STRING_DATA];
			} str;
		int len;
		} c_string;
	} o;
	fjson_object_delete_fn *_user_delete;
	void *_userdata;
	DEF_ATOMIC_HELPER_MUT(_mut_ref_count)
};

#ifdef __cplusplus
}
#endif

#endif
