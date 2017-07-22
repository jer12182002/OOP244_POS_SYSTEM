#define _CRT_SECURE_NO_WARNINGS  
// Lib includes
#include<iostream>
#include<cstring>
// inlcude Item and POS header files
#include"Item.h"
#include"POS.h"
#include"PosIO.h"
using namespace std;
namespace ict {
    // class Item implementaion

    Item::Item() {
        m_sku[0] = '\0';
        m_name = nullptr;
        m_price = 0;
        m_quantity = 0;
        m_taxed = 0;
    }

    Item::Item(const Item& o_item) {
        strcpy(m_sku, o_item.m_sku);
        m_price = o_item.m_price;
        m_quantity = o_item.m_quantity;
        m_taxed = o_item.m_taxed;

        if (o_item.m_name != nullptr) {
            m_name = new char[strlen(o_item.m_name) + 1];
            strncpy(m_name, o_item.m_name, strlen(o_item.m_name) + 1);
        } else {
            m_name = nullptr;
        }


    }

    Item::Item(const char sku[], const char *name, double price, int tax) {
        if (sku[0] != '\0' && name != nullptr) {
            strcpy(m_sku, sku);
            m_name = nullptr;
            m_name = new char[strlen(name) + 1];
            strcpy(m_name, name);
            m_quantity = 0;
            m_price = price;
        } else {
            m_sku[0] = '\0';
            m_name = nullptr;
            m_price = 0;
            m_taxed = 0;
            m_quantity = 0;
        }
    }

    Item::~Item() {
        delete[]m_name;
    }

    Item& Item::operator=(const Item& oldItem) {
        if (!Item::isEmpty()) {
            Item::name(oldItem.m_name);
            m_quantity = oldItem.m_quantity;
        }
        return *this;
    }

    void Item::sku(const char* o_sku) {
        strcpy(m_sku, o_sku);
		//cout << "sku-" << m_sku << endl;
    }

    void Item::price(double o_price) {
        m_price = o_price;
		//cout << "price" << m_price<<endl;
    }

    void Item::name(const char *o_name) {
        delete[]m_name;
        m_name = new char[strlen(o_name) + 1];
        strcpy(m_name, o_name);
		//cout << "name-" << m_name<<endl;
    }

    void Item::taxed(bool o_taxed) {
        m_taxed = o_taxed;
		
    }

    void Item::quantity(int o_quantity) {
        m_quantity = o_quantity;
		//cout << "quantity-" << m_quantity << endl;
    }

    const char* Item::sku()const {
        return m_sku;
    }

    double Item::price()const {
        return m_price;
    }

    char* Item::name()const {
        return m_name;
    }

    bool Item::taxed()const {
        return m_taxed;
    }

    int Item::quantity()const {
        return m_quantity;
    }

    double Item::cost()const {
        double _cost;
        m_taxed == 1 ? _cost = m_price * (1 + TAX) : _cost = m_price;
        return _cost;
    }

    bool Item::isEmpty() {
        return ((m_sku[0] = '\0')&&(m_name = nullptr)
                &&(m_price = 0)&&(m_taxed = 0)&&(m_quantity = 0));
    }

    bool Item::operator==(const char* o_sku) {
        if (strcmp(m_sku, o_sku)) {
            return 1;
        }
        return 0;
    }

    int Item::operator+=(int quantity) {
        return Item::quantity() + quantity;
    }

    int Item::operator-=(int quantity) {
        return Item::quantity() - quantity;
    }

    double operator+=(double& left, const Item& item) {
        return left + (item.price() * item.quantity());
    }

    std::istream& operator>>(std::istream&is, Item& I) {
        I.read(is);
        return is;

    }

    std::ostream& operator<<(std::ostream&os, const Item& I) {

        I.write(os, true);
        return os;
    }

}

