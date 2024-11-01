#include "router.h"
#include <queue>
#include <vector>
#include "hashmap.h"
#include "geotools.h"
#include "geopoint.h"
#include "geodb.h"

std::vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const
{
    priority_queue<pair<GeoPoint, double>, vector<pair<GeoPoint, double>>, ComparePairs> places; //priority queue to keep all the pairs of geopoints and distance from origin
    HashMap<double> distance; //vector to keep track of distances
    HashMap< vector<GeoPoint> > currentPath; //path taken from origin
    HashMap<bool> hasVisited; //keeps track of places that havent been visited yet

    places.push({pt1 , 0}); //start the program with origin poitn
    distance[pt1.to_string()] = 0;
    currentPath[pt1.to_string()].push_back(pt1);
    while (!places.empty()) //whiel there are still places to check
    {
        GeoPoint temp = places.top().first;
        places.pop();
        
        if (temp.to_string() == pt2.to_string()) //found endpoint so return the path
            return currentPath[temp.to_string()];

        if (hasVisited[temp.to_string()]) //if we have visisted then we skip this point
            continue;
        
        hasVisited[temp.to_string()] = true;
        
        for (GeoPoint connected : m_dataBase.get_connected_points(temp)) //get all points connected to this point
        {
            double tempLength = distance_earth_miles(connected, temp); //get distance from point to current point

            if (hasVisited[connected.to_string()] && (distance[connected.to_string()] > tempLength + distance[temp.to_string()])) //if we have visited but the length is smaller, then we replace it
            {
                currentPath[connected.to_string()] = currentPath[temp.to_string()];
                currentPath[connected.to_string()].push_back(connected);
                places.push({ connected, distance[connected.to_string()]});
                distance[connected.to_string()] = tempLength + distance[temp.to_string()];
            }
            
            else if (!hasVisited[connected.to_string()]) //if we havent analyzed it
            {
                currentPath[connected.to_string()].clear();
                
                for (vector<GeoPoint>::iterator it = currentPath[temp.to_string()].begin(); it < currentPath[temp.to_string()].end(); it++)
                                currentPath[connected.to_string()].push_back(*(it));
                
                currentPath[connected.to_string()].push_back(connected);
                places.push({ connected, distance[connected.to_string()] });
                distance[connected.to_string()] = tempLength + distance[temp.to_string()];
            }

            else //distance too long so we dont do anything
                continue;
        }
        
        hasVisited[temp.to_string()] = true;
        
    }

    vector<GeoPoint> noPath; //case where there is no valid route
    return noPath;
    
}

