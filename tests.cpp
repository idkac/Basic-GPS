// #include <iostream>
// #include <sstream>
// #include <string>
// #include <vector>

// void processString(const std::string& str) {
//     std::istringstream iss(str);
//     int num;
//     double dub;
//     std::string word;
//     bool hasInts = false;
//     bool hasStrings = false;

//     // while (iss >> num) {
//     //     hasInts = true;
//     //     std::cout << "Integer: " << num << std::endl;
//     // }
//     while (iss >> dub)
//     {
//         std::cout << "double: " << dub << std::endl;
//     }
//     // Check if the string contains integers


//     // Check if the string contains non-numeric characters
//     iss.clear(); // Clear the error flags
//     iss.seekg(0); // Move the read position to the beginning of the string
//     while (iss >> word) {
//         hasStrings = true;
//         std::cout << "String: " << word << std::endl;
//     }

//     // Process based on the content of the string
//     if (hasInts && hasStrings) {
//         std::cout << "Mixed content: Both integers and strings." << std::endl;
//     } else if (hasInts) {
//         std::cout << "Only integers." << std::endl;
//     } else if (hasStrings) {
//         std::cout << "Only strings." << std::endl;
//     } else {
//         std::cout << "Empty string." << std::endl;
//     }
// }

// int main() {
//     std::vector<std::string> inputStrings;
//     inputStrings.push_back("string test 32.3223");
//     inputStrings.push_back("hello");
//     inputStrings.push_back("test | 23");
//     inputStrings.push_back("");

//     for (const auto& str : inputStrings) {
//         std::cout << "Processing: " << str << std::endl;
//         processString(str);
//         std::cout << std::endl;
//     }

//     return 0;
// }
// #include <iostream>
// #include <string>

// int main() {
//     std::string originalString = "example string with a delimiter";

//     // Find the position of the delimiter 'a'
//     size_t delimiterPos = originalString.find('a');

//     // Extract the substring from the beginning of the original string up to the delimiter
//     std::string substring = originalString.substr(0, delimiterPos);

//     std::cout << "Original string: " << originalString << std::endl;
//     std::cout << "Substring: " << substring << std::endl;

//     return 0;
// }

#include "geopoint.h"
#include "hashmap.h"
#include <vector>
#include "geob.h"
using namespace std;

int main()
{
    GeoDatabase g;
    g.load("testdata.txt");
    GeoPoint p;
    cout << "this worked";
    if (g.get_poi_location("Fox Plaza", p))
    {
        cout << p.sLatitude << " , " << p.sLongitude << endl;
    }
    else if (!g.get_poi_location("Fox Plaza", p))
    {
        cout << "alksdfjlk" << endl; 
    }
}
