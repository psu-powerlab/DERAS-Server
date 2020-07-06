//#define BOOST_TEST_MAIN
//#define BOOST_TEST_MODULE TimeTest
//#define BOOST_TEST_DYN_LINK

#include "tests/TimeTest.h"

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
    void Dst_Test(time_t time, int isdst, bool isDstStart)
    {
        tm* local = localtime(&time);
        char* str = ctime(&time);
        int expected_wday,expected_mon,expected_start,expected_end;

        // if start: month should be 2 && day should be between 8 and 14 (inclusive)
        // else: month should be 10 && day should be between 1 and 7 (inclusive)
        if (isDstStart)
        {
            expected_mon = 2;
            expected_start = 8;
            expected_end = 14;
        }
        else
        {
            expected_mon = 10;
            expected_start = 1;
            expected_end = 7;
        }
        expected_wday = 0; // dst always occur on sunday
        cout<<"testing DST for: "<<str<<endl;

        // --- test month -----
        cout<<"TEST DST MONTH: "<<local->tm_mon<<" == "<<expected_mon<<endl; // should be equal to expected month
        local->tm_mon==expected_mon? cout<<"PASS\n":cout<<"FAIL\n";

        // --- test day -----
        cout<<"TEST DST DAY (since sunday): "<<local->tm_wday<<" == "<<expected_wday<<endl; // because Sunday = 0
        local->tm_wday==expected_wday? cout<<"PASS\n":cout<<"FAIL\n";

        cout<<"TEST DST DAY (ordinal day): "<<expected_start<<" <= "<<local->tm_mday<<" <= "<<expected_end<<endl; // should be within range of expected start/end
        (local->tm_mday>=expected_start&&local->tm_mday<=expected_end)? cout<<"PASS\n":cout<<"FAIL\n";

        // --- test dst -----
        cout<<"TEST IS DST: "<<local->tm_isdst<<" == "<<isdst<<endl; // because Sunday = 0
        local->tm_isdst==isdst? cout<<"PASS\n":cout<<"FAIL\n";


    }
    void Dst_Time_Test()
    {
        Time t;
        time_t tmStart = t.dstStartTime;
        time_t tmEnd = t.dstEndTime;

        cout<<"----> test DST start..."<<t.dstStartTime<<endl;

        // test one sec before
        Dst_Test(tmStart-1,0,true);// ISSUE HERE ---- should be [March 8th - March 14th] (second Sunday in March)
        // test exact time
        Dst_Test(tmStart,1,true);
        // test one sec after
        Dst_Test(tmStart+1,1,true);


        // test one sec before
        Dst_Test(tmEnd-1,1,false);// ISSUE HERE ---- should be [Nov 1 th - Nov 7th] (first Sunday in November)
        // test exact time
        Dst_Test(tmEnd,0,false);
        // test one sec after
        Dst_Test(tmEnd+1,0,false);

        // Might be off-by-one error in boost?
        // Test DST offset
        // --- test dst -----
        cout<<"TEST DST OFFSET: "<<t.dstOffset<<" == 0"<<" || "<<t.dstOffset<<" == 3600"<<endl;
        t.dstOffset==0 || t.dstOffset == 3600? cout<<"PASS\n":cout<<"FAIL\n";

        cout<<"----> test DST end..."<<t.dstEndTime<<endl;
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
