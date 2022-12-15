#ifndef M_NET_BASE_H
#define M_NET_BASE_H

#define WEB_MOUNT_POINT "/www"

class HttpServer;

extern HttpServer* httpServer;

void netBaseInit ();

#endif