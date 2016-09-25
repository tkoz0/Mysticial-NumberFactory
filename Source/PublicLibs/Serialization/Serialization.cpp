/* Serialization.cpp
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 10/28/2012
 * Last Modified    : 09/26/2014
 * 
 */

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Dependencies
#include "PublicLibs/CompilerSettings.h"
#include "ParseException.h"
#include "Serialization.h"
namespace ymp{
namespace Serialization{
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
const ParseException UNEXPECTED_END_OF_STRING("Unexpected end of string.");
const ParseException UNEXPECTED_END_OF_LINE("Unexpected end of string.");
const ParseException INVALID_DIGIT("Unexpected end of string.");
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <typename ctype> YM_NO_INLINE
void parse_to_tab(const ctype*& str){
    ctype ch;
    do{
        ch = *str++;
        if (ch == '\0') UNEXPECTED_END_OF_STRING.fire();
        if (ch == '\n') UNEXPECTED_END_OF_LINE.fire();
    }while (ch != '\t');
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Line
YM_NO_INLINE void write_line(std::string& stream){
    stream += "\r\n";
}
YM_NO_INLINE void parse_line(const char*& str){
    char ch;
    do{
        ch = *str++;
        if (ch == '\0') UNEXPECTED_END_OF_STRING.fire();
    }while (ch != '\n');
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Integer
YM_NO_INLINE void write_siL(std::string& stream, const std::string& label, siL_t x){
    stream += label;
    stream += '\t';
    stream += std::to_string(x);
    write_line(stream);
}
YM_NO_INLINE siL_t parse_siL(const char*& str){
    //  Skip until after the first tab.
    parse_to_tab(str);

    //  Parse sign
    siL_t x = 0;
    bool sign = false;
    if (str[0] == '-'){
        str++;
        sign = true;
    }

    //  Parse number
    while (1){
        char ch = *str++;
        if (ch == '\0') UNEXPECTED_END_OF_STRING.fire();
        if (ch == '\r') continue;
        if (ch == '\n') break;
        if (ch < '0' || ch > '9') INVALID_DIGIT.fire();
        x *= 10;
        x += ch - '0';
    }

    //  Adjust sign
    if (sign)
        x = -x;

    return x;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Floating-Point
YM_NO_INLINE void write_float(std::string& stream, const std::string& label, double x){
    union{
        double f;
        u64_t i;
    };
    f = x;

    write_siL(stream, label, i);
}
YM_NO_INLINE double parse_float(const char*& str){
    union{
        double f;
        u64_t i;
    };
    i = (u64_t)parse_siL(str);
    return f;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  String
YM_NO_INLINE void write_str(std::string& stream, const std::string& label, const std::string& x){
    stream += label;
    stream += '\t';
    stream += x;
    write_line(stream);
}
YM_NO_INLINE std::string parse_str(const char*& str){
    //  Skip until after the first tab.
    parse_to_tab(str);

    std::string x;
    while (1){
        char ch = *str++;
        if (ch == '*') return x;
        if (ch == '\r') continue;
        if (ch == '\n') break;
        x += ch;
    }
    return x;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
}
}
