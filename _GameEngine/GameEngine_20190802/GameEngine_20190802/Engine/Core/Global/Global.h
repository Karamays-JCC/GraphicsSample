#pragma once
#include <cstdio>
#include <cstring>

//STL I/O 
#include <iostream>
#include <sstream>
#include <istream>
#include <ostream>

//STL Container
#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

#include <stack>
#include <queue>

//STL Other
#include <memory>
#include <string>
#include <chrono>
#include <regex>

//Customer Definition
#include "Public/WinSock.h"
#include "Public/OpenGL.h"
#include "Public/Assimp.h"
#include "Public/Nlohmann.h"

//Global Var
#include <Engine/Engine.h>
#include <Callback/CallbackList/UCallbackList.h>

extern class UCallbackList GlobalCallbackList;
extern std::shared_ptr<class Engine> GEngine;

