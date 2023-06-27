#include <Adafruit_NeoPixel.h>
//__________    __________  
//|    4    |  |    11   |
//|3       5|  |10     12|
//|         |  |         |
//|----6----|  |---13----|
//|         |  |         |
//|2       7|  |9      14|
//|____1____|  |____8____| 

// Single Digit
char zeroSegments[] = {1,2,3,4,5,7};
char oneSegments[] = {5,7};
char twoSegments[] = {4,5,6,2,1};
char threeSegments[] = {4,5,6,7,1};
char fourSegments[] = {3,6,5,7};
char fiveSegments[] = {4,3,6,7,1};
char sixSegments[] = {4,3,6,7,2,1};
char sevenSegments[] = {4,5,7};
char eightSegments[] = {1,2,3,4,5,6,7};
char nineSegments[] = {3,4,5,6,7,1};

#define TEAM_1 0
#define TEAM_2 1

typedef enum{
  WHITE,
  YELLOW,
  GREEN,
  BLUE,
  RED
}team_color_t;

team_color_t team_colors[2] = {RED,BLUE};
bool team_color_select_mode_active[2] = {false,false};
Timers T1_flash_timer(250), T2_flash_timer(250);
bool t1_flash_on = false, t2_flash_on = false;

#define COLOR_WHITE 255,255,255
#define COLOR_YELLOW 255,255,0
#define COLOR_GREEN 0,255,0
#define COLOR_BLUE 0,0,255
#define COLOR_RED 255,0,0
#define COLOR_OFF 0,0,0

#define PIN_T1_1 2
#define PIN_T1_2 5
#define PIN_T2_1 4
#define PIN_T2_2 3
#define NUMPIXELS 28



// WS2812B format is G-R-B (SMD select NEO_GRB)
// WS2811 format is R-G-B (TH select NEO_RGB)
Adafruit_NeoPixel T1_1 = Adafruit_NeoPixel(NUMPIXELS, PIN_T1_1, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel T1_2 = Adafruit_NeoPixel(NUMPIXELS, PIN_T1_2, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel T2_1 = Adafruit_NeoPixel(NUMPIXELS, PIN_T2_1, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel T2_2 = Adafruit_NeoPixel(NUMPIXELS, PIN_T2_2, NEO_RGB + NEO_KHZ800);


void initDigits();
void testDigits();
void updateTeamScores();
void clearAllSegments(Adafruit_NeoPixel * p, bool onesPlace);
void writeDigitValue(uint8_t value, Adafruit_NeoPixel * p);
void writeSegment(uint8_t segnum, bool onOff, Adafruit_NeoPixel * p);
void selectColor(uint8_t teamNum, uint8_t red, uint8_t green, uint8_t blue);
void cycleColorDown(uint8_t teamNum);
void cycleColorUp(uint8_t teamNum);
void cycleColor(uint8_t teamNum);
void colorSelectMode(uint8_t teamNum, bool modeActive);
void wipeDigits(Adafruit_NeoPixel * p);

void initDigits()
{  
  T1_1.begin(); // This initializes the NeoPixel library.
  T1_1.setDefaultColor(COLOR_RED);
  T1_2.begin(); // This initializes the NeoPixel library.
  T1_2.setDefaultColor(COLOR_RED);
  T2_1.begin(); // This initializes the NeoPixel library.
  T2_1.setDefaultColor(COLOR_BLUE);
  T2_2.begin(); // This initializes the NeoPixel library.
  T2_2.setDefaultColor(COLOR_BLUE);

  //Start digits at 0
  writeDigitValue(0, &T1_1);
  writeDigitValue(0, &T1_2);
  writeDigitValue(0, &T2_1);
  writeDigitValue(0, &T2_2);
}

void testDigits()
{
    static int counterVariable = 0;
    writeDigitValue(counterVariable, &T1_1);
    writeDigitValue(counterVariable, &T1_2);
    writeDigitValue(counterVariable, &T2_1);
    writeDigitValue(counterVariable++, &T2_2);
    if(counterVariable>99)
    {
      counterVariable = 0;
    }
}

void selectRawTeamColor(uint8_t teamNum, uint8_t r, uint8_t g, uint8_t b)
{
  if(teamNum==1)
  {
      T1_1.setDefaultColor(r,g,b);
      T1_2.setDefaultColor(r,g,b);
  }
  else
  {         
      T2_1.setDefaultColor(r,g,b);
      T2_2.setDefaultColor(r,g,b);
  }
}

void colorSelectMode(uint8_t teamNum, bool modeActive)
{
   team_color_select_mode_active[teamNum] = modeActive;
}

void selectColor(uint8_t teamNum, team_color_t newColor)
{
  team_colors[teamNum] = newColor;
  
  if(teamNum == TEAM_1)
  {     
    switch(team_colors[teamNum])  
    {
      case WHITE:
        T1_1.setDefaultColor(COLOR_WHITE);
        T1_2.setDefaultColor(COLOR_WHITE);
        break;
      case YELLOW:
        T1_1.setDefaultColor(COLOR_YELLOW);
        T1_2.setDefaultColor(COLOR_YELLOW);
        break;
      case GREEN:
        T1_1.setDefaultColor(COLOR_GREEN);
        T1_2.setDefaultColor(COLOR_GREEN);
        break;
      case BLUE:
        T1_1.setDefaultColor(COLOR_BLUE);
        T1_2.setDefaultColor(COLOR_BLUE);
        break;
      case RED:
        T1_1.setDefaultColor(COLOR_RED);
        T1_2.setDefaultColor(COLOR_RED);
        break;
      default:
        T1_1.setDefaultColor(COLOR_RED);
        T1_2.setDefaultColor(COLOR_RED);
        break;
    }
  }
  else
  {   
    switch(team_colors[teamNum])  
    { 
      case WHITE:
        T2_1.setDefaultColor(COLOR_WHITE);
        T2_2.setDefaultColor(COLOR_WHITE);
        break;
      case YELLOW:
        T2_1.setDefaultColor(COLOR_YELLOW);
        T2_2.setDefaultColor(COLOR_YELLOW);
        break;
      case GREEN:
        T2_1.setDefaultColor(COLOR_GREEN);
        T2_2.setDefaultColor(COLOR_GREEN);
        break;
      case BLUE:
        T2_1.setDefaultColor(COLOR_BLUE);
        T2_2.setDefaultColor(COLOR_BLUE);
        break;
      case RED:
        T2_1.setDefaultColor(COLOR_RED);
        T2_2.setDefaultColor(COLOR_RED);
        break;
      default:
        T2_1.setDefaultColor(COLOR_BLUE);
        T2_2.setDefaultColor(COLOR_BLUE);
        break;
    }
  }
}

void cycleColorDown(uint8_t teamNum)
{
  switch(team_colors[teamNum])
  {
    case WHITE:
      team_colors[teamNum] = RED;
      break;
    case YELLOW:
      team_colors[teamNum] = WHITE;
      break;
    case GREEN:
      team_colors[teamNum] = YELLOW;
      break;
    case BLUE:
      team_colors[teamNum] = GREEN;
      break;
    case RED:
      team_colors[teamNum] = BLUE;
      break;
    default:
      team_colors[teamNum] = RED;
      break;
  }
  selectColor(teamNum, team_colors[teamNum]);
}

void cycleColorUp(uint8_t teamNum)
{
  switch(team_colors[teamNum])
  {
    case WHITE:
      team_colors[teamNum] = YELLOW;
      break;
    case YELLOW:
      team_colors[teamNum] = GREEN;
      break;
    case GREEN:
      team_colors[teamNum] = BLUE;
      break;
    case BLUE:
      team_colors[teamNum] = RED;
      break;
    case RED:
      team_colors[teamNum] = WHITE;
      break;
    default:
      team_colors[teamNum] = WHITE;
      break;
  }
  selectColor(teamNum, team_colors[teamNum]);
}

void cycleColor(uint8_t teamNum)
{
  switch(team_colors[teamNum])
  {
    case WHITE:
      team_colors[teamNum] = YELLOW;
      break;
    case YELLOW:
      team_colors[teamNum] = GREEN;
      break;
    case GREEN:
      team_colors[teamNum] = BLUE;
      break;
    case BLUE:
      team_colors[teamNum] = RED;
      break;
    case RED:
      team_colors[teamNum] = WHITE;
      break;
    default:
      team_colors[teamNum] = WHITE;
      break;
  }
  selectColor(teamNum, team_colors[teamNum]);
}

void updateTeamScores()
{
  if(team_color_select_mode_active[TEAM_1])
  {
    if(T1_flash_timer.timerDone())
    {
      if(t1_flash_on)
      {
        writeDigitValue(t1_score, &T1_1);
        writeDigitValue(t1_score, &T1_2); 
        t1_flash_on = false;
      }
      else
      {
        wipeDigits(&T1_1);
        wipeDigits(&T1_2);
        t1_flash_on = true;
      }
    }
  }
  else
  {
      writeDigitValue(t1_score, &T1_1);
      writeDigitValue(t1_score, &T1_2); 
    
  }
  
  if(team_color_select_mode_active[TEAM_2])
  { 
    if(T2_flash_timer.timerDone())
    {
      if(t2_flash_on)
      {
        writeDigitValue(t2_score, &T2_1);
        writeDigitValue(t2_score, &T2_2);    
        t2_flash_on = false;
      }
      else
      {
        wipeDigits(&T2_1);
        wipeDigits(&T2_2);
        t2_flash_on = true;
      }   
    }
  }
  else
  {    
    writeDigitValue(t2_score, &T2_1);
    writeDigitValue(t2_score, &T2_2); 
  }
}

void wipeDigits(Adafruit_NeoPixel * p)
{
  clearAllSegments(p,true);
  clearAllSegments(p,false);
  p->show(); // This sends the updated pixel color to the hardware.
}

void clearAllSegments(Adafruit_NeoPixel * p, bool onesPlace)
{
  if(!onesPlace)
  {
    for(int i=NUMPIXELS/2;i<NUMPIXELS;i++)
    {
       p->setPixelColor(i, p->Color(COLOR_OFF));   
    }
  }
  else
  {    
    for(int i=0;i<NUMPIXELS/2;i++)
    {
       p->setPixelColor(i, p->Color(COLOR_OFF));   
    }
  }
}
void writeDigitValue(uint8_t value, Adafruit_NeoPixel * p)
{
  
  int digitPlace =0, thisValue = 0;
  for(int i=0; i<=1; i++)
  {
    if(i==1)
    {
      thisValue = value % 10;
      digitPlace = 0;
    }
    else
    {
      thisValue = value / 10;
      digitPlace = 7;
    }
  
    // Clear all segments before setting the segments
    clearAllSegments(p,i);
   
    switch(thisValue)
    {
      case 0:
        for(int i=0;i<sizeof(zeroSegments);i++)
        {
          writeSegment(zeroSegments[i]+digitPlace,true,p);
        }
        break;
      case 1:    
        for(int i=0;i<sizeof(oneSegments);i++)
        {
          writeSegment(oneSegments[i]+digitPlace,true,p);
        }
        break;
      case 2:    
        for(int i=0;i<sizeof(twoSegments);i++)
        {
          writeSegment(twoSegments[i]+digitPlace,true,p);
        }
        break;
      case 3:
        for(int i=0;i<sizeof(threeSegments);i++)
        {
          writeSegment(threeSegments[i]+digitPlace,true,p);
        }
        break;
      case 4:
        for(int i=0;i<sizeof(fourSegments);i++)
        {
          writeSegment(fourSegments[i]+digitPlace,true,p);
        }
        break;
      case 5:
        for(int i=0;i<sizeof(fiveSegments);i++)
        {
          writeSegment(fiveSegments[i]+digitPlace,true,p);
        }
        break;
      case 6:
        for(int i=0;i<sizeof(sixSegments);i++)
        {
          writeSegment(sixSegments[i]+digitPlace,true,p);
        }
        break;
      case 7:
        for(int i=0;i<sizeof(sevenSegments);i++)
        {
          writeSegment(sevenSegments[i]+digitPlace,true,p);
        }
        break;
      case 8:
        for(int i=0;i<sizeof(eightSegments);i++)
        {
          writeSegment(eightSegments[i]+digitPlace,true,p);
        }
        break;
      case 9:
        for(int i=0;i<sizeof(nineSegments);i++)
        {
          writeSegment(nineSegments[i]+digitPlace,true,p);
        }
        break;
      default:
        for(int i=0;i<sizeof(zeroSegments);i++)
        {
          writeSegment(zeroSegments[i]+digitPlace,true,p);
        }
        break;
    }
  }
    p->show(); // This sends the updated pixel color to the hardware.

}

void writeSegment(uint8_t segnum, bool onOff, Adafruit_NeoPixel * p)
{
  if(onOff)
  {
    p->setPixelColor(((segnum-1)*2), p->getDefaultColor()); // Moderately bright green color.
    p->setPixelColor(((segnum-1)*2)+1, p->getDefaultColor()); // Moderately bright green color.
  }
  else
  {    
    p->setPixelColor(((segnum-1)*2), p->Color(COLOR_OFF)); // Moderately bright green color.
    p->setPixelColor(((segnum-1)*2)+1, p->Color(COLOR_OFF)); // Moderately bright green color.
  }  
}
