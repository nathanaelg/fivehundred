#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <string>

enum side_t {left_side, right_side};
std::string fixed_width_string(std::string in, unsigned width, side_t align);

#endif /* _CONSOLE_H_ */
