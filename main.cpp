#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct order {
    vector<string> list;
    vector<double> listprices;
    vector<string> gmessage;
} order1;

bool AskIfYes (string question)
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

string GetNonEmptyString (string prompt, string errorMessage)
{
  string input;
  do {
    cout << prompt << endl;
    cin >> input;
    if (!input.empty()) {
      break;
    }
    cout << errorMessage;
  } while (1);
  return input;
}

int main (int argc, char *argv[])
{
    double registerCash, price, cash, change, tax, total, subtotal, taxRate;
    string answer, description, message;
    bool error, sales, cancel = false, order, giftyn;
  
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
            price = GetPositiveDouble("What is the price of the item?",
                                      "You must input a positive price!");
            order1.listprices.push_back(price);
            subtotal += price;
            description = GetNonEmptyString ("Item Description:",
					     "Error! No input!");
            order1.list.push_back(description);

            giftyn = AskIfYes("Do you want to include a gift message?");
            if (giftyn) {
	        message = GetNonEmptyString ("Enter your message:",
					     "Error! No input!");
                order1.gmessage.push_back("Gift Message:\t" + message);
            } else {
	        order1.gmessage.push_back("");
	    }
        
            cout << "Is there another item? y or n (Enter c to cancel)" << endl;
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
            for (int ii = 0; ii < order1.list.size(); ii++) {
                cout << endl << order1.list[ii] << endl << order1.listprices[ii] << endl << order1.gmessage[ii] << endl;
            }
            int taxx = (taxRate * subtotal) * 100;
            tax = taxx/100;
            total = subtotal + tax;
            cout << "Subtotal:\t" << subtotal << endl;
            cout << "Tax:\t" << tax << endl;
            cout << "Total:\t" << total << endl << endl << endl;
        }
        
        while (error && !cancel) {
	    cash = GetPositiveDouble ("Input the customer's cash payment:",
                                  "Error! No input!");
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
        
        order = AskIfYes ("Is there another order?");
    } while (order);
    
    cout << "The final amount of money in the cash register is $" << registerCash << endl;
    
    return 0;
}
