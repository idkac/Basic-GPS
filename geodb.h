//
//  geodb.h
//  Project4 test
//
//  Created by idkac on 3/14/24.
//

#ifndef geodb_h
#define geodb_h

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
GeoDatabase() {} ;
    virtual ~GeoDatabase() {};
    virtual bool load(const std::string& map_data_file);
    virtual bool get_poi_location(const std::string& poi,
                                  GeoPoint& point) const;
    virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt)
        const;
    virtual std::string get_street_name(const GeoPoint& pt1,
                                        const GeoPoint& pt2) const;
private:
    HashMap<GeoPoint> pointsOfInterest; //pois to latitude longtiude
    HashMap<vector<GeoPoint> > connections; //each coordinate will have a vector of more coordinates that it is connected to
    HashMap<string> roadNames; //have each coordinate as a string map to the roadname
};


#endif /* geodb_h */
