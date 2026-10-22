#include <bits/stdc++.h>
#include "headers.h"
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <cstdlib>
using json = nlohmann::json;

//global vars
int startMenuInput;
std::string citypicked;
std::string vacaycity;
// other
void clearterm(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
};
// menus ui
void usercity(){
    std::cout << "yeah" << std::endl;
};
void choosecity(){
    std::cout << "yo" << std::endl;
};
void citydata(){
    
};

void startmenu(){
    int choice; 
    auto menugraphic = [&choice](){
        std::cout << "--------------" << std::endl;
        std::cout << "---#sjryan" << std::endl;
        std::cout << "1. find out your vacay spot" << std::endl;
        std::cout << "2. choose your own city first" << std::endl;
        std::cout << "--------------" << std::endl;
        std::cin >> choice;
    };
    while(choice != 1 && choice != 2){
        menugraphic();
        switch(choice){
            case 1:
                clearterm();
                choosecity();
                break;
            case 2:
                clearterm();
                usercity();
                break;
            default:
                clearterm();
                menugraphic();
                break;    
        }
    }
};

int main(){
    startmenu();
}
