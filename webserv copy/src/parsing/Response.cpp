#include "../../includes/Response.hpp"
#include "../../includes/Request.hpp"
#include "../../includes/parsing.hpp"
#include <sys/stat.h>
std::string get_f_type(std::string str)
{
    std::string type = str.erase(0,str.find("."));
    if (!type.empty())
	{
		if (type == ".html") return "text/html";
		else if (type == ".htm") return "text/html";
		else if (type == ".shtml") return "text/html";
		else if (type == ".css") return "text/css";
		else if (type == ".xml") return "text/xml";
		else if (type == ".csv") return "text/csv";
		else if (type == ".gif") return "image/gif";
		else if (type == ".ico") return "image/x-icon";
		else if (type == ".jpeg") return "image/jpeg";
		else if (type == ".jpg") return "image/jpeg";
		else if (type == ".js") return "application/javascript";
		else if (type == ".json") return "application/json";
		else if (type == ".png") return "image/png";
		else if (type == ".pdf") return "application/pdf";
		else if (type == ".svg") return "image/svg+xml";
		else if (type == ".txt") return "text/plain";
		else if (type == ".atom") return "application/atom+xml";
		else if (type == ".rss") return "application/rss+xml";
		else if (type == ".webp") return "image/webp";
		else if (type == ".3gpp") return	"video/3gpp";
		else if (type == ".3gp") return "video/3gpp";
		else if (type == ".ts") return "video/mp2t";
		else if (type == ".mp4") return "video/mp4";
		else if (type == ".mpeg") return "video/mpeg";
		else if (type == ".mpg") return "video/mpeg";
		else if (type == ".mov") return "video/quicktime";
		else if (type == ".webm") return "video/webm";
		else if (type == ".flv") return "video/x-flv";
		else if (type == ".m4v") return "video/x-m4v";
		else if (type == ".mng") return "video/x-mng";
		else if (type == ".asx") return "video/x-ms-asf";
		else if (type == ".asf") return "video/x-ms-asf";
		else if (type == ".wmv") return "video/x-ms-wmv";
		else if (type == ".avi") return "video/x-msvideo";
		else if (type == ".mml") return "text/mathml";
		else if (type == ".txt") return "text/plain";
		else if (type == ".jad") return "text/vnd.sun.j2me.app-descriptor";
		else if (type == ".wml") return "text/vnd.wap.wml";
		else if (type == ".htc") return "text/x-component";
		else if (type == ".png") return "image/png";
		else if (type == ".tif") return "image/tiff";
		else if (type == ".tiff") return "image/tiff";
		else if (type == ".wbmp") return "image/vnd.wap.wbmp";
		else if (type == ".ico") return "image/x-icon";
		else if (type == ".jng") return "image/x-jng";
		else if (type == ".bmp") return "image/x-ms-bmp";
		else if (type == ".svg") return "image/svg+xml";
		else if (type == ".svgz") return "image/svg+xml";
		else if (type == ".mid") return "audio/midi";
		else if (type == ".midi") return "audio/midi";
		else if (type == ".kar") return "audio/midi";
		else if (type == ".mp3") return "audio/mpeg";
		else if (type == ".ogg") return "audio/ogg";
		else if (type == ".m4a") return "audio/x-m4a";
		else if (type == ".ra"	) return "audio/x-realaudio";
		else if (type == ".pl"	) return "application/x-perl";
		else if (type == ".py"	) return "application/x-python";
		else if (type == ".php"	) return "application/x-php";
		else if (type == ".cpp"	) return "application/x-c++";
		else if (type == ".c"	) return "application/x-c";
        else if (type == "*/*"    ) return "*/*";
	}
    return "application/octet-stream";

}


void Response::check_location(std::vector<Config> &parsing)
{
    int c = 0;
    if(r_data.getPath() != "")
    {
        std::cout <<"adadada"<< std::endl;
         std::vector<Location>::iterator it;
        for (it = parsing[0].getLocations().begin(); it != parsing[0].getLocations().end(); it++)
        {
            if(it->getLocationPath() == r_data.getPath() || r_data.getPath() == it->getRedirect())
            {
                c = 1;
                break;
            }
        }
        if(c == 0)
        {
            respons_404();
            return;
        }
        respons_200(it->getIndex());
        return;
    }
    respons_200(parsing[0].getIndex());
}
void Response::respons_201(std::string index)
{       index = "";
        std::ostringstream response;
        response << "HTTP/1.1 201 OK\r\n";
        response << "Content-Type: text/html\r\n";
        response << "Content-Length: 9\r\n";
        response << "\r\n";
        response << "hahah";
        std::string str = response.str();
        str.copy(response_buf2,str.length());
        response_buf2[str.length()] = '\0';
        std::cout <<"++++"<<response_buf2 <<"----" <<std::endl;
        len = strlen(response_buf2);
        c = -3;
}
void Response::respons_204()
{
    std::ostringstream response;

    response << "HTTP/1.1 204 OK\r\n";
    response << "Content-Type: text/html; charset=UTF-8\r\n";
    response << "Content-Length: " << 7 << "\r\n";
    response << "\r\n";
    response << "DELETED";
    std::string response_str = response.str();
    char* response_buf = new char[response_str.size() + 1];
    std::copy(response_str.begin(), response_str.end(), response_buf);
    response_buf[response_str.size()] = '\0';
    response_buf1 = response_buf;

}
void Response::respons_301()
{
    std::ostringstream response;

    response << "HTTP/1.1 301 Moved Permanently\r\n";
    response << "Location:  \r\n";
    response << "Content-Type: text/html; charset=UTF-8\r\n";
    response << "Content-Length: 0\r\n";
    response << "Connection: close\r\n";
    response << "\r\n";
    std::string response_str = response.str();
    char* response_buf = new char[response_str.size() + 1];
    std::copy(response_str.begin(), response_str.end(), response_buf);
    response_buf[response_str.size()] = '\0';
    response_buf1 = response_buf;
}
void Response::respons_200(std::string index)
{
     std::stringstream response;
    std::string line;
    if(!html_file.is_open())
    {
        glen = 0;
        html_file.open(index.c_str(), std::ios::in | std::ios::binary);
        html_file.seekg (0, html_file.end);
        length = html_file.tellg();
        html_file.seekg (0, html_file.beg);
        response << "HTTP/1.1 200 OK\r\n";
        response << "Content-Type: "<< get_f_type(index) <<"\r\n";
        response << "Content-Length: " << length << "\r\n";
        response << "\r\n";
        std::string str = response.str();
        str.copy(response_buf2,str.length());
        response_buf2[str.length()] = '\0';
        std::cout <<"++++"<<response_buf2 <<"----" <<std::endl;
        len = strlen(response_buf2);
    }
    else
    {
        html_file.read(response_buf2, 6000);
        len = html_file.gcount();
        std::cout << len<< "---" << glen <<"----"<<length << std::endl;
    }
}
void Response::respons(int client_sock,std::vector<Config> &parsing)
{
    if(c != -4 && remaining.size() == 0)
    {
        len = 0;
        c = 1;
    }
    std::cout << r_data.getPath() << std::endl;
    if(r_data.getMethod() == "GET" && c != -4 && remaining.size() == 0)
        check_location(parsing);
    else if(r_data.getMethod() == "POST")
    {
        respons_201("src/parsing/index1.html");
    }
    int i;
    if(len > 0 || c == -3)
    {
       char buff[6000];
       if(remaining.size() > 0)
       {
            memcpy(buff,remaining.c_str(), len);
            remaining = "";
       }
       else
       {
            memcpy(buff,response_buf2, len);
       }
       i = send(client_sock, buff ,len, 0);
       if(i == -1)
       {
            c = -4;
       }
       else
       {
           if(i < len)
           {
               std::cout << "t" <<std::endl;
               remaining = std::string(buff + i, len -i);
               len = len - i;
               std::cout << i << "----"<< len << "-----"<< glen<< std::endl;
           }
           glen = i + glen;
           c = 1;
       }
    }
    if(length <= glen)
    {
        c = -1;
        html_file.close();
    }
}
void Response::check_request(std::vector<Config>& parsing)
{
    // else
    // {
    //     std::vector<std::string>::iterator ite;
    //     for(ite = parsing[0].getAllowMethods().begin(); ite != parsing[0].getAllowMethods().end(); ite++)
    //     {
    //         if(*ite == r_data.getMethod())
    //            break;
    //     }
    // }
    if(r_data.getMethod() == "GET")
    {
        handle_get(parsing);
    }
    else if(r_data.getMethod() == "POST")
    {
        handle_post(parsing);
    }
    else if(r_data.getMethod() == "DELETE")
    {
        handle_delete(parsing);
    }
}
bool Response::check_path(std::vector<Config>& parsing)
{
    // int c = 0;
    // std::string root;
    // std::string loc = "";
    // if(r_data.getPath() != "")
    // {   
    //     std::vector<Location>::iterator it;
    //     for (it = parsing[0].getLocations().begin(); it != parsing[0].getLocations().end(); it++)
    //     {
    //         if(r_data.getPath().find(it->getLocationPath()) == 0)
    //         {
    //             loc = it->getLocationPath();
    //             c = 1;
    //             break;
    //         }
    //     }
    //     if(c == 0)
    //     {
    //         r_data.status_value = 404;
    //         return false;
    //     }
    //     root = it->getRoot();
    // }
    // else
    // {
    //     root = parsing[0].getRoot();
    // }
    // if (!root.empty() && root.back() == '/')
    //     root.pop_back();
    // root.append(r_data.path.substr(loc.size()));
    // struct stat buf;
    // std::cout << root << std::endl;
    // if (stat(root.c_str(), &buf) != 0) {
    //     r_data.status_value = 404;
    //     return false;
    // }
    // if (S_ISREG(buf.st_mode))
    // {

    // }
    // else if (S_ISDIR(buf.st_mode))
    // {
       
    // }
    (void) parsing;
    return true;
}
void Response::handle_get(std::vector<Config>& parsing)
{
    check_path(parsing);
}
void Response::handle_post(std::vector<Config>& parsing)
{
    (void) parsing;
}
void Response::handle_delete(std::vector<Config>& parsing)
{
    (void) parsing;
}