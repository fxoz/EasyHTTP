//
// Created by Lynx on 2025-05-13.
//

#include "url.h"

#include <string>

bool endsWith(const std::string &fullString, const std::string &ending) {
    if (ending.size() > fullString.size())
        return false;
    return fullString.compare(fullString.size() - ending.size(), ending.size(), ending) == 0;
}

std::string toShortDomain(std::string domainFull, int nSubdomains) {
    std::string domainShort;
    int countedDots = 0;
    for (int i = 0; i < domainFull.length(); i++) {
        char c = domainFull[i];

        if (countedDots >= nSubdomains)
            domainShort += c;

        if (c == '.')
            countedDots++;
    }

    return domainShort;
}

void parseUrl(std::string url, std::string &dShort, std::string &dFull, std::string &uPath) {
    // sft://
    // https://sub.sld.tld/path -> my.net, /path
    // a.co/b
    std::string domainFull; // sub.sld.tld
    std::string sld;
    std::string tld;
    std::string path;

    int nSubdomains = -1;// because of the dot before TLD
    bool isPath = false;

    std::string urlIter; // iterate over URL string
    for (int i = 0; i < url.length(); i++) {
        char c = url[i];

        if (c == '/') // WHEN / IS HIT
            isPath = true;

        if (endsWith(urlIter, "://")) { // END OF PROTOCOL
            domainFull = "";
            path = "";
            isPath = false; // '://' looks like a path
        }

        if (isPath) // AFTER PATH
            path += c;
        else { // BEFORE PATH
            domainFull += c;

            if (c == '.') // COUNT DOTS
                nSubdomains++;
        }

        urlIter += c;
    }

    path = path.empty() ? "/" : path;
    dFull = domainFull;
    dShort = toShortDomain(domainFull, nSubdomains);
    uPath = path;
}
