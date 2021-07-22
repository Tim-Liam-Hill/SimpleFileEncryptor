#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>

using namespace std;

//argc will always be at least 1  to account for name of executable program. the first argv starts at index 1
//index 2 is for the key. index 3 holds either 'd' for decrypt or 'e' for encrypt
//Decrypting will always create a new file
//Encrypting will also create a new file
void encryptFile(string);
void decryptFile(string);

//Global Variables are generally best avoided. In this specific program however, they prove convenient
//Still, it would be better practice to have them declared in the main file and pass them to the functions that
//need them
//That, or possibly store them in a struct. This program is just a simple experiment however, so
//Ill let myself off the hook just this once.
string unencryptedFileName = "imp.txt"; //file
string encryptedFileName = "enc.txt";   //enc
string decryptedFileName = "dec.txt";   //dec

void setFlags(int argc, char ** argv)
{
	if(argc % 2 != 1)
	{
		cout<<"Flags set incorrectly"<<endl;
		cout<<"use -enc 'name' to set the name of the encrpyted file"<<endl;
		cout<<"use -dec 'name' to set the name for the decrypted file to be produced"<<endl;
		cout<<"use -file 'name' to input the name of the file to be encrpyted"<<endl;
		throw "Flag error";
	}

	for(int i=3; i<argc; i+=2){
		string temp = string(argv[i]);
		if(temp == "-enc")
			encryptedFileName = argv[i+1];
		else if(temp == "-dec")
			decryptedFileName = argv[i+1];
		else if(temp == "-file")
			unencryptedFileName = argv[i+1];
		else{
			cout<<"Invalid flag set: '"<<argv[i]<<"' "<<endl;
			throw "Invalid flag";
		}
	} 

	return;
}

int main(int argc, char ** argv)
{
	
	if(argc < 3)
	{
		cout<<"Invalid number of command line arguments"<<endl;
		cout<<"Try (Encryptor.exe 'key' 'e/d')"<<endl;
		return 0;
	}

	string key = argv[1]; 
	string choice = argv[2];

	if(argc > 3)
		setFlags(argc, argv);
		
	if(choice == "d")
	{
		cout<<"Decrypting file"<<endl;
		decryptFile(key);
		cout<<"File Decrypted"<<endl;
	}
	else if(choice == "e")
	{
		cout<<"Encrypting file"<<endl;
		encryptFile(key);
		cout<<"File Encrypted"<<endl;
	}
	else
	{
		cout<<"Invalid option entered (Encryptor.exe 'key' 'e/d')"<<endl;
	}
	
	return 0;
}

string encryptCharacter(char  c, char keyChar)
{
	int val = (c - ' ') + (keyChar - ' ');
	if(val >= 95)
		val = val % 95;
	char encChar = val + ' ';
	string ret(1, encChar);
	return ret;
}

string decryptCharacter(char c, char keyChar)
{
	int val = (c - ' ') - (keyChar - ' ');
	if ( val < 0)
		val += 95;
	char encChar = val + ' ';
	string ret(1, encChar);
	return ret;
}

void encryptFile(string key)
{
	fstream encryptedFile;
	encryptedFile.open(encryptedFileName, ios::out); //ios::out seems to overwrite by default

	if(!encryptedFile)
	{
		cout<<"Could not open/create Encrypted File"<<endl;
		encryptedFile.close();
		throw "File error";
	}

	fstream plainTextFile;
	plainTextFile.open(unencryptedFileName, ios::in); //read

	if(!plainTextFile)
	{
		cout<<"Could not open plain text file - is it called "<<unencryptedFileName<<" ?"<<endl;
		plainTextFile.close();
		throw "File error";
	}


	string line = "";
	string newline = "";
	int indexOfKey = 0;
	while(!plainTextFile.eof())
	{
		getline(plainTextFile, line, '\n');
		newline = "";
		for(int i=0; i<line.length(); ++i)
		{
			if(indexOfKey == key.length())	//we want the key to wrap around with each line as opposed to restarting on each line
				indexOfKey = 0;
			newline += encryptCharacter(line[i], key[indexOfKey]);
			indexOfKey ++;
		}
		newline += "\n";
		encryptedFile << newline;
	}


	encryptedFile.close();
	plainTextFile.close();
}

void decryptFile(string key)
{
	fstream encryptedFile;
	encryptedFile.open(encryptedFileName, ios::in); 

	if(!encryptedFile)
	{
		cout<<"Could not open Encrypted File"<<endl;
		encryptedFile.close();
		throw "File error";
	}

	fstream decryptedFile;
	decryptedFile.open(decryptedFileName, ios::out); 

	if(!decryptedFile)
	{
		cout<<"Could not open/create decrypted file - is it called "<<decryptedFileName<<" ?"<<endl;
		decryptedFile.close();
		throw "File error";
	}

	string line = "";
	string newline = "";
	int indexOfKey = 0;
	while(!encryptedFile.eof())
	{
		newline = "";
		getline(encryptedFile, line);

		for(int i=0; i<line.length(); ++i)
		{
			if(indexOfKey == key.length())	//we want the key to wrap around with each line as opposed to restarting on each line
				indexOfKey = 0;
			newline += decryptCharacter(line[i], key[indexOfKey]);
			indexOfKey ++;
		}
		newline += "\n";
		decryptedFile << newline;
	}

	decryptedFile.close();
	encryptedFile.close();

}