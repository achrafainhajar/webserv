#include "../../includes/Response.hpp"
#include "../../includes/Request.hpp"
#include "../../includes/parsing.hpp"
#include <ftw.h>
#include <iostream>
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
    std::string str = response.str();
    str.copy(response_buf2, str.length());
    response_buf2[str.length()] = '\0';
    len = strlen(response_buf2);
}
void Response::respons_200(std::string index)
{
     std::stringstream response;
    std::string line;
    int i = 0;
    if(!html_file.is_open())
    {
        glen = 0;
                std::cout << index << std::endl;
        if(index[i] == '.')
        {
            while(index[i] == '.' || index[i] == '/')
                i++;
        }
        index = index.substr(i);

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
int Response::check_status()
{
    if(r_data.status_value == 301)
        respons_301();
    else if(r_data.status_value == 404)
        respons_404();
    else if(r_data.status_value == 400)
        respons_400();
    else if(r_data.status_value == 403)
        respons_403();
    else if(r_data.status_value == 405)
        respons_405();
    else if(r_data.status_value == 413)
        respons_413();
    else if(r_data.status_value == 500)
        respons_500();
    else if(r_data.status_value == 500)
        respons_500();
    else
        return 0;
    return 1;
}
void Response::respons(int client_sock,std::vector<Config> &parsing)
{
    (void)parsing;
    if(c != -4 && remaining.size() == 0)
    {
        len = 0;
        c = 1;
    }
    std::cout << r_data.getPath() << std::endl;
    if(check_status() == 1)
        c = -1;
    else if(r_data.getMethod() == "GET" && c != -4 && remaining.size() == 0)
        respons_200(fullpath);
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
void Response::handle_get(Config &config, Location location)
{
    (void) config;
    struct stat sb;

    std::string targetPath = location.getRoot() + r_data.getPath().substr(location.getLocationPath().size());

    if (stat(targetPath.c_str(), &sb) == 0) {
        if (S_ISDIR(sb.st_mode)) {
            if (r_data.getPath()[r_data.getPath().size() - 1] != '/') {
                r_data.status_value = 301;
                return;
            }
            else if (location.getAutoindex() == "on")
                fullpath = targetPath;  // For auto-indexing
            else {
                fullpath = targetPath + "/" + location.getIndex();
                if (access(fullpath.c_str(), F_OK) == -1)
                    r_data.status_value = 403;  // No index file and autoindex is off
                else
                    r_data.status_value = 200;
            }
        } else {
            fullpath = targetPath;
            r_data.status_value = (access(fullpath.c_str(), F_OK) != -1) ? 200 : 404;
        }
    } else {
        r_data.status_value = 404;
    }
}


void Response::check_request(std::vector<Config>& parsing)
{
    std::vector<Location> locations = parsing[0].getLocations();
    std::vector<Location>::iterator it;

    for (it = locations.begin(); it != locations.end(); ++it) {
        Location location = *it;
        if (r_data.getPath().find(location.getLocationPath()) != std::string::npos)
            break;
    }

    if(it == locations.end())
    {
        std::string root = parsing[0].getRoot();
        std::string targetPath = root + r_data.getPath();
        struct stat sb;

        if (stat(targetPath.c_str(), &sb) == 0) {
        if (S_ISDIR(sb.st_mode)) {
            std::string indexPath = targetPath +'/'+ parsing[0].getIndex();
            std::cout << indexPath << std::endl;
            if (access(indexPath.c_str(), F_OK) != -1) {
                r_data.status_value = 200;
                fullpath = indexPath;
                std::cout << targetPath << std::endl;
            } else {
                r_data.status_value = 404;
            }
        } else {
            if (access(targetPath.c_str(), F_OK) != -1) {
                r_data.status_value = 200;
                fullpath = targetPath;
                std::cout << fullpath << std::endl;
            } else {
                r_data.status_value = 404;
            }
        }
        } else {
            r_data.status_value = 404;
        }
    }
    if(r_data.status_value > 0)
        return;
    if(r_data.getMethod() == "GET")
    {
        handle_get(parsing[0],*it);
    }
    else if(r_data.getMethod() == "POST")
    {
        handle_post(parsing[0],*it);
    }
    else if(r_data.getMethod() == "DELETE")
    {
        handle_delete(parsing[0],*it);
    }
    std::cout << r_data.status_value << std::endl;
}

int delete_file(const char* fpath, const struct stat* sb, int typeflag, struct FTW* ftwbuf)
{
    (void) sb;
    (void) typeflag;
    (void) ftwbuf;
    if (remove(fpath) == 0) {
        std::cout << "Deleted file: " << fpath << std::endl;
        return 0;
    } else {
        std::cerr << "Failed to delete file: " << fpath << std::endl;
        return -1;
    }
}



int delete_directory_recursive(const std::string& directoryPath)
{
    int flags = FTW_DEPTH | FTW_PHYS;

    int result = nftw(directoryPath.c_str(), delete_file, 20, flags);
    if (result == -1) {
        return 500;
    }

    // Delete the directory itself
    if (rmdir(directoryPath.c_str()) == 0) {
        return 204;
    } else {
        return 500;
    }
}

void Response::handle_delete(Config &config,Location location)
{
    (void) config;
    (void) location;
    struct stat sb;
    std::string targetPath;

    if(fullpath.empty())
        targetPath = location.getRoot() + r_data.getPath().substr(location.getLocationPath().size());

    else
        targetPath = fullpath;
    std::cout << targetPath << std::endl;
    if (stat(targetPath.c_str(), &sb) == 0) {
        if (S_ISDIR(sb.st_mode)) {
            if (r_data.getPath()[r_data.getPath().size() - 1] != '/') {
                r_data.status_value = 409;
                return;
            }
            if(!location.getCgiPath().empty())
            {
                if(location.getIndex().empty())
                {
                    r_data.status_value = 409;
                    return;
                }
                // cgi code
            }
            else {
                r_data.status_value = delete_directory_recursive(targetPath.c_str());
            }
        } else {
            fullpath = targetPath;
             if(!location.getCgiPath().empty())
             {
                // cgi code
             }
             else
             {
                 if (remove(targetPath.c_str()) == 0)
                    r_data.status_value =  204;
                else
                    r_data.status_value =  403;     
             }
        }
    } else {
        r_data.status_value = 404;
    }
}
void Response::handle_post(Config &config,Location location)
{
    (void) config;
    (void) location;

    if(!location.getUpload().empty()) // la kan fih upload sf rah good  201
    {
        r_data.status_value = 201;
        return;
    }

    struct stat sb;

    std::string targetPath = location.getRoot() + r_data.getPath().substr(location.getLocationPath().size());

    if (stat(targetPath.c_str(), &sb) == 0) {
        if (S_ISDIR(sb.st_mode)) {
            if (r_data.getPath()[r_data.getPath().size() - 1] != '/') {
                r_data.status_value = 301;
                return;
            }
            else {
                fullpath = targetPath + "/" + location.getIndex();
                if (access(fullpath.c_str(), F_OK) == -1)
                    r_data.status_value = 403;  // No index file and autoindex is off
                else
                {
                    if(location.getCgiPath().empty())
                        r_data.status_value = 403;
                    else
                         r_data.status_value = 201; // Cgi location
                }
            }
        } else {
            fullpath = targetPath;
             if(location.getCgiPath().empty())
                r_data.status_value = 403;
            else
                 r_data.status_value = 201;
        }
    } else {
        r_data.status_value = 404;
    }
}
