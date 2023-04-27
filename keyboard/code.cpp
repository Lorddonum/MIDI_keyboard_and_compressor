float C2 = 79.0;
float Db2 = 83.0;
float D2 = 88.0;
float Eb2 = 93.0;
float E2 = 98.0;
float F2 = 103.0;
float Gb2 = 109.0;
float G2 = 115.0;
float Ab2 = 121.0;
float A_2 = 128.0;
float Bb2 = 135.0;
float B2 = 142.0;
float C3 = 149.0;
float Db3 = 157.0;
float D3 = 165.0;
float Eb3 = 173.0;
float E3 = 182.0;
float F3 = 191.0;

byte wave;
volatile long t;
float period;
volatile float pulseWidthScaled = 0;
volatile float pulseWidth = 0;
volatile float pulseWidthMin = 0;
volatile byte direct = 0; // pulsewidth will scale down when direct = 0 and scale up when direct = 1
volatile float rate = 0;
volatile float pulseK = 0;
int PWR = 0;
int trg = 1;
float freq = 0.0;

void setup() {
pinMode(0,INPUT_PULLUP); //18 keys with internal pullups enabled
pinMode(1,INPUT_PULLUP);
pinMode(2,INPUT_PULLUP);
pinMode(3,INPUT_PULLUP);
pinMode(4,INPUT_PULLUP);
pinMode(5,INPUT_PULLUP);
pinMode(6,INPUT_PULLUP);
pinMode(7,INPUT_PULLUP);
pinMode(8,INPUT_PULLUP);
pinMode(9,INPUT_PULLUP);
pinMode(10,INPUT_PULLUP);
pinMode(11,INPUT_PULLUP);
pinMode(12,INPUT_PULLUP);

pinMode(A1,INPUT_PULLUP);
pinMode(A2,INPUT_PULLUP);
pinMode(A3,INPUT_PULLUP);
pinMode(A4,INPUT_PULLUP);
pinMode(A5,INPUT_PULLUP);
pinMode(13,OUTPUT); //audio output
pinMode(A0,OUTPUT); //trigger output
delay(50);

TCCR1B = 0; //set entire TCCR1B register to 0
TCCR1B |= (1 &lt;&lt; WGM12); //turn on CTC mode
TCCR1B |= (1 &lt;&lt; CS10); // Set CS10 bit for 0 prescaler
TIMSK1 |= (1 &lt;&lt; OCIE1A); // enable timer compare interrupt
}

ISR(TIMER1_COMPA_vect){
if (t &lt; pulseWidthScaled) {
wave = B111111; 
}
else{
wave = B011111; 
}
t +=1;
if (t &gt;= period){ //Check Period and Adjust Pulse Width
t = 0;
if(direct == 0){
if(pulseWidthScaled &lt;= pulseWidthMin){
direct = 1;
pulseWidthScaled = pulseWidthMin + rate;
}
else{
pulseWidthScaled = pulseWidthScaled - rate;
}
}
if(direct == 1){
if(pulseWidthScaled &gt;= pulseWidth){
direct = 0;
pulseWidthScaled = pulseWidth - rate;
}

else{
pulseWidthScaled = pulseWidthScaled + rate;
}
}
}
PORTB = wave; //PORTB manipulation to produce audio output
}

void loop() {
rate = (pulseK*period/40000); //sets PWM speed, 40000 sounds nice
if(digitalRead(A5)==LOW){ //look for key press
if(freq != F3) //these six lines of code generate the trigger pulse
trg = 1;
if(trg == 1)
digitalWrite(A0, HIGH);
digitalWrite(A0, LOW);
trg = 0;
freq = F3; 
period = 50000/freq; 
pulseWidth = period * 0.5;
pulseWidthMin = period * 0.2;
pulseK = pulseWidth - pulseWidthMin;
}
else if(digitalRead(A4)==LOW){
if(freq != E3)
trg = 1;
if(trg == 1)
digitalWrite(A0, HIGH);
digitalWrite(A0, LOW);
trg = 0;
freq = E3;
period = 50000/freq;
pulseWidth = period * 0.5;
pulseWidthMin = period * 0.2;
pulseK = pulseWidth - pulseWidthMin;
}
else if(digitalRead(A3)==LOW){
if(freq != Eb3)
trg = 1;
if(trg == 1)
digitalWrite(A0, HIGH);
digitalWrite(A0, LOW);
trg = 0;
freq = Eb3;
period = 50000/freq;
pulseWidth = period * 0.5;
pulseWidthMin = period * 0.2;
pulseK = pulseWidth - pulseWidthMin;
}
else if(digitalRead(A2)==LOW){

if(freq != D3)
trg = 1;
if(trg == 1)
digitalWrite(A0, HIGH);
digitalWrite(A0, LOW);
trg = 0;
freq = D3;
period = 50000/freq;
pulseWidth = period * 0.5;
pulseWidthMin = period * 0.2;
pulseK = pulseWidth - pulseWidthMin;
}

//this is so tiresome i wish i could sleep

else if(digitalRead(A1)==LOW){
if(freq != Db3)
trg = 1;
if(trg == 1)
digitalWrite(A0, HIGH);
digitalWrite(A0, LOW);
trg = 0;
freq = Db3;
period = 50000/freq;
pulseWidth = period * 0.5;
pulseWidthMin = period * 0.2;
pulseK = pulseWidth - pulseWidthMin;
}
else if(digitalRead(12)==LOW){
if(freq != C3)
trg = 1;
if(trg == 1)
digitalWrite(A0, HIGH);
digitalWrite(A0, LOW);
trg = 0;
freq = C3;
period = 50000/freq;
pulseWidth = period * 0.5;
pulseWidthMin = period * 0.2;
pulseK = pulseWidth - pulseWidthMin;
}
else if(digitalRead(11)==LOW){
if(freq != B2)
trg = 1;
if(trg == 1)
digitalWrite(A0, HIGH);
digitalWrite(A0, LOW);
trg = 0;
freq = B2;
period = 50000/freq;
pulseWidth = period * 0.5;
pulseWidthMin = period * 0.2;
pulseK = pulseWidth - pulseWidthMin;
}
else if(digitalRead(10)==LOW){
if(freq != Bb2)
trg = 1;
if(trg == 1)
digitalWrite(A0, HIGH);
digitalWrite(A0, LOW);

//anwli khedam f drb ghllf w79 rb but i think we gotta change this shit i pulled most of it online and didnt bother renaming shit

trg = 0;
freq = Bb2;
period = 50000/freq;
pulseWidth = period * 0.5;
pulseWidthMin = period * 0.2;
pulseK = pulseWidth - pulseWidthMin;
}
else if(digitalRead(9)==LOW){
if(freq != A_2)
trg = 1;
if(trg == 1)
digitalWrite(A0, HIGH);
digitalWrite(A0, LOW);
trg = 0;
freq = A_2;
period = 50000/freq;
pulseWidth = period * 0.5;
pulseWidthMin = period * 0.2;
pulseK = pulseWidth - pulseWidthMin;
}
else if(digitalRead(8)==LOW){
if(freq != Ab2)
trg = 1;
if(trg == 1)
digitalWrite(A0, HIGH);
digitalWrite(A0, LOW);
trg = 0;
freq = Ab2;
period = 50000/freq;
pulseWidth = period * 0.5;
pulseWidthMin = period * 0.2;
pulseK = pulseWidth - pulseWidthMin;
}
else if(digitalRead(7)==LOW){
if(freq != G2)
trg = 1;
if(trg == 1)
digitalWrite(A0, HIGH);
digitalWrite(A0, LOW);
trg = 0;
freq = G2;
period = 50000/freq;
pulseWidth = period * 0.5;
pulseWidthMin = period * 0.2;
pulseK = pulseWidth - pulseWidthMin;
}
else if(digitalRead(6)==LOW){
if(freq != Gb2)
trg = 1;
if(trg == 1)
digitalWrite(A0, HIGH);
digitalWrite(A0, LOW);
trg = 0;
freq = Gb2;
period = 50000/freq;
pulseWidth = period * 0.5;

pulseWidthMin = period * 0.2;
pulseK = pulseWidth - pulseWidthMin;
}

//HEEEEEEEEEELP

else if(digitalRead(5)==LOW){
if(freq != F2)
trg = 1;
if(trg == 1)
digitalWrite(A0, HIGH);
digitalWrite(A0, LOW);
trg = 0;
freq = F2;
period = 50000/freq;
pulseWidth = period * 0.5;
pulseWidthMin = period * 0.2;
pulseK = pulseWidth - pulseWidthMin;
}
else if(digitalRead(4)==LOW){
if(freq != E2)
trg = 1;
if(trg == 1)
digitalWrite(A0, HIGH);
digitalWrite(A0, LOW);
trg = 0;
freq = E2;
period = 50000/freq;
pulseWidth = period * 0.5;
pulseWidthMin = period * 0.2;
pulseK = pulseWidth - pulseWidthMin;
}

//ok ginkoe helped at last

else if(digitalRead(3)==LOW){
if(freq != Eb2)
trg = 1;
if(trg == 1)
digitalWrite(A0, HIGH);
digitalWrite(A0, LOW);
trg = 0;
freq = Eb2;
period = 50000/freq;
pulseWidth = period * 0.5;
pulseWidthMin = period * 0.2;
pulseK = pulseWidth - pulseWidthMin;
}
else if(digitalRead(2)==LOW){
if(freq != D2)
trg = 1;
if(trg == 1)
digitalWrite(A0, HIGH);
digitalWrite(A0, LOW);
trg = 0;
freq = D2;
period = 50000/freq;
pulseWidth = period * 0.5;
pulseWidthMin = period * 0.2;
pulseK = pulseWidth - pulseWidthMin;
}
else if(digitalRead(1)==LOW){

if(freq != Db2)
trg = 1;
if(trg == 1)
digitalWrite(A0, HIGH);
digitalWrite(A0, LOW);
trg = 0;
freq = Db2;
period = 50000/freq;
pulseWidth = period * 0.5;
pulseWidthMin = period * 0.2;
pulseK = pulseWidth - pulseWidthMin;
}
else if(digitalRead(0)==LOW){
if(freq != C2)
trg = 1;
if(trg == 1)
digitalWrite(A0, HIGH);
digitalWrite(A0, LOW);
trg = 0;
freq = C2;
period = 50000/freq;
pulseWidth = period * 0.5;
pulseWidthMin = period * 0.2;
pulseK = pulseWidth - pulseWidthMin;
}
else{ //if no key is pressed, no output
freq = 0;
period = 0;
pulseWidth = period * 0.5;
pulseWidthMin = period * 0.2;
pulseWidthScaled = 0;
pulseK = pulseWidth - pulseWidthMin;
}
}

//what a good cute final else to end this fucking mess with and istg i refuse to fucking stylize all that shit fuck you and fuck your mom and fuck prof and fuck musk and fuck jk rowling and fuck my dad and fuck your dad and fuck anyone who does not give me money for free daily i hope i could just die instead of go through this fucking mess every single day. go back to line 200