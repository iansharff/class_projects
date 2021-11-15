#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Ian Sharff
COSC 010
Project 3
"""


class Person:
    """Person class containing attributes for name, phone #, email."""

    def __init__(self, lname, fname, phone, email):
        self._lname = lname
        self._fname = fname
        self._phone = phone
        self._email = email
        print(f'{self.fullname()} was added to the database')

    def lname(self, l=None):
        """Last name setter/getter."""
        if l:
            self._lname = l
        return self._lname

    def fname(self, f=None):
        """First name setter/getter."""
        if f:
            self._fname = f
        return self._fname

    def phone(self, p=None):
        """Phone number setter/getter."""
        if p:
            self._phone = p
        return self._phone

    def email(self, e=None):
        """Email setter/getter."""
        if e:
            self._phone = e
        return self._email

    def fullname(self):
        """Return Person object's full name."""
        return self.fname() + ' ' + self.lname()


class Client(Person):
    """Person subclass representing clients with added attributes."""

    def __init__(self, lname, fname, phone, email, card=None):
        super().__init__(lname, fname, phone, email)
        if card is None:
            self._card = "No card on file"
        else:
            self._card = card

    def card(self, c=None):
        """Credit car number setter/getter."""
        if c: self._card = c
        return self._card

    def __str__(self):
        """Return string representation."""
        return f'{self.fullname()} : {self.phone()} | {self.email()} | {self.card()}'

    def __del__(self):
        """Print message to inform deletion of instance from list"""
        print(f"{self.fullname()} deleted from database.")

class Employee(Person):
    """Person subclass representing company employees."""

    def __init__(self, lname, fname, phone, email, wage):
        super().__init__(lname, fname, phone, email)
        self._wage = wage
        self._hours = 0

    def wage(self, w=None):
        if w: self._wage = w
        return self._wage
#Not implemented in the program, could allow for workers to log hours
    def hours(self, h=None, addition=False):
        if addition and h:
            self._hours += h
        elif h:
            self._hours = h

        return self._hours

    def payday(self, balance_list):
        paycheck = self.hours() * self.wage()
        self.hours(0)
        balance_list.append(-1 * paycheck)
        return paycheck

    def payraise(self, percent_increase):
        multiplier = percent_increase * 0.01 + 1
        self.wage(self._wage * multiplier)

    def __str__(self):
        return f'{self.fullname()} : {self.phone()} | {self.email()}\nCurrent Hourly Wage: ${self.wage()}\nHours Logged: {self.hours()}\n'

    def __del__(self):
        print(f"{self.fullname()} deleted from database.")

class Product:
    """Represent items purchased, sold or used by the company."""

    def __init__(self, name, quantity, unit_cost, unit_price):
        self._name = name
        self._quantity = quantity
        self._unit_cost = unit_cost
        self._unit_price = unit_price

    def name(self, p=None):
        if p: self._name = p
        return self._name

    def quantity(self, q=None):
        if q: self._quantity = q
        return self._quantity

    def unit_cost(self, uc=None):
        if uc: self._unit_cost = uc
        return self._unit_cost

    def unit_price(self, up=None):
        if up: self._unit_price = up
        return self._unit_price

    def buyitem(self, num):
        cost = num * self.unit_cost()
        self._quantity += num
        return cost

    def sellitem(self, num):
        self._quantity -= num
        pricetag = num * self.unit_price()
        return pricetag

    def __str__(self):
        return f'{self.name()} | {self.quantity()} in stock\nUnit Cost: ${self.unit_cost()}\nUnit Sell Price: ${self.unit_price()}\n'
    
    def __del__(self):
        print(f"{self.name()} item deleted from database.")
        
