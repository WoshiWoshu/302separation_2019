#include <string>
#include <algorithm>

bool hasOnlySpacesTabs(const std::string& str)
{
    if (str.find_first_not_of(' ') == str.npos
    || str.find_first_not_of('\t') == str.npos)
        return true;
    else
        return false;
}

bool isPosNum(const std::string &str)
{
    std::string::const_iterator itStr =
    std::find_if(str.begin(), str.end(), [](const char c) { return !std::isdigit(c); });

    return itStr == str.end();
}
