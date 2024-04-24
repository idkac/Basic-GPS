#ifndef GEOB_H_
#define GEOB_H_

#include "base_classes.h"
#include "geopoint.h"
#include "hashmap.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class GeoDatabase: public GeoDatabaseBase
{
public:
GeoDatabase() : roadNames(0.2), connections(0.2), pointsOfInterest(0.75) {} ;
    virtual ~GeoDatabase() {};
    virtual bool load(const std::string& map_data_file);
    virtual bool get_poi_location(const std::string& poi,
                                  GeoPoint& point) const;
    virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt)
        const;
    virtual std::string get_street_name(const GeoPoint& pt1,
                                        const GeoPoint& pt2) const;
private:
    void addPointToConnections(vector<GeoPoint>* vector, GeoPoint point);
    void midpointAdd(GeoPoint point, GeoPoint pointToAdd);
    HashMap<GeoPoint> pointsOfInterest; //pois to latitude longtiude
    HashMap<vector<GeoPoint> > connections; //each coordinate will have a vector of more coordinates that it is connected to
    HashMap<string> roadNames; //have each coordinate as a string map to the roadname
};

#endif // GEOB_H_
