#include <iostream> 
#include <vector> 
#include <set> 
#include <algorithm> // for copy and std::find 
#include <iterator> // for back_inserter 
using namespace std; 

  

int main() { 

    // Step 1: Populate Containers 

    vector<string> dynamicWidgets = { "Speedometer", "Tachometer", "FuelGauge", "OilPressure", "BatteryVoltage" }; 

    set<string> staticWidgets = { "Logo", "WarningLights" }; 
    // Step 2: Use Iterators 
    // Print all dynamic widgets using an iterator 

    cout << "Dynamic Widgets:" << endl; 

    for (auto it = dynamicWidgets.begin(); it != dynamicWidgets.end(); ++it) { 

        cout << *it << endl; 

    } 

    // Check if a specific widget (e.g., "WarningLights") is in the set using set::find 

    string searchWidget = "WarningLights"; 

    auto findIt = staticWidgets.find(searchWidget); 

    if (findIt != staticWidgets.end()) { 

        cout << searchWidget << " is in static widgets." << endl; 

    } 

    else { 

        cout << searchWidget << " is not in static widgets." << endl; 

    } 

    // Step 3: Advanced Iteration 

    // Combine both containers into a vector<string> using copy 

    vector<string> allWidgets; 

    allWidgets.reserve(dynamicWidgets.size() + staticWidgets.size()); // Reserve space for efficiency 

    copy(dynamicWidgets.begin(), dynamicWidgets.end(), back_inserter(allWidgets)); 

    copy(staticWidgets.begin(), staticWidgets.end(), back_inserter(allWidgets)); 


    // Use find to locate a specific widget in the combined container 

    string searchCombinedWidget = "Tachometer"; 

    auto combinedFindIt = find(allWidgets.begin(), allWidgets.end(), searchCombinedWidget); 

    if (combinedFindIt != allWidgets.end()) { 

        cout << searchCombinedWidget << " is in the combined widget list." << endl; 

    } 

    else { 

        cout << searchCombinedWidget << " is not in the combined widget list." << endl; 

    } 


    // Output Results 

    cout << "All Widgets:" << endl; 

    for (const auto& widget : allWidgets) { 

        cout << widget << endl; 

    } 

    return 0; 

} 