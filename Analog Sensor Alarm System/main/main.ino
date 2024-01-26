// Définition des constantes
#define POT_PIN A0 // broche du potentiomètre
#define LED_R 11 // broche de la LED rouge
#define LED_V 12 // broche de la LED verte
#define LED_B 13 // broche de la LED bleue
#define SEUIL_BAS 307 // seuil bas pour l'alarme (1,5 V)
#define SEUIL_HAUT 716 // seuil haut pour l'alarme (3,5 V)

// Déclaration des variables globales
volatile int sensorValue = 0; // valeur lue du potentiomètre

void setup() {
  // Configuration des broches
  pinMode(POT_PIN, INPUT); // potentiomètre en entrée
  pinMode(LED_R, OUTPUT); // LED rouge en sortie
  pinMode(LED_V, OUTPUT); // LED verte en sortie
  pinMode(LED_B, OUTPUT); // LED bleue en sortie
  
  // Configuration du timer2
  TCCR2A = (1 << WGM21); // mode CTC, pas de sortie
  TCCR2B = (1 << CS21); // prédiviseur de 8
  OCR2A = 9; // valeur de comparaison pour 10 µs
  TIMSK2 = (1 << OCIE2A); // interruption activée sur match
  
  // Configuration du port série
  Serial.begin(9600); // vitesse de 9600 bauds
}

void loop() {
  // Affichage de la valeur lue sur le port série
  Serial.print("Valeur du capteur : ");
  Serial.println(sensorValue);
}

// Routine d'interruption du timer2
ISR(TIMER2_COMPA_vect) {
  // Lecture du potentiomètre
  sensorValue = analogRead(POT_PIN);
  
  // Mise à jour de la LED RVB
  if (sensorValue < SEUIL_BAS) { // alarme basse
    digitalWrite(LED_R, LOW); // LED rouge éteinte
    digitalWrite(LED_V, LOW); // LED verte éteinte
    digitalWrite(LED_B, HIGH); // LED bleue allumée
  }
  else if (sensorValue > SEUIL_HAUT) { // alarme haute
    digitalWrite(LED_R, HIGH); // LED rouge allumée
    digitalWrite(LED_V, LOW); // LED verte éteinte
    digitalWrite(LED_B, LOW); // LED bleue éteinte
  }
  else { // valeur normale
    digitalWrite(LED_R, LOW); // LED rouge éteinte
    digitalWrite(LED_V, HIGH); // LED verte allumée
    digitalWrite(LED_B, LOW); // LED bleue éteinte
  }
}
