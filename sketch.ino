#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2        
#define DHTTYPE DHT22   

#define BUZZER_PIN 8     
#define TEMPERATURE_THRESHOLD 30  

LiquidCrystal_I2C lcd(0x27, 20, 4);  
DHT dht(DHTPIN, DHTTYPE);  

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);  
  Serial.begin(9600);          
  lcd.init();                   
  lcd.backlight();              
  dht.begin();                  

 
  lcd.setCursor(0, 1);
  lcd.print("Monitoring...");

  
  lcd.setCursor(0, 0);
  printTypingEffect("Suhu", 200);
  delay(2000);  

  
  lcd.setCursor(0, 0);  
  lcd.print(" "); 
  printTypingEffect("Kelembaban", 200);
  delay(1000);  

  // Menampilkan 
  lcd.setCursor(0, 1);  
  lcd.print("Monitoring...");  
}

void loop() {
  
  float temperature = dht.readTemperature();  
  float humidity = dht.readHumidity();  


  if (isnan(temperature) || isnan(humidity)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gagal membaca");
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print("SUHU: ");
  lcd.print(temperature);
  lcd.print(" C");

  
  lcd.setCursor(0, 1);  
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");


  if (temperature > TEMPERATURE_THRESHOLD) {
    digitalWrite(BUZZER_PIN, HIGH);  
  } else {
    digitalWrite(BUZZER_PIN, LOW);   
  }

  delay(2000);  
}


void printTypingEffect(String text, int delayTime) {
  for (int i = 0; i < text.length(); i++) {
    lcd.print(text[i]); 
    delay(delayTime);    
  }
}
