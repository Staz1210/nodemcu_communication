
void loop() {

  if(BTSerial.available() > 0){
    char_received = BTSerial.read();
    string_received = string_received + char_received;
  }

  if(char_received == '*'){
    Serial.println(string_received);
    
    parsing_data(string_received); //Melakukan Parsing Data
    encode_to_json(); //Merubah Data Hasil Parsing ke dalam bentuk Json
    
    Serial.println("Below Is Encoded Data");
    Serial.println(JsonMessageToSend);

    post_get_start();
    
    string_received="";
  }
}
 
