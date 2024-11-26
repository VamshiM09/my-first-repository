#include <iostream>
#include <vector>
#include <string>

// Define the Menu class
class Menu {
private:
    std::string name; // Name of the menu item
    std::vector<Menu*> subMenus; // List of sub-menus
    Menu* parent; // Pointer to the parent menu

public:
    // Constructor to initialize the menu with a name and an optional parent
    Menu(const std::string& name, Menu* parent = nullptr)
        : name(name), parent(parent) {}

    // Method to add a sub-menu to the current menu
    void addSubMenu(Menu* subMenu) {
        subMenus.push_back(subMenu);
    }

    // Method to display the current menu and its sub-menus
    void display() {
        std::cout << "Menu: " << name << "\n";
        for (size_t i = 0; i < subMenus.size(); ++i) {
            std::cout << i + 1 << ". " << subMenus[i]->getName() << "\n";
        }
        std::cout << "0. Back\n";
    }

    // Getter method to retrieve the name of the menu
    const std::string& getName() const {
        return name;
    }

    // Method to get a sub-menu based on the index
    Menu* getSubMenu(int index) {
        if (index > 0 && index <= subMenus.size()) {
            return subMenus[index - 1];
        }
        return nullptr;
    }

    // Getter method to retrieve the parent menu
    Menu* getParent() const {
        return parent;
    }
};

// Function to navigate through the menu system
void navigateMenu(Menu* currentMenu) {
    while (true) {
        currentMenu->display(); // Display the current menu
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice; // Get user input

        if (choice == 0) {
            if (currentMenu->getParent() != nullptr) {
                currentMenu = currentMenu->getParent(); // Go back to the parent menu
            }
            else {
                std::cout << "Already at the top level.\n";
            }
        }
        else {
            Menu* nextMenu = currentMenu->getSubMenu(choice); // Get the selected sub-menu
            if (nextMenu != nullptr) {
                currentMenu = nextMenu; // Navigate to the selected sub-menu
            }
            else {
                std::cout << "Invalid choice. Try again.\n";
            }
        }
    }
}

int main() {
    // Create the menu structure
    Menu mainMenu("Main Menu");
    Menu settings("Settings", &mainMenu);
    Menu displaySettings("Display Settings", &settings);
    Menu audioSettings("Audio Settings", &settings);
    Menu media("Media", &mainMenu);
    Menu radio("Radio", &media);
    Menu bluetoothAudio("Bluetooth Audio", &media);

    // Add sub-menus to their respective parents
    mainMenu.addSubMenu(&settings);
    mainMenu.addSubMenu(&media);
    settings.addSubMenu(&displaySettings);
    settings.addSubMenu(&audioSettings);
    media.addSubMenu(&radio);
    media.addSubMenu(&bluetoothAudio);

    // Start navigating from the main menu
    navigateMenu(&mainMenu);

    return 0;
}
