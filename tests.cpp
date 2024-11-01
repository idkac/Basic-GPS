////
////  tests.cpp
////  Project4 test
////
////  Created by idkac on 3/11/24.
////
//
#include "tour_generator.h"
#include "geopoint.h"
#include "geotools.h"
#include "hashmap.h"
#include <vector>
#include "geodb.h"
#include "router.h"
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    GeoDatabase g;
    g.load("/Users/idkac/Desktop/Coding Projects/ucla cs32/Project4/Project4 test/mapdata.txt");
    Router temp(g);
    GeoPoint p1("34.0628867", "-118.4470365");
    GeoPoint p2("34.0625329", "-118.4470263");
    GeoPoint p3("34.0624128", "-118.4470197");
    
    for (GeoPoint temp1 : temp.route(p1, p2))
    {
        cout << temp1.to_string() << endl;
    }
    
//    Stops tempStop;
//    tempStop.load("/Users/idkac/Desktop/Coding Projects/ucla cs32/Project4/Project4 test/stops.txt");
//    TourGenerator tour(g, temp);
//    vector<TourCommand> tourCommands = tour.generate_tour(tempStop);
    cout << angle_of_turn(p1, p2, p3) << endl;
    
}


