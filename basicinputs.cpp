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
    while(true){
        menugraphic();
        switch(choice){
            case 1: //vc select
                if((citypicked.empty()) || (statepicked.empty())){
                    clearterm();
                    if(citypicked.empty() && statepicked.empty()){
                        std::cout << "Please select a city and state first.\n";
                    }
                    else if(citypicked.empty()){
                        std::cout << "Please select a city first.\n";
                    }
                    else if(statepicked.empty()){
                        std::cout << "Please select a state first.\n";
                    }
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
    std::cout << "state selected" <<std::endl;
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
    std::cout << "city selecterd" << std::endl;
};
void comparecity(){
    int choice=0;
    auto menugraphic = [&choice](){
        std::cout << "---------------------" << std::endl;
        std::cout << "##Comparing Cities##" << std::endl;
        std::cout << "User City: " + citypicked << std::endl;
        std::cout << "Cali City: " + vacaycity << std::endl;
        std::cout << "1. Temperature data" << std::endl;
        std::cout << "2. Preciptation data" << std::endl;
        std::cout << "3. Wind data" << std::endl;
        std::cout << "4. Return to  CAcity select" << std::endl;
        std::cin >> choice;
    };
    while(choice != 1 && choice !=2 && choice !=3 && choice!=4){
        menugraphic();
        switch(choice){
            case 1:
                clearterm();
                tempdata();
                break;
            case 2:
                clearterm();
                precipdata();
                break;
            case 3:
                clearterm();
                winddata();
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
            vacaycity = "SanJose";
            citydata();
            comparecity();
            break;
        case 2: //sf
            clearterm();
            vacaycity = "SanFrancisco";
            citydata();
            comparecity();
            break;
        case 3: //sac
            clearterm();
            vacaycity = "Sacramento";
            citydata();
            comparecity();
            break;
        case 4: //la
            clearterm();
            vacaycity = "LosAngeles";
            citydata();
            comparecity();
            break;
        case 5: //sd
            clearterm();
            vacaycity = "SanDiego";
            citydata();
            comparecity();
            break;
        default:
            clearterm();
            choosecity();
            break;
    }
};
void citydata(){
    std::cout << "citydata entering" << std::endl;
    usercorddata.clear();
    usercitydata.clear();
    vacaycitydata.clear();
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL* curl = curl_easy_init();
    if(!curl){
        std::cerr << "Could not initialize CURL." << std::endl;
        curl_global_cleanup();
        return;
    }
    //grab datas
    auto grabvcdata = [&curl](){ //grabs vacation city data
        if(curl){
            curl_easy_setopt(curl,CURLOPT_URL,cities.at(vacaycity));
            curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, writeCallBack);
            curl_easy_setopt(curl,CURLOPT_WRITEDATA,&vacaycitydata);
            CURLcode result = curl_easy_perform(curl);
            if(result == CURLE_OK){
                std::cout<< "City data loaded: " << cities.at(vacaycity) << "\n";
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
        json data = json::parse(usercorddata, nullptr, false);
        if(data.is_discarded() || !data.is_array() || data.empty() || !data[0].contains("lat") || !data[0].contains("lon")){
            std::cerr << "Couldn't find coord data" << std::endl;
            return;
        }
        
        //latlong
        std::string latitudedata = data[0]["lat"].get<std::string>();
        std::string longitudedata = data[0]["lon"].get<std::string>();

        curl_easy_setopt(curl,CURLOPT_URL,("https://api.open-meteo.com/v1/forecast?latitude="+latitudedata+"&longitude="+longitudedata+"&daily=temperature_2m_max,temperature_2m_mean,temperature_2m_min,wind_speed_10m_max,sunrise,sunset,uv_index_clear_sky_max,precipitation_probability_max,precipitation_sum&hourly=wind_speed_10m&timezone=America%2FLos_Angeles&temperature_unit=fahrenheit&wind_speed_unit=mph&precipitation_unit=inch").c_str());
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
    grabvcdata();
    grabucCORDdata();
    grabucdata();
    if(curl){
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
};

//WEATHER DATA (make sure to combine all this into one function, either this ship or next ship.)
void tempdata(){
    json ucdata = json::parse(usercitydata);
    json vcdata = json::parse(vacaycitydata);
    int choice = 0;
    double ucdailymin = ucdata["daily"]["temperature_2m_min"][0].get<double>();
    double ucdailymean = ucdata["daily"]["temperature_2m_mean"][0].get<double>();
    double ucdailymax = ucdata["daily"]["temperature_2m_max"][0].get<double>();
    
    double vcdailymin =vcdata["daily"]["temperature_2m_min"][0].get<double>();
    double vcdailymean =vcdata["daily"]["temperature_2m_mean"][0].get<double>();
    double vcdailymax =vcdata["daily"]["temperature_2m_max"][0].get<double>();

    auto menugraphic = [&choice,&ucdailymin,&ucdailymean,&ucdailymax,&vcdailymin,&vcdailymean,&vcdailymax](){
        //output 
        std::cout << "-----------------" << std::endl;
        std::cout << citypicked + "'s minimum temperature today (F): " << ucdailymin << std::endl;
        std::cout << citypicked + "'s maximum temperature today (F): " << ucdailymax << std::endl;
        std::cout << "------------------------" << std::endl;
        std::cout << vacaycity + "'s minimum temperature today (F)" << vcdailymin << std::endl;
        std::cout << vacaycity + "'s maximum temperature today (F)" << vcdailymax << std::endl;
        std::cout << "---------------------------------" << std::endl;
        if(ucdailymean <= 70.0){
            std::cout << "Stay at home if you prefer the colder days." << std::endl;
        }
        else if(ucdailymean >70.0 && ucdailymean <85.0 ){
            std::cout << "Stay at home if you prefer the more warmer and chill days." <<std::endl;
        }
        else if(ucdailymean>85.0){
            std::cout << "Stay at home if you prefer hotter days." <<std::endl;
        }
        
        if(vcdailymean <= 70.0){
            std::cout << "Head out to " + vacaycity << "if you want a nice cool day." <<std::endl;
        }
        else if(vcdailymean >70.0 && vcdailymean <85.0){
            std::cout << "Head out to " + vacaycity << " if you want a nice warm day." << std::endl;
        }
        else if(vcdailymax >85.0){
            std::cout << "Head out to " + vacaycity << " if you want a nice warm day." << std::endl;
        }
        std::cout << "1. Return to city comparison" <<std::endl;
        std::cout << "2. Return to menu screen" << std::endl;
        std::cin >> choice;
    };
    while(choice !=1 && choice !=2){
        clearterm();
        menugraphic();
    }
    switch(choice){
        case 1:
            clearterm();
            comparecity();
            break;
        case 2:
            clearterm();
            startmenu();
            break;
        default:
            clearterm();
            menugraphic();
            break;
    }
}
void precipdata(){
    int choice =0;
    json ucdata = json::parse(usercitydata);
    json vcdata = json::parse(vacaycitydata);
    double ucmaxchance = ucdata["daily"]["precipitation_probability_max"][0].get<double>();
    double ucprecipsum = ucdata["daily"]["precipitation_sum"][0].get<double>(); //need to add this to the links later

    double vcmaxchance = vcdata["daily"]["precipitation_probability_max"][0].get<double>();
    double vcprecipsum = vcdata["daily"]["precipitation_sum"][0].get<double>();
    auto menugraphic = [&choice, &ucmaxchance, &ucprecipsum, &vcmaxchance,&vcprecipsum](){
        std::cout << "------------------------" << std::endl;
        std::cout << "Chance of preciptation today at your city (" << citypicked << "): " << ucmaxchance << std::endl;
        std::cout << "Inches of rain today: " << ucprecipsum << std::endl;
        std::cout << "------------------" << std::endl;
        std::cout << "Chance of preciptation today at " << vacaycity << ": " << vcmaxchance << std::endl;
        std::cout << "Inches of rain today at " << vacaycity << ": " << vcprecipsum << std::endl;
        std::cout << "--------------------" << std::endl;
        std::cout << "1. Return to city comparison" << std::endl;
        std::cout << "2. Return to start menu" << std::endl;
        std::cin >> choice;
    };
    while(choice != 1 && choice!=2){
        clearterm();
        menugraphic();
    }
    switch(choice){
        case 1:
            clearterm();
            comparecity();
            break;
        case 2:
            clearterm();
            startmenu();
            break;
        default:
            clearterm();
            menugraphic();
            break;
    }
}
void winddata(){ // all 10m above ground
    int choice =0;
    json ucdata = json::parse(usercitydata); 
    json vcdata = json::parse(vacaycitydata);

    double ucwspeedhour = ucdata["hourly"]["wind_speed_10m"][0].get<double>(); // hourly and need to add to urls
    double ucwspeedmax = ucdata["daily"]["wind_speed_10m_max"][0].get<double>();

    double vcwspeedhour = ucdata["hourly"]["wind_speed_10m"][0].get<double>();
    double vcwspeedmax = ucdata["daily"]["wind_speed_10m_max"][0].get<double>();
    auto menugraphic = [&choice,&ucwspeedhour,&ucwspeedmax,&vcwspeedhour,&vcwspeedmax](){
        std::cout << "-----------------" << std::endl;
        std::cout << "Current wind speed 10 meters off the ground in your city: " << ucwspeedhour << std::endl;
        std::cout << "Fastest wind speed today 10 meters off the ground: " << ucwspeedmax << std::endl;
        std::cout << "-------------------" << std::endl;
        std::cout << "Current wind speed in " + vacaycity + ": " << vcwspeedhour << std::endl;
        std::cout << "Fastest wind speed today in " + vacaycity + ": " << vcwspeedmax << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "1. Return to city comparison" << std::endl;
        std::cout << "2. Return to start menu" << std::endl;
        std::cin >> choice;
    };
    while(choice !=1 && choice !=2){
        clearterm();
        menugraphic();
    }
    switch(choice){
        case 1:
            clearterm();
            comparecity();
            break;
        case 2:
            clearterm();
            startmenu();
            break;
        default:
        clearterm();
        menugraphic();
        break;
    }
}
// wow i didnt even know i didnt have a int main... swore i had one
int main(){
    std::cout << "startapp" << std::endl;
    startmenu();
    std::cout << "startmen died" << std::endl;
    std::cin.get();
    return 0;
}