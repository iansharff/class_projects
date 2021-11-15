#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Oct 26 16:06:35 2020

@author: iansharff
"""
class Location:
    def __init__(self, name, difficulty, available):
        self.name = name
        self.difficulty = difficulty
        self.available = available
    def welcome_statement(self):
        

beach = Location("Beach", "Easy", False)
forest = Location("Forest", "Medium", False)
cave = Location("Cave", "Hard", False)
town = Location("Town", "Peaceful", True)        

