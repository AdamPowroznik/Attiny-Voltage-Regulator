int zmienna_pomiaru_ADC;

void setup() {
  DDRB |= (1<<PB1);
  PORTB |= (1<<PB3);
  wczytaj_ustawienia_ADC();
  wczytaj_ustawienia_PWM();
}

void loop() {
  zmienna_pomiaru_ADC = pomiar_napiecia();
  if(zmienna_pomiaru_ADC < 5)
    OCR0B = 0; 
  else if(zmienna_pomiaru_ADC > 230)
    OCR0B = 255;
  else
    OCR0B = (zmienna_pomiaru_ADC);
  }


int pomiar_napiecia(void){
  ADCSRA |= (1<<ADSC);
  while(ADCSRA & (1<<ADSC));
  return ADCH;
}

void wczytaj_ustawienia_ADC(void){
    ADMUX |= (1<<MUX0) | (1<<MUX1); // Wybranie ADC3 czyli PB3
    ADMUX |= (1<<ADLAR); //przesunięcie wyniku pomiaru do 8 bit
    ADCSRA |= (1<<ADPS0) | (1<<ADPS2) | (1<<ADEN); //adc prescaler - 32
}

void wczytaj_ustawienia_PWM (void){
  TCCR0B |= (1<<CS00); //prescaler
  TCCR0A |= (1<<WGM01 | (1<<WGM00)); //fast PWM
  TCCR0A |= (1<<COM0B1); //compare match metod
}
