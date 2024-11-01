//
//  router.h
//  Project4 test
//
//  Created by idkac on 3/14/24.
//

#ifndef router_h
#define router_h


#include "base_classes.h"
#include "geodb.h"

using namespace std;

class Router : public RouterBase
{
public:
    Router(const GeoDatabaseBase &dataBase) : m_dataBase(dataBase) {};
    virtual ~Router() {};
    virtual std::vector<GeoPoint> route(const GeoPoint &pt1, const GeoPoint &pt2) const;
    
private:
    const GeoDatabaseBase& m_dataBase;
    struct ComparePairs
    {
        bool operator()(const pair<GeoPoint, double> p1, const pair<GeoPoint, double> p2) const
        {
            double dif1 = p1.second;
            double dif2 = p2.second;
            return dif1 < dif2;
        }
    };
};

#endif /* router_h */
