#!/bin/bash

dot -Tpng ${1}.txt -o ${1}.png
open ${1}.png
