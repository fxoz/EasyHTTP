//
// Created by Lynx on 2025-05-13.
//

#ifndef WEBRESPONSE_H
#define WEBRESPONSE_H

#include <map>
#include <string>
#include <iostream>

class WebResponse {
protected:

public:
    std::string _error;
    std::string raw;
    std::string text;

    int latencyFullMs;
    int latencyResponseMs;

    int statusCode;
    bool isGood;
    std::string statusMessage;
    std::string httpVersion;
    std::map<std::string, std::string> headers;

    WebResponse() = default;
    ~WebResponse() = default;

    friend std::ostream& operator<<(std::ostream& os, const WebResponse& r);

    void _processHeaders();
    void _processStatus();
    void _process();

    std::string getError() const {
        return _error;
    }
};

#endif //WEBRESPONSE_H
