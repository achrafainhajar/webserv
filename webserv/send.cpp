#include "parsing.hpp"

void pars::respons_404()
{
    std::string response = "HTTP/1.1 404 Not Found\r\n"
                      "Content-Length: 0\r\n"
                      "Connection: close\r\n\r\n";
    r_data.response_buf = (char *)response.c_str();
}
void pars::respons_200(std::string index)
{
    std::ifstream html_file;
    std::ostringstream response;
    std::string response_body;
    std::string line;

    html_file.open(index.c_str());
    while (getline(html_file, line))
    {
        response_body += line + "\n";
    }
    response << "HTTP/1.1 200 OK\r\n";
    response << "Content-Type: text/html; charset=UTF-8\r\n";
    response << "Content-Length: " << response_body.length() << "\r\n";
    response << "\r\n";
    response << response_body;
    std::string response_str = response.str();
    char response_buf[response_str.size() + 1];
    std::copy(response_str.begin(), response_str.end(), response_buf);
    response_buf[response_str.size()] = '\0';
    r_data.response_buf = response_buf;

}
void pars::res_location(std::vector<loc>::iterator it)
{
    respons_200(it->index);
}
void pars::check_location()
{
    int count = 0;
    if(!r_data.url.empty())
    {
        std::vector<loc>::iterator it;
        for (it = s_data[0].location.begin(); it != s_data[0].location.end(); it++)
        {
            if(it->path == r_data.url)
            {
                count = 1;
                break;
            }
        }
        if(count == 0)
        {
            respons_404();
            return;
        }
        respons_200(r_data.url);
        return;
    }
     respons_200(s_data[0].index);
}
void pars::respons(int client_sock)
{
    check_location();
    send(client_sock, r_data.response_buf ,strlen(r_data.response_buf), 0);
}