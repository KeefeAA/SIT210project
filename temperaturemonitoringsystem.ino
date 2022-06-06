TCPClient client; // Declare the ThingSpeak client

// Using the ThingSpeak library 
#include "ThingSpeak.h"

// Using DHT library for the DHT22 sensor
#include "Adafruit_DHT.h"

const pin_t RED_LED = D5; // Set Red LED to D5 
const pin_t GREEN_LED = D7; // Set Green LED to D7

int channelID = 1757324; // Thingspeak Channel ID	 

const char * writeAPIKey = "4QM0AFDTNTY7H6TV"; // Write API Key

const int buzzer = A5; // Set buzzer to pin A5

DHT dht(D3, DHT22); // Set DHT to pin D3

int i = 0; // Initialise counter for while loop 

void setup() {
    ThingSpeak.begin(client); // Initialise ThingSpeak client 
    dht.begin(); // Initialise DHT sensor
    
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(buzzer, OUTPUT);
}

void loop() {
    float temperature = dht.getTempCelcius(); // Read temperature as Celsius
    
    if(temperature < 25)
    {
        //Turns on green led if temperature is less than 25 degrees Celcius
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
    }
    
    else
    {
        // Turn off green LED and turn on red LED
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(RED_LED, HIGH);
        
        while(i<=5)
        {
            // The buzzer will buzz for 1 second, 5 times
            tone(buzzer,1000);
            delay(1000);
            noTone(buzzer);
            delay(1000);
            i++;
        }
    }
    
    // Sending data to ThingSpeak
    ThingSpeak.writeField(channelID, 1, temperature, writeAPIKey);
    delay(15000); 
}