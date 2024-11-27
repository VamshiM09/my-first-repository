#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <string> 
#include <set> 
using namespace std; 

// Define the Control struct 

struct Control { 

    int id; 

    string type; // "button" or "slider" 

    string state; // "visible", "invisible", "disabled" 



    // Default constructor 

    Control() : id(0), type(""), state("") {} 

    // Parameterized constructor 

    Control(int i, const string& t, const string& s) : id(i), type(t), state(s) {} 

}; 


// Helper function to print control details 

void printControl(const Control& control) { 

    cout << "ID: " << control.id << ", Type: " << control.type << ", State: " << control.state << endl; 

} 

void printControls(const vector<Control>& controls) { 

    for_each(controls.begin(), controls.end(), printControl); 

    cout << endl; 

} 

int main() { 

    // Initializing two lists of controls 

    vector<Control> list1 = { 

        {1, "button", "visible"}, 

        {3, "slider", "invisible"}, 

        {5, "button", "disabled"} 

    }; 


    vector<Control> list2 = { 

        {2, "slider", "visible"}, 

        {4, "button", "visible"}, 

        {6, "slider", "disabled"} 

    }; 

  
    // Step 1: Sorting by ID using std::sort 

    sort(list1.begin(), list1.end(), [](const Control& a, const Control& b) { return a.id < b.id; }); 

    sort(list2.begin(), list2.end(), [](const Control& a, const Control& b) { return a.id < b.id; }); 

    cout << "List 1 sorted by ID:" << endl; 

    printControls(list1); 

    cout << "List 2 sorted by ID:" << endl; 

    printControls(list2); 


    // Step 2: Using std::stable_sort to maintain relative order for controls with equal IDs 

    stable_sort(list1.begin(), list1.end(), [](const Control& a, const Control& b) { return a.id < b.id; }); 

    stable_sort(list2.begin(), list2.end(), [](const Control& a, const Control& b) { return a.id < b.id; }); 


    cout << "List 1 stable sorted by ID:" << endl; 

    printControls(list1); 

    cout << "List 2 stable sorted by ID:" << endl; 

    printControls(list2); 

  
    // Step 3: Binary Search using std::lower_bound and std::upper_bound 

    int searchID = 4; 

    auto lower = lower_bound(list2.begin(), list2.end(), searchID, [](const Control& c, int id) { return c.id < id; }); 

    auto upper = upper_bound(list2.begin(), list2.end(), searchID, [](int id, const Control& c) { return id < c.id; }); 

  

    if (lower != list2.end() && lower->id == searchID) { 

        cout << "Control with ID " << searchID << " found at position: " << (lower - list2.begin()) << endl; 

        printControl(*lower); 

    } 

    else { 

        cout << "Control with ID " << searchID << " not found." << endl; 

    } 

  
    // Step 4: Merging two sorted lists using std::merge 

    vector<Control> mergedList(list1.size() + list2.size()); 

    merge(list1.begin(), list1.end(), list2.begin(), list2.end(), mergedList.begin(), [](const Control& a, const Control& b) { return a.id < b.id; }); 

  
    cout << "Merged list:" << endl; 

    printControls(mergedList); 

  
    // Step 5: Using std::inplace_merge to combine controls from two segments in the same list 

    vector<Control> combinedList = list1; 

    combinedList.insert(combinedList.end(), list2.begin(), list2.end()); 

    inplace_merge(combinedList.begin(), combinedList.begin() + list1.size(), combinedList.end(), [](const Control& a, const Control& b) { return a.id < b.id; }); 


    cout << "Inplace merged list:" << endl; 

    printControls(combinedList); 


    // Step 6: Set operations using std::set_union and std::set_intersection 

    set<int> ids1, ids2; 

    for (const auto& control : list1) ids1.insert(control.id); 

    for (const auto& control : list2) ids2.insert(control.id); 


    vector<int> unionIDs(ids1.size() + ids2.size()); 

    auto unionEnd = set_union(ids1.begin(), ids1.end(), ids2.begin(), ids2.end(), unionIDs.begin()); 

    unionIDs.resize(unionEnd - unionIDs.begin()); 

    vector<int> intersectionIDs(min(ids1.size(), ids2.size())); 

    auto intersectionEnd = set_intersection(ids1.begin(), ids1.end(), ids2.begin(), ids2.end(), intersectionIDs.begin()); 

    intersectionIDs.resize(intersectionEnd - intersectionIDs.begin()); 


    cout << "Union of IDs:" << endl; 

    for (int id : unionIDs) cout << id << " "; 

    cout << endl; 


    cout << "Intersection of IDs:" << endl; 

    for (int id : intersectionIDs) cout << id << " "; 

    cout << endl; 

    return 0; 

} 

 