#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Oct  8 21:14:27 2020

@author: iansharff
"""

#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Oct  6
Ian Sharff
COSC-010
Project 1
10/09/2020
"""
import sys
import time
import math
delaytime = 0


#Greet function collects and returns the selected username
def Greet():
    username = input("Hello! I am Updog your digital assistant. What is your name?\nEnter username: ")
    time.sleep(2 * delaytime)
    print("")
    print(f"Nice to meet you {username}!")
    time.sleep(delaytime)
    print("I serve a variety of functions,")
    time.sleep(delaytime)
    print("but, in order to use them,")
    time.sleep(delaytime)
    print("you will have to choose a password.")
    time.sleep(2 * delaytime)
    print("")
    return username

def EnterPassword():
    print("Your password must contain the following:")
    time.sleep(delaytime)
    print("• Six or more characters\n• A capital letter\n• A lowercase letter\n• At least one special character (!,#,$,%,&)")
    time.sleep(delaytime)
    
    specialcharacters = ["!", "#", "$", "%", "&"]
    password_valid = False
    password_verified = False
    
    while password_valid == False or password_verified == False :
        
        password = input("Enter Password: ")
        time.sleep(delaytime)
        over_six = len(password) >= 6
        all_upper = password.isupper()
        all_lower = password.islower()
        for char in password :
            if char in specialcharacters :
                has_special = True
                break
            else :
                has_special = False
        
        if over_six == False :
            print("Sorry, password must contain at least six characters")
        elif all_upper == True or all_lower == True or has_special == False :
            print("Sorry, password must contain a lowercase letter, a capital letter, and at least one special character")
        else :
            password_valid = over_six and has_special and not all_upper and not all_lower
            print("Password accepted")
            time.sleep(delaytime)
            
            verified_pw = input("Please re-enter your password to verify it: ")
            time.sleep(delaytime)
            if verified_pw != password :
                print("Passwords are not verified")
                time.sleep(delaytime)
                print("Try again.")
                time.sleep(delaytime)
            else :
                print("Password verified.")
                print("")
                time.sleep(delaytime)
                password_verified = True
    return password

def Login(username, password):
    print("Now you are ready to log in to your account.")
    time.sleep(delaytime)
    user_entry = ""
    password_entry = ""
    attempts_left = 3
    
    while user_entry != username and password_entry != password and attempts_left > 0 :
        user_entry = input("Username: ")
        time.sleep(delaytime)
        password_entry = input("Password: ")
        if user_entry != username or password_entry != password :
            print("Username/Password combiniation is incorrect")
            time.sleep(delaytime)
            attempts_left -= 1

            print(f"You have {attempts_left} attempts left.")
            time.sleep(delaytime)
            if attempts_left == 0 :
                print("You are out of attempts and have been locked out.")
                sys.exit(0)
        else :
            print(f"Welcome {username}!")
            print("")
            time.sleep(delaytime)
   
def FunctionSelection(username):
    print(f"Now, {username}, what would you like me to do?")
    time.sleep(delaytime)
    print("In my current version, I only have one function.")
    time.sleep(delaytime)    
    print("Please choose from the following: \n•Calculator")
    time.sleep(delaytime)
    
    function_choice = input("Choose function: ")
    time.sleep(delaytime)
    
    return function_choice

def Calculator():
    normal_operators = ["-", "+", "/", "*"]
    exitloop = False
    while exitloop == False :
        print("Please choose an operator (-,+,*,/,!)")
        operator = input("Enter operator: ")
        
        if operator in normal_operators :
            try :
                firstnumber = float(input("Choose the first number: "))
                secondnumber = float(input("Choose the second number: "))
                time.sleep(delaytime)
            except: 
                print("Values unacceptable. Must be numeric. Cannot compute.")
                sys.exit(0)
            
            if operator == "+" :
                answer = firstnumber + secondnumber
            elif operator == "-" :
                answer = firstnumber - secondnumber
            elif operator == "*" :
                answer = firstnumber * secondnumber
            else :
                try :
                    answer = firstnumber / secondnumber
                except :
                    print("Error. Cannot divide by zero. Goodbye.")
                    sys.exit(0)
                
            print(f"{firstnumber} {operator} {secondnumber} is equal to {answer}")
            
        elif operator == "!" :
            try :
                number = float(input("Choose a number: "))
            except:
                print("Invalid entry, must be numeric. Cannot compute")
                sys.exit(0)
            try :
                factorial = math.factorial(number)
            except :
                print("Value unacceptable ")
            
            print(f"The factorial of {number} is {factorial}")
            
        else :
            print("Invalid operator. Goodbye.")
            sys.exit(0)
        
        repeat = input("If you would like to do another calculation, please type Yes")
        if repeat == "Yes" :
            pass
        else :
            exitloop = True

def SignOff(username):
    print(f"See you later {username}!")

def main():
    username = Greet()
    password = EnterPassword()
    Login(username, password)
    function_choice = FunctionSelection(username)
    if function_choice == "Calculator":
        Calculator()
    else :
        pass
    SignOff(username)

main()
