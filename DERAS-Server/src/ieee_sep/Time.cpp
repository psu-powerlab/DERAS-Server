///////////////////////////////////////////////////////////
//  Time.cpp
//  Implementation of the Class Time
//  Created on:      13-Apr-2020 2:51:45 PM
//  Original author: kholbroo
///////////////////////////////////////////////////////////

#include <iostream>
//#include <iomanip>
//#include <ctime>
//#include <chrono>
#include "ieee_sep/Time.h"
#include "boost/date_time/time_zone_base.hpp"
#include "boost/date_time/local_time/local_time.hpp"
#include "boost/date_time/posix_time/posix_time.hpp" //include all types plus i/o

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
  using namespace boost::gregorian;
  using namespace boost::local_time;
  using namespace boost::posix_time;

Time::Time() : Resource("\\tm"), pollRate(900)
{
    ptime lt(second_clock::local_time());
    ptime ut(second_clock::universal_time());
    //setup some timezones for creating and adjusting times
    //first time zone uses the time zone file for regional timezone definitions
    tz_database tz_db;
    tz_db.load_from_file("doc/date_time_zonespec.csv");
    time_zone_ptr pst_tz = tz_db.time_zone_from_region("America/Los_Angeles");
    local_date_time ldt(lt,pst_tz);

    currentTime = to_time_t(ut);
    dstEndTime = to_time_t(pst_tz->dst_local_end_time(ldt.date().year()));
    dstOffset = (pst_tz->dst_offset()).total_seconds();
    dstStartTime = to_time_t(pst_tz->dst_local_start_time(ldt.date().year()));
    localTime = to_time_t(lt);
    quality = 7;
    tzOffset = (pst_tz->base_utc_offset()).total_seconds();

    #ifdef TEST
        Time::Print();
    #endif // TEST
}



Time::~Time()
{
    // do nothing
}

boost::property_tree::ptree Time::serialize()
{
    boost::property_tree::ptree pt;
    pt.put("Time.<xmlattr>.pollRate", pollRate);
    pt.put("Time.<xmlattr>.href", href);
    pt.put("Time.<xmlattr>.xmlns", xmlns);
    pt.put("Time.currentTime", currentTime);
    pt.put("Time.dstEndTime", dstEndTime);
    pt.put("Time.dstOffset", dstOffset);
    pt.put("Time.dstStartTime", dstStartTime);
    pt.put("Time.localTime", localTime);
    pt.put("Time.quality", quality);
    pt.put("Time.quality2", quality);
    pt.put("Time.tzOffset", tzOffset);
    return pt;
}

void Time::Print ()
{
        boost::property_tree::ptree pt = Time::serialize();
        write_xml(std::cout, pt);
}
