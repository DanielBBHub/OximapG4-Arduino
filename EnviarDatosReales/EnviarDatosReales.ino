
//Libreria
#include <bluefruit.h>

int Vgas = A3;
int Vref = A4;
int Vtemp = A5;


int Vgas_value = 0;
int Vref_value = 0;
int Vtemp_value = 0;

int i = 0;
float suma = 0;
float media = 0;

void setup() {
  
  Serial.begin(115200); //Inicializamos el Serial
  
  Bluefruit.begin(); //Inicializamos el modulo del micro

  Serial.println("PRUEBAS iBeacon"); 

  Serial.println("El nombre del iBeacon es BeaconRuben"); 
  Bluefruit.setName("BeaconRuben"); //Nombre del ibeacon enviado
  Bluefruit.ScanResponse.addName(); 

  
 
  
}//setup()

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

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
  BLEBeacon elBeacon( beaconUUID, Vgas_value, media, 73 );
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

namespace Loop {
   int cont = 0;
};

void loop() {
  
  using namespace Loop; 

  cont++; //Incrementamos el contador

  Vgas_value = analogRead(Vgas); //Leemos el sensor de gas
  Serial.print("Vgas_value: ");
  Serial.println(Vgas_value);

  Vref_value = analogRead(Vref);
  //Serial.print("Vref_value: ");
  //Serial.println(Vref_value);

  Vtemp_value = analogRead(Vtemp);
  //Serial.print("Vtemp_value: ");
  //Serial.println(Vtemp_value);

  suma += Vgas_value;

  media = suma/i;

  Serial.print("Media: ");
  Serial.println(media);

  i++;

  starAdvertising(); //Llamada a la función

  delay(1000);
  Serial.print( "Tiempo entre Beacons enviados:" );
  Serial.println( cont );

}//loop