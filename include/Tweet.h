#ifndef Tweet_h
#define Tweet_h

#include <exception>
#include <stdexcept>
#include <string>

class Tweet {
  private:
  std::string message;
  std::string user;

  bool isValid(const std::string& user) { return '@' == user[0]; }

  public:
  Tweet(){};
  Tweet(const std::string& message, const std::string& user)
      : message(message), user(user) {
    if (!isValid(user)) throw std::runtime_error("Invalid username");
  }

};
#endif

