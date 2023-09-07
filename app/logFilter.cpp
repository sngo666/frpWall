#include "./logFilter.h"

conn_info::conn_info(conn_time m_t, string m_ip, int m_port) : time(m_t),
                                                               ip(m_ip),
                                                               port(m_port)
{
}

conn_info::conn_info()
{
  this->time = default_time;
  this->port = -1;
  this->ip = "defaut_ip";
}

conn_info::~conn_info()
{
}

logFilter::logFilter()
{
}

logFilter::~logFilter()
{
}

void logFilter::log_watcher(const string &log_folder_path)
{
  conn_time current_time = logFilter::get_current_time();
  string logPath = log_folder_path +
                   "/log." +
                   std::to_string(current_time.year) +
                   "-" + ((current_time.month < 10) ? ("0" + std::to_string(current_time.month)) : std::to_string(current_time.month)) +
                   "-" + ((current_time.day < 10) ? ("0" + std::to_string(current_time.day)) : std::to_string(current_time.day)) +
                   ".log";
  ifstream log_file;
  log_file.open(logPath);
  if (!log_file.is_open())
  {
    cout << "[warn] cannot open log file from " + logPath << endl;
    return;
  }
  cout << "[info] log_file opened: " + logPath << endl;
}

conn_time logFilter::get_current_time()
{

  time_t now = time(0);
  tm *curr = localtime(&now);
  return conn_time{
      1900 + curr->tm_year,
      1 + curr->tm_mon,
      curr->tm_mday,
      curr->tm_hour,
      curr->tm_min,
      curr->tm_sec};
}

conn_info logFilter::get_conn_info(const string &log)
{
  conn_info inf;
  vector<string> loginfo;
  std::regex messReg(R"(^([0-9]{4})/([0-9]{2})/([0-9]{2})\s([0-9]{2}):([0-9]{2}):([0-9]{2})\s(.*)\sget a user connection\s\[([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}):([0-9]{1,5})\]$)");
  std::smatch m;

  if (std::regex_match(log, m, messReg))
  {
    cout << "match success" << endl;

    for (const auto &elem : m)
    {
      // std::cout << elem << std::endl;
      loginfo.push_back(elem.str());
      // std::cout << elem.str() << std::endl;
    }

    conn_time m_time = {
        atoi(loginfo[1].c_str()),  // year
        atoi(loginfo[2].c_str()),  // month
        atoi(loginfo[3].c_str()),  // day
        atoi(loginfo[4].c_str()),  // hour
        atoi(loginfo[5].c_str()),  // minutes
        atoi(loginfo[6].c_str())}; // second
    return {m_time, loginfo[8], atoi(loginfo[9].c_str())};
  }
  return inf;
}
ostream &operator<<(ostream &out, const conn_info &info)
{
  out << "date: " << info.time.year << "/" << info.time.month << "/" << info.time.day << endl;
  out << "time: " << info.time.hour << ":" << info.time.minute << ":" << info.time.second << endl;

  out << "ip: " << info.ip << ":" << info.port << endl;

  return out;
}

// path : XDB_PATH
string logFilter::ip_2_region(const string &input_ip)
{
  char cwd[256];
  _getcwd(cwd, 256);
  const char *XDB_PATH = "ip2region.xdb";

  xdb_searcher_t searcher;
  char region_buffer[256], ip_buffer[16];
  const char *ip = input_ip.c_str();
  long search_time = 0;

  cout << "[info] "
       << "xdb PATH :" << cwd << "\\" << XDB_PATH << endl;

  int err = xdb_new_with_file_only(&searcher, XDB_PATH);
  if (err != 0)
  {
    cout << "failed to create xdb searcher from `" << XDB_PATH << "` with errno = " << err << endl;
    return "";
  }

  search_time = xdb_now();

  err = xdb_search_by_string(&searcher, ip, region_buffer, sizeof(region_buffer));
  if (err != 0)
  {
    cout << "failed search( " << ip << " ) with errno= " << err << endl;
  }
  else
  {
    cout << "IP Address : " << ip << endl;
    cout << "{region: " << region_buffer << ", took :" << xdb_now() - search_time << " μs}" << endl;
  }

  xdb_close(&searcher);
  return ip;
}
