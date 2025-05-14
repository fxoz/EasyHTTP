#include <iostream>
#include <map>
#include <string>

#include "request.h"
#include "url.h"
#include "WebResponse.h"

void testing_url() {
    std::string url = "https://sub.sld.tld/path?as=index.aspx";
    std::string dFull, dShort, path;
    parseUrl(url, dFull, dShort, path);
    std::cout << dFull << " | " << dShort << " | " << path << std::endl;
    std::cout << dFull.compare("sub.sld.tld") << dShort.compare("sld.tld")  << path.compare("/path?as=index.aspx") << std::endl;
}

int main() {
    WebResponse r = request("https://echo-http-requests.appspot.com/echo");

    std::cout << "Raw response: " << r.raw << std::endl;
    std::cout << "HTTP Version: " << r.httpVersion << std::endl;
    std::cout << "Status Code: " << r.statusCode << std::endl;
    std::cout << "Latency full: " << r.latencyFullMs << "ms" << std::endl;
    std::cout << "Latency response: " << r.latencyResponseMs << "ms" << std::endl;
    std::cout << "Error: " << r.getError() << std::endl;

    return 0;
}
