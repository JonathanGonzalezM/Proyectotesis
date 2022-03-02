//incluir librerias necesarias para el sistema
#include <Arduino.h>
#include <ESP32Time.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Proporcione la información del proceso de generación del token.
#include "addons/TokenHelper.h"
//Proporcione la información de impresión de la carga útil de RTDB y otras funciones auxiliares.
#include "addons/RTDBHelper.h"

// Inserte sus credenciales de red
#define WIFI_SSID "FAMILIA GONZALEZ MENDOZA"
#define WIFI_PASSWORD "22051998@"

//clave API
#define API_KEY "AIzaSyClhRCEpeK7i9SyLUYdUs0ggRmqXWj6w9k"

//URL de base de datos
#define DATABASE_URL "https://semaforointeligenteproyecto-default-rtdb.firebaseio.com/"

#define CARPETA1 "/autos/ida/"
#define CARPETA2 "/autos/vuelta/"

//valores definidos para la ruta en la case de datos de firebase de los autos de ida
#define ENERO1      "/Enero/autos/ida/"
#define FEBRERO1    "/Febrero/autos/ida/"
#define MARZO1      "/Marzo/autos/ida/"
#define ABRIL1      "/Abril/autos/ida/"
#define MAYO1       "/Mayo/autos/ida/"
#define JUNIO1      "/Junio/autos/ida/"
#define JULIO1      "/Julio/autos/ida/"
#define AGOSTO1     "/Agosto/autos/ida/"
#define SEPTIEMBRE1 "/Septiembre/autos/ida/"
#define OCTUBRE1    "/Octubre/autos/ida/"
#define NOVIEMBRE1  "/Noviembre/autos/ida/"
#define DICIEMBRE1  "/Diciembre/autos/ida/"

//valores definidos para la ruta en la case de datos de firebase
#define ENERO2      "/Enero/autos/vuelta/"
#define FEBRERO2    "/Febrero/autos/vuelta/"
#define MARZO2      "/Marzo/autos/vuelta/"
#define ABRIL2      "/Abril/autos/vuelta/"
#define MAYO2       "/Mayo/autos/vuelta/"
#define JUNIO2      "/Junio/autos/vuelta/"
#define JULIO2      "/Julio/autos/vuelta/"
#define AGOSTO2     "/Agosto/autos/vuelta/"
#define SEPTIEMBRE2 "/Septiembre/autos/vuelta/"
#define OCTUBRE2    "/Octubre/autos/vuelta/"
#define NOVIEMBRE2 "/Noviembre/autos/vuelta/"
#define DICIEMBRE2  "/Diciembre/autos/vuelta/"

//Definir objeto de datos de Firebase
FirebaseData fbdo;

//Definir las variables de autenticación
FirebaseAuth auth;
FirebaseConfig config;

// definir variables
unsigned long sendDataPrevMillis = 0;
unsigned long s=0;
unsigned long ss=0;
unsigned long s1=0;
unsigned long s2=0;
unsigned long s11=0;
unsigned long s22=0;
int count = 1;
int count2 = 1;
bool signupOK = false;

//sensor 1 
const int Trigger1 = 2;   //Pin digital 2 para el Trigger del sensor
const int Echo1 = 0;   //Pin digital 0 para el Echo del sensor

//sensor 2
const int Trigger2 = 32;   //Pin digital 32 para el Trigger del sensor
const int Echo2 = 35;   //Pin digital 33 para el Echo del sensor

ESP32Time rtc; // variable para el formato fecha

void setup(){
  //conectar al router (INTERNET)
  
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  //iniciar fecha y hora
  rtc.setTime(50,58,23,31,01,2022); // segundos-minutos-horas-dia-mes-año
  
  // Asigne la clave api (obligatorio) 
  config.api_key = API_KEY;

  // Asigne la URL de RTDB (obligatorio)
  config.database_url = DATABASE_URL;

  // ingresar
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

    // Asigne la función de devolución de llamada para la tarea de generación de tokens de ejecución prolongada 
  config.token_status_callback = tokenStatusCallback; // ver complementos/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  //activar pines del sensor 1
  pinMode(Trigger1, OUTPUT); //pin como salida
  pinMode(Echo1, INPUT);  //pin como entrada
  digitalWrite(Trigger1, LOW);//Inicializamos el pin con 0:

  //activar pines del sensor 2
  pinMode(Trigger2, OUTPUT); //pin como salida
  pinMode(Echo2, INPUT);  //pin como entrada
  digitalWrite(Trigger2, LOW);//Inicializamos el pin con 0:
  
}

//Metodo de recoleccion de datos sensor 1
int sensor1(int valor){
  digitalWrite(Trigger1, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger1, LOW);
  int distancia1 = pulseIn(Echo1, HIGH); //obtenemos el ancho del pulso
  distancia1 = distancia1/valor;
  return distancia1;
}

//Metodo de recoleccion de datos sensor 2
int sensor2(int valor){
  digitalWrite(Trigger2, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger2, LOW);
  int distancia2 = pulseIn(Echo2, HIGH); //obtenemos el ancho del pulso
  distancia2 = distancia2/valor;
  return distancia2;
}

void loop(){
    //variables para recibir datos de fecha y hora
    int d1 = rtc.getDay();
    int h1 = rtc.getHour();
    int m1 = rtc.getMinute();
    int s1 = rtc.getSecond();
    
    const int divisor = 59;       // variable divisible para sensor (convertir a centimetros)
    int dis1 = sensor1(divisor);  // variable recibida del sensor 1 (centimetros)
    Serial.println(dis1);         // mostrar distancia en la serial (sensro1)
    
    int dis2 = sensor2(divisor);  // variable recibida del sensor 2 (centimetros)
    Serial.println(dis2);         // mostrar distancia en la serial (sensro2)

    //condiciones para ingresar a la base de datos de Firebase
    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1 || sendDataPrevMillis == 0)){
      //condicion para reiniciar el conteo cada que inicie un nuevo mes
      if(d1==01 && h1==00 && m1==00 && s1==01){
        count = 1;
        count2 = 1;
        }   
        
      sendDataPrevMillis=millis();
      //condicion para esperar 0.5 segundos
      if(sendDataPrevMillis >= (s1+250)){
        s1=sendDataPrevMillis;
        
        //ciclo para evaluar si esta en el rango de 11cm o inferior
        while(dis1<=11){
          const int divisor = 59;          
          int dis = sensor1(divisor); // variable recibida del sensor 1 (centimetros)
          
          //condicion para evaluar que la distacia sea 11cm o superior 
          if(dis>11){
            
            // condición para enviar el dato del contador iniciando en 1
            if (Firebase.RTDB.setInt(&fbdo, CARPETA1, count)){
            Serial.println("PASSED");            
            }
            else {
              Serial.println("FAILED");
            }
            
            mesesIda();             // metodo para aguardar los datos por meses
            count++;                // Contador
            sendDataPrevMillis =0;
            break;                  //terminar el ciclo
          }        
        }
      }
              
      if(sendDataPrevMillis>= (s2+250)){   
        s2=sendDataPrevMillis;   
        while(dis2<=11){
          const int divisor = 59;
          int dis = sensor2(divisor);
          if(dis>11){
            if (Firebase.RTDB.setFloat(&fbdo, CARPETA2, count2)){
                Serial.println("PASSED");
              }
              else {
                Serial.println("FAILED");
              }
              mesesVuelta();
              count2++; 
              sendDataPrevMillis =0;
              break;
          }
        }
      }
  }
}

//metodo para almacenar los datos por meses
void mesesIda(){
  int Enero;
  int Febrero;
  int Marzo;
  int Abril;
  int Mayo;
  int Junio;
  int Julio;
  int Agosto;
  int Septiembre;
  int Octubre;
  int Noviembre;
  int Diciembre;
  
  int mes = rtc.getMonth();
  Serial.println(rtc.getDateTime(true)); 
  // interruptor que recibira el mes en numero, para guardar la variable contador por mes
  switch (mes){
    case 0:
      Enero = count; //guardar variable count en la variable Enero
      //condicion para guardar datos en Firebase
      if (Firebase.RTDB.setInt(&fbdo, ENERO1, Enero)){} 
        break; //interrumpir el proceso y salir de switch
    case 1:
      Febrero = count;
      if (Firebase.RTDB.setInt(&fbdo, FEBRERO1, Febrero)){}
        break;
     case 2:
     Marzo = count;
     if (Firebase.RTDB.setInt(&fbdo, MARZO1, Marzo)){}
        break;
    case 3:
      Abril = count;
      if (Firebase.RTDB.setInt(&fbdo, ABRIL1, Abril)){}
        break;
    case 4:
      Mayo = count;
      if (Firebase.RTDB.setInt(&fbdo, MAYO1, Mayo)){}
        break;
    case 5:
      Junio = count;
      if (Firebase.RTDB.setInt(&fbdo, JUNIO1, Junio)){}
        break;
     case 6:
     Julio = count;
      if (Firebase.RTDB.setInt(&fbdo, JULIO1, Julio)){}
        break;
    case 7:
      Agosto = count;
      if (Firebase.RTDB.setInt(&fbdo, AGOSTO1, Agosto)){}
        break;
     case 8:
      Septiembre = count;
      if (Firebase.RTDB.setInt(&fbdo, SEPTIEMBRE1, Septiembre)){}
        break;
    case 9:
      Octubre = count;
      if (Firebase.RTDB.setInt(&fbdo, OCTUBRE1, Octubre)){}
        break;
     case 10:
      Noviembre = count;
      if (Firebase.RTDB.setInt(&fbdo, NOVIEMBRE1, Noviembre)){}
        break;
    case 11:
      Diciembre = count;
      if (Firebase.RTDB.setInt(&fbdo, DICIEMBRE1, Diciembre)){} 
        break;
  }  
}

void mesesVuelta(){
  int Eneroi;
  int Febreroi;
  int Marzoi ;
  int Abrili;
  int Mayoi;
  int Junioi;
  int Julioi;
  int Agostoi;
  int Septiembrei;
  int Octubrei;
  int Noviembrei;
  int Diciembrei;

  int mes = rtc.getMonth();
  Serial.println(mes);
    Serial.println(rtc.getDateTime(true));
  switch (mes){
    case 0:
      Eneroi = count2;
      if (Firebase.RTDB.setInt(&fbdo, ENERO2, Eneroi)){}
        break;
    case 1:
      Febreroi = count2; 
      if (Firebase.RTDB.setInt(&fbdo, FEBRERO2, Febreroi)){}
        break;
     case 2:
      Marzoi = count2;
      if (Firebase.RTDB.setInt(&fbdo, MARZO2, Marzoi)){}
        break;
    case 3:
      Abrili = count2;
      if (Firebase.RTDB.setInt(&fbdo, ABRIL2, Abrili)){}
        break;
    case 4:
      Mayoi = count2;
      if (Firebase.RTDB.setInt(&fbdo, MAYO2, Mayoi)){}
        break;
    case 5:
      Junioi = count2;
      if (Firebase.RTDB.setInt(&fbdo, JUNIO2, Junioi)){}
        break;
     case 6:
      Julioi = count2;
      if (Firebase.RTDB.setInt(&fbdo, JULIO2, Julioi)){}
        break;
    case 7:
      Agostoi = count2;
      if (Firebase.RTDB.setInt(&fbdo, AGOSTO2, Agostoi)){}
        break;
     case 8:
      Septiembrei = count2;
      if (Firebase.RTDB.setInt(&fbdo, SEPTIEMBRE2, Septiembrei)){}
        break;
    case 9:
      Octubrei = count2; 
      if (Firebase.RTDB.setInt(&fbdo, OCTUBRE2, Octubrei)){}
        break;
     case 10:
      Noviembrei = count2
      if (Firebase.RTDB.setInt(&fbdo, NOVIEMBRE2, Noviembrei)){}
        break;
    case 11:
      Diciembrei = count2;
      if (Firebase.RTDB.setInt(&fbdo, DICIEMBRE2, Diciembrei)){} 
        break;
  }  
}
