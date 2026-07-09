#include <Arduino.h>
#include <SettingsGyver.h>
#include <GyverDBFile.h>
#include <StringUtils.h>
#include <LittleFS.h>
#include <WiFiConnector.h>
#include <GyverMAX7219.h>
#include <GyverGFX.h>
#include <RunningGFX.h>

MAX7219<4, 1, 5> mtrx; // 4 matrices, 1 row
RunningGFX run(&mtrx);
SettingsGyver settings("My Settings");
GyverDBFile db(&LittleFS, "/data.db");

const char *buttons[] = {
    "Busy",
    "Away",
    "Available",
};

DB_KEYS(
    kk,
    wifi_ssid,
    wifi_pass,
    apply);

String input_data;
byte bright = 5; //Default brightness value

void print_text(const char *text) // Display text on matrix with scrolling
{
  run.stop();
  mtrx.clear();
  run.setText(text);
  run.start();
}

void build(sets::Builder &b)
{
  if (WiFi.status() != WL_CONNECTED) // Show WiFi settings if not connected
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
        static String send_data;
        send_data = input_data;
        run.stop();
        mtrx.clear();
        mtrx.update();
        run.setText(send_data);
        run.start();
      }
    }
    // Quick status buttons
    if (b.beginButtons())
    {
      if (b.Button(buttons[0]))
      {
        print_text(buttons[0]);
      }
      if (b.Button(buttons[1]))
      {
        print_text(buttons[1]);
      }
      if (b.Button(buttons[2]))
      {
        print_text(buttons[2]);
      }
      b.endButtons();
    }
    if (b.Button("Clear"))
    {
      run.stop();
      mtrx.clear();
      mtrx.update();
    }
    {
      sets::Group g(b, "Settings");
      if(b.Slider("Bright", 0, 15, 1, "", &bright)){
        mtrx.setBright(bright);

      }
    }
  }
}

void setup()
{
  mtrx.begin();
  mtrx.setBright(bright);
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
  while (WiFi.status() != WL_CONNECTED)
  {
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