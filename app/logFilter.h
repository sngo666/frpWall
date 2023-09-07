#ifndef __LOGFILTER_H__
#define __LOGFILTER_H__

#include <iostream>
#include <cstring>
#include <vector>
#include <regex>
#include <ctime>
#include <fstream>

#include <direct.h>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "yaml-cpp/yaml.h"
#include "../include/xdb_searcher.h"

using boost::asio::ip::tcp;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ostream;
using std::string;
using std::vector;
using namespace YAML;

std::string make_daytime_string();

struct conn_time
{
  int year;
  int month;
  int day;

  int hour;
  int minute;
  int second;

  friend ostream &operator<<(ostream &out, const conn_time &time)
  {
    out << "date: " << time.year << "/" << time.month << "/" << time.day << endl;
    out << "time: " << time.hour << ":" << time.minute << ":" << time.second << endl;

    return out;
  }
};

class conn_info
{
public:
  conn_info();
  conn_info(conn_time m_t, string m_ip, int m_port);
  ~conn_info();

  conn_time time;
  string ip;
  int port;

  const conn_time default_time = {-1, -1, -1, -1, -1, 1970};
  // string conn_type;
  // string token;
};

class logFilter
{
public:
  logFilter();
  ~logFilter();

  static conn_time get_current_time();
  static conn_info get_conn_info(const string &);
  friend ostream &operator<<(ostream &out, const conn_info &info);

  static void log_watcher(const string &log_folder_path);

  static string ip_2_region(const string &input_ip);
};

#endif