#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Tamagochi";
const char* password = "123nigga";

String htmlContent = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Tamagochi</title>
  <style>
            *,body{
                padding: 0px;
                margin: 0px;
                font-family: sans-serif;
            }

            .canvas{
                background-color: black;
                max-width: 100vw;
                max-height: 100vh;
                min-height: 100vh;
                color: white;
            }
            .text-c{
                text-align: center;
            }
            .cen{
                margin-left: auto;
                margin-right: auto;
            }
            .mt-20{
                margin-top: 20px;
            }


            /* CSS */
            .button-15 {
            background-image: linear-gradient(#42A1EC, #0070C9);
            border: 1px solid #0077CC;
            border-radius: 4px;
            box-sizing: border-box;
            color: #FFFFFF;
            cursor: pointer;
            direction: ltr;
            display: block;
            font-family: "SF Pro Text","SF Pro Icons","AOS Icons","Helvetica Neue",Helvetica,Arial,sans-serif;
            font-size: 17px;
            font-weight: 400;
            letter-spacing: -.022em;
            line-height: 1.47059;
            min-width: 30px;
            overflow: visible;
            padding: 4px 15px;
            text-align: center;
            vertical-align: baseline;
            user-select: none;
            -webkit-user-select: none;
            touch-action: manipulation;
            white-space: nowrap;
            }

            .button-15:disabled {
            cursor: default;
            opacity: .3;
            }

            .button-15:hover {
            background-image: linear-gradient(#51A9EE, #147BCD);
            border-color: #1482D0;
            text-decoration: none;
            }

            .button-15:active {
            background-image: linear-gradient(#3D94D9, #0067B9);
            border-color: #006DBC;
            outline: none;
            }

            .button-15:focus {
            box-shadow: rgba(131, 192, 253, 0.5) 0 0 0 3px;
            outline: none;
            }
    </style>
</head>
<body>
  <div class="canvas">
      <h1 class="text-c">Esp8266 Tamagochi</h1>
        <h2 class="text-c">Hi</h2>
        <h3 class="text-c">Wanna check on ur plant nigga?</h3>

        <h1 class="text-c mt-20">Kelembapan : {PERCENTAGE}</h1>
        <button class="cen mt-20 button-15" onclick="toggleLED()">Siram Tanaman!</button>
    </div>
    <script>
      function toggleLED() {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "/toggleLED", true);
        xhr.send();
      }
  </script>
</body>
</html>
)=====";

ESP8266WebServer server(80);
bool ledState = false;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", htmlContent);
  });

  server.on("/toggleLED", HTTP_GET, []() {
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
    server.send(200, "text/plain", "LED toggled");
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
