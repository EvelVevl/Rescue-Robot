const int pin = A0;  
const int LeftIn1 = 9;
const int LeftIn2 = 8;
const int RightIn1 = 7;
const int RightIn2 = 6; 
const int trig = 5;
const int echo = 4;

void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  Serial.begin(9600); 


//want to get 5 readings with delay of 100 milliseconds inbetween them and then average them to get the threshold
 threshold();
}
void loop()
{
 float val;
 float threshold;
 val = analogRead(pin);  
 long duration, cm;

//first if statement to turn on ultrasonic sensor if detects noise of over 10 (may need to ajust later on)
   if (val > 10 + threshold)
  {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimetres(duration);
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();  
  delay(100);
   } 
   else 
   {
    digitalWrite(echo, LOW);
    digitalWrite(trig, LOW);
   }
   
// second if statement to turn on wheels if detects something 50 cm infront of it
  if (cm <= 50){
   digitalWrite(LeftIn1, LOW);
   digitalWrite(LeftIn2, HIGH);
   digitalWrite(RightIn1, LOW);
   digitalWrite(RightIn2, HIGH);
  }else{
    digitalWrite(LeftIn1, LOW);
    digitalWrite(LeftIn2, LOW);
    digitalWrite(RightIn1, LOW);
    digitalWrite(RightIn2, LOW);
  }
        
      Serial.println(val,DEC);//print the sound value to serial
      delay(100);
}

long microsecondsToCentimetres(long microseconds)
{
  return microseconds / 29 / 2;
}


void threshold(){
  int read1 = analogRead(pin);
  delayMicroseconds(100);
  int read2 = analogRead(pin);
  delayMicroseconds(100);
  int read3 = analogRead(pin);
  delayMicroseconds(100);
  int read4 = analogRead(pin);
  delayMicroseconds(100);
  int read5 = analogRead(pin);
  delayMicroseconds(100);
  //averaging 
  float threshold = ((read1 + read2 + read3 + read4 + read5)/5);
  Serial.print("threshold ");
  Serial.print(threshold);

  return threshold;
}
