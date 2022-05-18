Timers parseTimeoutTimer(50);

void rxPacket();
bool parseTeamColorPacket();
void sendResponsePacket();

void rxPacket()
{
  bool respondPlease = false;
  int TRIGGERED = 0;
  if (Serial.available())
  {
    TRIGGERED = Serial.read();
    digitalWrite(13,!digitalRead(13));
  }

  switch (TRIGGERED)
  {
    case 'A':  //Add T1
      t1_score += 1;
      respondPlease=true;
      break;
    case 'B':  //Sub T1
      t1_score -= 1;
      respondPlease=true;
      break;
    case 'C': // Add T2
      t2_score += 1;
      respondPlease=true;
      break;
    case 'D': // Sub T2
      t2_score -= 1;
      respondPlease=true;
      break;
      
    case 'E': //Reset All
      t1_score = 0;
      t2_score = 0;
      respondPlease=true;
      break;

    case 'T':
      if(parseTeamColorPacket())
      {      
      }
      break;
      
    case 'Y': // Set 15 T1
      t1_score = 15;
      respondPlease=true;
      break;
    case 'Z': // Set 15 T2
      t2_score = 15;
      respondPlease=true;
      break;
  }
  
  if(respondPlease)  
    sendResponsePacket();
}

bool parseTeamColorPacket()
{
  uint8_t teamNumber = 0;
  int r=0,g=0,b=0;
  float decimalPlace=100;
  
  parseTimeoutTimer.resetTimer();
  while(!parseTimeoutTimer.timerDone())
  {
    if(Serial.available()>12)
    {
          Serial.print(Serial.peek());
          Serial.print(" ");
        switch(Serial.read())
        {
          case '1':
            teamNumber = 1;
            break;
          case '2':
            teamNumber = 2;       
            break;
        }      
        //Remove the comma
          Serial.write(Serial.peek());
          Serial.print(" ");
        Serial.read();
        //----------Read R Value--------
        for(int j=0;j<3;j++)
        {
          Serial.write(Serial.peek());
          r+=(Serial.read()-48)*decimalPlace;
          decimalPlace=decimalPlace/10.0;
        }
        //Remove the comma
          Serial.write(Serial.peek());
          Serial.print(" ");
        Serial.read();
        decimalPlace = 100;
         //----------Read G Value--------
        for(int j=0;j<3;j++)
        {
          Serial.write(Serial.peek());
          g+=(Serial.read()-48)*decimalPlace;
          decimalPlace=decimalPlace/10.0;
        }
        //Remove the comma
          Serial.write(Serial.peek());
          Serial.print(" ");
        Serial.read();
        decimalPlace = 100;
         //----------Read B Value--------
        for(int j=0;j<3;j++)
        {
          Serial.write(Serial.peek());
          b+=(Serial.read()-48)*decimalPlace;
          decimalPlace=decimalPlace/10.0;
        }
        
      }
    }
    if(teamNumber!=0)
    {
      Serial.print("red:");
      Serial.print(r);
      Serial.print(",green:");
      Serial.print(g);
      Serial.print(",blue:");
      Serial.print(b);
      Serial.print(",");
       selectRawTeamColor(teamNumber,r,g,b);
       return true;
    }
    return false;
  }


void sendResponsePacket()
{
  Serial.print("T1:");
  if(t1_score<10) Serial.print("0");
  Serial.print(t1_score);
  Serial.print("T2:");
  if(t2_score<10) Serial.print("0");
  Serial.print(t2_score);
}
