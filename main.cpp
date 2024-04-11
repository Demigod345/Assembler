#include "src/pass2.cpp"

using namespace std;

int main()
{
  cout << "****Input file and executable(assembler.out) should be in same folder****" << endl
       << endl;
  cout << "Enter name of input file:";
  cin >> fileName;

  cout << "\nLoading OPTAB" << endl;
  load_tables();

  cout << "\nPerforming PASS1" << endl;
  cout << "Writing intermediate file to 'intermediate_" << fileName << "'" << endl;
  cout << "Writing error file to 'error_" << fileName << "'" << endl;
  pass1();

  cout << "Writing SYMBOL TABLE" << endl;
  printtab.open("tables_" + fileName);
  writeToFile(printtab, "**********************************SYMBOL TABLE*****************************\n");
  for (auto const &it : SYMTAB)
  {
    writestring += it.first + ":-\t" + "name:" + it.second.name + "\t|" + "address:" + it.second.address + "\t|" + "relative:" + intToStringHex(it.second.relative) + " \n";
  }
  writeToFile(printtab, writestring);

  writestring = "";
  cout << "Writing LITERAL TABLE" << endl;

  writeToFile(printtab, "**********************************LITERAL TABLE*****************************\n");
  for (auto const &it : LITTAB)
  {
    writestring += it.first + ":-\t" + "value:" + it.second.value + "\t|" + "address:" + it.second.address + " \n";
  }
  writeToFile(printtab, writestring);

  writestring = "";
  cout << "Writing EXTREF TABLE" << endl;

  writeToFile(printtab, "**********************************EXTREF TABLE*****************************\n");
  for (auto const &it0 : CSECT_TAB)
  {
    for (auto const &it : it0.second.EXTREF_TAB)
      writestring += it.first + ":-\t" + "name:" + it.second.name + "\t|" + it0.second.name + " \n";
  }
  writeToFile(printtab, writestring);

  writestring = "";
  cout << "Writing EXTDEF TABLE" << endl;

  writeToFile(printtab, "**********************************EXTDEF TABLE*****************************\n");
  for (auto const &it0 : CSECT_TAB)
  {
    for (auto const &it : it0.second.EXTDEF_TAB)
    {
      if (it.second.name != "undefined")
        writestring += it.first + ":-\t" + "name:" + it.second.name + "\t|" + "address:" + it.second.address + "\t|" + " \n";
    }
  }

  writeToFile(printtab, writestring);

  cout << "\nPerforming PASS2" << endl;
  cout << "Writing object file to 'object_" << fileName << "'" << endl;
  cout << "Writing listing file to 'listing_" << fileName << "'" << endl;
  pass2();
}