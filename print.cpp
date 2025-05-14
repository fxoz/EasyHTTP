//
// Created by Felix on 2025-05-14.
//


#include <string>
#include <windows.h>

#include "WebResponse.h"


constexpr int RED = 64;
constexpr int BLUE = 16;
constexpr int GREEN = 32;
constexpr int WHITE = 7;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printField(std::ostream& os, const std::string& label, const auto& value, auto color) {
    setColor(color);
    os << label;
    setColor(WHITE);
    os << " " << value << '\n';
}

std::ostream& operator<<(std::ostream& os, const WebResponse& r) {
    os << '\n';
    printField(os, "HTTP", r.httpVersion, BLUE);
    printField(os, "Status Code", r.statusCode, BLUE);
    printField(os, "Status Message", r.statusMessage, BLUE);
    printField(os, "Latency (Full)", std::to_string(r.latencyFullMs) + "ms", BLUE);
    printField(os, "Latency (Response)", std::to_string(r.latencyResponseMs) + "ms", BLUE);

    if (!r.getError().empty()) {
        printField(os, "ERROR", r.getError(), RED);
    }

    return os;
}
