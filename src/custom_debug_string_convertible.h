//
//  custom_debug_string_convertible.h
//  secp256k1_bitcoin
//
//  Created by pebble8888 on 2018/03/06.
//  Copyright © 2018年 pebble8888. All rights reserved.
//

#ifndef custom_debug_string_convertible_h
#define custom_debug_string_convertible_h

#include <string>

class CustomDebugStringConvertible {
    virtual std::string debugString(void) = 0;
};

#endif /* custom_debug_string_convertible_h */
