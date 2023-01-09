
//Libreria
#include <bluefruit.h>

int Vgas = A3;
int Vref = A4;
int Vtemp = A5;

float relacionV = 3.3/4096;

float Vgas_value = 0;
float Vref_value = 0;
float Vtemp_value = 0;

int i = 0;
float suma = 0;
float media = 0;

int cont = 0;
int contador_total = 0;

double M = 0;
double C = 0;

int contador_muestras = 0;

void setup() {
  
  Serial.begin(115200); //Inicializamos el Serial
  
  Bluefruit.begin(); //Inicializamos el modulo del micro

  Serial.println("PRUEBAS iBeacon"); 

  Serial.println("El nombre del iBeacon es BeaconRuben"); 
  Bluefruit.setName("Oximap"); //Nombre del ibeacon enviado
  Bluefruit.ScanResponse.addName(); 

  analogReadResolution(12);
 
  
}//setup()

/*-------------------------------------------------------------------------------------------------
En la funcion starAdvertising() configuramos muestro beacon, anadiendo una uuid personalizada para
que sea mas facil de reconocer en la app.
Tambien se le pasan los valores de la medicion de gas y de la media de dichas mediciones como minor
y manor
*/-------------------------------------------------------------------------------------------------
void starAdvertising(){

  //Advertising packet
  Bluefruit.Advertising.stop();
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addName(); //Se añade el nombre al beacon

  //Creamos el uuid del beacon 
  Serial.println( "Creamos el Beacon");
  uint8_t beaconUUID[16] = {
     'O', 'X', 'I', 'M', 'A', 'P', 'G', '4',
     '_', 'S', 'P', 'R', 'I', 'N', 'T', '1'
     };

  //Le asignamos el mayor y minor para reconocer nuestro beacon
  BLEBeacon elBeacon( beaconUUID, C, contador_muestras, 73 );
  elBeacon.setManufacturer( 0x004c ); 
  Bluefruit.Advertising.setBeacon( elBeacon );

  //Advertising pack
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds

  
}//startAdvertising()

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------


/*-------------------------------------------------------------------------------------------------
En el loop recogemos en variables los datos obtenidos del sensor y realizamos una media con ellos,
además se llama a la funcion starAdvertising()
*/-------------------------------------------------------------------------------------------------
void loop() {
  

  Vgas_value = analogRead(Vgas); //Leemos el sensor de gas
  Vref_value = analogRead(Vref);
  Vtemp_value = analogRead(Vtemp);

  suma += Vgas_value;

  media = suma/i;

  i++;

  cont++; //Incrementamos el contador

  M = 41 * 499 * pow(10,-9) *pow(10,3);

  C = 1/ M * (Vgas_value *relacionV - Vref_value *relacionV);//valor en ppm

//mostrar en serial plotter
  Serial.print(Vgas_value*relacionV);
  Serial.print(",");
  Serial.print(Vref_value*relacionV);
  Serial.print(",");
  Serial.print(C);
  Serial.print(",");
  Serial.println(media*relacionV);

  if(cont == 20){//cuando tengo 20 muestras pongo un segundo de retardo
    cont = 0;

    if(contador_total == 5){//cuando ya han pasado 5 segundos finalizo
    
    contador_muestras++;

    starAdvertising(); 
      //abort();//finaliza la ejecución
      contador_total = 0;
    }
    contador_total++;
    delay(1000);
  }


}//loop
