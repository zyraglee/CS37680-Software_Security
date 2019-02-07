//Password Hash and Salt Cracker
//Zyra De Los Reyes
//Software Security
#include <string>
#include <sstream>
#include <iostream>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
//include our openssl header
#include <openssl/sha.h>
using namespace std;

struct HashedFiles{
	string user[100];
	string password[100];
	string hashed[100];
	string salt[100];
	int length;	

};
//variables for iterating through loop
int a,b,c,d,e,f,g;

//string array for characters we will iterate through
string alpha[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};

//for salt
string alphaNum[] = {"0","1","2","3","4","5","6","7","8","9",
		   "a","b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
		   "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
//begin openssl function
string sha256(const string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}
//end openssl function

int main (int argc,char* argv[])

{

        HashedFiles hf;
        ifstream file;
        file.open(argv[1]);
	int pos; //index position in file
	hf.length = atoi(argv[2]);
	
	if (!file) {
                cout << "Unable to open file.\n Usage: "<<argv[0] <<  "[file.txt] [password max]"<<endl;
                return 1; // terminate with error
        }
	
	if(argv[1] == string("hashed.txt")){ 
        for(int i = 0; i < 100 ; i++){
                file >>hf.user[i] >> hf.password[i] >> hf.hashed[i];
		//cout <<i+1 << " "<< user[i] <<  " " << password[i] <<  " " << hashed[i] << endl;	
	}
	// I could have an in n to randomize value of index between 0-99 but 
	// keeping it to an arbitrary position i picked for now

	pos = 16;
	string hashedKey = hf.hashed[pos];
	string userName = hf.user[pos];

	std::string crackhash = hashedKey;
	
	for (a=0; a<26; a++){
		for (b=0; b<26; b++){
			for (c=0; c<26; c++){
				for(d = 0; d < 26; d++){
				//concatinate strings variables a, b, c, d and g into standard string s
					std::string s = static_cast<std::ostringstream&>(std::ostringstream().seekp(0) << alpha[a] << alpha[b] << alpha[c]<<alpha[d]).str();
//				cout << "password " << s << " hash " << sha256(s) << endl;

				//begin string comparison
				//compare output of sha256(s) with the user input. if they are the same output the plaintext of s and password found

  					std::string passhash = sha256(s);
  					std::string password = s;
				
  					if ( passhash==crackhash){ 
						std::cout << "\n" << "Password found at index " << pos << endl;;
						cout <<  "Hashed Password: " << passhash << "\n" <<"Decoded Password: "  << password << "\n"<< "Length: " << hf.length << "\n"<< "Matched Username: "<< userName << endl;
  						return 0;
					}
				}
			}
		}
	
	}
	}//end of if
	else{
		//picking an arbitrary value
		 
		//dividing this by column
		for(int i = 0; i < 100 ; i++){
                	file >>hf.user[i] >> hf.salt[i] >> hf.hashed[i];
		//	cout << i + 1 <<" " << hf.salt[i] << endl;
		}
		pos = 84; // an arbitrary number i picked, maybe i can rand() this so its different everytime		    
		string salty = hf.salt[pos];
		string saltedHash = hf.hashed[pos];
		string userSalt = hf.user[pos];
		string crackhash = saltedHash;
		//cout << saltedHash;
		for (e = 0; e < 62; e++){
			string saltChar = alphaNum[e];
			if (saltChar == salty){
				cout << "Salt character found: " << saltChar<< endl;
				
				for (a=0; a<26; a++){
				for (b=0; b<26; b++){
				for (c=0; c<26; c++){
				for (d =0;d<26; d++){
					std::string ss = static_cast<std::ostringstream&>(std::ostringstream().seekp(0) << alpha[a] << alpha[b] << alpha[c]<<alpha[d]).str();
					    string s = ss + saltChar;
					    //cout <<"password " << s << " hash " << sha256(s) << endl;	
					    std::string passhash = sha256(s);
  					    std::string password = s;
					    if ( passhash==saltedHash){ 
						std::cout << "\n" << "Password found at index " << pos << endl;;
						cout <<  "Hashed Password: " << passhash << "\n" <<"Decoded Password: "  << password << "\n"<< "Length: " << hf.length << "\n"<< "Matched Username: "<< userSalt << endl;
  						return 0;
					}

				}
				}
				}
				}
			}

		}
		
		//
		




	   }
	

}
