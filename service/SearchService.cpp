#include "SearchService.h"

SearchService::SearchService(BookDAO* bookDAO) : db(bookDAO) {}

SearchService::~SearchService() = default;

bool SearchService::searchBookById(const string& bookId, Book& book) const {
    return db->searchBookById(bookId, book);
}

vector<Book> SearchService::searchBooksByCategory(const string& category) const {
    return db->searchBooksByCategory(category);
}

vector<Book> SearchService::searchBookByAuthor(const string& author) const {
    return db->searchBookByAuthor(author);
}

bool SearchService::searchBookByTitle(const string& bookTitle, Book& book) const {
    return db->searchBookByTitle(bookTitle, book);
}