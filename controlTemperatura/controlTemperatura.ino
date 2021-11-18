#define DEBUG(a) Serial.println(a);

// CONTROL DE TEMPERATURA POR ARDUINO

// Esta variable será 0 si la clave ingresada en la app es incorrecta y cambiará a 1 cuando sea correcta. El cambio se realizará en la 1ra fase del loop().
int estadoAcceso=0;

// La variable temperatura estará en el sistema decimal, y luego se cambiará de binario para mostrarse en los leds
int temperatura;

void setup() {

  Serial.begin(9600);
  
  //Digitos del número en binario
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  //Leds de control
  pinMode(8, OUTPUT); //verde
  pinMode(9, OUTPUT); //rojo
  
}


// Funciones que usaremos: Binario, RojoVerde y BajarTemperatura.
 void Binario(int temperatura){
  int a=0, b=0, c=0, d=0, e=0;
      if (temperatura>=16){
        a=1;
        digitalWrite(2, HIGH);
      }
      if (temperatura>=8){
        b=1;
        digitalWrite(3, HIGH);
      }
      if (temperatura>=4){
        c=1;
        digitalWrite(4, HIGH);
      }
      if (temperatura>=2){
        d=1;
        digitalWrite(5, HIGH);
      }
      if (temperatura>=1){
        e=1;
        digitalWrite(6, HIGH);
      } 
 }

void RojoVerde (int temperatura){
  if (temperatura>27){
        digitalWrite(9, HIGH); //led rojo
      }else{
        digitalWrite(8, HIGH); //led verde
      }
}

void BajarTemperatura(int temperatura){
  if (temperatura>27){
       if (Serial.available()){
          String lectura=Serial.readStringUntil('\n');
          if(lectura.equals("BAJAR X")){
            temperatura=random(0,31);
            RojoVerde(temperatura);
            Binario(temperatura);
            DEBUG(lectura);
          }
       }
   }
}
 
void loop() {

  //1RA FASE
  //En esta fase se recibe la clave desde la app y el estadoAcceso debe cambiar de 0 a 1 si fue correcta.

  //2DA FASE
  if (estadoAcceso=1){
    
    while(true){
      //todos los leds apagados para empezar una nueva medición
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      
      temperatura=random(0,31);
      Serial.println(temperatura);
      RojoVerde(temperatura);

      // Convertimos a binario
      Binario(temperatura);

      // Bajar la temperatura (en caso sea necesario)
      BajarTemperatura(temperatura);

      //Cada 5 seg se hará una nueva medición
      delay(5000);
     }  
  
  }
}
