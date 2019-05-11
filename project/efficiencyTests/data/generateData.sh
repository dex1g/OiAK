#!/bin/bash
# Generate data using dd tool
# 1GB numbers
dd if=/dev/urandom of=firstNumber1GB bs=1024 count=1048576 
dd if=/dev/urandom of=secondNumber1GB bs=1024 count=1048576 
# 1MB number
dd if=/dev/urandom of=firstNumber1MB bs=1024 count=1024 
# 20KB number
dd if=/dev/urandom of=firstNumber20KB bs=1024 count=20