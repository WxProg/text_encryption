/* ================================================================
PROGRAM Simple Text Encryption

        AUTHOR: <Antwon Bryce>
        FSU MAIL NAME: <acb19d>
        RECITATION SECTION NUMBER: <03>
        RECITATION INSTRUCTOR NAME: <Samuel Ostlund>
        Course Information: <COP 3014>
        Project Number: <5>
        Due Date: <Wednesday 24, 2021>
        PLATFORM: Windows OS / CLion IDE

SUMMARY

This program will be used to encrypt and decrypt two given text file using substitution & caesar cypher.
The substitution cypher uses a fixed substitution. The Caesar cypher, shifts the alphabet by a fixed number
of places,then uses simple substitution.

INPUT

The user is prompted to make a choice. The user is prompted to enter a valid file name that contains the encrypted
text. If file name is incorrect, the program restarts.

OUTPUT

Prints out the echoprint of all data as well as the decoded text message.


ASSUMPTIONS

- The maximum length of a text line is 80 characters.
- Data files are valid and not empty.
- If invalid is entered, program restarts and prompts user for a valid filename.

 */
/* ================================================================ */

#include <string>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <array>

using namespace std;

//decrypt the encrypted data.
string decryption (char *alphabet, string decryptionKey, string encryptData );
//shift the array base on the shift amount provided in the file
string shiftArray(char alphabet[], int shiftAmount);
//deals with the substitution decryption
void substitutionCypher();
//deals with the caesar cypher
void caesarCypher();

int main() {
    //holds the choice from user input
    char choice = 's';

    //loop until user enters q for quit
    while(choice != 'q'){
        //menu
        cout <<"***************************************" << endl;
        cout <<"\nWhat would you like do?" << endl;
        cout <<"To decode a text file using the substitution cypher, press s." << endl;
        cout <<"To decoded a text file using the caesar cypher, press c." << endl;
        cout <<"To quit decoding, press q." << endl;
        cout <<"What was your choice? ", cin >> choice;


        switch (choice) {
            case 's':
                substitutionCypher();
                break;
            case 'c':
                caesarCypher();
                break;
            case 'q':
                break;
            default:
                cout << "Invalid input" << endl;
                break;
        }
    }
    return 0;
}

//decrypt the encrypted data.
string decryption (char *alphabet, string decryptionKey, string encryptData ){
       //stores the index of the decrypt letter
       int foundIndex = -1;

       //loops through the encrypted data
       for ( int i = 0; i < encryptData.length(); i++){

           //loop through the key to find the index to get the decrypted data
           for (int j = 0; j < decryptionKey.length(); j++){
               // check for the encrypted data in the key
               if ( toupper(encryptData[i]) == toupper(decryptionKey[j])) {
                   foundIndex = j; //index of key found
                   break;
               } else {
                   foundIndex= -1; //index of key not found
               }

           }

           //if found
           if(foundIndex > -1){
               //change the encrypted data
               encryptData [i] = alphabet[foundIndex];
           }

       }
       return encryptData;
}

void substitutionCypher(){
    string fileName; //file name
    string line; // stores each line from file
    string cypherCode; // stores the key use to decrypt
    int count= 0;
    //alphabet use to decrypt
    char alphabet [26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U',
                          'V','W','X','Y','Z'};

    cout << "Please enter file name to decode -> ", cin >> fileName;
    ifstream cypherFile(fileName);// read file

    //check if file exists
    if (!cypherFile.is_open()){
        cout << "Incorrect file" << endl;
        return;
    }

    //reading line by line
    while(getline(cypherFile, line)){

       //get the first line that holds the decryption key
        if(count <= 0){
            cypherCode = line;
            cout << "=> " <<endl;
        }else{
            //decrypting the data input and displaying it
            string result = decryption(alphabet, cypherCode, line);
            cout << line << endl;
            cout << "=> " << result << endl;
        }
        count++;
    }
}
void caesarCypher(){
    string fileName;
    string line; // stores each line from file
    int shiftCount; //holds the amount to shift by
    string cypherCode;// stores the key use to decrypt

    //alphabet use to decrypt
    char alphabet [26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U',
                          'V','W','X','Y','Z'};

    cout << "Please enter file name: " << endl;
    cin >> fileName;
    ifstream cypherFile(fileName);// read file

    //check if file exists
    if (!cypherFile.is_open()){
        cout << "Incorrect file" << endl;
        return;
    }

    //get shift count
    cypherFile >> shiftCount;
    cout << shiftCount << endl;

    //shift the alphabet to get the decryption code
    cypherCode = shiftArray(alphabet,shiftCount);

    //reading line by line
    while(getline(cypherFile, line)){

        //decrypting the data input and displaying it
        string result = decryption(alphabet, cypherCode, line);
        cout << line << endl;
        cout << "=> " << result << endl;
    }
}

//shifting the array
string shiftArray(char alphabet[], int shiftAmount){

    string tempString = "";
    int count = 0;

    //adding the alphabet to a temp array shifted
    for(int i = shiftAmount; i < 26; i++){
        tempString.push_back(alphabet[i]);
        count++;
    }

    count = 0;

    //adding the first group of elements that was shifted
    for(int i = (26-shiftAmount); i < 26; i++){
        tempString.push_back(alphabet[count]);
        count ++;
    }

    return tempString;
}