#define frequenceMicroS 100
#define frequenceFramesMicroS 50000

int btnUP = 3, btnDOWN = 4, btnLEFT = 5, btnRIGHT = 2, btnCONF = 6,
stateUP, stateDOWN, stateLEFT, stateRIGHT, stateCONF, counter=0, counter2=0,
pointer[2] = {0,0};

int cols[] = {38,41,39,32,35,34,42,44},
    rows[] = {30,40,31,36,45,33,43,37};

int W[8][8] =
{
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,1,1,0,0,1},
  {1,0,0,1,1,0,0,1},
  {1,0,1,0,0,1,0,1},
  {1,0,1,0,0,1,0,1},
  {0,1,0,0,0,0,1,0}
};

int L[8][8] =
{
  {0,1,1,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,1,1,1,1,1,1,0},
  {0,1,1,1,1,1,1,0}
};

int tab[8][8] = 
{
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};

int maping[8][8] =
{
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};

void createNewMap()
{
  int num, i, j, c=0;

  for (i=0;i<8;i++)
  {
    for (j=0;j<8;j++)
    {
      num = random(0, 64);
      if (num < 8) maping[i][j] = 1;
      else maping[i][j] = 0;
    }
  }

  for (i=0;i<8;i++)
  {
    for (j=0;j<8;j++)
    {
      tab[i][j]=0;
    }
  }

  while (c<30000)
  {
    if ((int)(c / 1250)%2==0)
    {
      for (i=0;i<8;i++)
      {
        digitalWrite(cols[i], LOW);
        for (j=0;j<8;j++)
        {
            digitalWrite(rows[j], maping[j][i]);
            digitalWrite(rows[j], LOW);
        }
        digitalWrite(cols[i], HIGH);
      }
      delayMicroseconds(100);
      c+=2;
    }
    else
    {
      delayMicroseconds(200);
      c++;
    }
    
  }
}

void verify()
{
  int i,j,conf=1;
  for (i=0;i<8;i++)
  {
    for (j=0;j<8;j++)
    {
      if (maping[i][j] != tab[i][j])
      {
        if (tab[i][j]) 
        {
          win_lose(L);
          return;
        }
        conf=0;
      }
    }
  }

  if (conf)
  {
    win_lose(W);
  }
}

void win_lose(int A[8][8])
{
  int i,j;
  delay(1000);
  while (digitalRead(btnCONF))
  {
    for (i=0;i<8;i++)
    {
      digitalWrite(cols[i], LOW);
      for (j=0;j<8;j++)
      {
          digitalWrite(rows[j], A[j][i]);
          digitalWrite(rows[j], LOW);
      }
      digitalWrite(cols[i], HIGH);
    }
  }
  createNewMap();
  pointer[0]=0; pointer[1]=0;
}

void setup(){
	pinMode(btnUP, INPUT_PULLUP);
	pinMode(btnDOWN, INPUT_PULLUP);
	pinMode(btnLEFT, INPUT_PULLUP);
	pinMode(btnRIGHT, INPUT_PULLUP);
	pinMode(btnCONF, INPUT_PULLUP);

  randomSeed(analogRead(0));

  for (int i=0; i<8; i++)
  {
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);

    digitalWrite(cols[i], HIGH);
  }

  createNewMap();
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

    if (counter2<250)
    {
      digitalWrite(cols[pointer[1]], LOW);
      digitalWrite(rows[pointer[0]], HIGH);
      digitalWrite(rows[pointer[0]], LOW);
      digitalWrite(cols[pointer[1]], HIGH);
    }
    
    if (counter2>=500) counter2=0;

    delayMicroseconds(frequenceMicroS);
    counter++;
    counter2++;
  }

  counter = 0;
  
  if (stateUP)
  {
    if (pointer[0] != 0)
    {
      --pointer[0];
    }
  }
  if (stateDOWN)
  {
    if (pointer[0] != 7)
    {
      ++pointer[0];
    }
  }
  if (stateLEFT)
  {
    if (pointer[1] != 0)
    {
      --pointer[1];
    }
  }
  if (stateRIGHT)
  {
    if (pointer[1] != 7)
    {
      ++pointer[1];
    }
  }
  if (stateCONF)
  {
      tab[pointer[0]][pointer[1]] = !tab[pointer[0]][pointer[1]];
      verify();
  }
}
