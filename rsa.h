#include <iostream>
#include <math.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <cmath>
#include "time.h"

using namespace std;

#ifndef RSA_H_
#define RSA_H_

static int choice = 0;
static double e = 0;
vector <double> tot; 

struct Private
{
    double n; //Modulus, can be expose to public
    double d; // Private Key
};

struct Public{
    double n; //Modulus, can be expose to public
    double e; //Public Key
};

struct Keypair
{
    Private privateKey;
    Public publicKey;
};

class rsa {
    private:
        int k =0; 
        double p=0;
        double q=0; 
        double phi = 0; 
    public:
        int getK();
        double getP();
        double getQ();
        double getPhi();
        void assignP(double number);
        void assignQ(double number);
        void exit();
        bool isPrime(int number);
        double modInverse(int a, int m);
        int gcd(int num1, int num2);
        int lcm(int num1, int num2);
        string getBinary(int number);
        double getMod(int const base, string const& expo_Binary, int const modulo);
        double powerMod(long base, long exponent, long modulus);
        double encrypt(int number,int e,int n);
        double decrypt(int number,int e,int n);
        void generatePQ();
        void autoMode(Keypair &keys, int flag);
        void manualMode(Keypair &keys);
        void subMenu();
        void mainMenu();
};

//***************FUNTIONS***************
double rsa::getPhi(){
    return phi; 
}

// This function will automatically print out the submenu
void rsa::subMenu(){
    cout << endl;
    cout <<"===================================================== \n";
    cout << "\t\tSUBMENU\t\t \n";
    cout <<"===================================================== \n";
    cout << "1. AUTO MODE \n";
    cout << "2. MANUAL MODE \n";
    cout << "3. EXIT \n";
    cout <<"===================================================== \n";
    cout << "**NOTE: AUTO MODE: P and Q will be auto generated" << endl;
    cout << "**    MANUAL MODE: Insert all values manually" << endl;
    cout <<"===================================================== \n";
    cout << "PLEASE INSERT YOUR CHOICE: ";
}
// This function is used to return k value
int rsa::getK(){
    return k;
}
//This function is used to return p value
double rsa::getP(){
    return p;
}
//This function is used to return Q value
double rsa::getQ(){
    return q;
}
// This function assign the value of P
void rsa::assignP(double number){
    p = number;
}
void rsa::assignQ(double number){
    q = number;
}
//This function is used to exit the program
void rsa::exit(){
    cout << endl;
    cout << "Hope You have fun playing with the RSA algorithm!\n";
    k =1;
}
// This function check if the number is Prime
// return 1: True/ 2: False
bool rsa::isPrime(int number)
{
    for(int i = 2; i <= number / i; i++){
        if(number % i == 0){
            return false;
        }
    }
    return true;
}

// This function finds the modular inverse using Extended Euclidian
double rsa::modInverse(int a, int m){
    int temp = m;
    int y = 0;
    int x = 1;

    if (m == 1)
        return 0;

    while (a > 1)
    {
        // q is quotient
        int q = a / m;
        int t = m;

        // m is now the remainder
        m = a % m;
        a = t;
        t = y;

        // Update y and x
        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += temp;//make it positive

    return x;
}
// This function will return the greates common divisor of 2 value num1 and num2
// The function will recursively call itself with the value num2 , num2%num1
int rsa::gcd(int num1, int num2){
    if(num2 == 0)
    return num1;
    return gcd(num2, num1%num2);
}
// This function will return the least common multiple of 2 value num1 and num2
int rsa::lcm(int num1, int num2){
    return (num1*num2)/(gcd(num1, num2));
}
// This function take in a number (exponent) and change it from decimal to binary
string rsa::getBinary(int number){
    string numInBinary;
    while(number){
        numInBinary += (number%2) + '0';//  //Add the substract value from left side of ascii table to the string
        number/=2;
    }
    reverse(numInBinary.begin(), numInBinary.end());
    return numInBinary;
}
// This function applied Square and Multiply Algorithm to calculate modulo
double rsa::getMod(int const base, string const& numInBinary, int const modulo){
    int remain = base; 
    for(int i= 1; i < numInBinary.size(); i++){
        //If the bit is 0 then square the value
        remain = (remain * remain) % modulo;
        //subtract the left side of the expression
        //If the bit is 1 then square the value and multiply
        if((numInBinary.at(i)- '0') ==  1){
            remain = (base * remain) % modulo;
        }
        else 
        remain = remain; 
    }
    //cout << remain << endl;
    return remain;
}

// This function is used to calculate a^b mod n 
double rsa::powerMod(long base, long expo, long modu){
    string numInBinary = getBinary(expo);
    long const remainder = getMod(base, numInBinary, modu);
    return remainder;
}
// This function trigger the encryption process 
// C = M^e mod n 
double rsa::encrypt(int number,int e,int n){
    cout << "PROCESSING...\n" << endl;
    cout << "The Input number is: " << number << endl; 
    int ciphertext = powerMod(number,e, n);
    cout << "The Cipher Text after encryption is: " << ciphertext << endl;
    return ciphertext;
}
// This function trigger the decryption process
// M = C^d mod n 
double rsa::decrypt(int ciphertext,int  d,int  n){
    cout << "PROCESSING...\n" << endl;
    cout << "The input CipherText is: " << ciphertext << endl; 
    int ogMessage = powerMod(ciphertext, d, n);
    cout << "The origional message after decryption is: " << ogMessage << endl;
    return ogMessage;
}

// This function will automatic generate P and Q 
// Validate both P Q as prime number before return the value

void rsa::generatePQ(){
    double p=0; 
    double q=0;
    createValue:
    srand(time(NULL));
    do{
        p=rand()%(100-2 +1) + 2; // random between 2 and 100
    }
    while(!isPrime(p));

    do{
        q=rand()%(100-2 +1) + 2;
    }
    while(!isPrime(q));

    if(p == q) 
        goto createValue;

    assignP(p);
    assignQ(q);

    // cout << "P: " << p << endl;
    // cout << "Q: " << q << endl;
}

// This function will be used to generate private and public key based on the user input 
// Take in user's input for P, Q -> Calculate Phi, N -> generate e/d 
// Public exponent will calculate the private exponent and store @Keypair
// Flag to indicate the manual input inside automode
void rsa::autoMode(Keypair &keys, int flag){
    generatePQ(); // 
    int p=getP();
    int q=getQ(); 
    // double p =53; 
    // double q =73; 
    double n; // p*q
    double e,d = 0; // public and private

    cout << "Two number P & Q after being generated:" << p << " and " << q<< endl;
    n=p*q; 
    phi =(p-1) *(q-1);
    int lamda = lcm(p-1, q-1);

    for(int i=3; i<phi; i++){
        if(gcd(i, lamda) == 1){
            tot.push_back(i); // Assign all the value of E into vector
        }
    }

    //Print Vector:
    cout << "vector E = ";
    for(auto i : tot){
        cout << i << " ";
    }
    
    if(flag == 1){ // manual choose encrypt or decrypt{
        gete:
        int userInput;
        bool exitcondition = true;
        while(exitcondition){
            cout << "\nPlease choose e that: 1 < e < phi(n) and does not share any factors with phi."<< endl;
            cin >> userInput; 
            cout << "UserInput: " << userInput << endl;
            for (int i=0; i< tot.size(); i++){ 
                if( tot[i]== userInput){
                e = (userInput);
                cout << "match" <<endl;
                exitcondition = false;
                }
            }   
        }
        d = modInverse(e, phi);
        if(e == d){
            cout << "E and D can not be identical. Please insert another E.";
            goto gete;
        }
    }
    //Assign The value e
    else{
    check:
    int ran = rand() % tot.size(); 
    e= tot[ran]; 
    d = modInverse(e, phi);
    if( e == d)
        goto check;
    }

    keys.privateKey.d = d; 
    keys.privateKey.n = n; 
    keys.publicKey.e = e;
    keys.publicKey.n = n;
    cout<<"The N value is: "<<n<<endl;
    cout<<"The phi(n) is: "<<phi<<endl;
    //cout<<"The lambda(n) is:"<<lamda<<endl;
    cout<<"The toitient e is: "<<e<<endl;
    cout << "TEST D ? : " << d << endl;
    cout << "Public Key = (n, e) = (" << n << ", " << e << ")" << endl;
    cout << "Private Key = (n, d) = (" << n << ", " << d << ")" << endl;
}

void rsa::manualMode(Keypair &keys){
    double p,q; 
    cout << "Please insert P value: " << endl;
    while((!(cin >> p) || (!isPrime(p)|| (p<2) || p>100))){
        cout << "ERROR: Invalid input. Please insert a prime value that less than 100\n Re-enter: ";
        cin.clear();
        cin.ignore(132, '\n');
    }

    cout << "Please insert Q value: " << endl;
    while((!(cin >> q) || (!isPrime(q)|| (q<2) || q>100))){
        cout << "ERROR: Invalid input. Please insert a prime value that less than 100\n Re-enter: ";
        cin.clear();
        cin.ignore(132, '\n');
    }

    double n; // p*q
    double e,d = 0; // public and private
    n=p*q; 
    phi =(p-1) *(q-1);
    int lamda = lcm(p-1, q-1);

    for(int i=3; i<phi; i++){
        if(gcd(i, lamda) == 1){
            tot.push_back(i); // Assign all the value of E into vector
        }
    }
    gete:
        int userInput;
        bool exitcondition = true;
        while(exitcondition){
            cout << "\nPlease choose e that: 1 < e < phi(n) and does not share any factors with phi."<< endl;
            cin >> userInput; 
            cout << "UserInput: " << userInput << endl;
            for (int i=0; i< tot.size(); i++){ 
                if( tot[i]== userInput){
                e = (userInput);
                cout << "match" <<endl;
                exitcondition = false;
                }
            }   
        }
        d = modInverse(e, phi);
        if(e == d){
            cout << "E and D can not be identical. Please insert another E.";
            goto gete;
        }
    
    keys.privateKey.d = d; 
    keys.privateKey.n = n; 
    keys.publicKey.e = e;
    keys.publicKey.n = n;

    cout << "Public Key = (n, e) = (" << n << ", " << e << ")" << endl;
    cout << "Private Key = (n, d) = (" << n << ", " << d << ")" << endl;

    }

void rsa::mainMenu(){
    cout << endl;
    cout<<"===================================================== \n";
    cout << "\t\tRSA- Project\t \n";
    cout<<" \t\tMENU \t \n ";
    cout<<"===================================================== \n";
    cout<<" 1.Encryption Mode\n";
    cout<<" 2.Decryption Mode\n";
    cout<<" 3.Exit\n"; 
    cout<<" PLEASE ENTER YOUR CHOICE: ";
    cin >> choice; 
    if(choice == 1){
        Keypair newKey4Encrypt;
        Keypair encryptManualKey;
       
        int choice;
        do{
        subMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            int subChoice;
            cout<<"===================================================== \n";
            cout << "\t\tPlease Select the Following option:\t \n";
            cout<<"1. E automatical generate \n";
            cout<<"2. Manually enter E\n";
            cout<<"3. Exit \n";
            cout<<"===================================================== \n";
            cout<<"Please Select your answer: ";
            while((!(cin >> subChoice)|| (subChoice <1||subChoice >3))){
                cout << "ERROR: Please Choose only from 1-3";
                cin.clear();
                cin.ignore(132, '\n');
            }
            switch (subChoice)
            {
            case 1:{
                double message2;
                autoMode(newKey4Encrypt, 0);
                cout << "Please insert message that you want to encrypt: ";
                cin >> message2; 
                int cipherText = encrypt(message2, newKey4Encrypt.publicKey.e, newKey4Encrypt.publicKey.n);
                break;
            }
            case 2:{
                double message;
                autoMode(newKey4Encrypt, 1);
                cout << "Please insert message that you want to encrypt: ";
                cin >> message; 
                int cipherText = encrypt(message, newKey4Encrypt.publicKey.e, newKey4Encrypt.publicKey.n);
                break;
            } 
            case 3:{
                break;
            }
            default:
                cout << "Invalid Choice, please Choose again: ";
                break;
            }
            break;    
        }
            
        case 2:
        {   
            Keypair encryptManualKey;
            manualMode(encryptManualKey);
            double messageManual;
            cout << "Please insert message that you want to encrypt: ";
            cin >> messageManual; 
            int cipherText = encrypt(messageManual, encryptManualKey.publicKey.e, encryptManualKey.publicKey.n);
            break;   
        }
        case 3:
        {
            break;
        }
        default:
        {
            cout << "Not a valid choice, Please insert again: ";
            break;
        }
        }
        }
        while(choice != 3);
    }
    else if( choice == 2){

        //PHAI SHOW CAI SUB MENU TRUOC 
        int choice2; 
        do{
            subMenu();
            cin >> choice2;
            switch (choice2)
            {
            case 1:
            {
                    Keypair newKey4Decrypt;
                //manually enter e
                int subChoice2; 
                cout<<"===================================================== \n";
                cout << "\t\tPlease Select the Following option:\t \n";
                cout<<"1. D automatical generate \n";
                cout<<"2. Manually enter D\n";
                cout<<"3. Exit \n";
                cout<<"===================================================== \n";
                cout<<"Please Select your answer: ";
                while((!(cin >> subChoice2)|| (subChoice2 <1||subChoice2 >4))){
                    cout << "ERROR: Please Choose only from 1-3";
                    cin.clear();
                    cin.ignore(132, '\n');
                }
                switch (subChoice2)
                {
                    case 1:{
                        double decryptMessage;
                        autoMode(newKey4Decrypt, 0); 
                        cout << "Please insert ciphertext that you want to decrypt: "; 
                        cin >> decryptMessage;
                        int ogMesasge = decrypt(decryptMessage, newKey4Decrypt.privateKey.d, newKey4Decrypt.publicKey.n);
                        break;
                    }
                    case 2: 
                    {
                        int privateKey; 
                        autoMode(newKey4Decrypt, 0); 
                        cout <<"SAU KHI CHAY AUTO THI PRIVATE KEY K =" << newKey4Decrypt.privateKey.d << endl;
                        // cout << "Please insert your private Key: " << endl; 
                        // while((!(cin >> privateKey) || (privateKey != newKey4Decrypt.privateKey.d))){
                        //     cout << "ERROR: Invalid Private Key D. Please insert it again" << endl;
                        //     cin.clear();
                        //     cin.ignore(132, '\n');
                        // }
                        // cout << "Please enter your cipher text for decryption: ";
                        // double usertext; 
                        // cin >> usertext;
                        // cin.ignore();
                        // double ogMessage = decrypt(usertext, newKey4Decrypt.privateKey.d, newKey4Decrypt.publicKey.e);
                        bool exitcondition = true;
                        while(exitcondition){
                        cout << "Please insert your private Key: " << endl; 
                        cin >> privateKey; 
                        for (int i=0; i< tot.size(); i++){ 
                        double d = modInverse(tot[i], getPhi());

                        if(d == privateKey){
                        cout << "\nCongratuation, You have insert the correct private key!\n" <<endl;
                        exitcondition = false;
                        }
                        }
                    
                        }
                        break;
                    }
                    case 3:
                    {
                        break;
                    }
                    default:
                        cout << "Invalid Choice, Please try again:";
                        break;
                }
            break;
        }
            
        case 2:{
            Keypair newKey;
                manualMode(newKey);
                double messageManual;
                cout << "Please insert the cipher text that you want to decrypt:";
                cin >> messageManual; 
                int ogMessage = decrypt(messageManual, newKey.privateKey.d, newKey.publicKey.n);
            break;
        }
            case 3:{
                break;
            }
            default:
                cout << "Not a valid choice, Please choose again";
                break;
            }
    }
    while(choice2 != 3);
    }
    else if(choice == 3){
        exit();
    }
}
#endif 