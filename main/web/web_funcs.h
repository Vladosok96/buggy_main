#pragma once
#include <string>
#include "esp_http_server.h"

std::string webSystemJson();
void webSystemSet(httpd_req_t *req);
