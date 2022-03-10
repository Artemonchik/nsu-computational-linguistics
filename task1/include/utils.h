#pragma once

#include <string>

static int russianLower(wchar_t r) {
    switch (r) {
        case L'А':
            r = L'а';
            break;
        case L'Б':
            r = L'б';
            break;
        case L'В':
            r = L'в';
            break;
        case L'Г':
            r = L'г';
            break;
        case L'Д':
            r = L'д';
            break;
        case L'Е':
            r = L'е';
            break;
        case L'Ё':
            r = L'е';
            break;
        case L'Ж':
            r = L'ж';
            break;
        case L'З':
            r = L'з';
            break;
        case L'И':
            r = L'и';
            break;
        case L'Й':
            r = L'й';
            break;
        case L'К':
            r = L'к';
            break;
        case L'Л':
            r = L'л';
            break;
        case L'М':
            r = L'м';
            break;
        case L'Н':
            r = L'н';
            break;
        case L'О':
            r = L'о';
            break;
        case L'П':
            r = L'п';
            break;
        case L'Р':
            r = L'р';
            break;
        case L'С':
            r = L'с';
            break;
        case L'Т':
            r = L'т';
            break;
        case L'У':
            r = L'у';
            break;
        case L'Ф':
            r = L'ф';
            break;
        case L'Х':
            r = L'х';
            break;
        case L'Ц':
            r = L'ц';
            break;
        case L'Ч':
            r = L'ч';
            break;
        case L'Ш':
            r = L'ш';
            break;
        case L'Щ':
            r = L'щ';
            break;
        case L'Ъ':
            r = L'ъ';
            break;
        case L'Ы':
            r = L'ы';
            break;
        case L'Ь':
            r = L'ь';
            break;
        case L'Э':
            r = L'э';
            break;
        case L'Ю':
            r = L'ю';
            break;
        case L'Я':
            r = L'я';
            break;
        default:
            r = std::towlower(r);
    }
    return r;
}

static std::wstring make_wstring(std::string a) {
    std::wstring ws(a.begin(), a.end());
    return ws;
}

static std::wstring make_wstring(const char *a) {
    std::string str(a);
    std::wstring ws(str.begin(), str.end());
    return ws;
}