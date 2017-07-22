#define _CRT_SECURE_NO_WARNINGS 

#include "Error.h"
#include <cstring>

namespace ict{
    char* m_message;
    Error::Error(){
        m_message=nullptr;
    }
    
    Error::Error(const char* errorMessage){
        m_message=nullptr;
        Error::message(errorMessage);
    }
    
    void Error::operator=(const char* errorMessage){
       // delete []m_message;
        //m_message=nullptr;
       // m_message = new char [strlen(errorMessage)+1];
        //strcpy(m_message,errorMessage);
        Error::clear();
        Error::message(errorMessage);
    }
     Error::~Error(){
        delete[] m_message;
    }
    
    void Error::clear(){
        delete []m_message;
        m_message=nullptr;
    }
    bool Error::isClear()const{
        return (m_message==nullptr);
    }
    void Error::message(const char* value){
        delete []m_message;
        m_message = new char [strlen(value)+1];
        strcpy(m_message,value);
    }
    
    Error::operator const char*() const{
        return m_message;
    }
    
    Error::operator bool()const{
        return m_message==nullptr;
    }
    
     std::ostream &operator<<(std::ostream &os,const Error &e){
        if(!e.isClear()){
         os<<e.m_message;
       
        }
         return os;
     }
     
       
        
    
    
}
