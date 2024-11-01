//
//  tour_generator.cpp
//  Project4 test
//
//  Created by idkac on 3/11/24.
//

#include "tour_generator.h"
#include "stops.h"
#include "tourcmd.h"
#include "geotools.h"
using namespace std;

vector<TourCommand> TourGenerator::generate_tour(const Stops& stops) const
{
    vector<TourCommand> result;
    
    string poiName;
    string talkingPoints;
    TourCommand poiCommand;
    
    for (int i = 0; i < stops.size(); i++)
    {
        stops.get_poi_data(i, poiName, talkingPoints);
        GeoPoint temp;
        if (!m_dataBase.get_poi_location(poiName, temp)) //check invalid poi stops
        {
            vector<TourCommand> empty;
            return empty;
        }
        else
        {
            GeoPoint pt1;
            GeoPoint pt2;
            m_dataBase.get_poi_location(poiName, pt1);
            poiCommand.init_commentary(poiName, talkingPoints); //push first POI's name and commetnary
            result.push_back(poiCommand);
            
            int tempInt = i + 1;
            if (stops.get_poi_data(tempInt, poiName, talkingPoints)) //we see if there is another POI after this, if there is we will make route
            {
                if (!m_dataBase.get_poi_location(poiName, pt2)) //check poi validity
                {
                    vector<TourCommand> empty;
                    return empty;
                }
                vector <GeoPoint> route = m_routerBase.route(pt1, pt2);
                for (int j = 0; j < route.size(); j++) //iteratre through vector and generate commands
                {
                    if (j < route.size() - 1) //get proceed command
                    {
                        TourCommand direction;
                        GeoPoint point1 = route[j];
                        GeoPoint point2 = route[j+1];
                        direction.init_proceed(findDirection(point1, point2), m_dataBase.get_street_name(point1, point2), distance_earth_miles(point1, point2), point1, point2);
                        result.push_back(direction);
                    }
                    if (j < route.size() - 2) //if there is 2 more points after current then we generate turn
                    {
                        TourCommand direction;
                        GeoPoint point1 = route[j];
                        GeoPoint point2 = route[j+1];
                        GeoPoint point3 = route[j+2];
                        
                        string tempString = findTurn(point1, point2, point3);
                        if (tempString == "left" || tempString == "right")
                        {
                            direction.init_turn(tempString, m_dataBase.get_street_name(point2, point3));
                            result.push_back(direction);
                        }
                    }
                }
            }
        }
    }
    return result;
}

string TourGenerator::findDirection(GeoPoint pt1, GeoPoint pt2) const
{
    double angle = angle_of_line(pt1, pt2);
    if (angle >= 0 && angle < 22.5)
        return "east";
    else if (angle >= 22.5 && angle < 67.5)
        return "northeast";
    else if (angle >= 67.5 && angle < 112.5)
        return "north";
    else if (angle >= 112.5 && angle < 157.5)
        return "northwest";
    else if (angle >= 157.5 && angle < 202.5)
        return "west";
    else if (angle >= 202.5 && angle < 247.5)
        return "southwest";
    else if (angle >= 247.5 && angle < 292.5)
        return "south";
    else if (angle >= 292.5 && angle < 337.5)
        return "southeast";
    else
        return "east";
}

string TourGenerator::findTurn(const GeoPoint pt1, const GeoPoint pt2, const GeoPoint pt3) const
{
    double angle = angle_of_turn(pt1, pt2, pt3);
    if (angle >=1 && angle < 180)
        return "left";
    else if (angle >= 180 && angle <= 359)
        return "right";
    else
        return "";
}
