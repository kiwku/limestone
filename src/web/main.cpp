#include <GLES3/gl3.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

void main_loop() {
  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

int main() {
  fmt::print(fmt::fg(fmt::color::red) | fmt::emphasis::bold, "Hello World\n");
  emscripten_set_main_loop(main_loop, 0, 1);
  return 0;
}