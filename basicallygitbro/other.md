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