#ifndef SEMESTRAL_SRC_USER_INTERFACES_ABSTRACT_EXIT_EXCEPTION_H_
#define SEMESTRAL_SRC_USER_INTERFACES_ABSTRACT_EXIT_EXCEPTION_H_

#include <stdexcept>

class ExitException : public std::runtime_error
{
public:
    ExitException() : std::runtime_error("") {}
};

#endif //SEMESTRAL_SRC_USER_INTERFACES_ABSTRACT_EXIT_EXCEPTION_H_
