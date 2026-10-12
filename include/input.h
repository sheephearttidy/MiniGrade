#pragma once
#include "common.h"

ErrCode read_int(const char* s, int* out);
ErrCode read_str(const char* s, char* out, size_t max_len);
ErrCode read_score(const char* s, int* out);