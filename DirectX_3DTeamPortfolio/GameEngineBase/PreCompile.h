#pragma once

#include <WS2tcpip.h> // inet_pton 함수를 사용하기 위한 헤더
#include <WinSock2.h> // window.h보다 무조건 위쪽에 있어야 한다.
#pragma comment (lib, "ws2_32") // <= 윈도우 서버 사용을 위한 라이브러리


#include <Windows.h>
#include <string>
#include <string_view> // C++ 
#include <functional>
#include <memory>

#include <map>
#include <list>
#include <set>
#include <vector>
#include <chrono>
#include <mutex>
