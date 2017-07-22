#ifndef ICT_NONPERISHABLE_H__
#define ICT_NONPERISHABLE_H__
#include"Item.h"
#include"Error.h"
//#include"Error.cpp"
namespace ict{
    class NonPerishable:public Item{
        Error m_err;//Error is a class type in Error.h
        
    protected:
        bool ok() const;
        void error(const char* message);
        virtual char signature()const;
    public:
        std::fstream& save(std::fstream& file)const;
        std::fstream& load(std::fstream& file);
        std::ostream& write(std::ostream& ostr, bool linear)const;
	std::istream&read(std::istream&);
    };
    

    
}








#endif