#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include <iostream>
#include<fstream>
#include<iomanip>
#include "NonPerishable.h"

using namespace std;
namespace ict {

    bool NonPerishable::ok() const {
        return m_err.isClear();

    }

    void NonPerishable::error(const char* message) {
        m_err.message(message);
    }

    char NonPerishable::signature()const {
        //return char 'N' if it is written in
        return 'N';
    }

    std::fstream & NonPerishable::save(std::fstream & file)const {
        /*if (file.is_open()) {
            //file<<(m_err.isClear()?(const char*)NonPerishable::signature():Item::sku());
            if (m_err.isClear()) {
                file << NonPerishable::signature();
            } else {
                file << Item::sku();
            }
            if (m_err.isClear()) {
                file << NonPerishable::signature();
            } else {
                file << Item::name();
            }
            if (m_err.isClear()) {
                file << NonPerishable::signature();
            } else {
                file << Item::price();
            }
            if (m_err.isClear()) {
                file << NonPerishable::signature();
            } else {
                file << Item::taxed();
            }
            if (m_err.isClear()) {
                file << NonPerishable::signature();
            } else {
                file << Item::quantity();
            }
            return file;
        } else {
            cout << "file is not open" << endl;
        }
        return file;*/

        if (file.is_open()) {
            file << signature() << ','
                    << Item::sku() << ','
                    << Item::name() << ','
                    << Item::price() << ','
                    << Item::taxed() << ','
                    << Item::quantity();
        } else {
            cout << "file is not open" << endl;
        }

        return file;
    }

    std::fstream & NonPerishable::load(std::fstream & file) {
        char sku[MAX_SKU_LEN + 1];
        char name[80];
        double price;
        int quantity;
        bool taxed;
        if (file.is_open()) {
            file.getline(sku, MAX_SKU_LEN, ',');
			file.getline(name, 30, ',');
            file >> price;
            file.ignore() >> taxed;
            file.ignore() >> quantity;
            /*if (file.fail()) {
                cout << "file wrong";
            }*/
            Item::sku(sku);
            Item::name(name);
            Item::price(price);
            taxed ? Item::taxed(1) : Item::taxed(0);
            Item::quantity(quantity);

        } else {
            cout << "file is not open" << endl;
        }
        return file;

    }

    std::ostream & NonPerishable::write(std::ostream& ostr, bool linear)const {
        if (NonPerishable::ok()) {
            if (linear) {
                ostr << left << setw(MAX_SKU_LEN) << Item::sku() << '|'
                        << left << setw(20) << Item::name() << '|'
                        << right << setw(7) << fixed << setprecision(2) << Item::price() << '|';
                if (Item::taxed()) {
                    ostr << " T";
                } else {
                    ostr << "  ";
                }
                ostr <<signature() << '|';
                ostr << setw(4) << Item::quantity() << '|'
                     << setw(9) << Item::cost() * Item::quantity() << '|';
            } else {
                ostr << "Name:" << endl << Item::name() << endl
                        << "Sku: " << Item::sku() << endl
                        << "Price: " << Item::price() << endl
                        << "Price after tax: ";
                if (Item::taxed()) {
                    ostr << Item::cost();
                } else {
                    ostr << "N/A";
                }
                ostr << endl;
                ostr << "Quantity: " << Item::quantity() << endl
                        << "Total Cost: " << Item::quantity() * Item::cost() << endl;
            }
        } else {
            ostr << m_err;
        }
        return ostr;


    }

    std::istream & NonPerishable::read(std::istream& istr) {
        char sku[MAX_SKU_LEN + 1];
        char name[80];
        double price;
        char taxed;
        int quantity;
		istr.clear();
		istr.ignore();
        m_err.clear();
        cout << "Item Entry:" << endl;
        cout << "Sku: ";

       // istr >> sku;
		istr.get(sku, MAX_SKU_LEN + 1, '\n');
        if (!istr.fail())Item::sku(sku);
		istr.clear();
		istr.ignore();

        cout << "Name:" << endl;
        //istr>>name;
		istr.get(name, MAX_SKU_LEN + 1, '\n');
        if (!istr.fail())Item::name(name);
		istr.clear();
		istr.ignore();
        cout << "Price: ";
        istr>>price;
        istr.fail() ? m_err.message("Invalid Price Entry") : Item::price(price);

        if (m_err.isClear()) {
            cout << "Taxed: ";
            istr >> taxed;
            if (taxed == 'Y' || taxed == 'y' || taxed == 'N' || taxed == 'n') {
                (taxed == 'Y' || taxed == 'y') ? Item::taxed(1) : Item::taxed(0);
                /* if (taxed == 'Y' || taxed == 'y') {
                    Item::taxed(1);
                } else {
                    Item::taxed(0);
                }*/
            } else {
                m_err.message("Invalid Taxed Entry, (y)es or (n)o");
                istr.setstate(ios::failbit);
            }

          if (m_err.isClear()) { 
            cout << "Quantity: ";
            istr >> quantity;
            istr.fail() ? m_err.message("Invalid Quantity Entry") : Item::quantity(quantity);
        }
        }

        return istr;
    }

}

