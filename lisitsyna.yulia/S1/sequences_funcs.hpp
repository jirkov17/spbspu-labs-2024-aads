#ifndef SEQUENCES_FUNCS_HPP
#define SEQUENCES_FUNCS_HPP

#include <iosfwd>
#include <string>
#include "list.hpp"

using sequences_t = List< std::pair< std::string, List< unsigned long long > > >;

sequences_t readSequences(size_t& maxLen, std::istream & in);
void outSequencesName(const sequences_t & sequences, std::ostream & out);
void outSequencesValues(const sequences_t & sequences, size_t maxLen, std::ostream & out);
List< unsigned long long > sumSequencesValues(const sequences_t & sequences, size_t maxLen);
void outSequence(const List< unsigned long long > & sequence, std::ostream & out);

#endif
