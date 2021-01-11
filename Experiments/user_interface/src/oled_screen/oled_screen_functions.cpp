/*******************************************************************************
* OLED Screen Library
*
* File name:    oled_screen.cpp
*
*
*
*******************************************************************************/

#include <sstream>
#include <string.h>
using namespace std;

// Local Libraries
#include "oled_screen_class.h"

// Call U8G2 Constructor
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

//---------------------------------
// OLED Screen Setup Function (One Time Call At Startup)
//---------------------------------
void oled_screen_class::oled_setup()
{
    u8g2.begin();

    //main_menu();//draw_bitmap(0, 0, main_menu_bmp, SCREEN_WIDTH, SCREEN_HEIGHT);    // Draw a bitmap image
};



//---------------------------------
// Function to draw a specified bitmap onto screen, offset by x_pos, y_pos, with a width of w and height of h
//---------------------------------
void oled_screen_class::draw_bitmap(uint8_t x_pos, uint8_t y_pos, const uint8_t *bitmap, uint8_t w, uint8_t h)
{
    u8g2.clearBuffer();         // clear the internal memory

    // drawbitmap(Width Center Point, Height Center Point, bit map height/8, bit map width, bit map array)
    u8g2.drawBitmap(x_pos,y_pos,w/4,h,bitmap);
    u8g2.sendBuffer();          // transfer internal memory to the display
    wait(1000);
}


//---------------------------------
// Function to wait a specified delay, in milliseconds
//---------------------------------
void oled_screen_class::wait(long delay)
{
    unsigned long currentMillis = millis();
    previousMillis = currentMillis;
    
    while(currentMillis - previousMillis < delay) {
        currentMillis = millis();
    }
}



//---------------------------------
// Function to write an input string to the display
//---------------------------------
void oled_screen_class::print_text(char str[], int textSize=2)
{
    #define charsPerLine 20 // Number of characters (textsize = 1) that fit on a line
    //int TextSize = 2;
    
    int currentPosition = 0;
    int currentLine = 0;

    u8g2.clearBuffer();         // clear the internal memory

    // Skipping multi-line support for now...
    u8g2.drawStr(0, 0, str);
    /*for ( int i = 0 ; i < strlen(str); i++)
    {
        if(str[i] == '\\' && str[i+1]=='n'){
            currentPosition = 0;
            currentLine += textSize;
            //display.setCursor(currentPosition,currentLine);
            i++;
        }
        else if(currentPosition+textSize >= charsPerLine){
            currentPosition = 0;
            currentLine += textSize;
            //display.setCursor(currentPosition,currentLine);
        }
        else{
          u8g2.drawStr(currentPosition, currentLine, str[i]);
          u8g2.sendBuffer();
          //display.print(str[i]);
          //display.display();
          wait(10);
        }
    }*/
}



//---------------------------------
// Function to display the score
//---------------------------------
void oled_screen_class::display_score() {
    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font

    u8g2.drawStr(0,10,"Score = ");  // write something to the internal memory
    std::string s = std::to_string(score);
    char const *pchar = s.c_str();  //use char const* as target typ
    u8g2.drawStr(8,10,pchar);  // write something to the internal memory

    u8g2.sendBuffer();          // transfer internal memory to the display
}



//---------------------------------
// Function to update the current score and display the new score
//---------------------------------
void oled_screen_class::update_score(int newScore) {
    score = newScore;
    display_score();
}



//---------------------------------
// Function to play animation
//---------------------------------
void oled_screen_class::lightShow() {
    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    u8g2.drawStr(0,10,"LightShow!!...");  // write something to the internal memory
    u8g2.sendBuffer();          // transfer internal memory to the display
/*  int16_t i;

  display.clearDisplay(); // Clear display buffer

  for(i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1);
    display.display(); // Update screen with each newly-drawn line
    wait(1);
  }
  for(i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i);
    display.display();
    wait(1);
  }
  wait(250);

  display.clearDisplay();

  for(i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0);
    display.display();
    wait(1);
  }
  for(i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i);
    display.display();
    wait(1);
  }
  wait(250);

  display.clearDisplay();

  for(i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0);
    display.display();
    wait(1);
  }
  for(i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i);
    display.display();
    wait(1);
  }
  wait(250);

  display.clearDisplay();

  for(i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i);
    display.display();
    wait(1);
  }
  for(i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1);
    display.display();
    wait(1);
  }*/
}



//---------------------------------
// Function to display "Victory" animation
//---------------------------------
void oled_screen_class::victory()
{
    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    u8g2.drawStr(0,10,"VICTORY!!!...");  // write something to the internal memory
    u8g2.sendBuffer();          // transfer internal memory to the display

/*    // Display a scrolling "VICTORY!"
    display.clearDisplay();
    
    //display.setTextSize(2); // Draw 2X-scale text
    //display.setTextColor(WHITE);
    //display.setCursor(40, 00);
    print_text((char*)" VICTORY!");
    //display.display();
    display.startscrolldiagright(0x00, 0x07);
    wait(8000);
    display.stopscroll();
    wait(2000);

    // Light Show
    lightShow();*/
}



//---------------------------------
// Function shortcuts to display various screens
//---------------------------------

void oled_screen_class::menu_start()
{
    draw_bitmap(0, 0, menu_start_bmp, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void oled_screen_class::start_back()
{
    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    u8g2.drawStr(0,10,"Place robot on line");  // write something to the internal memory

    u8g2.drawBitmap(0, SCREEN_HEIGHT/2, (SCREEN_WIDTH/2)/4, SCREEN_HEIGHT/2, back_selected_bmp);
    u8g2.drawBitmap(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, (SCREEN_WIDTH/2)/4, SCREEN_HEIGHT/2, start_bmp);
    u8g2.sendBuffer();          // transfer internal memory to the display
}

void oled_screen_class::start_start()
{
    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    u8g2.drawStr(0,10,"Place robot on line");  // write something to the internal memory
    u8g2.sendBuffer();          // transfer internal memory to the display

    u8g2.drawBitmap(0, SCREEN_HEIGHT/2, (SCREEN_WIDTH/2)/4, SCREEN_HEIGHT/2, back_bmp);
    u8g2.drawBitmap(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, (SCREEN_WIDTH/2)/4, SCREEN_HEIGHT/2, start_selected_bmp);
    u8g2.sendBuffer();          // transfer internal memory to the display
}

void oled_screen_class::countdown()
{
    print_text((char*)"\n  5", 4);
    wait(1000);
    print_text((char*)"\n  4", 4);
    wait(1000);
    print_text((char*)"\n  3", 4);
    wait(1000);
    print_text((char*)"\n  2", 4);
    wait(1000);
    print_text((char*)"\n  1", 4);
    wait(1000);
    eyes_open();
}

void oled_screen_class::menu_guide()
{
    draw_bitmap(0, 0, menu_guide_bmp, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void oled_screen_class::guide()
{
    draw_bitmap(0, 0, guide_bmp, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void oled_screen_class::menu_score()
{
    draw_bitmap(0, 0, menu_score_bmp, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void oled_screen_class::score_back()
{
    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    u8g2.drawStr(0,10,"Last Score = ");  // write something to the internal memory
    u8g2.sendBuffer();          // transfer internal memory to the display

    std::string s = std::to_string(score);
    char const *pchar = s.c_str();  //use char const* as target typ
    u8g2.drawStr(8,10,pchar);  // write something to the internal memory

    u8g2.drawBitmap(0, SCREEN_HEIGHT/2, (SCREEN_WIDTH/2)/4, SCREEN_HEIGHT/2, back_selected_bmp);
    u8g2.sendBuffer();          // transfer internal memory to the display
}

void oled_screen_class::menu_cal()
{
    draw_bitmap(0, 0, menu_cal_bmp, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void oled_screen_class::cal_back()
{
    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    u8g2.drawStr(0,10,"Calibrate?");  // write something to the internal memory

    u8g2.drawBitmap(0, SCREEN_HEIGHT/2, (SCREEN_WIDTH/2)/4, SCREEN_HEIGHT/2, back_selected_bmp);
    u8g2.drawBitmap(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, (SCREEN_WIDTH/2)/4, SCREEN_HEIGHT/2, start_bmp);
    u8g2.sendBuffer();          // transfer internal memory to the display
}

void oled_screen_class::cal_start()
{
    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    u8g2.drawStr(0,10,"Calibrate?");  // write something to the internal memory

    u8g2.drawBitmap(0, SCREEN_HEIGHT/2, (SCREEN_WIDTH/2)/4, SCREEN_HEIGHT/2, back_bmp);
    u8g2.drawBitmap(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, (SCREEN_WIDTH/2)/4, SCREEN_HEIGHT/2, start_selected_bmp);
    u8g2.sendBuffer();          // transfer internal memory to the display
}

void oled_screen_class::calibrate()
{
    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    u8g2.drawStr(0,10,"Calibrate");  // write something to the internal memory
    u8g2.sendBuffer();          // transfer internal memory to the display
    wait(1000);

    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    u8g2.drawStr(0,10,"Calibrate");  // write something to the internal memory
    u8g2.drawStr(0,20,".");  // write something to the internal memory
    u8g2.sendBuffer();          // transfer internal memory to the display
    wait(1000);

    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    u8g2.drawStr(0,10,"Calibrate");  // write something to the internal memory
    u8g2.drawStr(0,20,"..");  // write something to the internal memory
    u8g2.sendBuffer();          // transfer internal memory to the display
    wait(1000);

    eyes_resting();
    eyes_open();
    eyes_happy();
}


void oled_screen_class::eyes_happy()
{
    draw_bitmap(0, 0, eyes_happy_bmp, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void oled_screen_class::eyes_happy_2()
{
    draw_bitmap(0, 0, eyes_happy_2_bmp, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void oled_screen_class::eyes_open()
{
    draw_bitmap(0, 0, eyes_open_bmp, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void oled_screen_class::eyes_open_2()
{
    draw_bitmap(0, 0, eyes_open_2_bmp, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void oled_screen_class::eyes_resting()
{
    draw_bitmap(0, 0, eyes_resting_bmp, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void oled_screen_class::eyes_resting_2()
{
    draw_bitmap(0, 0, eyes_resting_2_bmp, SCREEN_WIDTH, SCREEN_HEIGHT);
}

/*void oled_screen_class::main_menu_guide_selected()
{
    u8g2.drawBitmap(0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, guide_button_bmp);
    u8g2.drawBitmap(SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, score_button_bmp);
    u8g2.drawBitmap(0, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, start_button_bmp);
    u8g2.drawBitmap(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, more_button_bmp);
    u8g2.sendBuffer();          // transfer internal memory to the display
    wait(1000);
}*/
