
/*
 * code created by tim teacher productive PPLG SMKN 2 BJM
 * 2013
 * open source (boleh di modifikasi sesuai kebutuhan)
 */


// memasukkan library untuk mengaktifkan wifi pada nodemcu
#include <ESP8266WiFi.h>


//pemebrian nama untuk mode access point
// nodemcu memancanrkan sinyal wifi yang bisa terhubbung dengan smartphone
//ganti nama access-point dengan nama kelompok masing masing
const char* ssid     = "Kelompok 4 PPLGB";

// port untuk webserver
WiFiServer server(80);

// mendefinisikan variavel untuk header http request
String header;

// variabel status untuk digital 4 pada nodemcu esp8266
String outputD4status = "off";

//mendifinisakan kalau D4 yang akan digunakan untuk memati dan hidupkan D4
const int outputD4 = D4;

void setup() {
  // mengaktifkan pin mode yang akan digunakan untuk mengaktifkan pompa air
  pinMode(outputD4, OUTPUT);
 
  // mengatur dalam posisi d4 mati dengan menggunakan HIGH, karna menggunakan tipe relay yang aktif jika dalam kondisi LOW
  digitalWrite(outputD4, HIGH);



  
  // mengaktifkan wifi 
  WiFi.softAP(ssid);

  
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // memperbolehkan client mengakses web server dari hp ke nodemcu

  if (client) {                             // jika ada client baru konek,
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
        

        
            if (header.indexOf("GET /D4/on") >= 0)
            {
              outputD4status = "on";
              digitalWrite(outputD4, LOW);
            } 
            else if (header.indexOf("GET /D4/off") >= 0)
            {
 
              outputD4status = "off";
              digitalWrite(outputD4, HIGH);
            }
             
            
             
            // TAMPILAN UNTUK HALAMAN WEB
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // fontawesome link
            client.println("@import url('https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.3/css/all.min.css');");
            // bootstrap link
            client.println("@import url('https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha3/dist/css/bootstrap.min.css');");

            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>");
            client.println(".btn {padding: 16px 40px; margin: 2px; font-size: 22px;;}");
            client.println("body {background-color: #d1e5f4;}");
            client.println("</style></head>");

            // Web Page Heading
            client.println("<body>");
            client.println("<h1>LAC'FUME PRODUCT</h1>");
            client.println("<h1>PENGHARUM RUANGAN OTOMATIS</h1>");
            
            // navbar
            client.println("<nav class='navbar navbar-expand-lg navbar-dark bg-dark p-3'>");
            client.println("<div class='container-fluid'>");
            client.println("<a class='navbar-brand' href='#'>Lac'fume</a>");
            client.println("<button class='navbar-toggler' type='button' data-bs-toggle='collapse' data-bs-target='#navbarSupportedContent' aria-controls='navbarSupportedContent' aria-expanded='false' aria-label='Toggle navigation'>");
            client.println("<span class='navbar-toggler-icon'></span>");
            client.println("</button>");
            client.println("<div class='collapse navbar-collapse' id='navbarSupportedContent'>");
            client.println("<ul class='navbar-nav mb-2 mb-lg-0'>");
            client.println("<li class='nav-item'>");
            client.println("<a class='nav-link active' aria-current='page' href='#'>Home</a>");
            client.println("</li>");
            client.println("<li class='nav-item dropdown'>");
            client.println("<a class='nav-link dropdown-toggle' href='#' role='button' data-bs-toggle='dropdown' aria-expanded='false'>");
            client.println("More");
            client.println("</a>");
            client.println("<ul class='dropdown-menu dropdown-menu dropdown-menu-dark'>");
            client.println("<li><a class='dropdown-item' target='_blank' href='https://www.instagram.com/lac.fume'>Instagram Lac'fume</a></li>");
            client.println("<li><a class='dropdown-item' target='_blank' href='https://api.whatsapp.com/send?phone=6287816983631'>Contact Developer</a></li>");
            client.println("<li><hr class='dropdown-divider'></li>");
            client.println("<li><a class='dropdown-item' target='_blank' href='https://rentry.co/lecfume'>Usage Procedure</a></li>");
            client.println("</ul>");
            client.println("</li>");
            client.println("</ul>");
            client.println("</div>");
            client.println("</div>");
            client.println("</nav>");
            client.println("<br />");
            client.println("<br />");

            // button
            client.println("<br>");
            client.println("<p>D4 - status " + outputD4status + "</p>");
            client.println("<div class='container my-3 d-flex align-items-center justify-content-center'>");
            client.println("<div class='p-5 bg-white border rounded shadow-sm text-center' style='width: 300px;'>");
            
            // jika outputD4status adalah off, maka button akan berubah menjadi ON button      
            if (outputD4status == "off") {
              client.println("<p><a href='/D4/on' class='btn btn-success'><i class='fas fa-power-off'></i> ON</a></p>");
            } else {
              client.println("<p><a href=\"/D4/off\"> class='btn btn-danger'><i class='fas fa-power-off'></i> OFF</a></p>");
            }
            client.println("</div>");
            client.println("</div>");


            // footer
            client.println("<footer class='bg-dark text-light text-end pb-3 p-2' style='position: absolute; bottom: 0; width: 100%'>");
            client.println("<p>Created website by <a href='https://github.com/fesloth' target='_blank' style='text-decoration: none;' class='text-warning fw-bold'>Developer Lac'fume</a></p>");
            client.println("</footer>");

            // script 
            client.println("<script src='https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha3/dist/js/bootstrap.bundle.min.js'></script>");

            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}