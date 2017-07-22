#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<iomanip>
#include"PosApp.h"
#include "Item.h"
#include "NonPerishable.h"
#include "Perishable.h"
using namespace std;
namespace ict {
	int billcount=0;
    PosApp::PosApp(const char* filename, const char*billfname) {
        //cout<<"!!!!"<<endl;
        //cout<<m_noOfItems;
        if (strlen(filename) != 0 && strlen(billfname) != 0) {
            PosApp::deallocateItems();
            strcpy(m_filename, filename);
            strcpy(m_billfname, billfname);
            m_noOfItems=0;
            PosApp::loadRecs();
            
        }
    }

    int PosApp::menu() {
		cin.clear();
        int sel = -1;
        cout << "The Sene-Store" << endl;
        cout << "1- List items" << endl;
        cout << "2- Add Perishable item" << endl;
        cout << "3- Add Non-Perishable item" << endl;
        cout << "4- Update item quantity" << endl;
        cout << "5- Show Item" << endl;
        cout << "6- POS" << endl;
        cout << "0- exit program" << endl;
        cout << "> ";
        cin>>sel;
        cout << endl;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(2000, '\n');
            cout << "===Invalid Selection, try again===" << endl << endl;
            sel = -1;
        }
        return sel;
    }

    void PosApp::deallocateItems() {
        // delete[]m_items;
        // m_items=nullptr;
    }

    void PosApp::loadRecs() {
        //cout<<"2"<<endl;
        char id = 'o';
        //char sku[MAX_SKU_LEN+1];
        //char *name;
        //double price;
        //bool taxed;
        //int quantity;
       // m_noOfItems = 0;
	PosApp::deallocateItems();
        
        fstream fileIn(m_filename, ios::in);
        if (!fileIn) { //if(!fileIn.is_open())
            fileIn.clear();
            fileIn.close(); //exit(EXIT_FAILURE);
            fileIn.open(m_filename, ios::out);
            fileIn.close();
            cout<<"if not open"<<endl;
        } else {
            	m_noOfItems=0;
		while (fileIn.good()){
             //   cout<<"filename=="<<m_filename;
              //  cout<<"its still open"<<endl;
                fileIn>>id;
//				fileIn.clear();
				fileIn.ignore();
         
	     
				//    cout<<"id is=="<<id<<endl;
                if (id == 'P') {
                    // m_items[m_noOfItems]=new Perishable::load(fileIn);
                    m_items[m_noOfItems] = new Perishable();
                    m_items[m_noOfItems]->load(fileIn);
   		    m_noOfItems++;
                   // cout<<"+++++++++!"<<m_noOfItems<<endl;
                } else if(id=='N'){
                    //m_items[m_noOfItems]=new NonPerishable::load(fileIn);
                    m_items[m_noOfItems] = new NonPerishable();
                    m_items[m_noOfItems]->load(fileIn);
                    m_noOfItems++;
                 //   cout<<"---------!"<<m_noOfItems<<endl;
                }
               // cout<<"!!!!loadRecs-"<<m_noOfItems;
    		//cout<<m_items[m_noOfItems]->sku()<<endl;        
    //        cout<<"item==="<<m_noOfItems<<endl;   
               // cout<<"@@@@@"<<m_noOfItems;
            }
            fileIn.clear();
            fileIn.close();
        }
		//m_noOfItems--;
		//cout << "noofitem" << m_noOfItems;
    }

    void PosApp::saveRecs() {
    /*  //  cout<<"3"<<endl;
       int count=0;
        fstream fileOut("m_filename", ios::out);
        {
            while(count!=m_noOfItems){
                //fileOut << m_items[count];
				m_items[count]->save(fileOut);
				count++;
            }
        
        //fileOut.clear();
        //cout<<"!!!!saveRecs-"<<m_noOfItems;
        fileOut.close();
        PosApp::loadRecs();
		//doesnt run properly~!!!!!!!!!!why!!!!!!!!!!!!!!!!!!!???????????????????????
	}*/
	
		fstream fileOut(m_filename, ios::out);
	//	m_noOfItems++;
	for (int i = 0; i< m_noOfItems; i++)
	{
		if (m_items[i]->quantity() > 0)
		{
			m_items[i]->save(fileOut);
		}
	}
	fileOut.close();
	loadRecs();

	}
    int PosApp::searchItems(const char* sku) const {
		
		
		for (int i = 0; i <= m_noOfItems; i++) {
			//cout <<"for---"<< m_items[i]->sku()<<endl;
			if (strcmp(sku, m_items[i]->sku()) == 0) {
				return i;
			}
        }
        return -1;
    }

    void PosApp::updateQty() {
		int position = -1, quantity = 0;
		char sku[MAX_SKU_LEN + 1];
		cout << "Please enter the SKU: ";
		cin >> sku;
		cin.clear();
		cin.ignore();
		for (int i =0 ; i < m_noOfItems; i++) {
			if (!strcmp(m_items[i]->sku(),sku)) {
				position = i ;
			}
		}if (position != -1) {
			m_items[position]->write(cout, 0);
			
			
			cout << endl << "Please enter the number of purchased items: ";
			cin >> quantity;
			m_items[position]->quantity(quantity+m_items[position]->quantity());
			PosApp::saveRecs();
			cout << "updated!" << endl;
		}
		else {
			cout << "Not found!" << endl;
		}
		cout << endl;

    }

    void PosApp::listItems()const{
		double totalPrice = 0,total=0;
//	cout<<"item~~~~~~~~~~~~ "<<m_noOfItems<<endl;    
		cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total |" << endl;
        cout << "-----|--------|--------------------|-------|---|----|---------|" << endl;
        for (int i = 0; i < m_noOfItems-1; i++) {
           /*	cout << setfill(' ') << right << setw(4) << (i+1) << " | "
				<< m_items[i]->sku() << setw(4) << '|' << left << setw(20) << m_items[i]->name() << '|'
				<< setw(7) <<right<< m_items[i]->price() << '|' << setw(3);
			if (m_items[i]->taxed())cout << 'P';
			else cout << 'N';
			cout <<'|' << setw(4) <<right<< m_items[i]->quantity() << '|' << fixed <<setprecision(2)<<right<<setw(9)<< m_items[i]->cost()<<'|' << endl;
			totalPrice += m_items[i]->cost();*/
			cout << setfill(' ') << right << setw(4) << (i + 1) << " | ";
			m_items[i]->write(cout, 1);
			total = m_items[i]->cost()*m_items[i]->quantity();
			totalPrice += total;
			cout << endl;
		}
		cout
			<< "-----^--------^--------------------^-------^---^----^---------^" << endl
			<<right<< setw(48) << "Total: $  |";
		cout  << setw(14)<<right<<totalPrice  <<'|'<<right<< endl
			<< "-----^--------^--------------------^-------^---^----^---------^" << endl;
    }

    void PosApp::addItem(bool isPerishable) {
		(isPerishable) ? m_items[m_noOfItems] = new Perishable : m_items[m_noOfItems] = new NonPerishable;
		m_items[m_noOfItems]->read(cin);
		//cin.ignore();
		cin.clear();
		if (cin.good()) {
	
			cout << "Item added." << endl<<endl;
			m_noOfItems++;
		}
		
		

    }
	void PosApp::truncateBillFile() {
		fstream file(m_billfname, ios::out| ios::trunc);
		file.close();
	
	}

	void PosApp::showBill() {//collorbate with Hassan Assowe
		char id='O';
		double total = 0;
		Item* item;
		//fstream fileIn(m_billfname, ios::in);
		fstream fileIn(m_billfname, ios::in);
		if (!fileIn.fail())
		{
			cout << "v--------------------------------------------------------v" << endl;
			cout << "| " << Date() << setfill(' ') << setw(39) << "|" << endl;
			cout << "| SKU    | Item Name          | Price |TX |Qty |   Total |" << endl;
			cout << "|--------|--------------------|-------|---|----|---------|" << endl;
			//while(fileIn)  //this will have error
			while (!fileIn.eof())
			{
			
				fileIn >> id;
				fileIn.ignore();
			

				(id == 'P'&&id!='O') ? item = new Perishable() : item = new NonPerishable();
					item->load(fileIn);
					total += item->cost();
					
				cout << "| ";
				item->write(cout, 1);
				cout << endl;

			}

			cout << "^--------^--------------------^-------^---^----^---------^" << endl;
			cout << "|                                 Total $ |";
			cout << setw(14)<<right << fixed << setprecision(2) << total <<'|'<< endl;
			cout << "v--------------------------------------------------------v" << endl;
		}
		fileIn.close();
		PosApp::truncateBillFile();

	}
	void PosApp::addToBill(Item& I){//collorbate with Hassan Assowe
		//cout << "~~~~~~~~~AddBill";
		int quantity = I.quantity();
		//fstream fileIn(m_billfname,ios::out||ios::app);
		fstream fileIn(m_billfname, ios::out|ios::app);
		if (I.quantity() > 0)
		{
			I.quantity(1);
			I.save(fileIn);
			I.quantity(quantity - 1);
			
		}

		fileIn.close();
		PosApp::saveRecs();
	}

	void PosApp::POS() {
		char sku[MAX_SKU_LEN];
		
		//char space;
		int find = -1,run=1;
		while (run == 1) {
			cin.clear();
			cin.ignore();
			cout << "Please enter the SKU: ";
			//cin >> sku;
			cin.get(sku,MAX_SKU_LEN+1,'\n');
			//cin.ignore(2,'\n');
			//cin.clear();
			//cin >> sku >> space;
			//cout << "sku===" << sku << "len===" << strlen(sku);
			if(strcmp(sku,"")==0){
				PosApp::showBill();
				run = 0;
				break;
			}
			else {
			 find=PosApp::searchItems(sku); 
			// cout << "!!!!!!!!!!!!!!!!!!!" << endl;
			}
			
			if(find!=-1){
				for (int i = 0; i < m_noOfItems; i++) {
					 
				}
				//cout << "find ==" << find<<endl;
				cout << "v-----------------------------------v" << endl;
				cout << "| " << m_items[find]->name() << endl;
				cout << "v-----------------------------------v" << endl;
				addToBill(*m_items[find]);
	//			billcount = find;
			}
			else  {
				cout << "Not found!" << endl;
			}


		}
	
	}
		


    void PosApp::run() {
        int sel = -1;
		char sku[MAX_SKU_LEN + 1];
		int find = -1;
		double total = 0;
        while (sel != 0) {

            sel = PosApp::menu();
            switch (sel) {
                case 1:
                    PosApp::listItems();
                    break;
                case 2:
                    PosApp::addItem(1);
                    break;
                case 3:
                    PosApp::addItem(0);
                    break;
                case 4:
                    PosApp::updateQty();
                    break;
                case 5:
					
					cout << endl << "Please enter the SKU: ";
					cin >> sku;
					cin.clear();
					cin.ignore();
					find=PosApp::searchItems(sku);
					if (find != -1) {
						cout << "Name: " << endl;
						cout << m_items[find]->name()<<endl;
						cout << "Sku: " << m_items[find]->sku() << endl;
						cout << "Price: " << m_items[find]->price() << endl;
						cout << "Price after tax: ";
						if (m_items[find]->taxed()) {
							cout <<fixed<<setprecision(2)<< m_items[find]->price()*(1+TAX);
							total = m_items[find]->price()*(1+TAX)*m_items[find]->quantity();
						}
						else {
							cout << m_items[find]->price();
							total = m_items[find]->price()*m_items[find]->quantity();
						}
						cout <<endl<< "Quantity: " << m_items[find]->quantity()<<endl;
						cout << "Total Cost: " << fixed << setprecision(2) << total<<endl<<endl;
						//cout << "Expiry date:!!!!"<<endl;
					//	m_items[find]->write(cout, 0);
					}
					else {
						cout << "Not found!" << endl << endl;
						
					}



                    break;
                case 6:
                    PosApp::POS();
					//PosApp::showBill();
					break;

            }


        }
        cout << "Goodbye!";
    }
}






/*
ouputs:
-------------------------------------
update:
Please enter the SKU: 1313
Name:
Paper Tissue
Sku: 1313
Price: 1.22
Price after tax: 1.38
Quantity: 194
Total Cost: 267.45

Please enter the number of purchased items: 12
Updated!

------------------------------
Please enter the SKU: 3434
Not found!

-------------------------------------
add item:
Perishable Item Entry:
Sku: 5656
Name:
Honey
Price: 12.99
Taxed: y
Quantity: 12
Expiry date (YYYY/MM/DD): 1200/10/12
Invalid Year in Date Entry

Perishable Item Entry:
Sku: 5656
Name:
Honey
Price: 12.99
Taxed: y
Quantity: 12
Expiry date (YYYY/MM/DD): 2017/5/15
Item added.

--------------------------------------------
list item:
 Row | SKU    | Item Name          | Price |TX |Qty |   Total |
-----|--------|--------------------|-------|---|----|---------|
   1 | 1234   |Milk                |   3.99|  P|   2|     7.98|
   2 | 3456   |Paper Cups          |   5.99| TN|  38|   257.21|
   3 | 4567   |Butter              |   4.56| TP|   9|    46.38|
   4 | 1212   |Salted Butter       |   5.99|  P| 111|   664.89|
   5 | 1313   |Paper Tissue        |   1.22| TN| 206|   283.99|
   6 | 5656   |Honey               |  12.99| TP|  12|   176.14|
-----^--------^--------------------^-------^---^----^---------^
                               Total Asset: $  |       1436.59|
-----------------------------------------------^--------------^


--------------------------------------
printbill:
v--------------------------------------------------------v
| 2017/04/02, 12:42                                      |
| SKU    | Item Name          | Price |TX |Qty |   Total |
|--------|--------------------|-------|---|----|---------|
| 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
| 1313   |Paper Tissue        |   1.22| TN|   1|     1.38|
| 5656   |Honey               |  12.99| TP|   1|    14.68|
^--------^--------------------^-------^---^----^---------^
|                               Total: $  |         22.05|
^-----------------------------------------^--------------^

-------------------------------------------------------
POS:
Sku: 1212
v------------------->
| Salted Butter
^------------------->
Sku: 1212
v------------------->
| Salted Butter
^------------------->
Sku: 1313
v------------------->
| Paper Tissue
^------------------->
Sku: 1234
v------------------->
| Milk
^------------------->
Sku: 7654
Not found!
Sku: 5656
v------------------->
| Honey
^------------------->
Sku:
v--------------------------------------------------------v
| 2017/04/02, 12:58                                      |
| SKU    | Item Name          | Price |TX |Qty |   Total |
|--------|--------------------|-------|---|----|---------|
| 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
| 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
| 1313   |Paper Tissue        |   1.22| TN|   1|     1.38|
| 1234   |Milk                |   3.99|  P|   1|     3.99|
| 5656   |Honey               |  12.99| TP|   1|    14.68|
^--------^--------------------^-------^---^----^---------^
|                               Total: $  |         32.03|
^-----------------------------------------^--------------^

------------------------------------------------------
run:
The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> 5

Please enter the SKU: 5656
v-----------------------------------v
Name:
Honey
Sku: 5656
Price: 12.99
Price after tax: 14.68
Quantity: 10
Total Cost: 146.79
Expiry date: 2017/05/15
^-----------------------------------^

The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> 5

Please enter the SKU: 12345
Not found!

The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> five

===Invalid Selection, try again===

The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> 0

Goodbye!

 */
