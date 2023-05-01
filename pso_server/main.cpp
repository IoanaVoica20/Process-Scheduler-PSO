#include <iostream>
#include "server.h"

int main()
{
  Server& srv = Server::getInstance();
  srv.StartServer();
}

//export LD_PRELOAD=$LD_PRELOAD:/home/ioana/parce/lib_parce.so