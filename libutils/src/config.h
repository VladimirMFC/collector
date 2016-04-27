#pragma once

#include <stdbool.h>
#include <stdint.h>

bool config_exist();
bool config_open(const char* filename);
bool config_close();

const char* config_value(const char* key);

int64_t config_value_int(const char* key);
double config_value_double(const char* key);
bool config_value_bool(const char* key);
const char* config_value_string(const char* key);
