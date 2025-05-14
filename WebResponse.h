//
// Created by Lynx on 2025-05-13.
//

#ifndef WEBRESPONSE_H
#define WEBRESPONSE_H

#include <string>

class WebResponse {
private:

public:
    int latencyFullMs;
    int latencyResponseMs;

    std::string _error;
    std::string raw;

    int statusCode;
    std::string httpVersion;

    WebResponse() = default;
    ~WebResponse() = default;

    void _process();

    std::string getError() const {
        return _error;
    }
};



#endif //WEBRESPONSE_H
