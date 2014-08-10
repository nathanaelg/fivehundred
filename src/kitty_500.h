#ifndef _KITTY_500_H_
#define _KITTY_500_H_

#include "card_collection_500.h"

class Kitty_500 : public CardCollection_500
{
public:
   Kitty_500();

   Card_500 * pop();
   std::string print_name(unsigned number) const;
};

#endif /* _KITTY_500_H_ */
