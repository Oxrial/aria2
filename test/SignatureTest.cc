#include "Signature.h"
#include "Exception.h"
#include "File.h"
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>

namespace aria2 {

class SignatureTest:public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(SignatureTest);
  CPPUNIT_TEST(testSave);
  CPPUNIT_TEST_SUITE_END();
public:
  void setUp() {}

  void tearDown() {}

  void testSave();
};


CPPUNIT_TEST_SUITE_REGISTRATION(SignatureTest);

void SignatureTest::testSave()
{
  Signature sig;
  sig.setBody("SIGNATURE");
  std::string filepath = "/tmp/aria2_SignatureTest_testSave";
  File outfile(filepath);
  if(outfile.exists()) {
    outfile.remove();
  } 
  CPPUNIT_ASSERT(sig.save(filepath));
  {
    std::ifstream in(filepath.c_str());
    std::string fileContent;
    in >> fileContent;
    CPPUNIT_ASSERT_EQUAL(sig.getBody(), fileContent);
  }
  // second attempt to save will fail because file already exists.
  CPPUNIT_ASSERT(!sig.save(filepath));
}

} // namespace aria2
