#include "geob.h"
#include "base_classes.h"
#include "geopoint.h"
#include "geotools.h"
#include "hashmap.h"
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

void GeoDatabase::addPointToConnections(vector<GeoPoint>* vector, GeoPoint point)
{
    if (vector == nullptr)
    {
        vector = new std::vector<GeoPoint>;
        vector -> push_back(point);
        connections.insert(point.to_string(), *vector);
    }
    else
        vector -> push_back(point);
}

void GeoDatabase::midpointAdd(GeoPoint point, GeoPoint pointToAdd)
{
    vector<GeoPoint>* temp = connections.find(point.to_string());
    temp -> push_back(pointToAdd);
}

bool GeoDatabase::load(const string &map_data_file)
{
    std::ifstream inf(map_data_file);
    std::cout << map_data_file << std::endl;
    if (!inf)
    {
        cerr << "tjhis is not working" << endl;
        return false;
    }
    string line;
    string streetName;
    while(getline(inf, line))
    {
        istringstream iss(line);
        string coord1, coord2, coord3, coord4;
        bool hasName = false;

        if (!hasName)
        {
            streetName = line;
            hasName = true;
        }
        else
        {
            hasName = false;
            while (iss >> coord1 >> coord2 >> coord3 >> coord4)
            {
                GeoPoint point(coord1, coord2);
                GeoPoint point2(coord3, coord4);
                roadNames.insert(point.to_string() + point2.to_string(), streetName);
                vector<GeoPoint>* tempVector = connections.find(point.to_string());
                vector<GeoPoint>* tempVector2 = connections.find(point2.to_string());

                addPointToConnections(tempVector, point2);
                addPointToConnections(tempVector2, point);

                string newLine;
                getline(inf, newLine);
                int temp = stoi(newLine);

                while (temp > 0)
                {
                    getline(inf, newLine);
                    replace(newLine.begin(), newLine.end(), '|', ' ');
                    GeoPoint mid = midpoint(point, point2);
                    roadNames.insert(mid.to_string(), streetName);
                    vector<GeoPoint>* midVector = connections.find(mid.to_string());
                    addPointToConnections(midVector, mid);
                    midpointAdd(mid, point);
                    midpointAdd(mid, point2);

                    istringstream iss(newLine);
                    string point1, point2, POIname;

                    while (iss >> POIname >> point1 >> point2)
                    {
                        GeoPoint poi(point1, point2);
                        pointsOfInterest.insert(POIname, point);
                        roadNames.insert(poi.to_string(), streetName);
                        vector<GeoPoint>* poiVector = connections.find(poi.to_string());
                        addPointToConnections(poiVector, poi);
                        midpointAdd(mid, poi);
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
    return *temp;
}

string GeoDatabase::get_street_name(const GeoPoint &pt1, const GeoPoint &pt2) const
{
    const string* temp = roadNames.find(pt1.to_string() + pt2.to_string());
    return *temp;
}
