/*
 * Copyright (C) 2021 ~ 2022 Deepin Technology Co., Ltd.
 *
 * Author:     weizhixiang <weizhixiang@uniontech.com>
 *
 * Maintainer: weizhixiang <weizhixiang@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "dstring.h"

#include <assert.h>

DString::DString()
{

}

DString::~DString()
{

}

std::vector<std::string> DString::splitChars(const char *cs, char c)
{
    assert(cs);

    std::vector<std::string> ret;
    unsigned long idx = 0;
    unsigned long size = strlen(cs);
    bool found = false;
    std::string sub;
    for (unsigned long i=0; i < size; i++) {
        if (!strneq(&cs[i], &c, 1))
            continue;

        sub.assign(cs, found ? idx+1:idx, found ? i-idx-1:i-idx);
        if (idx < i && !sub.empty()) {
            ret.push_back(sub);
        }
        idx = i;
        found = true;
    }
    sub.assign(cs, found ? idx+1:idx, found ? size-idx-1:size-idx);
    if (idx < size && !sub.empty()) {
        ret.push_back(sub);
    }

    return ret;
}

std::vector<std::string> DString::splitStr(const std::string &str, char c)
{
    return splitChars(str.c_str(), c);
}

std::vector<std::string> DString::splitVectorChars(const std::vector<char> &content, size_t length, char c)
{
    std::vector<std::string> ret;
    size_t pos = 0;
    bool hasChar = true;
    for (size_t i = 0; i < length; i++) {
        if (content[i] == c && i > pos && hasChar) {
            std::string str;
            for (size_t j = pos; j <= i; j++) {
                str += std::string(1, content[j]);
            }
            ret.push_back(str);
            pos = i + 1;
            hasChar = false;
        } else {
            hasChar = true;
        }
    }

    return ret;
}

bool DString::startWith(const char *chars, const char *prefix)
{
    assert(chars);
    assert(prefix);

    size_t len;
    len = strlen(prefix);
    return strneq(chars, prefix, len);
}

bool DString::startWith(const std::string &str, const std::string &prefix)
{
    return startWith(str.c_str(), prefix.c_str());
}

bool DString::endWith(const char *chars, const char *suffix)
{
    assert(chars);
    assert(suffix);

    size_t charsLen = strlen(chars);
    size_t suffixLen = strlen(suffix);

    if (charsLen == 0 || charsLen < suffixLen)
        return false;

    return memcmp(chars + charsLen - suffixLen, suffix, suffixLen) == 0;
}

bool DString::endWith(const std::string &str, const std::string &suffix)
{
    return endWith(str.c_str(), suffix.c_str());
}

char *DString::delQuote(const char *chars)
{
    char *data = nullptr;
    if (!chars)
        return data;

    if (strneq(chars, "\"", 1) && strneq(chars + strlen(chars) - 1, "\"", 1)) {
        data = static_cast<char *>(calloc(1, strlen(chars) - 2));
        memcpy(data, chars + 1, strlen(chars) - 1);
    } else {
        data = static_cast<char *>(calloc(1, strlen(chars) + 1));
        memcpy(data, chars, strlen(chars) + 1);
    }

    return data;
}

void DString::delQuote(std::string &str)
{
    while (*str.begin() == '\"' && *str.rbegin() == '\"')
        str.assign(str.substr(1, str.size() - 2));
}

std::string DString::join(std::vector<std::string> strs, std::string joinStr)
{
    std::string ret;
    for (uint i = 0; i < strs.size(); i++) {
        if (i < strs.size() - 1) {
            ret += strs[i] + joinStr;
        } else {
            ret += strs[i];
        }
    }
    return ret;
}

