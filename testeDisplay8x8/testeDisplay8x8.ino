//             Y6 Y3 X4 Y1 X6 X7 Y2 Y4
//int imp[] = {31,33,35,37,39,41,43,45};
//             Y8 X5 X3 Y5 X8 Y7 X2 X1
//int par[] = {30,32,34,36,38,40,42,44};

/*
Para formar os desenhos as linhas recebem o valor, 
e as colunas recebem o valor barrado(invertido).
*/

int desenho[8][8] = 
{
  {0,0,0,0,0,0,0,0},
  {0,0,1,0,0,1,0,0},
  {0,0,1,0,0,1,0,0},
  {0,0,1,0,0,1,0,0},
  {0,0,0,0,0,0,0,0},
  {0,1,0,0,0,0,1,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,0,0,0,0,0}
};

int desenho2[8][8] = 
{
  {0,0,0,1,1,0,0,0},
  {0,0,1,1,1,1,0,0},
  {0,1,1,1,1,1,1,0},
  {1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1},
  {0,1,1,0,0,1,1,0}
};

int cols[]= {44,42,34,35,32,39,41,38};

int rows[]= {37,43,33,45,36,31,40,30};

int pixels[8][8];

void setup() {
  // put your setup code here, to run once:
  int i, j;
  for (i = 0; i < 8; i++)
  {
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);

    digitalWrite(cols[i], HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int i,j;
  for (i=0;i<8;i++)
  {
    digitalWrite(cols[i], LOW);
    for (j=0;j<8;j++)
    {
      digitalWrite(rows[j], desenho2[j][i]);
      // delay(10); // <0.1 nao funciona>
      // delayMicroseconds(100); // <funciona>
      digitalWrite(rows[j], LOW);
    }
    digitalWrite(cols[i], HIGH);
  }
}
