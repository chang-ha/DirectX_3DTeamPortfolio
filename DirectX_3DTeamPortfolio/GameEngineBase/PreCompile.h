#pragma once

#include <WS2tcpip.h> // inet_pton �Լ��� ����ϱ� ���� ���
#include <WinSock2.h> // window.h���� ������ ���ʿ� �־�� �Ѵ�.
#pragma comment (lib, "ws2_32") // <= ������ ���� ����� ���� ���̺귯��


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
