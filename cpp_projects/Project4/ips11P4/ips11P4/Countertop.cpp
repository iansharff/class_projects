//
//  Countertop.cpp
//  ips11P4
//
//  Created by Ian Sharff on 4/21/21.
//

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include "Countertop.h"

using namespace std;

const double MARBLE_RATE {92.99}, // Set stone prices per square foot
             GRANITE_RATE {78.99},
             QUARTZ_RATE {56.99},
             LOWER_LIMIT {5.0}, // Set lower and upper limit of the length and depth
             UPPER_LIMIT {25.0},
             MIN_PERCENT {0.58}, // Set percent range for height based on depth
             MAX_PERCENT {0.80},
             AREA_MULTIPLIER {1.26}, // Set wastage multiplier for stone area
             EDGE_RATE {4.99}; // Set rate for finished edges per foot

const int MIN_EDGES {0}, // Set minimum and maximum number of length or depth edges
          MAX_EDGES {2};

// Error message constants
const string DATES_SAME = "The order date is the same as the delivery date.",
             DATES_OOR = "The delivery date is too far from the order date.",
             STONE_INVALID = "Invalid stone type",
             LENGTH_INVALID = "Invalid length.",
             DEPTH_INVALID = "Invalid depth.",
             HEIGHT_INVALID = "Invalid height.",
             LEN_EDGE_INVALID = "Invalid number of length edges.",
             DEP_EDGE_INVALID = "Invalid number of depth edges.";

using namespace std;
// Constructor

Countertop::Countertop()
{
    stone_code = 'X';
    length = 0;
    depth = 0;
    height = 0;
    length_edges = 0;
    depth_edges = 0;
    order_number = "Empty";
    region = "Empty";
    
}
// Setter member function definitions

void Countertop::set_stone_code (char sc)
{   stone_code = sc;    }

void Countertop::set_length(double l)
{   length = l;         }

void Countertop::set_depth(double d)
{   depth = d;          }

void Countertop::set_height(double h)
{   height = h;         }

void Countertop::set_length_edges(int le)
{   length_edges = le;  }

void Countertop::set_depth_edges(int de)
{   depth_edges = de;   }

void Countertop::set_order_number(string on)
{   order_number = on;  }

void Countertop::set_region(string r)
{   region = r;         }

// Getter member function definitions

char Countertop::get_stone_code()
{   return stone_code;      }

double Countertop::get_length()
{   return length;          }

double Countertop::get_depth()
{   return depth;           }

double Countertop::get_height()
{   return height;          }

int Countertop::get_length_edges()
{   return length_edges;    }

int Countertop::get_depth_edges()
{   return depth_edges;     }

string Countertop::get_order_number()
{   return order_number;    }

string Countertop::get_region()
{   return region;          }

// Error message functions

// Add error message to Countertop object's vector error_messages
void Countertop::add_error_message(string error_message)
{   error_messages.push_back(error_message);    }

// Return true if no error messages, false otherwise
bool Countertop::countertop_valid()
{
    if (error_messages.size() == 0)
        return true;
    else
        return false;
}

// Display countertop error messages
void Countertop::display_errors()
{
    if (!countertop_valid())
    {
        for (std::string error_message: error_messages)
            cout << "ERROR: " << error_message << endl;
    }
}

// Validation member function definitions

void Countertop::validate_stone_code()
{
    if (stone_code != 'M' && stone_code != 'G' && stone_code != 'Q')
        add_error_message(STONE_INVALID);
}

void Countertop::validate_length()
{
    if (length > UPPER_LIMIT || length < LOWER_LIMIT)
        add_error_message(LENGTH_INVALID);
}

void Countertop::validate_depth()
{
    if (depth > length || depth < LOWER_LIMIT)
        add_error_message(DEPTH_INVALID);
}

void Countertop::validate_height()
{
    if (height > MAX_PERCENT * depth || height < MIN_PERCENT * depth)
        add_error_message(HEIGHT_INVALID);
}

void Countertop::validate_length_edges()
{
    if (length_edges > MAX_EDGES || length_edges < MIN_EDGES)
        add_error_message(LEN_EDGE_INVALID);
}

void Countertop::validate_depth_edges()
{
    if (depth_edges > MAX_EDGES || depth_edges < MIN_EDGES)
        add_error_message(DEP_EDGE_INVALID);
}

// Calculation member function definitions

// Calculate required area for construction
double Countertop::calculate_area()
{
    double area {};
    area = ceil(get_length() * get_height() * AREA_MULTIPLIER);
    return area;
}

// Calculate stone cost according to stone code
double Countertop::calculate_stone_cost()
{
    double stone_cost {};
    double stone_area = calculate_area();
    switch (get_stone_code())
    {
        case 'M':   // Marble
            stone_cost = stone_area * MARBLE_RATE;  // Calculate cost depending on stone type
            break;
        case 'G':   // Granite
            stone_cost = stone_area * GRANITE_RATE;
            break;
        case 'Q':   // Quartz
            stone_cost = stone_area * QUARTZ_RATE;
            break;
    }
    return stone_cost;
}

// Calculate edge finishing cost
double Countertop::calculate_edge_cost()
{
    double edge_cost {};
    edge_cost = EDGE_RATE * (length_edges * length + depth_edges * depth);
    return edge_cost;
}


// Display information for a Countertop object
void Countertop::display_countertop_data()
{
    cout << get_stone_code();
    cout << setw(6) << get_length();
    cout << setw(6) << get_depth();
    cout << setw(6) << get_height();
    cout << setw(2) << get_length_edges();
    cout << setw(2) << get_depth_edges();
    cout << setw(11) << get_order_number();
    cout << setw(7) << get_region();
}
