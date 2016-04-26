#pragma once

#include <stdbool.h>

void daemonize(const char* cmd);
void options_parse(int argc, char** argv);
bool config_handler();
