#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_SIZE 256

int main ()
{
	FILE *fptr;
	srand((unsigned int)(time(NULL)));
	char pass[100];
	int lengthpass; //lenght of password
	int lengthnumpass; //number of passwords
	unsigned char ibuf[lengthpass];
	unsigned char hashbuf[32];

	//Part of code for the length of the passwords
	printf("Please enter the length of passwords: ");
	scanf("%d", &lengthpass);

	//while to make sure the length of the password is from 3 to 8
	while (lengthpass < 3 || lengthpass > 8) {
		printf("Password length is not between 3 and please enter it again");
		scanf("%d", &lengthpass);
	}

	//Part of code that asks for the number of passwords to be created
	printf("Please enter the number of passwords you want to create: ");
	scanf("%d", &lengthnumpass);

	//int length = 1;
	int len = 8;
	char src[50], dest[50]; 
	char s[8];
	char salt[1];
	static const char alphanum[] = "0123456789abcdefghijklmonpqrstuvwxyz"; //Created for the usage of randomized usernames
	int k;
        int j;
	int i;
	int p;

	//Part of code that makes just the username and password and stores it into plaintext.txt
	for(j = 0; j < lengthnumpass; j++) {
		fptr = fopen("plaintext.txt", "a+");
			for( i = 0; i < lengthpass; i++) {
				pass[i] = 97 + rand() % 26; //Part of code that creates the random password
				//Part of code that creates the randomized username
				for(k = 0; k < len; k++) {
					s[k] = alphanum[rand() % (sizeof(alphanum) - 1)];
				}
			}
	s[len] ='\0';				
	pass[i] = '\0';
	fprintf(fptr, "%s %s\n", s, pass);
	fclose(fptr);
	}

	//Part of code that makes the username, password, and hashes the password and stores it into hashed.txt
	for (j = 0; j < lengthnumpass; j++) {
	fptr = fopen("hashed.txt", "a+");
	fprintf(fptr, "\n%s  ", s);
	pass[i] = '\0';
        	for (i = 0; i < lengthpass; i++) {
			pass[i] = 97 + rand() % 26;	//Creates random password

			//Creates random username
			for (k = 0; k < len; k++) {
				s[k] = alphanum[rand() % (sizeof(alphanum) - 1)];
			}
		}

		//Hashes the password
		for ( i = 0; i < lengthpass; i++) {
			ibuf[i] = pass[i];
			SHA256(ibuf, strlen(pass), hashbuf);
			for (i = 0; i < 32; i++) {
				hashbuf[i];
				fprintf(fptr, "%02x", hashbuf[i]);
			}
			
		
		}
	s[len] = '\0';
	fclose(fptr);
	}

	//This part of code that creates username, password, salt, and hashes the password+salt
	for (j = 0; j < lengthnumpass; j++) {
	fptr = fopen("salt.txt", "a+");
        fprintf(fptr, "\n%s %c " , s, salt[1]);       
                for (i = 0; i < lengthpass; i++) {
                        pass[i] = 97 + rand() % 26;
			for (p = 0; p < 1; p++) {
				salt[p] = alphanum[rand() % (sizeof(alphanum) -1)];
				//fprintf(fptr, " %c ", salt[0]);
			}
			for(k = 0; k < len; k++) {
                                s[k] = alphanum[rand() % (sizeof(alphanum) - 1)];
                        }
		}
		

		
		//part of code that hashes the password+salt
		for(i = 0; i < lengthpass; i++) {	
			//fprintf(fptr, "%s ", salt); 
		        /*
			for(p = 0; p < 1; p++) {
				salt[p] = alphanum[rand() % (sizeof(alphanum) -1)];				
				//fprintf(fptr, "%s ", salt);
			} 
			*/
			
			strcpy(dest, &pass[i]); 
			strcpy(src, &salt[p]);
			strncat(dest, src, 100);
			ibuf[i] = dest[i];
			SHA256(ibuf, strlen(dest), hashbuf);
			for(i = 0; i < 32; i++) {
                                fprintf(fptr, "%02x", hashbuf[i]);
                        }
             
                }
	//fprintf(fptr, " %s ", salt);
	pass[i] = '\0';
	s[len] = '\0';
	fclose(fptr);
        }
}
