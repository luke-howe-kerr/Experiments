#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct order {
    vector<string> list;
    vector<double> listprices;
    string gmessage;
} order1;

bool AskIfYes(string question)
{
    bool ret;
    string answer;
    cout << question << endl;
    do {
        cout<< "Enter y or n: ";
        cin >> answer;
    } while ("y" != answer && "Y" != answer && "n" != answer && "N" != answer);

    if ("y" == answer || "Y" == answer) {
        ret = true;
    }	else {
        ret = false;
    }

    return ret;
}

double GetPositiveDouble (string prompt, string errorMessage)
{
  double input;
  do {
    cout << prompt << endl;
    cin >> input;
    if (input > 0) {
      break;
    }
    cout << errorMessage;
  } while (1);
  return input;
}

int main (int argc, char *argv[])
{
  double registerCash, price, cash, change, tax, total, subtotal, taxRate;
    string answer, description, giftyn, message;
    bool error, sales, cancel = false, order;
  
    registerCash = GetPositiveDouble("How much money is in the cash register?",
				     "You must have some positive money in the register!");
    
    taxRate = GetPositiveDouble("Enter the tax rate: (in percent)",
			    "Error! Must input a positive tax value!");

    taxRate = taxRate/100;
    
    cout << "The first order." << endl << endl;
    
    do {
        cancel = false;
        subtotal = 0;
        error = true;
        do {
            cout << "What is the price of the item?" << endl;
            cin >> price;
            order1.listprices.push_back(price);
            subtotal += price;
            do {
                cout << "Item description: " << endl;
                cin >> description;
                if (description.empty()) {
                    cout << "Error! No input! Please enter an item description:" << endl;
                }
            } while (description.empty());
            order1.list.push_back(description);
        
            cout << "Is there another item? y or n (c to cancel the order)" << endl;
            cin >> answer;
            if ("y" == answer || "Y" == answer) {
                sales = true;
            } else if ("c" == answer || "C" == answer) {
                cancel = true;
            } else {
                sales = false;
            }
        } while (sales && !cancel);
        
        if (!cancel) {
            cout << "Do you want to include a gift message? y or n" << endl;
            cin >> giftyn;
            if ("y" == giftyn || "Y" == giftyn) {
                cout << "Enter your message:" << endl;
                cin >> message;
                order1.gmessage = message;
            }
            
            
            for (int ii = 0; ii < order1.list.size(); ii++) {
                cout << endl << order1.list[ii] << endl << order1.listprices[ii] << endl << "Gift Message:" << endl << order1.gmessage << endl;
            }
            tax = taxRate * subtotal;
            total = subtotal + tax;
            cout << "Subtotal:\t" << subtotal << endl;
            cout << "Tax:\t" << tax << endl;
            cout << "Total:\t" << total << endl;
        }
        
        while (error && !cancel) {
            cout << "Input the customer's cash payment:" << endl;
            cin >> cash;
            //If you input anything other than an integer it creates an infinite loop. Why is cin not working?
            change = cash - total;
        
            if (cash < total) {
                cerr << "Not enough payment!" << endl;
                error = true;
            } else if (change > registerCash) {
                cerr << "ERROR!! Not enough change in the cash register!" << endl;
                error = true;
            } else {
                cout << "Your change is $" << change << endl;
                registerCash += total;
                error = false;
            }
        }
        
        cout << "Is there another order? y or n" << endl;
        cin >> answer;
        if ("y" == answer || "Y" == answer) {
            order = true;
        } else {
            order = false;
        }
    } while (order);
    
    cout << "The final amount of money in the cash register is $" << registerCash << endl;
    
    return 0;
}
