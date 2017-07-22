// compilation safegaurds
#ifndef ICT_DATE_H_
#define ICT_DATE_H_
#include <iostream>
#include"POS.h"
// ict namespace 

namespace ict {
    // Date defined Error values

#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4
#define HOUR_ERROR 5
#define MIN_ERROR 6

    class Date {
    public:
        // member variables
        int m_year;
        int m_mon;
        int m_day;
        int m_hour;
        int m_min;
        int m_readErrorCode;
        bool m_dateOnly;



        // private methods
        int value()const;
        void errCode(int errorCode);
        


    public:
        // constructors
        Date();

        Date(const int, const int, const int);

        Date(const int, const int, const int, const int, const int = 0);


        void set();
        void set(int, int, int, int, int);
        // operator ovrloads
        bool operator==(const Date& D)const;
        bool operator!=(const Date& D)const;
        bool operator<(const Date& D)const;
        bool operator>(const Date& D)const;
        bool operator<=(const Date& D)const;
        bool operator>=(const Date& D)const;

        // methods
        int errCode()const;
        bool bad()const;
        bool dateOnly()const;
        void dateOnly(bool value);



        int mdays()const;

        // istream  and ostream read and write methods
        std::istream& read(std::istream&);
        std::ostream& write(std::ostream&)const;

        // operator<< and >> overload prototypes for cout and cin


    };
   	std::istream& operator>>(std::istream& , Date& );
	std::ostream& operator<<(std::ostream& , const Date& );
};
#endif