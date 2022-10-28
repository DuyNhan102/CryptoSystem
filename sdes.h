//INFO3006 
//October 10th, 2022
//Code by DuyNhan Ta

#include <iostream>
#include<string>
#include<vector>


#ifndef SDES_H_
#define SDES_H_

//***************VARIABLE***************
using namespace std;
            static int round1_key[9], round2_key[8];
            static int selection = 0;
            static int *round_text1, *cipher_text, *round_text2;

//***************CLASS***************
class sdes{
    public:
            int getk();
            int getS0(int r, int c);
            int getS1(int r, int c);
            void menu();
            void exit();
            void p10(int key[]);
            void p8(int key[]);
            void left_shift(int leftHalf[], int rightHalf[], int shiftTime);
            void IP(int plainText[]);
            void InverseIP(int plainText[]);
            void p4(int s0s1[]);
            int* decrypt(int plainText[],int* round_text,int key[]);
            int* encrypt(int plainText[],int* round_text,int key[]);
            int* EP(int right_half[]);
            int* createKey(int key[], int round);
            int* rounds(int pt[], int key[], int round_number, int flag);
            void XOR(int arr1[], int arr2[]);
            int bin2dec(int arr[], int size);
            int EP2 (int right_half[], int output[]);
    private:
            int k = 0;  
};

//***************FUNTIONS***************
// This function transfer from binary to decimal
int sdes::bin2dec(int arr[], int size){
    int dec = 0 ;
        for(int i = 0 ; i < size ; i++)
            dec = (dec << 1) + arr[i] ;
        return dec;
}

// This function is used to return k value
int sdes::getk(){
    return k;
}
//This function is used to exit the program
void sdes::exit ()
    {
       cout << endl;
       cout << " Hope you have fun time playing with S-DES algorithm. See you again\n";
       k = 1;
    }
// The key of 10 bits will be input into p8 table
// output: array of permuted bits
void sdes::p8(int key[]){
    //Input:  1 2 3 4 5 6  7 8 9 10
	//Output: 6 3 7 4 8 5 10 9

    int array[8] = {6,3,7,4,8,5,10,9};// initialize output from p8 table
    int backupKey[10];

    //Copy the key
    for(int i =0; i< 10; i++){
        backupKey[i]= key[i];
    }

    for( int i=0; i< 8; i++){
        key[i] = backupKey[array[i]-1]; //lay cai value cua input key dua tren index duoc tao ra output[i] 
        //cout << key [i] << "\t";
    }
}
//This function will perform XOR operation 
    void sdes::XOR(int arr1[], int arr2[]){
        int temp[8];
        for(int i=0; i<8; i++)
        {
            temp[i] = arr1[i] ^ arr2[i];
        }
        for (int i=0; i<8; i++)
            arr2[i] = temp[i];
    }
// The key of 10 bits will be input into p10 table
// output: array of permuted bits
void sdes::p10(int key[]){
    //Input:  1 2 3 4 5 6  7 8 9 10
	//Output: 3 5 2 7 4 10 1 9 8 6 

    int array[10] = {3,5,2,7,4,10,1,9,8,6}; // initialize output from p10 table
    int backupKey[10];

    //Copy the key
    for(int i= 0; i< 10; i++){
        backupKey[i] = key[i];
    }

    for (int i=0; i< 10; i++){
        //permute the bits
        key[i] = backupKey[array[i]-1]; 
        //cout << key [i] << "\t";
    }

}

// 2 key of 5 bits will be input into p4 table
// output: array of permuted bits
void sdes::p4(int s0s1[]){
    //In 1 2 3 4
    //Out 2 4 3 1right_half
    int array[4] = {2,4,3,1};
    int temp[4];

    for(int i=0; i<4; i++)
        temp[i] = s0s1[i];

    for(int i =0; i<4; i++){
        s0s1[i] = temp[array[i]-1];
    }

}
// This funtion is used to do the one bit left shift on each half
void sdes::left_shift(int leftHalf[], int rightHalf[], int shiftTime){

    //back up the first value of each half because we have to use it for later
    int backup1 = leftHalf[0]; 
    int backup2 = rightHalf[0];
    // Shift the array to the left 1 
    // run the loop from 0-3 and 4th element will be assign manually
    for(int i=0; i<4; i++){
        leftHalf[i] = leftHalf[i+1]; 
        rightHalf[i] = rightHalf[i+1];
    }
    leftHalf[4] = backup1; //value of the first index go to the last index inside array after LS-1
    rightHalf[4] = backup2; //value of the first index go to the last index inside array after LS-1


    if( shiftTime == 2){
        left_shift(leftHalf, rightHalf, 1); 
    }
}
// this function will generate the key  after each round in the Key generator process
// If round == 1 return Key1[]
// If round == 2 return Key2[]
int* sdes::createKey(int key[], int round){
    //divide 10 bits key into left half and right half
    int left_half[5], right_half[5];
    static int key1[10], key2[8];
    //assign the input key to p10 table
    p10(key); 
    //divide the key into 2 half
    for(int i=0; i<10; i++){
        if(i < 5 ){// left half
            left_half[i] = key[i];
        } 
        else {// Right half
            right_half[i-5] = key[i];
        }
        }

    //left shift on both left half and right half
    left_shift(left_half, right_half, 1);

    //Join Left and Right half back to form a key store in key1 array
    for(int i=0; i < 5; i++){
        key1[i] = left_half[i]; 
        key1[i+5] = right_half[i];
    }

    if(round == 1){
    p8(key1);
    return key1; 
    }
    //For generation of key 2
    else{
        left_shift(left_half, right_half, 2); // left shift 2 
        //Join the key back together store in Key 2 array
        for(int i=0; i<5; i++){
            key2[i]= left_half[i];
            key2[i+5]= right_half[i];
        }
        p8(key2);
        return key2;
    }
}
// This function will assogm plainText into initial permutation table (IP-8)
// And permute the bits
void sdes::IP(int plainText[]){
    ///In:  1 2 3 4 5 6 7 8 
	//Out: 2 6 3 1 4 8 5 7 

    int out[8] = {2,6,3,1,4,8,5,7};
    int backup[8];

    for(int i= 0; i< 8; i++){
        backup[i] = plainText[i];
    }

    for (int i=0; i< 8; i++){
        plainText[i] = backup[out[i]-1];
        //cout << plainText[i] << "\t";
    }

}

void sdes::InverseIP(int plainText[]){
    int array[8] = {2,6,3,1,4,8,5,7};
    int temp[8];

    for(int i=0; i<8; i++){
        temp[i] = plainText[i];
    }

    for(int i=0; i<8; i++){
        plainText[array[i]-1] = temp[i];
    }
}

// This function will assign right half 4 bits into expand and permutate table EP
// And permute the bits
int* sdes::EP(int right_half[]){
    //right[1,2,3,4]
    //out: 8 bits: [4 1 2 3 2 3 4 1 ]
    int array[8] = {4,1,2,3,2,3,4,1};
    int temp[4]; 
    static int expand_right[8];
    //copy the array for backup
    for(int i=0; i< 4; i++)
        temp[i] = right_half[i];
    //assign the value    
    for(int i=0; i<8; i++){
        expand_right[i]=temp[array[i]-1];
    }
    return expand_right;
}

// This function will return the value inside the s0 Table by collumn and row
int sdes::getS0(int r, int c){
    int s0[4][4]= { //4 *4 matrix in binary     
            {01,00,11,10},
			{11,10,01,00},
			{00,10,01,11},
			{11,01,11,10}
    };
    return s0[r][c];
}
// This function will return the value inside the s0 Table by collumn and row
int sdes::getS1(int r, int c){
    int s1[4][4]={
            {00,01,10,11},
			{10,00,01,11},
			{11,00,01,00},
			{10,01,00,11}
    };
    return s1[r][c];
}
// This function will encrypt using sdes algorithm 
// return ciphertext

int* sdes::encrypt(int plainText[],int* round_text,int key[]){
    //roundText will be the return value after encryption
    //
    round_text = rounds(plainText, key, 1, 0); 
    InverseIP(round_text);
    cout<<"\n\n-------------CIPHER TEXT-------------\n";

    for(int i=0; i<8; i++)
        cout << round_text[i];
    return round_text;    

}
// This function wi;; decrypt the cipher text with secret key
// return original message
int* sdes::decrypt(int plainText[],int* round_text,int key[]){
    //roundText will be the return value after encryption
    //
    round_text = rounds(plainText, key, 1, 1); 
    InverseIP(round_text);
    cout<<"\n\n------------PLAIN TEXT-------------\n";

    for(int i=0; i<8; i++)
        cout << round_text[i];
    return round_text;    

}
//This function will start the sdes process
// round number start with 1.
// flag 1 for encryption, 2 for decryption
int* sdes::rounds(int pt[],int key[],int roundNum,int flag)
{
	int left[4],right[4],*expanded_right,s0[4],s1[4],temp_key[10];
    int expanded_right2[8];
	cout<<"\nROUND-"<<roundNum;
	for(int i=0;i<10;i++)
	{	
		temp_key[i]=key[i];		//backup the key
	}
	if(roundNum==1)
	IP(pt);	

	
    //Divide the plainText after IP into 2 halves
	for(int i=0;i<4;i++)
	{
		left[i]=pt[i];
		right[i]=pt[i+4];
		//cout<<left[i];
	}
	expanded_right= EP(right); // doing EP with right halves
	 for(int i=0;i<8;i++)
	 	expanded_right2[i] = expanded_right[i];

	static int* key1;
	if(flag==0)	    // Flag == 0 for encrypt
	{	key1=createKey(key,roundNum);		//key1 in round1 and key2 in round2 during key generation process
		cout<<"\n\nEncrypt Key of Round "<<roundNum<<endl;
		for(int i=0;i<8;i++)
		{	
			cout<<key1[i];
		}
	}
	else	//else flag=1 for decrypt
	{
		if(roundNum==1)			//if round1 use key2
		{
            key1 = createKey(key, roundNum +1); // first use key2 for decrypt
		}
		else				//if round2 use key1
		{
            key1 = createKey(key, roundNum -1);
        }	
		
		cout<<"\n\nDecrypt Key use forRound "<<roundNum<<endl;
		for(int i=0;i<8;i++)
		{	
			cout<<key1[i];
		}
	}

    // XOR with key1
    for(int i=0;i<8;i++)
	{
		expanded_right2[i]=expanded_right2[i] ^ key1[i];
    }


	for(int i=0;i<4;i++)
	{   
        //Perform EXOR operation from EP and key1
        // EXOR [1 2 3 4 5 6 7 8]
        // S0  [1 2 3 4]
        // S1  [5 6 7 8]
			s0[i]=expanded_right2[i]; // assign first 4 bits to S0
			
	}
    int n = 0;
    int k =4;
    for(n, k; k<8; n++, k++){
        s1[n] = expanded_right2[k];
    }

    /*RULES: First and Last bits of S0 is for Row
             Whatever left in the middle is for Collunn
    After that transfer the bit to number to have row and collumn*/

    int arrayStoreRown[2];
    arrayStoreRown[0] = s0[0];
    arrayStoreRown[1] = s0[3];
    int row = bin2dec(arrayStoreRown, 2);

    int arrayStoreCol[2];
    arrayStoreCol[0] = s0[1];
    arrayStoreCol[1] = s0[2];
	// int row=s0[3]+(s0[0]*2); 
	// int column=s0[2]+(s0[1]*2);
    int column = bin2dec(arrayStoreCol, 2);
    
	static int s0s1[4];
	int ss0=getS0(row,column);

	row=s1[3]+(s1[0]*2);
	column=s1[2]+(s1[1]*2);

	int ss1=getS1(row,column);

    //create s0s1[]
    s0s1[0]=ss0/10;
	s0s1[1]=ss0%10;
	s0s1[3]=ss1%10;
	s0s1[2]=ss1/10;

	p4(s0s1);

	static int newText[8];
	//s0s1 EXOR Left_Half from step 1
	for(int i=0;i<4;i++)
	{
		s0s1[i]=s0s1[i] ^ left[i];
		//swap the s0s1 and right half from step 1 to generate plain text for next round
		if(roundNum!=2)		//if round is not 2nd one and it's not for decoding
		{
			newText[i]=right[i];
			newText[i+4]=s0s1[i];
		}
		else							//else don't swap
		{
			newText[i+4]=right[i];
			newText[i]=s0s1[i];	
		}
	}

	/*cout<<"\n\ns0s1:\n";
	for(int i=0;i<4;i++)
		cout<<s0s1[i];
	*/
	cout<<"\n\nRound "<<roundNum<<" Output:\n";
	for(int i=0;i<8;i++)
		cout<<newText[i]<<"\t";
	cout<<endl;

	

	if(roundNum==1)
	{
		if(flag==0)		//if encoding
			rounds(newText,temp_key,2,0);
		else			//else decoding
			rounds(newText,temp_key,2,1);
	}
	else
	{
		return newText;
	}

}


void sdes::menu ()
   {
    cout << endl;
    cout<<"===================================================== \n";
    cout<<" \t\tMENU \t \n ";
    cout<<"===================================================== \n";
    cout<<" 1.Encryption\n";
    cout<<" 2.Decryption\n";
    cout<< "3.Exit\n"; 
    cout<< "PLEASE SELECT YOUR CHOICE: " ;
        cout << " ";
        cin >> selection;

   if (selection == 1)
   {
    int plainText[8], key[10];
    cout<<"\nEnter the plain text (8-bits) [Please using space] :";
	for(int i=0;i<8;i++)
		cin>>plainText[i];
           
    cout << "\n Enter the Key (10-bits) :";
    for(int i = 0; i<10; i++)
        cin >> key[i];
    encrypt(plainText,round_text1,key);	
   }
   else if (selection == 2)
   {
    int cipherText[8], key[10];
    cout<<"\nEnter the cipher text (8-bits) [Please using space] :";
	for(int i=0;i<8;i++)
		cin>>cipherText[i];
           
    cout << "\n Enter the Key (10-bits) :";
    for(int i = 0; i<10; i++)
        cin >> key[i]; 

    decrypt(cipherText, round_text2, key);
   }
   else if (selection == 3)
   {
       exit();
   }
   }


#endif 