//INFO3006 
//October 10th, 2022
//Code by DuyNhan Ta

#include <iostream>
#include<string>
#include<vector>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <cmath>
#include "time.h"
#include "rsa.h"
#include "sdes.h"

using namespace std;

int main(){
    int userChoice;
    do{
    cout << endl;
    cout<<"===================================================== \n";
    cout<<" \t\tASSIGNMENT -2 \t \n ";
    cout<<"===================================================== \n";
    cout<<" 1.S-DES\n";
    cout<<" 2.RSA\n";
    cout << " 3.Exit\n";
    cout << "PLEASE ENTER YOUR CHOICE: "; 
        cout << " ";
        cin >> userChoice; 
        switch (userChoice)
        {
        case 1:
        {
        sdes newSDES; 

        while (true)
        {
        cout << endl;
        if (newSDES.getk() == 1)
        {
            break;
        }
        newSDES.menu ();
        }
            break;
        }
        case 2:
        {
        rsa newRSA;
    
        while (true)
        {
        cout << endl;
        if(newRSA.getK() == 1){
            break;
        }
        newRSA.mainMenu();
    }
            break;
        }
        default:
            cout << "Thank you!" << endl;
            break;
        }
    }
    while(userChoice != 3);

    return 0;

}