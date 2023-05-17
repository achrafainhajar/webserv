# ifndef REQUEST_HPP
#define REQUEST_HPP
#include "Utils.hpp"
#include <cstdlib>
class Request
{
    public:
        int                                 k;
        std::string                         request;
        std::string                         method;
        std::string                         path;
        std::string                         version;
        std::fstream                         body;
        std::map<std::string, std::string>  header;
        bool                                read;
        bool                                status;
        size_t                              content_length;
        size_t                              len;
        int                                 status_value;
    public :
        Request(){ status = false; k = 1; read = false; status_value = 0;}
        void  clear();
        void request_append(const char *str,int length,size_t size);
        void parse_header(size_t size);
        void fill_header(size_t size);
        std::map<std::string, std::string> getheader() const;
        std::string getMethod() const;
        std::string getPath() const;
        std::string getVersion() const;
        std::fstream &getBody();
        void pars_chunked_body(size_t size);
        bool getread();
        int  getk();
};
#endif