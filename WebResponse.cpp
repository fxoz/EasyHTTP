//
// Created by Lynx on 2025-05-13.
//

#include "WebResponse.h"

#include <sstream>

void WebResponse::_process() {
    std::istringstream iss(raw);
    std::string firstWord;
    std::string secondWord;

    iss >> firstWord >> secondWord;

    if (iss.fail()) {
        _error = "Failed to read the first two words.";
        return;
    }

    size_t firstSlash = firstWord.find('/');

    if (firstSlash == std::string::npos) {
        _error = "Could not parse HTTP version.";
        return;
    }

    httpVersion = firstWord.substr(firstSlash + 1);
    statusCode = std::stoi(secondWord);
}
