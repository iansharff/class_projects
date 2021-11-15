#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Dec 12 18:28:03 2020

@author: iansharff
"""

with open('output.txt', 'r') as testfile:
    count = 0
    for line in testfile:
        count += len(line)
        print(len(line), end = ',')
    else:
        print('\n')
    print(f"Final count = {count}")