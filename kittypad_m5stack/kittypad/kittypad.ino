#include <M5Stack.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define KEYBOARD_I2C_ADDR     0X88
#define KEYBOARD_INT 5

const char* ssid     = "My-mifi";//Wifi AP SSID
const char* password = "Hackathon";//Wifi AP PASSWORD

void setup() {
   Serial.begin(115200);
//Init M5 stack
  m5.begin();
m5.Lcd.printf("Connecting....");
//connecting to Wifi access point
   WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    m5.Lcd.printf(".");
}

//Connected
  m5.Lcd.printf("Connected !!!");
//Set Screen Level Brightness
  m5.Lcd.setBrightness(100);
//Draw cattroll logo on the screen
   m5.Lcd.drawJpgFile(SD,"/1.jpg");

  //init reading the keypad using interrupt method
   Wire.begin();
    pinMode(KEYBOARD_INT, INPUT_PULLUP);
}

void loop() {

// scanning the input keys
  if(digitalRead(KEYBOARD_INT) == LOW) {
    Wire.requestFrom(KEYBOARD_I2C_ADDR, 1);  // request 1 byte from keyboard
    while (Wire.available()) { 
      uint8_t key_val = Wire.read();                  // receive a byte as character
      if(key_val != 0) {
        if(key_val > 20 && key_val < 0x7F) { // ASCII String
          Serial.print((char)key_val);
          //M5.Lcd.print((char)key_val);
          if((key_val == 'U')||(key_val == 'D')||(key_val == 'L')||(key_val == 'R'))
          {
	//Init HTTP client
            HTTPClient http;   
            String  commandUrl("http://159c65e6.ngrok.io/action/1/");//Python server address
            if(key_val == 'U')
            {
              commandUrl += "up";
            }
            else if(key_val == 'D')
            {
              commandUrl += "down";
            }
            else if(key_val == 'L')
            {
              commandUrl += "left";
            }
            else
              commandUrl += "right";

              http.begin(commandUrl);  //Specify destination for HTTP request
              //http.addHeader("Content-Type", "text/plain"); 
              int httpResponseCode = http.POST("h");   //Send the actual POST request
              Serial.println(commandUrl);
              if(httpResponseCode>0)
              {
                String response = http.getString();                       //Get the response to the request
                Serial.println(httpResponseCode);   //Print return code
                Serial.println(response);           //Print request answer
              }
              else
              {
                Serial.print("Error on sending POST: ");
                Serial.println(httpResponseCode);
              }
              http.end(); 
          }
        } else {
//Log the key code for debugging
          Serial.printf("0x%02X ",key_val);
        }
      }
    }
}

}
