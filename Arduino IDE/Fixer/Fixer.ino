#define sensor A0 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)

#define bufSize 500
unsigned int valuesBuffer[bufSize]; 

void printAvgBuffer();
int bufIndex;

void setup() {
  Serial.begin(115200); // start the serial port
  int bufIndex = 0;
}

void loop() {  
  unsigned int val = analogRead(A0);
  valuesBuffer[bufIndex] = val;
  bufIndex = (bufIndex + 1) % (bufSize + 1);
  if(bufIndex == bufSize){
    printAvgBuffer();
  }
}


void printAvgBuffer(){
  int avg = 0;
  int sum = 0;
  for(int i = 0; i < bufSize; i++){
    sum += valuesBuffer[i];
  }
  avg = sum / bufSize;
  Serial.println(avg);
}
