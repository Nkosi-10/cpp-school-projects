#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

// Struct to hold each resource's data
struct Resource {
    int resourceID;
    string resourceName;
    int quantity;
    double unitPrice;
    string location;

    // Default constructor
    Resource() : resourceID(0), quantity(0), unitPrice(0.0) {}
};

// Read all resources from a file and return them as a vector
vector<Resource> readResourcesFromFile(const string& filename) {
    vector<Resource> resources;
    ifstream inFile(filename);
    string line;

    while (getline(inFile, line)) {
        Resource res;
        size_t pos = 0, prev = 0;

        // Parse line using '|' as delimiter
        pos = line.find('|');
        if (pos == string::npos) continue;
        res.resourceID = stoi(line.substr(prev, pos - prev));
        prev = pos + 1;

        pos = line.find('|', prev);
        res.resourceName = line.substr(prev, pos - prev);
        prev = pos + 1;

        pos = line.find('|', prev);
        res.quantity = stoi(line.substr(prev, pos - prev));
        prev = pos + 1;

        pos = line.find('|', prev);
        res.unitPrice = stod(line.substr(prev, pos - prev));
        prev = pos + 1;

        res.location = line.substr(prev);
        resources.push_back(res);
    }

    inFile.close();
    return resources;
}

// Write all resource data back to file
void writeResourcesToFile(const string& filename, const vector<Resource>& resources) {
    ofstream outFile(filename);
    for (const auto& res : resources) {
        outFile << res.resourceID << "|" << res.resourceName << "|" << res.quantity << "|"
                << fixed << setprecision(2) << res.unitPrice << "|" << res.location << "\n";
    }
    outFile.close();
}

// Helper function to get valid integer input
int getIntInput(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        cin >> val;
        if (cin.fail()) {
            cout << "Invalid input. Try again." <<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
    }
}

// Helper function to get valid decimal input
double getDoubleInput(const string& prompt) {
    double val;
    while (true) {
        cout << prompt;
        cin >> val;
        if (cin.fail()) {
            cout << "Invalid input. Try again." <<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
    }
}

// Add a new resource
void addResource(vector<Resource>& resources) {
    Resource res;
    int maxID = 0;

    // Find highest existing ID
    for (const auto& r : resources) maxID = max(maxID, r.resourceID);
    res.resourceID = maxID + 1;

    // Get input from user
    cout << "Enter Resource Name: ";
    getline(cin, res.resourceName);
    res.quantity = getIntInput("Enter Quantity: ");
    res.unitPrice = getDoubleInput("Enter Unit Price: ");
    cout << "Enter Location: ";
    getline(cin, res.location);

    // Add to list
    resources.push_back(res);
    cout << "Resource added." <<endl;
}

// Update an existing resource by ID
void updateResource(vector<Resource>& resources) {
    int id = getIntInput("Enter Resource ID to update: ");
    for (auto& res : resources) {
        if (res.resourceID == id) {
            cout << "Enter new name (or press enter to skip): ";
            string name;
            getline(cin, name);
            if (!name.empty()) res.resourceName = name;

            int qty = getIntInput("Enter new quantity (0 to skip): ");
            if (qty != 0) res.quantity = qty;

            double price = getDoubleInput("Enter new unit price (0 to skip): ");
            if (price != 0.0) res.unitPrice = price;

            cout << "Enter new location (or press enter to skip): ";
            string loc;
            getline(cin, loc);
            if (!loc.empty()) res.location = loc;

            cout << "Resource updated." <<endl;
            return;
        }
    }
    cout << "Resource not found." <<endl;
}

// Delete a resource by ID
void deleteResource(vector<Resource>& resources) {
    int id = getIntInput("Enter Resource ID to delete: ");
    for (auto it = resources.begin(); it != resources.end(); ++it) {
        if (it->resourceID == id) {
            resources.erase(it);
            cout << "Resource deleted." <<endl;
            return;
        }
    }
    cout << "Resource not found. " <<endl;
}

// Search resources by ID, Name, or Location
void searchResource(const vector<Resource>& resources) {
    cout << "Search by: 1-ID, 2-Name, 3-Location: ";
    int choice = getIntInput("");
    vector<Resource> results;

    if (choice == 1) {
        int id = getIntInput("Enter ID: ");
        for (const auto& res : resources)
            if (res.resourceID == id) results.push_back(res);
    } else if (choice == 2) {
        string name;
        cout << "Enter name: ";
        getline(cin, name);
        for (const auto& res : resources)
            if (res.resourceName.find(name) != string::npos) results.push_back(res);
    } else if (choice == 3) {
        string loc;
        cout << "Enter location: ";
        getline(cin, loc);
        for (const auto& res : resources)
            if (res.location.find(loc) != string::npos) results.push_back(res);
    }

    // Show results
    if (results.empty()) {
        cout << "No results found. " <<endl;
    } else {
        for (const auto& res : results) {
            cout << "ID: " << res.resourceID
                 << ", Name: " << res.resourceName
                 << ", Qty: " << res.quantity
                 << ", Price: " << res.unitPrice
                 << ", Location: " << res.location <<endl;
        }
    }
}

// Display all resource data
void displayResources(const vector<Resource>& resources) {
    cout << "\n--- All Resources --- " <<endl;
    for (const auto& res : resources) {
        cout << "ID: " << res.resourceID
             << ", Name: " << res.resourceName
             << ", Qty: " << res.quantity
             << ", Price: " << fixed << setprecision(2) << res.unitPrice
             << ", Location: " << res.location <<endl;
    }
}

// Main menu loop
int main() {
    string filename = "resources.txt";  // File to save/load resource data
    vector<Resource> resources = readResourcesFromFile(filename);  // Load data at start
    int choice;

    do {
        // Show menu
        cout << "\n--- Disaster Relief Resource Management --- " <<endl;
        cout << "1. Add Resource " <<endl;
        cout << "2. Update Resource" <<endl;
        cout << "3. Delete Resource " <<endl;
        cout << "4. Search Resource " <<endl;
        cout << "5. Display All " <<endl;
        cout << "6. Exit\n";
        choice = getIntInput("Choose option: ");

        // Handle menu selection
        switch (choice) {
            case 1: addResource(resources); break;
            case 2: updateResource(resources); break;
            case 3: deleteResource(resources); break;
            case 4: searchResource(resources); break;
            case 5: displayResources(resources); break;
            case 6: cout << "Goodbye!" <<endl; break;
            default: cout << "Invalid option! "<<endl;
        }

        // Save after changes
        if (choice >= 1 && choice <= 4)
            writeResourcesToFile(filename, resources);

    } while (choice != 6);  // Repeat until exit

    return 0;
}

