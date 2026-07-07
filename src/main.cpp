#include <Arduino.h>
#include <SettingsGyver.h>
#include <GyverDBFile.h>
#include <StringUtils.h>
#include <LittleFS.h>
#include <WiFiConnector.h>
#include <GyverMAX7219.h>
#include <GyverGFX.h>
#include <RunningGFX.h>


MAX7219<4, 1, 5> mtrx;
RunningGFX run(&mtrx);
SettingsGyver settings("My Settings");
GyverDBFile db(&LittleFS, "/data.db");

const char* buttons[] = {
    "Busy",
    "Away",
    "Available",
};


DB_KEYS(
    kk,
    wifi_ssid,
    wifi_pass,
    apply);
String input;
String input_data;

void build(sets::Builder &b)
{
  if (WiFi.status() != WL_CONNECTED)
  {
    {
      sets::Group g(b, "WiFi");
      b.Input(kk::wifi_ssid, "SSID");
      b.Pass(kk::wifi_pass, "Password", "***");

      if (b.Button(kk::apply, "Connect"))
      {
        db.update();
        WiFiConnector.connect(db[kk::wifi_ssid], db[kk::wifi_pass]);
      }
    }
  }
  else
  {
    {
      sets::Group g(b, " ");
      b.Input("", &input_data);
      if (b.Button("Send"))
      {
        run.stop();
        mtrx.clear();
        run.setText(input_data);
        run.start();
      }
    }
    if (b.beginButtons())
    {
      if (b.Button(buttons[0]))
      {
        run.stop();
        mtrx.clear();
        run.setText(buttons[0]);
        run.start();
      }
      if (b.Button(buttons[1]))
      {
        run.stop();
        mtrx.clear();
        run.setText(buttons[1]);
        run.start();
      }
      if (b.Button(buttons[2]))
      {
        run.stop();
        mtrx.clear();
        run.setText(buttons[2]);
        run.start();
      }
      b.endButtons();
    }
  }
}



void setup()
{
  mtrx.begin();
  mtrx.setBright(5);
  run.setSpeed(15);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

#ifdef ESP32
  LittleFS.begin(true);
#else
  LittleFS.begin();
#endif
  db.begin();
  db.init(kk::wifi_ssid, "");
  db.init(kk::wifi_pass, "");

  WiFiConnector.connect(db[kk::wifi_ssid], db[kk::wifi_pass]);
   while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected: ");
    Serial.println(WiFi.localIP());
  settings.begin();
  settings.onBuild(build);
}

void loop()
{
  WiFiConnector.tick();
  settings.tick();
  run.tick();
}