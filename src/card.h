#ifndef _CARD_H_
#define _CARD_H_

#include <map>
#include <string>

template <typename key_t, typename value_t>
value_t find_with_exception(std::map<key_t, value_t> const & map, key_t key) {
   typedef std::map<key_t, value_t> map_t;
   typename map_t::const_iterator i = map.find(key);
   if (i == map.end()) throw "Could not find key.";
   return i->second;
}

class Card
{
public:
   enum suit_t {none, hearts, diamonds, clubs, spades};
   enum number_t {ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, joker};
   enum colour_t {red, black, neither};

   Card(number_t number, suit_t suit = none);

   friend bool operator== (Card const &c1, Card const &c2);
   friend bool operator!= (Card const &c1, Card const &c2);

   suit_t suit() const;
   number_t number() const;
   colour_t colour() const;

   std::string print() const;
   std::string print_full() const;
   std::string print_short_suit() const;
   std::string print_short_number() const;

protected:
   suit_t _suit;
   number_t _number;
   colour_t _colour;
};

#endif /* _CARD_H_ */
