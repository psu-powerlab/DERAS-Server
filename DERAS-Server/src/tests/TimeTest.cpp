//#define BOOST_TEST_MAIN
//#define BOOST_TEST_MODULE TimeTest
//#define BOOST_TEST_DYN_LINK

#include "tests/TimeTest.h"
/*#include <boost/test/unit_test.hpp>
using namespace boost::unit_test;


BOOST_AUTO_TEST_CASE(test_current_time)
{
    Time time;
    std::cout<<"here"<<std::endl;
    //BOOST_CHECK(T)
    //cout<<time.currentTime()<<endl;
}

//BOOST_AUTO_TEST_SUITE_END()

*/
namespace TimeTest{
    void Current_Time_Test()
    {
        Time t1;
        time_t t2 = time(0);
        usleep(1000000);
        time_t t3 = time(0);
        cout<<"TEST BEFORE SLEEPING: "<<t1.currentTime<<" == "<<t2<<endl;
        t1.currentTime==t2? cout<<"PASS\n":cout<<"FAIL\n";
        cout<<"TEST AFTER SLEEPING: "<<t1.currentTime<<" == "<<t3<<endl;
        t1.currentTime<t3? cout<<"PASS\n":cout<<"FAIL\n";
        return;
    }
    void Dst_Time_Test()
    {
        Time t;
        time_t tmStart = t.dstStartTime;
        time_t tmEnd = t.dstEndTime;


        cout<<t.dstStartTime<<" to --> "<<t.dstEndTime<<endl;
        // calculate start
        tm* localStart = localtime(&tmStart);
        // just to make it human readable only
        stringstream st,en;
        st<<std::put_time(localStart,"%c\n");
        cout<<st.str()<<endl; // ISSUE HERE ---- should be [March 8th - March 14th] (second Sunday in March)
        cout<<"Week day ( Sun = 0 & Sat = 6): "<<localStart->tm_wday<<endl;
        cout<<"Month: "<<localStart->tm_mon+1<<endl<<endl<<endl;;

        // calculate end
        tm* localEnd = localtime(& tmEnd);
        en<<std::put_time(localEnd, "%c\n");
        cout<<en.str()<<endl; // ISSUE HERE ---- should be [Nov 1 th - Nov 7th] (first Sunday in November)
        cout<<"Week day ( Sun = 0 & Sat = 6): "<<localEnd->tm_wday<<endl;
        cout<<"Month: "<<localEnd->tm_mon + 1<<endl;

        // Might be off-by-one error in boost?

    }
    void Quality_Test()
    {
        Time t;
        cout<<"QUALITY: "<<+t.quality<<endl;
        cout<<"TEST QUALITY: "<<"3 <= "<<+t.quality<<" <= 7"<<endl;
        t.quality >= 3 && t.quality<=7? cout<<"PASS\n":cout<<"FAIL\n";
    }
    void Href_Test()
    {
        Time t;
        cout<<"TEST HREF: "<<t.href<<" !=  EMPTY"<<endl;
        !t.href.empty()? cout<<"PASS\n":cout<<"FAIL\n";
    }
    void XMLNS_Test()
    {
        Time t;
        cout<<"TEST XMLNS: "<<t.xmlns<<" !=  EMPTY"<<endl;
        !t.xmlns.empty()? cout<<"PASS\n":cout<<"FAIL\n";
    }
    void Poll_Rate_Test()
    {
        Time t;
        cout<<"TEST POLL RATE: "<<t.pollRate<<" >= "<< 0<<endl;
        t.pollRate>=0? cout<<"PASS\n":cout<<"FAIL\n";
    }
    void Local_Time_Test()
    {
        Time t1;
        long int cur_tm = (long int) t1.currentTime;
        time_t current1 = time(&cur_tm);
        time_t current2 = time(0);
        tm* local1 = localtime(&current1);
        tm* local2 = localtime(&current2);
        string l1 = to_string(local1->tm_hour)+":"+to_string(local1->tm_min)+":"+to_string(local1->tm_sec);
        string l2 = to_string(local2->tm_hour)+":"+to_string(local2->tm_min)+":"+to_string(local2->tm_sec);
        // testing for the formatting as the local time is calculated using the current time (which run prior to this)
        cout<<"TEST LOCAL TIME (FORMATTED): "<<l1<<" == "<< l2<<endl;
        l1==l2? cout<<"PASS\n":cout<<"FAIL\n";

    }
    void Time_Zone_Offset()
    {
        /*
        string tz1;
        stringstream tz2;

        auto now = std::chrono::system_clock::now();
        auto tm_t = std::chrono::system_clock::to_time_t(now);

        tz2 << std::put_time(std::localtime(&tm_t),"%z\n");
        tz1 = std::to_string(t1.tzOffset);
        cout<<"TEST TIME ZONE OFFSET: "<<tz1<<" == "<< tz2.str()<<endl;
        tz1==tz2.str()? cout<<"PASS\n":cout<<"FAIL\n";
        */
        Time t1;
        string tz2;
        string tz1 = std::to_string(t1.tzOffset);
        time_t current_time = time(0);
        tm* local = localtime(&current_time);
        tz2 = std::to_string(local->tm_gmtoff);
        cout<<"TEST TIME ZONE OFFSET: "<<tz1<<" == "<< tz2<<endl;
        tz1==tz2? cout<<"PASS\n":cout<<"FAIL\n";
    }
    int main()
    {
        cout<<" ---------------------- Time Test Start --------------------- "<<endl;
        cout<<"\n----->testing current time...\n\n";
        Current_Time_Test();
        cout<<"----------------------------------\n";
        cout<<"\n----->testing time zone offset...\n\n";
        Time_Zone_Offset();
        cout<<"----------------------------------\n";
        cout<<"\n----->testing local time...\n\n";
        Local_Time_Test();
        cout<<"----------------------------------\n";
        cout<<"\n----->testing Daylight Saving Start Time...\n\n";
        Dst_Time_Test();
        cout<<"----------------------------------\n";
        cout<<"\n----->testing Poll Rate...\n\n";
        Poll_Rate_Test();
        cout<<"----------------------------------\n";
        cout<<"\n----->testing XML Namespace Time...\n\n";
        XMLNS_Test();
        cout<<"----------------------------------\n";
        cout<<"\n----->testing Href...\n\n";
        Href_Test();
        cout<<"----------------------------------\n";
        cout<<"\n----->testing Quality...\n\n";
        Quality_Test();
        cout<<" ---------------------- Time Test End ---------------------- "<<endl;
        return 0;
    }
}
