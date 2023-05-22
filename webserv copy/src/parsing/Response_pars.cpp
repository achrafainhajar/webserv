#include "../../includes/Response.hpp"
#include "../../includes/Request.hpp"
#include "../../includes/parsing.hpp"
#include <ftw.h>
#include <iostream>
#include <sys/stat.h>

void Response::handle_get(Config &config, Location location)
{
    (void) config;
    struct stat sb;

    std::string targetPath = location.getRoot() + r_data.getPath().substr(location.getLocationPath().size());

    if (stat(targetPath.c_str(), &sb) == 0) {
        if (S_ISDIR(sb.st_mode)) {
            if (r_data.getPath()[r_data.getPath().size() - 1] != '/') {
                r_data.status_value = 301;
                fullpath = r_data.getPath() + '/';
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
                fullpath = r_data.getPath() + '/';
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
