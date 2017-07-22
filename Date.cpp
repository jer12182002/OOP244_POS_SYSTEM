#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
#include "Date.h"
#include "POS.h"

namespace ict {

    void Date::set() {
        time_t t = time(NULL);
        tm lt = *localtime(&t);
        m_day = lt.tm_mday;
        m_mon = lt.tm_mon + 1;
        m_year = lt.tm_year + 1900;
	//std::cout<<"111111111setfor time";
        if (dateOnly()) {
            m_hour = m_min = 0;
        } else {
            m_hour = lt.tm_hour;
            m_min = lt.tm_min;
        }
    }
    	void Date::set(int year, int mon, int day, int hour, int min) {
		m_year = year;
		m_mon = mon;
		m_day = day;
		m_hour = hour;
		m_min = min;
		m_readErrorCode=NO_ERROR;
	}


    int Date::value()const {
        return m_year * 535680 + m_mon * 44640 + m_day * 1440 + m_hour * 60 + m_min;
    }

    int Date::mdays()const {
        int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1};
        int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
        mon--;
        return days[mon] + int((mon == 1)*((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
    }

    Date::Date() {
	  //  std::cout<<"22222222222222222222222222222222222222";
	    m_dateOnly = false;
        set();
    }

    Date::Date(int year, int mon, int day) {
        m_dateOnly = true;
        m_year = year;
        m_mon = mon;
        m_day = day;
        m_hour = 0;
        m_min = 0;
        m_readErrorCode = NO_ERROR;

    }

    Date::Date(int year, int mon, int day, int hour, int min) {
	    //std::cout<<"55555555555555555arguement";
    	    m_dateOnly = false;
        set(year,mon,day,hour,min);
	m_readErrorCode=NO_ERROR;	
    }

    bool Date::operator==(const Date& D)const {
        return (this->value() == D.value());
        
    }

    bool Date::operator!=(const Date& D)const {
        return (this->value() != D.value());
        
    }

    bool Date::operator<(const Date& D)const {
        return (this->value() < D.value());
    }

    bool Date::operator>(const Date& D)const {
        return (this->value() > D.value());
    }

    bool Date::operator<=(const Date& D)const {
        return (this->value() <= D.value());
    }

    bool Date::operator>=(const Date& D)const {
        return (this->value() >= D.value());
    }

    int Date::errCode()const {
        return m_readErrorCode;
    }
    void Date::errCode(int errorCode){
        m_readErrorCode=errorCode;
    }
    bool Date::bad()const {
        return (m_readErrorCode != 0);
    }

    bool Date::dateOnly()const {
        return m_dateOnly;
    }

    void Date::dateOnly(bool value) {
        m_dateOnly = value;
        if (value) {
            m_hour = 0;
            m_min = 0;
        }
    }
    // istream  and ostream read and write methods
  
    
            /*Reads the date in the following format: YYYY/MM/DD (e.g. 2015/03/24) from
             *  the console if m_dateOnlye only is true or in the following format: YYYY/MM/DD, hh:mm 
             * (e.g. 2015/03/24, 22:15) if _dateonly is false. This function does not prompt the
             *  user. If the istream(is) object fails at any point, this function sets m_readErrorCode
             *  to CIN_FAILED and does NOT clear the istream object. If the istream(istr) object reads 
             * the numbers successfully, this function validates them. It checks that they are in range, 
             * in the order of year, month and day (see the general header-file and the mday() function 
             * for acceptable ranges for years and days respectively). If any number is not within range,
             *  this function sets m_readErrorCode to the appropriate error code and omits any further validation. 
             * Irrespective of the result of the process, this function returns a reference to the istream(istr) object.*/
    std::istream& Date::read(std::istream& is) {
     /*1.if m_dateOnly==1,or input is in the right format then read(cin)
       2.but if m_dateOnly ==0, dont read
      *3.if is object is fail to read.then set m_readErrorCode=CIN_FAILED(true in both variables)
      *4.if is object read successfully, then call mday() function to check whether the input is in the 
      *  right range. If its not in the right range, then set m_readErrorCode to the error by what we defined const in the header file.
      */
       int year=0,month=0,day=0,hour=0,min=0;
       Date::errCode(NO_ERROR);
	   is >> year;
       if(is.get()!='/'){
           errCode(CIN_FAILED);
       }
       is>>month;
       if(is.get()!='/'){
       errCode(CIN_FAILED);
       }
       if(dateOnly()){
           is>>day;
		   if(!errCode()){
               set(year,month,0,0,0);
               (year<MIN_YEAR||year>MAX_YEAR)?errCode(YEAR_ERROR):errCode(NO_ERROR);
               if(month<1||month>12){
                   errCode(MON_ERROR);
               }else if(day<1||day>mdays()){
                   errCode(DAY_ERROR);
               }
               
           }
           m_day=day;
		   //is.clear();
		   //is.ignore();
           return is;
       }else{
           is>>day;
           if(is.get()!=','){
               errCode(CIN_FAILED);
           }
           is>>hour;
           if(is.get()!=':'){
           errCode(CIN_FAILED);
           }
           is>>min;
           if(NO_ERROR==errCode()){
               set(year,month,0,0,0);
               (year<MIN_YEAR||year>MAX_YEAR)?errCode(YEAR_ERROR):errCode(NO_ERROR);
                  
                if (month<1||month>12){
                   errCode(MON_ERROR);
               }else if(day<1||day>mdays()){
                   errCode(DAY_ERROR);
               }else if(hour<0||hour>23){
                   errCode(HOUR_ERROR);
               }else if(min<0||min>59){
                   errCode(MIN_ERROR);
               }
           }
           
       }
       
       m_day=day;
       m_hour=hour;
       m_min=min;
              
       
return is;
   }

    std::ostream& Date::write(std::ostream& ostr)const {
      
        //	std::cout<<"33333333333333333333333333333333333write";
	ostr<<m_year<<"/";
	ostr.width(2);
	ostr.fill('0');
	ostr<<m_mon<<"/";
	ostr.width(2);
	ostr.fill('0');
	ostr<<m_day;
	if(!m_dateOnly){
	ostr<<", "<<m_hour<<":"<<m_min;
	}
   
        return ostr;
    }
    // operator<< and >> overload prototypes for cout and cin
  

	//overloading  >> operator
		std::istream& operator>>(std::istream& is, Date& date){
	//		std::cout<<"4444444444444444444444444444444input";
		return 	date.read(is);
		
	}
	std::ostream& operator<<(std::ostream& os, const Date& date){
	//	std::cout<<"77777777777777777output";
		return date.write(os);
	
	}
}
