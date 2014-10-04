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
   void remove_card(Card_500 * card);
   void remove_card(Card::number_t number, Card::suit_t suit);
   bool has_card(Card_500 * card) const;
   bool has_card(Card::number_t number, Card::suit_t suit) const;

   // Printing
   std::string print() const;
   virtual std::string print_name(unsigned number) const;

   std::vector<Card_500 *> cards_in_suit(Card::suit_t suit, Game_500::suit_t trumps = Game_500::no_trumps) const;
   std::vector<Card_500 *> all_cards() const;
   void sort(Game_500::suit_t trumps, Card::suit_t led = Card::none);

   struct win_number_compare
   {
      Game_500::suit_t trumps;
      Card::suit_t led;
      win_number_compare(Game_500::suit_t t, Card::suit_t l) { trumps = t; led = l; }
      bool operator() (Card_500 * l, Card_500 * r) { return l->win_number(trumps, led) < r->win_number(trumps, led); }
   };

protected:
   std::vector<Card_500 *> cards;
   unsigned const max_size_;
   unsigned const deal_size_;
};

#endif /* _CARD_COLLECTION_500_H_ */
