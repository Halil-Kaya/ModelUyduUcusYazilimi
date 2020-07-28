
void setup() {

  Serial.begin(9600);

  /*
   * 4101.4125N,2856.1179E location olarak böyle bir data geliyor
   * bu datayı kullanım şekli şöyle; N ve E +, W ve S -
   * 
   * öncelikle ilk değerin ilk iki basamağı longitude, 2. değerin ilk iki basamağı latitude
   * öncelikle bunları ayırmam lazım ondan sonra sondaki kelimeye göre başına + veya - değeri yerleştirmem lazım
   * 
   * konumumuzu bulmak için olması gereke data +41 01.4125N, +28 56.1179E
  */  

  //Not: burda dikkatli olmam gereken bir olaya var. eğer konum 0101.4125N,0856.1179E şekilde geldi diyelim.
  //longitude va latidu 01,08 olarak değil 10,85 olarak almam lazım
  //yani sonuc +10 1.4125N, +85 6.1179E olarak almam lazım
  
 
  /*
  Gpste kullandığımız fonksiyonlar ve bize döndürdüğü değerler
  Gps.latitude: 4102.81
  GPS.lat: N
  GPS.longitude: 2856.58
  GPS.lon: E
  */

  String LatitudeValue = "4102.81";
  String LongitudeValue = "2856.58";

  String Latitude = String(LatitudeValue[0]) + LatitudeValue[1];
  String Longitude = String(LongitudeValue[0]) + LongitudeValue[1];

  String LatitudeCordinat = "";
  String LongitudeCordinat = "";

   for(int i=2 ; i<LatitudeValue.length() ; i++){
    
     LatitudeCordinat = LatitudeCordinat + LatitudeValue[i]; 
     
   }

     for(int i=2 ; i<LongitudeValue.length() ; i++){
    
     LongitudeCordinat = LongitudeCordinat + LongitudeValue[i]; 
     
   }
  
  Serial.println("Latitude: " + String(Latitude));
  Serial.println("Longitude: " + String(Longitude));

  
  Serial.println("LatitudeCordinat: " + String(LatitudeCordinat));
  Serial.println("LongitudeCordinat: " + String(LongitudeCordinat));

  
}



void loop() {
  
}
