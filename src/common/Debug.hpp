#pragma once

class Debug {
public:
  Debug();
  ~Debug();
  void Log(const char *text);
  void Error(const char *text);
};