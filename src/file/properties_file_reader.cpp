#include "file/properties_file_reader.h"

#include <fstream>


/// ***********************************************************************************************************************
/// ************************************************* PUBLIC **************************************************************

/// CONSTRUCTOR()
PropertiesFileReader::PropertiesFileReader(std::string file_name) throw(std::string) {

  // Open file
  std::ifstream prop_file(file_name, std::ios::in);
  if (!prop_file.is_open())
    throw std::string("File cannot be opened");

  // Read all not commented or blank lines
  std::string line {""};
  std::string key;
  std::string value;
  size_t i {0};
  while (!prop_file.eof()){
    getline(prop_file, line);
    if ( line.find('=') == std::string::npos) // Not a property
      continue;

    // Add key and value, trimming leading and trailing spaces, and skipping if the first character is '#'
    key.clear();
    i = 0;
    while (line[i] != '='){
      if (!isspace(line[i]))
        key.push_back(line[i]);
      i++;
    };
    if (key.length() == 0 || key[0] == '#' || key[0] == '!') // Not a property
      continue;

    // Read value
    value.clear();
    while ( isspace(line[++i]) );
    value  = line.substr(i);
    // And remove trailing spaces
    i = value.length();
    while ( isspace(value[--i]) );
    value.erase(++i);

    _properties.insert(std::pair<std::string, std::string>(key, value));
  }

  // Close file
  prop_file.close();
}


/// property(string key, vector<T> &values)
template <class TYPE, typename = std::enable_if<std::is_arithmetic<TYPE>::value> >
std::vector<TYPE> PropertiesFileReader::propertyCast(std::string key) const throw(std::string) {
  std::pair <std::multimap<std::string, std::string>::const_iterator, std::multimap<std::string, std::string>::const_iterator> ret;
  ret = _properties.equal_range(key);
  if ( ret.first == _properties.end() )
    throw std::string("Key NOT found: " + key);

  std::vector<TYPE> values;
  values.reserve(_properties.count(key));
  while ( ret.first != ret.second ) {
    if ( std::is_floating_point<TYPE>::value)
      values.push_back(TYPE(atof( (ret.first->second).c_str() )));
    else if ( sizeof(TYPE) > sizeof(int) )
      values.push_back(TYPE(atol( (ret.first->second).c_str() )));
    else
      values.push_back(TYPE(atoi( (ret.first->second).c_str() )));

    ret.first++;
  }

  return values;
}


/// operator() (string key)
std::vector<std::string> PropertiesFileReader::operator() (std::string key) const throw(std::string) {
  std::pair <std::multimap<std::string, std::string>::const_iterator, std::multimap<std::string, std::string>::const_iterator> ret;
  ret = _properties.equal_range(key);
  if ( ret.first == _properties.end() )
    throw std::string("Key NOT found: " + key);

  std::vector<std::string> values;
  values.reserve(_properties.count(key));
  while ( ret.first != ret.second ) {
    values.push_back(ret.first->second);
    ret.first++;
  }

  return values;
}
