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
//call writecallback
size_t writeCallBack(char* data, size_t size, size_t nmemb, std::string* response){
    response->append(data,size*nmemb);
    return size*nmemb;
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
void usercity(){
    std::string choice;
    auto menugraphic = [&choice](){
        std::cout << "-----------" << std::endl;
        std::cout << "---#input city name ex. SanJose " << std::endl;
        std::cout << "-------------" << std::endl;
        std::cin >> choice;
    }
    while(choice.empty() != 1 && choice.find(" ") !=std::string::npos){
        clearterm();
        menugraphic();
    }
};
void choosecity(){
    int choice;
    auto menugraphic = [&choice](){
        std::cout << "--------------" << std::endl;
        std::cout << "---#select a city" << std::endl;
        std::cout << "1. san jose" << std::endl;
        std::cout << "2. san francisco" << std::endl;
        std::cout << "2. sacramento" << std::endl;
        std::cout << "2. los angeles" << std::endl;
        std::cout << "5. san diego" << std::endl;
        std::cout << "--------------" << std::endl;
        std::cin >> choice;
    };
    while(choice!=1 && choice!=2 && choice!=3 && choice!=4 && choice!=5){
        clearterm();
        menugraphic();
    }
    switch(choice){
        case 1: //sj
            clearterm();
            citypicked = "SanJose";
            startmenu();
            break;
        case 2: //sf
            clearterm();
            citypicked = "SanFrancisco";
            startmenu();
            break;
        case 3: //sac
            clearterm();
            citypicked = "Sacramento";
            startmenu();
            break;
        case 4: //la
            clearterm();
            citypicked = "LosAngeles";
            startmenu();
            break;
        case 5: //sd
            clearterm();
            citypicked = "SanDiego";
            startmenu();
            break;
        default:
            clearterm();
            choosecity();
            break;
    }
};
void citydata(){
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL* curl = curl_easy_init();
    std::string usercitydata; // move globally after done
    std::string vacaycitydata; // move globally after done
    //grab datas
    auto grabvcdata = [&vacaycitydata,&curl](){
        if(curl){
            curl_easy_setopt(curl,CURLOPT_URL,cities.at(citypicked));
            curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, writeCallBack);
            curl_easy_setopt(curl,CURLOPT_WRITEDATA,&vacaycitydata);
            CURLcode result = curl_easy_perform(curl);
            if(result == CURLE_OK){
                std::cout<< "City data loaded: " << cities.at(citypicked) << "\n";
            }
            else{
                std::cerr << curl_easy_strerror(result) << "\n";
            }
            curl_easy_cleanup(curl);
        }
    };
    auto grabucdata = [&usercitydata,&curl](){
        // curl_easy_setopt(curl,CURLOPT_URLcities, ) cities.at(citypicked)? i need to figure out how i can get the users data based off location name
    };
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
                break;    
        }
    }
};

int main(){
    std::cout << "yea yea yea we up up up" << std::endl;
    startmenu();
}
