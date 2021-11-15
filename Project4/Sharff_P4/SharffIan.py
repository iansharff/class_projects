#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Ian Sharff
COSC 010
Project 4 (Final)
"""
import csv
import os
import matplotlib.pyplot as mpp
import datetime

def main():
    """ Run various functions required by the project stipulations"""
    infilename = 'SharffIan.csv' # Name of CSV file
    outfilename = 'output.txt' # Default output file name
    print(f"Current output file name is: {outfilename}")
    print("Change output file name?") # Option to change output file name
    if yesorno():
        outfilename = input("Enter new output file name: ") + ".txt"
        print(f"Output file updated to: {outfilename}")
    array = read_file(infilename) # List of lists of elements in rows
    dict_array = read_dict_file(infilename) # List of dictionaries
    # Fieldname keys map to values, defaults to first row
   
    print_data(array) # Option to print raw data
    question3(array) # Option to display the test index searches in Q3
    questions4and5(dict_array, outfilename) # Prints specified variable calcs
    
    # Option to append fill data frame and run the character count functions
    print(f"Append full data frame to {outfilename}?")
    if yesorno():
        line_lengths = AppendFunction(outfilename, array)
        display_lengths(line_lengths)
    # Option to run the line plot function, work in progress
    print("Display graph of two-year adjusted close price?")
    if yesorno():
        MakeGraphs(dict_array)
    
    # Option to append calculations to the existing output .txt file
    UserChoice(dict_array, outfilename)
    remove_file(outfilename)

def yesorno():
    """Collect input, if and only if 'yes', returns True"""
    if input('-->').lower() == 'yes':
        return True
    else:
        return False

def read_file(f):
    """Read file to 2D list with csv import"""
    with open(f, newline = '') as csvfile:
        reader = csv.reader(csvfile)
        rows = [r for r in reader]
        return rows

def read_dict_file(f):
    """Read file to list of dictionaries with csv import DictReader class method"""
    with open(f, newline = '') as csvfile:
        d_reader = csv.DictReader(csvfile)
        rows = [r for r in d_reader]
        return rows
    
def print_data(arr):
    """Print raw data from CSV by row"""
    print("Print raw data?")
    if yesorno():
        for row in arr:
            print(','.join(row))    

def question3(arr):
    """Display searched values according to question 3"""
    print("Display test elements?")
    if yesorno():
        print("Third row: ")
        print(*arr[2], sep = ',')
        
        print("First column: ")
        for row in arr:
            print(row[0])
        
        print("Row 0, column 4: ")
        print(arr[0][4])

def questions4and5(d_arr, filename):
    """Print and write calculations for high prices, low prices, and volume to .txt file"""
    
    print("Printing and writing calculations for high prices, low prices, and volumes...")
    # List comprehensions converting stings to floats
    high_prices = [float(r['High']) for r in d_arr]
    low_prices = [float(r['Low']) for r in d_arr]
    volumes = [float(r['Volume']) for r in d_arr]
    
    # Tuples associating variable names with float lists
    fields = [('High', high_prices), ('Low', low_prices), ('Volume', volumes)]
    
    # Writes calculations to files using display_calc functions
    with open(filename, 'w') as textfile:
        
        for variable, nums in fields:
            calculations = display_calc(variable, nums)
            print(calculations)
            textfile.write(calculations)
        print(f"File {filename} created.")

def AppendFunction(filename, dataframe):
    """Append raw data frame to output file"""
    # First writes lines to the text file
    with open(filename, 'a') as appfile:
        for item in dataframe:
            string_line = ','.join(item) + '\n'
            appfile.write(string_line)
    print(f"Dataframe appended to file '{filename}'")
    # Then reads file and adds character lengths and total characters to list
    with open(filename, 'r') as readfile:
        char_count = [len(line) for line in readfile]
        total_char = sum(char_count)
        char_count.append(total_char)
    # Return list to be displayed by function in main()
        return char_count

def UserChoice(dataframe, filename):
    """Collect user input to determine variable calculations to append to outfile"""
    if input("Append other calculations?\n-->").lower() != 'yes':
        return None
    else:
        with open(filename, 'a') as f:
            variables = list(dataframe[0].keys())
            variables.remove('Date')
            appending = True
            while appending:
                print("Enter variable name that you would calculations for")
                print("Available variables:")
                print(*variables, sep = ', ')
                choice = input('-->').title()
                if choice in variables:
                    workinglist = [float(row[choice]) for row in dataframe]
                    calculations = display_calc(choice, workinglist)
                    print(calculations)
                    f.write(calculations)
                    print(f"{choice} calculations appended to {filename}.")
                else:
                    print("Invalid entry")
                
                if input("Keep appending?\n-->").lower() != 'yes':
                    appending = False
            
def MakeGraphs(dataframe):
    """Plot adjusted close price against date for two-year MSFT stock data"""
    lineplot_name = "AdjustedClosePrices_LinePlot.jpg" # Name of line plot
    title = "Two-year MSFT Adjusted Close Price" # Title for plot
    
    # Date values converted to datetime.datetime objects to function with mpp
    xvals = [datetime.datetime.strptime(row['Date'], '%Y-%m-%d') for row in dataframe]
    # Adj Close values converted to float to be plotted on y-axis
    yvals = [float(row['Adj Close']) for row in dataframe]
    # Plot method
    mpp.plot(xvals, yvals)
    # Adds title and axis labels
    mpp.title(title)
    mpp.xlabel("Date")
    mpp.ylabel("Adjusted Close Price USD")
    
    # Save to .jpg file in folder
    mpp.savefig(lineplot_name)
    # Show plot in IPython
    mpp.show()

def calculate_mean(col):
    """Pass list parameter and return mean value"""
    mean = sum(col)/len(col)
    return mean

def calculate_median(col):
    """Pass list parameter and return median value"""
    m = len(col) // 2
    if len(col) % 2 == 0:
        median = (col[m] + col[m + 1]) / 2
    else:
        median = col[m]
    return median

def calculate_max(col):
    """Pass list parameter and return max value"""
    # List is alread sorted by the display_calc() function, no need to call max()
    maximum = col[-1]
    return maximum

def calculate_min(col):
    """Pass list parameter and return min value"""
    # List is already sorted
    minimum = col[0]
    return minimum

def round_two(num):
    """Pass float and return number rounded to two decimal places"""
    return round(num, 2)

def display_calc(name, li):
    """Pass and sort list parameter, format and return display string to be written to file"""
    li.sort()
    # Calc functions called with list parameter
    values = (calculate_mean(li), calculate_median(li), calculate_max(li), calculate_min(li))
    # Calls rounding function for each calculated value and returns list
    rounded_values = list(map(round_two, values))
    # Formats floats as string, ensuring that two decimals are displayed
    display = ("{} calculations:\n"
               "Mean: {:.2f}\n"
               "Median: {:.2f}\n"
               "Maximum: {:.2f}\n"
               "Minimum: {:.2f}\n\n")
    # format() string method called and name parameter indicates variable
    formatted_display = display.format(name, *rounded_values)
    return formatted_display

def display_lengths(lengths):
    """Display line length data from Question 5"""
    print("List of line lengths:\n")
    for num in lengths:
        print(num, end = ',')
    else: print('\n')
    print(f"Calculated total characters = {lengths[-1]}")

def remove_file(filename):
    """Option to delete the file produced by the program"""
    print(f"Delete file '{filename}'?")
    if yesorno():
        os.remove(filename)
        print("File deleted")
    print("Thank you, signing off...")


if __name__ == '__main__': main()
    