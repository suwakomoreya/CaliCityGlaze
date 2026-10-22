#include <bits/stdc++.h>
#include <string>
#include <curl/curl.h>

size_t writeCallback(char* data, size_t size, size_t nmemb, std::string* response){
    response->append(data,size*nmemb);
    return size * nmemb;
}
int main(){
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL* curl = curl_easy_init();
    std::string response;
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.open-meteo.com/v1/forecast?latitude=38.4088&longitude=-121.3716&hourly=temperature_2m&temperature_unit=fahrenheit");
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        CURLcode result = curl_easy_perform(curl);
        if(result == CURLE_OK){
            std::cout << response << "\n";

        }
        else{
            std::cerr << curl_easy_strerror(result) << '\n';
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}