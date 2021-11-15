#include<iostream>

using namespace std;

int main() {
    
    cout << "Welcome to Julia's Calculator!" << endl;
    cout << "Unfortunately, I am under construction." << endl;
    cout << "At this time, I can only add." << endl << endl;
    
    cout << "What is the first number of your expression?" << endl;
    int num1;
    cin >> num1;
    
    cout << "What do you want to add to that number?" << endl;
    
    int num2;
    cin >> num2;
    
    int total = num1 + num2;
    
    cout << "Do you want to add anything else to this total? (y/n)" << endl;
    char answer;
    cin >> answer;
    
    while (answer == 'y'){
        cout << "What else do you want to add?" << endl;
        int num;
        cin >> num;
        total += num;
        
        cout << "Do you want to add anything else? (y/n)" << endl;
        cin >> answer;
    }
    
    cout << "Your total is " << total << "." << endl;
    cout << "Thanks for using Julia's Calculator. Bye!" << endl;
    
    return 0;
    
}
