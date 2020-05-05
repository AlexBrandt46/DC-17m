// 60 rounds/magazine
// 300 rounds max in gun

const int firePin = 8;
const int ledPin = 9;
const int buzzPin = 7;
const int reloadPin = 6;

int firingState = 0;

int totalAmmo = 300;      // The max ammo the gun hold before resetting
int magAmmo = 60;               // The ammo count of the magazine currently in the gun

void setup() {
  Serial.begin(115200);
  Serial.println("starting");
  pinMode(ledPin, OUTPUT);
  pinMode(firePin, INPUT_PULLUP);
  pinMode(buzzPin, OUTPUT);
  pinMode(reloadPin, INPUT_PULLUP);
}

void loop() {

  // Read the button state for the trigger button (pressed or not pressed)
  firingState = digitalRead(firePin);

  // Check that there's still ammo in the current magazine and in the gun
  if (firingState == HIGH && magAmmo > 0 && totalAmmo > 0) {
    magAmmo -= 1;
    Serial.println(magAmmo);
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzPin, HIGH);
    delay(50);
  } 
  else if (firingState == LOW) {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzPin, LOW);

    if (digitalRead(reloadPin) == HIGH) {
      reload();
      Serial.println(totalAmmo);
      Serial.println(magAmmo);
    }
  }

  delay(100);
  
}

void reload() {
  // Check whether to remove a full magazine from the total ammo left or just what's left if there's less than a full magazine left
  if (totalAmmo >= 60) {
    totalAmmo -= (60 - magAmmo);
    magAmmo = 60;           // Add 60 rounds to the magazine
  }
  else if (totalAmmo != 0) {
    magAmmo = totalAmmo;
    totalAmmo = 0;
  }

  delay(300);
  
}
