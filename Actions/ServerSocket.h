// Definition of the ServerSocket class

#ifndef ServerSocket_class
#define ServerSocket_class

#include "Socket.h"


class ServerSocket : private Socket
{
 public:

  ServerSocket ( int port );
  ServerSocket (){};
  virtual ~ServerSocket();

  const ServerSocket& operator << ( const int[2] ) const;
  const ServerSocket& operator >> ( int[2] ) const;

  void accept ( ServerSocket& );

};


#endif
