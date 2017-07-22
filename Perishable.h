#ifndef ICT_PERISHABLE_H__
#define ICT_PERISHABLE_H__
#include"NonPerishable.h"
#include"POS.h"
#include"PosIO.h"
#include"Date.h"
using namespace std;
namespace ict {

    class Perishable : public NonPerishable {
        Date m_expiry;
    protected:
        char signature()const;

    public:
        Perishable();
        fstream& save(fstream&)const;
        fstream& load(fstream&);
        ostream& write(ostream&, bool);
        istream& read(istream&);
    };


};






#endif
