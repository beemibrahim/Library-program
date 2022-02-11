#include "LibraryControls.hpp"

void Handler::create_handler(const shared_ptr<Session> session,

                             const Bytes &body) {

  if (!json::accept(string(body.begin(), body.end()))) {
    session->close(400, "Json is invalid");
    return;
  }
  ordered_json object = ordered_json::parse(string(body.begin(), body.end()));
  // Are there three entries (name,author,pages)
  if (object.size() != 3) {
    session->close(400, "File doesnt have three entries");
    return;
  }

  // The Entries are this
  if (!object.contains("name") || !object.contains("author") ||
      !object.contains("pages")) {
    session->close(400, "File doesnt contain book propeties");
    return;
  }
  // The Entries are of this type
  if (!object["name"].is_string() || !object["author"].is_string() ||
      !object["pages"].is_number_integer()) {
    session->close(400, "Files book propeties are the wrong type");
    return;
  }
  // Are The Pages Non Zero , is the name/author empty ??
  if (object["pages"] <= 0 || object["name"] == "" || object["author"] == "") {
    session->close(
        400,
        "Files book propeties for empty / page number is zero or negative");
    return;
  }
  string author = object["author"];

  // Are there Letters In Author ??
  bool fail = true;
  for (int i = 0; i < author.size(); i++) {
    if ((author[i] > 96 && author[i] < 123) ||
        (author[i] > 64 && author[i] < 91)) {
      fail = false;
    }
  }
  if (fail == true) {
    session->close(400, "The Author must at least have one letter to be valid");
    return;
  }

  Book create;
  create.name = object["name"];
  create.author = object["author"];
  create.pages = object["pages"];

  try {
    delete service.create_book(create);
  } catch (vector<string> errors) {
    session->close(400, "Book is a duplicate");
    return;
  }
  ifstream input_file("ServerStorage/last_id.txt");
  std::string ids = std::string((std::istreambuf_iterator<char>(input_file)),
                                std::istreambuf_iterator<char>());
  int newid = stoi(ids);
  object["id"] = newid;
  string dump = object.dump(0);
  fprintf(stdout, "%.*s\n", (int)body.size(), body.data());
  session->close(OK, dump);
}

void Handler::find_all_book_handler(const shared_ptr<Session> session,

                                    const Bytes &body) {
  if (service.are_existing_books()) {
    session->close(400, "No Books Are In The Library");
    return;
  }
  std::unordered_map<int, Book *> m_books = service.find_all_books("", "", 0);
  std::unordered_map<int, Book *>::iterator it = m_books.begin();
  std::stringstream streamy;
  ordered_json emptyAe = ordered_json::array();
  for (; it != m_books.end(); it++) {
    ordered_json object;
    object["name"] = it->second->name;
    object["author"] = it->second->author;
    object["pages"] = it->second->pages;
    object["id"] = it->first;
    string dump = object.dump(0);
    streamy << dump << "\n\n";
  }
  string print = streamy.str();
  session->close(200, print);
}

void Handler::delete_all_book_handler(const shared_ptr<Session> session,
                                      const Bytes &body) {
  if (service.are_existing_books()) {
    session->close(400, "No Books Are In The Library");
    return;
  }
  service.delete_all_books();
  session->close(200, "All Books Deleted");
}

void Handler::find_book_handler(const shared_ptr<Session> session,
                                const Bytes &body, int id) {
  const Book *book = service.find_book(id);
  if (book == nullptr) {
    session->close(400, "Book doesnt exist");
  }
  Book Booky = *book;
  delete book;
  ordered_json object;
  object["name"] = Booky.name;
  object["author"] = Booky.author;
  object["pages"] = Booky.pages;
  object["id"] = id;
  string dump = object.dump(0);
  session->close(200, dump);
}

void Handler::delete_book_handler(const shared_ptr<Session> session,
                                  const Bytes &body, int id) {
  const Book *book = service.find_book(id);
  if (book == nullptr) {
    session->close(400, "Book doesnt exist");
    return;
  }
  service.delete_book(id);
  session->close(200, "Book Successfully Deleted");
}

void Handler::update_book_handler(const shared_ptr<Session> session,
                                  const Bytes &body, int id) {

  if (!json::accept(string(body.begin(), body.end()))) {
    session->close(400, "Json is invalid");
    return;
  }
  const Book *book = service.find_book(id);
  if (book == nullptr) {
    session->close(400, "Book doesnt exist");
    return;
  }

  ordered_json object = ordered_json::parse(string(body.begin(), body.end()));
  // Are there three entries (name,author,pages)
  if (object.size() != 3) {
    session->close(400, "File doesnt have three entries");
    return;
  }

  // The Entries are this
  if (!object.contains("name") || !object.contains("author") ||
      !object.contains("pages")) {
    session->close(400, "File doesnt contain book propeties");
    return;
  }
  // The Entries are of this type
  if (!object["name"].is_string() || !object["author"].is_string() ||
      !object["pages"].is_number_integer()) {
    session->close(400, "Files book propeties are the wrong type");
    return;
  }
  // Are The Pages Non Zero , is the name/author empty ??
  if (object["pages"] <= 0 || object["name"] == "" || object["author"] == "") {
    session->close(
        400,
        "Files book propeties for empty / page number is zero or negative");
    return;
  }
  string author = object["author"];

  // Are there Letters In Author ??
  bool fail = true;
  for (int i = 0; i < author.size(); i++) {
    if ((author[i] > 96 && author[i] < 123) ||
        (author[i] > 64 && author[i] < 91)) {
      fail = false;
    }
  }
  if (fail == true) {
    session->close(400, "The Author must at least have one letter to be valid");
    return;
  }
  Book create;
  create.name = object["name"];
  create.author = object["author"];
  create.pages = object["pages"];
  try {
    service.update_book(id, create);
  } catch (vector<string> errors) {
    session->close(400, "book is a duplicate");
    return;
  }
  object["id"] = id;
  string dump = object.dump(0);
  session->close(200, dump);
}

void Handler::patch_book_handler(const shared_ptr<Session> session,
                                 const Bytes &body, int id) {
  // Is the Json Valid ??
  Book create;
  create.name = "";
  create.author = "";
  create.pages = 0;

  if (!json::accept(string(body.begin(), body.end()))) {
    session->close(400, "File isnt a valid json File");
    return;
  }
  const Book *book = service.find_book(id);
  if (book == nullptr) {
    session->close(400, "Book doesnt exist");
    return;
  }

  ordered_json object = ordered_json::parse(string(body.begin(), body.end()));

  if (object.size() < 1 || object.size() > 3) {
    session->close(400, "Patch propeties not specified");
    return;
  }

  if (!object.contains("name") && !object.contains("author") &&
      !object.contains("pages")) {
    session->close(400, "Patch propeties not specified");
    return;
  }

  int exsize = 0;
  if (object.contains("name")) {
    if (!object["name"].is_string()) {
      session->close(400, "Files book propeties are the wrong type");
      return;
    }
    if (object["name"] == "") {
      session->close(400, "Book propeties are empty");
      return;
    }
    create.name = object["name"];
    exsize += 1;
  }
  if (object.contains("author")) {
    if (!object["author"].is_string()) {
      session->close(400, "Files book propeties are the wrong type");
      return;
    }
    if (object["author"] == "") {
      session->close(400, "Book propeties are empty");
      return;
    }

    string author = object["author"];
    // Are there Letters In Author ??
    bool fail = true;
    for (int i = 0; i < author.size(); i++) {
      if ((author[i] > 96 && author[i] < 123) ||
          (author[i] > 64 && author[i] < 91)) {
        fail = false;
      }
    }
    if (fail == true) {
      session->close(400,
                     "The Author must at least have one letter to be valid");
      return;
    }
    create.author = object["author"];

    exsize += 1;
  }
  if (object.contains("pages")) {
    if (!object["pages"].is_number_integer()) {
      session->close(400, "Files book propeties are the wrong type");
      return;
    }
    if (object["pages"] <= 0) {
      session->close("The number of pages are invalid");
      return;
    }

    exsize += 1;
    create.pages = object["pages"];
  }
  if (object.size() != exsize) {
    session->close(400, "Patch propeties are invalid");
    return;
  }
  const Book *books;
  Book booku;
  try {
    books = service.patch_book(id, create);
    booku = *books;
    delete books;
  } catch (vector<string> errors) {
    session->close(400, "Book would have been a duplicate if patched");
    return;
  }

  ordered_json object2;
  object2["name"] = booku.name;
  object2["author"] = booku.author;
  object2["pages"] = booku.pages;
  object2["id"] = id;
  string dump = object2.dump(0);
  session->close(200, dump);
}
