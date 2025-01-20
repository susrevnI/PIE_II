#define frequenceMicroS 100
#define frequenceFramesMicroS 1000000

int btnUP = 3, btnDOWN = 4, btnLEFT = 5, btnRIGHT = 2, btnCONF = 6,
stateUP, stateDOWN, stateLEFT, stateRIGHT, stateCONF, counter=0,
cobra[64][2], sentido[2], T, fruta[2];

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

void Winner_Losing(int h)
{
  int i, j, k=0;
  while (digitalRead(btnCONF))
  {
    if (k > frequenceFramesMicroS/200)
    {
      if (h)
      {
        for (i=0;i<8;i++)
        {
          digitalWrite(cols[i], LOW);
          for (j=0;j<8;j++)
          {
            digitalWrite(rows[j], W[j][i]);
            digitalWrite(rows[j], LOW);
          }
          digitalWrite(cols[i], HIGH);
        }
      }
      else
      {
        for (i = 0; i < T; i++)
        {
          digitalWrite(cols[cobra[i][0]], LOW);
          digitalWrite(rows[cobra[i][1]], HIGH);
          digitalWrite(rows[cobra[i][1]], LOW);
          digitalWrite(cols[cobra[i][0]], HIGH);
        }
      }
    }
    if (k>frequenceFramesMicroS/frequenceMicroS) k=0;
    delayMicroseconds(frequenceMicroS);
    k++;
  }
  newGame();
}

void newGame()
{
  cobra[0][0] = 0;cobra[0][1] = 0;
  cobra[1][0] = 1;cobra[1][1] = 0;
  cobra[2][0] = 2;cobra[2][1] = 0;
  T = 3;
  sentido[0] = 1;
  sentido[1] = 0;
  novaFruta();
}

void novaFruta()
{
  int i, x = random(0,8), y = random(0,8), conf = 1;

  while(conf)
  {
    conf = 0;

    for (i = 0; i < T; i++)
    {
      if (cobra[i][0] == x && cobra[i][1] == y)
      {
        conf = 1;
        x = random(0,8);
        y = random(0,8);
      }
    } 
  }
  fruta[0] = x;
  fruta[1] = y;
}

void moverCobra()
{

  if (cobra[T-1][0]+sentido[0] > 7 || cobra[T-1][1]+sentido[1] > 7 || cobra[T-1][0]+sentido[0] < 0 || cobra[T-1][1]+sentido[1] < 0)
  {
    // Losing!!!
    Winner_Losing(0);
    return;
  }

  if (cobra[T-1][0]+sentido[0] == fruta[0] && cobra[T-1][1]+sentido[1] == fruta[1])
  {
    T++;
    cobra[T-1][0] = cobra[T-2][0] + sentido[0];
    cobra[T-1][1] = cobra[T-2][1] + sentido[1];
    if (T == 16){
      // Winner!!!
      Winner_Losing(1);
    }

    return novaFruta();
  }
  
  int i;
  for (i = 0; i < T-1;i ++)
  {
    if (cobra[T-1][0]+sentido[0] == cobra[i][0] && cobra[T-1][1]+sentido[1] == cobra[i][1])
    {
      // Losing
      Winner_Losing(0);
      return;
    }
  }

  for (i = 0; i < T-1; i++)
  {
    cobra[i][0] = cobra[i+1][0];
    cobra[i][1] = cobra[i+1][1];
  }

  cobra[T-1][0] += sentido[0];
  cobra[T-1][1] += sentido[1];

}

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

  newGame();
}

void loop(){

  int i,j;
  while (counter*frequenceMicroS < frequenceFramesMicroS)
  {
    stateUP = !digitalRead(btnUP);
    stateDOWN = !digitalRead(btnDOWN);
    stateLEFT = !digitalRead(btnLEFT);
    stateRIGHT = !digitalRead(btnRIGHT);
    stateCONF = !digitalRead(btnCONF);

    for (i = 0; i < T; i++)
    {
      digitalWrite(cols[cobra[i][0]], LOW);
      digitalWrite(rows[cobra[i][1]], HIGH);
      digitalWrite(rows[cobra[i][1]], LOW);
      digitalWrite(cols[cobra[i][0]], HIGH);
    }

    if ((int)(counter / 2500)%2==0)
    {
      digitalWrite(cols[fruta[0]], LOW);
      digitalWrite(rows[fruta[1]], HIGH);
      digitalWrite(rows[fruta[1]], LOW);
      digitalWrite(cols[fruta[0]], HIGH);
    }

    delayMicroseconds(frequenceMicroS);
    counter++;
  }

  counter = 0;

  if (stateUP+stateDOWN+stateLEFT+stateRIGHT != 1) return moverCobra();
  
  if (stateUP && !sentido[1])
  {
    sentido[1] = -1;
    sentido[0] = 0;
  }
  if (stateDOWN && !sentido[1])
  {
    sentido[1] = 1;
    sentido[0] = 0;
  }
  if (stateLEFT && !sentido[0])
  {
    sentido[0] = -1;
    sentido[1] = 0;
  }
  if (stateRIGHT && !sentido[0])
  {
    sentido[0] = 1;
    sentido[1] = 0;
  }
  if (stateCONF)
  {
    // Void
  }

  moverCobra();
}
