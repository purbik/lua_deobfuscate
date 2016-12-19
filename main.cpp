/**
Wherigo lua text extractor
Author: purbik
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char * argv[])
{
  string funcName;
  string line;
  int i = 0;
  size_t pos1, pos2;

  ifstream in(argv[1]);
  ofstream out(argv[2]);


  while(getline(in, line))      ///find obfuscating function name
  {
    i++;
    istringstream iss(line);
    string word;
    getline(iss, word, ' ');
    if(word == "function")
    {
      getline(iss, funcName, '(');
      cerr << funcName << endl;
      break;
    }
    else
    {
      continue;
    }
  }

  for(int l = 0; l < 13; ++l)   ///copy obfuscating function
  {
    out << line << endl;
    getline(in, line);
    i++;
  }

  while(true)                   ///find all <funcName> function calls and save them in output program
  {
    pos1 = 0;
    pos2 = 0;
    while(pos1 != string::npos)
    {
      pos1 = line.find(funcName, pos2);
      if(pos1 != string::npos)
      {
        pos2 = line.find(')', pos1);
        cerr << "line: " << i << "\t" << pos1 << " - " << pos2 << endl;
        out << "print(" << line.substr(pos1, pos2-pos1+1) << ")" << endl;
      }
    }

    if(!getline(in,line))   ///cannot be in while condition, cause one line would be skipped (though it would not matter cause the <funcName> function will never appear there)
    {
      break;
    }
    i++;
  }
  return 0;
}
