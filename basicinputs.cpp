#include <bits/stdc++.h>
#include <string>
#include <curl/curl.h>
#include <nlohhman/json.hpp>
#include <cstdlib>
using json = nlohmann::json;

//global vars
int startMenuInput;
string "usercity";

int main(){
    
}

// other
void clearterm(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
};
// menus ui
void startmenu(){
    std::cout << "--------------" << endl;
    std::cout << "---#sjryan" << endl;
    std::cout << "1. find out your vacay spot" << endl;
    std::cout << "2. choose your own city first" << endl;
    std::cout << "--------------" << endl;

};
void usercity();
void choosecity();
void citydata();

