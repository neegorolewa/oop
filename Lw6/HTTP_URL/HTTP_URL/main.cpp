#include <iostream>
#include "CHttpUrl.h"

const std::string EXIT_COMMAND = "exit";

int main()
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line == EXIT_COMMAND)
        {
            break;
        }
        try
        {
            CHttpUrl url(line);
            std::cout << "Url: " << url.GetURL() << '\n'
                << "Protocol: " << ProtocolToStr(url.GetProtocol()) << '\n'
                << "Domain: " << url.GetDomain() << '\n'
                << "Port: " << url.GetPort() << '\n'
                << "Document: " << url.GetDocument() << '\n';
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}
