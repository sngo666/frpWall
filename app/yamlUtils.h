#ifndef __YAMLUTILS_H__
#define __YAMLUTILS_H__

#include <iostream>
#include <cstring>
#include <vector>
#include <cassert>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/parse.h"

using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace YAML;

struct rule
{
  string ip;
  int port;
  string country;
  string province;
  string city;
  int time_per_hour;
};

namespace YAML
{
  template <>
  struct convert<rule>
  {
    static Node encode(const rule &rhs)
    {
      Node node;
      node.push_back(rhs.ip);
      node.push_back(rhs.port);
      node.push_back(rhs.country);
      node.push_back(rhs.province);
      node.push_back(rhs.city);
      node.push_back(rhs.time_per_hour);
      return node;
    }

    static bool decode(const Node &node, rule &rhs)
    {

      rhs.ip = node["ip"].as<std::string>();
      rhs.country = node["country"].as<std::string>();
      rhs.province = node["province"].as<std::string>();
      rhs.city = node["city"].as<std::string>();
      rhs.port = node["port"].as<int>();
      rhs.time_per_hour = node["time_per_hour"].as<int>();

      return true;
    }
  };
}

class rule_config
{

  rule_config();

public:
  string tables_type;
  string log_folder_path;
  vector<string> allow_ip;
  vector<string> forbidden_ip;
  vector<rule> rules;

  rule_config(const string &filePath);
  ~rule_config();

  string get_str_by_attr(const string &attibute);
  string get_vec_vec_by_attr(const string &attibute);

  friend ostream &operator<<(ostream &out, const rule_config &config);
};

class yamlUtils
{

public:
  yamlUtils();
  ~yamlUtils();

  static string getString(const string &attibute, const YAML::Node &node);
  static vector<string> getStrVector(const string &attibute, const YAML::Node &node);
  static int getInteger(const string &attibute, const YAML::Node &node);
  static vector<rule> getRule(const YAML::Node &node);

  static void printVector(const vector<int> &);
  static void printVector(const vector<string> &);
};

#endif