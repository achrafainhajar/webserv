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
}