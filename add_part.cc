/*add_part.cc*/
/* comment from local1 */
#include <iostream>
#include <fstream>
#include <string>
#include "partbook.pb.h"
using namespace std;
 
/* This function fills in a Part message based on user input.*/
void PromptForPart(tutorial::Part* part) {
  cout << "Enter part ID number: ";
  int partid;
  cin >> partid;
  part->set_partid(partid);
  cin.ignore(256, '\n');
 
  cout << "Enter part name: ";
  getline(cin, *part->mutable_name());
 
  cout << "Enter vendor name (blank for none): ";
  string vendor;
  getline(cin, vendor);
  if (!vendor.empty()) {
    part->set_vendor(vendor);
  }
 
}
 
/* Main function:  Reads the entire part list from a file,
 * adds one part based on user input, then writes it back out to the same
 *   file.
 */
int main(int argc, char* argv[]) {
  /* Verify that the version of the library that we linked against is
   * compatible with the version of the headers we compiled against.
   */
  GOOGLE_PROTOBUF_VERIFY_VERSION;
 
  if (argc != 2) {
    cerr << "Usage:  " << argv[0] << " PART_BOOK_FILE" << endl;
    return -1;
  }
 
  tutorial::PartDetails part_book;
 
  {
    // Read the existing part book.
    fstream input(argv[1], ios::in | ios::binary);
    if (!input) {
      cout << argv[1] << ": File not found.  Creating a new file." << endl;
    } else if (!part_book.ParseFromIstream(&input)) {
      cerr << "Failed to parse part book." << endl;
      return -1;
    }
  }
 
  // Add a new part.
  PromptForPart(part_book.add_part());
 
  {
    // Write the new part book back to disk.
    fstream output(argv[1], ios::out | ios::trunc | ios::binary);
    if (!part_book.SerializeToOstream(&output)) {
      cerr << "Failed to write part book." << endl;
      return -1;
    }
  }
 
  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();
 
  return 0;
}
