/* Thread_Posix.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 09/16/2014
 * Last Modified    : 09/16/2014
 * 
 */

#pragma once
#ifndef _ymp_Time_Time_Posix_H
#define _ymp_Time_Time_Posix_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Dependencies
#include <sys/time.h>
namespace ymp{
namespace Time{
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class WallClock{
    struct timeval time;

public:
    static WallClock Now();
    double operator-(const WallClock& x) const;
    double SecondsElapsed() const{
        return Now() - *this;
    }
};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
}
}
#endif