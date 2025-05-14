//
// Created by Lynx on 2025-05-13.
//

#include "request.h"

#include <chrono>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <utility>

#include "url.h"
#include "WebResponse.h"

#pragma comment(lib, "ws2_32.lib")

WebResponse request(std::string url) {
    WebResponse res = {};

    auto timeStart = std::chrono::high_resolution_clock::now();
    std::string domainShort, domainFull, path;
    parseUrl(std::move(url), domainShort, domainFull, path);

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        res._error = "WSAStartup failed.";
        return res;
    }

    addrinfo hints{};
    addrinfo* serverInfo;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    const char* hostname = domainShort.c_str();
    const char* port = "80";

    if (getaddrinfo(hostname, port, &hints, &serverInfo) != 0) {
        res._error = "getaddrinfo failed.";
        WSACleanup();
        return res;
    }

    SOCKET sock = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);
    if (sock == INVALID_SOCKET) {
        res._error = "socket creation failed.";
        freeaddrinfo(serverInfo);
        WSACleanup();
        return res;
    }

    if (connect(sock, serverInfo->ai_addr, (int)serverInfo->ai_addrlen) == SOCKET_ERROR) {
        res._error = "connect failed.";
        closesocket(sock);
        freeaddrinfo(serverInfo);
        WSACleanup();
        return res;
    }

    freeaddrinfo(serverInfo);

    std::string request = "GET " + path + " HTTP/1.1\r\n";
    request += "Host: " + domainFull + "\r\n";
    request += "Connection: close\r\n";
    request += "\r\n";

    int bytesSent = send(sock, request.c_str(), request.length(), 0);
    if (bytesSent == SOCKET_ERROR) {
        res._error = "send failed.";
        closesocket(sock);
        WSACleanup();
        return res;
    }

    char buffer[4096];
    int bytesReceived;
    std::string rawResponse;

    auto timeResponse = std::chrono::high_resolution_clock::now();
    while ((bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesReceived] = '\0';
        rawResponse += buffer;
    }

    if (bytesReceived == SOCKET_ERROR) {
        res._error = "socket error.";
    }

    closesocket(sock);
    WSACleanup();

    res.raw = rawResponse;
    res.latencyFullMs = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - timeStart).count();

    res.latencyResponseMs = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - timeResponse).count();

    res._process();
    return res;
}
