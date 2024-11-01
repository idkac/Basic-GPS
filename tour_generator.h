//
//  tour_generator.h
//  Project4 test
//
//  Created by idkac on 3/14/24.
//

#ifndef tour_generator_h
#define tour_generator_h

#include "base_classes.h"
#include "hashmap.h"

class TourGenerator: public TourGeneratorBase
{
    public:
        TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router): m_dataBase(geodb), m_routerBase(router) {} ;
    virtual ~TourGenerator() {} ;
        virtual std::vector<TourCommand> generate_tour(const Stops& stops) const;
    
    private:
        std::string findDirection(GeoPoint pt1, GeoPoint pt2) const;
        std::string findTurn(const GeoPoint pt1, const GeoPoint pt2, const GeoPoint pt3) const;
        const GeoDatabaseBase& m_dataBase;
        const RouterBase& m_routerBase;
};

#endif /* tour_generator_h */
