#include <cstdlib>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <memory>
#include <restbed>
using namespace std;
using namespace restbed;
using json = nlohmann::json;
void post_method_handler(const shared_ptr<Session> session) {
  const auto request = session->get_request();

  int content_length = request->get_header("Content-Length", 0);

  session->fetch(content_length,
                 [](const shared_ptr<Session> session, const Bytes &body) {
                   json object = json::parse(string(body.begin(), body.end()));
                   /*
                   cout << "hello";
                   */
                   int cool = object["hello"];
                   cool += 1;
                   object["hello"] = cool;
                   string dump = object.dump();
                   int size = dump.size();
                   fprintf(stdout, "%.*s\n", size, body.data());
                   session->close(OK, dump);
                 });
}

int main(const int, const char **) {

  auto res = make_shared<Resource>();
  res->set_path("/api/book");
  res->set_method_handler("POST", post_method_handler);

  auto settings = make_shared<Settings>();
  settings->set_port(1984);
  settings->set_default_header("Connection", "close");

  Service service;
  service.publish(res);
  service.start(settings);

  return EXIT_SUCCESS;
}
