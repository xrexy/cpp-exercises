#ifndef PROMPT_H
#define PROMPT_H

#include <string>

template <typename T>
T prompt(const std::string &message, bool (*validationFunc)(T));

#endif // PROMPT_H
