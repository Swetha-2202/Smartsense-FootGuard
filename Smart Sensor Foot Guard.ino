# Smartsense-FootGuard
IoT-based Diabetic Foot Ulcer Prevention System using ESP32
// ----------------------------
// SmartSense FootGuard
// 4 FSR + Potentiometer + Buzzer
// ----------------------------

// FSR Pins
#define HEEL_FSR      34
#define MIDFOOT_FSR   35
#define FOREFOOT_FSR  32
#define TOE_FSR       33

// Potentiometer Pin
#define POT_PIN 39

// Buzzer Pin
#define BUZZER 25

void setup()
{
  Serial.begin(115200);

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  Serial.println("=================================");
  Serial.println(" SmartSense FootGuard Started ");
  Serial.println("=================================");
}

void loop()
{
  // Read FSR Values
  int heel     = analogRead(HEEL_FSR);
  int midfoot  = analogRead(MIDFOOT_FSR);
  int forefoot = analogRead(FOREFOOT_FSR);
  int toe      = analogRead(TOE_FSR);

  // Total Pressure
  int totalPressure =
      heel +
      midfoot +
      forefoot +
      toe;

  // Read Potentiometer
  int potValue = analogRead(POT_PIN);

  // Convert Potentiometer to Temperature
  // Range 25°C to 40°C
  float temperature =
      25.0 +
      ((float)potValue / 4095.0) * 15.0;

  String status;

  // Risk Logic
  if (temperature > 37.0 || totalPressure > 8000)
  {
    status = "HIGH RISK";

    digitalWrite(BUZZER, HIGH);
  }
  else if (temperature >= 36.0 || totalPressure > 4000)
  {
    status = "MONITOR";

    digitalWrite(BUZZER, LOW);
  }
  else
  {
    status = "SAFE";

    digitalWrite(BUZZER, LOW);
  }

  // Serial Output
  Serial.println("--------------------------------");

  Serial.print("Heel FSR      : ");
  Serial.println(heel);

  Serial.print("Midfoot FSR   : ");
  Serial.println(midfoot);

  Serial.print("Forefoot FSR  : ");
  Serial.println(forefoot);

  Serial.print("Toe FSR       : ");
  Serial.println(toe);

  Serial.print("TotalPressure : ");
  Serial.println(totalPressure);

  Serial.print("Temperature   : ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Status        : ");
  Serial.println(status);

  // Buzzer Status
  if(status == "HIGH RISK")
  {
    Serial.println("BUZZER ON");
  }
  else
  {
    Serial.println("BUZZER OFF");
  }

  delay(1000);
}
