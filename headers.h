#include <bits/stdc++.h>
#include <string>
#include <map>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <cstdlib>
using json = nlohmann::json;
std::map<std::string,std::string> cities = {
    {"SanJose","https://api.open-meteo.com/v1/forecast?latitude=37.3394&longitude=-121.895&daily=temperature_2m_max,temperature_2m_min,wind_speed_10m_max,sunrise,sunset,uv_index_clear_sky_max,precipitation_probability_max&timezone=America%2FLos_Angeles&temperature_unit=fahrenheit"}
    ,{"SanFrancisco","https://api.open-meteo.com/v1/forecast?latitude=37.7749&longitude=-122.4194&daily=temperature_2m_max,temperature_2m_min,wind_speed_10m_max,sunrise,sunset,uv_index_clear_sky_max,precipitation_probability_max&timezone=America%2FLos_Angeles&temperature_unit=fahrenheit"}
    ,{"Sacramento","https://api.open-meteo.com/v1/forecast?latitude=38.5816&longitude=-121.4944&daily=temperature_2m_max,temperature_2m_min,wind_speed_10m_max,sunrise,sunset,uv_index_clear_sky_max,precipitation_probability_max&timezone=America%2FLos_Angeles&temperature_unit=fahrenheit"}
    ,{"LosAngeles","https://api.open-meteo.com/v1/forecast?latitude=34.0522&longitude=-118.2437&daily=temperature_2m_max,temperature_2m_min,wind_speed_10m_max,sunrise,sunset,uv_index_clear_sky_max,precipitation_probability_max&timezone=America%2FLos_Angeles&temperature_unit=fahrenheit"}
    ,{"SanDiego","https://api.open-meteo.com/v1/forecast?latitude=32.7157&longitude=-117.1647&daily=temperature_2m_max,temperature_2m_min,wind_speed_10m_max,sunrise,sunset,uv_index_clear_sky_max,precipitation_probability_max&timezone=America%2FLos_Angeles&temperature_unit=fahrenheit"}
};

void clearterm();
void usercity();
void choosecity();
void citydata();
void startmenu();
void selectprovince();