/*list_parts.cc*/
#include <iostream>
#include <fstream>
#include <string>
#include "partbook.pb.h"
using namespace std;
 
// Iterates though all parts in the PartDetails and prints info about them.
void ListParts(const tutorial::PartDetails& part_book) {
  for (int i = 0; i < part_book.part_size(); i++) {
    const tutorial::Part& part = part_book.part(i);
 
    cout << "Part ID: " << part.partid() << endl;
    cout << "  Name: " << part.name() << endl;
    if (part.has_vendor()) {
      cout << "  Vendor: " << part.vendor() << endl;
    }
 
  }
}
 
// Main function:  Reads the entire part book from a file and prints all
//   the information inside.
int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;
 
  if (argc != 2) {
    cerr << "Usage:  " << argv[0] << " PART_BOOK_FILE" << endl;
    return -1;
  }
 
  tutorial::PartDetails part_book;
 
  {
    // Read the existing data file.
    fstream input(argv[1], ios::in | ios::binary);
    if (!part_book.ParseFromIstream(&input)) {
      cerr << "Failed to parse part book." << endl;
      return -1;
    }
  }
 
  ListParts(part_book);
 
  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();
 
  return 0;
}