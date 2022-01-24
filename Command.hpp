#ifndef _COMMAND
#define _COMMAND

#include <json.hpp>

using nlohmann::json;
class Command {
public:
  // create = 1
  // deleteid = 2
  // deleteall = 3
  // DeleteCond = 4
  // findid = 5
  // findAll = 6
  // findCond = 7
  // Update = 8
  // Patch = 9
  int type;
  int id;
  json command;
  std::vector<std::string> warning_log;
};

#endif //_COMMAND
