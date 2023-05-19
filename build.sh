#!/bin/env bash

set -e;

C_COMPILER='cc';
C_FLAGS='-O0 -Wall -Wextra -Wconversion';

${C_COMPILER} ${C_FLAGS} main.c;
