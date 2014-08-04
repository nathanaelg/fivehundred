#include "console.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

std::string fixed_width_string(std::string in, unsigned width, side_t align)
{
   wchar_t wide_in[1000];
   mbstowcs(wide_in, in.data(), 1000);
   unsigned in_length = wcslen(wide_in);
   if (in_length > width)
   {
      if (align == left_side) return in.substr(0, width);
      if (align == right_side) return in.substr(in_length - width);
      throw std::runtime_error("Align must be left or right");
   }
   else
   {
      std::string out = "";
      if (align == left_side) out += in;
      for (unsigned i = 0; i < width - in_length; i++) out += " ";
      if (align == right_side) out += in;
      return out;
   }
}
