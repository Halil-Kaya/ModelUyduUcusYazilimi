#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // I2C Interface



// Connect the GPS Power pin to 5V
// Connect the GPS Ground pin to ground
// Connect the GPS TX (transmit) pin to Digital 8
// Connect the GPS RX (receive) pin to Digital 7

SoftwareSerial mySerial(8, 7);
Adafruit_GPS GPS(&mySerial);
#define GPSECHO  true
#define HOUR_OFFSET +3

float ilkBasinc = 0;
void setup()
{
  Serial.begin(115200);
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_10HZ);   
  GPS.sendCommand(PGCMD_ANTENNA);

  delay(1000);
  //enableGPSInterrupt();



  Serial.println(F("BMP280 test"));

  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); 

  for(int i =0;i<5;i++){
    ilkBasinc = bmp.readPressure()/100;
  }

  ilkBasinc = 0;


  for(int i =0;i<10;i++){
    ilkBasinc += bmp.readPressure()/100; 
  }

  ilkBasinc = ilkBasinc/10;

  
  
    


}

uint32_t timer = millis();
void loop()                     // run over and over again
{ 
 GPSSensoru();
 
}
void BMP280Sensoru(){

   Serial.println("sicaklik: "+String(bmp.readTemperature()));    
   Serial.println("Basinc: "+String(bmp.readPressure()/100));
   Serial.println("Yukseklik: "+String(bmp.readAltitude(ilkBasinc)));
 
}

void GPSSensoru(){

   char c = GPS.read();
  if ((c) && (GPSECHO))
    
  if (GPS.newNMEAreceived()) {

    if (!GPS.parse(GPS.lastNMEA()))  
      return;  
  }


  if (millis() - timer > 150) {

  timer = millis(); 
  
  String GpsTime = String(GPS.hour+HOUR_OFFSET) + ":" + GPS.minute + ":" + GPS.seconds ;
  String GpsDate = String(GPS.day) + "/"+GPS.month+"/"+GPS.year;
  String LatitudeValue = String(GPS.latitude);
  String LongitudeValue = String(GPS.longitude);

  String Latitude = String(LatitudeValue[0]) + LatitudeValue[1];
  String Longitude = String(LongitudeValue[0]) + LongitudeValue[1];
  String LatitudeMark;
  String LotitudeMark;

  if(GPS.lat == 'N'){
    LatitudeMark = 'N';
  }else if(GPS.lat == 'E'){    
    LatitudeMark = 'E';
  }else if(GPS.lat == 'S'){    
    LatitudeMark = 'S';
  }else if(GPS.lat == 'W'){    
    LatitudeMark = 'W';
  }

   if(GPS.lon == 'N'){
    LotitudeMark = 'N';
  }else if(GPS.lon == 'E'){    
    LotitudeMark = 'E';
  }else if(GPS.lon == 'S'){    
    LotitudeMark = 'S';
  }else if(GPS.lon == 'W'){    
    LotitudeMark = 'W';
  }
  

  if(GPS.lat == 'N' || GPS.lat == 'E'){
    Latitude = "+" + Latitude;
  }else{
    Latitude = "-" + Latitude;  
  }


  

  if(GPS.lon == 'N' || GPS.lon == 'E'){
    Longitude = "+" + Longitude;
  }else{
    Longitude = "-" + Longitude;  
  }


  String LatitudeCordinat = "";
  String LongitudeCordinat = "";

   for(int i=2 ; i<LatitudeValue.length() ; i++){
    
     LatitudeCordinat = LatitudeCordinat + LatitudeValue[i]; 
     
   }

     for(int i=2 ; i<LongitudeValue.length() ; i++){
    
     LongitudeCordinat = LongitudeCordinat + LongitudeValue[i]; 
     
   }

  String GpSspeed = String(GPS.speed);
  String GpsAltitude = String(GPS.altitude);
  String GpsAngle = String(GPS.angle);
  
  
  Serial.println("Time: "+GpsTime);
  Serial.println("Date: "+GpsDate);
  Serial.println("Gps.latitude: "+Latitude);
  Serial.println("GPS.longitude: "+Longitude);
  Serial.println("LatitudeCordinat: "+LatitudeCordinat);
  Serial.println("LongitudeCordinat: "+LongitudeCordinat);
  Serial.println("speed: "+GpSspeed);
  Serial.println("GpsAltitude: "+GpsAltitude);
  Serial.println("GpsAngle: "+GpsAngle);
  Serial.println("Lat: "+LatitudeMark);
  Serial.println("Lon: "+LotitudeMark);
  BMP280Sensoru();
  
  
  }
  
}


SIGNAL(TIMER0_COMPA_vect) {
  // Use a timer interrupt once a millisecond to check for new GPS data.
  // This piggybacks on Arduino's internal clock timer for the millis()
  // function.
  GPS.read();
}

void enableGPSInterrupt() {
  // Function to enable the timer interrupt that will parse GPS data.
  // Timer0 is already used for millis() - we'll just interrupt somewhere
  // in the middle and call the "Compare A" function above
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
}
