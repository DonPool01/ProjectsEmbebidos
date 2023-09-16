#include <Arduino.h>
#include <WiFi.h>

const char * SSID = "Aguapanela";
const char * PASS = "Pamelachu";
const char * HOST = "www.google.com";
const int PORT = 80; //puerto por defecto

// funcion que inicializa el dispositivo, velocidad del puerto serial, direcciones d epines I/O, objetos que representen sensores.
void setup() {
  Serial.begin(115200);
  WiFi.begin(SSID,PASS);//se inicializa el modulo wifi y se vincula a red indicada SSID
  Serial.print("Intentando conexion");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Conectado Bebe");
  Serial.printf("Direccion Ip: ");
  Serial.println(WiFi.localIP());

  pinMode(2, OUTPUT);//configuramos el pin 2 como salida
  digitalWrite(2, HIGH);//encendemos el led
}

void loop() {

WiFiClient clientes; //objeto que realiza peticiones a un socket servidor
if (!clientes.connect(HOST,PORT)){
  Serial.println("Conexion fallida al servidor");
  delay(1000);
  return;
}

//si llega a esta linea es pq si hubo conexion con el servidor
//ahora tenemos un flujo de transmision y otro de recepcion

String Request = String ("GET / HTTP/1.1\r\n") + "Host: " + HOST + "\r\n" + "Connection: close\r\n\r\n";//parametro de cabecera
// enviamos la peticion a el protocolo HTTP al servidor

clientes.print(Request);
unsigned long inicio = millis();
while (clientes.available() == 0)
{
  if (millis()- inicio > 5000)
  {
    Serial.println("Tiempo de espera del servidor agotado");
    clientes.stop();
    return ;
  }
  
}
// si se llega a este punto es porque se recibieron datos del servidor (clientes.available() !=0)

while (clientes.available())
{
  String linea = clientes.readStringUntil('\r');// leer string hasta encontrar el caracter enter
  Serial.println(linea);
}
Serial.println("Fin de conexion al servidor");
clientes.stop();
delay(5000);// evitar muchas peticiones al servidor y nos pongan en un black list
/*
  delay(500);
  digitalWrite(2, LOW);
  delay(500);
  digitalWrite(2, HIGH);
*/  
}

