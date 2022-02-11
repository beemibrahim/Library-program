#include "Library_DatabaseService.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <memory>
#include <restbed>

using namespace std;
using namespace restbed;
using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

class Handler {
public:
  LibraryDatabaseService service;
  void create_handler(const shared_ptr<Session> session, const Bytes &body);
  void find_all_book_handler(const shared_ptr<Session> session,
                             const Bytes &body);
  void delete_all_book_handler(const shared_ptr<Session> session,
                               const Bytes &body);
  void find_book_handler(const shared_ptr<Session> session, const Bytes &body,
                         int id);
  void delete_book_handler(const shared_ptr<Session> session, const Bytes &body,
                           int id);
  void update_book_handler(const shared_ptr<Session> session, const Bytes &body,
                           int id);
  void patch_book_handler(const shared_ptr<Session> session, const Bytes &body,
                          int id);
};
