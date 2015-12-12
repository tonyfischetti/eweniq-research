#!/bin/bash

perl -ne 'print if !$a{$_}++';
