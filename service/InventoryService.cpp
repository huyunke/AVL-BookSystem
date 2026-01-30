#include "InventoryService.h"

InventoryService::InventoryService(BookDAO* bookDAO, BookCopyDAO* bookCopyDAO)
: db(bookDAO), bookCopyDAO(bookCopyDAO) {}

InventoryService::~InventoryService() = default;

bool InventoryService::addBook(const Book& book) const {
    return db->addBook(book);
}

bool InventoryService::deleteBook(const string& bookId) const {
    return db->deleteBook(bookId);
}

bool InventoryService::addBookCopy(const BookCopy& bookCopy) const {
    return bookCopyDAO->addBookCopy(bookCopy);
}

bool InventoryService::deleteBookCopy(const string& copyId) const {
    return bookCopyDAO->deleteBookCopy(copyId);
}

bool InventoryService::updateBook(const Book& book) const {
    return db->updateBook(book);
}