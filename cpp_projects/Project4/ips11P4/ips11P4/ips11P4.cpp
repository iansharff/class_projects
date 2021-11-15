//
//  main.cpp
//  ips11P4
//
//  Created by Ian Sharff on 4/21/21.
// /Users/iansharff/Desktop/COSC-051/Project4/ips11P4/ips11P4/P4OrdersA/P4OrdersA-All.dat

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include "Countertop.h"

using namespace std;

// Numeric constants
const double MARBLE_RATE {92.99}, // Set stone prices per square foot
             GRANITE_RATE {78.99},
             QUARTZ_RATE {56.99};


const int MONTH_RANGE {4}; // Set maximum difference between delivery and order dates in months

// Error message constants
const string DATES_SAME = "The order date is the same as the delivery date.",
             DATES_OOR = "The delivery date is too far from the order date.",
             STONE_INVALID = "Invalid stone type",
             LENGTH_INVALID = "Invalid length.",
             DEPTH_INVALID = "Invalid depth.",
             HEIGHT_INVALID = "Invalid height.",
             LEN_EDGE_INVALID = "Invalid number of length edges.",
             DEP_EDGE_INVALID = "Invalid number of depth edges.";


// Function Prototypes
void greet_user(), print_options();

char display_menu();

void upload_file(string file_name, bool &load_success, vector<Countertop> &v_countertops),
    all_details (const vector<Countertop> &v_countertops),
    order_details (const vector<Countertop> &v_countertops),
    stone_summary(const vector<Countertop> &v_countertops),
    region_summary (const vector<Countertop> &v_countertops);

bool clear_vector (vector<Countertop> &v_countertops);

bool vector_is_empty(const vector<Countertop>&);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                     *
 *                                                     *
 *                     Function Main                   *
 *                                                     *
 *                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main()
{
    vector<Countertop> v_countertops;
    
    bool load_success{}, user_quit{};
    
    greet_user();
    
    while(!user_quit)
    {
        // Call display menu function to determine operation
        char user_choice = display_menu();
        switch(user_choice)
        {
            // Upload file call
            case 'U':
            {
                string file_name;
                cout << "Please enter the file name and path: ";
                cin >> file_name;
                
                upload_file(file_name, load_success, v_countertops);
                break;
            }
            // Display all details
            case 'A':
                all_details(v_countertops);
                break;
            // Display details of a specific order
            case 'O':
                order_details(v_countertops);
                break;
            // Display summary by region
            case 'R':
                region_summary(v_countertops);
                break;
            // Display summary by stone code
            case 'S':
                stone_summary(v_countertops);
                break;
            // Clear all vectors
            case 'C':
            {
                clear_vector(v_countertops);
                break;
            }
            // Quit program
            case 'Q':
                user_quit = true;
                break;
            default: cout << "Unintended Error" << endl;
        }
    }
    cout << endl;
    return 0;
    
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                     *
 *                                                     *
 *                   Function Greet User               *
 *                                                     *
 *                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void greet_user()
{
    cout << "Welcome to Claude's Custom Counters, Inc. Calculator!" << endl;
    cout << "This application calculates cost and fabrication data" << endl;
    cout << "based on sales data input files." << endl;
    cout << endl << endl;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                     *
 *                                                     *
 *                  Function Display Menu              *
 *                                                     *
 *                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

char display_menu()
{
    char menu_choice {};
    bool choice_valid {};
    do
    {
        // Display menu options
        cout << setw(40) << "Upload a regional sales data file";
        cout << setw(5) << "U" << endl;
        cout << setw(40) << "Display details for all loaded data";
        cout << setw(5) << "A" << endl;
        cout << setw(40) << "List details for a specific order number";
        cout << setw(5) << "O" << endl;
        cout << setw(40) << "Display summary by region";
        cout << setw(5) << "R" << endl;
        cout << setw(40) << "Display summary by stone code";
        cout << setw(5) << "S" << endl;
        cout << setw(40) << "Clear all vectors";
        cout << setw(5) << "C" << endl;
        cout << setw(40) << "Quit";
        cout << setw(5) << "Q" << endl << endl;
        
        // Collect user choice, clear input buffer, captialize character
        cout << "Enter your choice: ";
        cin >> menu_choice;
        cin.ignore(20, '\n');
        menu_choice = toupper(menu_choice);
        
        // Validate choice
        if(menu_choice != 'U'
           && menu_choice != 'A'
           && menu_choice != 'O'
           && menu_choice != 'R'
           && menu_choice != 'S'
           && menu_choice != 'C'
           && menu_choice != 'Q')
        {
            cout << endl << "Invalid entry. Please try again." << endl << endl;
        }
        else
            choice_valid = true;
    }
    while(!choice_valid);
    return menu_choice;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                     *
 *                                                     *
 *            Function Upload File                     *
 *                                                     *
 *                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void upload_file(string file_name, bool &load_success, vector<Countertop> &v_countertops)
{
    ifstream input_file;
    input_file.open(file_name);
    if (!input_file)
    {
        cout << "An error occured while opening file with path: " << file_name << endl;
        cout << "Load unsuccessful." << endl;
    }
    else
    {
        // Define variables
        char
            stone_code{}; // Stone character from input file
        
        double
            length{}, // Dimensions from input file
            depth{},
            height{};
        
        int order_year {},  // Year, month and day values for order and delivery dates read from
            order_month {}, // input file
            order_day {},
            delivery_year {},
            delivery_month {},
            delivery_day {},
            num_length_edges {},    // Number of length and depth edges to be finished read from input file
            num_depth_edges {},
            valid_records {0}, // Accumulators for total records, valid records and invalid records
            invalid_records {0},
            total_records {0};
        
        string order_number, region;
        // Read first line containing headers
        
        string first_line;
        getline(input_file, first_line);
        
        vector<string> headers {"Ord. Date",
                                "Del. Date",
                                "SC", "Len.",
                                "Dep.", "Hei.",
                                "Len. Edges",
                                "Dep. Edges",
                                "Ord. Num.",
                                "Region"};
        
        // Output headers for loaded data
        for (string header: headers)
        {
            cout << header << "  ";
        }
        cout << endl;
        
        // Output dividing line
        cout << setfill('-');
        cout << setw(58) << '-' << endl;
        cout << setfill(' ');
        
        while(input_file.peek() != EOF)
        {
            Countertop countertop;
            
            total_records ++;
            // Read order year, month and date from input file line
            input_file >> order_year;
            input_file.ignore();
            input_file >> order_month;
            input_file.ignore();
            input_file >> order_day;
            
            // Format order date including leading zeroes and pring to console
            cout << right << setfill('0');  // Set fill character to '0' and right justify, only for dates
            cout << order_year << '/';
            cout << setw(2) << order_month << '/';
            cout << setw(2) << order_day << ' ';
            
            // Read delivery year, month and date from input file line
            input_file >> delivery_year;
            input_file.ignore();
            input_file >> delivery_month;
            input_file.ignore();
            input_file >> delivery_day;
            
            // Format delivery date including leading zeroes and print to console
            cout << delivery_year << '/';
            cout << setw(2) << delivery_month << '/';
            cout << setw(2) << delivery_day << ' ';
            cout << setfill(' ');
            
            int diff_in_months = 12 * (delivery_year - order_year) + (delivery_month - order_month);
            
            // Add error message if order date and delivery date are the same
            if ((order_day == delivery_day) && (order_month == delivery_month) && (order_year == delivery_year))
                
                countertop.add_error_message(DATES_SAME);
            
            // Add error message if dates out of range
            else if (diff_in_months > MONTH_RANGE)
            {
                countertop.add_error_message(DATES_OOR);
            }
            
            input_file >> stone_code;
            cout << left;
            cout << setw(2) << stone_code;
            stone_code = toupper(stone_code);   // Capitalize stone code to simplify logic
            countertop.set_stone_code(stone_code);
            countertop.validate_stone_code();
            
            // Add error message if stone code is invalid
            
            // Length input, output and validation
            input_file >> length;
            cout << setw(6) << length;
            countertop.set_length(length);
            countertop.validate_length();
            
            // Depth input, output and validation
            input_file >> depth;
            cout << setw(6) << depth;
            countertop.set_depth(depth);
            countertop.validate_depth();
            
            // Height input, output and validation
            input_file >> height;
            cout << setw(6) << height;
            countertop.set_height(height);
            countertop.validate_height();
            
            // Length edges input, output and validation
            input_file >> num_length_edges;
            cout << setw(2) << num_length_edges;
            countertop.set_length_edges(num_length_edges);
            countertop.validate_length_edges();
            
            // Depth edges input, output and validation
            input_file >> num_depth_edges;
            cout << setw(2) << num_depth_edges;
            countertop.set_depth_edges(num_depth_edges);
            countertop.validate_depth_edges();
            
            input_file >> order_number;
            cout << setw(11) << order_number;
            countertop.set_order_number(order_number);
            
            input_file >> region;
            cout << setw(7) << region;
            countertop.set_region(region);
            
            // Ignore characters in buffer until a newline is reached
            input_file.ignore(999, '\n');
            
            cout << endl;
            if (countertop.countertop_valid())
            {
                // Increment valid records count
                valid_records ++;
                
                // Add valid data to vectors
                v_countertops.push_back(countertop);
                
            }
            else
            {
                // Increment invalid records count
                invalid_records ++;
                
                // Display error messages
                countertop.display_errors();
            }
        }
        cout << right << endl;
        cout << "Valid Entries: " << valid_records << endl;
        cout << "Invalid Entries: " << invalid_records << endl;
        cout << "Total Entries: " << total_records << endl << endl;
        
        if (v_countertops.empty())
        {
            load_success = false;
            cout << "Load unsuccessful" << endl;
        }
        else
        {
            load_success = true;
            cout << "Load successful" << endl;
        }
        
    }
    input_file.close();
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                     *
 *                                                     *
 *            Function Display All Details             *
 *                                                     *
 *                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void all_details(const vector<Countertop> &v_countertops)
{
    
    // Define calculated variables
    double
        stone_area{},   // Area to be calculated if record is valid
        stone_cost{},   // Stone cost, depends on stone code
        edge_cost{},    // Edge finishing cost, does not depend on stone code
        total_cost{};  // Sum of edge and stone cost
    
    bool no_data = vector_is_empty(v_countertops);
    
    
    if (!no_data)
    {
        vector<string> headers {"SC", "Len.", "Dep.", "Hei.", "Len. Edges", "Dep. Edges", "Ord. Num.", "Region", "Sq. Ft.", "Tot. Cost"};
        
        for (string header: headers)
        {
            cout << header << "  ";
        }
        cout << setfill('-');
        cout << setw(58) << '-' << endl;
        cout << setfill(' ');
        
        for(auto i {0}; i < v_countertops.size(); i++)
        {
            Countertop current_countertop = v_countertops.at(i);
            
            current_countertop.display_countertop_data();
            
            stone_area = current_countertop.calculate_area();
            edge_cost = current_countertop.calculate_edge_cost();
            stone_cost = current_countertop.calculate_stone_cost();
            
            total_cost = edge_cost + stone_cost;
            
            cout << fixed << setprecision(2);
            cout << setw(7) << stone_area;
            cout << setw(10) << total_cost;
            cout << endl;
        }
        cout << endl;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                     *
 *                                                     *
 *            Function Display Order Details           *
 *                                                     *
 *                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void order_details(const vector<Countertop> &v_countertops)
{
    double
        stone_area{},   // Area to be calculated if record is valid
        stone_cost{},   // Stone cost, depends on stone code
        edge_cost{},    // Edge finishing cost, does not depend on stone code
        total_cost{};  // Sum of edge and stone cost
    
    bool no_data {};
    no_data = vector_is_empty(v_countertops);
    
    if (!no_data)
    {
        string order_number;
        cout << "Enter the order number to search: ";
        cin >> order_number;
        
        int order_index {-1};
        Countertop current_countertop;
        
        for (auto i {0}; i < v_countertops.size(); i++)
        {
            current_countertop = v_countertops.at(i);
            if (current_countertop.get_order_number() == order_number)
            {
                order_index = i;
                break;
            }
        }
        
        if(order_index != -1)
        {
            current_countertop.display_countertop_data();
            
            stone_area = current_countertop.calculate_area();
            edge_cost = current_countertop.calculate_edge_cost();
            stone_cost = current_countertop.calculate_stone_cost();
            
            total_cost = edge_cost + stone_cost;
            cout << fixed << setprecision(2);
            cout << setw(7) << stone_area;
            cout << setw(10) << total_cost;
            cout << endl;
        }
        else
        {
            cout << "Order number " << order_number << " not found." << endl;
        }
        
    }
    cout << endl;
    return;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                     *
 *                                                     *
 *        Function Display Stone Code Summary          *
 *                                                     *
 *                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void stone_summary(const vector<Countertop> &v_countertops)
{
    double stone_cost {},
        stone_area {},
        edge_cost {},
        total_marble_area {0},
        total_marble_cost{0},
        total_granite_area{0},
        total_granite_cost{0},
        total_quartz_area{0},
        total_quartz_cost{0};
    
    int total_marble_orders{0}, // Accumulators for order counts
    total_granite_orders{0},
    total_quartz_orders{0};
    
    bool no_data = vector_is_empty(v_countertops);
    
    if (!no_data)
    {
        Countertop current_countertop;
        
        for(auto i {0}; i < v_countertops.size(); i++)
        {
            current_countertop = v_countertops.at(i);
            
            stone_area = current_countertop.calculate_area();
            edge_cost = current_countertop.calculate_edge_cost();
            
            switch (current_countertop.get_stone_code())
            {
                case 'M':   // Marble
                    stone_cost = stone_area * MARBLE_RATE;  // Calculate cost depending on stone type
                    total_marble_area += stone_area;    // Add stone area to corresponding accumulator
                    total_marble_cost += stone_cost + edge_cost;
                    total_marble_orders++;
                    break;
                case 'G':   // Granite
                    stone_cost = stone_area * GRANITE_RATE;
                    total_granite_area += stone_area;
                    total_granite_cost += stone_cost + edge_cost;
                    total_granite_orders++;
                    break;
                case 'Q':   // Quartz
                    stone_cost = stone_area * QUARTZ_RATE;
                    total_quartz_area += stone_area;
                    total_quartz_cost += stone_cost + edge_cost;
                    total_quartz_orders++;
                    break;
            }
        }
        cout << right << setw(37) << "Summary by Stone (Valid Orders)" << endl;
        cout << setw(9) << "Stone";
        cout << setw(9) << "Count";
        cout << setw(18) << "Square Feet";
        cout << setw(18) << "Cost ($)" << endl;
        
        // Top separating line
        cout << setfill('-');
        cout << setw(58) << '-' << endl;
        
        cout << fixed << setprecision(2);
        
        // Marble output
        cout << setfill(' ');
        cout << setw(9) << "Marble";
        cout << setw(9) << total_marble_orders;
        cout << setw(18) << total_marble_area;
        cout << setw(18) << total_marble_cost << endl;
        
        // Granite output
        cout << setw(9) << "Granite";
        cout << setw(9) << total_granite_orders;
        cout << setw(18) << total_granite_area;
        cout << setw(18) << total_granite_cost << endl;
        
        // Quartz output
        cout << setw(9) << "Quartz";
        cout << setw(9) << total_quartz_orders;
        cout << setw(18) << total_quartz_area;
        cout << setw(18) << total_quartz_cost << endl;
    }
    cout << endl;
    return;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                     *
 *                                                     *
 *            Function Display Region Summary          *
 *                                                     *
 *                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void region_summary(const vector<Countertop> &v_countertops)
{
    double stone_cost {},
        stone_area {},
        edge_cost {},
        total_north_area {0},
        total_north_cost{0},
        total_south_area{0},
        total_south_cost{0},
        total_east_area{0},
        total_east_cost{0},
        total_west_area{0},
        total_west_cost{0},
        total_other_area{0},
        total_other_cost{0};
    
    int total_north_orders{0}, // Accumulators for order counts
        total_south_orders{0},
        total_east_orders{0},
        total_west_orders{0},
        total_other_orders{0};
    
    bool no_data = vector_is_empty(v_countertops);
    
    if (!no_data)
    {
        Countertop current_countertop;
        
        for(auto i {0}; i < v_countertops.size(); i++)
        {
            current_countertop = v_countertops.at(i);
            
            stone_area = current_countertop.calculate_area();
            edge_cost = current_countertop.calculate_edge_cost();
            stone_cost = current_countertop.calculate_stone_cost();
            
            if (current_countertop.get_region() == "North")
            {
                total_north_orders ++;
                total_north_area += stone_area;
                total_north_cost += stone_cost + edge_cost;
            }
            else if (current_countertop.get_region() == "South")
            {
                total_south_orders ++;
                total_south_area += stone_area;
                total_south_cost += stone_cost + edge_cost;
            }
            else if (current_countertop.get_region() == "East")
            {
                total_east_orders ++;
                total_east_area += stone_area;
                total_east_cost += stone_cost + edge_cost;
            }
            else if (current_countertop.get_region() == "West")
            {
                total_west_orders ++;
                total_west_area += stone_area;
                total_west_cost += stone_cost + edge_cost;
            }
            else if (current_countertop.get_region() == "Other")
            {
                total_other_orders ++;
                total_other_area += stone_area;
                total_other_cost += stone_cost + edge_cost;
            }
        }
        cout << right << setw(37) << "Summary by Stone (Valid Orders)" << endl;
        cout << setw(9) << "Region";
        cout << setw(9) << "Count";
        cout << setw(18) << "Square Feet";
        cout << setw(18) << "Cost ($)" << endl;
        
        // Top separating line
        cout << setfill('-');
        cout << setw(58) << '-' << endl;
        
        cout << fixed << setprecision(2);
        
        // North output
        cout << setfill(' ');
        cout << setw(9) << "North";
        cout << setw(9) << total_north_orders;
        cout << setw(18) << total_north_area;
        cout << setw(18) << total_north_cost << endl;
        
        // South output
        cout << setw(9) << "South";
        cout << setw(9) << total_south_orders;
        cout << setw(18) << total_south_area;
        cout << setw(18) << total_south_cost << endl;
        
        // East output
        cout << setw(9) << "East";
        cout << setw(9) << total_east_orders;
        cout << setw(18) << total_east_area;
        cout << setw(18) << total_east_cost << endl;
        
        // West output
        cout << setw(9) << "West";
        cout << setw(9) << total_west_orders;
        cout << setw(18) << total_west_area;
        cout << setw(18) << total_west_cost << endl;
        
        // Other output
        cout << setw(9) << "Other";
        cout << setw(9) << total_other_orders;
        cout << setw(18) << total_other_area;
        cout << setw(18) << total_other_cost << endl;
    }
    cout << endl;
    return;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                     *
 *                                                     *
 *                 Function Clear Vectors          *
 *                                                     *
 *                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

bool clear_vector(vector<Countertop> &v_countertops)
{
    bool no_data = vector_is_empty(v_countertops);
    
    bool clearing_successful{};
    if (!no_data)
    {
        v_countertops.clear();
        
        if (v_countertops.empty())
        {
            clearing_successful = true;
            cout << "All vectors cleared." << endl;
        }
        else
            cout << "Operation unsuccessful" << endl;
    }
    cout << endl;
    return clearing_successful;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                     *
 *                                                     *
 *                 Function Vector Empty               *
 *                                                     *
 *                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

bool vector_is_empty(const vector<Countertop> &v_countertops)
{
    bool vectors_empty {false};
    if (v_countertops.empty())
    {
        cout << endl;
        cout << "No data has been loaded. Please upload a file to perform this action";
        cout << endl << endl;
        vectors_empty = true;
    }
    return vectors_empty;
}
