#include <iostream>
#include"parsing.hpp"
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
void check_arguments(int argc,char **argv)
{
    if(argc > 2)
    {
        std::cerr<<"Too many arguments" << std::endl;
        exit(1);
    }
    (void)argv;
}
int main(int argc,char **argv)
{
    check_arguments(argc,argv);
    pars parsing(argv[1]);
    std::ifstream html_file;
    html_file.open("index.html");
    std::string response_body;
     std::string line;
    while (getline(html_file, line)) {
        response_body += line + "\n";
    }
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8888);
    bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    listen(sock, 1);
    while(true)
    {

        int client_sock = accept(sock, NULL, NULL);

        char buf[4096];
        ssize_t nread = recv(client_sock, buf, sizeof(buf), 0);
        if (nread < 0) {
            std::cerr << "Error reading from client" << std::endl;
        } else {
            std::string request(buf, nread);

            parsing.fill_request(request);
               std::ostringstream response;
               response << "HTTP/1.1 200 OK\r\n";
                response << "Content-Type: text/html\r\n";
                response << "Content-Length: " << response_body.length() << "\r\n";
                response << "\r\n";
                response << response_body;
                std::string response_str = response.str();
                 char response_buf[response_str.size() + 1];
    std::copy(response_str.begin(), response_str.end(), response_buf);
    response_buf[response_str.size()] = '\0';

// Send the response
            send(client_sock, response_buf ,strlen(response_buf), 0);
        }
        close(client_sock);
    }
    close(sock);

    return 0;

}