#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

//Order contains the lists of item descriptions, prices, and gft messages (if applicable)
struct order {
    vector<string> list;
    vector<double> listprices;
    vector<string> gmessage;
} order1;

//AskIfYes outputs a yes or no question to the user and determines if the answer is a yes or a no
bool AskIfYes (string question)
{
    bool ret;
    string answer;
    cout << question << endl;
    do {
        cout<< "Enter y or n: ";
        getline (cin, answer);
    } while ("y" != answer && "Y" != answer && "n" != answer && "N" != answer);

    if ("y" == answer || "Y" == answer) {
        ret = true;
    }	else {
        ret = false;
    }

    return ret;
}

//GetPositiveDouble simply ensures that the user does not input a negative number or 0
double GetPositiveDouble (string prompt, string errorMessage)
{
  string inputString;
  double inputDbl;
  do {
    cout << prompt << endl;
    getline (cin, inputString);
    stringstream(inputString) >> inputDbl;
    if (inputDbl > 0) {
      break;
    }
    cerr << errorMessage;
  } while (1);
  return inputDbl;
}

//GetNonEmptyString ensures that when asked for a string, the user does not leave the answer blank
string GetNonEmptyString (string prompt, string errorMessage)
{
  string input;
  do {
    cout << prompt << endl;
    getline (cin, input);
    if (!input.empty()) {
      break;
    }
    cerr << errorMessage << endl;
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

    //The first loop contains each order that is run through the register
    do {
        cancel = false;
        subtotal = 0;
        error = true;

	//This loop acquires the price of the item, its description, and an optional gift message
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
            getline (cin, answer);
            if ("y" == answer || "Y" == answer) {
                sales = true;
            } else if ("c" == answer || "C" == answer) {
                cancel = true;
            } else {
                sales = false;
            }
        } while (sales && !cancel);

	//Either prints out a cancelled message or the list of items and the order totals
	if (cancel) {
	    cout << "Order canceled!" << endl;
	} else {
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

	//Accepts and processes the customer's cash payment
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
