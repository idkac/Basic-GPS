//
//  geodb.cpp
//  Project4 test
//
//  Created by idkac on 3/14/24.
//

#include "geodb.h"
#include "base_classes.h"
#include "geopoint.h"
#include "geotools.h"
#include "hashmap.h"
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

bool GeoDatabase::load(const string &map_data_file)
{
    std::ifstream inf(map_data_file); //check if you can get the map.txt file
    std::cout << map_data_file << std::endl;
    if (!inf)
    {
        cerr << "Error getting file" << endl;
        return false;
    }
    string line;
    string streetName;
    bool hasName = false;
    while(getline(inf, line))
    {
        istringstream iss(line);
        string coord1, coord2, coord3, coord4;

        if (!hasName) //checks if you have gotten a street name, if not then you get street name and skip
        {
            streetName = line;
            hasName = true;
        }
        else
        {
            hasName = false; //if we got a street name then we get the coords under it
            while (iss >> coord1 >> coord2 >> coord3 >> coord4)
            {
                GeoPoint beginning(coord1, coord2);
                GeoPoint end(coord3, coord4);
                roadNames.insert(beginning.to_string() + end.to_string(), streetName); //insert both paths into roadnames
                roadNames.insert(end.to_string() + beginning.to_string(), streetName);
                connections[beginning.to_string()].push_back(end); //insert both into connections
                connections[end.to_string()].push_back(beginning);

                string newLine; //get teh line after which has the number of POIs
                getline(inf, newLine);
                int temp = stoi(newLine);

                if (temp > 0) //if there are pois
                {
                    GeoPoint mid = midpoint(beginning, end); //create and insert everything for midpoint
                    roadNames.insert(mid.to_string() + beginning.to_string(), streetName);
                    roadNames.insert(mid.to_string() + end.to_string(), streetName);
                    roadNames.insert(beginning.to_string() + mid.to_string(), streetName);
                    roadNames.insert(end.to_string() + mid.to_string(), streetName);
                    
                    connections[mid.to_string()].push_back(beginning);
                    connections[mid.to_string()].push_back(end);
                    connections[beginning.to_string()].push_back(mid);
                    connections[end.to_string()].push_back(mid);

                    for (int i = 0; i < temp; i++) //for loop to repeat for rest of the pois
                    {
                        getline(inf, newLine);
                        string poiName = newLine.substr(0, newLine.find('|')); //get all the important parts
                        string poiLocation = newLine.substr(newLine.find('|') + 1, newLine.length());
                        string poiCoord1 = poiLocation.substr(0, poiLocation.find(' '));
                        string poiCoord2 = poiLocation.substr(poiLocation.find(' ') + 1, poiLocation.length());
                        
                        GeoPoint poi(poiCoord1, poiCoord2);
                        pointsOfInterest.insert(poiName, poi);
                        connections[mid.to_string()].push_back(poi);
                        connections[poi.to_string()].push_back(mid);
                        roadNames.insert(mid.to_string() + poi.to_string(), "a path");
                        roadNames.insert(poi.to_string() + mid.to_string(), "a path");
                    }
                }
            }
        }
    }
    return true;
}

bool GeoDatabase::get_poi_location(const std::string &poi, GeoPoint &point) const
{
    const GeoPoint* temp = pointsOfInterest.find(poi);
    if (temp == nullptr)
        return false;
    else
        point = *temp;

    return true;
}

vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint &pt) const
{
    const vector<GeoPoint>* temp = connections.find(pt.to_string());
    if (temp == nullptr)
    {
        vector<GeoPoint> empty;
        return empty;
    }
    return *temp;
}

string GeoDatabase::get_street_name(const GeoPoint &pt1, const GeoPoint &pt2) const
{
    const string* temp = roadNames.find(pt1.to_string() + pt2.to_string());
    if (temp == nullptr)
    {
        return "";
    }
    return *temp;
}
