/*
 * ips11P2.cpp
 *
 * COSC 051-02 S21
 * Project #2
 *
 * Due on: 03-17-2021
 * Author: Ian Sharff
 *
 * In accordance with the class policies and Georgetown's
 * Honor Code, I certify that, with the exception of the
 * class resources and those items noted below, I have neither
 * given nor received any assistance on this project.
 *
 * References not otherwise commented within the program source code:
 */
// /Users/iansharff/Desktop/COSC-051/Project2/ips11P2/P2OrdersB.dat
#include <iostream>
#include <fstream> // ifstream
#include <iomanip> // setw, fixed, setfill, setprecision
#include <string>
#include <vector>
#include <cmath> // round

using namespace std;

int main()
{
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

    // Define error messages for invalid records in sales file
    const string DATES_SAME = "The order date is the same as the delivery date.",
                 DATES_OOR = "The delivery date is too far from the order date.", // Delivery date out of range
                 STONE_INVALID = "Invalid stone type",
                 LENGTH_INVALID = "Invalid length.",
                 DEPTH_INVALID = "Invalid depth.",
                 HEIGHT_INVALID = "Invalid height.",
                 LEN_EDGE_INVALID = "Invalid number of length edges.",
                 DEP_EDGE_INVALID = "Invalid number of depth edges.";
    // Define file object and file path string, prompt user to enter file path
    ifstream input_file;
    string file_name;
    cout << "Please input the full path and name of the file: ";
    cin >> file_name;
    
    // Open file to read
    input_file.open(file_name);
    
    string first_line;
    getline(input_file, first_line);
    
    vector<string> headers {"Ord. Date", "Del. Date", "SC", "Len.", "Dep.", "Hei.", "Sq. Ft.", "Total Cost"};

    for (string header: headers)
    {
        cout << header << "  ";
    }
    cout << endl;
    
    // Output dividing line
    cout << setfill('-');
    cout << setw(58) << '-' << endl;
    
    // Variable definitions
    char
        stone_code{}; // Stone character from input file
    double
        length{}, // Dimensions from input file
        depth{},
        height{},
        stone_area{},   // Area to be calculated if record is valid
        stone_cost{},   // Stone cost, depends on stone code
        edge_cost{},    // Edge finishing cost, does not depend on stone code
        total_cost{},   // Sum of edge and stone cost
        total_marble_area{0},   // Accumulators for each stone type for total area used, total stone
        total_marble_cost{0},   // costs and total order count
        total_granite_area{0},
        total_granite_cost{0},
        total_quartz_area{0},
        total_quartz_cost{0};


    int
        order_year {},  // Year, month and day values for order and delivery dates read from
        order_month {}, // input file
        order_day {},
        delivery_year {},
        delivery_month {},
        delivery_day {},
        length_edges {},    // Number of length and depth edges to be finished read from input file
        depth_edges {},
        valid_records {0}, // Accumulators for total records, valid records and invalid records
        invalid_records {0},
        total_records {0},
        dates_same_ec {0},   // Accumulators for error messages (ec = error count)
        dates_oor_ec {0},
        stone_invalid_ec {0},
        length_invalid_ec {0},
        depth_invalid_ec {0},
        height_invalid_ec {0},
        len_edge_invalid_ec {0},
        dep_edge_invalid_ec {0},
        total_ec {0},   // Total error count
        multiple_ec{0}, // Records with multiple errors
        total_marble_orders{0}, // Accumulators for order counts
        total_granite_orders{0},
        total_quartz_orders{0};
    
    
    
    // Extract characters from file until end-of-file is reached
    // and peek member function returns EOF
    while (input_file.peek() != EOF)
    {
        // String vector containing error messages associated with each erroneous record
        vector<string> error_messages;
        // Increment total records accumulator
        total_records++;
        
        // Read order year, month and date from input file
        input_file >> order_year;
        input_file.ignore();
        input_file >> order_month;
        input_file.ignore();
        input_file >> order_day;
        
        // Format date including leading zeroes and print to console
        cout << right << setfill('0');  // Set fill character to '0' and right justify, only for dates
        cout << order_year << '/';
        cout << setw(2) << order_month << '/';
        cout << setw(2) << order_day << ' ';
        
        // Read delivery year, month and date from input file
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
        
        // Calculate difference in months to verify that delivery is not too far from order date
        int diff_in_months = 12 * (delivery_year - order_year) + (delivery_month - order_month);
        
        // Add error message if order date and delivery date are the same
        if ((order_day == delivery_day) && (order_month == delivery_month) && (order_year == delivery_year))
        {
            error_messages.push_back(DATES_SAME);
            dates_same_ec++;
        }
        // Add error message if dates out of range
        else if (diff_in_months > MONTH_RANGE)
        {
            error_messages.push_back(DATES_OOR);
            dates_oor_ec++;
        }
        // Read stone code from input file and print to console
        input_file >> stone_code;
        cout << left; // Set to left justified
        cout << setw(2) << stone_code;
        
        stone_code = toupper(stone_code);   // Capitalize stone code to simplify logic
        // Add error message if stone code is invalid
        if (stone_code != 'M' && stone_code != 'G' && stone_code != 'Q')
        {
            error_messages.push_back(STONE_INVALID);
            stone_invalid_ec++;
        }
        // Read length, depth and height from input file, print to console, and add error messages if invalid
        
        // Length input, output and validation
        input_file >> length;
        cout << setw(6) << length;
        if (length > UPPER_LIMIT || length < LOWER_LIMIT)
        {
            error_messages.push_back(LENGTH_INVALID);
            length_invalid_ec++;
        }
        // Depth input, output and validation
        input_file >> depth;
        cout << setw(6) << depth;
        if (depth > length || depth < LOWER_LIMIT)
        {
            error_messages.push_back(DEPTH_INVALID);
            depth_invalid_ec++;
        }
        // Height input, output and validation
        input_file >> height;
        cout << setw(6) << height;
        if (height > MAX_PERCENT * depth || height < MIN_PERCENT * depth)
        {
            error_messages.push_back(HEIGHT_INVALID);
            height_invalid_ec++;
        }
        // Length edges input, output and validation
        input_file >> length_edges;
        cout << setw(2) << length_edges;
        if (length_edges > MAX_EDGES || length_edges < MIN_EDGES)
        {
            error_messages.push_back(LEN_EDGE_INVALID);
            len_edge_invalid_ec++;
        }
        // Depth edges input, output and validation
        input_file >> depth_edges;
        cout << setw(2) << depth_edges;
        if (depth_edges > MAX_EDGES || depth_edges < MIN_EDGES)
        {
            error_messages.push_back(DEP_EDGE_INVALID);
            dep_edge_invalid_ec++;
        }
        // Ignore characters in buffer until a newline is reached
        input_file.ignore(999, '\n');
        
        
        
        // Perform proper calculations if record is valid
        if (error_messages.empty()) // True if no error messages have been added to vector
        {
            valid_records++; // Increment valid record count
            
            // Calculate stone area and edge finishing cost, both are not dependent on stone type
            stone_area = ceil(length * height * AREA_MULTIPLIER);
            edge_cost = EDGE_RATE * (length_edges * length + depth_edges * depth);
            
            // Calculate stone cost, update accumulators according to stone type
            switch (stone_code)
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
            // Calculate total cost, output stone area and total cost, set precision to two decimal places
            total_cost = edge_cost + stone_cost;
            cout << fixed << setprecision(2);
            cout << setw(7) << stone_area;
            cout << total_cost << endl;
        }
        else    // Execute if record contains an error
        {
            invalid_records++; // Increment invalid records count
            cout << endl;
            for (string message: error_messages) // Output all error messages for given record
            {
                cout << "ERROR: " << message << endl;
                total_ec++; // Increment total error count
            }
            
            if (error_messages.size() > 1) // Increment multiple error count if more than one error message
                multiple_ec++;
            
            cout << endl;
        }
    }
    // Close input file
    input_file.close();
    
    // Format and output totals for each stone
    cout << endl << endl;
    cout << "Counts: Total Records = " << total_records;
    cout << "  Records with Errors = " << invalid_records;
    cout << "  Records without Errors = " << valid_records;
    cout << endl << endl;
    
    // Table and column headers
    cout << right << setw(37) << "TOTALS (Valid Records)" << endl;
    cout << setw(9) << "Stone";
    cout << setw(9) << "Count";
    cout << setw(18) << "Square Feet";
    cout << setw(18) << "Cost ($)" << endl;
    
    // Top separating line
    cout << setfill('-');
    cout << setw(58) << '-' << endl;
    
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
    
    // Bottom separating line
    cout << setfill('-');
    cout << setw(58) << '-' << endl << endl;
    cout << setfill(' ');

    

    // Display total error counts
    cout << setw(30) << "ERROR COUNTS" << endl;
    cout << setfill('-');
    cout << setw(58) << '-' << endl;
    
    cout << DATES_SAME << " : " << dates_same_ec << endl;
    cout << DATES_OOR << " : " << dates_oor_ec << endl;
    cout << STONE_INVALID << " : " << stone_invalid_ec << endl;
    cout << LENGTH_INVALID << " : " << length_invalid_ec << endl;
    cout << DEPTH_INVALID << " : " << depth_invalid_ec << endl;
    cout << HEIGHT_INVALID << " : " << height_invalid_ec << endl;
    cout << LEN_EDGE_INVALID << " : " << len_edge_invalid_ec << endl;
    cout << DEP_EDGE_INVALID << " : " << dep_edge_invalid_ec << endl;
    
    cout << setfill('-');
    cout << setw(58) << '-' << endl;
    cout << "Total errors in file: " << total_ec << endl;
    cout << "Number of records with multiple errors: " << multiple_ec << endl;
    cout << setw(58) << '-' << endl;
    cout << "Thank you for shopping with Claude's Custom Counters!" << endl;
    
    cout << endl;
    return 0;
}
