#include <SPI.h>
#include <MFRC522.h> 
#include <Wire.h>           
#include <LiquidCrystal_I2C.h>   

#define SS_PIN 10
#define RST_PIN 9
#define RED 22
#define GREEN 23
#define BUZZ 8

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
LiquidCrystal_I2C lcd(0x27,20,4);   //I2C Address: 0x27, 20x4 LCD(20 columns x 4 rows)  

String butter = String(000)+" "+String(000)+" "+String(000)+ " "+String(000);
String cheese = String(201)+" "+String(139)+" "+String(204)+ " "+String(177);
String doritos = String(82)+" "+String(85)+" "+String(86)+ " "+String(48);
String watermelon = String(214)+" "+String(169)+" "+String(83)+ " "+String(43);
String milano = String(118)+" "+String(225)+" "+String(86)+ " "+String(43);
int price = 0, head=1, b =1, c= 1, d=1, w=1, m=1;
String uidString;

void setup() {
  Serial.begin(9600);    
  pinMode(RED, OUTPUT);   //initializing red led as output
  pinMode(GREEN, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  lcd.init();      // Init LCD
  lcd.backlight();  
}

void loop() 
{
  if(head==1)
  {
    lcd.setCursor(0,0);  
    lcd.print("       Welcome");  
    lcd.setCursor(0,1);  
    lcd.print("          to"); 
    lcd.setCursor(0,2);  
    lcd.print("     Superstore"); 
    head++;
  }
  if(rfid.PICC_IsNewCardPresent())    //to check if any card is present nearby
  {
      readRFID();
  }
  delay(1000);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BUZZ, LOW);
}

void readRFID()
{
    rfid.PICC_ReadCardSerial();
    Serial.println("============================");
    lcd.clear();  
    uidString = String(rfid.uid.uidByte[0])+" "+String(rfid.uid.uidByte[1])+" "+String(rfid.uid.uidByte[2])+ " "+String(rfid.uid.uidByte[3]);
    boolean butter1 = true, cheese1 = true, doritos1 = true, watermelon1 = true, milano1 = true;
    Serial.println(uidString);    //print rfid uid number on serial monitor
      if(String(uidString) == String(butter))
      {
          butter1 = false;
      }
      else if(String(uidString) == String(cheese))
      {
          cheese1 = false;
      }
      else if(String(uidString) == String(doritos))
      {
          doritos1 = false;
      }
      else if(String(uidString) == String(watermelon))
      {
          watermelon1 = false;
      }
      else if(String(uidString) == String(milano))
      {
          milano1 = false;
      }
    if (butter1 == false)
    {
      if(b%2 == 1)
      {
            Serial.println("200g Butter Added to Cart");
            Serial.println("Rs.: 50");
            lcd.setCursor(0,0);  
            lcd.print("  200g Butter Added");  
            lcd.setCursor(0,1);
            lcd.print("      Rs.: 50");
            price+=50; 
            additem();
      }
       else if (b%2 == 0)
            {
               Serial.println("200g Butter Removed from Cart");
               price-=50;
               lcd.setCursor(0,0);  
               lcd.print("200g Butter Removed");  
               lcd.setCursor(0,1);
               lcd.print("      - Rs.: 50");
               removeitem();
            }
       b++;
    }
    else if(cheese1 == false)
    {
      if(c%2 == 1)
      {
            Serial.println("200g Cheese Added to Cart");
            Serial.println("Rs.: 100");
            lcd.setCursor(0,0);  
            lcd.print("  200g Cheese Added");  
            lcd.setCursor(0,1);
            lcd.print("      Rs.: 100");
            price+=100;
            additem();
      }
      else if (c%2 ==0)
            {
               Serial.println("200g Cheese Removed from Cart");
               price-=100;
               lcd.setCursor(0,0);  
               lcd.print(" 200g Cheese Removed");  
               lcd.setCursor(0,1);
               lcd.print("      - Rs.: 100");
               removeitem();
            }
      c++;
    }
    else if(doritos1 == false)
    {
      if(d%2 == 1)
      {
            Serial.println("Doritos Added to Cart");
            Serial.println("Rs.: 35");
            lcd.setCursor(0,0);  
            lcd.print("    Doritos Added");  
            lcd.setCursor(0,1);
            lcd.print("       Rs.: 35");
            price+=35;
            additem();
      }
      else if (d%2 ==0)
            {
               Serial.println("Doritos Removed from Cart");
               price-=35;
               lcd.setCursor(0,0);  
               lcd.print("   Doritos Removed");  
               lcd.setCursor(0,1);
               lcd.print("      - Rs.: 35");
               removeitem();
            }
      d++;
    }
    else if(watermelon1 == false)
    {
      if(w%2 == 1)
      {
            Serial.println("Watermelon Added to Cart");
            Serial.println("Rs.: 75");
            lcd.setCursor(0,0);  
            lcd.print("  Watermelon Added");  
            lcd.setCursor(0,1);
            lcd.print("      Rs.: 75");
            
            price+=75;
            additem();
      }
      else if (w%2 ==0)
            {
               Serial.println("Watermelon Removed from Cart");
               lcd.setCursor(0,0);  
               lcd.print(" Watermelon Removed");  
               lcd.setCursor(0,1);
               lcd.print("      - Rs.: 75");
               price-=75;
               removeitem();
            }
      w++;
    }
    else if(milano1 == false)
    {
      if(m%2 == 1)
      {
            Serial.println("Milano Added to Cart");
            Serial.println("Rs.: 50");
            price+=50;
            
            lcd.setCursor(0,0);  
            lcd.print("    Milano Added");  
            lcd.setCursor(0,1);
            lcd.print("       Rs.:50");
            additem();
      }
      else if (m%2 ==0)
            {
               Serial.println("Milano Removed from Cart");
               price-=50;
               
              lcd.setCursor(0,0);  
              lcd.print("   Milano Removed");  
              lcd.setCursor(0,1);
              lcd.print("     - Rs.:50");
              removeitem();
            }
      m++;
    }
    else
    {
          Serial.println("\nUnknown Item");
          lcd.clear();
          lcd.setCursor(0,1);  
          lcd.print("====Unknown Item===="); 
    }
    
   Serial.println("==========================");
   lcd.setCursor(0,2);  
   lcd.print("===================="); 
   Serial.print("Bill Total: Rs. ");
   Serial.println(price);
   lcd.setCursor(0,3);  
   lcd.print(" Bill Total: Rs. "); 
   lcd.print(price);
   Serial.println("\n");
   Serial.println("UPI ID.: superstore@oksbi");
   Serial.println("============================");
}

void additem()
{
  digitalWrite(GREEN, LOW);
  digitalWrite(BUZZ, HIGH);
}
void removeitem()
{
    digitalWrite(RED, LOW);
    digitalWrite(BUZZ, HIGH);
    delay(100);
    digitalWrite(BUZZ, LOW);
    delay(100);
    digitalWrite(BUZZ, HIGH);
    delay(100);
    digitalWrite(BUZZ, LOW);
    digitalWrite(RED, HIGH);
}
