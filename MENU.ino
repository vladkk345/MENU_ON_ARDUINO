// Include libraries
#include <GyverOLED.h> 
#include <GyverButton.h>

#define ITEMS 16 // Quantity items in menu

GButton down(4, HIGH_PULL, NORM_OPEN); // Button down
GButton up(5, HIGH_PULL, NORM_OPEN); // Button up
GButton ok(6, HIGH_PULL, NORM_OPEN); // Button OK

GyverOLED<SSD1306_128x64, OLED_BUFFER> oled; // Creating object with name oled

uint8_t data[ITEMS]; // Declaration array, which contain data on 16 items menu
bool flag = true; // Flag change state

// Inicialization and setting parameters display
void setup() {
  delay(50);
  oled.init();
  oled.setContrast(255); 
}

void loop(void) { 
  static uint8_t pointer = 0; // Declaration pointer of item menu 
  // Declaration show strings on display
  String str_one = "Parameter."; 
  String str_two = ":";

  // Handle push buttons
  down.tick();
  up.tick();
  ok.tick();

  if(down.isClick() or down.isHold()) // If button down push or hold
  {
      if(flag) // If flag set, then move pointer on 1 position down
      {
          pointer = constrain(pointer + 1, 0, ITEMS - 1); // constrain at items menu (before 16 items)
      }
      else // Else increase counter data
      {  
        data[pointer]++;      
      }   
  }

  if(up.isClick() or up.isHold()) // If button up push or hold
  {
     if(flag) // If flag set, then move pointer on 1 position up
     {
         pointer = constrain(pointer - 1, 0, ITEMS - 1); 
     }
     else // Else decrease counter data
     {      
        data[pointer]--;              
     }
  }
  
  if(ok.isClick()) // If push button OK
  {
     flag = !flag;  // Invert state flag
  }
  
  oled.clear(); // Clear display
  oled.home(); // Return to begin of display (zero position)
  
  if(pointer < 8)
  { 
    // Loop for show first 8 items menu
     for(uint8_t i = 0; i < 8;i++) 
     {
       oled.setCursor(8,i); // Set cursor on the beginning strings
       oled.println(str_one + i + str_two); // Showing strings (names of items menu) with numbers
       oled.setCursor(85,i); // Set cursor on the end strings
       oled.print(data[i]); // Print data
     } 
  }
  
  if(pointer >= 8)
  {
    // Loop for show rest 8 items menu
     for(uint8_t i = 0; i < 8;i++)
     {
       oled.setCursor(8,i); 
       oled.println(str_one + (i+8) + str_two); 
       oled.setCursor(85,i); 
       oled.print(data[i+8]); 
     } 
  } 
  PrintPointer(pointer); // Call function print pointer
  oled.update(); // Update display
}

// Function print pointer
void PrintPointer(uint8_t ptr)
{
    if(ptr >= 8) // If pointer more or equal 8
    {
      if(flag) // If flag set
      {
        oled.setCursor(0, ptr-8); // Set cursor on position 0 and (number pointer - 8)
        oled.print(">"); // Print icon pointer
      }
      else 
      {
        oled.setCursor(120, ptr-8); // Set cursor on position 120 and (number pointer - 8)
        oled.print("<"); // Print icon pointer
      }
    } 
    else 
    {
      if(flag) // If flag also set
      {
        oled.setCursor(0, ptr); // Set cursor on position 0 and number pointer
        oled.print(">"); // Print icon pointer
      }
      else
      {
        oled.setCursor(120, ptr); // Set cursor on position 120 and number pointer
        oled.print("<"); // Print icon pointer
      }
    }
}
