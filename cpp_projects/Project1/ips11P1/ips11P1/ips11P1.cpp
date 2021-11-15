/*
 * ips11P1.cpp
 *
 * COSC 051-02 S21
 * Project #1
 *
 * Due on: 03-02-2021
 * Author: Ian Sharff
 *
 * In accordance with the class policies and Georgetown's
 * Honor Code, I certify that, with the exception of the
 * class resources and those items noted below, I have neither
 * given nor received any assistance on this project.
 *
 * References not otherwise commented within the program source code:
 *
 * http://www.cplusplus.com/reference/cmath/
 * 
 */

#include <iostream>
#include <iomanip> /* setprecision, fixed */
#include <string> /* string class */
#include <cmath> /* round */

using namespace std;

int main() {
    const double MARBLE_RATE {92.99}, // Set stone prices per square foot
                 GRANITE_RATE {78.99},
                 QUARTZ_RATE {56.99},
                 LOWER_LIMIT {5.0}, // Set lower and upper limit of the length and depth
                 UPPER_LIMIT {25.0},
                 MIN_PERCENT {58.0}, // Set percent range for height based on depth
                 MAX_PERCENT {80.0},
                 AREA_MULTIPLIER {1.26}, // Set wastage multiplier for stone area
                 EDGE_RATE {4.99}; // Set rate for finished edges per foot
    
    const int MIN_EDGES {0}, // Set minimum and maximum number of length or depth edges
              MAX_EDGES {2};
    
    // Introduce program
    cout << "Thank you for shopping with Claude's Custom Counters!" << endl;
    cout << "Let's calculate the cost of your new counter!" << endl << endl;
    
    // Extract single character from input stream for use in switch statement
    cout << "Choose a material (M - Marble, G - Granite, Q - Quartz): ";
    char stone_code {}; //
    stone_code = toupper(cin.get()); // Convert to uppercase to simplify switch statement
    cin.ignore(50, '\n'); // Ignore characters remaining in input buffer if present
    
    // Define stone_rate and stone_name to be assigned depending on extracted stone_code
    double stone_rate {};
    string stone_name;
    
    // Assign stone_rate and stone_name according to stone code
    switch (stone_code) {
        case 'M' :
            stone_rate = MARBLE_RATE;
            stone_name = "Marble";
            break;
        case 'G' :
            stone_rate = GRANITE_RATE;
            stone_name = "Granite";
            break;
        case 'Q' :
            stone_rate = QUARTZ_RATE;
            stone_name = "Quartz";
            break;
        default : // End program if stone code is invalid
            cout << "Invalid stone choice (" << stone_code << "). Goodbye..." << endl;
            return 0;
    }
    
    // Collect length as a double
    double length {};
    cout << "Enter the length of the counter (";
    cout << LOWER_LIMIT << "' - ";
    cout << UPPER_LIMIT << "'): ";
    cin >> length;
    
    // End program if length outside of specified limits
    if (length > UPPER_LIMIT || length < LOWER_LIMIT) {
        cout << "Length (" << length << ") out of range. Goodbye..." << endl;
        return 0;
    }
    
    // Collect depth as a double
    double depth {};
    cout << "Enter the depth of the counter (";
    cout << LOWER_LIMIT << "' - ";
    cout << length << "'): ";
    cin >> depth;
    
    // End program if depth is under the lower limit or higher than the length
    if (depth > length || depth < LOWER_LIMIT) {
        cout << "Depth (" << depth << ") out of range. Goodbye..." << endl;
        return 0;
    }
    
    // Define upper and lower limits for height based on percentages of depth
    double min_height {MIN_PERCENT / 100 * depth},
           max_height {MAX_PERCENT / 100 * depth},
           height {};
    
    // Collect height as a double
    cout << "Enter the height of the counter (";
    cout << min_height << "' - " << max_height << "'): ";
    cin >> height;
    
    // End program if height outside of specified limits
    if (height > max_height || height < min_height) {
        cout << "Height (" << height << ") out of range. Goodbye..." << endl;
        return 0;
    }
    
    // Collect integer number of length edges to be finished
    int num_length_edges;
    cout << "Enter the number of length edges to be polished (";
    cout << MIN_EDGES << " - " << MAX_EDGES << "): ";
    cin >> num_length_edges;
    
    // End program if outside of specified limits
    if (num_length_edges > MAX_EDGES || num_length_edges < MIN_EDGES) {
        cout << "Invalid number of length edges (" << num_length_edges << "). Goodbye..." << endl;
        return 0;
    }
    
    // Collect integer number of depth edges to be finished
    int num_depth_edges;
    cout << "Enter the number of depth edges to be polished (";
    cout << MIN_EDGES << " - " << MAX_EDGES << "): ";
    cin >> num_depth_edges;
    
    // End program if outside of specified limits
    if (num_depth_edges < MIN_EDGES || num_depth_edges > MAX_EDGES) {
        cout << "Invalid number of depth edges (" << num_depth_edges << "). Goodbye..." << endl;
        return 0;
    }
    
    // Calculate total area required with multiplier rounded to nearest whole number
    double total_area {round(length * height * AREA_MULTIPLIER)};
    // Output dimensions entered by user and calculated required area of stone
    cout << endl << endl;
    cout << "__DIMENSIONS__" << endl << endl;
    cout << "Length : " << length << " ft." << endl;
    cout << "Depth : " << depth << " ft." << endl;
    cout << "Height : " << height << " ft." << endl;
    cout << stone_name << " required : " << total_area << " sq. ft." << endl << endl;
    
    // Calculate costs for stone area, finished edges, and total cost
    double stone_cost {total_area * stone_rate},
           edge_cost {EDGE_RATE * (num_depth_edges * depth + num_length_edges * length)},
           total_cost {stone_cost + edge_cost};
    
    // Output costs
    cout << "____COSTS____" << endl << endl;
    cout << fixed << setprecision(2);
    cout << stone_name << " : " << stone_cost << endl;
    cout << "Edge finishing : " << edge_cost << endl;
    cout << "TOTAL COST : " << total_cost << endl << endl;
    
    // Display exit message
    cout << "Thank you for shopping with Claude's Custom Counters, Inc." << endl;
    return 0;
}
