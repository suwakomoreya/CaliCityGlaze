#include <bits/stdc++.h>
#include "headers.h"
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <cstdlib>
using json = nlohmann::json;

//global vars
int startMenuInput;
//userdata
std::string citypicked;
std::string usercorddata;
std::string vacaycity;
std::string statepicked;
//data
std::string usercitydata;
std::string vacaycitydata;
//apikey
std::string geocodekey = "&api_key=6adab10ae89cc706096065wae95ed98";

//call writecallback
size_t writeCallBack(char* data, size_t size, size_t nmemb, std::string* response){
    response->append(data,size*nmemb);
    return size*nmemb;
}
//start


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
    int choice=0;
    auto menugraphic = [&choice](){
        std::cout <<
        R"(======================================
                        SJ #1              
        --------------------------------------
        1. Compare CA cities with your City
        2. Select your city                
        3. Select your state
        ======================================)"
        << std::endl;
        std::cin >> choice;
    };
    while(choice != 1 && choice !=2 && choice !=3){
        menugraphic();
        switch(choice){
            case 1: //vc select
                if((citypicked.empty()) || (statepicked.empty())){
                    clearterm();
                    std::cout << "Please select a city and state first" << std::endl;
                    menugraphic();
                    break;
                }
                else if(citypicked.empty() && (statepicked.empty()!=1)){
                    clearterm();
                    std::cout << "Please select a city" << std::endl;
                    menugraphic();
                    break;
                }
                else if((citypicked.empty() !=1)&& (statepicked.empty())){
                    clearterm();
                    std::cout << "Please select a state" << std::endl;
                    menugraphic();
                    break;
                }
                else{
                    clearterm();
                    choosecity();
                    break;
                }
            case 2: //ucselect
                clearterm();
                usercity();
                break;
            case 3://stateselect
                clearterm();
                selectprovince();
                break;
            default: //require valid input
                clearterm();
                break;
        }
    }
}
void selectprovince(){ //states will have %2C%20 before it (, )
    //only gonna do us states for now
    std::string choice;
    auto menugraphic = [&choice](){
        std::cout << "---------"<< std::endl;
        std::cout << "---#input a u.s state ex. California" << std::endl;
        std::cout << "---------------" << std::endl;
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::getline(std::cin >> std::ws, choice);
     };
    while((choice.empty()) || (choice.find(" ") != std::string::npos)){
        clearterm();
        menugraphic();
    }
    statepicked = choice;
}
void usercity(){
    std::string choice;
    auto menugraphic = [&choice](){
        std::cout << "-----------" << std::endl;
        std::cout << "---#input city name ex. San Jose " << std::endl;
        std::cout << "-------------" << std::endl;
        std::getline(std::cin >> std::ws, choice);
    };
    while(choice.empty()){ //&& choice.find(" ") !=std::string::npos
        clearterm();
        menugraphic();
    };
    if(choice.find(" ") != std::string::npos){
        size_t index = 0;
        while((index=choice.find(' ', index))!= std::string::npos){
            choice.replace(index,1,"%20");
            index+=3;    
        }
    }
    citypicked = choice;
};
void comparecity(){
    int choice=0;
    auto menugraphic[&choice](){
        std::cout << "---------------------" << std::endl;
        std::cout << "##Comparing Cities##" << std::endl;
        std::cout << "User City: " + citypicked << std::endl;
        std::cout << "Cali City: " + vacaycity << std::endl;
        std::cout << "1. Temperature data" << std::endl;
        std::cout << "2. Preciptation data" << std::endl;
        std::cout << "3. Wind data" << std::endl;
        std::cout << "4. Return to  CAcity select" << std::endl;
        std::cin >> choice;
    }
    while(choice != 1 && choice !=2 && choice !=3){
        menugraphic();
        switch(choice){
            case 1:
                clearterm();
                break;
            case 2:
                clearterm();
                break;
            case 3:
                clearterm();
                break;
            case 4:
                clearterm();
                choosecity();
                break;
            default:
                clearterm();
                break;
        }
    }
}
void choosecity(){
    int choice =0;
    auto menugraphic = [&choice](){
        std::cout << "--------------" << std::endl;
        std::cout << "---#select a city" << std::endl;
        std::cout << "1. san jose" << std::endl;
        std::cout << "2. san francisco" << std::endl;
        std::cout << "3. sacramento" << std::endl;
        std::cout << "4. los angeles" << std::endl;
        std::cout << "5. san diego" << std::endl;
        std::cout << "--------------" << std::endl;
        std::cin >> choice;
    };
    //wrong input results in this
    while(choice!=1 && choice!=2 && choice!=3 && choice!=4 && choice!=5){
        clearterm();
        menugraphic();
    }

    switch(choice){
        case 1: //sj
            clearterm();
            citypicked = "SanJose";
            comparecity();
            break;
        case 2: //sf
            clearterm();
            citypicked = "SanFrancisco";
            comparecity();
            break;
        case 3: //sac
            clearterm();
            citypicked = "Sacramento";
            comparecity();
            break;
        case 4: //la
            clearterm();
            citypicked = "LosAngeles";
            comparecity();
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
    //grab datas
    auto grabvcdata = [&curl](){ //grabs vacation city data
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
        }
    };

    auto grabucCORDdata = [&curl](){ //COORDINATE DATA not actaul city data. use this to get user city data
        curl_easy_setopt(curl,CURLOPT_URL,("https://geocode.maps.co/search?q=" + citypicked + "%2C%20" + statepicked + geocodekey).c_str()); // cities.at(citypicked)? //i need to figure out how i can get the users data based off location name
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, writeCallBack);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,&usercorddata);
        CURLcode result = curl_easy_perform(curl);
        if(result == CURLE_OK){
            std::cout<< "User city data coordinates loaded: " << citypicked << "\n";
        }
        else{
            std::cerr << curl_easy_strerror(result) << "\n";
        }
    };

    auto grabucdata = [&curl](){
        // parse data
        json data = json::parse(usercorddata);
        
        //latlong
        std::string latitudedata = data[0]["lat"].get<std::string>();
        std::string longitudedata = data[0]["lon"].get<std::string>();

        curl_easy_setopt(curl,CURLOPT_URL,("https://api.open-meteo.com/v1/forecast?latitude="+latitudedata+"&longitude="+longitudedata+"&daily=temperature_2m_max,temperature_2m_mean,temperature_2m_min,wind_speed_10m_max,sunrise,sunset,uv_index_clear_sky_max,precipitation_probability_max&timezone=America%2FLos_Angeles&temperature_unit=fahrenheit").c_str());
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, writeCallBack);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,&usercitydata);
        CURLcode result = curl_easy_perform(curl);
        if(result == CURLE_OK){
            std::cout << "User city data loaded: " << citypicked << "\n";
        }
        else{
            std::cerr << curl_easy_strerror(result) << "\n";
        }
        
    };
    if(curl){
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
};

//WEATHER DATA (make sure to combine all this into one function, either this ship or next ship.)
void tempdata(){
    json ucdata = json::parse(usercitydata);
    json vcdata = json::parse(vacaycitydata);

    // tempdailyminmax
    int ucdailymin = ucdata[0]["temperature_2m_min"].get<int>();
    int ucdailymean = ucdata[0]["temperature_2m_mean"].get<int>();
    int ucdailymax = ucdata[0]["temperature_2m_max"].get<int>();

    int vcdailymin = vcdata[0]["temperature_2m_min"].get<int>();
    int vcdailymean = ucdata[0]["temperature_2m_mean"].get<int();
    int vcdailymax = vcdata[0]["temperature_2m_max"].get<int>();
//output (should turn into menugraphic)
    std::cout << "-----------" << std::endl;
    std::cout << citypicked + "'s minimum temperature today (F): " << ucdailymin << std::endl;
    std::cout << citypicked + "'s maximum temperature today (F)" << ucdailymax << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << vacaycity + "'s minimum temperature today (F)" << vcdailymin << std::endl;
    std::cout << vacaycity + "'s maximum temperature today (F)" << vcdailymax << std::endl;
    std::cout << "-------------------" << std::endl;
    if()
}
void precipdata(){

}
void winddata(){

}