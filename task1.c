#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <openssl/sha.h>
#include <string.h>
#define MAX_USER_SIZE 8
#define MAX_PASS_SIZE 10
int main(){
   int passwordFile, option;
   printf("Which password file would you like to use?\n");
   printf("1: Plaintext username-password. \n");
   printf("2: Username and hashed password. \n");
   printf("3: Username, salt and hashed password+salt. \n");
   char line[2];
   fgets(line, 3, stdin);
   sscanf(line, "%d", &passwordFile);
   if(passwordFile != 1 && passwordFile != 2 && passwordFile != 3){
      printf("ERROR:Incorrect selection\n");
      return 0;
      }
   printf("What would you like to do?\n");
   printf("1: Create an account.\n");
   printf("2: Log in. \n");
   fgets(line, 3, stdin);
   sscanf(line, "%d", &option);
   if(option != 1 && option != 2){
      printf("ERROR:Incorrect selection\n");
      return 0;
      }
   int i = 0;
   char userName[MAX_USER_SIZE+1];
   char password[MAX_PASS_SIZE+1];
   for (i = 0; i< MAX_USER_SIZE+1;i++){
      userName[i] = '0';
      }
   for(i = 0; i< MAX_PASS_SIZE+1;i++){
      password[i] = '0';
      }
   printf("What is your username?\n");
   fgets(userName, MAX_USER_SIZE+1, stdin);
   i = 0;
   while(userName[i] != '\n'){
      if(isalnum(userName[i])){
          i++;
   }
      else{
          printf("Error: Username not valid! \n");
	  return 0;
      }
   }
   printf("What is your password?\n");
   fgets(password, MAX_PASS_SIZE+1, stdin);
   i = 0;
   while(password[i] != '\n'){
      if(islower(password[i])){
         i++;
      }
      else{
         printf("Error:Password not valid!\n");
	 return 0;
      }
   }
   FILE *fp;
   char tempUser[MAX_USER_SIZE+1];
   for (i=0; i<MAX_USER_SIZE+1; i++){
      tempUser[i] = 0;
      }
   char tempPass[MAX_PASS_SIZE+1];
   for (i=0; i<MAX_PASS_SIZE+1;i++){
      tempPass[i] = 0;
      }
   unsigned char tempHash[64];
   char tempSalt[9];
   char hashed[64];
   char hashed2[64];
   if(option == 2) {
       switch(passwordFile){
       fflush(stdin);
       case 1:fp =fopen("plaintext.txt", "r");
                while(!feof(fp)){
       		  fscanf(fp, "%s", tempUser);
		  char *p = strchr (tempUser, '\0');
		  *p++ = '\n';
		  fscanf(fp, "%s", tempPass);
		  char *p2 = strchr (tempPass, '\0');
		  *p2++ = '\n';
		  if(strcmp(tempUser, userName) == 0 && strcmp(tempPass, password) == 0){
		     printf("Login Successful!");
		     return 0;
		     }
		  else{
		     }
	      }
	      printf("Incorrect Username or Password! \n");
	      break;
       case 2: fp = fopen("hashed.txt", "r");
		 unsigned char ibuf[MAX_PASS_SIZE+1];
		 unsigned char obuf[32];
              while(!feof(fp)){
	         fscanf(fp, "%s", tempUser);
		 char *p3 = strchr (tempUser, '\0');
		 *p3++ = '\n';
		 fscanf(fp, "%s", tempHash);
		 for(i = 0; i< strlen(password); i++){
		    ibuf[i] = password[i];
		 }
		 SHA256(ibuf, strlen(password)-1, obuf);
		 int j = 0;
		 for(i=0; i<16; i++){
		    sprintf(&hashed[j], "%02x", obuf[i]);
		    j=j+2;
		 }
		 j=0;
                 for(i=16; i<32; i++){
		    sprintf(&hashed2[j], "%02x", obuf[i]);
		    j=j+2;
		 }
		 strcat(hashed, hashed2);
		 if(strcmp(tempUser, userName) == 0 && strcmp((char *)tempHash, hashed) == 0){
		    printf("Login Successful!");
		    return 0;
		    }
		 else{
		 }
              }
	      printf("Incorrect Username or Password!\n");
       	      break;
       case 3:fp = fopen("salt.txt", "r");
              unsigned char ibuf2[MAX_PASS_SIZE+10];
	      unsigned char obuf2[32];
              char passSalt[MAX_PASS_SIZE+2];
	      while(!feof(fp)){
	         memset(passSalt, 0, MAX_PASS_SIZE+9);
		 fscanf(fp, "%s", tempUser);
		 char *p4 = strchr (tempUser, '\0');
		 *p4++ = '\n';
		 fscanf(fp, "%s", tempSalt);
		 char *p5 = strchr(tempSalt, '\0');
		 *p5++ = '\n';
		 strncat(passSalt, password, strlen(password)-1);
		 strncat(passSalt, tempSalt, 1);
		 fscanf(fp, "%s", tempHash);
		 for(i=0;i<strlen(passSalt);i++){
		    ibuf2[i] = passSalt[i];
		 }
		SHA256(ibuf2, strlen(passSalt), obuf2);
		int j = 0;
		for(i=0; i<16; i++){
		   sprintf(&hashed[j], "%02x", obuf2[i]);
		   j=j+2;
		}
		j=0;
		for(i=16; i<32; i++){
		   sprintf(&hashed2[j], "%02x", obuf2[i]);
		   j=j+2;
		}
		strcat(hashed, hashed2);
		if(strcmp(tempUser, userName) == 0 && strcmp((char *)tempHash, hashed) == 0){
		   printf("Login Successful!");
		   return 0;
		   }
		else{
		}
	      }
	      printf("Incorrect Username or Password!\n");
	      break;
       default: printf("Error cannot open files");
       }
   }
   else if(option == 1){
       switch(passwordFile){
       int i;
       case 1: fp = fopen("plaintext.txt", "a+");
               for(i = 0; i<sizeof(userName); i++){
	          if(userName[i] != '\n' && userName[i] !='0'){
	             fprintf(fp, "%c", userName[i]);
		  }
	       }
	       fprintf(fp," ");
	       for (i = 0; i <sizeof(password); i++){
		  if(password[i] != '\n' && password[i] != '0'){
	          fprintf(fp, "%c", password[i]);
		  }
	       }
	       fprintf(fp, "\n");
	       /*fprintf(fp, "%s%s\n", userName, password);*/
	       fclose(fp);
               break;
       case 2: fp = fopen("hashed.txt", "a+");
	       unsigned char ibuf[MAX_PASS_SIZE+2];
	       unsigned char obuf[32];
	       for (i = 0; i < strlen(password); i++){
	          ibuf[i] = password[i];
	       }
               SHA256(ibuf, strlen(password)-1, obuf);
	       for(i = 0; i< sizeof(userName); i++){
	          if(userName[i] != '\n' && userName[i] != '0'){
		     fprintf(fp, "%c", userName[i]);
		     }
		  }
	       fprintf(fp, " ");
	       for (i = 0; i < 32; i++) {
	          fprintf(fp, "%02x", obuf[i]);
	       }
	       fprintf(fp, "\n");
               break;
       case 3: fp = fopen("salt.txt", "a+");
       	       time_t t;
	       char saltArray[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','0','1','2','3','4','5','6','7','8','9'};
	       srand((unsigned) time(&t));
               unsigned char ibuf1[MAX_PASS_SIZE+9];
	       unsigned char obuf1[32];
	       char salt[2];
	       int num;
	       for(i = 0; i<1; i++){
	          num = rand() % 62;
	          salt[i] = saltArray[num];
	       }
	       char message[MAX_PASS_SIZE+9];
	       for(i = 0; i < sizeof(message); i++){
	          message[i] = 0;
	       }
	       strncat(message, password, strlen(password)-1);
	       strncat(message, salt, 1);
	       for(i = 0; i< strlen(message);i++){
	          ibuf1[i] = message[i];
	       }
	       SHA256(ibuf1, strlen(message), obuf1);
	       for(i = 0; i < sizeof(userName);i++){
	          if(userName[i] != '\n' && userName[i] != '0'){
		     fprintf(fp, "%c", userName[i]);
		     }
	       }
	       fprintf(fp, " ");
	       for(i =0; i<1;i++){
	          fprintf(fp, "%c", salt[i]);
	       }
	       fprintf(fp, " ");
	       for(i = 0; i < 32; i++){
	          fprintf(fp,"%02x", obuf1[i]);
	       }
	       fprintf(fp,"\n");
	       break;
       default: printf("Error cannot open files");
       }
   }
   return 0;
}
