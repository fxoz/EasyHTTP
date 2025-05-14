//
// Created by Lynx on 2025-05-13.
//

#include "WebResponse.h"

#include <iostream>
#include <set>
#include <sstream>
#include <windows.h>

std::string trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t");
    auto end = s.find_last_not_of(" \t");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

std::pair<std::string, std::string> parseHeader(const std::string& input) { // parse headers formatted like 'Name: Value'
    auto pos = input.find(':');
    if (pos == std::string::npos) return {trim(input), ""};
    return {trim(input.substr(0, pos)), trim(input.substr(pos + 1))};
}

int WebResponse::_processHeaders() {
    std::string result;
    std::istringstream iss(raw);

    std::cout << raw;

    int i = 0;
    for (std::string line; std::getline(iss, line); i++) {
        if (i == 0) continue;

        if (line == "\r") { // stop of headers
            return i
        }

        auto [headerName, headerValue] = parseHeader(line);
        headers[headerName] = headerValue;
    }

}

void WebResponse::_processStatus() {
    std::istringstream iss(raw.substr(0, raw.find('\n')));
    std::string version, code;

    if (!(iss >> version >> code)) {
        _error = "Failed to read the status line.";
        return;
    }

    if (version.find('/') == std::string::npos) {
        _error = "Could not parse HTTP version.";
        return;
    }

    httpVersion = version.substr(version.find('/') + 1);
    statusCode = std::stoi(code);
    std::getline(iss >> std::ws, statusMessage);
}

void WebResponse::_process() {
    _processStatus();
    int textStartLineNo = _processHeaders();

    isGood = statusCode < 400;


}