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
    void Dest_Time_Test()
    {

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
        cout<<" ---------------------- Time Test ---------------------- "<<endl;
        cout<<"\n----->testing current time...\n\n";
        Current_Time_Test();
        cout<<"----------------------------------\n";
        cout<<"\n----->testing time zone offset...\n\n";
        Time_Zone_Offset();
        cout<<"----------------------------------\n";
        cout<<"\n----->testing local time...\n\n";
        Local_Time_Test();
        cout<<"----------------------------------\n";
        return 0;
    }
}
