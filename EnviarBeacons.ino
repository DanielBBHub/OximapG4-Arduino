//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Autor: Rubén Marín Samper
// Fecha: 08/10/2022
// Fichero: EnviarBeacons.ino
// Descripción: código para el envío de iBeacons a través del Bluetooth del microcontrolador proporcionado
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//Libreria
#include <bluefruit.h>

void setup() {
  
  Serial.begin(115200); //Inicializamos el Serial
  
  Bluefruit.begin(); //Inicializamos el modulo del micro

  Serial.println("PRUEBAS iBeacon"); 

  Serial.println("El nombre del iBeacon es BeaconRuben"); 
  Bluefruit.setName("BeaconRuben"); //Nombre del ibeacon enviado
  Bluefruit.ScanResponse.addName(); 

  
  starAdvertising(); //Llamada a la función
  
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
     'R', 'U', 'B', 'E', 'N', 'G', 'T', 'I',
     '_', 'S', 'P', 'R', 'I', 'N', 'T', '0'
     };

  //Le asignamos el mayor y minor para reconocer nuestro beacon
  BLEBeacon elBeacon( beaconUUID, 20, 02, 73 );
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

  delay(1000); // Nos esperamos un segundo

  Serial.print( "Tiempo entre Beacons enviados:" );
  Serial.println( cont );

}//loop

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
