# Californian City Comparison
https://open-meteo.com/en/docs
https://geocode.maps.co/docs/endpoints/

A terminal app that compares the users city weather data with five big californian cities.
![Alt text](images/showcase.gif)
* Unit switching (temperature, precipitation measurement, wind speed)
* Current windspeed, max windspeed
* Days forecast based on average heat

The terminal app is small and uses Geocode api to translate the users city into a coordinate that the Openmateo API uses to find the weather of the chosen locations

Required libraries to build:
https://github.com/nlohmann/json
[Libcurl](https://curl.se/download.html)
msys2 ucrt64 gcc c++ compiler

1. install dependencies `pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-curl mingw-w64-ucrt-x86_64-nlohmann-json`
2. navigate to directory `cd path/to/CaliCityGlaze`
3. compile `g++ main.cpp -o CaliCityGlaze.exe -lcurl`
4. run application `./CaliCityGlaze.exe`

