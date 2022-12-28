// ConsoleApplication1.cpp : Defines the entry point for the console application.
//


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//must be 8 char
//less than 15
//must have one Upper and one Lower case letter
//one digit
//must have string 4 char
//cannot have username
//can only have numbers and letters
//checks 8 char min


bool minLength(const char *password){

    return  (strlen(password) >= 8);

}

bool maxLength(const char *password){

    return (strlen(password) <= 15);

}

bool isUpper(const char password){

    return password >= 'A' && password <= 'Z';

}

//checks if 1 upper case
bool upperCase(const char *password){

    while (*password != '\0'){

        if (isUpper(*password)){
            return true;
        }

        password++;

    }

    return false;
}

bool isLower(const char password){
    return password >= 'a' && password <= 'z';

}
//checks if 1 lower case
bool lowerCase(const char *password){
    while (*password != '\0'){

        if (isLower(*password)){
            return true;
        }

        password++;

    }
    return false;

}

bool isDigit(const char password){
    return password >= '0' && password <= '9';
}

//checks if atleast 1 digit
bool contDigit(const char *password){

    while (*password != '\0'){

        if (isDigit(*password)){
            return true;
        }

        password++;

    }
    return false;



}

//checks if string of 4 char
bool stringCheck(const char *password){

    int count = 0; //counts 4 letters in a row

    while (*password != '\0') {
        if ((isLower(*password) || isUpper(*password))) {
            count++;


            if (count == 4) {
                return true;

            }
        }
        else {
            count = 0;

        }
        ++password;

    }

    return false;



}

//checks for allowed chars
bool allowedChars(const char *password){

    while (*password != '\0') {

        if (!(isUpper(*password) || isLower(*password) || isDigit(*password))) {
            return false;

        }


        ++password;

    }

    return true; //returns false is there are special chars

}

//converts uppercase to lowercase for username check



//compares parts of strings
bool containsSubstring(const char *string1, const char *string2) {

    int j = 0;
    int len1 = strlen(string1);
    int len2 = strlen(string2);

    for (int i = 0; i <= len2 - len1; i++){

        for (j = 0; j<len1; j++){
            if (string2[i + j] != string1[j]){

                break;

            }

        }
        if (j == len1){
            return true;

        }
    }

    return false;

}
/////////////////////////////////////////////////////////////////////////////////////////////////
void convertUtoL(const char *source, char *dest){

    while (*source != '\0'){
        if (isUpper(*source)){
            *dest = *source + 32;


        }
        else {
            *dest = *source;
        }

        dest++;
        source++;

    }

    *dest = '\0';

}



//checks for no username
bool user(const char * username, const char *password){

    char *tempUserName[strlen(username)];
    convertUtoL(username, tempUserName);
    char *tempPassword[strlen(password)];
    convertUtoL(password, tempPassword);


    //compares lowercase username and lowercase password
    bool contains = containsSubstring(tempUserName, tempPassword);

    //lowerCase(password);

    return contains;  //means password contains username
}


bool isStrongPassword(const char * username, const char * password) {


    return minLength(password) && upperCase(password) && lowerCase(password) && contDigit(password) && stringCheck(password) &&
           allowedChars(password)&& !user(username, password) ;
    //
}


//checks if defualt is good
bool isStrongDefaultPassword(const char * username, const char * password) {

    return maxLength(password) && minLength(password) && upperCase(password) && lowerCase(password) && contDigit(password) && stringCheck(password) &&
           allowedChars(password) && !user(username, password);

}


//generates random strong password
void generateDefaultPassword(char * default_password, const char * default_username)
{
    srand(time(NULL));


    while (!isStrongDefaultPassword(default_username, default_password)) {
        //numbers
        for (int i = 0; i < 14; i++) {
            int num = rand() % 122;
            while (!(isUpper(num) || isLower(num) || isDigit(num))) {

                num = rand() % 122;
            }

            default_password[i] = num;
        }
        printf("Here is your auto-generated password: %s\n", default_password);

    }


}



int main()
{
    char *password;
    char defualtPassword[15];
    char tempPassword[50];
    password = tempPassword;

    char * username;
    char tempuser[50];
    username = tempuser;
    int choice;


    while (!isStrongPassword(username, password)) {
        printf("please enter your username: \n");
        scanf("%s", username);
        printf("please enter your password: \n");
        scanf("%s", password);

        if (isStrongPassword(username, password)) {
            printf(" Your password is strong\n");

        }
        else {
            printf("Your password is weak try again\n");

        }


    }

    generateDefaultPassword(defualtPassword, username);


    return 0;
}
