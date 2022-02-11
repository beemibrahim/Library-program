#include "LibraryControls.hpp"
using namespace std;
using namespace restbed;
using json = nlohmann::json;
void create_book_handler(const shared_ptr<Session> session) {
  Handler service;
  service.service.import();
  const auto request = session->get_request();

  int content_length = request->get_header("Content-Length", 0);
  session->fetch(content_length, [&](const shared_ptr<Session> session,

                                     const Bytes &body) {
    service.create_handler(session, body);
    session->close();
  });
}

void find_all_book_handler(const shared_ptr<Session> session) {
  Handler service;
  service.service.import();
  const auto request = session->get_request();

  int content_length = request->get_header("Content-Length", 0);
  session->fetch(content_length, [&](const shared_ptr<Session> session,

                                     const Bytes &body) {
    service.find_all_book_handler(session, body);
    session->close();
  });
}

void delete_all_book_handler(const shared_ptr<Session> session) {
  Handler service;
  service.service.import();
  const auto request = session->get_request();

  int content_length = request->get_header("Content-Length", 0);
  session->fetch(content_length, [&](const shared_ptr<Session> session,

                                     const Bytes &body) {
    service.delete_all_book_handler(session, body);
    session->close();
  });
}

void find_book_handler(const shared_ptr<Session> session) {
  Handler service;
  service.service.import();
  const auto request = session->get_request();

  const string ids = request->get_path_parameter("id");
  int id = 0;
  try {
    id = stoi(ids);
  } catch (std::exception &e) {
    session->close(400, "Provide an id of a book");
    return;
  }

  int content_length = request->get_header("Content-Length", 0);
  session->fetch(content_length, [&](const shared_ptr<Session> session,

                                     const Bytes &body) {
    service.find_book_handler(session, body, id);
    session->close();
  });
}

void delete_book_handler(const shared_ptr<Session> session) {
  Handler service;
  service.service.import();
  const auto request = session->get_request();

  const string ids = request->get_path_parameter("id");
  int id = 0;
  try {
    id = stoi(ids);
  } catch (std::exception &e) {
    session->close(400, "Provide an id of a book");
    return;
  }

  int content_length = request->get_header("Content-Length", 0);
  session->fetch(content_length, [&](const shared_ptr<Session> session,

                                     const Bytes &body) {
    service.delete_book_handler(session, body, id);
    session->close();
  });
}

void update_book_handler(const shared_ptr<Session> session) {
  Handler service;
  service.service.import();
  const auto request = session->get_request();

  const string ids = request->get_path_parameter("id");
  int id = 0;
  try {
    id = stoi(ids);
  } catch (std::exception &e) {
    session->close(400, "Provide an id of a book");
    return;
  }

  int content_length = request->get_header("Content-Length", 0);
  session->fetch(content_length, [&](const shared_ptr<Session> session,

                                     const Bytes &body) {
    service.update_book_handler(session, body, id);
    session->close();
  });
}

void patch_book_handler(const shared_ptr<Session> session) {
  Handler service;
  service.service.import();
  const auto request = session->get_request();

  const string ids = request->get_path_parameter("id");
  int id = 0;
  try {
    id = stoi(ids);
  } catch (std::exception &e) {
    session->close(400, "Provide an id of a book");
    return;
  }

  int content_length = request->get_header("Content-Length", 0);
  session->fetch(content_length, [&](const shared_ptr<Session> session,

                                     const Bytes &body) {
    service.patch_book_handler(session, body, id);
    session->close();
  });
}

int main(const int, const char **) {

  auto res = make_shared<Resource>();
  res->set_path("/api/book");
  res->set_method_handler("POST", create_book_handler);
  res->set_method_handler("GET", find_all_book_handler);
  res->set_method_handler("DELETE", delete_all_book_handler);

  auto resb = make_shared<Resource>();
  resb->set_path("/api/book/{id: .*}");
  resb->set_method_handler("GET", find_book_handler);
  resb->set_method_handler("DELETE", delete_book_handler);
  resb->set_method_handler("PUT", update_book_handler);
  resb->set_method_handler("PATCH", patch_book_handler);

  auto settings = make_shared<Settings>();
  settings->set_port(1984);
  settings->set_default_header("Connection", "close");

  Service service;
  service.publish(res);
  service.publish(resb);

  service.start(settings);

  return EXIT_SUCCESS;
}
