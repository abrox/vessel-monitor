#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <stdexcept>

#include <QPalette>
//#include <qlayout.h>

/// Simple utility to convert strings to numbers
/// copied from :
/// http://stackoverflow.com/questions/1012571/stdstring-to-float-or-double
///
template<typename T>
   T stringToNumber(const std::string& numberAsString)
   {
      T valor;

      std::stringstream stream(numberAsString);
      stream >> valor;
      if (stream.fail()) {
         std::runtime_error e(numberAsString);
         throw e;
      }
      return valor;
   }



QPalette colorTheme( const QColor &base );


#endif // UTILS_H

