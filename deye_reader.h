#include <ModbusMaster.h>

#define DEYE_SERIAL Serial2
#define DEYE_SLAVE_ID 1

ModbusMaster deye;

struct DeyeData {
  float grid_power;          // Puissance réseau (kW)
  float pv_power_total;      // Puissance PV totale (kW)
  float pv_power_mppt1;      // Puissance MPPT1 (kW)
  float pv_power_mppt2;      // Puissance MPPT2 (kW)
  float daily_production;    // Production journalière (kWh)
  float daily_consumption;   // Consommation journalière (kWh)
  float daily_grid;          // Import/Export journalier (kWh)
  float battery_soc;         // Niveau batterie (%)
  float battery_power;       // Puissance batterie (kW, + charge, - décharge)
  String battery_status;     // Statut batterie
};

void deye_setup() {
  DEYE_SERIAL.begin(9600, SERIAL_8N1, 16, 17); // RX, TX
  deye.begin(DEYE_SLAVE_ID, DEYE_SERIAL);
}

DeyeData read_deye_data() {
  DeyeData data;
  
  // Lecture des registres (adresses basées sur deye_hybrid.yaml)
  uint8_t result;
  uint16_t registers[32];
  
  // Lecture bloc de registres
  result = deye.readHoldingRegisters(0x100, 16);
  if (result == deye.ku8MBSuccess) {
    for (int i = 0; i < 16; i++) {
      registers[i] = deye.getResponseBuffer(i);
    }
    
    // Décodage des valeurs (exemple - ajuster selon votre modèle)
    data.grid_power = (int16_t)registers[0] * 0.1; // kW
    data.pv_power_total = (registers[1] + registers[2]) * 0.1; // kW
    data.pv_power_mppt1 = registers[1] * 0.1; // kW
    data.pv_power_mppt2 = registers[2] * 0.1; // kW
    data.daily_production = registers[3] * 0.1; // kWh
    data.daily_consumption = registers[4] * 0.1; // kWh
    data.daily_grid = (int16_t)registers[5] * 0.1; // kWh
    data.battery_soc = registers[6]; // %
    data.battery_power = (int16_t)registers[7] * 0.1; // kW
    
    // Statut batterie
    uint16_t status = registers[8];
    if (status == 1) data.battery_status = "Charge";
    else if (status == 2) data.battery_status = "Decharge";
    else data.battery_status = "Inactif";
  }
  
  return data;
}