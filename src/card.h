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

   suit_t suit;
   number_t number;
   colour_t colour;

   Card(suit_t, number_t);
   std::string print() const;
   std::string print_full() const;
   std::string print_short_suit() const;
   std::string print_short_number() const;
};

#endif /* _CARD_H_ */
