#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_NeoPixel.h>

#define ONE_WIRE_BUS 7  // Pin waar de sensor DS18B20 is verbonden
#define NUMPIXELS 30    // Aantal LEDs op de strip

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, 2, NEO_GRB + NEO_KHZ800);

const int pinLedBlauw = 2;       // Pin voor blauwe kleur
const int pinLedGroen = 4;       // Pin voor groene kleur
const int pinLedRood = 8;        // Pin voor rode kleur

void setup() {
  strip.begin();
  strip.show();  // Zet alle LEDs uit

  Serial.begin(115200);
  sensors.begin();
  pinMode(pinLedBlauw, OUTPUT);
  pinMode(pinLedGroen, OUTPUT);
  pinMode(pinLedRood, OUTPUT);
}

void loop() {
  delay(2000); // Wacht even tussen metingen

  sensors.requestTemperatures(); // Vraag de temperatuur op bij DS18B20
  float temperatuur = sensors.getTempCByIndex(0);

  if (temperatuur == -127.00) {
    Serial.println("Fout bij het lezen van de temperatuur. Controleer de verbindingen en de pull-up weerstand.");
    return;
  }

  char tempStr[6]; // Buffer om de temperatuur als string op te slaan
  dtostrf(temperatuur, 4, 2, tempStr); // Converteer float naar string met twee decimalen

  Serial.print("Temperatuur: ");
  Serial.print(tempStr);
  Serial.println(" °C");

  // Zet alle LEDs uit
  digitalWrite(pinLedBlauw, LOW);
  digitalWrite(pinLedGroen, LOW);
  digitalWrite(pinLedRood, LOW);

  // Activeer de blauwe LED (pin 2) onder de 25 graden
  if (temperatuur < 25) {
    digitalWrite(pinLedRood, HIGH);
    digitalWrite(pinLedGroen, HIGH);
  }
  // Activeer de groene LED (pin 4) tussen 25 en 28 graden
  else if (temperatuur >= 25 && temperatuur < 28) {
    digitalWrite(pinLedRood, HIGH);
    digitalWrite(pinLedBlauw, HIGH);
  }
  // Activeer de rode LED (pin 8) boven de 28 graden
  else {
    digitalWrite(pinLedGroen, HIGH);
    digitalWrite(pinLedBlauw, HIGH);
  }
  
  // Werk de kleur van de LED-strip bij op basis van de temperatuur
  colorTemperature(temperatuur);
}

// Functie om de temperatuur te vertalen naar een kleur en de LED-strip bij te werken
void colorTemperature(float temperature) {
  // Als je de kleur van de strip wilt aanpassen op basis van de temperatuur, kun je dat hier doen
  // Voorlopig schakelt de code alleen de blauwe, groene of rode LED in op basis van de temperatuur
}

// Functie om de LED-strip in te stellen op één kleur
void fillStripColor(uint32_t color) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}
