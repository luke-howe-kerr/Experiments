#include <iostream>
#include <string>
using namespace std;

int main ()
{
    double startCash, price, cash, change, sales;
    string answer;
    bool error;
    cout << "How much money is in the cash register?" << endl;
    cin >> startCash;
    
    do {
        cout << "What is the price of the item?" << endl;
        cin >> price;
        price *= 1.055;
        cout << "The final price is $" << price << endl;
        
        do {
            cout << "Input the customer's cash payment:" << endl;
            cin >> cash;
            change = cash - price;
            
            if (change > startCash) {
                cout << "ERROR!! Not enough change in the cash register!" << endl;
                error = true;
            } else {
                cout << "Your change is $" << change << endl;
                startCash -= change;
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
    
    cout << "The final amount of money in the cash register is $" << startCash << endl;
    
    return 0;
}