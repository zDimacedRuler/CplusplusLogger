#include<sstream>
#include<iostream>
#include <time.h>
#include <string>

#define MAX_DATE 20

using namespace std;

template<typename T>
void c_m(ostringstream &os, T arg1){
    os<<arg1;
}

template<typename T, typename... Args>
void c_m(ostringstream &os, T arg1, Args... args){
    os<<arg1<<" : ";
    c_m(os,args...);
}

template<typename... Args>
void func(Args... args){
    ostringstream os;
    c_m(os, args...);
    cout<<os.str()<<endl;
}

std::string get_date()
{
   time_t now;
   char the_date[MAX_DATE];
   now = time(0);
   strftime(the_date, MAX_DATE, "%Y-%m-%d.%X", localtime(&now));
   return std::string(the_date);
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}
enum class Gender{
    male=0,
    female=1,
};

int main(){
    Gender a = Gender::female;
    func("Hello","World","by","Aman");
    cout<<get_date()<<endl;
    cout<<currentDateTime()<<endl;
    cout<<static_cast<int>(a)<<endl;
    return 1;
}
