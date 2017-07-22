#ifndef ICT_ITEM_H__
#define ICT_ITEM_H__
// inlcude PosIO and POS header files
#include"POS.h"
#include"PosIO.h"
namespace ict{
  // class Item
    class Item:public PosIO{
        char m_sku[MAX_SKU_LEN+1];
        char *m_name;
        double m_price;
        bool m_taxed;
        int m_quantity;
    public:
        Item();
        Item(const Item&);
        Item(const char[],const char*,double,int);
        Item& operator=(const Item&);
        virtual ~Item();
        void sku(const char *);
        void price(double);
        void name(const char*);
        void taxed(bool);
        void quantity(int);
        const char * sku()const;
        double price()const;
        char* name()const ;
        bool taxed()const;
        int quantity()const;
        double cost()const;
        bool isEmpty();
        bool  operator==(const char* );
        int operator+=(int);
        int operator-=(int);
    };









  // end class Item
  // operator += 
  double operator+=(double& d, const Item& I);
  // operator << and operator >>
 std::istream& operator>>(std::istream&, Item&);
  std::ostream& operator<<(std::ostream&, const Item&);
}


#endif