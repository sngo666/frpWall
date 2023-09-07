#include "./yamlUtils.h"

rule_config::~rule_config()
{
}

ostream &operator<<(ostream &out, const rule_config &config)
{
  out << "tables_type:  " << config.tables_type << endl;
  out << "log_folder_path: " << config.log_folder_path << endl;

  cout << "allow_ip: " << endl;
  for (auto iter : config.allow_ip)
  {
    cout << iter << endl;
  }

  cout << "forbidden_ip: " << endl;
  for (auto iter : config.forbidden_ip)
  {
    cout << iter << endl;
  }

  cout << "rules: " << endl;
  for (auto iter : config.rules)
  {
    cout << "-" << endl;
    cout << "ip: " << iter.ip << endl;
    cout << "port: " << iter.port << endl;
    cout << "country: " << iter.country << endl;
    cout << "province: " << iter.province << endl;
    cout << "city: " << iter.city << endl;
    cout << "time_per_hour: " << iter.time_per_hour << endl;
    cout << "-" << endl;
  }

  return out;
}

rule_config::rule_config(const string &filePath)
{
  YAML::Node config = YAML::LoadFile(filePath);
  // tables_type
  {
    this->tables_type = yamlUtils::getString("tables_type", config);
    if (this->tables_type == "")
    {
      cout << "[err] attribute \""
           << "tables_type"
           << "\" isn't existed." << endl;
      assert("tables_type loding error.");
    }
  }

  {
    this->log_folder_path = yamlUtils::getString("log_folder_path", config);
    if (this->log_folder_path == "")
    {
      cout << "[err] attribute \""
           << "log_folder_path"
           << "\" isn't existed." << endl;
      assert("log_folder_path loading error");
    }
  }

  {
    this->rules = vector<rule>(yamlUtils::getRule(config));
    if (this->rules.size() == 0)
    {
      cout << "[warn] attribute \""
           << "rules"
           << "\" contains nothing.check your format." << endl;
    }
  }

  {
    this->allow_ip = vector<string>(yamlUtils::getStrVector("allow_ip", config));
    if (this->allow_ip.size() == 0)
    {
      cout << "[warn] attribute \""
           << "allow_ip"
           << "\" contains nothing." << endl;
    }
  }

  {
    this->forbidden_ip = vector<string>(yamlUtils::getStrVector("forbidden_ip", config));
    if (this->forbidden_ip.size() != 0)
    {
      cout << "[warn] attribute \""
           << "forbidden_ip"
           << "\" contains nothing." << endl;
    }
  }
}
yamlUtils::yamlUtils()
{
}

yamlUtils::~yamlUtils()
{
}

vector<rule> yamlUtils::getRule(const YAML::Node &node)
{
  auto rules = node["rules"];
  vector<rule> res_vec;

  for (auto iter : rules)
  {
    if (iter["ip"].IsDefined() &&
        iter["port"].IsDefined() &&
        iter["country"].IsDefined() &&
        iter["province"].IsDefined() &&
        iter["city"].IsDefined() &&
        iter["time_per_hour"].IsDefined())
    {
      rule temp = {
          iter["ip"].as<string>(),
          iter["port"].as<int>(),
          iter["country"].as<string>(),
          iter["province"].as<string>(),
          iter["city"].as<string>(),
          iter["time_per_hour"].as<int>(),
      };
      res_vec.push_back(temp);
    }
    else
    {
      cout << "[warn] wrong form in yaml node \"rules\", which will not be loaded.such as:" << endl;
      cout << "  - {" << endl;
      cout << "      ip: \"1.2.3.4\"" << endl;
      cout << "      port: \"-1\"" << endl;
      cout << "      country: \"中国\"" << endl;
      cout << "      province: \"四川\"" << endl;
      cout << "      region: \"理塘\"" << endl;
      cout << "      time_per_hour: \"20\"" << endl;
      cout << "  }" << endl;
    }
  }
  cout << "[info] " << res_vec.size() << " rule(s) loaded and " << rules.size() - res_vec.size() << " rule(s) loading failed!" << endl;
  return res_vec;
}

string yamlUtils::getString(const string &key, const YAML::Node &node)
{
  string res_str = node[key].as<string>();
  if (res_str != "null")
  {
    return res_str;
  }
  return "";
}

vector<string> yamlUtils::getStrVector(const string &key, const YAML::Node &node)
{
  vector<string> resVec;
  if (node[key])
  {
    // cout << node[key] << endl;
    vector<string> arr = node[key].as<vector<string>>();
    if (arr.size() > 0)
    {
      for (auto ptr = arr.begin(); ptr != arr.end(); ptr++)
      {
        resVec.push_back(*ptr);
      }
    }
    else
      cout << "[warn] get nothing from key: " << key << endl;
  }
  return resVec;
}

int yamlUtils::getInteger(const string &key, const YAML::Node &node)
{
  int res_num = node[key].as<int>();
  if (node[key])
  {
    res_num = node[key].as<int>();
  }
  return res_num;
}

void yamlUtils::printVector(const vector<int> &m_v)
{
  for (int i = 0; i < m_v.size(); i++)
  {
    cout << m_v[i] << endl;
  }
  cout << "[info] " << m_v.size() << " elements printed!" << endl;
}

void yamlUtils::printVector(const vector<string> &m_v)
{
  for (int i = 0; i < m_v.size(); i++)
  {
    cout << m_v[i] << endl;
  }
  cout << "[info] " << m_v.size() << " elements printed!" << endl;
}