#ifndef _CARD_COLLECTION_500_H_
#define _CARD_COLLECTION_500_H_

#include <vector>
#include "card_500.h"

class CardCollection_500
{
public:
   CardCollection_500(unsigned max_size);
   CardCollection_500(unsigned max_size, unsigned deal_size);

   // Number of cards, maximum number allowed (before throwing exception), expected number on a deal
   unsigned size() const;
   unsigned max_size() const;
   unsigned deal_size() const;

   void add_card(Card_500 * card);
   Card_500 * remove_card(Card_500 * card);
   bool has_card(Card_500 * card) const;

   // Printing
   std::string print() const;
   virtual std::string print_name(unsigned number) const;
   std::vector<Card_500 *> cards_in_suit(Card::suit_t suit, Game_500::suit_t trumps = Game_500::no_trumps) const;
   void sort(Game_500::suit_t trumps, Card::suit_t led = Card::none);

protected:
   std::vector<Card_500 *> cards;
   unsigned const _max_size;
   unsigned const _deal_size;

   // Comparators required to use std::sort for sorting
   struct win_number_compare
   {
      Game_500::suit_t trumps;
      Card::suit_t led;
      win_number_compare(Game_500::suit_t t, Card::suit_t l) { trumps = t; led = l; }
      bool operator() (Card_500 * l, Card_500 * r) { return l->win_number(trumps, led) < r->win_number(trumps, led); }
   };
   struct suit_compare
   {
      Game_500::suit_t trumps;
      suit_compare(Game_500::suit_t t) { trumps = t; }
      bool operator() (Card_500 * l, Card_500 * r) { return l->suit(trumps) < r->suit(trumps); }
   };
};

#endif /* _CARD_COLLECTION_500_H_ */
