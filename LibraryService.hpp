
#ifndef _LIBRARY_LIBRARY_SERVICE_HPP_
#define _LIBRARY_LIBRARY_SERVICE_HPP_

#include "Book.hpp"
#include "Command.hpp"
class LibraryService {
  /* IMPORTANT NOTE :  The caller of these functions are responbilites for
   freeing the Book pointers that are returned :

   .create_book()

   .find_book()

   .find_all_books() <----- iterate over it

   .update_book()

   .patch_book()
   */
public:
  virtual void import(std::unordered_map<int, Book *> library, int id) = 0;
  virtual const Book *create_book(const Book &book) = 0;
  virtual bool validate(const Book &book) = 0;
  virtual std::stringstream execute_command(Command &command) = 0;

  virtual const Book *find_book(unsigned const int &id) = 0;
  virtual bool dupchk(const Book &book) = 0;
  virtual bool dupchk_upd(const Book &book, int id) = 0;
  virtual const std::unordered_map<int, Book *>
  find_all_books(const std::string &name = "", const std::string &author = "",
                 unsigned const int &pages = 0) = 0;

  virtual const Book *update_book(unsigned const int &id, const Book &book) = 0;
  virtual const Book *patch_book(unsigned const int &id, const Book &book) = 0;

  virtual bool delete_book(unsigned const int &id) = 0;

  virtual void delete_condition(const std::string &name = "",
                                const std::string &author = "",
                                unsigned const int &pages = 0) = 0;

  virtual void delete_all_books() = 0;
};
#endif // _LIBRARY_SERVICE_HPP_
