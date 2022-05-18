#define TEAM1_PLUS_PIN A1
#define TEAM1_RST_PIN 7
#define TEAM1_MINUS_PIN 6

#define TEAM2_PLUS_PIN 9
#define TEAM2_RST_PIN A0
#define TEAM2_MINUS_PIN 8


bool T1_P_DEPRESSED = false,
T1_R_DEPRESSED = false,
T1_M_DEPRESSED = false,
T2_P_DEPRESSED = false,
T2_R_DEPRESSED = false,
T2_M_DEPRESSED = false;

Timers T1_ResetButtonTimer(1000);
Timers T2_ResetButtonTimer(1000);

Timers T1_ButtonHoldTimer(100);
Timers T2_ButtonHoldTimer(100);

bool T1_ColorSelectMode = false, T2_ColorSelectMode = false;
uint8_t t1_score_holder = 0, t2_score_holder = 0;

void initButtons(){
  pinMode(TEAM1_PLUS_PIN,INPUT_PULLUP);
  pinMode(TEAM1_RST_PIN,INPUT_PULLUP);
  pinMode(TEAM1_MINUS_PIN,INPUT_PULLUP);
  pinMode(TEAM2_PLUS_PIN,INPUT_PULLUP);
  pinMode(TEAM2_RST_PIN,INPUT_PULLUP);
  pinMode(TEAM2_MINUS_PIN,INPUT_PULLUP);
  
}

void updateButtons()
{
  bool changedScore = false;
  
  /******************************T1_PLUS************************/
  if(!digitalRead(TEAM1_PLUS_PIN) && !T1_P_DEPRESSED)
  { 
    if(T1_ColorSelectMode)  
    {
      cycleColorUp(TEAM_1);
    }
    else
    {
      t1_score++;
      changedScore = true;
    }
    T1_P_DEPRESSED = true;
    T1_ButtonHoldTimer.resetTimer();
  }
  else if(!digitalRead(TEAM1_PLUS_PIN) && T1_P_DEPRESSED && T1_ButtonHoldTimer.timerDone())
  {    
    if(!T1_ColorSelectMode)  
    {
      t1_score++;
      changedScore = true;
    }
  }
  else if(digitalRead(TEAM1_PLUS_PIN) && T1_P_DEPRESSED)
  {
    T1_P_DEPRESSED = false;
  }

  
  /******************************T1_RESET************************/
  if(!digitalRead(TEAM1_RST_PIN)&& !T1_R_DEPRESSED)
  {
    t1_score_holder = t1_score;
    if(T1_ColorSelectMode)
    {
      T1_ColorSelectMode = false;
      colorSelectMode(TEAM_1, false);
      T1_ResetButtonTimer.setInterval(250);
      T1_ResetButtonTimer.resetTimer();
      while(!T1_ResetButtonTimer.timerDone());
      T1_ResetButtonTimer.setInterval(1000);
    }
    else
    {
      T1_R_DEPRESSED = true;
      T1_ResetButtonTimer.resetTimer();
    }
  }
  else if(!digitalRead(TEAM1_RST_PIN) && T1_R_DEPRESSED && T1_ResetButtonTimer.timerDone())
  {    
    t1_score = t1_score_holder;
    changedScore = true;
    T1_ColorSelectMode = true;
    colorSelectMode(TEAM_1, true);
  }
  else if(digitalRead(TEAM1_RST_PIN) && T1_R_DEPRESSED)
  {    
    if(!T1_ColorSelectMode)
    {
      t1_score=0;
      changedScore = true;      
    }
    T1_R_DEPRESSED = false;
  }

  
  /******************************T1_MINUS************************/
  if(!digitalRead(TEAM1_MINUS_PIN) && !T1_M_DEPRESSED)
  {
    if(T1_ColorSelectMode)
    {
      cycleColorDown(TEAM_1);
    }
    else
    {
      t1_score--;
      changedScore = true;
    }
    T1_M_DEPRESSED = true;
    T1_ButtonHoldTimer.resetTimer();
  }
  else if(!digitalRead(TEAM1_MINUS_PIN) && T1_M_DEPRESSED && T1_ButtonHoldTimer.timerDone())
  {    
    if(!T1_ColorSelectMode)
    {
      t1_score--;
      changedScore = true;
    }
  }
  else if(digitalRead(TEAM1_MINUS_PIN) && T1_M_DEPRESSED)
  {
    T1_M_DEPRESSED = false;    
  }

  
  /******************************T2_PLUS************************/
  if(!digitalRead(TEAM2_PLUS_PIN) && !T2_P_DEPRESSED)
  {
    if(T2_ColorSelectMode)
    {
      cycleColorUp(TEAM_2);
    }
    else
    {
      t2_score++;
      changedScore = true;
    }
    T2_P_DEPRESSED = true;
  }
  else if(!digitalRead(TEAM2_PLUS_PIN) && T2_P_DEPRESSED && T2_ButtonHoldTimer.timerDone())
  {    
    if(!T2_ColorSelectMode)
    {
      t2_score++;
      changedScore = true;
    }
  }
  else if(digitalRead(TEAM2_PLUS_PIN) && T2_P_DEPRESSED)
  {
    T2_P_DEPRESSED = false;    
  }
  /******************************T2_RESET************************/
  if(!digitalRead(TEAM2_RST_PIN) && !T2_R_DEPRESSED)
  {
    t2_score_holder = t2_score;
    if(T2_ColorSelectMode)
    {
      T2_ColorSelectMode = false;
      colorSelectMode(TEAM_2, false);
      T2_ResetButtonTimer.setInterval(250);
      T2_ResetButtonTimer.resetTimer();
      while(!T2_ResetButtonTimer.timerDone());
      T2_ResetButtonTimer.setInterval(1000);
    }
    else
    {
      T2_R_DEPRESSED = true;    
      T2_ResetButtonTimer.resetTimer();
    }
  }
  else if(!digitalRead(TEAM2_RST_PIN) && T2_R_DEPRESSED && T2_ResetButtonTimer.timerDone())
  {       
    t2_score = t2_score_holder;
    changedScore = true;
    T2_ColorSelectMode = true;
    colorSelectMode(TEAM_2, true);
  }
  else if(digitalRead(TEAM2_RST_PIN) && T2_R_DEPRESSED)
  {
    if(!T2_ColorSelectMode)
    {
      t2_score=0;
      changedScore = true;      
    }
    T2_R_DEPRESSED = false;    
  }
  
  /******************************T2_MINUS************************/
  if(!digitalRead(TEAM2_MINUS_PIN) && !T2_M_DEPRESSED)
  {
    if(T2_ColorSelectMode)
    {
      cycleColorDown(TEAM_2);
    }
    else
    {
      t2_score--;
      changedScore = true;
    }
    T2_M_DEPRESSED = true;
  }
  else if(!digitalRead(TEAM2_MINUS_PIN) && T2_M_DEPRESSED && T2_ButtonHoldTimer.timerDone())
  {    
    if(!T2_ColorSelectMode)
    {
      t2_score--;
      changedScore = true;
    }
  }
  else if(digitalRead(TEAM2_MINUS_PIN) && T2_M_DEPRESSED)
  {    
    T2_M_DEPRESSED = false;
  }
  
  if(changedScore)
  {
    sendResponsePacket();
    
  }
}
