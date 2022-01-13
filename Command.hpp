#include <json.hpp>

using nlohmann::json;
class Command {
  int type;
  bool fail;
  int id;
  json command;
};
