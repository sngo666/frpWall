#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include "yaml-cpp/yaml.h"
#include "./app/yamlUtils.h"
#include "./app/logFilter.h"
#include "./app/asio_request.h"
#include "./include/xdb_searcher.h"
#include "./app/file_operator.h"

#include <boost/bind/bind.hpp>

using std::cin;
using std::cout;
using std::endl;

int main()
{
  system("chcp 65001");

  string filePath = "./test.yaml";

  YAML::Node node = YAML::LoadFile(filePath);
  string str;
  conn_info test_info = logFilter::get_conn_info("2023/03/19 07:08:09 [I] [proxy.go:189] [b1ff6b99d2870fc1] [ssh] get a user connection [170.64.190.69:55570]");

  // logFilter::print_conn_info(test_info);
  logFilter::ip_2_region("58.248.179.252");

  //  http://1.117.176.217/shu-main/index.php
  //  http://opendata.baidu.com/api.php?query=117.136.12.79&co=&resource_id=6006&oe=utf8
  //  https://ip.useragentinfo.com/json?ip=117.136.12.79
  //  https://blog.csdn.net/weixin_29053561/article/details/111996442
  // asio_request::post_request("opendata.baidu.com", "/api.php", "query=117.136.12.79&co=&resource_id=6006&oe=utf8");
  // asio_request::get_https_request("blog.csdn.net", "/weixin_29053561/article/details/111996442", "");
  // asio_request::get_https_request("ip.useragentinfo.com", "/json", "ip=117.136.12.79");

  string path = "./test.txt";
  ifstream test_file;
  test_file.open(path);
  long long loca = 0;
  string line;

  // if (test_file.is_open())
  // {
  //   while (getline(test_file, line))
  //   {
  //     loca = test_file.tellg();
  //     cout << line << endl;
  //     cout << loca << endl;
  //   }
  // }

  logFilter::log_watcher("D:/workspace/CppWorkSpace/frpWall/build");
  // system("pause");
  return 0;
}
