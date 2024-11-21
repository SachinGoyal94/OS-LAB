#include <iostream> 
using namespace std; 
const int MESSAGE_COUNT = 5;  // Number of messages 
// Function to send messages 
void sender(int messages[]) { 
for (int i = 0; i < MESSAGE_COUNT; i++) { 
messages[i] = i + 1;  // Sending message (just assigning a value) 
cout << "Sender: Sent message " << messages[i] << endl; 
} 
} 
// Function to receive messages 
void receiver(int messages[]) { 
for (int i = 0; i < MESSAGE_COUNT; i++) { 
cout << "Receiver: Received message " << messages[i] << endl;  // Receiving message 
} 
} 
int main() { 
int messages[MESSAGE_COUNT];  // Simulate a message queue with an array 
sender(messages);             
receiver(messages);           
return 0; 
} 