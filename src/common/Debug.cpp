#include "Debug.hpp"

#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

#ifdef __EMSCRIPTEN__
void Debug::Log(const char *text) {
  printf("LOG: %s\n", text);
}
void Debug::Error(const char *text) {
  printf("ERROR: %s\n", text);
}
#else
void Debug::Log(const char *text) {
  fmt::print(fmt::fg(fmt::color::yellow), "LOG: {}\n", text);
}
void Debug::Error(const char *text) {
  fmt::print(fmt::fg(fmt::color::red), "ERROR: {}\n", text);
}
#endif

Debug::Debug() {
}

Debug::~Debug() {
}
