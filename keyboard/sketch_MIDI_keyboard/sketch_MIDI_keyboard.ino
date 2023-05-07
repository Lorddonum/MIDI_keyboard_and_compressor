uint8_t buffer[8]={0};

#define Pin_A1 A1
#define Pin_A2 A2
#define Pin_A3 A3
#define Pin_A4 A4
#define Pin_A5 A5
#define Pin_D0 0
#define Pin_D1 1
#define Pin_D2 2
#define Pin_D3 3
#define Pin_D4 4
#define Pin_D5 5
#define Pin_D6 6
#define Pin_D7 7
#define Pin_D8 8
#define Pin_D9 -9
#define Pin_D10 -10
#define Pin_D11 -11
#define Pin_D12 -12


void setup(void) {
  Serial.begin(9600);
  //setting up the pins to read
  pinMode(Pin_A1,INPUT);
  pinMode(Pin_A2,INPUT);
  pinMode(Pin_A3,INPUT);
  pinMode(Pin_A4,INPUT);
  pinMode(Pin_A5,INPUT);

  pinMode(Pin_D0,INPUT);
  pinMode(Pin_D1,INPUT);
  pinMode(Pin_D2,INPUT);
  pinMode(Pin_D3,INPUT);
  pinMode(Pin_D4,INPUT);
  pinMode(Pin_D5,INPUT);
  pinMode(Pin_D6,INPUT);
  pinMode(Pin_D7,INPUT);
  pinMode(Pin_D8,INPUT);
  pinMode(Pin_D9,INPUT);
  pinMode(Pin_D10,INPUT);
  pinMode(Pin_D11,INPUT);
  pinMode(Pin_D12,INPUT);
  
}

void loop(void) {
  //WHITE KEYS
  if(digitalRead(Pin_D0)){ //a 
    buffer[2]=4;
    Serial.write(buffer,8);
    release();
  }

  if(digitalRead(Pin_D2)){ //s 
    buffer[2]=22;
    Serial.write(buffer,8);
    release();
  }

  if(digitalRead(Pin_D4)){ //d
    buffer[2]=7;
    Serial.write(buffer,8);
    release();
  }

  if(digitalRead(Pin_D5)){ //f
    buffer[2]=9;
    Serial.write(buffer,8);
    release();
  }

  if(digitalRead(Pin_D7)){ //g
    buffer[2]=10;
    Serial.write(buffer,8);
    release();
  }

  if(digitalRead(Pin_D9)){ //h
    buffer[2]=11;
    Serial.write(buffer,8);
    release();
  }

  if(digitalRead(Pin_D11)){ //j
    buffer[2]=13;
    Serial.write(buffer,8);
    release();
  }

  if(digitalRead(Pin_D12)){ //k
    buffer[2]=14;
    Serial.write(buffer,8);
    release();
  }

  if(digitalRead(Pin_A2)){ //l
    buffer[2]=15;
    Serial.write(buffer,8);
    release();
  }

  if(digitalRead(Pin_A4)){ //;
    buffer[2]=51;
    Serial.write(buffer,8);
    release();
  }

  if(digitalRead(Pin_A5)){ //'
    buffer[2]=52;
    Serial.write(buffer,8);
    release();
  }

  //BLACK KEYS
  if(digitalRead(Pin_D1)){ //w
    buffer[2]=26;
    Serial.write(buffer,8);
    release();
  }

  if(digitalRead(Pin_D3)){ //e
    buffer[2]=8;
    Serial.write(buffer,8);
    release();
  }

  if(digitalRead(Pin_D6)){ //t
    buffer[2]=23;
    Serial.write(buffer,8);
    release();
  }

  if(digitalRead(Pin_D8)){ //y
    buffer[2]=28;
    Serial.write(buffer,8);
    release();
  }

  if(digitalRead(Pin_D10)){ //u
    buffer[2]=24;
    Serial.write(buffer,8);
    release();
  }

  if(digitalRead(Pin_A1)){ //o
    buffer[2]=18;
    Serial.write(buffer,8);
    release();
  }

  if(digitalRead(Pin_A3)){ //p
    buffer[2]=19;
    Serial.write(buffer,8);
    release();
  }
  
}

void release(void){
  buffer[0]=0;
  buffer[2]=0;
  Serial.write(buffer,8);
}
