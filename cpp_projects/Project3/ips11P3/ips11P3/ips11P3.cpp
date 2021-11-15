/*
 * ips11P3.cpp
 *
 * COSC 051-02 S21
 * Project #3
 *
 * Due on: 04-8-2021
 * Author: Ian Sharff
 *
 * In accordance with the class policies and Georgetown's
 * Honor Code, I certify that, with the exception of the
 * class resources and those items noted below, I have neither
 * given nor received any assistance on this project.
 *
 * References not otherwise commented within the program source code:
 
 /Users/iansharff/Desktop/COSC-051/Project3/P3OrdersB/P3OrdersB-All.dat
 /Users/iansharff/Desktop/COSC-051/Project3/P3OrdersB/P3OrdersB-E.dat
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;
// Define global constants

// Numeric constants
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
          MAX_EDGES {2},
          MONTH_RANGE {4}; // Set maximum difference between delivery and order dates in months


// Error message constants
const string DATES_SAME = "The order date is the same as the delivery date.",
             DATES_OOR = "The delivery date is too far from the order date.",
             STONE_INVALID = "Invalid stone type",
             LENGTH_INVALID = "Invalid length.",
             DEPTH_INVALID = "Invalid depth.",
             HEIGHT_INVALID = "Invalid height.",
             LEN_EDGE_INVALID = "Invalid number of length edges.",
             DEP_EDGE_INVALID = "Invalid number of depth edges.";

// Function prototypes
void greet_user(), print_options();

char display_menu();

void upload_file(string file_name,
                 bool &load_success,
                 vector<char> &stone_codes,
                 vector<double> &lengths,
                 vector<double> &depths,
                 vector<double> &heights,
                 vector<int> &length_edges,
                 vector<int> &depth_edges,
                 vector<string> &order_numbers,
                 vector<string> &regions);

void all_details(const vector<char> &stone_codes,
                 const vector<double> &lengths,
                 const vector<double> &depths,
                 const vector<double> &heights,
                 const vector<int> &length_edges,
                 const vector<int> &depth_edges,
                 const vector<string> &order_numbers,
                 const vector<string> &regions);

void order_details(const vector<char> &stone_codes,
                 const vector<double> &lengths,
                 const vector<double> &depths,
                 const vector<double> &heights,
                 const vector<int> &length_edges,
                 const vector<int> &depth_edges,
                 const vector<string> &order_numbers,
                 const vector<string> &regions);

void stone_summary(const vector<char> &stone_codes,
                 const vector<double> &lengths,
                 const vector<double> &depths,
                 const vector<double> &heights,
                 const vector<int> &length_edges,
                 const vector<int> &depth_edges,
                 const vector<string> &order_numbers,
                 const vector<string> &regions);

void region_summary(const vector<char> &stone_codes,
                 const vector<double> &lengths,
                 const vector<double> &depths,
                 const vector<double> &heights,
                 const vector<int> &length_edges,
                 const vector<int> &depth_edges,
                 const vector<string> &order_numbers,
                 const vector<string> &regions);

bool clear_all_vectors(vector<char> &stone_codes,
                       vector<double> &lengths,
                       vector<double> &depths,
                       vector<double> &heights,
                       vector<int> &length_edges,
                       vector<int> &depth_edges,
                       vector<string> &order_numbers,
                       vector<string> &regions);

bool vectors_are_empty(const vector<char> &stone_codes,
                       const vector<double> &lengths,
                       const vector<double> &depths,
                       const vector<double> &heights,
                       const vector<int> &length_edges,
                       const vector<int> &depth_edges,
                       const vector<string> &order_numbers,
                       const vector<string> &regions);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                     *
 *                                                     *
 *                     Function Main                   *
 *                                                     *
 *                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main()
{
    // Define vectors for valid data
    vector<char> stone_codes;
    vector<double> lengths, depths, heights;
    vector<int> length_edges, depth_edges;
    vector<string> order_numbers, regions;
    
    // Define variables
    bool load_success {};
    // Display greeting message
    greet_user();
    
    // Define flag variable
    bool user_quit {};
    
    // Loop while user has not chosen to quit
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
                
                upload_file(file_name, load_success, stone_codes, lengths, depths, heights, length_edges, depth_edges, order_numbers, regions);
                break;
            }
            // Display all details
            case 'A':
                all_details(stone_codes, lengths, depths, heights, length_edges, depth_edges, order_numbers, regions);
                break;
            // Display details of a specific order
            case 'O':
                order_details(stone_codes, lengths, depths, heights, length_edges, depth_edges, order_numbers, regions);
                break;
            // Display summary by region
            case 'R':
                region_summary(stone_codes, lengths, depths, heights, length_edges, depth_edges, order_numbers, regions);
                break;
            // Display summary by stone code
            case 'S':
                stone_summary(stone_codes, lengths, depths, heights, length_edges, depth_edges, order_numbers, regions);
                break;
            // Clear all vectors
            case 'C':
            {
                clear_all_vectors(stone_codes, lengths, depths, heights, length_edges, depth_edges, order_numbers, regions);
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

void upload_file(string file_name,
                 bool &load_success,
                 vector<char> &stone_codes,
                 vector<double> &lengths,
                 vector<double> &depths,
                 vector<double> &heights,
                 vector<int> &length_edges,
                 vector<int> &depth_edges,
                 vector<string> &order_numbers,
                 vector<string> &regions)
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
        
        vector<string> headers {"Ord. Date", "Del. Date", "SC", "Len.", "Dep.", "Hei.", "Len. Edges", "Dep. Edges", "Ord. Num.", "Region"};
        
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
            vector<string> error_messages;
            
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

                error_messages.push_back(DATES_SAME);
            
            // Add error message if dates out of range
            else if (diff_in_months > MONTH_RANGE)
            {
                error_messages.push_back(DATES_OOR);
            }
            
            input_file >> stone_code;
            cout << left;
            cout << setw(2) << stone_code;
            stone_code = toupper(stone_code);   // Capitalize stone code to simplify logic
            
            // Add error message if stone code is invalid
            if (stone_code != 'M' && stone_code != 'G' && stone_code != 'Q')
            {
                error_messages.push_back(STONE_INVALID);
            }
            // Read length, depth and height from input file, print to console, and add error messages if invalid
            
            // Length input, output and validation
            input_file >> length;
            cout << setw(6) << length;
            if (length > UPPER_LIMIT || length < LOWER_LIMIT)
            {
                error_messages.push_back(LENGTH_INVALID);
            }
            
            // Depth input, output and validation
            input_file >> depth;
            cout << setw(6) << depth;
            if (depth > length || depth < LOWER_LIMIT)
            {
                error_messages.push_back(DEPTH_INVALID);
            }
            
            // Height input, output and validation
            input_file >> height;
            cout << setw(6) << height;
            if (height > MAX_PERCENT * depth || height < MIN_PERCENT * depth)
            {
                error_messages.push_back(HEIGHT_INVALID);
            }
            
            // Length edges input, output and validation
            input_file >> num_length_edges;
            cout << setw(2) << num_length_edges;
            if (num_length_edges > MAX_EDGES || num_length_edges < MIN_EDGES)
            {
                error_messages.push_back(LEN_EDGE_INVALID);
            }
            
            // Depth edges input, output and validation
            input_file >> num_depth_edges;
            cout << setw(2) << num_depth_edges;
            if (num_depth_edges > MAX_EDGES || num_depth_edges < MIN_EDGES)
            {
                error_messages.push_back(DEP_EDGE_INVALID);
            }
            
            input_file >> order_number;
            cout << setw(11) << order_number;
            
            input_file >> region;
            cout << setw(7) << region;
            
            // Ignore characters in buffer until a newline is reached
            input_file.ignore(999, '\n');
            
            cout << endl;
            if (error_messages.empty())
            {
                // Increment valid records count
                valid_records ++;
                
                // Add valid data to vectors
                stone_codes.push_back(stone_code);
                lengths.push_back(length);
                depths.push_back(depth);
                heights.push_back(height);
                length_edges.push_back(num_length_edges);
                depth_edges.push_back(num_depth_edges);
                order_numbers.push_back(order_number);
                regions.push_back(region);
                
            }
            else
            {
                // Increment invalid records count
                invalid_records ++;
                
                // Display error messages
                cout << endl;
                for (string message: error_messages)
                {
                    cout << "ERROR: " << message << endl;
                }
                cout << endl;
            }
        }
        cout << right << endl;
        cout << "Valid Entries: " << valid_records << endl;
        cout << "Invalid Entries: " << invalid_records << endl;
        cout << "Total Entries: " << total_records << endl << endl;
        
        if (stone_codes.empty()
            || lengths.empty()
            || depths.empty()
            || heights.empty()
            || length_edges.empty()
            || depth_edges.empty()
            || order_numbers.empty()
            || regions.empty())
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

void all_details(const vector<char> &stone_codes,
                 const vector<double> &lengths,
                 const vector<double> &depths,
                 const vector<double> &heights,
                 const vector<int> &length_edges,
                 const vector<int> &depth_edges,
                 const vector<string> &order_numbers,
                 const vector<string> &regions)
{
    
    // Define calculated variables
    double
        stone_area{},   // Area to be calculated if record is valid
        stone_cost{},   // Stone cost, depends on stone code
        edge_cost{},    // Edge finishing cost, does not depend on stone code
        total_cost{};  // Sum of edge and stone cost
    
    bool no_data = vectors_are_empty(stone_codes, lengths, depths, heights, length_edges, depth_edges, order_numbers, regions);
    
    
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
        
        for(auto i {0}; i < stone_codes.size(); i++)
        {
            cout << stone_codes.at(i);
            cout << setw(6) << lengths.at(i);
            cout << setw(6) << depths.at(i);
            cout << setw(6) << heights.at(i);
            cout << setw(2) << length_edges.at(i);
            cout << setw(2) << depth_edges.at(i);
            cout << setw(11) << order_numbers.at(i);
            cout << setw(7) << regions.at(i);
            
            stone_area = ceil(lengths.at(i) * heights.at(i) * AREA_MULTIPLIER);
            edge_cost = EDGE_RATE * (length_edges.at(i) * lengths.at(i)
                                     + depth_edges.at(i) * depths.at(i));
            switch (stone_codes.at(i))
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
            
            total_cost = edge_cost + stone_cost;
            cout << fixed << setprecision(2);
            cout << setw(7) << stone_area;
            cout << setw(10) << total_cost;
            cout << endl;
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                     *
 *                                                     *
 *            Function Display Order Details           *
 *                                                     *
 *                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void order_details(const vector<char> &stone_codes,
                 const vector<double> &lengths,
                 const vector<double> &depths,
                 const vector<double> &heights,
                 const vector<int> &length_edges,
                 const vector<int> &depth_edges,
                 const vector<string> &order_numbers,
                 const vector<string> &regions)
{
    double
        stone_area{},   // Area to be calculated if record is valid
        stone_cost{},   // Stone cost, depends on stone code
        edge_cost{},    // Edge finishing cost, does not depend on stone code
        total_cost{};  // Sum of edge and stone cost
    
    bool no_data = vectors_are_empty(stone_codes, lengths, depths, heights, length_edges, depth_edges, order_numbers, regions);
    
    if (!no_data)
    {
        string order_number;
        cout << "Enter the order number to search: ";
        cin >> order_number;
        
        int order_index {-1};
        
        for (auto i {0}; i < order_numbers.size(); i++)
        {
            if (order_numbers.at(i) == order_number)
            {
                order_index = i;
                break;
            }
        }
        
        if(order_index != -1)
        {
            cout << stone_codes.at(order_index);
            cout << setw(6) << lengths.at(order_index);
            cout << setw(6) << depths.at(order_index);
            cout << setw(6) << heights.at(order_index);
            cout << setw(2) << length_edges.at(order_index);
            cout << setw(2) << depth_edges.at(order_index);
            cout << setw(11) << order_numbers.at(order_index);
            cout << setw(7) << regions.at(order_index);
            
            stone_area = ceil(lengths.at(order_index) * heights.at(order_index) * AREA_MULTIPLIER);
            edge_cost = EDGE_RATE * (length_edges.at(order_index) * lengths.at(order_index)
                                     + depth_edges.at(order_index) * depths.at(order_index));
            switch (stone_codes.at(order_index))
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

void stone_summary(const vector<char> &stone_codes,
                 const vector<double> &lengths,
                 const vector<double> &depths,
                 const vector<double> &heights,
                 const vector<int> &length_edges,
                 const vector<int> &depth_edges,
                 const vector<string> &order_numbers,
                 const vector<string> &regions)
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
    
    bool no_data = vectors_are_empty(stone_codes, lengths, depths, heights, length_edges, depth_edges, order_numbers, regions);
    
    if (!no_data)
    {
        for(auto i {0}; i < stone_codes.size(); i++)
        {
            stone_area = ceil(lengths.at(i) * heights.at(i) * AREA_MULTIPLIER);
            edge_cost = EDGE_RATE * (length_edges.at(i) * lengths.at(i)
                                     + depth_edges.at(i) * depths.at(i));
            switch (stone_codes.at(i))
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

void region_summary(const vector<char> &stone_codes,
                 const vector<double> &lengths,
                 const vector<double> &depths,
                 const vector<double> &heights,
                 const vector<int> &length_edges,
                 const vector<int> &depth_edges,
                 const vector<string> &order_numbers,
                 const vector<string> &regions)
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
    
    bool no_data = vectors_are_empty(stone_codes, lengths, depths, heights, length_edges, depth_edges, order_numbers, regions);
    
    if (!no_data)
    {
        for(auto i {0}; i < stone_codes.size(); i++)
        {
            stone_area = ceil(lengths.at(i) * heights.at(i) * AREA_MULTIPLIER);
            edge_cost = EDGE_RATE * (length_edges.at(i) * lengths.at(i)
                                     + depth_edges.at(i) * depths.at(i));
            
            switch (stone_codes.at(i))
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
            if (regions.at(i) == "North")
            {
                total_north_orders ++;
                total_north_area += stone_area;
                total_north_cost += stone_cost + edge_cost;
            }
            else if (regions.at(i) == "South")
            {
                total_south_orders ++;
                total_south_area += stone_area;
                total_south_cost += stone_cost + edge_cost;
            }
            else if (regions.at(i) == "East")
            {
                total_east_orders ++;
                total_east_area += stone_area;
                total_east_cost += stone_cost + edge_cost;
            }
            else if (regions.at(i) == "West")
            {
                total_west_orders ++;
                total_west_area += stone_area;
                total_west_cost += stone_cost + edge_cost;
            }
            else if (regions.at(i) == "Other")
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
 *                 Function Clear All Vectors          *
 *                                                     *
 *                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

bool clear_all_vectors(vector<char> &stone_codes,
                       vector<double> &lengths,
                       vector<double> &depths,
                       vector<double> &heights,
                       vector<int> &length_edges,
                       vector<int> &depth_edges,
                       vector<string> &order_numbers,
                       vector<string> &regions)
{
    bool no_data = vectors_are_empty(stone_codes, lengths, depths, heights, length_edges, depth_edges, order_numbers, regions);
    
    bool clearing_successful{};
    if (!no_data)
    {
        stone_codes.clear();
        lengths.clear();
        depths.clear();
        heights.clear();
        length_edges.clear();
        depth_edges.clear();
        order_numbers.clear();
        regions.clear();
        
        if (stone_codes.empty()
            && lengths.empty()
            && depths.empty()
            && heights.empty()
            && length_edges.empty()
            && depth_edges.empty()
            && order_numbers.empty()
            && regions.empty())
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
 *                 Function Vectors Empty              *
 *                                                     *
 *                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

bool vectors_are_empty(const vector<char> &stone_codes,
                       const vector<double> &lengths,
                       const vector<double> &depths,
                       const vector<double> &heights,
                       const vector<int> &length_edges,
                       const vector<int> &depth_edges,
                       const vector<string> &order_numbers,
                       const vector<string> &regions)
{
    bool vectors_empty {};
    if (stone_codes.empty()
        && lengths.empty()
        && depths.empty()
        && heights.empty()
        && length_edges.empty()
        && depth_edges.empty()
        && order_numbers.empty()
        && regions.empty())
    {
        cout << endl;
        cout << "No data has been loaded. Please upload a file to perform this action";
        cout << endl << endl;
        vectors_empty = true;
    }
    return vectors_empty;
}
