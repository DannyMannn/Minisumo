const int SENSOR_IR1 = A0;
int lectura_ir1 = 0; // lectura del sensor IR1

const int SENSOR_IR2 = A1;
int lectura_ir2 = 0; // lectura del sensor IR2

// MOTORES conectados al puente H
int izqA = 3;
int izqB = 5;
int derA = 6;
int derB = 9;

// SENSORQTR
const int ECHO = 10;
const int TRIG = 11;
int duracion, distancia;

const int SPEED = 255;

void setup(){
    Serial.begin(9600);
    delay (5000); // TIEMPO DE SEGURIDAD

    //sesnor ultrasonico
    pinMode(ECHO, INPUT);
    pinMode(TRIG, OUTPUT);

    //motores
    pinMode(derA, OUTPUT);
    pinMode(derB, OUTPUT);
    pinMode(izqA, OUTPUT);
    pinMode(izqB, OUTPUT);
}


void loop(){
    //lectura de sesnores IR
    lectura_ir1 = digitalRead(SENSOR_IR1);
    lectura_ir1 = digitalRead(SENSOR_IR1);
    delay(10);

    // DEBUG
    /*
    Serial.print("Sensor IR1: ");
    Serial.print(lectura_ir1);
    
    Serial.print("Sensor IR2: ");
    Serial.print(lectura_ir2);
    */

    /***********SENSOR QTR*************/
    digitalWrite(TRIG, HIGH);
    delay(0.01);
    digitalWrite(TRIG, LOW);
    duracion = pulseIn(ECHO, HIGH);
    distancia = (duracion / 2) / 29; //cambiar esto???
    delay(1);

    /*
    Serial.print(distancia);
    Serial.println("cm");
    */

    if(distancia <= 15){ // ATACA OPONENTE
        // MOVER HACIA ADELANTE
        forwards(SPEED);
    }
    if(distancia > 16){ // o tratar de buscar oponente?
        rotate(SPEED);
        delay(10);
    }

    /***********SENSORES IR*************/
   // MOVERSE HACIA ATRÁS SI DETECTA BLANCO
   if(lectura_ir1 == 0 || lectura_ir2 == 0){ // cambiar valores < 650 means white line???
    backwards(SPEED);
    delay(500);
   }
   else{ // do we need this?
    rotate(SPEED);
    delay(10);
   }
}

void forwards(int speed){
    analogWrite(derB, 0);
    analogWrite(izqB, 0);
    analogWrite(derA, speed);
    analogWrite(izqA, speed);
}

void backwards(int speed){
    analogWrite(derB, speed);
    analogWrite(izqB, speed);
    analogWrite(derA, 0);
    analogWrite(izqA, 0);
}

void rotate(int speed){
    analogWrite(derB, speed);
    analogWrite(izqB, 0);
    analogWrite(derA, 0);
    analogWrite(izqA, speed);
}

void stop(){
    analogWrite(derB, 0);
    analogWrite(izqB, 0);
    analogWrite(derA, 0);
    analogWrite(izqA, 0);
}