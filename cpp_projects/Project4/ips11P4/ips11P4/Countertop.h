//
//  Countertop.h
//  ips11P4
//
//  Created by Ian Sharff on 4/24/21.
//

#include <string>
#include <vector>

using namespace std;

// Countertop class definition
class Countertop
{
private:
    char stone_code;
    double length, depth, height;
    int length_edges, depth_edges;
    string order_number, region;
    bool is_valid;
    vector<string> error_messages {};
  
public:
    // Default constructor
    Countertop();
    
    // Member function prototypes

    
    // Setter function prototypes
    void set_stone_code(char),
    set_length(double),
    set_depth(double),
    set_height(double),
    set_length_edges(int),
    set_depth_edges(int),
    set_order_number(string),
    set_region(string);
    
    // Getter function prototypes
    
    char get_stone_code();
    
    double get_length(),
    get_depth(),
    get_height();
    
    int get_length_edges(),
    get_depth_edges();
    
    string get_order_number(),
    get_region();
    
    // Error message functions
    
    void add_error_message(string);
    void display_errors();
    bool countertop_valid();
    
    // Validation member functions
    void validate_stone_code(),
    validate_length(),
    validate_depth(),
    validate_height(),
    validate_length_edges(),
    validate_depth_edges(),
    validate_order_number(),
    validate_region();
    
    // Calculation member functions
    
    double calculate_area();
    double calculate_stone_cost();
    double calculate_edge_cost();

    // Display member functions
    void display_countertop_data();
    
};

