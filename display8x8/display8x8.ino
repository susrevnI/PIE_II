#define frequenceMicroS 100
#define frequenceFramesMicroS 50000

int btnUP = 3, btnDOWN = 4, btnLEFT = 5, btnRIGHT = 2, btnCONF = 6,
stateUP, stateDOWN, stateLEFT, stateRIGHT, stateCONF, counter=0,
pointer[2] = {0,0};

int cols[] = {38,41,39,32,35,34,42,44},
    rows[] = {30,40,31,36,45,33,43,37};

int tab[8][8] = 
{
  {1,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};

void setup(){
	pinMode(btnUP, INPUT_PULLUP);
	pinMode(btnDOWN, INPUT_PULLUP);
	pinMode(btnLEFT, INPUT_PULLUP);
	pinMode(btnRIGHT, INPUT_PULLUP);
	pinMode(btnCONF, INPUT_PULLUP);

  for (int i=0; i<8; i++)
  {
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);

    digitalWrite(cols[i], HIGH);
  }
}

void loop(){
  stateUP = !digitalRead(btnUP);
  stateDOWN = !digitalRead(btnDOWN);
  stateLEFT = !digitalRead(btnLEFT);
  stateRIGHT = !digitalRead(btnRIGHT);
  stateCONF = !digitalRead(btnCONF);

  int i,j;
  while (counter*frequenceMicroS < frequenceFramesMicroS)
  {
    for (i=0;i<8;i++)
    {
      digitalWrite(cols[i], LOW);
      for (j=0;j<8;j++)
      {
          digitalWrite(rows[j], tab[j][i]);
          digitalWrite(rows[j], LOW);
      }
      digitalWrite(cols[i], HIGH);
    }

    delayMicroseconds(frequenceMicroS);
    counter++;
  }

  counter = 0;
  
  if (stateUP)
  {
    if (pointer[0] != 0)
    {
      tab[pointer[0]][pointer[1]] = 0;
      tab[--pointer[0]][pointer[1]] = 1;
    }
  }
  if (stateDOWN)
  {
    if (pointer[0] != 7)
    {
      tab[pointer[0]][pointer[1]] = 0;
      tab[++pointer[0]][pointer[1]] = 1;
    }
  }
  if (stateLEFT)
  {
    if (pointer[1] != 0)
    {
      tab[pointer[0]][pointer[1]] = 0;
      tab[pointer[0]][--pointer[1]] = 1;
    }
  }
  if (stateRIGHT)
  {
    if (pointer[1] != 7)
    {
      tab[pointer[0]][pointer[1]] = 0;
      tab[pointer[0]][++pointer[1]] = 1;
    }
  }
  if (stateCONF)
  {
    
  }
}
