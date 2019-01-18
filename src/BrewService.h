#ifndef BrewService_h
#define BrewService_h

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#elif defined(ESP_PLATFORM)
#include <WiFi.h>
#include <AsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <AsyncJson.h>
#include <IPAddress.h>
#include <AsyncJsonRequestWebHandler.h>
#include <AsyncJsonCallbackResponse.h>
#include <TimeLib.h>
#include <NtpClientLib.h>
#include <enum.h>
#include <MashService.h>
#include <BoilService.h>
#include <KettleHeaterService.h>
#include <BrewSettingsService.h>

#define MASH_SETTINGS_FILE "/config/mashSettings.json"
#define START_BREW_SERVICE_PATH "/rest/startbrew"
#define GET_ACTIVE_STEP_SERVICE_PATH "/rest/getactivestep"

class BrewService
{
public:
  BrewService(AsyncWebServer *server,
              FS *fs,
              MashService *mashService,
              BoilService *boilService,
              BrewSettingsService *brewSettingsService,
              KettleHeaterService *kettleHeaterService);

  ~BrewService();

  void loop();

private:
  FS *_fs;
  AsyncWebServer *_server;
  BoilService *_boilService;
  MashService *_mashService;
  BrewSettingsService *_brewSettingsService;
  KettleHeaterService *_kettleHeaterService;

  float _setPoint;

  boolean _brewStarted;
  StepType _activeStep;

  void getActiveStep(AsyncWebServerRequest *request);
  void startBrew(AsyncWebServerRequest *request);
};
#endif