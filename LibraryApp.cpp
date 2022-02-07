#include "LibraryApp.hpp"

#include "LibraryFileService.hpp"
#include "LibraryService.hpp"
#include "Library_DatabaseService.hpp"
#include "Library_MemoryService.hpp"
void LibraryApp::runLibrary(string config) {
  bool tru = false;
  Book *retr;

  if (config == "m") {
    service = new LibraryMemoryService();
  } else if (config == "f") {
    service = new LibraryFileService();
    ExtractRet extr = extract();
    service->import(extr.books, extr.last_id);
  } else {
    service = new LibraryDatabaseService();
  }

  for (;;) {
    this->userinput = UserInput();
    std::cout.flush();
    Command command;
    userinput.GetInput();
    try {
      command = userinput.ParseInput();
    } catch (vector<string> errors) {
      cout << "\n             Log :             \n\r";
      cout << "-----------------------------------\n\r";

      for (int i = 0; i < errors.size(); i++) {
        cout << ". ";
        cout << errors[i] << "\n\r";
      }
      cout << "Command Failed , read my REAMDE.md on github : "
              "https://github.com/beemibrahim/Library-program\n\n";
      continue;
    }

    service->execute_command(command);
  }
}

std::string readFileIntoString(const std::string &path) {
  std::ifstream input_file(path);
  if (!input_file.is_open()) {
    std::cerr << "Could not open the file - '" << path << "'" << std::endl;
    exit(EXIT_FAILURE);
  }
  return std::string((std::istreambuf_iterator<char>(input_file)),
                     std::istreambuf_iterator<char>());
}

ExtractRet LibraryApp::extract() {
  ExtractRet answer;
  std::stringstream streamser;
  const std::filesystem::path Books{"Books"};
  for (auto &p : std::filesystem::directory_iterator(Books)) {
    // Getting contents of the file
    std::stringstream streamser;
    streamser << p;
    std::string filename = streamser.str(); // "Books/<filename>"
    filename = filename.substr(1, filename.size() - 2);
    int pos = filename.find(".");
    std::string ids = filename.substr(6, pos);
    int id = stoi(ids);
    std::string filecon = readFileIntoString(filename);
    json command = json::parse(filecon);

    // Extracting
    Book *book = new Book;
    book->name = command["name"];
    book->author = command["author"];
    book->pages = command["pages"];
    answer.books[id] = book;

    // Comparing to find conditions
  }
  std::fstream filey;
  filey.open("Information/last_id.txt");
  std::string su = readFileIntoString("Information/last_id.txt");
  answer.last_id = stoi(su);
  return answer;
}
