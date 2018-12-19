//FUNGSI UNTUK MELAKUKAN GET
String get_request(String url_api_get){
  HTTPClient http_get;
  http_get.begin(url_api_get);

  String payload;

  int httpCode_get = http_get.GET(); //Melakukan method GET
  Serial.println(httpCode_get);
    if (httpCode_get > 0) { //Check the returning code
 
      payload = http_get.getString();       //Mengambil data pada get berupa string
      Serial.println(payload);              //Melihat data hasil dari get
      Serial.println("COMPLETE");           //Debug sederhana (Optional)
    }
  http_get.end(); //menutup koneksi http_get
  return payload;
}
/////////////////////////////

//FUNGSI UNTUK MELAKUKAN POST
String post_request(String url_api_post, String content_type, char jsonMessage[]){
  HTTPClient http_post;
  http_post.begin(url_api_post);
  http_post.addHeader("Content-Type", content_type);

  String payload;

  int httpCode_post = http_post.POST(jsonMessage);
  Serial.println(httpCode_post);
    if (httpCode_post > 0) { //Check the returning code
 
      payload = http_post.getString();   //Mengambil request respon akibat dari post
      Serial.println(payload);                     //Print the response payload2
      Serial.println("COMPLETE");
    }
  http_post.end(); //menutup koneksi http_get

  reset_string_data();
  return payload;
}
//////////////////////////////////

//PARSING HASIL PEMBACAAN BLUETOOTH//
/*Global variable pembacaan bluetooth*/
String soil_temperature;
String soil_vwc;
String soil_ec;
String soil_salinity;
String soil_tds;
String soil_epsilon;
String air_humidity;
String air_temperature;
String air_gas_quality;

void parsing_data(String received_data){
  Serial.println("--PARSING START--");
  
  int data_loc[9]; //membaca lokasi data
  data_loc[0]=received_data.indexOf('#');
  soil_temperature=received_data.substring(1, data_loc[0]);
  Serial.println(soil_temperature);
  
  data_loc[1]=received_data.indexOf('#', data_loc[0]+1);
  soil_vwc=received_data.substring(data_loc[0]+1, data_loc[1]);
  Serial.println(soil_vwc);
  
  data_loc[2]=received_data.indexOf('#', data_loc[1]+1);
  soil_ec=received_data.substring(data_loc[1]+1, data_loc[2]);
  Serial.println(soil_ec);

  data_loc[3]=received_data.indexOf('#', data_loc[2]+1);
  soil_salinity=received_data.substring(data_loc[2]+1, data_loc[3]);
  Serial.println(soil_salinity);
  
  data_loc[4]=received_data.indexOf('#', data_loc[3]+1);
  soil_tds=received_data.substring(data_loc[3]+1, data_loc[4]);
  Serial.println(soil_tds);

  data_loc[5]=received_data.indexOf('#', data_loc[4]+1);
  soil_epsilon=received_data.substring(data_loc[4]+1, data_loc[5]);
  Serial.println(soil_epsilon);

  data_loc[6]=received_data.indexOf('#', data_loc[5]+1);
  air_humidity=received_data.substring(data_loc[5]+1, data_loc[6]);
  Serial.println(air_humidity);

  data_loc[7]=received_data.indexOf('#', data_loc[6]+1);
  air_temperature=received_data.substring(data_loc[6]+1, data_loc[7]);
  Serial.println(air_temperature);

  data_loc[8]=received_data.indexOf('*', data_loc[7]+1);
  air_gas_quality=received_data.substring(data_loc[7]+1, data_loc[8]);
  Serial.println(air_gas_quality); 

  Serial.println("--PARSING COMPLETE--");
}
//////////////////////////////////////////////////////////////////


//FUNGSI ENCODER DALAM FORMAT JSON//
void encode_to_json(){
  StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer. Tidak harus 300, sesuai kebutuhuan
  JsonObject& JsonEncoding = JSONbuffer.createObject();

  JsonEncoding["soil_temperature"] = soil_temperature;
  JsonEncoding["soil_vwc"] = soil_vwc;
  JsonEncoding["soil_ec"] = soil_ec;
  JsonEncoding["soil_salinity"] = soil_salinity;
  JsonEncoding["soil_tds"] = soil_tds;
  JsonEncoding["soil_epsilon"] = soil_epsilon;
  JsonEncoding["air_humidity"] = air_humidity;
  JsonEncoding["air_temperature"] = air_temperature;
  JsonEncoding["air_gas_quality"] = air_gas_quality;
  
  JsonEncoding.prettyPrintTo(JsonMessageToSend, sizeof(JsonMessageToSend)); //Mengatur tulisan agar dicetak dalam format json
  
}

//RESET STRING UNTUK PARSING BERIKUTNYA
void reset_string_data(){
  soil_temperature = "";
  soil_vwc = "";
  soil_ec = "";
  soil_salinity = "";
  soil_tds = "";
  soil_epsilon = "";
  air_humidity = "";
  air_temperature = "";
  air_gas_quality = "";
}
/////////////////////////////////////////

//KOMUNIKASI KE INTERNET
void post_get_start(){
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    
    Serial.println("BEGIN"); //Debug sederhana (Optional)

    Serial.println("Bellow is data that will be posted:");
    Serial.println(JsonMessageToSend); //Mencetak dalam format json
    
    //MELAKUKAN GET..
    String url_get = "http://aizd-webservice.herokuapp.com/api/v1/alpha"; //Masukkan url api untuk melakukan get*****
    String hasil_get = get_request(url_get); //Memanttp://aizd.herokuapp.com/api/v1/pot-nodesggil fungsi get_request lalu disimpan pada pada string hasil_get
    Serial.println("Berikut adalah hasil dari get:");
    Serial.println(hasil_get);
    //////////////////

    //MELAKUKAN POST..
    String url_post = "http://aizd-webservice.herokuapp.com/api/v1/alpha/5c19304cb1b6b100044cdb1a"; //Masukkan url api untuk melakukan post****
    String content_type_post = "application/json"; //Masukkan content-type sesuai dengan program pada back-end
    String hasil_post = post_request(url_post, content_type_post, JsonMessageToSend);
    Serial.println("Berikut adalah hasil dari post:");
    Serial.println(hasil_post);
    ////////////////////
 
  }
}
////////////////////////////////


