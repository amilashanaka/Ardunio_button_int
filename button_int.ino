//testing interrupt on pin2, Arduino UNO Rev 3
const byte interruptPin = 2;
volatile bool state = LOW;

void setup() 
{
    pinMode( interruptPin, INPUT_PULLUP );
    Serial.begin(115200);
    Serial.flush();
    Serial.println("Started");
    pinMode( interruptPin, INPUT_PULLUP );
    attachInterrupt(digitalPinToInterrupt(interruptPin), ISR_button_pressed, FALLING);
}

void loop() 
{
    if (state)//if an interrup has occured
    {
        Serial.print("Interrupt at time "); Serial.println(millis());
        delay(1000);//simulate task executing
        if (digitalRead(interruptPin))//if button is released let ISR set flag.
        {
            attachInterrupt(digitalPinToInterrupt(interruptPin), ISR_button_pressed, FALLING );
            state = false;//reset interrupt flag
        }
            
    }
}


void ISR_button_pressed(void) 
{
    if (!state)//set flag to low if flag is true
    {
        state = true;//set flag
        detachInterrupt( digitalPinToInterrupt(interruptPin) );
        
    }//if
}