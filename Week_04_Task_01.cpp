#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <string> 
using namespace std; 

  

// Define the Control struct 

struct Control { 

    int id; 

    string type; // "button" or "slider" 

    string state; // "visible", "invisible", or "disabled" 

  

    // Constructor for easy initialization 

    Control(int i, const string& t, const string& s) : id(i), type(t), state(s) {} 

}; 

// Helper function to print control details 

void printControl(const Control& control) { 

    cout << "ID: " << control.id << ", Type: " << control.type << ", State: " << control.state << endl; 

} 

  

int main() { 

    // Initialize the vector with sample controls 

    vector<Control> controls = { 

        {1, "button", "visible"}, 

        {2, "slider", "invisible"}, 

        {3, "button", "disabled"}, 

        {4, "slider", "visible"}, 

        {5, "button", "visible"}, 

        {6, "slider", "visible"}, 

        {7, "button", "invisible"}, 

        {8, "slider", "disabled"}, 

         

    }; 

    // Using for_each to iterate through all controls and print their details 

    cout << "All Controls:" << endl; 

    for_each(controls.begin(), controls.end(), printControl); 

    // Using find_if to find a control with a specific ID 

    int searchID = 5; 

    auto it = find_if(controls.begin(), controls.end(), [searchID](const Control& c) { return c.id == searchID; }); 

    if (it != controls.end()) { 

        cout << "Control with ID " << searchID << " found: "; 

        printControl(*it); 

    } 

    else { 

        cout << "Control with ID " << searchID << " not found." << endl; 

    } 

    // Using find_if to find the first invisible control 

    auto invisibleIt = find_if(controls.begin(), controls.end(), [](const Control& c) { return c.state == "invisible"; }); 

    if (invisibleIt != controls.end()) { 

        cout << "First invisible control found: "; 

        printControl(*invisibleIt); 

    } 

    else { 

        cout << "No invisible control found." << endl; 

    } 

    // Using adjacent_find to check for consecutive controls with the same state 

    auto adjacentIt = adjacent_find(controls.begin(), controls.end(), [](const Control& c1, const Control& c2) { return c1.state == c2.state; }); 

    if (adjacentIt != controls.end() && (adjacentIt + 1) != controls.end()) { 

        cout << "Consecutive controls with the same state found:" << endl; 

        printControl(*adjacentIt); 

        printControl(*(adjacentIt + 1)); 

    } 

    else { 

        cout << "No consecutive controls with the same state found." << endl; 

    } 

  

    // Using count_if to count the number of visible controls 

    int visibleCount = count_if(controls.begin(), controls.end(), [](const Control& c) { return c.state == "visible"; }); 

    cout << "Number of visible controls: " << visibleCount << endl; 

  

    // Using count_if to count sliders that are disabled 

    int disabledSlidersCount = count_if(controls.begin(), controls.end(), [](const Control& c) { return c.type == "slider" && c.state == "disabled"; }); 

    cout << "Number of disabled sliders: " << disabledSlidersCount << endl; 

    return 0; 

} 

 