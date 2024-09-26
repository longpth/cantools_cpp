// cantools_cpp.cpp : Defines the entry point for the application.
//

#include "CANBusManager.hpp"
#include "Parser.hpp"

using namespace std;

int main() {
    // Create CANBusManager instance as a unique_ptr
    auto busManager = std::make_shared<CANBusManager>();

    // Create the Parser with CANBusManager unique_ptr
    Parser parser(busManager); // Transfer ownership to the parser

    // Load database from file
    parser.loadDBC("../../../../DbcFiles/tesla_can.dbc");

    return 0;
}