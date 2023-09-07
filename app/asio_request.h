#ifndef ASIO_REQUEST_H
#define ASIO_REQUEST_H

#include <stdio.h>
#include <iostream>
#include <fstream>
// #include "json.h"
#include "boost/asio.hpp"
#include "boost/asio/ssl.hpp"

using namespace std;
// using boost::asio::ssl;
using boost::asio::ip::tcp;
typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;

namespace asio_request
{
  string post_request(const string &, const string &, const string &);
  string post_https_request(const string &, const string &, const string &);

  string get_request(const string &, const string &, const string &);
  string get_https_request(const string &, const string &, const string &);
};

#endif
