#include <iostream> 
using namespace std; 
const int MEMORY_SIZE = 100;  // Total memory size 
int memory[MEMORY_SIZE];      // Array representing memory blocks 
// Function to display memory 
void displayMemory() 
{ 
    cout << "Memory Allocation: "; 
    for (int i = 0; i < MEMORY_SIZE; i++) 
    { 
        if (memory[i] != 0) 
        { 
            cout << memory[i] << " "; 
        } 
        else 
        { 
            cout << "- ";  // Represents free space 
        }    
    } 
    cout << endl; 
} 
// First Fit Strategy 
void firstFit(int size) 
{ 
    bool allocated = false; 
    for (int i = 0; i < MEMORY_SIZE; i++) 
    { 
        if (memory[i] == 0) 
        {  // Find free space 
            int j = i; 
            while (j < MEMORY_SIZE && memory[j] == 0 && (j - i) < size) 
            { 
                j++; 
            } 
            if (j - i >= size) 
            { 
                for (int k = i; k < i + size; k++) 
                { 
                    memory[k] = size;  // Allocate memory 
                } 
                cout << "Memory allocated using First Fit." << endl; 
                allocated = true; 
                break; 
            } 
        } 
    } 
    if (!allocated) 
    { 
        cout << "Not enough memory for this allocation using First Fit!" << endl; 
    } 
} 
// Best Fit Strategy 
void bestFit(int size) 
{ 
    int bestStart = -1, bestSize = MEMORY_SIZE + 1; 
    for (int i = 0; i < MEMORY_SIZE; i++) 
    { 
        if (memory[i] == 0) 
        {  // Find free space 
            int j = i; 
            while (j < MEMORY_SIZE && memory[j] == 0 && (j - i) < size) 
            { 
                j++; 
            } 
            if (j - i >= size && j - i < bestSize)  
            { 
                bestSize = j - i; 
                bestStart = i; 
            } 
        } 
    } 
    if (bestStart != -1) 
    { 
        for (int i = bestStart; i < bestStart + size; i++) 
        { 
            memory[i] = size;  // Allocate memory 
        } 
        cout << "Memory allocated using Best Fit." << endl; 
    } 
    else 
    { 
        cout << "Not enough memory for this allocation using Best Fit!" << endl; 
    } 
} 
// Worst Fit Strategy 
void worstFit(int size) 
{ 
    int worstStart = -1, worstSize = -1; 
    for (int i = 0; i < MEMORY_SIZE; i++) 
    { 
        if (memory[i] == 0) 
        {  // Find free space 
                int j = i; 
            while (j < MEMORY_SIZE && memory[j] == 0 && (j - i) < size) 
            { 
                j++; 
            } 
            if (j - i >= size && j - i > worstSize) 
            { 
                worstSize = j - i; 
                worstStart = i; 
            } 
        } 
    } 
    if (worstStart != -1) 
    { 
        for (int i = worstStart; i < worstStart + size; i++) 
        { 
            memory[i] = size;  // Allocate memory 
        } 
        cout << "Memory allocated using Worst Fit." << endl; 
    } 
    else 
    { 
        cout << "Not enough memory for this allocation using Worst Fit!" << endl; 
    } 
} 
int main() { 
// Initialize memory as free 
for (int i = 0; i < MEMORY_SIZE; i++) 
{ 
    memory[i] = 0; 
} 
int choice, size; 
while (true) 
{ 
    // Menu for the user 
    cout << "\nMemory Allocation Strategies:\n"; 
    cout << "1. First Fit\n"; 
    cout << "2. Best Fit\n"; 
    cout << "3. Worst Fit\n"; 
    cout << "4. Exit\n"; 
    cout << "Choose an option: "; 
    cin >> choice; 
    if (choice == 4) { 
    cout << "Exiting program.\n"; 
    break; 
    } 
    cout << "Enter the memory size to allocate: "; 
    cin >> size; 
    // Choose the allocation strategy 
    switch (choice) { 
    case 1: 
    firstFit(size); 
    break; 
    case 2: 
    bestFit(size); 
    break; 
    case 3: 
    worstFit(size); 
    break; 
    default: 
    cout << "Invalid choice. Please try again.\n"; 
    continue; 
    } 
    // Display the current state of memory 
    displayMemory(); 
} 
return 0; 
}