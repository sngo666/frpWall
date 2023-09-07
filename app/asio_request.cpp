#include "asio_request.h"

string asio_request::post_request(const string &host, const string &path, const string &form)
{
  long length = form.length();

  boost::asio::io_service service;

  tcp::resolver resolver(service);
  // tcp::resolver::query query(host.c_str(), "http");
  tcp::resolver::iterator iter = resolver.resolve(host, "80");

  tcp::socket _socket(service);
  boost::asio::connect(_socket, iter);

  boost::asio::streambuf request;
  ostream request_stream(&request);

  request_stream << "POST " << path << " HTTP/1.1\r\n";
  request_stream << "Host: " << host << "\r\n";
  request_stream << "Accept: */*\r\n";
  request_stream << "Content-Type:application/json; charset=utf-8\r\n";
  request_stream << "Content-Length: " << length << "\r\n";
  request_stream << "Connection: close\r\n\r\n";
  request_stream << form;

  boost::asio::write(_socket, request);

  boost::asio::streambuf response;
  boost::asio::read_until(_socket, response, "\r\n");

  istream response_stream(&response); // 应答流
  string http_version;
  response_stream >> http_version;
  unsigned int status_code;
  response_stream >> status_code;
  string status_message;
  getline(response_stream, status_message);
  if (!response_stream || http_version.substr(0, 5) != "HTTP/")
  {
    printf("invaliable respond\n");
  }
  if (status_code != 200)
  {
    printf("response returning status code %d\n", status_code);
  }

  boost::asio::read_until(_socket, response, "\r\n\r\n");

  string header;
  int len = 0;
  while (getline(response_stream, header) && header != "\r")
  {
    if (header.find("Content-Length: ") == 0)
    {
      stringstream stream;
      stream << header.substr(16);
      stream >> len;
    }
  }

  long size = response.size();

  if (size > 0)
  {
    // .... do nothing
  }

  boost::system::error_code error;
  while (boost::asio::read(_socket, response, boost::asio::transfer_at_least(1), error))
  {
    // 获取应答长度
    size = response.size();
    if (len != 0)
    {
      cout << size << "  Byte  " << (size * 100) / len << "%\n";
    }
  }
  if (error != boost::asio::error::eof)
  {
    throw boost::system::system_error(error);
  }

  cout << size << " Byte download finished." << endl;

  // 将streambuf类型转换为string类型返回
  istream is(&response);
  is.unsetf(ios_base::skipws);
  string sz;
  sz.append(istream_iterator<char>(is), istream_iterator<char>());

  cout << sz << endl;

  // 返回转换后的字符串
  return sz;
}
string asio_request::post_https_request(const string &host, const string &path, const string &form)
{
  long length = form.length();

  boost::asio::io_service service;
  tcp::resolver resolver(service);

  boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23_client);
  // ctx.set_default_verify_paths();
  ctx.set_verify_mode(boost::asio::ssl::context::verify_none);
  ssl_socket _ssl_socket(service, ctx);
  auto iter = resolver.resolve(host, "443");

  boost::asio::connect(_ssl_socket.next_layer(), iter.begin(), iter.end());
  _ssl_socket.lowest_layer().set_option(tcp::no_delay(true));

  // _ssl_socket.set_verify_mode(boost::asio::ssl::verify_peer);
  // _ssl_socket.set_verify_callback(boost::asio::ssl::rfc2818_verification(host));
  _ssl_socket.handshake(ssl_socket::client);

  boost::asio::streambuf request;
  ostream request_stream(&request);

  request_stream << "POST " << path << " HTTP/1.1\r\n";
  request_stream << "Host: " << host << "\r\n";
  request_stream << "Accept: */*\r\n";
  request_stream << "Content-Type:application/json; charset=utf-8\r\n";
  request_stream << "Content-Length: " << length << "\r\n";
  request_stream << "Connection: close\r\n\r\n";
  request_stream << form;

  boost::asio::write(_ssl_socket, request);

  boost::asio::streambuf response;
  boost::asio::read_until(_ssl_socket, response, "\r\n");
  istream response_stream(&response); // 应答流
  string http_version;
  response_stream >> http_version;
  unsigned int status_code;
  response_stream >> status_code;
  string status_message;
  getline(response_stream, status_message);
  if (!response_stream || http_version.substr(0, 5) != "HTTP/")
  {
    printf("invaliable respond\n");
  }
  if (status_code != 200)
  {
    printf("response returning status code %d\n", status_code);
  }

  boost::asio::read_until(_ssl_socket, response, "\r\n\r\n");

  string header;
  int len = 0;
  while (getline(response_stream, header) && header != "\r")
  {
    if (header.find("Content-Length: ") == 0)
    {
      stringstream stream;
      stream << header.substr(16);
      stream >> len;
    }
  }

  long size = response.size();

  if (size > 0)
  {
    // .... do nothing
  }

  boost::system::error_code error;
  while (boost::asio::read(_ssl_socket, response, boost::asio::transfer_at_least(1), error))
  {
    // 获取应答长度
    size = response.size();
    if (len != 0)
    {
      cout << size << "  Byte  " << (size * 100) / len << "%\n";
    }
  }
  if (error != boost::asio::error::eof)
  {
    throw boost::system::system_error(error);
  }

  cout << size << " Byte download finished." << endl;

  // 将streambuf类型转换为string类型返回
  istream is(&response);
  is.unsetf(ios_base::skipws);
  string sz;
  sz.append(istream_iterator<char>(is), istream_iterator<char>());

  cout << sz << endl;

  // 返回转换后的字符串
  return sz;
}

string asio_request::get_request(const string &host, const string &path, const string &form)
{
  long length = form.length();

  boost::asio::io_service service;

  tcp::resolver resolver(service);
  // tcp::resolver::query query(host.c_str(), "http");
  tcp::resolver::iterator iter = resolver.resolve(host, "80");

  tcp::socket _socket(service);
  boost::asio::connect(_socket, iter);

  boost::asio::streambuf request;
  ostream request_stream(&request);

  request_stream << "GET " << path + "?" + form << " HTTP/1.1\r\n";
  request_stream << "Host: " << host << "\r\n";
  request_stream << "Accept: */*\r\n";
  // request_stream << "Accept-Language: zh-CN,zh-HK;q=0.8,en-US;q=0.5,en;q=0.3\r\n";
  // request_stream << "Upgrade-Insecure-Requests: 1\r\nSec-Fetch-Dest: document\r\nSec-Fetch-Mode: navigate\r\nSec-Fetch-Site: none\r\nSec-Fetch-User: ?1\r\n\r\n";

  // request_stream << "Content-Type:application/json; charset=utf-8\r\n";
  request_stream << "Connection: keep-alive\r\n\r\n";

  boost::asio::write(_socket, request);

  boost::asio::streambuf response;
  boost::asio::read_until(_socket, response, "\r\n");

  istream response_stream(&response); // 应答流
  string http_version;
  response_stream >> http_version;
  unsigned int status_code;
  response_stream >> status_code;
  string status_message;
  getline(response_stream, status_message);
  if (!response_stream || http_version.substr(0, 5) != "HTTP/")
  {
    printf("invaliable respond\n");
  }
  if (status_code != 200)
  {
    printf("response returning status code %d\n", status_code);
  }

  boost::asio::read_until(_socket, response, "\r\n\r\n");

  string header;
  int len = 0;
  while (getline(response_stream, header) && header != "\r")
  {
    if (header.find("Content-Length: ") == 0)
    {
      stringstream stream;
      stream << header.substr(16);
      stream >> len;
    }
  }

  long size = response.size();

  if (size > 0)
  {
    // .... do nothing
  }

  boost::system::error_code error;
  while (boost::asio::read(_socket, response, boost::asio::transfer_at_least(1), error))
  {
    // 获取应答长度
    size = response.size();
    if (len != 0)
    {
      cout << size << "  Byte  " << (size * 100) / len << "%\n";
    }
  }
  if (error != boost::asio::error::eof)
  {
    throw boost::system::system_error(error);
  }

  cout << size << " Byte download finished." << endl;

  // 将streambuf类型转换为string类型返回
  istream is(&response);
  is.unsetf(ios_base::skipws);
  string sz;
  sz.append(istream_iterator<char>(is), istream_iterator<char>());

  cout << sz << endl;

  // 返回转换后的字符串
  return sz;
}

string asio_request::get_https_request(const string &host, const string &path, const string &form)
{
  long length = form.length();

  boost::asio::io_service service;
  tcp::resolver resolver(service);

  boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23_client);
  // ctx.set_default_verify_paths();
  ctx.set_verify_mode(boost::asio::ssl::context::verify_none);
  ssl_socket _ssl_socket(service, ctx);
  auto iter = resolver.resolve(host, "443");

  boost::asio::connect(_ssl_socket.next_layer(), iter.begin(), iter.end());
  _ssl_socket.lowest_layer().set_option(tcp::no_delay(true));

  // _ssl_socket.set_verify_mode(boost::asio::ssl::verify_peer);
  // _ssl_socket.set_verify_callback(boost::asio::ssl::rfc2818_verification(host));
  _ssl_socket.handshake(ssl_socket::client);

  boost::asio::streambuf request;
  ostream request_stream(&request);

  request_stream << "GET " << path + "?" + form << " HTTP/1.1\r\n";
  request_stream << "Host: " << host << "\r\n";
  request_stream << "Accept: */*\r\n";
  // request_stream << "Accept-Language: zh-CN,zh-HK;q=0.8,en-US;q=0.5,en;q=0.3\r\n";
  // request_stream << "Upgrade-Insecure-Requests: 1\r\nSec-Fetch-Dest: document\r\nSec-Fetch-Mode: navigate\r\nSec-Fetch-Site: none\r\nSec-Fetch-User: ?1\r\n\r\n";
  // request_stream << "Accept-Encoding: gzip, deflate, br\r\n";
  request_stream << "Connection: keep-alive\r\n\r\n";

  boost::asio::write(_ssl_socket, request);

  boost::asio::streambuf response;
  boost::asio::read_until(_ssl_socket, response, "\r\n");
  istream response_stream(&response); // 应答流
  string http_version;
  response_stream >> http_version;
  unsigned int status_code;
  response_stream >> status_code;
  string status_message;
  getline(response_stream, status_message);
  if (!response_stream || http_version.substr(0, 5) != "HTTP/")
  {
    printf("invaliable respond\n");
  }
  if (status_code != 200)
  {
    printf("response returning status code %d\n", status_code);
  }

  boost::asio::read_until(_ssl_socket, response, "\r\n\r\n");

  string header;
  int len = 0;
  while (getline(response_stream, header) && header != "\r")
  {
    if (header.find("Content-Length: ") == 0)
    {
      stringstream stream;
      stream << header.substr(16);
      stream >> len;
    }
  }

  long size = response.size();

  if (size > 0)
  {
    // .... do nothing
  }

  boost::system::error_code error;
  while (boost::asio::read(_ssl_socket, response, boost::asio::transfer_at_least(1), error))
  {
    // 获取应答长度
    size = response.size();
    if (len != 0)
    {
      cout << size << "  Byte  " << (size * 100) / len << "%\n";
    }
  }
  if (error != boost::asio::error::eof)
  {
    throw boost::system::system_error(error);
  }

  cout << size << " Byte download finished." << endl;

  // 将streambuf类型转换为string类型返回
  istream is(&response);
  is.unsetf(ios_base::skipws);
  string sz;
  sz.append(istream_iterator<char>(is), istream_iterator<char>());

  cout << sz << endl;

  // 返回转换后的字符串
  return sz;
}
