/* ------------------------------------------------- */

#pragma once

#ifndef ESPTelnetDbg_h
#define ESPTelnetDbg_h

/* ------------------------------------------------- */

#if defined(ARDUINO_ARCH_ESP32)
  #include <WiFi.h>
  #include <WebServer.h>
#elif defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266WebServer.h>
#endif

/* ------------------------------------------------- */

class ESPTelnetDbg {
  typedef void (*CallbackFunction) (String str);

  public:
    ESPTelnetDbg();

    bool begin();
    void loop();
    void stop();

    void print(String str);
    void print(char c);
    void println(String str);
    void println(char c);
    void println();

    String getIP() const;
    String getLastAttemptIP() const;
    
    void onConnect(CallbackFunction f);
    void onConnectionAttempt(CallbackFunction f);
    void onReconnect(CallbackFunction f);
    void onDisconnect(CallbackFunction f);
    void onInputReceived(CallbackFunction f);
    
  protected:
    WiFiServer server = WiFiServer(23);
    WiFiClient client;
    boolean isConnected = false;
    String ip = "";
    String attemptIp;
    String input = "";

    bool isClientConnected(WiFiClient client);

    CallbackFunction on_connect = NULL;
    CallbackFunction on_reconnect  = NULL;
    CallbackFunction on_disconnect = NULL;
    CallbackFunction on_connection_attempt = NULL;
    CallbackFunction on_input  = NULL;
};

/* ------------------------------------------------- */

  // << operator
  template<class T> inline ESPTelnetDbg &operator <<(ESPTelnetDbg &obj, T arg) { obj.print(arg); return obj; } 

/* ------------------------------------------------- */
#endif
/* ------------------------------------------------- */