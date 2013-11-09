#include <iostream>
#include <string>
using namespace std;

int main (int argc, char *argv[])
{
    double registerCash, price, cash, change, sales;
    string answer;
    bool error;
    cout << "How much money is in the cash register?" << endl;
    cin >> registerCash;
    
    do {
        cout << "What is the price of the item?" << endl;
        cin >> price;
        price *= 1.055;
        cout << "The final price is $" << price << endl;
        
        do {
            cout << "Input the customer's cash payment:" << endl;
            cin >> cash;
            change = cash - price;
            
            if (cash < price) {
                cerr << "Not enough payment!" << endl;
                error = true;
            } else if (change > registerCash) {
                cerr << "ERROR!! Not enough change in the cash register!" << endl;
                error = true;
            } else {
                cout << "Your change is $" << change << endl;
                registerCash += price;
                error = false;
            }
        } while (error);
        
        cout << "Is there another item? y or n" << endl;
        cin >> answer;
        if ("y" == answer || "Y" == answer) {
            sales = true;
        } else {
            sales = false;
        }
        
    } while (sales);
    
    cout << "The final amount of money in the cash register is $" << registerCash << endl;
    
    return 0;
}