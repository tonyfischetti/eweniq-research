#!/bin/bash

gcc -o eweniq-glib eweniq-glib.c -O3 -Wall -Wextra -I/opt/local/include/glib-2.0 -I/opt/local/lib/glib-2.0/include -I/opt/local/include -L/opt/local/lib -lglib-2.0 -lintl
