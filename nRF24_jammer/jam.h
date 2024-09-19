void VSPI_init() {
  sp = new SPIClass(VSPI);
  sp->begin();
  radio1.begin(sp);
  radio1.setAutoAck(false);
  radio1.stopListening();
  radio1.setRetries(0, 0);
  radio1.setPALevel(RF24_PA_MAX, true);
  radio1.setDataRate(RF24_2MBPS);
  radio1.setCRCLength(RF24_CRC_DISABLED);
  radio1.startConstCarrier(RF24_PA_MAX, 80);
}
void HSPI_init() {
  hp = new SPIClass(HSPI);
  hp->begin();
  radio.begin(hp);
  radio.setAutoAck(false);
  radio.stopListening();
  radio.setRetries(0, 0);
  radio.setPALevel(RF24_PA_MAX, true);
  radio.setDataRate(RF24_2MBPS);
  radio.setCRCLength(RF24_CRC_DISABLED);
  radio.startConstCarrier(RF24_PA_MAX, 40); 
}
void bluetooth_jam(){
  HSPI_init();
  VSPI_init();
  while (true){
    if (Separate_or_together == 0){
      if (bluetooth_jam_method == 0){
        for (int i = 0; i < 22; i++) {
          radio.setChannel(bluetooth_channels[i]);
          radio1.setChannel(bluetooth_channels_reversed[i]);
        }
      }
      if (bluetooth_jam_method == 1){
        radio.setChannel(random(40));
        radio1.setChannel(random(40, 80));
      }
      if (bluetooth_jam_method == 2){
        for (int i = 0; i < 80; i++) {
          radio.setChannel(i);
          radio1.setChannel(i-79);
        }
      }
    }
    if (Separate_or_together == 1){
      if (bluetooth_jam_method == 0){
        for (int i = 0; i < 22; i++) {
          radio.setChannel(bluetooth_channels[i]);
          radio1.setChannel(bluetooth_channels[i]);
        }
      }
      if (bluetooth_jam_method == 1){
        int random_channel = random(80);
        radio.setChannel(random_channel);
        radio1.setChannel(random_channel);
      }
      if (bluetooth_jam_method == 2){
        for (int i = 0; i < 80; i++) {
          radio.setChannel(i);
          radio1.setChannel(i);
        }
      }
    }
  }
}
void drone_jam(){
  HSPI_init();
  VSPI_init();
  while (true){
    if (Separate_or_together == 0){
      if (drone_jam_method == 0){
        radio.setChannel(random(64));
        radio1.setChannel(random(64, 125));
      }
      if (drone_jam_method == 1){
        for (int i = 0; i < 125; i++){
          radio.setChannel(i);
          radio1.setChannel(i-125);
        }
      }
    }
    if (Separate_or_together == 1){
      if (drone_jam_method == 0){
        int random_channel = random(125);
        radio.setChannel(random_channel);
        radio1.setChannel(random_channel);
      }
      if (drone_jam_method == 1){
        for (int i = 0; i < 125; i++){
          radio.setChannel(i);
          radio1.setChannel(i);
        }
      }
    }
  }
}
void ble_jam(){
  HSPI_init();
  VSPI_init();
  while (true){
    if (Separate_or_together == 0){
      for (int i = 0; i < 3; i++){
        radio.setChannel(ble_channels[i]);
        radio1.setChannel(ble_channels_reversed[i]);
      }
    }
    if (Separate_or_together == 1){
      for (int i = 0; i < 3; i++){
        radio.setChannel(ble_channels[i]);
        radio1.setChannel(ble_channels[i]);
      }
    }
  }
}
void wifi_jam(){
  HSPI_init();
  VSPI_init();
  while (true){
    if (Separate_or_together == 0){
      for (int channel = 0; channel < 13; channel++) {
        for (int i = (channel * 5) + 1; i < (channel * 5) + 23; i++) {
          radio.setChannel(i);
          radio1.setChannel(83-i);
          radio.writeFast(&jam_text, sizeof(jam_text));
          radio1.writeFast(&jam_text, sizeof(jam_text));
        }
      }
    }
    if (Separate_or_together == 1){
      for (int channel = 0; channel < 13; channel++) {
        for (int i = (channel * 5) + 1; i < (channel * 5) + 23; i++) {
          radio.setChannel(i);
          radio1.setChannel(i);
          radio.writeFast(&jam_text, sizeof(jam_text));
          radio1.writeFast(&jam_text, sizeof(jam_text));
        }
      }
    }
  }
}