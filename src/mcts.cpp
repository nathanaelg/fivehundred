#include "mcts.h"

void MCTS::check(bool expr, const char* message)
{
   if (!expr) {
      throw std::invalid_argument(message);
   }
}

void MCTS::assertion_failed(const char* expr, const char* file_cstr, int line)
{
   using namespace std;

   // Extract the file name only.
   string file(file_cstr);
   auto pos = file.find_last_of("/\\");
   if (pos == string::npos) {
      pos = 0;
   }
   file = file.substr(pos + 1);  // Returns empty string if pos + 1 == length.

   stringstream sout;
   sout << "Assertion failed: " << expr << " in " << file << ":" << line << ".";
   throw runtime_error(sout.str().c_str());
}
