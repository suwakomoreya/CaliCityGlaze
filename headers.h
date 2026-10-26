#include <bits/stdc++.h>
#include <string>
#include <map>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <cstdlib>
using json = nlohmann::json;
//measuring data for units
extern std::string measurelink;
extern std::string speedlink;
extern std::string templink;

std::map<std::string,std::string> cities = {
    {"SanJose","https://api.open-meteo.com/v1/forecast?latitude=37.3394&longitude=-121.895&daily=temperature_2m_max,temperature_2m_mean,temperature_2m_min,wind_speed_10m_max,sunrise,sunset,uv_index_clear_sky_max,precipitation_probability_max,precipitation_sum&hourly=wind_speed_10m&timezone=America%2FLos_Angeles"+templink+speedlink+measurelink}
    ,{"SanFrancisco","https://api.open-meteo.com/v1/forecast?latitude=37.7749&longitude=-122.4194&daily=temperature_2m_max,temperature_2m_mean,temperature_2m_min,wind_speed_10m_max,sunrise,sunset,uv_index_clear_sky_max,precipitation_probability_max,precipitation_sum&hourly=wind_speed_10m&timezone=America%2FLos_Angeles"+templink+speedlink+measurelink}
    ,{"Sacramento","https://api.open-meteo.com/v1/forecast?latitude=38.5816&longitude=-121.4944&daily=temperature_2m_max,temperature_2m_mean,temperature_2m_min,wind_speed_10m_max,sunrise,sunset,uv_index_clear_sky_max,precipitation_probability_max,precipitation_sum&hourly=wind_speed_10m&timezone=America%2FLos_Angeles"+templink+speedlink+ measurelink}
    ,{"LosAngeles","https://api.open-meteo.com/v1/forecast?latitude=34.0522&longitude=-118.2437&daily=temperature_2m_max,temperature_2m_mean,temperature_2m_min,wind_speed_10m_max,sunrise,sunset,uv_index_clear_sky_max,precipitation_probability_max,precipitation_sum&hourly=wind_speed_10m&timezone=America%2FLos_Angeles"+templink+speedlink+ measurelink}
    ,{"SanDiego", "https://api.open-meteo.com/v1/forecast?latitude=32.7157&longitude=-117.1647&daily=temperature_2m_max,temperature_2m_mean,temperature_2m_min,wind_speed_10m_max,sunrise,sunset,uv_index_clear_sky_max,precipitation_probability_max,precipitation_sum&hourly=wind_speed_10m&timezone=America%2FLos_Angeles"+templink+speedlink + measurelink}
};
// data takes: temperature daily max, temperature daily min, wind speed max, sunset time, uv index_clearskymax, precip probability max, timezone pdt temp fahrenheit
void clearterm();
void startmenu();
void usercity();
void choosecity();
void citydata();
void selectprovince();
void comparecity();
void unitscr();
void tempdata();
void precipdata();
void winddata();

