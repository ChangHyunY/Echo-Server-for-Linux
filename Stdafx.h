#ifndef STDAFX_H
#define STDAFX_H

using namespace std;

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <queue>

#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

#include "Protocol.h"

const int MAX_SESSION_COUNT = 100;

#endif
