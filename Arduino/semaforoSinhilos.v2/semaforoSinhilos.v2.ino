// Pines utilizados
//Semaforo 1-2-3
#define LEDVERDE1 2
#define LEDAMARILLO1 3
#define LEDROJO1 4
#define LEDVERDE2 5
#define LEDAMARILLO2 6
#define LEDROJO2 7

const int Trigger = 11;   //Pin digital 2 para el Trigger del sensor
const int Echo = 12;   //Pin digital 3 para el Echo del sensor

int tiempoCambio = 5000; // Tiempo de espera entre transición de LEDs
int tiempoEspera = 25000; // Tiempo de espera hasta comenzar transición
int tiempoSensor = 10000;

void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
 
 // Modo entrada/salida de los pines
 //Semaforo 1-2-3
  pinMode(LEDVERDE1, OUTPUT);
  pinMode(LEDAMARILLO1, OUTPUT);
  pinMode(LEDROJO1, OUTPUT);
  pinMode(LEDVERDE2, OUTPUT);
  pinMode(LEDAMARILLO2, OUTPUT);
  pinMode(LEDROJO2, OUTPUT);

  // Apagamos todos los LEDs
  digitalWrite(LEDVERDE1, LOW);
  digitalWrite(LEDAMARILLO1, LOW);
  digitalWrite(LEDROJO1, LOW);
  digitalWrite(LEDVERDE2, LOW);
  digitalWrite(LEDAMARILLO2, LOW);
  digitalWrite(LEDROJO2, LOW);

  // Estado inicial: semáforo 1 abierto, semáforo 2 cerrado
  digitalWrite(LEDVERDE1, HIGH);
  digitalWrite(LEDROJO2, HIGH);  
}

void loop() { 
  FuncionamientoSemaforo();  
}

int sensor(int valor){
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  int distancia = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  distancia = distancia/valor;
  return distancia;
}


void SemaforoP1(){
  // Apagamos semáforo 1
  // Esperamos
  delay(tiempoEspera);
 // Pasamos a luz amarilla
  digitalWrite(LEDVERDE1, LOW);
  digitalWrite(LEDAMARILLO1, HIGH);
  // Esperamos
  delay(tiempoCambio);
  // Pasamos a luz roja
  digitalWrite(LEDAMARILLO1, LOW);
  digitalWrite(LEDROJO1, HIGH);
  // Pasamos a luz amarilla
  digitalWrite(LEDROJO2, LOW);
  digitalWrite(LEDVERDE2, HIGH);
  // Apagamos semáforo 2
  // Esperamos
  delay(tiempoSensor);
}

void SemaforoP2(){
  digitalWrite(LEDVERDE2, LOW);
  digitalWrite(LEDAMARILLO2, HIGH);
  // Esperamos
  delay(tiempoCambio);
  // Pasamos a luz roja
  digitalWrite(LEDAMARILLO2, LOW);
  digitalWrite(LEDROJO2, HIGH);
  // Pasamos a luz amarilla
  digitalWrite(LEDROJO1, LOW);
  digitalWrite(LEDVERDE1, HIGH);
}

void FuncionamientoSemaforo(){
  do{
  SemaforoP1();
  int dis;
  int c = 0;
    while(c < 10){
      const int divisor = 59;
      int dis = sensor(divisor);
      Serial.println(dis);
      delay(1000);
      c++;
      if(dis<=20 && digitalRead(LEDVERDE1)== LOW){         
          SemaforoP2();
          c=10;
      }
    }
  if(digitalRead(LEDVERDE2)== HIGH){  
    SemaforoP2();
  } 
  }while(true);
}
