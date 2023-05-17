# ifndef RESPONSE_HPP
#define  RESPONSE_HPP
#include"Request.hpp"
#include "parsing.hpp"
class Response
{
    public:
    int sockfd;
    std::fstream html_file;
    long glen;
    long length;
    char response_buf2[6000];
    std::string remaining;
    char *response_buf1;
    long len;
    Request r_data;
    int c;
    int count;
    Response(const Response& other)
        : sockfd(other.sockfd)
         
    {
    }

    // Copy assignment operator
    Response& operator=(const Response& other)
    {
        if (this != &other)
        {
            sockfd = other.sockfd;
            glen = other.glen;
            length = other.length;
            len = other.len;

            char* new_response_buf1 = new char[len];
            std::memcpy(new_response_buf1, other.response_buf1, len * sizeof(char));
            delete[] response_buf1;
            response_buf1 = new_response_buf1;

            std::memcpy(response_buf2, other.response_buf2, sizeof(response_buf2));

                       c = other.c;
            count = other.count;

        }
        return *this;
    }
    Response(){remaining = "";}
    bool check_path(std::vector<Config>& parsing);
    void handle_get(std::vector<Config>& parsing);
    void handle_post(std::vector<Config>& parsing);
    void handle_delete(std::vector<Config>& parsing);
    void check_request(std::vector<Config>& parsing);
    void respons(int client_sock,std::vector<Config>& parsing);
    void respons_200(std::string index);
    void check_location(std::vector<Config>& parsing);
    void respons_404(void);
    void respons_201(std::string index);
    void respons_204(void);
    void respons_301(void);
    void respons_400(void);
    void respons_403(void);
    void respons_405(void);
    void respons_413(void);
    void respons_500(void);
    void respons_504(void);
};  
size_t whitespaces(std::string str,size_t n);
size_t fill_data(std::string str,std::string dest,size_t n , std::string &data);
#endif