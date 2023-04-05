#include "parsing.hpp"

void pars::fill_request(std::string data)
{
    
    std::stringstream s(data);
    int count = 1;
    for(int i = 0;data[i];i++)
    {
        if(data[i] == ' ')
            count++;
    }
    if(count == 3)
    {
        s >> r_data.method;
        s >> r_data.url;
    }
    else
        s >> r_data.method;
    std::stringstream a(s_data[0].allow_methods);
    std::string word;
    count = 0;
    while (a >> word) {
       if(word == r_data.method)
            count = 1;
    }

    if(count == 0)
        exit(1);
}